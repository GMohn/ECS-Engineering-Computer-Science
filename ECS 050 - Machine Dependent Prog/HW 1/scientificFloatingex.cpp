#include <iostream>
#include <string>

using namespace std;

bool checkIfZero(float fNumber);
void printSign(unsigned int sign);

/*************************
* check if number is 0
***************************/
bool checkIfZero(float fNumber)
{
    if(fNumber == 0)
    {
        cout << "0E0" << endl;
        return true;
    }
    return false;
}


/*************************
* print Sign
***************************/
void printSign(unsigned int sign)
{
    if (sign != 1)
    {
        sign = sign + 1;
        cout << sign << ".";
    }
    else
    {
        cout << "-" << sign << ".";
    }
}

/*************************
* Main Method
***************************/

int main()
{
    // Variable declarations.
    float floatNumber;
    //Mantissa 23 bits
    unsigned int mantis[23];
    unsigned int exponent;
    unsigned int sign;
    unsigned int fInteger;

    //Prompt the user to enter
    cout << "Please enter a float: ";
    cin >> floatNumber;

    //Check if number is zero
    if(checkIfZero(floatNumber))
    {
        return 0;
    }

    fInteger = *((unsigned int *)&floatNumber);
    //Right shift
    sign = fInteger >> 31;
    exponent = fInteger & 0x7f800000;
    exponent >>= 23;

    for (int i = 22; i >= 0; i--)
        mantis[(22 - i)] = ((fInteger >> i)&1);

    for (int i = 0; i <= 22; i++)
    {
        if (mantis[i] == 0)
        {
            int count = 0;
            for (int j = i; j <= 22; j++)
                if ( mantis[j] == 1)
                    count++;
            if (count == 0)
                mantis[i] = 2;
        }
    }

    if (exponent != 0)
        exponent = exponent - 127;

    // Program Output
    printSign(sign);
    for (int i = 0; i <= 22; i++)
    {
        if (mantis[i] == 0 || mantis[i] == 1)
        {
            cout << mantis[i];
        }
    }
    cout << "E" << exponent << endl;
    return 0;
}