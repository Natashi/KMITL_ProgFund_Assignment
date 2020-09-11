#define _CRT_SECURE_NO_WARNINGS     //Screw your safety nets

#include <iostream>

using namespace std;

int main() {
    int count = 0;
    double* data = nullptr;

    printf("Input the amount of numbers: ");
    if (scanf("%d", &count) && count >= 0) {
        data = new double[count];

        printf("Input %d number(s): ", count);
        {
            int iCount = 0;
            while (iCount < count) {
                if (scanf("%lf", &data[iCount]))
                    ++iCount;
            }
        }

        double sum = 0.0;
        for (int i = 0; i < count; ++i)
            sum += data[i];
        printf("The sum is %.3f.", sum);

        delete[] data;
    }
    else
        printf("Amount must be a valid positive integer.");

    return 0;
}