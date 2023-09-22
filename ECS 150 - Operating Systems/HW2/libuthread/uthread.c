#include <assert.h>
#include <signal.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "private.h"
#include "uthread.h"
#include "queue.h"
// defining states of thread
#define UNUSED(x) (void)(x)
#define READY 0
#define IDLE 1
#define RUNNING 2
#define BLOCKED 3
#define EXITED 4


struct uthread_tcb {
	uthread_ctx_t *context;
	int state;
	uthread_func_t func;
	void* arg;
	void* top_of_stack;
};
// queue to store our threads
queue_t queue;
queue_t idle_queue;
struct uthread_tcb* main_thread;
struct uthread_tcb* running_thread;

struct uthread_tcb *uthread_current(void)
{

	return running_thread;
};


void fix_queue(queue_t queue)
{
	struct uthread_tcb *uthread_current;
	uthread_current = malloc(sizeof(struct uthread_tcb));
	uthread_current->top_of_stack = uthread_ctx_alloc_stack();
	uthread_current->context = uthread_ctx_alloc_stack();

	running_thread = malloc(sizeof(struct uthread_tcb));
	running_thread->top_of_stack = uthread_ctx_alloc_stack();
	running_thread->context = uthread_ctx_alloc_stack();
	queue_t hold;
	hold = queue_create();


	for (int i = 0,length = queue_length(queue); i < length ;i++) {
		if(!queue_dequeue(queue,(void**)&uthread_current)){
			// if not running
			if (uthread_current->state != RUNNING)
				queue_enqueue(hold,(void*)uthread_current);
			// running
			else
				running_thread = uthread_current;
		}
	}

	queue_enqueue(queue, running_thread);
	for (int i = 0,holdlen = queue_length(hold); i < holdlen;i++) {
		if(!queue_dequeue(hold,(void**)&uthread_current))
			queue_enqueue(queue, (void*)uthread_current);
	}
}
void uthread_yield(void)
{
	struct uthread_tcb *uthread_current;
	uthread_current = malloc(sizeof(struct uthread_tcb));
	uthread_current->top_of_stack = uthread_ctx_alloc_stack();
	uthread_current->context = uthread_ctx_alloc_stack();

	struct uthread_tcb* next_thread;
	next_thread = malloc(sizeof(struct uthread_tcb));
	next_thread->top_of_stack = uthread_ctx_alloc_stack();
	next_thread->context = uthread_ctx_alloc_stack();

	if(running_thread->state == EXITED) {
		if(!queue_dequeue(queue,(void**)&next_thread))
			queue_enqueue(queue,(void*)next_thread);
		next_thread->state = RUNNING;
		fix_queue(queue);
		uthread_ctx_switch(running_thread->context,next_thread->context);
	}
	fix_queue(queue);

	if(!queue_dequeue(queue,(void**)&uthread_current)) {
		if(!queue_dequeue(queue,(void**)&next_thread))
			next_thread->state = RUNNING;
		// if statement to check if state has been changed to block or exited
		if (uthread_current->state != RUNNING) {
			queue_enqueue(queue,(void*)next_thread);
		}
		else {
		uthread_current->state = READY;
		queue_enqueue(queue,(void*)next_thread);
		queue_enqueue(queue,(void*)uthread_current);
		}

		fix_queue(queue);
		uthread_ctx_switch(uthread_current->context,next_thread->context);

	}
}

void uthread_exit(void)
{
	int queue_len = queue_length(queue);
	if(!queue_dequeue(queue,(void**)&running_thread))
		running_thread->state = EXITED;
	// swap next avail thread
	if(queue_len>1) {
		uthread_yield();
	}
	//last running thread back to main
	else if(queue_len == 1) {
		struct uthread_tcb *next_thread;
		next_thread = malloc(sizeof(struct uthread_tcb));
		if(!queue_dequeue(idle_queue,(void**)&next_thread))
			uthread_ctx_switch(running_thread->context,next_thread->context);
	}

}

int uthread_create(uthread_func_t func, void *arg)
{
	/* TODO Phase 2 */
	struct uthread_tcb* new_thread = malloc(sizeof(struct uthread_tcb));
	if (new_thread == NULL)
		return -1;
	new_thread->context = malloc(sizeof(uthread_ctx_t));
	new_thread->func = func;
	new_thread->arg = arg;
	new_thread->state = READY;
	new_thread->top_of_stack = uthread_ctx_alloc_stack();
	queue_enqueue(queue,new_thread);
	if (new_thread->top_of_stack == NULL)
		return -1;
	if(uthread_ctx_init(new_thread->context,new_thread->top_of_stack,new_thread->func,new_thread->arg) == -1)
		return -1;

	return 0;

}

int uthread_run(bool preempt,uthread_func_t func, void *arg)
{

	if(preempt)
	{
		//preempt_start(preempt);
		//preempt_enable();
	}

	//  Cooperative thread model
	struct uthread_tcb* main_thread = malloc(sizeof(struct uthread_tcb));
	main_thread->context = malloc(sizeof(uthread_ctx_t));
	// check allocation worked
	if (main_thread == NULL||main_thread->context == NULL)
		return -1;
	// check if queue has been initialized. if it has then create the main thread.
	if(queue == NULL) {
		struct uthread_tcb *initial_thread;
		initial_thread = malloc(sizeof(struct uthread_tcb));
		initial_thread->top_of_stack = uthread_ctx_alloc_stack();
		initial_thread->context = uthread_ctx_alloc_stack();
		queue = queue_create();
		idle_queue = queue_create();
		main_thread->func = NULL;
		main_thread->state = IDLE;
		main_thread->arg = NULL;
		uthread_create(func, arg);
		if(!queue_dequeue(queue,(void**)&initial_thread)) {
			initial_thread->state = RUNNING;
			queue_enqueue(queue,(void*)initial_thread);
			queue_enqueue(idle_queue,(void*)main_thread);
			fix_queue(queue);
			uthread_ctx_switch(main_thread->context,initial_thread->context);
		}
	}
	// while there are threads ready to run
	while(queue_length(queue) >= 1) {
		// no more threads to run
		if(queue_length(queue) == 1) {
			struct uthread_tcb *final_thread;
			final_thread = malloc(sizeof(struct uthread_tcb));
			final_thread->top_of_stack = uthread_ctx_alloc_stack();
			final_thread->context = uthread_ctx_alloc_stack();
			if(!queue_dequeue(queue,(void**)&final_thread)) {
				final_thread->state = RUNNING;
				uthread_ctx_switch(main_thread->context,final_thread->context);
			}
			return 0;
		}
		else {
			uthread_yield();
		}
	}

	return 1;

}

void uthread_block(void)
{

	struct uthread_tcb* blocked_thread;
	blocked_thread = malloc(sizeof(struct uthread_tcb));
	blocked_thread = running_thread;
	blocked_thread->state = BLOCKED;
	struct uthread_tcb* next_thread;
	next_thread = malloc(sizeof(struct uthread_tcb));
	if(!queue_dequeue(queue,(void**)&next_thread)) {
		queue_enqueue(queue,next_thread);
		next_thread->state = RUNNING;
		fix_queue(queue);
		uthread_ctx_switch(blocked_thread->context,next_thread->context);
	}
	else {
		if (!queue_dequeue(idle_queue,(void**)&next_thread))
			uthread_ctx_switch(blocked_thread->context,next_thread->context);
	}

}
void uthread_unblock(struct uthread_tcb *uthread)
{
	fix_queue(queue);
	if(!queue_dequeue(queue,(void**)&running_thread)) {
		uthread->state = RUNNING;
		running_thread->state = IDLE;
		uthread_ctx_switch(running_thread->context,uthread->context);
	}
}

