#include <iostream>
#include <queue>
using namespace std;

template<class T,class Container = deque<T>>
class Stack {
public:
	//��ջ
	void push(const T& val) {
		_con.push_back(val);
	}
	//��ջ
	void pop() {
		_con.pop_back();
	}
	//��ȡջ��Ԫ��
	const T& top() {
		return _con.back();
	}
	size_t size() {
		return _con.size();
	}
	bool empty() {
		return _con.empty();
	}

private:
	Container _con;
};

void test() {
	Stack<int> sk;
	sk.push(1);
	sk.push(2);
	sk.pop();
	sk.push(3);
	sk.push(4);
	sk.pop();
	sk.push(5);

	cout << sk.top() << endl;
	cout << sk.size() << endl;
}

//int main() {
//	test();
//
//	return 0;
//}

