#include <iostream>
using namespace std;

template<class T>
class Vector {
	//构造函数
	Vector()
		:_start(nullptr)
		, _finsh(nullptr)
		, _eos(nullptr)
	{}
	//元素个数
	size_t size()const {
		return _finsh - _start;
	}
	//vector的容量
	size_t capacity()const {
		return _eos - _start;
	}
	//尾插
	void pushBack(const T& val) {
		if (_finsh == _eos) {
			//需要增容
			size_t newC = capacity() == 0 ? 1 : 2 * capacity();
			reserve(newC);
		}
		*_finsh = val;
		++_finsh;
	}

	void reserve(size_t n) {
		if (n > capacity()) {
			size_t oldsize = size();
			//开空间
			T* tmp = new T[n];
			//拷贝内容
			for (int i = 0; i < size(); i++) {
				tmp[i] = _start[i];
			}
			delete[] _start;
			//更新指针
			_start = tmp;
			_finsh = _start + oldsize;
			_eos = _start + n;
		}
	}
	//重载[]运算符
	T& operator[](size_t pos) {
		if (pos < size())
			return _start[pos];
	}
	const T& operator[](size_t pos)const {
		if (pos < size()) {
			return _start[pos];
		}
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

	void resize(size_t n, const T& val = T()) {
		if (n > capacity()) {
			reserve(n);
		}
		if (n > size()) {
			while (_finsh != _start + n) {
				*finsh++ = val;
			}
		}
		_finsh = _start + n;
	}
	void insert(iterator pos, const T& val) {
		if (pos >= _start && pos <= _finsh) {
			size_t len = size();
			//检查容量
			if (_finsh == _eos) {
				size_t newC = capacity() == 0 ? 1 : 2 * capacity();
				reserve(newC);
				pos = _start + len;
			}
			iterator end = _finsh;
			while (end > pos) {
				*end = *(end - 1);
				--end;
			}
			*pos = val;
			++finsh;
		}
	}
}	//删除操作
iterator erase(iterator pos) {
	//先判断删除位置是否有效
	if (pos >= _start && pos < _finsh) {
		//移动元素
		iterator begin = pos + 1;
		while (begin < _finsh) {
			*(begin - 1) = *begin;
			++begin;
		}
		//更新_size
		--_finsh;
		return pos;//此时pos是删除位置的下一位
	}
}
//析构函数
~Vector() {
	if (_start) {
		delete[]_start;
		_start = _finish = _eos = nullptr;
	}
}

Vector(const Vector& v)
	:_start(new T[v.capacity()]);
{
	//深拷贝
	for (auto& e : v) {
		_start[i] = v[i];
	}
	_finish = _start + v.size();
	_eos = _start + v.capacity();
}

Vector<T>& operator=(const Vector v) {
	Swap(v);
	return *this;
}
void Swap(const Vector<T>& v) {
	swap(_start, v._start);
	swap(_finish, v._finish);
	swap(_eos, v._eos);
}

private:
	T* _start;
	T* _finsh;
	T* _eos;
};