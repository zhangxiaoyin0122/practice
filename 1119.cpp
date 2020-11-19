#include <iostream>
using namespace std;

template <class T>
class Vector {
	//���캯��
	Vector()
		:_start(nullptr)
		, _finsh(nullptr)
		, _eos(nullptr)
	{}
	//��ȡ����Ԫ�ظ���
	size_t size()const {
		return _finsh - _start;
	}
	//��ȡ����������
	size_t capacity()const {
		return _eos - _start;
	}
	//β��
	void pushBack(const T& val) {
		if (_finsh == _eos) {
			//��Ҫ����
			size_t newC = capacity() == 0 ? 1 : 2 * capacity();
			reserve(newC);
		}
		*_finsh = val;
		_size++;
	}
	//����
	void reserve(size_t n) {
		if (n > capacity()) {
			size_t oldSize = size();
			//���ռ�
			T* tmp = new T[n];
			//���
			for (int i = 0; i < size(); i++) {
				tmp[i] = _start[i];
			}
			delete[] _start;
			_start = tmp;
			_finsh = _start + oldSize;
			_eos = _start + n;
		}
	}
	//����[]�����
	const T& operator[](size_t pos)const {
		if (pos < size())
			return _start[pos];
	}

	typedef T* iterator;
	typedef const T* const_iterator;

	iterator begin() {
		return _start;
	}
	iterator end() {
		return _finsh;
	}
	const_iterator begin()const {
		return _start;
	}
	const_iterator end()const {
		return _finsh;
	}
	//
	void resize(size_t n, const T& val = T()) {
		if (n > capacity()) {
			reserve(n);
		}
		if (n > size()) {
			//���
			while (_finsh != _start + n) {
				*finsh++ = val;
			}
		}
		//����size
		_finsh = _start + n;
	}
	void insert(iterator pos, const T& val) {
		if (pos >= _start && pos <= _finsh) {
			//
			size_t len = size();
			if (_finsh == _eos) {
				size_t newC = capacity() == 0 ? 1 : 2 * capacity();
				reserve(newC);
			}
			iterator end = _finsh;
			while (end > pos) {
				*end = *(end - 1);
				--end;
			}
			*pos = val;
			++_finsh;
		}
	}
	iterator erase(iterator pos) {
		if (pos >= _start && pos < _finsh) {
			iterator begin = pos + 1;
			while (begin < _finsh) {
				*(begin - 1) = *begin;
				++begin;
			}
			--_finsh;
			return pos;
		}
	}
	~Vector() {
		if (_start) {
			delete[] _start;
			_start = _finsh = _eos = nullptr;
		}
	}
	Vector(cosnt Vector& v)
		:_start(new T[v.capacity()])
	{
		for (auto& e : v) {
			_start[i] = e;
		}
		_finsh = _start + v.size();
		_eos = _start + v.capacity();
	}

	Vector<T>& operator=(cosnt Vector v) {
		Swap(v);
		return *this;
	}

	void Swap(const Vector<T>& v) {
		swap(_start, v._start);
		swap(_finsh, v._finsh);
		swap(_eos, v._eos);
	}

private:
	T* _start;
	T* _finsh;
	T* _eos;
};


template <class T>
void VectorPrint(const Vector<T>& v) {
	for (int i = 0; i < v.size(); i++) {
		cout << v[i] << " ";
	}
	cout << endl;

	Vector<T>::iterator it = v.begin();
	while (it != v.end()) {
		cout << *it << " ";
		++it;
	}
	cout << endl;
}