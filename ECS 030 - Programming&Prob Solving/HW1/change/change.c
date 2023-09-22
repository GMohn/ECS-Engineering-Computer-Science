//calculate change from withdrawl amount
#include <stdio.h>
int main(void) {
	int totalChange = 0;	
	int hundredChange = 0; //setting all change variables
	int fiftyChange = 0;
	int twentyChange = 0;
	int tenChange = 0;	
	int fiveChange = 0;
	int oneChange = 0;
	
	printf("Please enter the amount of money you wish to withdraw: "); 
	scanf("%d", &totalChange); //prompt user for withdrawl amount	
	
	hundredChange = totalChange / 100; //round down to 100s
	printf("You received %d hundred(s)\n", hundredChange);
	
	fiftyChange = (totalChange % 100) / 50; //compute change
	printf("You received %d fifty(s)\n", fiftyChange);
	
	twentyChange = ((totalChange % 100) % 50) / 20; //uses remainder to distribute into further bills
	printf("You received %d twenty(s)\n", twentyChange);
	
	tenChange = (((totalChange % 100) % 50 ) % 20) / 10;
	printf("You received %d ten(s)\n", tenChange);
	
	fiveChange = ((((totalChange % 100) % 50 ) % 20) % 10) / 5;
	printf("You received %d five(s)\n", fiveChange);
	
	oneChange = (((((totalChange % 100) % 50 ) % 20) % 10) % 5) / 1;
	printf("You received %d one(s)\n", oneChange);

return 0;
}
