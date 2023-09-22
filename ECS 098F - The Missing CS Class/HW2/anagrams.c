/*
 * Program to determine if two words are anagrams of eachother.
 * The words must contain only alphanumeric characters.
 */
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

bool AreAnagrams(char* word1, char* word2) {
    word2 = strdup(word2);
    while(strlen(word1) != 0) {
        char* c = index(word2, *word1);
        if(c == NULL) {
            return false;
        } else {
            *c = '-';
        }
        word1++;
    }
    return true;
}

int main(int argc, char** argv) {
    if(argc != 3) {
        printf("Usage: %s <word> <word>\n", argv[0]);
        return 1;
    }

    bool are_anagrams = AreAnagrams(argv[1], argv[2]);
    printf("%s and %s are %sanagrams of each other.\n", argv[1], argv[2], are_anagrams ? "" : "not ");

    if(are_anagrams) {
        return 0;
    } else {
        return 1;
    }
}