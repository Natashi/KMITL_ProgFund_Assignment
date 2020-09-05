#define _CRT_SECURE_NO_WARNINGS     //Screw your safety nets

#include <iostream>

using namespace std;

int main() {
    double n, d;

    printf("I'll divide your numbers, I guess.\n");
    printf("Input two numbers: ");
    if (scanf("%lf %lf", &n, &d)) {
        printf("The quotient is: %.7f", n / d);
    }
    else
        printf("One of them's not a number.");

    return 0;
}