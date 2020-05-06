#include "PrintCombination.h"

#define ELEMENTS_FOR_COMBINATION 5	//i.e., C(5,4)
#define DLEMENTS_FOR_CHOICE 4

int main(void)
{
	int *arrayPtr = new int[ELEMENTS_FOR_COMBINATION];

	//Get all elements for combination
	for (int i = 0; i < ELEMENTS_FOR_COMBINATION; ++i)
		arrayPtr[i] = i + 1;

	PrintCombination(arrayPtr, ELEMENTS_FOR_COMBINATION, DLEMENTS_FOR_CHOICE);

	if (arrayPtr != NULL)
		delete[] arrayPtr;

	return 0;
}
