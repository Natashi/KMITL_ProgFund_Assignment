#define _CRT_SECURE_NO_WARNINGS     //Screw your safety nets

#include <iostream>

using namespace std;

int main() {
    double l, r;

    printf("I'll add your numbers, I guess.\n");
    printf("Input two numbers: ");
    if (scanf("%lf %lf", &l, &r)) {
        printf("The sum is: %.5f", l + r);
    }
    else
        printf("One of them's not a number.");

    return 0;
}