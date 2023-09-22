/* ask user for a year and tells them whether or not the year is a leap year */
#include <stdio.h>
//declare leap year calculation
void leap_year(int year);
int main() {

	int user_Year = 0; // set variable of user inputted year
	printf("Please enter a year: "); // prompt user for input
	scanf("%d", &user_Year);
	leap_year(user_Year);

	return 0;
}
void leap_year(int year){

	if (year % 400 == 0){
		printf("%d is a leap year.", year);
}
	else if (year % 4 == 0 && year % 100 != 0){
		printf("%d is a leap year.", year);
}
	else {
		printf("%d is not leap year.", year);
}
return;
}
