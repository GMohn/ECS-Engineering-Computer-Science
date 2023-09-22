#include "Reflector.h"
#include "common.h"
#include "stdlib.h"
#include "string.h"

char reflect(const char *reflector, char c) {
    if (c == ' ') {
        return ' '; // Return space character as is
    }
    int index = c - 'A';
    return reflector[index];
}

