#include "StringUtils.h" 	  			 	 
#include <algorithm> 
#include <cctype>
#include <cstdio>
#include<iostream>

namespace StringUtils{
    
std::string Slice(const std::string &str, ssize_t start, ssize_t end){
    // Your code goes here
    std::string TempStr = str; //store string  
    if (start == end){ //if start of slice is the end of slice then return an empty string
        return "";
    }
    if (start < 0){
        start += str.length(); 
    }
    if (end <= 0 ){
        end += str.length(); 
    }
    ssize_t SliceLength = end - start; //measure length of slice
    if (SliceLength < 1){ //if Slice is less than 1 then return empty string
        return "";
    }  
    return TempStr.substr(start,SliceLength); //https://stackoverflow.com/questions/27992264/c-equivalent-of-python-string-slice

}

std::string Capitalize(const std::string &str){
    // Your code goes here
    std::string TempStr, Lowercase;
    for (char ch : str){  //https://stackoverflow.com/questions/9438209/for-every-character-in-string
        TempStr += tolower(ch); //make all characters lowercase
    }
    TempStr[0] = toupper(TempStr[0]); //first character capitalized
    return TempStr;
}

std::string Title(const std::string &str){
    // Your code goes here
    std::string TempStr, LowerString;
    bool isFirst = true;
    char isPrev;
    //thispointer.com/convert-first-letter-of-each-word-of-a-string-to-upper-case-in-c/
    for (char ch : str){
        LowerString += tolower(ch); //create two temp strings, one to change and store. make all characters lower case
    }

    for (char ch: LowerString){ // for lower string check if its a letter
        if (isFirst){
            isFirst = false;
            isPrev = ch;
            TempStr += toupper(ch);
            continue;
        }
        if (!isalpha(isPrev) || ispunct(isPrev) || isPrev == ' '){
            isPrev = ch;
            TempStr += toupper(ch); //when letter not found, capitalize
            continue;
        }

        TempStr += ch;
        isPrev = ch;

    } 
      return TempStr;
}

std::string LStrip(const std::string &str){
    // Your code goes here
    std::string TempStr;
    bool Stripped = true;
    for (char ch : str){
        if (isblank(ch) && Stripped){
        std::cout << "String is  if blank:" << TempStr << std::endl;    
            continue;
        }
        else{ //build the string from the else statement
            Stripped = false;
            TempStr +=ch;
            std::cout << "String is else:" << TempStr << std::endl;
        }
    }
    std::cout << "String is :" << TempStr << std::endl; 
    return TempStr;
}

std::string RStrip(const std::string &str){
    // Your code goes here
    std::string TempStr = str; //copy string temporarily
    int length = str.length() - 1;
    for (int count = length; count >= 0 ; count--){
        if(isblank(TempStr[count]) || TempStr[count] == '\n'){
            TempStr.erase(count,1);
        }
        else{
            break;
        }
    }
        return TempStr;
}

std::string Strip(const std::string &str){
    // Your code goes here
    std::string TempStr;
    TempStr = LStrip(str);
    TempStr = RStrip(TempStr);
    return TempStr;
}

std::string Center(const std::string &str, int width, char fill){ 
    // Your code goes here
    std::string TempStr = Strip(str);
    int LengthStr = TempStr.length() + 1;
    if ((width - TempStr.length()) % 2){
        TempStr += fill;
    }
    for (int count = LengthStr; count < width; count +=2){
        TempStr += fill;
        TempStr = fill + TempStr;
    }
    std::cout << "Center String is :" << TempStr << std::endl; 

    return TempStr;
}

std::string LJust(const std::string &str, int width, char fill){ //stackoverflow.com/questions/17512825/align-text-to-center-in-string-c
    // Your code goes here
    std::string TempStr = Strip(str);
    int LengthStr = TempStr.length();
    for (int count = LengthStr; count < width; count++){
        TempStr += fill;
    }
    return TempStr;
}

std::string RJust(const std::string &str, int width, char fill){
    // Your code goes here
    std::string TempStr = Strip(str);
    int LengthStr = TempStr.length();
    for (int count = LengthStr; count < width; count++){
        TempStr = fill + TempStr;
    }
    return TempStr;
}

std::string Replace(const std::string &str, const std::string &old, const std::string &rep){
    // Your code goes here
    std::string TempStr = str;
    size_t replace = str.find(old);
    while (replace != std::string::npos){
        TempStr.replace(replace, old.length(), rep);
        replace = TempStr.find(old);
    }
    return TempStr;
}

std::vector< std::string > Split(const std::string &str, const std::string &splt){
    // Your code goes here
    std::vector<std::string> StringVec;
    std::string TempStr = str;
    if (splt.empty()){
        TempStr = StringUtils::Replace(TempStr, "\n", " ");
        TempStr = StringUtils::Replace(TempStr, "\t", " ");
        TempStr = StringUtils::Replace(TempStr, "\r", " ");
        TempStr = StringUtils::Replace(TempStr, "\b", " ");
        int count = 0;
        for (char &ch: TempStr){
            if (ch == ' ' && *(&ch + 1) == ' '){
                int LengthStr = 1;
                while (*(&ch + LengthStr) == ' '){
                    LengthStr++;
                }
                TempStr.erase(count, LengthStr - 1);
            }
            count++;
        }
        return StringUtils::Split(TempStr, " ");
    }
    else{
        size_t div = str.find(splt), div2;
        StringVec.push_back(Slice(TempStr, 0 , div));
        while(true){
            TempStr = &TempStr[div + 1];
            div2 = TempStr.find(splt);
            if (div2 != std::string::npos){
                StringVec.push_back(Slice(TempStr, 0 , div2));
                div = div2;
            }
            else{
                StringVec.push_back(TempStr);
                break;
            }
        }
        return StringVec;
    }

    }

std::string Join(const std::string &str, const std::vector< std::string > &vect){
    // Your code goes here
    std::string TempStr;
    size_t count = 0;
    for (auto cont : vect){
        count++;
        if(count >= vect.size())
            TempStr += cont;
        else
            TempStr += cont + str;
    }
    return TempStr;
}

std::string ExpandTabs(const std::string &str, int tabsize){
    // Your code goes here
    std::vector<std::string> Expanded = StringUtils::Split(str, "\t");
    size_t count = 0;
    for (auto &comp : Expanded){
        count++;
        if (count == Expanded.size()){
            break;
        }
        if (int(comp.length()) >= tabsize){
            comp = StringUtils::LJust(comp, tabsize * 2);
        }
        else
            comp = StringUtils::LJust(comp, tabsize);
    }

    return StringUtils::Join("", Expanded);
}

int EditDistance(const std::string &left, const std::string &right, bool ignorecase){
    // Your code goes here
    return 0;
}

}
