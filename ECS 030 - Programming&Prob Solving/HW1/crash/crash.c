#include <stdio.h>


int main() {
	double train_1_Miles = 0.00; //set variables of starting pos
	double train_2_Miles = 0.00;
	double train_1_Mph = 0.00; //set variables of speed in mph
	double train_2_Mph = 0.00;

	printf("Please enter the starting position of train 1: "); //prompt user for given values
	scanf("%lf", &train_1_Miles);

	printf("Please enter the speed of train 1: ");
	scanf("%lf", &train_1_Mph);

	printf("Please enter the starting position of train 2: ");
	scanf("%lf", &train_2_Miles);

	printf("Please enter the speed of train 2: ");
	scanf("%lf", &train_2_Mph);

	double time_Crash = (train_2_Miles - train_1_Miles) / (train_1_Mph + train_2_Mph); // for time in hours subtract train distance and divide by sum of mph

	double distance_Crash = (train_1_Mph * time_Crash) + train_1_Miles; //distance = rate * time + initial distance

	printf("The two trains will collide in %.2f hours %.2f miles down the track.", time_Crash, distance_Crash);
	return 0;
}




