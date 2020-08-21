#define _CRT_SECURE_NO_WARNINGS     //Screw your safety nets

#include <iostream>

using namespace std;

void ReverseBytes(char* sPtr, char* ePtr) {
    while (sPtr < ePtr) {
        char tmp = *ePtr;
        *ePtr = *sPtr;
        *sPtr = tmp;

        ++sPtr;
        --ePtr;
    }
}

int main() {
    char str[512];

    printf("Input string: ");
    if (scanf("%511[^\n]", str)) {
        char* sPtr = &str[0];
        char* ePtr = sPtr;
        while (*ePtr) ++ePtr;

        --ePtr;
        ReverseBytes(sPtr, ePtr);

        printf("The reversed string is: %s", str);
    }

    return 0;
}