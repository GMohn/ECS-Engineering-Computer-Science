#include "GenericTraits.h"
#include "quick_sort.h"
#include "Int.h"
#include "Human.h"
#include "Student.h"
#include "Rectangle.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 256

int main(int argc, char const *argv[]) {

  // Open the input and output files, use stdin and stdout if not configured.
  FILE *output = NULL;
  int outputGiven = (argc >= 3);
  if (!outputGiven)
    output = stdout;
  else
    output = fopen(argv[2], "w");

  FILE *input = NULL;
  int inputGiven = (argc >= 2);
  if (!inputGiven)
    input = stdin;
  else
    input = fopen(argv[1], "r");

  // Read the type of the object.
  char type[MAX_LEN];
  memset(type, 0, MAX_LEN);
  (void)!fscanf(input, "%s\n", type);

  // read the number of objects.
  int n = 0;
  (void)!fscanf(input, "%d\n", &n);

  // Get the constructor of the object.
  Constructor ctor = get_constructor(type);
  if (ctor == NULL) {
    fprintf(stderr, "Error: Constructor not found for type '%s'\n", type);
    return 1;
  }

  // Read the following n objects from the input.
  // Initialize them using prototype.
  GenericTraits **array[n];
  char tmp[MAX_LEN];
  for (int i = 0; i < n; i++) {
    memset(tmp, 0, MAX_LEN);
    (void)!fgets(tmp, MAX_LEN, input);
    /* Your code here to initialize the objects */
    if (strcmp(type, "Int") == 0) {
      array[i] = new_Int(tmp);

    }
    else if (strcmp(type, "Human") == 0) {
      array[i] = new_Human(tmp);
      //dump_Human(array[i], stdout);
    }
    else if (strcmp(type, "Student") == 0) {
      array[i] = new_Student(tmp);
    }
    else if (strcmp(type, "Rectangle") == 0) {
      array[i] = new_Rectangle(tmp);
    }
    else {
      fprintf(stderr, "Error: Unknown type '%s'\n", type);
      return 1;
    }
  }

  // Sort n objects.
  quick_sort(array, n);


  // Print n objects to output using dump.
  for (int i = 0; i < n; i++) {
    /* Your code here to print the sorted objects */
    if (strcmp(type, "Int") == 0) {
      dump_Int(array[i], output);
    }
    else if (strcmp(type, "Human") == 0) {
      dump_Human(array[i], output);
    }
    else if (strcmp(type, "Student") == 0) {
      dump_Student(array[i], output);
    }
    else if (strcmp(type, "Rectangle") == 0) {
      dump_Rectangle(array[i], output);
    }
  }

  /* Your code here to de-allocate the memories we have allocated. */
  for (int i = 0; i < n; i++) {
    // De-allocate objects based on the type
    if (strcmp(type, "Int") == 0) {
      drop_Int(array[i]);
    }
    else if (strcmp(type, "Human") == 0) {
      drop_Human(array[i]);
    }
    else if (strcmp(type, "Student") == 0) {
      drop_Student(array[i]);
    }
    else if (strcmp(type, "Rectangle") == 0) {
      drop_Rectangle(array[i]);
    }
  }
  // Close the files we opened.
  if (outputGiven)
    fclose(output);
  if (inputGiven)
    fclose(input);
  return 0;
}
