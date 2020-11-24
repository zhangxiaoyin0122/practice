#include <iostream>
#include <string>
using namespace std;

int mian() {
	string str1, str2;
	getline(cin, str1);
	getline(cin, str2);
	string ans;
	for (int i = 0; i < str1.length(); i++) {
		if (str2.find(str1[i]) == string::npos) {
			ans += str1[i];
		}
	}
	cout << ans << endl;
	return 0;
}

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	vector<int> vec;
	int num;
	while (cin >> num) {
		vec.resize(num * 3);
		for (int i = 0; i < num * 3; i++) {
			cin >> vec[i];
		}
		sort(vec.begin(), vec.end());
		long result = 0;
		int j = num * 3 - 1;
		for (int i = 0; i < num; i++) {
			result += vec[j - 1];
			j -= 2;
		}
		cout << result << endl;
	}
	return 0;
}

vector<vector<int> > levelOrder(TreeNode* root) {
	vector<vector<int>> result;
	queue<TreeNode*> q;
	if (root)
		q.push(root);
	while (!q.empty()) {
		vector<int> tmp;
		int size = q.size();
		for (int i = 0; i < size; i++) {
			TreeNode* node = q.front();
			tmp.push_back(node->val);
			q.pop();
			if (node->left)
				q.push(node->left);
			if (node->right)
				q.push(node->right);
		}
		result.push_back(tmp);
	}
	return result;
}
};