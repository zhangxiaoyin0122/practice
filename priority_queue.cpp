#include <iostream>
#include <queue>
#include <vector>
using namespace std;

template<class T>
struct Less {
	bool operator()(const T& vala, const T& valb) {
		return vala < valb;
	}
};

template<class T>
struct Greater {
	bool operator()(const T& vala, const T& valb) {
		return vala > valb;
	}
};

template<class T,class Container = deque<T>,class Compare = Less<T> >
class Priority_Queue {
public:
	void push(const T& val) {
		_con.push_back(val);
		ShiftUp(_con.size() - 1);
	}
	//删除堆顶元素
	void pop() {
		swap(_con[0], _con[_con.size() - 1]);
		_con.pop_back();
		ShiftDown(0);
	}

	size_t size()const {
		return _con.size();
	}

	const T& top()const {
		return _con.front();
	}
	//判空
	bool empty() {
		return _con.empty();
	}
private:
	//向下调整
	void ShiftDown(int parent) {
		int child = 2 * parent + 1;
		while (child < _con.size()) {
			if (child + 1 < _con.size() && _com( _con[child], _con[child + 1]) ) {
				child++;
			}
			if (_com(_con[parent], _con[child])) {
				swap(_con[child], _con[parent]);
				parent = child;
				child = 2 * parent + 1;
			}
			else {
				break;
			}
		}
	}
	//向上调整
	void ShiftUp(int child) {
		int parent = (child - 1) / 2;
		while (child > 0) {
			if (_com(_con[parent],_con[child])) {
				swap(_con[child], _con[parent]);
				child = parent;
				parent = (child - 1) / 2;
			}
			else
				break;
		}
	}
private:
	Container _con;
	Compare _com;
};

void test2() {
	Priority_Queue<int, vector<int>, Greater<int>> pq;
	pq.push(1);
	pq.push(2);
	pq.push(3);
	pq.push(4);
	pq.push(5);
	pq.push(6);
	pq.push(7);

	while (!pq.empty()) {
		cout << pq.top() << " ";
		pq.pop();
	}
	cout << endl;
}

int main() {
	test2();
	return 0;
}