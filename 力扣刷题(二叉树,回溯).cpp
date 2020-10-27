//257.������������·��:
class Solution {
public:
	void dfs(TreeNode* root, vector<string>& result, vector<int>& vec) {
		vec.push_back(root->val);
		if (root->left == nullptr && root->right == nullptr) { //������
			string path;
			for (int i = 0; i < vec.size() - 1; i++) {
				path += to_string(vec[i]);
				path += "->";
			}
			path += to_string(vec[vec.size() - 1]);
			result.push_back(path);
			return;
		}
		if (root->left) {
			dfs(root->left, result, vec);
			vec.pop_back();
		}
		if (root->right) {
			dfs(root->right, result, vec);
			vec.pop_back();
		}
	}
	vector<string> binaryTreePaths(TreeNode* root) {
		vector<string> result; //������
		if (root == nullptr)
			return result;
		vector<int> vec;
		dfs(root, result, vec);
		return result;
	}
};

//77.���
class Solution {
public:
	vector<vector<int> > result; //������
	vector<int> path;
	void backtracking(int n, int k, int start) {
		//��ֹ����
		if (path.size() == k) {
			result.push_back(path);
			return;
		}
		for (int i = start; i <= n; i++) {
			path.push_back(i); //����ڵ�
			backtracking(n, k, i + 1); //�ݹ�
			path.pop_back(); //����
		}
	}
	vector<vector<int>> combine(int n, int k) {
		backtracking(n, k, 1);
		return result;
	}
};

//111.����������С���

class Solution {
public:
	int minDepth(TreeNode* root) {
		if (root == nullptr)
			return 0;
		//��ֹ����
		if (root->left == nullptr && root->right != nullptr) {
			return 1 + minDepth(root->right);
		}
		if (root->right == nullptr && root->left != nullptr) {
			return 1 + minDepth(root->left);
		}
		return min(minDepth(root->left), minDepth(root->right)) + 1;
	}
};

222.�������ڵ����
�ݹ�:
class Solution {
public:
	int countNodes(TreeNode* root) {
		//��ֹ����
		if (root == nullptr)
			return 0;
		int left = countNodes(root->left);
		int right = countNodes(root->right);
		return left + right + 1;
	}
};
����:
class Solution {
public:
	int countNodes(TreeNode* root) {
		queue<TreeNode*> q;
		if (root != nullptr)
			q.push(root);
		int count = 0;
		while (!q.empty()) {
			int size = q.size();
			count += size;
			for (int i = 0; i < size; i++) {
				TreeNode* node = q.front();
				q.pop();
				if (node->left) q.push(node->left);
				if (node->right) q.push(node->right);
			}
		}
		return count;
	}
};

//110:ƽ�������
class Solution {
public:
	int getPath(TreeNode* root) {
		if (root == nullptr)
			return 0;
		int left = getPath(root->left);
		if (left == -1) return -1;
		int right = getPath(root->right);
		if (right == -1) return -1;
		return abs(left - right) > 1 ? -1 : 1 + max(left, right);
	}
	bool isBalanced(TreeNode* root) {
		if (root == nullptr)
			return true;
		if (getPath(root) != -1) {
			return true;
		}
		return false;
	}
};

//112:·���ܺ�
class Solution {
public:
	bool hasPathSum(TreeNode* root, int sum) {
		if (root == nullptr)
			return false;
		if (!root->left && !root->right && root->val == sum)
			return true;
		return hasPathSum(root->left, sum - root->val) || hasPathSum(root->right, sum - root->val);
	}
};