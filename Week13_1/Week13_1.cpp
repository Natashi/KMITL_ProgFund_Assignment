#define _CRT_SECURE_NO_WARNINGS     //Screw your safety nets

#include <iostream>

using namespace std;

//Peak degeneracy
void StringToOWO(const char* strIn, size_t inSize, char* strOut, size_t outSizeMax, size_t* pWritten) {		
	size_t iStr = 0;

	auto LoadChar = [&](char c) {
		if (iStr >= outSizeMax) return;
		strOut[iStr++] = c;
	};

	if (outSizeMax >= 5) {
		outSizeMax -= 5;	//For null terminator and ' owo'

		while (iStr < outSizeMax) {
			char ch = *strIn;
			if (ch == '\0') break;

			if (ch == 'i' || ch == 'e')
				LoadChar('w');
			LoadChar(ch);

			++strIn;
		}

		LoadChar(' ');
		LoadChar('o');
		LoadChar('w');
		LoadChar('o');
		LoadChar('\0');		//Terminator
	}

	if (pWritten) *pWritten = iStr;
}

int main() {
	char str[512];

	printf("Input string: ");
	if (scanf("%511[^\n]", str)) {
		char strRes[1024];

		size_t resCount;
		StringToOWO(str, 512, strRes, 1024, &resCount);
		
		if (resCount > 0)
			printf("Degeneracy applied.\n%s", strRes);
	}

	return 0;
}