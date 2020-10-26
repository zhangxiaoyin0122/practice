//前序遍历:
//递归:
class Solution {
public:
	void traversal(TreeNode* root, vector<int>& result) {
		if (!root)
			return;
		result.push_back(root->val);
		traversal(root->left, result);
		traversal(root->right, result);
	}
	vector<int> preorderTraversal(TreeNode* root) {
		vector<int> result;
		traversal(root, result);
		return result;
	}
};
//迭代法:
class Solution {
public:
	//迭代统一的风格写法
	vector<int> preorderTraversal(TreeNode* root) {
		vector<int> result;
		if (!root)
			return result;
		stack<TreeNode*> st;
		st.push(root);
		while (!st.empty()) {
			TreeNode* node = st.top();
			if (node) {
				st.pop();
				if (node->right) st.push(node->right);
				if (node->left) st.push(node->left);
				st.push(node);
				st.push(nullptr);
			}
			else {
				st.pop();
				node = st.top();
				st.pop();
				result.push_back(node->val);
			}
		}
		return result;
	}
};

中序遍历:

class Solution {
public:
	void traversal(TreeNode* root, vector<int>& result) {
		if (root == nullptr)
			return;
		traversal(root->left, result);
		result.push_back(root->val);
		traversal(root->right, result);
	}
	vector<int> inorderTraversal(TreeNode* root) {
		vector<int> result;
		traversal(root, result);
		return result;
	}
};


//迭代:
class Solution {
public:
	vector<int> inorderTraversal(TreeNode* root) {
		stack<TreeNode*> st;
		vector<int> result;
		TreeNode* cur = root;
		while (!st.empty() || cur) {
			if (cur != nullptr) {
				st.push(cur);
				cur = cur->left;
			}
			else {
				cur = st.top();
				st.pop();
				result.push_back(cur->val);
				cur = cur->right;
			}
		}
		return result;
	}
};

//后序遍历
class Solution {
public:
	void traversal(TreeNode* root, vector<int>& result) {
		if (root == nullptr)
			return;
		traversal(root->left, result);
		traversal(root->right, result);
		result.push_back(root->val);
	}
	vector<int> postorderTraversal(TreeNode* root) {
		vector<int> result;
		traversal(root, result);
		return result;
	}
};
//迭代:
class Solution {
public:
	vector<int> postorderTraversal(TreeNode* root) {
		vector<int> result;
		stack<TreeNode*> st;
		st.push(root);
		while (!st.empty()) {
			TreeNode* node = st.top();
			st.pop();
			if (node != nullptr)
				result.push_back(node->val);
			else
				continue;
			st.push(root->left);
			st.push(root->right);
		}
		reverse(result.begin(), result.end());
		return result;
	}
};

//二叉树的最大深度:
class Solution {
public:
	int maxDepth(TreeNode* root) {
		if (root == nullptr)
			return 0;
		return max(maxDepth(root->left), maxDepth(root->right)) + 1;
	}
};

class Solution {
public:
	int maxDepth(TreeNode* root) {
		if (root == nullptr)
			return 0;
		int leftDepth = maxDepth(root->left);
		int rightDepth = maxDepth(root->right);
		return max(leftDepth, rightDepth) + 1;
	}
};