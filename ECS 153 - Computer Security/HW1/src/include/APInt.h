#ifndef APINT_H
#define APINT_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Struct definition for APInt
typedef struct {
  int size;
  uint8_t *bytes;
} APInt;

/* Constructive methods */
APInt *newAPInt(uint64_t val);
  // Clone an APInt
APInt *APInt_clone(APInt *a);

/*Common operations*/
uint64_t APInt_get_uint64(const APInt *apint);
  // Left shift of an APInt
void APInt_lhs(APInt **apints, int dst, int src, uint64_t k);
  // add between two APInt
void APInt_add(APInt **dst, APInt **op1, APInt **op2);
  // Mult APInt with APInt
void APInt_multiply(APInt **dst ,APInt **op1, APInt **op2);
  // Mult APInt with uint64_t
void APInt_multiply_uint64(APInt **dst, APInt **src, uint64_t k);
  // Power
void APInt_power(APInt** dst, APInt** src, int k, int n);
  // Comparison
int APInt_compare(APInt **op1, APInt **op2);


// Destructor
void APInt_destroy(APInt *a);

// Printing method
void APInt_print(APInt **a, FILE *file);




#endif