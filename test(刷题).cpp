#include <sstream>
#include <iostream>
#include <string>
using namespace std;

int main() {
	int a = 123456;
	string ans;
	stringstream s;
	s << a;
	s >> ans;
	//cout << ans << endl;
	const char* str = "-1234561556545155";
	int id = atoi(str);
	cout << id << endl;
	string str1 = "+1343";
	int sr = stoi(str1);
	cout << sr << endl;
	return 0;
}


int solve(int money, vector<pair<int, int> >& moneyCount) {
	int num = 0;
	for (int i = moneyCount.size() - 1; i >= 0; i--) {
		int c = min(money / moneyCount[i].first, moneyCount[i].second);
		money -= c * moneyCount[i].first;
		num += c;
	}
	if (money > 0) {
		num = -1;
	}
	return num;
}


class Solution {
public:
	bool canJump(vector<int>& nums) {
		int rightMost = 0;
		for (int i = 0; i < nums.size(); i++) {
			if (i <= rightMost) {
				rightMost = max(rightMost, i + nums[i]);
			}
			if (rightMost >= nums.size() - 1)
				return true;
		}
		return false;
	}
};
class Solution {
public:
	int maxProfit(vector<int>& prices) {
		int price = 0;
		for (int i = 1; i < prices.size(); i++) {
			if (prices[i] > prices[i - 1]) {
				price += prices[i] - prices[i - 1];
			}
		}
		return price;
	}
};

class Solution {
public:
	int balancedStringSplit(string s) {
		int cnt = 0;
		int balance = 0;
		for (int i = 0; i < s.size(); i++) {
			if (s[i] == 'R') {
				balance++;
			}
			else {
				balance--;
			}
			if (balance == 0)
				cnt++;
		}
		return cnt;
	}
};

void swap(int* arr, int left, int right) {
	int temp = arr[left];
	arr[left] = arr[right];
	arr[right] = temp;
}

void selectSort(int* arr, int n) {
	for (int i = 0; i < n - 1; i++) {
		int min = i;
		for (int j = i + 1; j < n; j++) {
			if (arr[j] < arr[min])
				min = j;
		}
		swap(arr, min, i);
	}
}

//方法一:递归实现
class Solution {
public:
	int Fibonacci(int n) {
		if (n == 0)
			return 0;
		if (n <= 2)
			return 1;
		return Fibonacci(n - 2) + Fibonacci(n - 1);
	}
};
//方法二:动态规划
class Solution {
public:
	int Fibonacci(int n) {
		//开数组
		int* dp = new int[n + 1];
		//初始化
		dp[0] = 0;
		dp[1] = 1;
		for (int i = 2; i <= n; i++) {
			//状态转移方程
			dp[i] = dp[i - 1] + dp[i - 2];
		}
		int ret = dp[n];
		delete[] dp;
		return ret;
	}
};
//方法三:迭代
class Solution {
public:
	int Fibonacci(int n) {
		int first = 0;
		int second = 1;
		int third = n;
		for (int i = 2; i <= n; i++) {
			third = first + second;
			first = second;
			second = third;
		}
		return third;
	}
};

class Solution {
public:
	bool wordBreak(string s, unordered_set<string> &dict) {
		if (s.length() == 0 || dict.size() == 0)
			return false;
		vector<bool> can_break(s.size() + 1, false);
		can_break[0] = true;
		for (int i = 1; i <= s.size(); i++) {
			for (int j = i; j >= 0; j--) {
				if (can_break[j] && dict.find(s.substr(j, i - j)) != dict.end()) {
					can_break[i] = true;
					break;
				}
			}
		}
		return can_break[s.size()];
	}
};