#define _CRT_SECURE_NO_WARNINGS     //Screw your safety nets

#include <iostream>

using namespace std;

int main() {
    int n;

    printf("I'll multiply your number by 10, I guess.\n");
    printf("Input number: ");
    if (scanf("%511d", &n)) {
        printf("Your new number is: %d", n * 10);
    }
    else
        printf("That's not a number.");

    return 0;
}