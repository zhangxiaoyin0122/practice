class Solution {
public:
	TreeNode* insertIntoBST(TreeNode* root, int val) {
		if (root == nullptr) {
			TreeNode* node = new TreeNode(val);
			return node;
		}
		if (root->val < val) {
			root->right = insertIntoBST(root->right, val);
		}
		if (root->val > val) {
			root->left = insertIntoBST(root->left, val);
		}
		return root;
	}
};

class Solution {
public:
	vector<vector<int>> levelOrder(TreeNode* root) {
		vector<vector<int >> result;
		if (root == nullptr)
			return result;

		deque<TreeNode*> d;
		d.push_back(root);
		int flags = 1; //标志
		while (!d.empty()) {
			if (flags == 1) {
				int sz = d.size();
				vector<int> tmp;
				for (int i = 0; i < sz; i++) {
					TreeNode* node = d.front();
					d.pop_front();
					tmp.push_back(node->val);
					if (node->left) d.push_back(node->left);
					if (node->right) d.push_back(node->right);
				}
				result.push_back(tmp);
				flags = 0;
			}
			else if (flags == 0) {
				int sz = d.size();
				vector<int> tmp;
				for (int i = 0; i < sz; i++) {
					TreeNode* node = d.back();
					d.pop_back();
					tmp.push_back(node->val);
					if (node->right) d.push_front(node->right);
					if (node->left) d.push_front(node->left);
				}
				result.push_back(tmp);
				flags = 1;
			}
		}
		return result;
	}
};

class Solution {
private:
	int maxCount;
	int count;
	vector<int> result;
	TreeNode* pre;
	void searchBST(TreeNode* root) {
		if (root == nullptr)
			return;
		searchBST(root->left);
		//操作
		if (pre == nullptr) { //第一个节点
			count = 1;
		}
		else if (pre->val == root->val) {
			count++;
		}
		else {
			count = 1;
		}
		pre = root;
		if (count == maxCount) {
			result.push_back(pre->val);
		}
		if (count > maxCount) {
			maxCount = count;
			result.clear();
			result.push_back(pre->val);
		}
		searchBST(root->right);
		return;
	}
public:
	vector<int> findMode(TreeNode* root) {
		maxCount = 0;
		count = 0;
		result.clear();
		searchBST(root);
		return result;
	}
};