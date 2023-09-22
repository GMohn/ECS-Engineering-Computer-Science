/* this program prompts the user for the vertices of a rectangular prism  and calculates the surface area and volume of the prism */

#include <stdio.h>
#include <math.h>

double get_dist(dist_a_x, dist_a_y, dist_a_z, dist_b_x, dist_b_y, dist_b_z){ //calculate the distance between 2 points of coord xyz
	double distance_evaluated = 0; //set variable of evaluated distance
	distance_evaluated = sqrt(Pow((dist_b_x - dist_a_x) , 2.00) + Pow((dist_b_y - dist_a_y) , 2.00) + Pow((dist_b_z - dist_a_z) , 2.00));

	return distance_evaluated;
}



}

double get_rect_area(length_rec, height_rec){ //calculate area of rectangle
	return (length_rec * height_rec);


}

double get_surface_area(dist_coord_01, dist_coord_12, dist_coord_34){ //return the sum of 2 times the three each rectangles by calling rect_area func of 3 rectangles 

	return (2 * get_rect_area(dist_coord_12, dist_coord_34)) + (2 * get_rect_area(dist_coord_34, dist_coord_01)) + (2 * get_rect_area(dist_coord_12, dist_coord_01));
}

double get_volume(dist_coord_01, dist_coord_12, dist_coord_34){ //return volume of Width * height * length
	return (dist_coord_01 * dist_coord_12 * dist_coord_34);
}


int main(){
/* setting variables for: evaluted distances from for loop stored into dist coord of the two edges, get_dist parameters and get_rect parameters, and 3 seperate user inputted coordinates */
	int i =0;
	double dist_coord_01 = 0;
	double dist_coord_12 = 0;
	double dist_coord_23 = 0;
	double dist_coord_34 = 0;
	double dist_coord_45 = 0;
	double dist_coord_56 = 0;
	double dist_coord_67 = 0;
	double distance_coordinates = 0;


	double user_First_Coordinate_x = 0;
	double user_First_Coordinate_y = 0;
	double user_First_Coordinate_z = 0;

	double user_Second_Coordinate_x = 0;
	double user_Second_Coordinate_y = 0;
	double user_Second_Coordinate_z = 0;

	double user_Third_Coordinate_x = 0;
	double user_Third_Coordinate_y = 0;
	double user_Third_Coordinate_z = 0;

	double user_Fourth_Coordinate_x = 0;
	double user_Fourth_Coordinate_y = 0;
	double user_Fourth_Coordinate_z = 0;

	double user_Fifth_Coordinate_x = 0;
	double user_Fifth_Coordinate_y = 0;
	double user_Fifth_Coordinate_z = 0;

	double user_Sixth_Coordinate_x = 0;
	double user_Sixth_Coordinate_y = 0;
	double user_Sixth_Coordinate_z = 0;

	double user_Seventh_Coordinate_x = 0;
	double user_Seventh_Coordinate_y = 0;
	double user_Seventh_Coordinate_z = 0;

	double user_Eighth_Coordinate_x = 0;
	double user_Eighth_Coordinate_y = 0;
	double user_Eighth_Coordinate_z = 0;
	
	printf("Enter the first coordinate in the form x y z: \n");// prompting user, stored in seperate values
	scanf("%lf %lf %lf", &user_First_Coordinate_x, &user_First_Coordinate_y, &user_First_Coordinate_z); 
 
	printf("Enter the second coordinate in the form x y z: \n");
	scanf("%lf %lf %lf", &user_Second_Coordinate_x, &user_Second_Coordinate_y, &user_Second_Coordinate_z);

	printf("Enter the third coordinate in the form x y z: \n");
	scanf("%lf %lf %lf", &user_Third_Coordinate_x, &user_Third_Coordinate_y, &user_Third_Coordinate_z);

	printf("Enter the fourth coordinate in the form x y z: \n");
	scanf("%lf %lf %lf", &user_Fourth_Coordinate_x, &user_Fourth_Coordinate_y, &user_Fourth_Coordinate_z);

	printf("Enter the fifth coordinate in the form x y z: \n");
	scanf("%lf %lf %lf", &user_Fifth_Coordinate_x, &user_Fifth_Coordinate_y, &user_Fifth_Coordinate_z);

	printf("Enter the sixth coordinate in the form x y z: \n");
	scanf("%lf %lf %lf", &user_Sixth_Coordinate_x, &user_Sixth_Coordinate_y, &user_Sixth_Coordinate_z);

	printf("Enter the seventh coordinate in the form x y z: \n");
	scanf("%lf %lf %lf", &user_Seventh_Coordinate_x, &user_Seventh_Coordinate_y, &user_Seventh_Coordinate_z);

	printf("Enter the eighth coordinate in the form x y z: \n");
	scanf("%lf %lf %lf", &user_Eighth_Coordinate_x, &user_Eighth_Coordinate_y, &user_Eighth_Coordinate_z);

// initial get_dist parameters of coord_a and coord_b are edges 0 to 1
	double coord_a_x = user_First_Coordinate_x;
	double coord_a_y = user_First_Coordinate_y;
	double coord_a_z = user_First_Coordinate_z;
	double coord_b_x = user_Second_Coordinate_x;
	double coord_b_y = user_Second_Coordinate_y;
	double coord_b_z = user_Second_Coordinate_z;

	for (i = 0; i <= 7; distance_coordinates = get_dist(coord_a_x, coord_a_y, coord_a_z, coord_b_x, coord_b_y, coord_b_z), ++i){// run for loop 8 times of func get_dist and store distance

		if (i == 0){// run if else statement to assign variables for each iteration
			dist_coord_01 = distance_coordinates;
			double coord_a_x = user_Second_Coordinate_x;
			double coord_a_y = user_Second_Coordinate_y;
			double coord_a_z = user_Second_Coordinate_z;
			double coord_b_x = user_Third_Coordinate_x;
			double coord_b_y = user_Third_Coordinate_y;
			double coord_b_z = user_Third_Coordinate_z;
// change parameters of get_dist to coords of edges 1 to 2 
			 
}
		else if (i == 1){ 
			dist_coord_12 = distance_coordinates;//coords of edges 1 to 2
			double coord_a_x = user_Third_Coordinate_x;
			double coord_a_y = user_Third_Coordinate_y;
			double coord_a_z = user_Third_Coordinate_z;
			double coord_b_x = user_Fourth_Coordinate_x;
			double coord_b_y = user_Fourth_Coordinate_y;
			double coord_b_z = user_Fourth_Coordinate_z; // new coords for edges 2 to 3
			
}
		else if (i == 2){
			dist_coord_23 = distance_coordinates;
			double coord_a_x = user_Fourth_Coordinate_x;
			double coord_a_y = user_Fourth_Coordinate_y;
			double coord_a_z = user_Fourth_Coordinate_z;
			double coord_b_x = user_Fifth_Coordinate_x;
			double coord_b_y = user_Fifth_Coordinate_y;
			double coord_b_z = user_Fifth_Coordinate_z;
}
		else if (i == 3){
			dist_coord_34 = distance_coordinates;
			double coord_a_x = user_Fifth_Coordinate_x;
			double coord_a_y = user_Fifth_Coordinate_y;
			double coord_a_z = user_Fifth_Coordinate_z;
			double coord_b_x = user_Sixth_Coordinate_x;
			double coord_b_y = user_Sixth_Coordinate_y;
			double coord_b_z = user_Sixth_Coordinate_z;
}
		else if (i == 4){
			dist_coord_45 = distance_coordinates;			
			double coord_a_x = user_Sixth_Coordinate_x;
			double coord_a_y = user_Sixth_Coordinate_y;
			double coord_a_z = user_Sixth_Coordinate_z;
			double coord_b_x = user_Seventh_Coordinate_x;
			double coord_b_y = user_Seventh_Coordinate_y;
			double coord_b_z = user_Seventh_Coordinate_z;
}
		else if (i == 5){
			dist_coord_56 = distance_coordinates;			
			double coord_a_x = user_Seventh_Coordinate_x;
			double coord_a_y = user_Seventh_Coordinate_y;
			double coord_a_z = user_Seventh_Coordinate_z;
			double coord_b_x = user_Eighth_Coordinate_x;
			double coord_b_y = user_Eighth_Coordinate_y;
			double coord_b_z = user_Eighth_Coordinate_z;
}
		else if (i == 6){
			dist_coord_67 = distance_coordinates;
}
		else {
			return 0;
}

}
	printf("The surface area of the prism is %.2f", get_surface_area(dist_coord_01, dist_coord_12, dist_coord_34));			
	printf("The volume of the prism is %.2f", get_volume(dist_coord_01, dist_coord_12, dist_coord_34));
	return 0;
}









		
