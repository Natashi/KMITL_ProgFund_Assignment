#define _CRT_SECURE_NO_WARNINGS     //Screw your safety nets

#include <iostream>

using namespace std;

int* _expand_alloc(int* ptr, size_t oldSize, size_t newSize) {
	int* newPtr = new int[newSize];
	memcpy(newPtr, ptr, oldSize * sizeof(int));
	delete[] ptr;
	return newPtr;
}

bool ExtractFactor(int x, int* res) {
	for (int i = 2; i < x; ++i) {
		if (x % i == 0) {
			*res = i;
			return true;
		}
	}
	return false;
}

int main() {
	int x;
	
	printf("Input an integer: ");
	if (scanf("%d", &x)) {
		size_t listResSize = 8;
		int* listRes = new int[listResSize];
		size_t listResIndex = 0;

		auto add_list = [&](int x) {
			listRes[listResIndex++] = x;
			if (listResIndex >= listResSize) {
				size_t newSize = listResSize * 2;
				listRes = _expand_alloc(listRes, listResSize, newSize);
				listResSize = newSize;
			}
		};

		//-----------------------------------------------------------------------

		int num = x;

		if (num != 1) {
			if (num < 0) {
				add_list(-1);
				num = -num;
			}
			while (true) {
				int nextFactor = 0;
				bool bFindNext = ExtractFactor(num, &nextFactor);
				if (bFindNext) {
					add_list(nextFactor);
					num /= nextFactor;
				}
				else break;
			};
			if (num != 1)
				add_list(num);
		}
		else {
			add_list(1);
		}

		//-----------------------------------------------------------------------

		if (listResIndex > 0) {
			printf("%d = ", x);

			if (listResIndex > 1) {
				size_t i = 0;
				while (true) {
					printf("%d", listRes[i]);
					if (++i >= listResIndex) break;
					printf(" * ");
				}
			}
			else {	//Prime
				printf("1 * %d", listRes[0]);
			}
		}

		delete[] listRes;
	}
	else {
		printf("Input must be an integer.");
	}

	return 0;
}