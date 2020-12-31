#include <iostream>
using namespace std;

//ֱ�Ӳ�������
void insertSort(int*  array, int n) {
	for (int i = 0; i < n - 1; i++) {
		int end = i; //���������е����һ��λ��
		int key = array[end + 1]; //������Ԫ�ص�ֵ
		while (i >= 0 && key < array[end]) {
			//�ҵ���һ��С�ڵ���key��ֵ
			//���array[end]��ֵ����key��ֵ,������ƶ�
			array[end + 1] = array[end];
			end--;
		}
		array[end + 1] = key;
	}
}

//ϣ������(��С��������):�Ľ����ֱ�Ӳ�������
void shellSort(int* array, int n) {
	int gap = n;
	while (gap > 1) {
		gap = gap / 2;
		for (int i = 0; i < n - gap; i += gap) {
			int end = i;
			int key = array[end + gap];
			while (i >= 0 && array[end] > key) {
				array[end + gap] = array[end];
				end -= gap;
			}
			array[end + gap] = key;
		}
	}
}

void Swap(int* array, int left, int right) {
	int tmp = array[left];
	array[left] = array[right];
	array[right] = tmp;
}
//ѡ������1:
void sellectSort(int* array, int n) {
	for (int i = 0; i < n-1; i++) {
		int start = i;
		int min = i;
		for (int j = start + 1; j < n; j++) {
			if (array[j] < array[min])
				min = j;
		}
		Swap(array, start, min);
	}
}
//ѡ������2:
void sellectSort2(int* array, int n) {
	int begin = 0;
	int end = n - 1;
	while (begin < end) {
		int min = begin;
		int max = begin;
		for (int i = begin + 1; i <= end; i++) {
			if (array[i] >= array[max])
				max = i;
			if (array[i] < array[min])
				min = i;
		}
		Swap(array, begin, min);
		if (max == begin) {
			max = min;
		}
		Swap(array, end, max);
		begin++;
		end--;
	}
}
//������
//���µ���
void shiftDown(int* array, int n, int parent) {
	int child = 2 * parent + 1;
	while (child < n) {
		if (child + 1 < n && array[child + 1] > array[child]) {
			child++;
		}
		if (array[child] > array[parent]) {
			Swap(array, child, parent);
		}
		else
			break;
	}
}
void heapSort(int* array, int n) {
	//���ö�����µ�������
	for (int i = (n - 2) / 2; i >= 0; i--) {
		shiftDown(array, n, i);
	}
	//��ʼ����
	while (n) {
		Swap(array, 0, n - 1);
		n--;
		shiftDown(array, n, 0);
	}
}
int main() {
	int array[10] = { 9,8,7,6,5,4,3,2,1,0 };
	int size = sizeof(array) / sizeof(array[0]);
	//insertSort(array, size);
	//shellSort(array, size);
	//sellectSort(array, size);
	//sellectSort2(array, size);
	heapSort(array, size);
	for (int i = 0; i < size; i++) {
		cout << array[i] << " ";
	}
	cout << endl;
	return 0;
}