#define _CRT_SECURE_NO_WARNINGS     //Screw your safety nets

#include <iostream>

using namespace std;

bool IsPalindrome(char* str) {
	char* sPtr = str;
	char* ePtr = sPtr;
	while (*ePtr) ++ePtr;
	--ePtr;

	while (sPtr < ePtr) {
		if (*sPtr != *ePtr) return false;
		++sPtr;
		--ePtr;
	}
	return true;
}

int main() {
	char str[512];

	printf("Input a string: ");
	scanf("%511s", str);

	printf("Input is %sa palindrome", IsPalindrome(str) ? "" : "not ");

	return 0;
}