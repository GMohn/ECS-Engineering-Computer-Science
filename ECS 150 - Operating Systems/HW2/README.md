# ECS 150 proj2

# libuthread: User-level thread library
## Summary
This project is a implmentation of a user level thread library. It is based on
parts of the pthread library.
## Implementation
The implementation of this program follows these steps:
1. Creating a First in First out linked listed queue  in order to satisfy given
   time complexities of functions.
2. Develop a user thread library in order to create, start and manipulate
   threads inside a process.
3. Create a semaphore style lock in order to better schedule threads.


### Linked list queue
To implement O(1) operations, the queue had to be created as a linked list. The
rear of the queue has a pointer `tail` that points the last element in the
queue. The tail moves for the `enqueue` operation. At the front of the queue, a
`head` pointer always points to the front. the head moves during the `dequeue`
operation. Each node is populated with given `data` and `next` which gives the
address of the next node in the list.
### User Level Thread
The thread control block kept track of `context`, `state`, `func`, `arg`, and
`top_of_stack`. The `context` was used to switch between threads. The `state`
would keep track of whether the thread is: ready, idle, running, blocked, or
exited. The main thread that calls `uthread_run` would be store in a global
queue called `idle_threads`. First we check if the normal threads `queue` has
been initialized. After ensuring `queue` has been created, an `initial_thread`
is allocated memory and calls `uthread_create`. After that, the threads are
enqueued to their respective queues. A context switch between `main_thread` and
`initial_thread` occurs and a while loop that checks `queue_length(queue)` calls
`uthread_yield` if there are more threads to run in the queue. `uthread_yield`
caused a lot of queue issues due to the numerous `queue_dequeue` calls in order
to populate a given thread. This issue forced the creation of a helper function,
`fix_queue` that ensured the running thread was at the top of the queue. This
would later create more problems when dealing with blocked threads as building
on top of it was a nightmare. `fix_queue` had to be called for most
`queue_dequeue` calls and later to update the current running thread. The
`uthread_exit` function is similar to the run function because there is a queue
length check; if there are still threads remaining we call `uthread_yield` other
wise context switch `running_thread` with `main_thread`
### Semaphore
The implementation of semaphore was fairly straight forward, however due to the
complex movement of a thread's data, the `queue` would sometimes hold bad
threads or remove threads when trying to populate a variable. The `sem_create`
function allocates space for the semaphore structure as well as initializes a
new queue called `wait_list`. `sem_down` tries to acquire a resource (`count`)
and if it is not available, removes them from the normal `queue` and puts it in
the new `wait_list`. It then calls `uthread_block` where the current running
thread becomes blocked, and gets the front of the queue to context switch with
it. This would keep the `next_thread` in `queue` while also removing
`current_thread` in sem_down. the `sem_up` function would increment first, then
check the count and it is greater than 0, it would dequeue the front of
`wait_list` and call `uthread_unblock` where the newly unblocked thread would
context switch with the current running thread, while also keeping them both in
`queue`.


### Sources

[linked list of queue](https://www.youtube.com/watch?v=A5_XdiK4J8A&ab_channel=mycodeschool)<br />
[How semaphores work](https://youtu.be/ukM_zzrIeXs)<br />
[Using structs accross files](https://stackoverflow.com/questions/3041797/how-to-use-a-defined-struct-from-another-source-file)<br />
[linux man page pthread_create](https://man7.org/linux/man-pages/man3/pthread_create.3.html)<br />
[return in struct pointer](https://stackoverflow.com/questions/34377423/c-return-struct-pointer)<br />
[pthread yield](https://stackoverflow.com/questions/65380997/how-does-the-function-pthread-yield-work)<br />
[semaphore synchronization](https://www.geeksforgeeks.org/semaphores-in-process-synchronization/)<br />
[linking static libraries](https://tldp.org/HOWTO/Program-Library-HOWTO/static-libraries.html)<br />
[static linking issues](https://stackoverflow.com/questions/20962152/static-library-linking-issues-no-reference-to-main-or-no-reference)<br />
[ucontext.h](https://pubs.opengroup.org/onlinepubs/7908799/xsh/ucontext.h.html)<br />
[linux semaphore.h](https://github.com/torvalds/linux/blob/master/include/linux/semaphore.h)<br />
