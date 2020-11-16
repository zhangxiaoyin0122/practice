#include <iostream>
using namespace std;

//交换函数
void Swap(int* array, int min, int start) {
	int tmp = array[min];
	array[min] = array[start];
	array[start] = tmp;
}

//插入排序
void insertSort(int* array, int n) {
	for (int i = 0; i < n - 1; i++) {
		//end 已排序的最后一个位置
		//k 待插入的元素(数据)
		int end = i;
		int key = array[end + 1];
		//找到第一个小于等于key的位置
		//如果array[end]的值大于k的值则向后移动
		while (end >= 0 && array[end] > key) {
			array[end + 1] = array[end];
			end--;
		}
		//插入到end的后面
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

//直接选择排序
void selectSort1(int* array, int n) {
	for (int i = 0; i < n - 1; i++) {
		int min = i;
		int start = i;
		for (int j = start + 1; j < n; j++) {
			if (array[j] < array[min]) {
				min = j;
			}
		}
		Swap(array, start, min);
	}
}



//利用多次向下调整建堆
void shiftDown(int* array, int n, int parent) {
	int child = parent * 2 + 1;
	while (child < n) {
		if (child + 1 < n && array[child] < array[child + 1])
			child++;
		if (array[parent] < array[child])
			Swap(array, parent, child);
	}
}
//堆排序
void heapSort(int* array, int n) {
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
	//往后冒泡
	while (n) {
		int flag = 1; // flag = 1 表示未交换
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

//快速排序:

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

//hoare法获取基准点:
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
	//begin 与 end 相遇
	Swap(array, start, begin);
	return begin;
}

//递归实现快排
void quickSort(int* array, int begin, int end) {
	if (begin >= end)
		return;
	int keyPos = partion(array, begin, end);
	quickSort(array, begin, keyPos - 1);
	quickSort(array, keyPos + 1, end);
}

//两个有序数组的合并
void merge(int* array, int begin, int mid, int end, int* tmp) {
	int begin1 = begin, end1 = mid, begin2 = mid + 1, end2 = end;
	int idx = begin;
	while (begin1 <= end1 && begin2 <= end2) {
		if (array[begin1] <= array[begin2])
			tmp[idx++] = array[begin1++];
		else
			tmp[idx++] = array[begin2++];
	}
	if (begin1 <= end1)
		memcpy(tmp + idx, array + begin1, sizeof(int)*(end1 - begin1 + 1));
	if (begin2 <= end2)
		memcpy(tmp + idx, array + begin2, sizeof(int)*(end2 - begin2 + 1));
	memcpy(array + begin, tmp + begin, sizeof(int)*(end - begin + 1));
}


//递归实现归并排序(实际就是分解)
void mergeSortR(int* array, int begin, int end, int* tmp) {
	if (begin >= end)
		return;
	int mid = begin + (end - begin) / 2;
	mergeSortR(array, begin, mid, tmp);
	mergeSortR(array, mid + 1, end, tmp);
	merge(array, begin, mid, end, tmp);
}

void mergeSort(int* array, int n) {
	int* tmp = (int*)malloc(sizeof(int)*n);
	mergeSortR(array, 0, n - 1, tmp);
	free(tmp);
}

void mergeSortNor(int* array, int n) {
	int* tmp = (int*)malloc(sizeof(int)*n);
	int k = 1;
	while (k < n) {
		for (int i = 0; i < n; i += 2 * k) {

			int begin = i;
			int mid = i + k - 1;
			if (mid >= n - 1)
				continue;
			int end = i + 2 * k - 1;
			if (end > n - 1)
				end = n - 1;
			merge(array, begin, mid, end, tmp);
		}
		k = 2 * k;
	}
	free(tmp);
}
//桶排序
void countSort(int* array, int n) {
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
	//将数组初始化为全0
	memset(countArr, 0, sizeof(int)*range);

	//计数
	for (int i = 0; i < range; i++) {
		countArr[array[i] - min]++;
	}
	//恢复数组
	int idx = 0;
	for (int i = 0; i < range; i++) {
		while (countArr[i]--)
			array[idx++] = i + min;
	}
	free(countArr);
}
