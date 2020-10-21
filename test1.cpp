//#include <iostream>
//using namespace std;
//
//int& add1(int& a) {
//	return ++a;
//}
//int& add2(int a) {
//	return ++a;
//}
//
//int main() {
//	int a = 1;
//	int& b = add1(a);
//	int& c = add2(a);
//	cout << b << endl;
//	cout << c << endl;
//	cout << sizeof(nullptr) << endl;
//	cout << sizeof(0) << endl;
//	cout << sizeof((void*)0) << endl;
//	return 0;
//}
//
//class Solution {
//public:
//	bool isPalindrome(int x) {
//		if (x < 0 || (x % 10 == 0 && x != 0))
//			return false;
//		int sum = 0;
//		while (x > sum) {
//			sum = 10 * sum + x % 10;
//			x /= 10;
//		}
//		return x == sum || x == sum / 10;
//	}
//};
//
//
#define  _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

class String {
public:
	typedef char* iterator;
	typedef const char* const_iterator;

	iterator begin() {
		return _str;
	}
	iterator end() {
		return _str + _size;
	}
	const_iterator begin()const {
		return _str;
	}
	const_iterator end()const {
		return _str + _size;
	}
	//�޲ι��캯��
	String()
		:_str(new char[16])
		, _size(0)
		, _capacity(strlen(_str)) 
	{
		_str[_size] = '\0';
	}
	//���캯��
	String(const char* str) {
		_size = strlen(str);
		_str = new char[_size+1];
		_capacity = _size;
		strcpy(_str, str);
	}
	//��������
	/*String(const String& str)
		:_str(new char[str._capacity])
		,_size(str._size)
		,_capacity(str._capacity)
	{
		strcpy(_str, str._str);
	}*/
	void Swap(String& str) {
		swap(_str, str._str);
		swap(_size, str._size);
		swap(_capacity, str._capacity);
	}
	//���������ִ�д��
	String(const String& str) 
		:_str(nullptr)
		,_size(0)
		,_capacity(0)
	{
		String tmp(str._str);
		Swap(tmp);
	}
	//��ֵ��������غ���
	/*String& operator=(const String& str) {
		if (this != &str) {
			//���ٿռ�
			char* tmp = new char[str._capacity+1];
			//���:
			strcpy(tmp, str._str);
			//�ͷ�ԭ�пռ�
			delete[] _str;
			_str = tmp;
			_size = str._size;
			_capacity = str._capacity;
		}
		return *this;
	}*/
	//��ֵ��������غ���(�ִ�д��);
	String& operator=(String str) {
		Swap(str);
		return *this;
	}
	//��������
	~String() {
		if (_str) {
			delete[]_str;
			_str = nullptr;
			_size = _capacity = 0;
		}
	}
private:
	char* _str;
	int _size;
	int _capacity;
};


void print() {
	String str("asdfgfghj");
	//��Χfor:
	for (auto i : str) {
		cout << i << " ";
	}
	cout << endl;

	//����������:
	String::iterator it = str.begin();
	while (it != str.end()) {
		cout << *it << " ";
		++it;
	}
	cout << endl;
}

void swap(int* array, int left, int right) {
	int tmp = array[left];
	array[left] = array[right];
	array[right] = tmp;
}
//ð������:
void bubbleSort(int* array, int n) {
	while (n--) {
		int flag = 1;
		for (int i = 1; i <= n; i++) {
			if (array[i] < array[i - 1]) {
				swap(array, i, i - 1);
				flag = 0;
			}
		}
		if (flag) {
			break;
		}
	}
}
//��������:
void insertSort(int* array, int n) {
	for (int i = 0; i < n-1; i++) {
		int end = i;
		int key = array[i+1];
		while (end >= 0 && array[end] > key) {
			array[end + 1] = array[end];
			end--;
		}
		array[end + 1] = key;
	}
}
void test() {
	int array[10] = { 9,5,6,3,1,7,4,0,8,2 };
	int size = sizeof(array) / sizeof(array[0]);
	//bubbleSort(array, size);
	insertSort(array, size);
	for (int i = 0; i < size; i++) {
		cout << array[i] << " ";
	}
	cout << endl;
}
int main() {
	print();
	test();
	return 0;
}