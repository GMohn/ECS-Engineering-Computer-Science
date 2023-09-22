// this program prints the pascal triangle to the amount of user inputted rows
#include <stdio.h>
//declare pascal calculation function
void factorial(int n);

int main(){
    //prompt user
	int user_n;
	printf("Please enter how many levels of Pascal's Triangle you would like to see: ");
	scanf("%d", &user_n);
	//call function
	factorial(user_n);

	return 0;
}
//this function uses a 2D array to create columns and rows of the pascal triangle
void factorial(int levels){
//declare long int variables and 2D array to avoid integer overflow
	long i;
	long j;
	long rows[100][100];
//for loop to iterate amount of user inputted rows
	for (i = 0; i < levels; ++i){
            //nested for loop to get values for each element
		for (j = 0; j <= levels; ++j){
		    //if at the end of the row, then set to 1
			if (i == j || j == 0)
            {
                rows[i][j] = 1;
            }
            //else (a+b)^n
			else
				{rows[i][j] =rows[i-1][j-1] + rows[i-1][j];
				}
				//nested if statement, if the element is 0, pass
                if (rows[i][j] == 0){
					continue;
}
                //print every other element
				else{
					printf("%li ", rows[i][j]);
}

		printf("\n");
}

return ;
}
}
