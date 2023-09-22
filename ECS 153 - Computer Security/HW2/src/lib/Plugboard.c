#include "Plugboard.h"
#include "common.h"
struct Plugboard {
    char swaps[26];
};

Plugboard *new_Plugboard(size_t num_pairs, const char *pairs) {
    Plugboard *plugboard = (Plugboard *)malloc(sizeof(Plugboard));
    if (plugboard == NULL) {
        return NULL; // Memory allocation failed, return NULL
    }

    // Initialize the plugboard swaps
    for (int i = 0; i < 26; ++i) {
        plugboard->swaps[i] = 'A' + i;
    }

    // Configure the plugboard swaps based on the pairs
    if (num_pairs > 0 && pairs != NULL) {
        for (size_t i = 0; i < num_pairs; ++i) {
            char first = pairs[i * 2];
            char second = pairs[i * 2 + 1];

            if (first < 'A' || first > 'Z' || second < 'A' || second > 'Z') {
                free(plugboard);
                return NULL; // Invalid configuration, return NULL
            }

            plugboard->swaps[first - 'A'] = second;
            plugboard->swaps[second - 'A'] = first;
        }
    }

    return plugboard;
}

char swap_Plugboard(Plugboard *plugboard, char letter) {
    if (letter < 'A' || letter > 'Z' ) {
        return letter; // Not a valid letter, no swap
    }

    return plugboard->swaps[letter - 'A'];
}

void free_Plugboard(Plugboard *plugboard) {
    free(plugboard);
}