#include <iostream>
#include <string>
using namespace std;

template <class T>
struct ListNode {
	T _val;
	ListNode* _next;
	ListNode* _prev;
	ListNode(const T& val = T())
		:_val(val),
		_next(nullptr),
		_prev(nullptr)
	{}
};

template<class T,class Ref,class Ptr>
struct ListIterator {
	typedef ListNode<T> Node;
	typedef ListIterator<T, Ref, Ptr> Self;
	//构造函数
	ListIterator(Node* node)
		:_node(node)
	{}

	//解引用
	Ref operator*() {
		return _node->_val;
	}
	//
	Ptr operator->() {
		return &_node->_next;
	}
	Self& operator++() {
		_node = _node->_next;
		return *this;
	}
	Self& operator--() {
		_node = _node->_prev;
		return *this;
	}
	bool operator!=(const Self& s) {
		return _node != s->_node;
	}
private:
	Node* _node;
};

template <class T>
class List {


private:
public:
	typedef ListNode<T> Node;
	typedef ListIterator<T, T&, T*> iterator;
	typedef ListIterator<T, const T&, const T*> const_iterator;

	iterator begin() {
		return iterator(_header->_next)
	}
	iterator end() {
		return iterator(_header);
	}
	const_iterator begin()const {
		return const_iterator(_header->_next);
	}
	const_iterator end()const {
		return const_iterator(_header);
	}

	//构造函数
	List()
		:_header(nullptr)
	{
		_header->_next = _header->_prev = _header;
	}
	//尾插
	void PushBack(const T& val) {
		Node* node = new Node(val);
		Node* last = _header->_prev;
		last->_next = node;
		node->_prev = last;
		node->_next = _header;
		_header->_next = node;
	}
	//头插
	void PushFront(const T& val) {
		//Node* node = new Node(val);
		insert(begin(), val);
	}
	//任意位置的插入
	void insert(iterator pos, const T& val) {
		//创造节点
		Node* node = new Node(val);
		Node* cur = pos._node;
		Node* prev = cur->_prev;
		prev->_next = node;
		node->_prev = prev;
		node->_next = cur;
		cur->_prev = node;
	}

	iterator erase(iterator pos) {
		if (pos != end()) {
			Node* cur = pos._node;
			Node* prev = cur->_prev;
			Node* next = cur->_next;
			dlete cur;
			prev->_next = next;
			next->_prev = prev;
			return iterator(next);
		}
		return pos;
	}

	size_t size()const {
		size_t count = 0;
		for (auto& e : *this)
			count++;
		return count;
	}

	~List() {
		if (_header) {
			clear();
			delete _header;
			_header = nullptr;
		}
	}

	void clear() {
		Node* cur = _header->_next;
		while (cur != _header) {
			Node* next = cur->_next;
			delete cur;
			cur = next;
		}
		//重建循环结构
		_header->_next = _header->_prev = _header;
	}

	List(const List<T>& l)
		:_header(new Node)
	{
		_header->_next = _header->_prev = _header;
		//深拷贝
		for (const auto& e : l) {
			pushBack(e);
		}
	}

	List<T> operator=(List<T> l) {
		swap(_header, l->_header);
		return *this;
	}
private:
	Node* _header;
};

template<class T>
void PrintListFor(const List<T>& l) {
	for (const auto& e : l) {
		cout << e << " ";
	}
	cout << endl;
}










