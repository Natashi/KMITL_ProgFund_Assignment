#define _CRT_SECURE_NO_WARNINGS     //Screw your safety nets

#include <iostream>

using namespace std;

int main() {
    char str[1024];

    printf("Input the string: ");
    scanf("%1023[^\n]", str);

    size_t len = 0;
    {
        char* pStr = &str[0];
        while (*pStr) {
            ++len;
            ++pStr;
        }
    }

    printf("The length of the string is %u characters.", len);

    return 0;
}