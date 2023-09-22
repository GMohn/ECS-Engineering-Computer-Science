
#include "Human.h"
#include "GenericTraits.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

void *new_Human(char *name) {
  // Find the first space or newline character
  char *end = strchr(name, ' ');
  if (end == NULL)
    end = strchr(name, '\n');

  // Calculate the length of the name
  size_t len = (end != NULL) ? (size_t)(end - name) : strlen(name);

  // Truncate the name if it's too long
  if (len >= MAX_LEN)
    len = MAX_LEN - 1;

  // Allocate memory for the Human object
  Human *human = malloc(sizeof(Human));

  // Set the GenericTraits implementation
  human->impl = malloc(sizeof(GenericTraits));
  human->impl->new = new_Human;
  human->impl->dump = dump_Human;
  human->impl->cmp = cmp_Human;
  human->impl->drop = drop_Human;

  // Copy the name into the Human object
  strncpy(human->name, name, len);
  human->name[len] = '\0';

  return human;
}

void dump_Human(void *self, FILE *fp) {
  Human *human = (Human *)self;
  fprintf(fp, "%s\n", human->name);
}

int cmp_Human(void *self, void *other) {
  Human *human1 = (Human *)self;
  Human *human2 = (Human *)other;
  int result = strcmp(human1->name, human2->name);

  //printf("Comparison: %s - %s = %d\n", human1->name, human2->name, result);

  return result;
}

void drop_Human(void *self) {
  Human *human = (Human *)self;
  free(human->impl);
  free(human);
}

void __attribute__((constructor)) register_Human() {
  // Register Human implementation with the system
  add_ctor_dtor("Human", new_Human, drop_Human);
}