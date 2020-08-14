#define _CRT_SECURE_NO_WARNINGS     //Screw your safety nets

#include <iostream>

using namespace std;

int main() {
    int depth;

    scanf("%d", &depth);
    if (depth >= 0) {
        printf("Ah, yes, pyramids. The staple of modern diet.\nNo, please don't actually eat one.\n");
        printf("Well, here's your anyways. %d blocks tall, just as you requested.\n", depth);

        if (depth == 0) {
            printf("\nThat's a very flat pyramid.\n");
        }
        else {
            for (int i = 0; i < depth; ++i) {
                int pitch = depth - i - 1;
                int block = (i + 1) * 2 - 1;
                for (int j = 0; j < pitch; ++j) putchar(' ');
                for (int j = 0; j < block; ++j) putchar('*');
                putchar('\n');
            }
        }
    }
    else {
        printf("We don't produce upside-down pyramids here.\n");
    }

    return 0;
}