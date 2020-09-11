#define _CRT_SECURE_NO_WARNINGS     //Screw your safety nets

#include <iostream>

using namespace std;

double _invsqroot(double x) {
    uint64_t _as_ui64 = *(uint64_t*)&x;
    double x2 = x * 0.5;
    double res = x;
    _as_ui64 = 0x5fe6eb50c7b537a9 - (_as_ui64 >> 1);   //Welcome to the gates of hell, again
    res = *(double*)&_as_ui64;
    res = res * (1.5 - (x2 * res * res));
    return res;
}
double hypot(double x, double y) {
    return 1.0 / _invsqroot(x * x + y * y);
}

int main() {
    double x, y;

    printf("Input two lengths: ");
    if (scanf("%lf %lf", &x, &y)) {
        printf("The length of the hypotenuse is: %.2f", hypot(x, y));
    }
    else
        printf("One of them's not a number.");

    return 0;
}