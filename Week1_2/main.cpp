#define _CRT_SECURE_NO_WARNINGS     //Screw your safety nets

#include <iostream>

using namespace std;

int _abs(int x) {
    return (x >> 31) ? ((int)(~x) + 1) : x;
}

int main() {
    int depth;

    printf("Input the pyramid's height: ");
    scanf("%d", &depth);
    if (depth == 0) {
        printf("That's a very flat pyramid.\n");
    }
    else {
        printf("Ah, yes, pyramids. The staple of modern diet.\nNo, please don't actually eat one.\n");
        printf("Well, here's your anyways. %d block%s tall%s, just as you requested.\n", _abs(depth),
            _abs(depth) == 1 ? "" : "s", depth < 0 ? ", and upside-down" : "");

        auto PrintRow = [](int width, int iRow) {
            int pitch = width - iRow - 1;
            int block = (iRow + 1) * 2 - 1;
            for (int j = 0; j < pitch; ++j) putchar(' ');
            for (int j = 0; j < block; ++j) putchar('*');
            putchar('\n');
        };

        if (depth > 0)
            for (int i = 0; i < depth; ++i) PrintRow(depth, i);
        else
            for (int i = -depth - 1; i >= 0; --i) PrintRow(-depth, i);
    }

    return 0;
}