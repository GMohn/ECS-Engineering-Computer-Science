#include "quick_sort.h"
#include "GenericTraits.h"
#include "Int.h"

void quick_sort(GenericTraits **array[], int n) {

    if (n <= 1) {
      return;
    }
    // Print the subarray before sorting
    /*printf("Subarray: \n");
    for (int i = 0; i < n; i++) {
        (*array[i])->dump(array[i], stdout);
    }*/
    // Choose the pivot as the last element

    GenericTraits **pivot = array[n - 1];

    // Print the pivot
    /*printf("Pivot: \n");
    (*pivot)->dump(pivot, stdout);
    printf("\n");*/
    // Partition the array
    int left = 0;
    int right = n - 2;

    while (left <= right) {
        //fprintf(stderr,"here");
        while (left <= right && (*array[left])->cmp(array[left], pivot) >= 0) {
          //printf("left is greater than or equal to pivot\n");
          //printf("Incrementing left\n");
          left++;
        }
        while (left <= right && (*array[right])->cmp(array[right], pivot) < 0) {
            //printf("left is less than the pivot\n");
            //printf("Decrementing right\n");
            right--;
        }

        if (left < right) {
            // Swap array[left] and array[right]
            GenericTraits **temp = array[left];
            array[left] = array[right];
            array[right] = temp;

            // Print the swap
            //printf("Swapped elements at indices %d and %d\n", left, right);
        }
    }

    // Move the pivot to its final position
    GenericTraits **temp = array[right + 1];
    array[right + 1] = array[n - 1];
    array[n - 1] = temp;

    // Print the pivot
    //printf("Pivot: element at index %d\n", right + 1);

    // Recursively sort the sub-arrays
    quick_sort(array, right + 1);
    quick_sort(array + right + 2, n - right - 2);
}



