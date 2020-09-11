#define _CRT_SECURE_NO_WARNINGS     //Screw your safety nets

#include <iostream>

using namespace std;

int main() {
    long long n;

    printf("Input a number: ");
    if (scanf("%lld", &n)) {
        printf("%lld ", n);
        if (n < 0)
            puts("is negative.");
        else if (n > 0)
            puts("is positive.");
        else
            puts("is zero.");
    }
    else {
        printf("That's not a number.");
    }

    return 0;
}