#ifndef ROTOR_H
#define ROTOR_H

#include "common.h"
#include <stdbool.h>
#include <string.h>

// Swap the rotor mappings for encryption or decryption
char swap_rotor(const char *rotor, char letter, bool reverse, size_t initial_setting);





#endif