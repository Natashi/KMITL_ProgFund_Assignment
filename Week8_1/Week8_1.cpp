#define _CRT_SECURE_NO_WARNINGS     //Screw your safety nets

#include <iostream>

using namespace std;

bool _isdigit(char x) {
	return (x >= '0' && x <= '9');
}
unsigned int _strtoul(const char* str, char** end) {
	unsigned int res = 0U;
	while (_isdigit(*str)) {
		res = res * 10U + (*str - '0');
		++str;
	}
	if (end) *end = (char*)str;
	return res;
}

int main() {
	char str[512];

	printf("Input string: ");
	if (scanf("%511s", str)) {
		unsigned int sum = 0U;

		char* cPtr = &str[0];
		char* ePtr = cPtr;
		while (*ePtr != '\0') ++ePtr;	//strlen-ish

		while (cPtr < ePtr) {
			if (_isdigit(*cPtr)) {
				char* nextPtr = cPtr;
				sum += _strtoul(cPtr, &nextPtr);
				cPtr = nextPtr;
			}
			else ++cPtr;
		}

		printf("Extracted number: %04u", sum);
	}

	return 0;
}