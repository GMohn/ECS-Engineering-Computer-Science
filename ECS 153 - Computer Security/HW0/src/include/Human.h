#ifndef HUMAN_H
#define HUMAN_H

#include "GenericTraits.h"
#include <stdint.h>
#include <stdlib.h>

#define MAX_LEN 256
/// Human only have a name.
typedef struct Human
{
  GenericTraits *impl;
  char name[MAX_LEN];
} Human;

void *new_Human(char *);
void dump_Human(void *self, FILE *fp);
int cmp_Human(void *self, void *other);
void drop_Human(void *self);

void __attribute__((constructor)) register_Human();

#endif