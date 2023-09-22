#include "APInt.h"
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

  /* Your code to init APInt array, and operate on them here. */
    // Initialize an array of APInts.
  int arr_size;
  int num_read = fscanf(input, "%d", &arr_size);
  if (num_read != 1) {
        fprintf(stderr, "expected 1 element in ARRAY SIZE\n");
        exit(1);
      }
  APInt **apints = (APInt **)malloc(arr_size * sizeof(APInt *));
  for (int i = 0; i < arr_size; i++) {
    apints[i] = newAPInt(0);
  }
  // Process the input file.
  char buffer[MAX_LEN];
  int i = 0;

  while (fscanf(input, "%s", buffer) != EOF) {
    if (strcmp(buffer, "UINT64") == 0) {
      uint64_t val;
      int num_read = fscanf(input, "%lu", &val);
      if (num_read != 1) {
        fprintf(stderr, "expected 1 element in UINT64\n");
        exit(1);
      }
      memcpy(apints[i]->bytes, &val, apints[i]->size); // Copy the bytes of the uint64_t to the APInt
      i++;
    }
    else if (strcmp(buffer, "HEX_STRING") == 0) {
      int num_read = fscanf(input, "%s", buffer);
      if (num_read != 1) {
        fprintf(stderr, "expected 1 element in HEX_STRING\n");
        exit(1);
      }
      char *hex_str = buffer;
      uint64_t val = strtoull(hex_str, NULL, 16);
      memcpy(apints[i]->bytes, &val, apints[i]->size);
      i++;
    }
    else if (strcmp(buffer, "CLONE") == 0) {
      int idx;
      int num_read = fscanf(input, "%d", &idx);
      if (num_read != 1) {
        fprintf(stderr, "expected 1 element in CLONE line\n");
        exit(1);
      }
      APInt* cloned = APInt_clone(apints[idx]);
      APInt_destroy(apints[i]);
      apints[i] = cloned;
      i++;
    }
    else if (strcmp(buffer, "DUMP") == 0) {
      for (int i = 0; i < arr_size ; i++){
        APInt_print(&apints[i], output);
      }
      fprintf(output, "\n");
    }
    else if (strcmp(buffer, "SHL") == 0) {
      int dst, src;
      uint64_t k;
      int num_read = fscanf(input, "%d %d %lu", &dst, &src, &k);
      if (num_read != 3) {
        fprintf(stderr, "expected 3 elements in SHL line\n");
        exit(1);
      }
      APInt_lhs(apints, dst, src, k);
    }
    else if (strcmp(buffer, "ADD") == 0) {
      int op1, op2, dst;
      int num_read = fscanf(input, "%d %d %d", &dst, &op1, &op2);
      if (num_read != 3) {
        fprintf(stderr, "expected 3 elements in ADD line\n");
        exit(1);
      }
      APInt_add(&apints[dst], &apints[op1], &apints[op2]);
    }
    else if (strcmp(buffer, "MUL_UINT64") == 0) {
      uint64_t dst, src, k;
      int num_read = fscanf(input, "%lu %lu %lu", &dst, &src, &k);
      if (num_read != 3) {
        fprintf(stderr, "expected 3 elements in MUL_UINT64 line\n");
        exit(1);
      }
      APInt_multiply_uint64(&apints[dst], &apints[src], k);
    }
    else if (strcmp(buffer, "MUL_APINT") == 0) {
      int dst, op1, op2;
      int num_read = fscanf(input, "%d %d %d", &dst, &op1, &op2);
      if (num_read != 3) {
        fprintf(stderr, "expected 3 elements in MUL_APINT line\n");
        exit(1);
      }
      APInt_multiply(&apints[dst], &apints[op1], &apints[op2]);
    }
    else if (strcmp(buffer, "CMP") == 0) {
      int op1, op2;
      int num_read = fscanf(input, "%d %d", &op1, &op2);
      if (num_read != 2) {
        fprintf(stderr, "expected 2 elements in CMP line\n");
        exit(1);
      }
      fprintf(output,"%d\n",APInt_compare(&apints[op1],&apints[op2]));
    }
    else if (strcmp(buffer, "POW") == 0) {
      int dst, src, k;
      int num_read = fscanf(input, "%d %d %d", &dst, &src, &k);
      if (num_read != 3) {
        fprintf(stderr, "expected 3 elements in POW line\n");
        exit(1);
      }
      APInt_power(&apints[dst],&apints[src],k,arr_size);
    }
    else if (strcmp(buffer, "END") == 0){
      break;
    }
    else break;
  }
  // Free the array of APInts.
  for (int i = 0; i < arr_size; i++){
    APInt_destroy(apints[i]);
  }
  free(apints);
  //APInt_destroy(apints);


  // Close the files we opened.
  if (outputGiven)
    fclose(output);
  if (inputGiven)
    fclose(input);

  return 0;
}
