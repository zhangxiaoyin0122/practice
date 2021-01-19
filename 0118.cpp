#include <iostream>
using namespace std;
//直接插入排序
void insertSort(int* array, int n) {
	for (int i = 0; i < n-1; i++) {
		int end = i;
		int key = array[end+1];
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
//交换函数
void Swap(int* array, int left, int right) {
	int tmp = array[left];
	array[left] = array[right];
	array[right] = tmp;
}
//直接选择排序:
//第一种:
void selectSort(int* array, int n) {
	for (int i = 0; i < n-1; i++) {
		int min = i;
		int start = i;
		for (int j = start + 1; j < n; j++) {
			if (array[min] > array[j])
				min = j;
		}
		Swap(array, min, start);
	}
}
//第二种:
void selectSort1(int* array, int n) {
	int begin = 0;
	int end = n - 1;
	while (begin < end) {
		int min = begin;
		int max = begin;
		for (int i = begin + 1; i <= end; i++) {
			if (array[i] > array[max])
				max = i;
			if (array[i] < array[min])
				min = i;
		}
		//找出最大值与最小值
		Swap(array, end, max);
		if (min == end) {
			min = max;
		}
		Swap(array, min, begin);
		begin++;
		end--;
	}
}
//堆排序:
//利用向下调整建堆(建大堆)
void shiftDown(int* array, int n, int parent) {
	int child = 2 * parent + 1;
	while (child < n) {
		if (child + 1 < n && array[child] < array[child + 1]) {
			child++;
		}
		if (array[child] > array[parent]) {
			Swap(array, parent, child);
			parent = child;
			child = 2 * parent + 1;
		}
		else
			break;
	}
}
//堆排序
void heapSort(int* array, int n) {
	//利用多次向下调整建大堆
	for (int i = (n - 2) / 2; i >= 0; i--) {
		shiftDown(array, n, i);
	}
	while (n) {
		Swap(array, 0, n - 1);
		n--;
		shiftDown(array, n, 0);
	}
}
//冒泡排序
void bubbleSort(int* array, int n) {
	while (n) {
		int flag = 1;
		for (int i = 0; i < n - 1; i++) {
			if (array[i] > array[i + 1]) {
				Swap(array, i, i + 1);
				flag = 0;
			}
		}
		if (flag)
			break;
		n--;
	}
}
//快排优化:三数取中key
int GetMid(int* array, int begin, int end) {
	int mid = begin + (end - begin) / 2;
	if (array[begin] < array[mid]) {
		if (array[mid] < array[end])
			return mid;
		else {
			if (array[begin] > array[end])
				return begin;
			else
				return end;
		}
	}
	else {
		if (array[mid] > array[end])
			return mid;
		else {
			if (array[begin] > array[end])
				return end;
			else
				return begin;
		}
	}
}

//快排:
//1.霍尔法取基准点:
int partion(int* array, int begin, int end) {
	int mid = GetMid(array, begin, end);
	Swap(array, begin, mid);
	int key = array[begin];
	int start = begin;
	while (begin < end) {
		while (begin < end && array[end] >= key) {
			end--;
		}
		while (begin < end && array[begin] <= key) {
			begin++;
		}
		Swap(array, begin, end);
	}
	Swap(array, start, begin);
	return begin;
}

//挖坑法:
int partion1(int* array, int begin, int end) {
	int mid = GetMid(array, begin, end);
	Swap(array, begin, mid);
	int key = array[begin];
	int start = begin;
	while (begin < end) {
		while (begin < end && array[end] >= key) {
			end--;
		}
		array[begin] = array[end];
		while (begin < end && array[begin] <= key) {
			begin++;
		}
		array[end] = array[begin];
	}
	//基准值入坑
	array[begin] = key;
	return begin;
}
//前后指针法:
int partion2(int* array, int begin, int end) {
	int mid = GetMid(array, begin, end);
	Swap(array, begin, mid);

	int prev = begin;
	int cur = prev + 1;
	int key = array[begin];
	while (cur <= end) {
		if (array[cur] < key && ++prev != cur) {
			Swap(array, prev, cur);
		}
		cur++;
	}
	Swap(array, begin, prev);
	return prev;
}
//递归实现快排
void quickSort(int* array, int begin, int end) {
	if (begin >= end) {
		return;
	}
	int keyPos = partion(array, begin, end);
	quickSort(array, 0, keyPos - 1);
	quickSort(array, keyPos + 1, end);
}


//计数排序:
void CountSort(int* array, int n) {
	//统计范围
	int min = array[0], max = array[0];
	for (int i = 1; i < n; i++) {
		if (array[i] < min)
			min = array[i];
		if (array[i] > max)
			max = array[i];
	}
	//开空间
	int range = max - min + 1;
	int* countArr = (int*)malloc(sizeof(int)*range);
	memset(countArr, 0, sizeof(int)*range);

	//计数
	for (int i = 0; i < range; i++) {
		countArr[array[i] - min]++;
	}
	//恢复数组
	int idx = 0;
	for (int i = 0; i < range; i++) {
		while (countArr[i]--) {
			array[idx++] = i + min;
		}
	}
	free(countArr);
}
void test() {
	int array[10] = { 6,2,3,5,4,1,9,8,7,0 };
	int sz = sizeof(array) / sizeof(array[0]);
	//insertSort(array, sz);
	//shellSort(array, sz);
	//selectSort1(array, sz);
	//heapSort(array, sz);
	//bubbleSort(array, sz);
	quickSort(array, 0, sz - 1);
	for (int i = 0; i < sz; i++) {
		cout << array[i] << " ";
	}
	cout << endl;
}
int main() {
	test();
	return 0;
}