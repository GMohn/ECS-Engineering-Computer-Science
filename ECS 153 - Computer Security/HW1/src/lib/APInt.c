#include "APInt.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>

/* Constructive Methods */
/* Create a new APInt from a uint64_t */
APInt *newAPInt(uint64_t val) {
  APInt *apint = (APInt *)malloc(sizeof(APInt));
  apint->size = sizeof(uint64_t);
  apint->bytes = (uint8_t *)malloc(apint->size);
  memcpy(apint->bytes, &val, apint->size);
  return apint;
}

/* Convert APInt to uint64_t */
uint64_t apintToUint64(APInt **apint) {
  uint64_t val;
  memcpy(&val, (*apint)->bytes, sizeof(uint64_t));
  return val;
}

APInt* APInt_clone(APInt *src) {
  // Allocate memory for the new APInt
  APInt *dest = malloc(sizeof(APInt));
  if (dest == NULL) {
    fprintf(stderr, "Error: Failed to allocate memory for dest in APInt_clone\n");
    exit(1);
  }
  dest->size = src->size;
  dest->bytes = malloc(dest->size * sizeof(uint8_t));
  if (dest->bytes == NULL) {
    fprintf(stderr, "Error: Failed to allocate memory for dest->bytes in APInt_clone\n");
    exit(1);
  }

  // Copy the bytes from the source to the destination
  memcpy(dest->bytes, src->bytes, dest->size);

  return dest;
}


void APInt_lhs(APInt **apints, int dst, int src, uint64_t k) {
    // Convert APInt to uint64_t
    uint64_t val;
    memcpy(&val, apints[src]->bytes, sizeof(uint64_t));

    // Left shift the value by k bits
    val <<= k;

    // Copy the shifted value back into APInt array
    memcpy(apints[dst]->bytes, &val, sizeof(uint64_t));
}

void APInt_add(APInt **dst, APInt **op1, APInt **op2) {
  uint64_t val1 = apintToUint64(op1);
  uint64_t val2 = apintToUint64(op2);
  uint64_t result = val1 + val2;
  APInt *temp = newAPInt(result);
  *dst = temp;
}

void APInt_multiply_uint64(APInt **dst, APInt **src, uint64_t k) {
    uint64_t apint_value = apintToUint64(src);
    APInt *result_apint = newAPInt(apint_value * k);
    memcpy((*dst)->bytes, result_apint->bytes, (*dst)->size);
    APInt_destroy(result_apint);
}

void APInt_multiply(APInt **dest, APInt **op1, APInt **op2) {
    // Retrieve the two APInts to be multiplied

    // Convert the APInts to uint64_t values
    uint64_t val1 = apintToUint64(op1);
    uint64_t val2 = apintToUint64(op2);

    // Multiply the two uint64_t values
    uint64_t result = val1 * val2;

    // Create a new APInt from the result
    APInt *new_apint = newAPInt(result);

    // Allocate memory for the destination APInt object using malloc
    *dest = (APInt *)malloc(sizeof(APInt));

    // Copy the new APInt object to the destination APInt object
    memcpy(*dest, new_apint, sizeof(APInt));

    // Free the memory occupied by the new APInt
    APInt_destroy(new_apint);
}

int APInt_compare(APInt **op1, APInt **op2) {
    // If the sizes of the APInts are different, the larger size means the number is greater.
    if ((*op1)->size != (*op2)->size) {
        return ((*op1)->size > (*op2)->size) ? 1 : -1;
    }

    // Compare the bytes of the APInts from most significant to least significant.
    for (int i = (*op1)->size - 1; i >= 0; i--) {
        if ((*op1)->bytes[i] > (*op2)->bytes[i]) {
            return 1;
        } else if ((*op1)->bytes[i] < (*op2)->bytes[i]) {
            return -1;
        }
    }

    // The APInts are equal.
    return 0;
}

void APInt_power(APInt** dst, APInt** src, int k, int n) {
  int i, j;
  for (i = 0; i < n; i++) {
    uint64_t power = 1;
    uint64_t base = 0;
    for (j = (*src[i]).size - 1; j >= 0; j--) {
      base = base << 8 | (*src[i]).bytes[j];
    }
    for (j = 0; j < k; j++) {
      power *= base;
    }
    int p = 0;
    while (power > 0) {
      (*dst[i]).bytes[p++] = power & 0xFF;
      power >>= 8;
    }
    (*dst[i]).size = p;
  }
}

void APInt_print(APInt **a, FILE *file) {
  fprintf(file, "0x");

  // Find the most significant non-zero byte
  int k = (*a)->size - 1;
  while (k > 0 && (*a)->bytes[k] == 0) {
    k--;
  }

  // Count the total number of hex digits
  int totalDigits = k * 2 + 1;
  if (((*a)->bytes[k] >> 4) != 0) {
    totalDigits++;
  }

  // Add a leading zero if the total number of digits is odd
  if (totalDigits % 2 != 0) {
    fprintf(file, "0");
  }

  // Print each byte in hexadecimal format, with a leading 0 if necessary.
  for (int i = k; i >= 0; i--) {
    if (i == k && ((*a)->bytes[i] >> 4) == 0) {
      fprintf(file, "%x", (*a)->bytes[i]);
    } else {
      fprintf(file, "%02x", (*a)->bytes[i]);
    }
  }

  fprintf(file, "\n");
}

void APInt_destroy(APInt *apint) {
  if (apint != NULL) {
    free(apint->bytes);
    free(apint);
  }
}


