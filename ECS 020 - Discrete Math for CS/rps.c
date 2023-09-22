#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

int main()
{
	int C=1; //loop control for game
	int R=1;
	int P=2;
	int S=3;
	int streak=0;
	int i;
	int Pscore=0;
	int Cscore=0;
	int choice;
	srand(time(NULL));
	for(i=0;i<100;i++){
	printf(" \n");
	}

	printf("Welcome to Rock, Paper Scissors\nRock=1 Paper=2 Scissors=3\n");
	while(C==1){
	for(i=0;i<5;i++){
	printf("Enter your choice:\n");
	scanf("%d",&choice);
		int computer=rand()%3+1; //creates random number for comp to use
		if (choice==1){
			if (computer==1){
				printf("Drawn\n");
			}
			if (computer==2){
				printf("Computer Wins.\nPaper Covers Rock\n");
				Cscore = Cscore + 1;
			}	
			if (computer==3){
				printf("You Win!\nRock Crushes Scissors!\n");
				Pscore = Pscore + 1;
			}
		}	
		 else if(choice==2){
			if(computer==2){
				printf("Draw.\n");
			}
			if (computer==3){
				printf("Computer Wins.\nScissors Cuts Paper\n");
				Cscore = Cscore + 1;
			}			
			if (computer==1){
				printf("You Win!\nPaper Covers Rock\n");
				Pscore = Pscore + 1;
			}
		}
		else if(choice==3){
			if(computer==3){
				printf("Draw\n");
			}			
			if(computer==2){
				printf("You Win!\nScissors Cuts Paper\n");
				Pscore = Pscore + 1;
			}
			if(computer==1){
				printf("Computer wins.\nRock Crushes Scissors\n");
				Cscore = Cscore + 1;
			}
		}
	else{
		printf("Incorrect input type please try again.\n");
		i = i - 1;
	}
		}
		if(Cscore > Pscore ){
			printf(" \n");
			printf("Computer wins %d to %d\n",Cscore,Pscore);
		
		}
		else if(Cscore < Pscore ){
			printf(" \n");			
			printf("Player wins %d to %d\n",Cscore,Pscore);
		}
		else if(Cscore == Pscore ){
			printf(" \n");			
			printf("No winner its a draw!\n");
		}

	printf("Would you like to rerun the program?\nPress 1 to continue, press anything else to exit:\n");
	scanf("%d",&C);
	Pscore = 0;
	Cscore = 0;
	}
	return(0);
}