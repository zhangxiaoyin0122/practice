#include <iostream>
using namespace std;

template<class T>
struct AVLNode {
	T _value;
	AVLNode<T>* _left;
	AVLNode<T>* _right;
	AVLNode<T>* _parent;
	int _bf; //平衡因子

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
	//搜索树的插入
	bool insert(const T& val) {
		//如果根为空
		if (_root == nullptr) {
			_root = new Node(val);
			return true;
		}
		//查找插入的位置
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
		//插入
		cur = new Node(val);
		if (parent->_value < val)
			parent->_right = cur;
		else
			parent->_left = cur;

		cur->_parent = parent;

		//更新＋调整
		while (parent) {
			//更新parent平衡因子
			if (parent->_left == cur)
				--parent->_bf;
			else
				++parent->_bf;

			//判断是否需要继续更新
			if (parent->_bf == 0)
				break;
			else if (parent->_bf == -1 || parent->_bf == 1) {
				cur = parent;
				parent = parent->_parent;
			}
			else if (parent->_bf == -2 || parent->_bf == 2) {
				//调整
				if (parent->_bf == -2 && cur->_bf == -1) {
					//左边的左边高,需要右旋
					RotateR(parent);
				}
				else if (parent->_bf == 2 && cur->_bf == 1) {
					//右边的右边高,需要左旋
					RotateL(parent);
				}
				else if (parent->_bf == 2 && cur->_bf == -1) {
					//右边的左边高,需要右旋＋左旋
					Node* subR = parent->_right;
					Node* subRL = subR->_left;
					int bf = subRL->_bf;
					//以cur为轴左旋
					RotateR(cur);
					//以parent为轴右旋
					RotateL(parent);

					//调整平衡因子
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
					//左边的右边高
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
	//右旋:
	void RotateR(Node* parent) {
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		subL->_right = parent;
		parent->_left = subLR;

		if (subLR) {
			subLR->_parent = parent;
		}
		//先连接subL的_parent
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
		//再连接parent的_parent
		parent->_parent = subL;
		parent->_bf = subL->_bf = 0;
	}
	//左旋:
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

		//左右子树高度差是否和平衡因子相等
		int subL = Height(root->_left);
		int subR = Height(root->_right);
		if (root->_bf != subR - subL)
		{
			cout << "节点：" << root->_value << "异常： bf: " << root->_bf << " 高度差：" << subR - subL << endl;
			return false;
		}
		//平衡因子的绝对值知否小于2
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

