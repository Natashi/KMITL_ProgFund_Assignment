#define _CRT_SECURE_NO_WARNINGS     //Screw your safety nets

#include <iostream>

using namespace std;

bool _isdigit(char x) {
    return x >= '0' && x <= '9';
}
bool _isalpha(char x) {
    return (x >= 'A' && x <= 'Z') || (x >= 'a' && x <= 'z');
}
char _toupper_(char x) {
    if (!_isalpha(x)) return x;
    return x > 'Z' ? (x - ('a' - 'A')) : x;
}
char _isvowel(char x) {
    x = _toupper_(x);
    return x == 'A' || x == 'E' || x == 'I' || x == 'O' || x == 'U';
}

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
            if (_isdigit(ch))
                ++countNumeric;
            else {
                if (_isalpha(ch)) {
                    if (_isvowel(ch))
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