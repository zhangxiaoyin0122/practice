#include <iostream>
using namespace std;
//ֱ�Ӳ�������
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
//��������
void Swap(int* array, int left, int right) {
	int tmp = array[left];
	array[left] = array[right];
	array[right] = tmp;
}
//ֱ��ѡ������:
//��һ��:
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
//�ڶ���:
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
		//�ҳ����ֵ����Сֵ
		Swap(array, end, max);
		if (min == end) {
			min = max;
		}
		Swap(array, min, begin);
		begin++;
		end--;
	}
}
//������:
//�������µ�������(�����)
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
//������
void heapSort(int* array, int n) {
	//���ö�����µ��������
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

//����:
//1.������ȡ��׼��:
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

//�ڿӷ�:
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
	//��׼ֵ���
	array[begin] = key;
	return begin;
}
//ǰ��ָ�뷨:
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
//�ݹ�ʵ�ֿ���
void quickSort(int* array, int begin, int end) {
	if (begin >= end) {
		return;
	}
	int keyPos = partion(array, begin, end);
	quickSort(array, 0, keyPos - 1);
	quickSort(array, keyPos + 1, end);
}


//��������:
void CountSort(int* array, int n) {
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
	memset(countArr, 0, sizeof(int)*range);

	//����
	for (int i = 0; i < range; i++) {
		countArr[array[i] - min]++;
	}
	//�ָ�����
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