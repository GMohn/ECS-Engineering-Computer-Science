#include <iostream> 
#include <cctype>
#include <math.h>
#include <vector>
#include <string>

int Base10(int,std::string, int);
std::string ConvertBase(int, int);

int main() {
	int NumberBase, NewBase;
	std::string Number;
	std::cout << "Please enter the number's base: ";
	std::cin >> NumberBase;
	std::cout << "Please enter the number: ";
	std::cin >>  Number;
	std::cout << "Please enter the new base: ";
	std::cin >> NewBase;
	Base10(NumberBase, Number, NewBase);
}

int Base10(int Base, std::string Num, int NewBase) {
	std::vector<int> NumberArr(Num.length());
	int NumberLen = Num.length();
	
	if (Base == 10) {
		std::cout << Num << " base " << Base << " is " << ConvertBase(std::stoi(Num), NewBase) << " base " << NewBase << std::endl;
		return 0;
	}

	//iterate through the string and index each number in array
	//if the character is a string convert from ascii to int
	//A is 65 so char decimal - 55 = 10
	for (int Curr = 0;Curr < NumberLen; Curr++) {
		if (isalpha(Num[Curr])) {
			int x = int(Num[Curr]) - 55;
			NumberArr[Curr] = x;
			//std::cout << "\nIf arr: " << NumberArr[Curr];
		}
		else {
			NumberArr[Curr] = Num[Curr]-48;
			//std::cout << "\nElse arr: " << NumberArr[Curr]<<std::endl;
		}
	}
	

	int i = 0;
	int BaseTenSum = 0;
	//std::cout << "Number Len: " << NumberLen << std::endl;
	for (;NumberLen > 0; NumberLen--) {
		//std::cout << "pow = " << pow(Base, NumberLen-1) << std::endl;
		BaseTenSum += (pow(Base, NumberLen-1) * NumberArr[i]);
		i++;
		//std::cout << "BaseTen: " << BaseTenSum << std::endl;
	}
	if (NewBase == 10) {
		std::cout << Num << " base " << Base << " is " << BaseTenSum << " base " << NewBase << std::endl;
		return 0;
	}
	else {
		std::cout << Num << " base " << Base << " is " << ConvertBase(BaseTenSum, NewBase) << " base " << NewBase << std::endl;
		return 0;
	}
	return 0;
}


std::string ConvertBase(int n, int NewBase) {
	int Remainder = 0, Quotient = n;
	std::string c = "";
	std::string Result = "", ReverseResult = "";
	while (Quotient != 0) {
		Remainder = Quotient % NewBase;
		if (Remainder > 9) {
			c = (Remainder + 55);
		}
		else {
			c = (Remainder + '0');
		}

		Result.append(c);
		Quotient = Quotient / NewBase;
	}
	for (int i = Result.size() - 1; i >= 0; i--) {
		ReverseResult = ReverseResult.append(1, Result[i]);
	};
	return ReverseResult;
}