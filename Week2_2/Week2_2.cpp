#define _CRT_SECURE_NO_WARNINGS     //Screw your safety nets

#include <iostream>

using namespace std;

int main() {
    char str[512];

    size_t countVowel = 0;
    size_t countConsonant = 0;
    size_t countNumeric = 0;

    printf("Input the string: ");
    if (scanf("%511[^\n]", str)) {
        char* pStr = &str[0];
        while (*pStr) {
            char ch = *pStr;
            if (ch >= '0' && ch <= '9')
                ++countNumeric;
            else {
                if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) {
                    if (ch > 'Z') ch -= 'a' - 'A';
                    if (ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U')
                        ++countVowel;
                    else
                        ++countConsonant;
                }
            }
            ++pStr;
        }
    }

    printf("Result: %u vowels, %u consonants, %u numbers", 
        countVowel, countConsonant, countNumeric);

    return 0;
}