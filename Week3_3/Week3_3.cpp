#define _CRT_SECURE_NO_WARNINGS     //Screw your safety nets

#include <iostream>

using namespace std;

int64_t FlipSign(int64_t x) {
    uint64_t neg = ~((uint64_t)x);
    return (int64_t&)neg + 1;
}

int main() {
    int64_t n;

    printf("Input number: ");
    if (scanf("%lld", &n)) {
        printf("The %s counterpart is: %lld", (n >> 63) ? "positive" : "negative", FlipSign(n));
    }
    else
        printf("That's not a number.");

    return 0;
}