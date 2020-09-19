#define _CRT_SECURE_NO_WARNINGS     //Screw your safety nets

#include <iostream>

using namespace std;

void GetTotalFee(int shop, int hour, int* sum) {
	if (shop >= 1000)
		*sum = (hour - 3) * 40;
	else if (shop < 1000)
		*sum = (hour - 1) * 40;
	if (*sum < 0) sum = 0;
	else if (*sum >= 160) *sum = 150;
}

int main() {
	int s, h, m;

	printf("Input (Shopping, Hour, Minute): ");
	if (scanf("%d%d%d", &s, &h, &m) == 3) {
		if ((s | h | m) >> 31) {
			printf("Input can't be negative.");
		}
		else {
			h += m / 60;
			if (m % 60) ++h;

			int sum = 0;
			GetTotalFee(s, h, &sum);
			printf("Total parking fee: %d", sum);
		}
	}
	else {
		printf("Please input a valid format.");
	}

	return 0;
}