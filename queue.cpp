#include <iostream>
#include <queue>
using namespace std;


template<class T,class Container = deque<T>>
class Queue {
public:
	void push(const T& val) {
		_con.push_back(val);
	}
	void pop() {
		_con.pop_front();
	}
	const T& front() {
		return _con.front();
	}
	size_t size()const {
		return _con.size();
	}
	bool empty() {
		return _con.empty();
	}


private:
	Container _con;
};

void test1() {
	Queue<int> q;
	q.push(1);
	q.push(2);
	q.pop();
	q.push(0);
	q.push(3);
	cout << q.size() << endl;
	q.push(4);
	cout << q.front() << endl;

}

//int main() {
//	test1();
//
//	return 0;
//}