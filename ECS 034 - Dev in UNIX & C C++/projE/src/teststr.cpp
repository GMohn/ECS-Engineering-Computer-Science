#include "SafeString.h"
#include <gtest/gtest.h>
#include <cstring>
#include <cstdlib>
#include <map>
#include <string>
#include <fstream>
#include <vector>
#include <chrono>
#include <cstdio>

TEST(SafeString, AllocateTest){
    char *SafeString = SafeStringAllocate(32);

    EXPECT_TRUE(SafeStringIsValid(SafeString));
    EXPECT_EQ(SafeStringLength(SafeString),0);
    EXPECT_TRUE(SafeStringMaxLength(SafeString) <= 64);
    EXPECT_TRUE(SafeStringMaxLength(SafeString) >= 32);

    SafeStringDestroy(SafeString);
}

TEST(SafeString, CreateTest){
    char *SafeString = SafeStringFromCstr("foo");

    EXPECT_TRUE(SafeStringIsValid(SafeString));
    EXPECT_EQ(SafeStringLength(SafeString),3);
    EXPECT_EQ(strlen(SafeString),3);
    EXPECT_EQ(strcmp(SafeString,"foo"), 0);
    EXPECT_TRUE(SafeStringMaxLength(SafeString) <= 64);
    EXPECT_TRUE(SafeStringMaxLength(SafeString) >= 32);

    SafeStringDestroy(SafeString);
}

TEST(SafeString, CopyTest){
    char *SafeString = SafeStringAllocate(32);

    EXPECT_TRUE(SafeStringIsValid(SafeString));
    EXPECT_EQ(SafeStringCopy(SafeString,"foo"),SafeString);
    EXPECT_EQ(SafeStringLength(SafeString),3);
    EXPECT_EQ(strlen(SafeString),3);
    EXPECT_EQ(strcmp(SafeString,"foo"), 0);
    EXPECT_TRUE(SafeStringMaxLength(SafeString) <= 64);
    EXPECT_TRUE(SafeStringMaxLength(SafeString) >= 32);

    SafeStringDestroy(SafeString);
}

TEST(SafeString, ConcatenateTest){
    char *SafeString = SafeStringAllocate(32);

    EXPECT_TRUE(SafeStringIsValid(SafeString));
    EXPECT_EQ(SafeStringConcatenate(SafeString,"foo"),SafeString);
    EXPECT_EQ(SafeStringLength(SafeString),3);
    EXPECT_EQ(strlen(SafeString),3);
    EXPECT_EQ(strcmp(SafeString,"foo"), 0);
    EXPECT_EQ(SafeStringConcatenate(SafeString,"bar"),SafeString);
    EXPECT_EQ(SafeStringLength(SafeString),6);
    EXPECT_EQ(strlen(SafeString),6);
    EXPECT_EQ(strcmp(SafeString,"foobar"), 0);
    EXPECT_TRUE(SafeStringMaxLength(SafeString) <= 64);
    EXPECT_TRUE(SafeStringMaxLength(SafeString) >= 32);

    SafeStringDestroy(SafeString);
}

TEST(SafeString, ResizeTest){
    char *SafeString = SafeStringAllocate(32);
    char *OldSafeString = SafeString;
    size_t OldMaxLength = SafeStringMaxLength(SafeString);

    EXPECT_TRUE(SafeStringIsValid(SafeString));
    EXPECT_TRUE(SafeStringMaxLength(SafeString) <= 64);
    EXPECT_TRUE(SafeStringMaxLength(SafeString) >= 32);
    EXPECT_TRUE(SafeStringResize(&SafeString, OldMaxLength+1) > OldMaxLength);
    EXPECT_TRUE(SafeString != OldSafeString);

    SafeStringDestroy(SafeString);
}

TEST(SafeString, ErrorTest){
    char OldString[64] = "foo";
    char *SafeString = SafeStringAllocate(32);
    char Garbage1[64] = {0x0F,0x1E,0x2D,0x3C,0x4B,0x5A,0x69,0x78,
                        'A','D','G','J','z','y','x','w',
                        'M','P','S','V','v','u','t','s','\0'};
    char Garbage2[64];

    memset(Garbage1+24,0,sizeof(Garbage1) - 24);
    memset(Garbage2,0,sizeof(Garbage2));
    EXPECT_FALSE(SafeStringIsValid(OldString));
    EXPECT_TRUE(SafeStringIsValid(SafeString));
    EXPECT_FALSE(SafeStringIsValid(Garbage1+12));
    EXPECT_FALSE(SafeStringIsValid(Garbage1+16));
    EXPECT_FALSE(SafeStringIsValid(Garbage1+24));
    EXPECT_FALSE(SafeStringIsValid(Garbage2+12));
    EXPECT_FALSE(SafeStringIsValid(Garbage2+16));
    EXPECT_FALSE(SafeStringIsValid(Garbage2+24));
    EXPECT_EQ(SafeStringConcatenate(SafeString,OldString),SafeString);
    EXPECT_EQ(SafeStringLength(SafeString),3);
    EXPECT_EQ(strlen(OldString),3);
    EXPECT_EQ(strlen(SafeString),3);
    EXPECT_EQ(strcmp(OldString,"foo"), 0);
    EXPECT_EQ(strcmp(SafeString,"foo"), 0);
    EXPECT_EQ(SafeStringLength(OldString),0);
    EXPECT_EQ(SafeStringLength(SafeString),3);
    EXPECT_EQ(SafeStringMaxLength(OldString),0);
    EXPECT_TRUE(SafeStringMaxLength(SafeString) <= 64);
    EXPECT_TRUE(SafeStringMaxLength(SafeString) >= 32);
    EXPECT_EQ(SafeStringCopy(OldString,SafeString),(char *)NULL);
    EXPECT_EQ(SafeStringConcatenate(OldString,SafeString),(char *)NULL);

    SafeStringDestroy(SafeString);
}

TEST(SafeString, SpeedTest){
    auto STDStringStart = std::chrono::steady_clock::now();
    std::string STDString;
    for(int Index = 0; Index < 1000; Index++){
        for(char Ch = '0'; Ch < '~'; Ch++){
            STDString = STDString + Ch;
        }
    }
    auto STDStringDuration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now()-STDStringStart);
    
    auto SafeStringStart = std::chrono::steady_clock::now();
    char *SafeString = SafeStringFromCstr("");
    char Buffer[2];
    Buffer[1] = '\0';
    for(int Index = 0; Index < 1000; Index++){
        for(char Ch = '0'; Ch < '~'; Ch++){
            Buffer[0] = Ch;
            while(SafeStringConcatenate(SafeString,Buffer) == (char*)NULL){
                SafeStringResize(&SafeString, SafeStringMaxLength(SafeString) + 1);
            }
        }
    }
    auto SafeStringDuration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now()-SafeStringStart);
    EXPECT_EQ(strcmp(STDString.c_str(),SafeString), 0);
    EXPECT_TRUE(STDStringDuration.count() >=  SafeStringDuration.count());
    SafeStringDestroy(SafeString);
}
