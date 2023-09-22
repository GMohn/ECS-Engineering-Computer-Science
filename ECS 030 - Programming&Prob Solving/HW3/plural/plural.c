//this program changes the user inputted noun to a plural version.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//declare plural function
void plural (char noun[]);

int main(){
//declare user inputted noun
	char user_noun[15];
	char* plural_form = NULL;
//prompt user
	printf("Please enter a word: ");
	scanf("%s", user_noun);
//call plural function
	plural_form = (char*)malloc(strlen(user_noun) * sizeof(plural_form));
	strcpy(plural_form, user_noun);

	plural(plural_form);
	printf("The plural from of %s is %s.", user_noun, plural_form);

return 0;
}
// func plural consists of if else statements to change the user inputted noun to plural
void plural (char noun[]){
//declare and get the length of the word
	int length;
	length = strlen(noun);
// condition to add es
	if (noun[length - 1] == 's' || (noun[length - 2] == 'c' && noun[length - 1] == 'h') || (noun[length - 2] == 's' && noun[length - 1] == 'h') || noun[length - 1] == 'z' || noun[length - 1] == 'x'){
		strcat(noun, "es");
}
//condition if consonant and y reassign last character to ies then add additional elements
	else if ((noun[length - 1] == 'y') && ((noun[length - 2] != 'a') && (noun[length - 2] != 'e') && (noun[length - 2] != 'i') && (noun[length - 2] != 'o') && (noun[length - 2] != 'u'))){
		noun[length - 1] = 'i';
		noun[length] = 'e';
		noun[length + 1] = 's';
		noun[length + 2] = '\0';
}
//condition for ending in f or fe
	else if ((noun[length - 1] == 'f') || (noun[length - 1] == 'e' && noun[length - 2] == 'f')){
//nested if statement to re-align characters of the string
		if (noun[length - 1] == 'e' && noun[length - 2] == 'f'){
			noun[length - 2] = 'v';
			noun[length-1] = 'e';
			noun[length] = 's';
			noun[length + 1] = '\0';
}
		else{
			noun[length - 1] = 'v';
			noun[length] = 'e';
			noun[length + 1] = 's';
			noun[length + 2] = '\0';
			}
}

	else{
		strcat(noun,"s");
}

}

