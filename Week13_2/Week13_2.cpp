#define _CRT_SECURE_NO_WARNINGS     //Screw your safety nets

#include <iostream>

using namespace std;

struct Chunk {
	size_t size;
	float* list;
};

size_t CreateChunkList(float* pNumList, size_t countNum, Chunk** ppChunk, size_t sizeChunk) {
	size_t totalChunks = countNum / sizeChunk;
	if ((totalChunks * sizeChunk) < countNum) ++totalChunks;

	*ppChunk = new Chunk[totalChunks];

	{
		Chunk tmpChunk;
		tmpChunk.size = sizeChunk;
		tmpChunk.list = new float[sizeChunk];

		size_t iChunk = 0, cChunk = 0;
		for (size_t iNum = 0; iNum < countNum; ++iNum) {
			tmpChunk.list[cChunk] = pNumList[iNum];

			++cChunk;
			if ((cChunk >= sizeChunk) || (iNum == countNum - 1)) {
				tmpChunk.size = cChunk;
				(*ppChunk)[iChunk] = tmpChunk;

				tmpChunk.list = new float[sizeChunk];

				cChunk = 0;
				++iChunk;
			}
		}
	}

	return totalChunks;
}

int main() {
	int countNumber = 0;
	int sizeChunk = 0;

	printf("Input the amount of numbers and the chunk size: ");
	if (scanf("%d %d", &countNumber, &sizeChunk)) {
		if (!(countNumber > 0 && sizeChunk > 0)) goto lab_cnt_fail;

		float* listNumber = new float[countNumber];
		Chunk* listChunks = nullptr;

		printf("Input %d numbers: ", countNumber);
		for (int i = 0; i < countNumber;) {
			if (scanf("%f", &listNumber[i])) ++i;
		}

		size_t countChunks = CreateChunkList(listNumber, countNumber, &listChunks, sizeChunk);
		{
			printf("\nFormatted chunks: [");
			for (size_t iChunk = 0; iChunk < countChunks; ++iChunk) {
				Chunk* pChunk = &listChunks[iChunk];
				printf("[");
				for (size_t iNum = 0; iNum < pChunk->size; ++iNum) {
					printf("%.1f", pChunk->list[iNum]);
					if (iNum != pChunk->size - 1) printf(", ");
				}
				printf("]");
				if (iChunk != countChunks - 1) printf(", ");
			}
			printf("]");
		}
	}
	else {
lab_cnt_fail:
		printf("Number count and chunk size must be positive integers.");
	}

	return 0;
}