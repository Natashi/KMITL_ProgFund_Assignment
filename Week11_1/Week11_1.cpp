#define _CRT_SECURE_NO_WARNINGS     //Screw your safety nets

#include <iostream>

using namespace std;

struct Box {
	float l;
	float t;
	float r;
	float b;
};

bool IsIntersected(Box* l, Box* r) {
	return !(r->l > l->r || r->r < l->l
		|| r->t > l->b || r->b < l->t);
}

int main() {
	Box listBox[2];

	printf("Input first rectangle (left, top, right, bottom): ");
	if (scanf("%f %f %f %f", &listBox[0].l, &listBox[0].t, &listBox[0].r, &listBox[0].b)) {
		printf("Input second rectangle (left, top, right, bottom): ");
		if (scanf("%f %f %f %f", &listBox[1].l, &listBox[1].t, &listBox[1].r, &listBox[1].b)) {
			bool res = IsIntersected(&listBox[0], &listBox[1]);
			printf("The given rectangles %sintersect.", res ? "" : "do not ");
		}
		else goto lab_invalid_box;
	}
	else {
lab_invalid_box:
		printf("Invalid box.");
	}

	return 0;
}