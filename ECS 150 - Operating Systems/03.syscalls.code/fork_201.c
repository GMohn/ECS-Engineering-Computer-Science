#include <stdio.h>
#include <unistd.h>

int main(void)
{
    pid_t pid;

    pid = fork();
    if (pid > 0)
        printf("I'm the parent!\n");
    else if (pid == 0)
        printf("I'm the child!\n");
    else
        printf("I'm the initial process! "
			   "But something went wrong...\n");

    printf("I'm here now, bye!\n");
    return 0;
}
