//This program returns the Nth fibonacci number
#include <stdio.h>
#include <stdlib.h>
//declarations
int fib(int n, int a, int b);
int final_number (int nth_value, int final);

int main (int argc, char*argv[])
{
    int a = 1; // start fibonacci sequence at 1,0
    int b = 0;
    int final = fib(atoi(argv[1]), a, b);
    return final_number(atoi(argv[1]),final);
}




//this function uses recursion to compute the nth number of the fibonacci number
int fib(int n, int a, int b)
{

    if( n <= 0){
        return 0; //N should never be less than 0
    }
    else if (n == 1){
        return a + b;
    }
    return fib(n-1, b, a + b); // go down number of iterations while adding sum of previous

}
//this function prints out the final value
int final_number(int nth_value, int final)
{
    printf("The %dth fibanocci number is %d.",nth_value, final);
    return 0;
}
