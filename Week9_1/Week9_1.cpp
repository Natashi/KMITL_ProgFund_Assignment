#define _CRT_SECURE_NO_WARNINGS     //Screw your safety nets

#include <iostream>

using namespace std;

struct linked_list_int_node {
	int data;
	linked_list_int_node* prev = nullptr;
	linked_list_int_node* next = nullptr;
};
struct linked_list_int {
	linked_list_int_node* begin = nullptr;
	linked_list_int_node* end = nullptr;

	size_t size = 0U;

	~linked_list_int() {
		linked_list_int_node* iNode = begin;
		while (iNode) {
			linked_list_int_node* next = iNode->next;
			delete iNode;
			iNode = next;
		}
	}

	linked_list_int_node* insert_back(int x) {
		linked_list_int_node* newNode = new linked_list_int_node();
		newNode->data = x;
		newNode->next = nullptr;
		if (begin == nullptr) {
			newNode->prev = nullptr;
			begin = newNode;
		}
		else if (end == nullptr) {
			newNode->prev = begin;
			begin->next = newNode;
			end = newNode;
		}
		else {
			newNode->prev = end;
			end->next = newNode;
			end = newNode;
		}
		++size;
 		return newNode;
	}
};

int main() {
	linked_list_int list;

	size_t count = 0;
	printf("Input the amount of numbers: ");
	if (scanf("%u", &count)) {
		printf("Input %u number(s):\n", count);
		{
			size_t iCount = 0;
			while (iCount < count) {
				int tmp;
				if (scanf("%d", &tmp)) {
					list.insert_back(tmp);
					++iCount;
				}
			}
		}

		printf("Inverted sequence:\n");
		for (linked_list_int_node* iNode = list.end; iNode != nullptr; iNode = iNode->prev) {
			printf("%d ", iNode->data);
		}
	}
	else
		printf("Amount must be a valid positive integer.");

	return 0;
}