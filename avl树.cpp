#include <iostream>
using namespace std;

template<class T>
struct AVLNode {
	T _value;
	AVLNode<T>* _left;
	AVLNode<T>* _right;
	AVLNode<T>* _parent;
	int _bf; //ƽ������

	AVLNode(const T& val = T())
		:_value(val)
		, _left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _bf(0)
	{}
};

template<class T>
class AVLTree {
public:
	typedef AVLNode<T> Node;
	AVLTree()
		:_root(nullptr)
	{}
	//�������Ĳ���
	bool insert(const T& val) {
		//�����Ϊ��
		if (_root == nullptr) {
			_root = new Node(val);
			return true;
		}
		//���Ҳ����λ��
		Node* cur = _root;
		Node* parent = nullptr;
		while (cur) {
			parent = cur;
			if (cur->_value == val)
				return false;
			else if (cur->_value < val)
				cur = cur->_left;
			else
				cur = cur->_right;
		}
		//����
		cur = new Node(val);
		if (parent->_value < val)
			parent->_right = cur;
		else
			parent->_left = cur;

		cur->_parent = parent;

		//���£�����
		while (parent) {
			//����parentƽ������
			if (parent->_left == cur)
				--parent->_bf;
			else
				++parent->_bf;

			//�ж��Ƿ���Ҫ��������
			if (parent->_bf == 0)
				break;
			else if (parent->_bf == -1 || parent->_bf == 1) {
				cur = parent;
				parent = parent->_parent;
			}
			else if (parent->_bf == -2 || parent->_bf == 2) {
				//����
				if (parent->_bf == -2 && cur->_bf == -1) {
					//��ߵ���߸�,��Ҫ����
					RotateR(parent);
				}
				else if (parent->_bf == 2 && cur->_bf == 1) {
					//�ұߵ��ұ߸�,��Ҫ����
					RotateL(parent);
				}
				else if (parent->_bf == 2 && cur->_bf == -1) {
					//�ұߵ���߸�,��Ҫ����������
					Node* subR = parent->_right;
					Node* subRL = subR->_left;
					int bf = subRL->_bf;
					//��curΪ������
					RotateR(cur);
					//��parentΪ������
					RotateL(parent);

					//����ƽ������
					if (bf == 1) {
						subR->_bf = 0;
						parent->_bf = -1;
					}
					else if (bf == -1) {
						subR->_bf = 1;
						parent->_bf = 0;
					}
				}
				else if (parent->_bf == -2 && cur->_bf == 1) {
					//��ߵ��ұ߸�
					Node* subL = parent->_left;
					Node* subLR = subL->_right;
					int bf = subLR->_bf;

					RotateL(cur);
					RotateR(parent);

					if (bf == 1) {
						parent->_bf = 0;
						subL->_bf = -1;
					}
					else if (bf == -1) {
						parent->_bf = 1;
						subL->_bf = 0;
					}
				}
				break;
			}
		}
		return true;
	}
	//����:
	void RotateR(Node* parent) {
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		subL->_right = parent;
		parent->_left = subLR;

		if (subLR) {
			subLR->_parent = parent;
		}
		//������subL��_parent
		if (parent == _root) {
			_root = subL;
			subL->_parent = nullptr;
		}
		else {
			Node* g = parent->_parent;
			subL->_parent = g;
			if (g->_left == parent)
				g->_left = subL;
			else
				g->_right = subL;
		}
		//������parent��_parent
		parent->_parent = subL;
		parent->_bf = subL->_bf = 0;
	}
	//����:
	void RotateL(Node* parent) {
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		subR->_left = parent;
		parent->_right = subRL;

		if (subRL)
			subRL->_parent = parent;

		if (parent == _root) {
			_root = subR;
			subR->_parent = nullptr;
		}
		else {
			Node* g = parent->_parent;
			subR->_parent = g;
			if (g->_left == parent)
				g->_left = subR;
			else
				g->_right = subR;
		}
		parent->_parent = subR;
		parent->_bf = subR->_bf = 0;
	}


	void inorder() {
		_inorder(_root);
		cout << endl;
	}
	void _inorder(Node* root) {
		if (root) {
			_inorder(root->_left);
			cout << root->_value << " ";
			_inorder(root->_right);
		}
	}

	bool isBalance()
	{
		return _isBalance(_root);
	}

	bool _isBalance(Node* root)
	{
		if (root == nullptr)
			return true;

		//���������߶Ȳ��Ƿ��ƽ���������
		int subL = Height(root->_left);
		int subR = Height(root->_right);
		if (root->_bf != subR - subL)
		{
			cout << "�ڵ㣺" << root->_value << "�쳣�� bf: " << root->_bf << " �߶Ȳ" << subR - subL << endl;
			return false;
		}
		//ƽ�����ӵľ���ֵ֪��С��2
		return abs(root->_bf) < 2
			&& _isBalance(root->_left)
			&& _isBalance(root->_right);
	}

	int Height(Node* root)
	{
		if (root == nullptr)
			return 0;
		int left = Height(root->_left);
		int right = Height(root->_right);
		return left > right ? left + 1 : right + 1;
	}
private:
	Node* _root;
};

