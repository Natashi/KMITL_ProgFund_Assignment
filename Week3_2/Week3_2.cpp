#define _CRT_SECURE_NO_WARNINGS     //Screw your safety nets

#include <iostream>

using namespace std;

double _invsqroot(double x) {
    uint64_t _as_ui64 = *(uint64_t*)&x;
    double x2 = x * 0.5;
    double res = x;
    _as_ui64 = 0x5fe6eb50c7b537a9 - (_as_ui64 >> 1);   //Welcome to the gates of hell
    res = *(double*)&_as_ui64;
    res = res * (1.5 - (x2 * res * res));
    return res;
}

int main() {
    double n;

    printf("I heard you liked square roots, so I'll compute square roots for you in the most obnoxious way possible.\n");
    printf("Input number: ");
    if (scanf("%lf", &n)) {
        if (n >= 0) {
            double sqr = 1.0 / _invsqroot(n);
            printf("The approximate square root is: %.3f", sqr);
        }
        else
            printf("Input must not be negative.");
    }
    else
        printf("That's not a number.");

    return 0;
}