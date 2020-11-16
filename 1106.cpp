#include <iostream>
using namespace std;

//��������
void Swap(int* array, int min, int start) {
	int tmp = array[min];
	array[min] = array[start];
	array[start] = tmp;
}

//��������
void insertSort(int* array, int n) {
	for (int i = 0; i < n - 1; i++) {
		//end ����������һ��λ��
		//k �������Ԫ��(����)
		int end = i;
		int key = array[end + 1];
		//�ҵ���һ��С�ڵ���key��λ��
		//���array[end]��ֵ����k��ֵ������ƶ�
		while (end >= 0 && array[end] > key) {
			array[end + 1] = array[end];
			end--;
		}
		//���뵽end�ĺ���
		array[end + 1] = key;
	}
}
//ϣ������
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

//ֱ��ѡ������
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



//���ö�����µ�������
void shiftDown(int* array, int n, int parent) {
	int child = parent * 2 + 1;
	while (child < n) {
		if (child + 1 < n && array[child] < array[child + 1])
			child++;
		if (array[parent] < array[child])
			Swap(array, parent, child);
	}
}
//������
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

//ð������
void bubbleSort(int* array, int n) {
	//����ð��
	while (n) {
		int flag = 1; // flag = 1 ��ʾδ����
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

//��������:

//�����Ż�:����ȡ��key
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

//hoare����ȡ��׼��:
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
	//begin �� end ����
	Swap(array, start, begin);
	return begin;
}

//�ݹ�ʵ�ֿ���
void quickSort(int* array, int begin, int end) {
	if (begin >= end)
		return;
	int keyPos = partion(array, begin, end);
	quickSort(array, begin, keyPos - 1);
	quickSort(array, keyPos + 1, end);
}

//������������ĺϲ�
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


//�ݹ�ʵ�ֹ鲢����(ʵ�ʾ��Ƿֽ�)
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
//Ͱ����
void countSort(int* array, int n) {
	//ͳ�Ʒ�Χ
	int min = array[0], max = array[0];
	for (int i = 1; i < n; i++) {
		if (array[i] < min)
			min = array[i];
		if (array[i] > max)
			max = array[i];
	}
	//���ռ�
	int range = max - min + 1;
	int* countArr = (int*)malloc(sizeof(int)*range);
	//�������ʼ��Ϊȫ0
	memset(countArr, 0, sizeof(int)*range);

	//����
	for (int i = 0; i < range; i++) {
		countArr[array[i] - min]++;
	}
	//�ָ�����
	int idx = 0;
	for (int i = 0; i < range; i++) {
		while (countArr[i]--)
			array[idx++] = i + min;
	}
	free(countArr);
}
