#include <stdio.h>
#include <unistd.h>

int main(void)
{
	printf("Hello ");
	sleep(2);
	printf("world!\n");

	write(STDOUT_FILENO, "Hello ", 6);
	sleep(2);
	write(STDOUT_FILENO, "world!\n ", 7);

	return 0;
}
