////�ж�һ�����������Ƿ�����ظ�Ԫ��
////(1).����set
//class Solution {
//public:
//	bool containsDuplicate(vector<int>& nums) {
//		if (nums.empty())
//			return false;
//		set<int> st;
//		for (auto e : nums) {
//			st.insert(e);
//		}
//		return nums.size() > st.size() ? true : false;
//	}
//};
////����map:
//class Solution {
//public:
//	bool containsDuplicate(vector<int>& nums) {
//		if (nums.empty())
//			return false;
//		map<int, int> mp;
//		for (auto e : nums) {
//			mp[e]++;
//		}
//		for (auto i : mp) {
//			if (i.second != 1)
//				return true;
//		}
//		return false;
//	}
//};
////�������� (����)
//class Solution {
//public:
//	bool containsDuplicate(vector<int>& nums) {
//		if (nums.empty())
//			return false;
//		sort(nums.begin(), nums.end());
//		for (int i = 1; i < nums.size(); i++) {
//			if (nums[i - 1] == nums[i])
//				return true;
//		}
//		return false;
//	}
//};
////�����ظ�Ԫ��
//class Solution {
//public:
//	bool containsNearbyDuplicate(vector<int>& nums, int k) {
//		if (nums.empty())
//			return false;
//		unordered_map<int, int> mp;
//		for (int i = 0; i < nums.size(); i++) {
//			if (mp.find(nums[i]) != mp.end()) {//������map�����ҵ�
//				int juli = abs(i - mp[nums[i]]);
//				if (juli <= k)
//					return true;
//				mp[nums[i]] = i;//����
//			}
//			else {
//				mp[nums[i]] = i;
//			}
//		}
//		return false;
//	}
//};

#include <iostream>
using namespace std;

int main() {
	cout << 0 % 4 << endl;
	return 0;
}
//�����ظ�Ԫ����
class Solution {
public:
	bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
		if (nums.empty() || t < 0)
			return false;
		long long mod = t + 1LL;
		unordered_map<long long, long long> buck;
		for (int i = 0; i < nums.size(); i++) {
			long long nth = nums[i] / mod;
			if (nums[i] < 0) //����
				nth--;
			if (buck.find(nth) != buck.end())
				return true;
			else if (buck.find(nth - 1) != buck.end() && abs(nums[i] - buck[nth - 1]) <= t)
				return true;
			else if (buck.find(nth + 1) != buck.end() && abs(nums[i] - buck[nth + 1]) <= t)
				return true;
			buck[nth] = nums[i];
			if (i >= k) {
				buck.erase(nums[i - k] / mod);
			}
		}
		return false;
	}
};
//������
class Solution {
public:
	int func(int n) {
		int sum = 0;
		while (n) {
			int tmp = n % 10;
			sum += tmp * tmp;
			n = n / 10;
		}
		return sum;
	}
	bool isHappy(int n) {
		int slow = n, fast = n;
		do {
			slow = func(slow);
			fast = func(fast);
			fast = func(fast);
		} while (slow != fast);
		return slow == 1;
	}
};