//This program adds and prints the matrices provided by the user inputs
#include <stdio.h>
int matrix_sum(int rows, int columns);
int main()
{
    //declare row and column vars
   int rows, columns;

   printf("Please enter the number of rows: ");
   scanf("%d", &rows);

   printf("Please enter the number of columns: ");
   scanf("%d", &columns);
   //call function with rows and columns as params
   matrix_sum(rows, columns);
   return 0;
}
int matrix_sum(int rows, int columns){
    //declare i and j to iterate loops, first and second matrix, and create sum of the two
    int i, j, second[100][100], sum[100][100];
    int** first;
    first = malloc(rows*sizeof(int));
     printf("Enter Matrix A\n");
//for loop to iterate row and columns to get user vars in each element
   for (i = 0; i < rows; i++)
      for (j = 0; j < columns; j++)
         scanf("%d", &(*(*first)[i])[j]);

   printf("Enter Matrix B\n");
//same for loop as before
   for (i = 0; i < rows; i++)
      for (j = 0 ; j< columns; j++)
            scanf("%d", &second[i][j]);

   printf("A + B =\n");
//for each iteration, add both matrices of corresponding cells to a new 2D array
   for (i = 0; i < rows; i++) {
      for (j = 0 ; j < columns; j++) {
         sum[i][j] = first[i][j] + second[i][j];
         printf("%d ", sum[i][j]);
      }
      printf("\n");
   }

}
