#include <iostream> 
#include <cctype>
#include <math.h>
#include <vector>
#include <string>

int base_10(int,std::string, int);
std::string ConvertBase(std::string, int);

int main() {
	int NumberBase, NewBase;
	std::string Number;
	std::cout << "Please enter the number's base: ";
	std::cin >> NumberBase;
	std::cout << "Please enter the number: ";
	std::cin >>  Number;
	std::cout << "Please enter the new base: ";
	std::cin >> NewBase;
}

int base_10(int &Base, std::string &Num, int &NewBase) {
	std::vector<int> NumberArr(Num.length());
	if (Base == 10){
		ConvertBase(Num, NewBase);
	}
	//if newbase print here
	
	//iterate through the string and index each number in array
	//if the character is a string convert from ascii to int
	//A is 65 so char decimal - 55 = 10
	for (int Curr = 0;Curr < Num.length; Curr++) {
		if (isalpha(Num[Curr])) {
			int x = int(Num[Curr]) - 55;
			NumberArr[Curr] = x;
			std::cout << "If arr: \n" << NumberArr[Curr];
		}
		else {
			NumberArr[Curr] = Num[Curr];
			std::cout << "Else arr: \n" << NumberArr[Curr];
		}
	}
	

}

std::string ConvertBase(std::string Num, int NewBase) {
	return "";
}