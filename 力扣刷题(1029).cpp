////小青蛙跳台阶:
////①动态规划:
//class Solution {
//public:
//	int numWays(int n) {
//		if (n == 1 || n == 0)
//			return 1;
//		int* dp = new int[n + 1];
//		dp[0] = 1;
//		dp[1] = 1;
//		for (int i = 2; i <= n; i++) {
//			dp[i] = (dp[i - 1] + dp[i - 2]) % 1000000007;
//		}
//		int result = dp[n];
//		delete[] dp;
//		return result;
//	}
//};
////②.递归  超出时间限制
//class Solution {
//public:
//	int numWays(int n) {
//		if (n == 0 || n == 1)
//			return 1;
//		return (numWays(n - 1) + numWays(n - 2)) % 1000000007;
//	}
//};
////③.迭代:
//class Solution {
//public:
//	int numWays(int n) {
//		int first = 1;
//		int second = 1;
//		int third = 1;
//		for (int i = 2; i <= n; i++) {
//			third = (first + second) % 1000000007;
//			first = second;
//			second = third;
//		}
//		return third;
//	}
//};


#include <iostream>
using namespace std;

struct TreeNode {
	TreeNode* left;
	TreeNode* right;
	int val;
};
	void dfs(TreeNode* root, int& tmp, int& sum) {
		tmp = tmp * 10 + root->val;
		if (root->left == nullptr && root->right == nullptr) {
			sum += tmp;
			return;
		}
		if (root->left) {
			dfs(root->left, tmp, sum);
			tmp /= 10;
		}
		if (root->right) {
			dfs(root->right, tmp, sum);
			tmp /= 10;
		}
	}
	int sumNumbers(TreeNode* root) {
		if (root->left == nullptr && root->right == nullptr)
			return root->val;
		int sum = 0;
		if (root->left)
			dfs(root->left, root->val, sum);
		if (root->right)
			dfs(root->right, root->val, sum);
		return sum;
	}


//129.求根到叶子节点的和
	class Solution {
	public:
		void dfs(TreeNode* root, int& tmp, int& sum) {
			tmp = tmp * 10 + root->val;
			if (root->left == nullptr && root->right == nullptr) {
				sum += tmp;
				return;
			}
			if (root->left) {
				dfs(root->left, tmp, sum);
				tmp /= 10;
			}
			if (root->right) {
				dfs(root->right, tmp, sum);
				tmp /= 10;
			}
		}
		int sumNumbers(TreeNode* root) {
			if (root == nullptr)
				return 0;
			if (root->left == nullptr && root->right == nullptr)
				return root->val;
			int sum = 0;
			int tmp = root->val;
			if (root->left)
				dfs(root->left, tmp, sum);
			tmp = root->val;
			if (root->right)
				dfs(root->right, root->val, sum);
			return sum;
		}
	};

//快乐数:
	class Solution {
	public:
		int sum(int n) {
			int sum = 0;
			while (n) {
				sum += (n % 10)*(n % 10);
				n /= 10;
			}
			return sum;
		}
		bool isHappy(int n) {
			unordered_set<int> st;
			while (1) {
				int tmp = sum(n);
				if (tmp == 1)
					return true;
				if (st.find(tmp) != st.end()) {
					return false;
				}
				else {
					st.insert(tmp);
				}
				n = tmp;
			}
		}
	};

//53.最大子序列和
	class Solution {
	public:
		int maxSubArray(vector<int>& nums) {
			int maxCount = nums[0];
			int max = nums[0];
			for (int i = 1; i < nums.size(); i++) {
				if (max < 0) {
					max = nums[i];
				}
				else {
					max += nums[i];
				}
				maxCount = max > maxCount ? max : maxCount;
			}
			return maxCount;
		}
	};

//动态规划
	class Solution {
	public:
		int maxSubArray(vector<int>& nums) {
			int* dp = new int[nums.size() + 1];
			int Maxcount = nums[0];
			dp[0] = nums[0];
			for (int i = 1; i < nums.size(); i++) {
				dp[i] = max(dp[i - 1] + nums[i], nums[i]);
				Maxcount = max(dp[i], Maxcount);
			}
			return Maxcount;
		}
	};

//买卖股票的最佳时机:
	class Solution {
	public:
		int maxProfit(vector<int>& prices) {
			if (prices.size() < 1)
				return 0;
			int min = prices[0];
			int maxCount = 0;
			for (int i = 1; i < prices.size(); i++) {
				if (prices[i] < min)
					min = prices[i];
				if (prices[i] - min > maxCount)
					maxCount = prices[i] - min;
			}
			return maxCount;
		}
	};
//动态规划:
	class Solution {
	public:
		int maxProfit(vector<int>& prices) {
			if (prices.size() < 1)
				return 0;
			int* dp = new int[prices.size()];
			dp[0] = 0;
			int min = prices[0];
			int maxCount = 0;
			for (int i = 0; i < prices.size(); i++) {
				if (prices[i] < min) {
					min = prices[i];
					dp[i] = 0;
				}
				else
					dp[i] = prices[i] - min;
				maxCount = max(dp[i], maxCount);
			}
			return maxCount;
		}
	};

	//定义单调队列
	class monotonousQueue {
	public:
		//插入数据  
		void push(int val) {
			while (!date.empty() && date.back() < val)  //队列不为空&&队列最后一个元素小于要插入的值
				date.pop_back();
			date.push_back(val);
		}
		void pop(int val) {
			if (!date.empty() && date.front() == val)
				date.pop_front();
		}
		int max() {
			return date.front();  //返回队列首元素
		}
	private:
		deque<int> date;
	};

	class Solution {
	public:
		vector<int> maxSlidingWindow(vector<int>& nums, int k) {
			vector<int> result;
			if (nums.size() < 0 || k > nums.size())
				return result;
			monotonousQueue q;
			for (int i = 0; i < nums.size(); i++) {
				if (i < k - 1) {
					q.push(nums[i]);
				}
				else {
					q.push(nums[i]);
					int tmp = q.max();
					q.pop(nums[i - k + 1]);
					result.push_back(tmp);
				}
			}
			return result;
		}
	};

//剑指 Offer 57 - II.和为s的连续正数序列
	class Solution {
	public:
		vector<vector<int>> findContinuousSequence(int target) {
			vector<vector<int> > result;
			int i = 1;
			int j = 1;
			int sum = 0;
			while (i <= target / 2) {
				if (sum < target) {
					sum += j;
					j++;
				}
				else if (sum > target) {
					sum -= i;
					i++;
				}
				else { //sum == target
					vector<int> tmp;
					for (int k = i; k < j; k++) {
						tmp.push_back(k);
					}
					result.push_back(tmp);
					sum -= i;
					i++;
				}
			}
			return result;
		}
	};