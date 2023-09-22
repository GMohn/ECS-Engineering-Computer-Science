#include "Rotor.h"
#include "common.h"

char swap_rotor(const char *rotor, char letter, bool reverse, size_t initial_setting) {
    size_t index = letter - 'A';
    if (index < 26) {
        if (!reverse) {
            // Get the mapped index without considering the initial setting
            size_t mapped_index = (index + initial_setting) % 26;
            // Apply the initial setting shift to the mapped index
            index = (mapped_index - initial_setting + 26) % 26;
            return rotor[index];
        } else {
            // Find the index of the letter in the shifted rotor mapping
            for (size_t i = 0; i < 26; i++) {
                if (rotor[i] == letter) {
                    // Apply the initial setting shift to get the corresponding index in the original mapping
                    index = (i + 26 - initial_setting) % 26;
                    return 'A' + index;
                }
            }
        }
    }
    return letter; // If no mapping found, return the original letter
}


