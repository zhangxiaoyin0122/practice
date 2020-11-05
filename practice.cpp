#include <iostream>
using namespace std;

template<class T>
struct BSTNode {
	T _val;
	BSTNode<T>* _right;
	BSTNode<T>* _left;

	BSTNode(T val)
		:_val(val)
		, _right(nullptr)
		, _left(nullptr)
	{}
};

template<class T>
class BSTree {
public:
	typedef BSTNode<T> Node;
	Node* find(const T& val) {
		Node* cur = _root;
		while (cur) {
			if (cur->_val == val)
				return cur;
			else if (cur->_val < val) {
				cur = cur->_right;
			}
			else
				cur = cur->_left;
		}
		return nullptr;
	}

	bool insert(const T& val) {
		if (_root == nullptr) {
			_root = new Node(val);
			return true;
		}
		Node* cur = _root;
		Node* parent = nullptr;
		while (cur) {
			parent = cur;
			if (cur->_val == val)
				return false;
			else if (cur->_val < val) {
				cur = cur->_right;
			}
			else {
				cur = cur->_left;
			}
		}
		//����
		cur = new Node(10);
		if (parent->_val < val) {
			parent->_right = cur;
		}
		else {
			parent->_left = cur;
		}
		return true;
	}

	bool erase(const T& val) {
		//����
		Node* cur = _root;
		Node* parent = nullptr;
		while (cur) {
			if (cur->_val == val)
				break;
			else if (cur->_val < val) {
				parent = cur;
				cur = cur->_right;
			}
			else {
				parent = cur;
				cur = cur->_left;
			}
		}
		//�ж��Ƿ��ҵ�
		if (cur == nullptr)
			return false;
		//ɾ��:
		//(1)Ҷ�ӽ��:
		if (cur->_right == nullptr && cur->_left == nullptr) {
			if (cur == _root) {
				_root = nullptr;
			}
			else {
				if (parent->_left == cur) {
					parent->_left = nullptr;
				}
				else {
					parent->_right = nullptr;
				}
			}
			delete cur;
		}
		//��Ϊ1�Ľ��,����Ϊ��
		else if (cur->_left == nullptr) {
			if (cur == _root) {
				_root = cur->_right;
			}
			else {
				if (parent->_left == cur) {
					parent->_left = cur->_right;
				}
				else
					parent->_right = cur->_right;
			}
			delete cur;
		}
		//��Ϊ1�Ľ��,�Һ���Ϊ��
		else if (cur->_right == nullptr) {
			if (cur == _root) {
				_root = cur->_left;
			}
			else {
				if (parent->_left == cur) {
					parent->_left = cur->_left;
				}
				else
					parent->_right = cur->_left;
			}
			delete cur;
		}
		//��Ϊ2�Ľ��
		else {
			Node* leftMostChild = cur->_right;
			Node* parent = cur;
			//����������������
			while (leftMostChild->_left) {
				parent = leftMostChild;
				leftMostChild = leftMostChild->_left;
			}
			//
			cur->_val = leftMostChild->_val;
			//ɾ��������������
			if (parent->_right == leftMostChild)
				parent->_right = leftMostChild->_right;
			else
				parent->_left = leftMostChild->_right;
			delete leftMostChild;
		}
		return true;
	}
	void inorder() {
		_inorder(_root);
		cout << endl;
	}
	void _inorder(Node* root) {
		if (root) {
			_inder(root->_left);
			cout << root->_val << " ";
			_inorder(root->_right);
		}
	}
	void destory(Node* root) {
		if (root) {
			destory(root->_left);
			destory(root->_right);
			delete root;
		}
	}
	~BSTree() {
		destory(_root);
	}

	void copyTree(Node* root) {
		if (root) {
			insert(root->_val);
			copyTree(root->_left);
			copyTree(root->_right);
		}
	}
	Node* copyTree2(Node* root) {
		if (root) {
			Node* cur = new Node(root->_val);
			cur->_left = copyTree2(root->_left);
			cur->_right = copyTree2(root->_right);
			return cur;
		}
		return nullptr;
	}
	//���캯��
	BSTree()
		:_root(nullptr)
	{}
	//��������
	BSTree(const BSTree<T>& bst)
		:_root(nullptr)
	{
		_root = copyTree2(_root);
	}
	//��ֵ�����:�ִ�д��
	BSTree& operator=(BSTree<T> bst) {
		swap(_root, bst._root);
		return *this;
	}
	BSTree& operator=(const BSTree<T>& bst) {
		if (this != &bst) {
			destory(_root);
			_root = copyTree2(bst._root);
		}
		return *this;
	}

private:
	Node* _root;
};