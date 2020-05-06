#include "PrintCombination.h"

void PrintCombination(int* arr, const int& combination_num, const int& dlement_num) {
	static bool init = false;
	if (!init) {//ªì©l¤Æ
		int* pre_store = new int[combination_num];
		for (int i = 0;i < combination_num;i++) {
			pre_store[i] = arr[i];
		}
		init = true;
		for (int i = dlement_num;i < combination_num;i++) {
			arr[i] = 0;
		}
		arr[combination_num - 1] = -87;
		PrintCombination(arr, dlement_num, dlement_num - 1);
		init = false;
		for (int i = 0;i < combination_num;i++) {
			arr[i] = pre_store[i];
		}
		delete[] pre_store;
		return;
	}
	int max_num = 0, max_index = -1;
	for (int i = 0;true;i++) {
		if (arr[i] <= 0 && max_index == -1) {
			max_index = i - 1;
		}
		if (arr[i] == -87) {
			max_num = i + 1;//5
			break;
		}
	}
	for (int i = max_index;i >= dlement_num;i--) {
		arr[i] = combination_num + (i - dlement_num);//3 4
		if (arr[i] > (i + max_num - max_index)) {
			if (dlement_num == 0) {//err handle
				return;//³Ì²×
			}	
			PrintCombination(arr, arr[dlement_num - 1] + 1, dlement_num - 1);
			return;
		}
	}
	for (int i = 0;i <= max_index;i++) {
		cout << arr[i] << ' ';
	}
	cout << endl;
	PrintCombination(arr, arr[max_index] + 1, max_index);
}