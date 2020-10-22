class Solution {
public:
	vector<int> twoSum(vector<int>& nums, int target) {
		vector<int> result;
		unordered_map<int, int> mp;
		for (int i = 0; i < nums.size(); i++) {
			if (mp.find(target - nums[i]) != mp.end()) { //找到
				result.push_back(mp[target - nums[i]]);
				result.push_back(i);
			}
			mp[nums[i]] = i;
		}
		return result;
	}
};

class Solution {
public:
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		ListNode* head = nullptr;
		ListNode* tail = nullptr;
		int carry = 0;
		while (l1 || l2) {
			int n1 = l1 ? l1->val : 0;
			int n2 = l2 ? l2->val : 0;
			int sum = n1 + n2 + carry;
			if (!head) {
				head = tail = new ListNode(sum % 10);
			}
			else {
				tail->next = new ListNode(sum % 10);
				tail = tail->next;
			}
			carry = sum / 10;
			if (l1) {
				l1 = l1->next;
			}
			if (l2) {
				l2 = l2->next;
			}

		}
		if (carry > 0) {
			tail->next = new ListNode(carry);
		}
		return head;
	}
};


//快速排序:

void quickSort(int* array, int begin, int end) {

}

class CQueue {
public:
	CQueue() { //清空队列
		while (!s1.empty()) {
			s1.pop();
		}
		while (!s2.empty()) {
			s2.pop();
		}
	}

	void appendTail(int value) { //尾插
		s1.push(value);
	}

	int deleteHead() { //头删
		if (s2.empty()) {
			while (!s1.empty()) {
				int tmp = s1.top();
				s1.pop();
				s2.push(tmp);
			}
		}
		if (s2.empty()) {
			return -1;
		}
		else {
			int result = s2.top();
			s2.pop();
			return result;
		}
	}
private:
	stack<int> s1;
	stack<int> s2;
};

class Solution {
public:
	int lengthOfLongestSubstring(string s) {
		//使用滑动窗口做
		unordered_set<char> st; //记录不重复的子串
		int result = 0;
		int rk = -1;
		for (int i = 0; i < s.length(); i++) {
			if (i != 0) { //窗口滑动的条件
				st.erase(s[i - 1]);
			}
			while (rk + 1 < s.length() && !st.count(s[rk + 1])) {
				st.insert(s[rk + 1]);
				++rk;
			}
			result = max(result, rk - i + 1);
		}
		return result;
	}
};

class Solution {
public:
	string longestPalindrome(string s) {
		//动态规划
		int n = s.size();
		vector<vector<int> > dp(n, vector<int>(n)); //定义二维数组存储是否是回文串
		string ans;
		for (int l = 0; l < n; l++) {
			for (int i = 0; i + l < n; i++) {
				int j = i + l;
				if (l == 0) {
					dp[i][j] = 1;
				}
				else if (l == 1) {
					dp[i][j] = s[i] == s[j];
				}
				else {
					if (dp[i + 1][j - 1] && s[i] == s[j]) {
						dp[i][j] = 1;
					}
					else {
						dp[i][j] = 0;
					}
				}
				if (dp[i][j] && l + 1 > ans.size()) {
					ans = s.substr(i, l + 1);
				}
			}
		}
		return ans;
	}
};



class Solution {
public:
	vector<int> twoSum(vector<int>& nums, int target) {
		vector<int> ans;
		unordered_set<int> st;
		for (int i = 0; i < nums.size(); ++i) {
			if (st.count(target - nums[i])) {
				ans.push_back(target - nums[i]);
				ans.push_back(nums[i]);
				break;
			}
			st.insert(nums[i]);
		}
		return ans;
	}
};

class Solution {
public:
	vector<int> ans;
	void inorder(TreeNode* root, vector<int>& ans) {
		if (!root) return;
		inorder(root->left, ans);
		ans.push_back(root->val);
		inorder(root->right, ans);
	}
	int kthLargest(TreeNode* root, int k) {
		inorder(root, ans);
		return ans[ans.size() - k];
	}
};