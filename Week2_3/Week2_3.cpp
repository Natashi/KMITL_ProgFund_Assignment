#define _CRT_SECURE_NO_WARNINGS     //Screw your safety nets

#include <iostream>

using namespace std;

int main() {
    int num;

    printf("Input number: ");
    if (scanf("%511d", &num)) {
        printf("%d is ", num);
        if (num > 0)
            printf("positive.");
        else if (num < 0)
            printf("negative.");
        else
            printf("zero.");
    }
    else
        printf("Not a number.");

    return 0;
}