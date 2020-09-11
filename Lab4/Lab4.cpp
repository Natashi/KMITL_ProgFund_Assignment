#define _CRT_SECURE_NO_WARNINGS     //Screw your safety nets

#include <iostream>
#include <conio.h>
#include <windows.h>

HANDLE stdoutHandle = INVALID_HANDLE_VALUE;
constexpr const int BOUND_L = 0;
constexpr const int BOUND_T = 0;
constexpr const int BOUND_R = 80;
constexpr const int BOUND_B = 25;

class ShipObj {
public:
    ShipObj(int x, int y) : x_(x), y_(y) {
        UpdateShip(0, 0);
    }

    void UpdateShip(int dx, int dy) {
        SetConsoleCursorPosition(stdoutHandle, { (SHORT)x_, (SHORT)y_ });
        puts("     ");
        x_ += dx;
        y_ += dy;
        x_ = max(x_, BOUND_L + 1);
        x_ = min(x_, BOUND_R - 6);
        y_ = max(y_, BOUND_T + 1);
        y_ = min(y_, BOUND_B - 2);
        SetConsoleCursorPosition(stdoutHandle, { (SHORT)x_, (SHORT)y_ });
        puts("<-0->");
    }
private:
    int x_;
    int y_;
};

int main() {
#define SKIP_L for (int i = 0; i < BOUND_L; ++i) putchar(' ');
    for (int i = 0; i < BOUND_T; ++i) putchar('\n');

    SKIP_L for (int i = BOUND_L; i < BOUND_R; ++i)
        putchar('*');
    putchar('\n');

    for (int i = BOUND_T + 1; i < BOUND_B - 1; ++i) {
        SKIP_L putchar('*');
        for (int i = BOUND_L + 1; i < BOUND_R - 1; ++i) putchar(' ');
        putchar('*');
        putchar('\n');
    }

    SKIP_L for (int i = BOUND_L; i < BOUND_R; ++i)
        putchar('*');
    putchar('\n');
#undef SKIP_L

    stdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    if (stdoutHandle == INVALID_HANDLE_VALUE) {
        printf("Error acquiring console handle.");
        return -1;
    }

    ShipObj* objShip = new ShipObj(39, 13);

    bool bFinish = false;
    while (!bFinish) {
        char ch = _getch();
        switch (ch) {
        case 'x':
            bFinish = true;
            break;
        case 'w':
            objShip->UpdateShip(0, -1);
            break;
        case 'a':
            objShip->UpdateShip(-1, 0);
            break;
        case 's':
            objShip->UpdateShip(0, 1);
            break;
        case 'd':
            objShip->UpdateShip(1, 0);
            break;
        }
    }

    SetConsoleCursorPosition(stdoutHandle, { (SHORT)0, (SHORT)(BOUND_B + 1) });
    return 0;
}