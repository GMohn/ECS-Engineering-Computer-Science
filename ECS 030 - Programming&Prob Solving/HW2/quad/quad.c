// user enters a the coefficients a, b and c and solves for x
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#define true 1
#define false 0

int quadratic(double coefficient_a, double coefficient_b, double coefficient_c){
    double quadratic_sqrt = 0;
	double quadratic_b1 = 0;
	double quadratic_b2 = 0;

	quadratic_sqrt = sqrt (coefficient_b * coefficient_b -(4 * coefficient_a * coefficient_c));	//isolate sqrt function

	quadratic_b1 = (-(coefficient_b) + quadratic_sqrt)/(2*coefficient_a); //use two vars for b+sqrt and b-sqrt
	quadratic_b2 = (-(coefficient_b) - quadratic_sqrt)/(2*coefficient_a);

/* if else statements to dictate whether they are are real solutions or not. Printing if they are.*/
	if ((isnan(quadratic_b1) == false) && isnan(quadratic_b2) == false && quadratic_b1 != quadratic_b2)
{
		printf("There are 2 real solutions\n");
		printf("Solution 1: %.2f\n", quadratic_b1);
		printf("Solution 2: %.2f\n", quadratic_b2);
}
	else if (isnan(quadratic_b1) == false){

		printf("There is one real solution: %.2f", quadratic_b1);
}
	else if (isnan(quadratic_b2) == false) {

		printf("There is one real solution: %.2f", quadratic_b2);
}
	else {
		printf("There are no real solutions");
}

return 0;
}

int main(){
	double quad_a = 0; //define variables of user input
	double quad_b = 0;
	double quad_c = 0;
	printf("Given a quadratic equation of the form a*x^2 + b * x + c\n");

	printf("Please enter a: \n"); // prompt user for inputs
	scanf("%lf", &quad_a);
	printf("Please enter b: \n");
	scanf("%lf", &quad_b);
	printf("Please enter c: \n");
	scanf("%lf", &quad_c);


	quadratic(quad_a, quad_b, quad_c);//call quadratic function
	return 0;
	}
