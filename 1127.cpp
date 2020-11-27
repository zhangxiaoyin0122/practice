//每日三道OJ题:1127
//第一道
#include <iostream>
#include <string>
using namespace std;

int main() {
	int M, N;
	cin >> M >> N;
	string num = "0123456789ABCDEF";
	if (M == 0) {
		cout << "0" << endl;
	}
	string ans;
	while (M) {
		if (M < 0) { //一定考虑到负数
			M = -M;
			cout << "-";
		}
		ans = num[M%N] + ans; //每次计算出的放在低位
		M /= N;
	}
	cout << ans << endl;
	return 0;
}
//第二道:
#include <iostream>
#include <vector>
using namespace std;

int main() {
	vector<int> vec;
	vec.resize(4);
	for (int i = 0; i < 4; i++) {
		cin >> vec[i];
	}
	//由所给条件,计算A,B,C的值
	int A = (vec[0] + vec[2]) / 2;
	int B = (vec[1] + vec[3]) / 2;
	int C = (vec[3] - vec[1]) / 2;
	//通过计算的值,判断是否满足已给条件
	if (A - B == vec[0] && B - C == vec[1] && A + B == vec[2] && B + C == vec[3]) {
		//注意输出格式
		cout << A << " " << B << " " << C << endl;
	}
	else {
		cout << "No" << endl;
	}
	return 0;
}

//第3道:
class Solution {
public:
	vector<vector<int>> result;
	vector<int> path;
	void trackbacking(TreeNode* root, int& expectNumber, int& sum) {
		path.push_back(root->val);
		sum += root->val;
		if (root->left == nullptr && root->right == nullptr && expectNumber == sum) {
			result.push_back(path);
			return;
		}
		if (root->left) {
			trackbacking(root->left, expectNumber, sum);
			path.pop_back();
			sum -= root->left->val;
		}
		if (root->right) {
			trackbacking(root->right, expectNumber, sum);
			path.pop_back();
			sum -= root->right->val;
		}
	}
	vector<vector<int> > FindPath(TreeNode* root, int expectNumber) {
		if (root == nullptr)
			return result;
		result.clear();
		path.clear();
		int sum = 0;
		trackbacking(root, expectNumber, sum);
		return result;
	}
};