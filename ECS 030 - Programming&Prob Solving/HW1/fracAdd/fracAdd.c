// Adds fractions together without simplifying
#include <stdio.h>

int main() {
	int first_Numerator = 0; //setting different variables for numerator and denominator
	int first_Denom = 0;
	int second_Numerator = 0;
	int second_Denom = 0;
	int fracNumerator =0;
	int fracDenom = 0;

	printf("Please enter the first fraction to be added: ");
	scanf("%i %*s %i", &first_Numerator, &first_Denom); //prompt user for both numerator and denom
	printf("Please enter the second fraction to be added: ");
	scanf("%i %*s %i", &second_Numerator, &second_Denom);
	
	fracNumerator = (second_Denom * first_Numerator) + (first_Denom * second_Numerator); //multiply denoms to both fractions
	fracDenom = (first_Denom * second_Denom);
	printf("%i/%i + %i/%i = %i/%i", first_Numerator, first_Denom, second_Numerator, second_Denom, fracNumerator, fracDenom); 

	return 0;
}

