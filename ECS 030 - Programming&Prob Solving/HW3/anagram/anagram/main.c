#include <stdio.h>
#include <string.h>
#include <ctype.h>
void anagram_check(char word_1[], char word_2[]);

int main()
{
    char user_char_1[21];
    char user_char_2[21];
    printf("Please enter the first word: ");
    scanf("%s", user_char_1);
    printf("Please enter the second word: ");
    scanf("%s", user_char_2);

    anagram_check(user_char_1, user_char_2);

return 0;
}
void anagram_check(char word_1[], char word_2[]){
    int i;
    int j;
    int c;
    int anagram = 0;
    char lower_word_1[21];
    char lower_word_2[21];

    strcpy(lower_word_1, word_1);
    strcpy(lower_word_2, word_2);
if(strlen(word_1)!=strlen(word_2))
{
    printf("%s is NOT an anagram of %s", word_1, word_2);
    return;
}


    for( i =0; word_1[i] != '\0'; ++i){
        lower_word_1[i] = tolower(lower_word_1[i]);
        }
    for( j = 0; word_2[j] != '\0'; ++j){
        lower_word_2[j] = tolower(lower_word_2[j]);
    }
    for( i = 0; i < strlen(lower_word_1); ++i)
    {
        for (j = 0; j < strlen(lower_word_2); ++j)
        {
            if(lower_word_1[i] == lower_word_2[j])
            {
                 ++anagram;
                 printf("%d anagram counter\n",anagram );

            }


        }
    }printf("%d str length",strlen(lower_word_1));
    if (anagram >= strlen(lower_word_1 )){
        printf("%s is an anagram of %s", word_1,word_2);
    }
    else{
         printf("%s is NOT an anagram of %s", word_1, word_2);
    }
return;


    }
