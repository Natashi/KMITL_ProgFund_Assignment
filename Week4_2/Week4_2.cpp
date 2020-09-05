#define _CRT_SECURE_NO_WARNINGS     //Screw your safety nets

#include <iostream>

using namespace std;

struct Circle {
    float x;
    float y;
    float r;
};

bool IsIntersected(Circle* l, Circle* r) {
    float dx = l->x - r->x;
    float dy = l->y - r->y;
    float rr = l->r + r->r;
    return (dx * dx + dy * dy) <= (rr * rr);
}

int main() {
    Circle* listCircle = new Circle[2];

    printf("Input first circle (x, y, r): ");
    if (scanf("%f %f %f", &listCircle[0].x, &listCircle[0].y, &listCircle[0].r)) {
        printf("Input second circle (x, y, r): ");
        if (scanf("%f %f %f", &listCircle[1].x, &listCircle[1].y, &listCircle[1].r)) {
            bool res = IsIntersected(&listCircle[0], &listCircle[1]);
            printf("The given circles %sintersect.", res ? "" : "do not ");
        }
    }

    delete[] listCircle;
    return 0;
}