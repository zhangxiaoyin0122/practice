#include <iostream>
using namespace std;
//直接插入排序
void insertSort(int* array, int n) {
	for (int i = 0; i < n - 1; i++) {
		int end = i;
		int key = array[end + 1];
		while (end >= 0 && array[end] > key) {
			array[end + 1] = array[end];
			end--;
		}
		array[end + 1] = key;
	}
}
//希尔排序
void shellSort(int* array, int n) {
	int gap = n;
	while (gap > 1) {
		gap = gap / 2;
		for (int i = 0; i < n - gap; i += gap) {
			int end = i;
			int key = array[end + gap];
			while (end >= 0 && array[end] > key) {
				array[end + gap] = array[end];
				end -= gap;
			}
			array[end + gap] = key;
		}
	}
}

void swap(int* array, int left, int right) {
	int tmp = array[left];
	array[left] = array[right];
	array[right] = tmp;
}
//向下调整
void shiftDown(int* array, int n, int parent) {
	int child = parent * 2 + 1;
	while (child < n) {
		if (child + 1 < n && array[child + 1] > array[child]) {
			child++;
		}
		if (array[parent] < array[child]) {
			swap(array, child, parent);
		}
		else
			break;
	}
}
//堆排序
void heapSort(int* array, int n) {
	//利用向下调整建堆
	for (int i = (n - 1) / 2; i >= 0; i--) {
		shiftDown(array, n, i);
	}

	while (n) {
		swap(array, 0, n - 1);
		n--;
		shiftDown(array, n, 0);
	}
}

void bubbleSort(int* array, int n) {
	//向后冒
	int flag = 1;
	while (n) {
		for (int i = 0; i < n - 1; i++) {
			if (array[i] > array[i+1]) {
				swap(array, i, i+1);
				flag = 0;
			}
		}
		if (flag)
			break;
		n--;
	}
}

void selectSort(int* array, int n) {	
	for (int i = 0; i < n; i++) {
		int min = i;
		int start = i;
		for (int j = i + 1; j < n; j++) {
			if (array[j] < array[min])
				min = j;
		}
		swap(array, start, min);
	}
}

int partion(int* array, int begin, int end) {
	int key = array[begin];
	int start = begin;
	while (begin < end) {
		while (begin < end && array[end] >= key) {
			end--;
		}
		while (begin < end && array[begin] <= key) {
			begin++;
		}
		swap(array, begin, end);
	}
	swap(array, start, begin);
	return begin;
}
void quickSort(int* array, int begin,int end) {
	if (begin > end)
		return;
	int keyPos = partion(array, begin, end);
	quickSort(array, 0,keyPos);
	quickSort(array, keyPos + 1, end);
}

int main() {
	int arr[9] = { 1,5,2,3,6,4,9,7,8 };
	int sz = sizeof(arr) / sizeof(arr[0]);
	//insertSort(arr, sz);
	//shellSort(arr, sz);
	//bubbleSort(arr, sz);
	selectSort(arr, sz);
	for (int i = 0; i < sz; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
	return 0;
}