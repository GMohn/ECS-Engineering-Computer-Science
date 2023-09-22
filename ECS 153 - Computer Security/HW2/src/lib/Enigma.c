#include "Enigma.h"
#include "EnigmaImpl.h"
#include "Plugboard.h"
#include "Reflector.h"
#include "Rotor.h"
#include <stdbool.h>

Enigma *new_Enigma(size_t num_rotors, const char **rotors, size_t *rings,
                   size_t *inits, const char *reflector, size_t num_pairs,
                   const char *pairs) {
    // Check for valid configuration parameters
    if (strlen(reflector) != 26) {
        return NULL; // Invalid configuration, return NULL
    }

    Enigma *enigma = (Enigma *)malloc(sizeof(Enigma));

    // Initialize enigma with the provided configuration
    if (enigma == NULL) {
        return NULL; // Memory allocation failed, return NULL
    }

    // Allocate memory for rings and inits arrays in enigma
    enigma->rings = (size_t *)malloc(num_rotors * sizeof(size_t));
    enigma->inits = (size_t *)malloc(num_rotors * sizeof(size_t));

    // Copy values from the original rings and inits arrays
    memcpy(enigma->rings, rings, num_rotors * sizeof(size_t));
    memcpy(enigma->inits, inits, num_rotors * sizeof(size_t));



        // Allocate memory for the array of rotor pointers
    const char** allocated_rotors = (const char**)malloc(num_rotors * sizeof(const char*));

    // Allocate memory for each individual rotor string and copy the strings
    for (size_t i = 0; i < num_rotors; ++i) {
        const char* rotor = rotors[i];
        size_t rotor_length = strlen(rotor) + 1; // Include space for the null terminator
        char* allocated_rotor = (char*)malloc(rotor_length * sizeof(char));
        strncpy(allocated_rotor, rotor, rotor_length);
        allocated_rotors[i] = allocated_rotor;
    }
    // Assign the allocated rotor pointers to the Enigma machine
    enigma->rotors = allocated_rotors;

    // Initialize the Enigma fields with the provided configuration

    enigma->num_rotors = num_rotors;
    enigma->reflector = reflector;
    enigma->num_pairs = num_pairs;
    enigma->pairs = pairs;

    // Initialize the plugboard
        // Configure the plugboard to map each character to itself
    enigma->plugboard = new_Plugboard(num_pairs, pairs);

    if (enigma->plugboard == NULL) {
        free(enigma->rings);
        free(enigma->inits);
        free(enigma);
        return NULL; // Plugboard initialization failed, return NULL
    }

    // Additional initialization code can be added here as needed

    return enigma;
}


char *encrypt_Enigma(Enigma *self, char *dst, const char *src) {
    size_t src_len = strlen(src);

    for (size_t i = 0; i < src_len; ++i) {
        char letter = src[i];
        // Pass the letter through the plugboard
        char encrypted_letter = swap_Plugboard(self->plugboard, letter);

        // Apply the initial setting shift
        for (size_t j = 0; j < self->num_rotors; ++j) {
            encrypted_letter = swap_rotor(self->rotors[j], encrypted_letter, false, self->inits[j]);
        }

        // Pass the letter through the reflector
        encrypted_letter = reflect(self->reflector, encrypted_letter);

        // Pass the letter through the rotors in reverse order
        for (size_t j = self->num_rotors; j > 0; --j) {
            encrypted_letter = swap_rotor(self->rotors[j - 1], encrypted_letter, true, self->inits[j - 1]);
        }

        // Pass the letter through the plugboard (second time)
        encrypted_letter = swap_Plugboard(self->plugboard, encrypted_letter);

        // Store the encrypted letter in the destination buffer
        dst[i] = encrypted_letter;
    }

    dst[src_len] = '\0';

    return dst;
}


void reset_rotor_Enigma(Enigma *self, size_t *new_setting) {
    // Reset the rotor settings to the new configuration
    for (size_t i = 0; i < self->num_rotors; ++i) {
        self->inits[i] = new_setting[i];
    }
}

void free_Enigma(Enigma *self) {
    // Additional deallocation for other components of the Enigma machine
        // Deallocate memory for the plugboard
    free_Plugboard(self->plugboard);
        // Deallocate memory for the rotors
    free(self->rings);
    free(self->inits);

    // Deallocate memory for the Enigma object itself
    free(self);
}

void get_setting_Enigma(Enigma *self, char *ret) {
    // Get the current rotor settings of the Enigma machine
    // Store the settings in the 'ret' buffer
    for (size_t i = 0; i < self->num_rotors; ++i) {
        size_t num = self->inits[i];
        ret[i] = 'A'+ num ;
    }
}

void tick_Enigma(Enigma *self) {
    // Perform a single tick on the Enigma machine
    size_t num_rotors = self->num_rotors;

    // Notches loop
    char rot_edges[num_rotors][26];
    for (size_t i = 0; i < num_rotors; ++i) {
        //DEBUGF("seg message: %d\n", i );
        const char* comma = strchr(self->rotors[i], ',');

        if (comma != NULL) {

            const char* substring = comma + 1;
            //DEBUGF("Debug message: %s\n", substring);
            strncpy(rot_edges[i], substring, sizeof(rot_edges[i]) - 1);

            rot_edges[i][sizeof(rot_edges[i]) - 1] = '\0'; // Null-terminate the string
        }
    }
    bool rot = false;
    for (size_t i = 0; i < num_rotors; ++i) {
        //DEBUGF("i: %d\n",i);
        for (size_t j = 0; j < strlen(rot_edges[i]); ++j) {
            if (self->inits[i] == (size_t)(rot_edges[i][j] - 'A')) {
                //DEBUGF("rot edges message: %s\n","ding");
                rot = true;
                break;
            }
        }
        if(rot){
            if (self->inits[i] == 25) {
                self->inits[i] = 0;
            }
            else {
                ++self->inits[i];
            }
           rot = false;

        }else{
            if (self->inits[i] == 25) {
                self->inits[i] = 0;
            }
            else {
                ++self->inits[i];
            }
            
            break;
        }
    }
    

}


void tick_n_Enigma(Enigma *self, size_t n) {
    // Perform n ticks on the Enigma machine
    for (size_t i = 0; i < n; ++i) {
        tick_Enigma(self);
    }
}