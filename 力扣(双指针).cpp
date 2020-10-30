//贪心方法:
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

//动态规划:
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
//力扣 - 121.买卖股票的最佳时机

题目链接 : https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock/ 

//贪心算法:
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
//力扣 - 3.无重复的最长子串

class Solution {
public:
	int lengthOfLongestSubstring(string s) {
		//滑动窗口
		unordered_set<char> st;
		int n = s.size();
		int rk = -1;
		int result = 0;
		for (int i = 0; i < n; i++) {
			if (i != 0) {   //滑动窗口的巧妙之处,也是相后滑动的体现
				st.erase(s[i - 1]);
			}
			while (rk + 1 < n && !st.count(s[rk + 1])) {
				st.insert(s[rk + 1]);
				++rk;
			}
			result = max(result, rk - i + 1);
		}
		return result;
	}
};
力扣 - 239.滑动窗口的最大值

题目链接 : https://leetcode-cn.com/problems/sliding-window-maximum/

//利用双端队列实现单调队列
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
//力扣 - 剑指offer 57 - II.和为s的连续正数序列
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