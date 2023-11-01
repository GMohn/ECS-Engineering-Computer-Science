#include <stdio.h>
#include <unistd.h>

int a = 42;

int main(int argc, char *argv[])
{
	int b = 23;

	printf("Hello world!\n");
	fork();
	printf("My favorite number is %d.\n",
		   argc + a + b);

	return 0;
}
