#ifndef PLUGBOARD_H
#define PLUGBOARD_H

#include "common.h"
#include <stdlib.h>
#include <string.h>

typedef struct Plugboard Plugboard;

Plugboard *new_Plugboard(size_t num_pairs, const char *pairs);
char swap_Plugboard(Plugboard *plugboard, char letter);
void free_Plugboard(Plugboard *plugboard);

#endif