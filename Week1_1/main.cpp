#define _CRT_SECURE_NO_WARNINGS     //Screw your safety nets

#include <iostream>

using namespace std;

int main() {
    char name[512];

    scanf("%511[^\n]", name);
    printf("Hello, %s.\nYou might be wondering why this program is so simple. "
        "I have no bloody idea.", name);

    return 0;
}