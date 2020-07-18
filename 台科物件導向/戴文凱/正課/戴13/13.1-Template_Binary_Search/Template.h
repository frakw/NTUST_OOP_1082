#pragma once
template<typename T>
void ItrBinarySearch(const T a[], int first, int last, T key, bool& found, int& location) {
	int mid = (first + last) / 2;;
	while (last >= first) {//要用>= 不可用>
		if (key > a[mid]) {
			first = mid + 1;
		}
		else if (key < a[mid]) {
			last = mid - 1;
		}
		else {
			location = mid;
			found = true;
			return;
		}
		mid = (first + last) / 2;
	}
	found = false;
	return;
}


template<typename T>
void RecBinarySearch(const T a[], int first, int last, T key, bool& found, int& location) {
	if (first > last) {//要用>= 不可用>
		found = false;
		return;
	}
	int mid = (first + last) / 2;
	if (key > a[mid]) {
		RecBinarySearch(a, mid + 1, last, key, found, location);
	}
	else if (key < a[mid]) {
		RecBinarySearch(a, first, mid - 1, key, found, location);
	}
	else {
		found = true;
		location = mid;
	}
}