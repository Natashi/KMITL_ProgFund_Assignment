#define _CRT_SECURE_NO_WARNINGS     //Screw your safety nets

#include <iostream>

using namespace std;

int main() {
	int s, h, m;

	printf("Input (Shopping, Hour, Minute): ");
	if (scanf("%d%d%d", &s, &h, &m) == 3) {
		h += m / 60;
		if (m % 60) ++h;

		int sum = 0;
		if (s >= 1000)
			sum = (h - 3) * 40;
		else if (s < 1000)
			sum = (h - 1) * 40;
		if (sum >= 160) sum = 150;
		else if (sum < 0) sum = 0;

		printf("Total parking fee: %d", sum);
	}
	else {
		printf("Please input a valid format.");
	}

	return 0;
}