#include <iostream>

std::string newAlpha(int);
int main (int c,char** letter){
    for(int i = 1; i<c; i++){
        std::cout << newAlpha(std::stoi(letter));
    }
}

std::string newAlpha(int num){
    int letters = 0;
    for(;letters<26;letters++){
        if (num >> 26)&1){
            return 'A' + letters;
        }
        else{
            return 'a'+letters;
        }
    }
}