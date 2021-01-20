//最长公共字符串
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	string str1, str2;
	while (cin >> str1 >> str2) {
			if (str1.size() > str2.size()) {
			swap(str1, str2); //字符串长度小的置于str1
		}
		int len1 = str1.size(), len2 = str2.size();
		int start = 0, max = 0;//起始位置

		//使用动归的方法做
		//开辟二维数组的空间
		vector<vector<int> > map(len1 + 1, vector<int>(len2 + 1, 0));
		for (int i = 1; i <= len1; i++) {
			for (int j = 1; j <= len2; j++) {
				if (str1[i - 1] == str2[j - 1]) {
					map[i][j] = map[i - 1][j - 1] + 1;
				}
				//如果有更长的公共子串,更新长度
				if (map[i][j] > max) {
					max = map[i][j];
					start = i - max;
				}
			}
			cout << str1.substr(start, max) << endl;
		}
	}
	return 0;
}

//空瓶换饮料喝
#include <iostream>
using namespace std;

int GetNum(int num) {
	int sum = 0;
	while (num > 1) {
		sum = num / 3;
		num = sum + sum % 3;
		if (num == 2) {
			sum++;
			break;
		}
	}
	return sum;
}

int main() {
	int num;
	while (cin >> num) {
		cout << GetNum(num) << endl;
	}
	return 0;
}

////统计每个月兔子的总数
#include <iostream>
using namespace std;
//第一个月:1
//第二个月:1
//第三个月:2
//第四个月:3
//第五个月:5
//第六个月:8
int main() {
	int month; //输入型参数:月份
	while (cin >> month) {
		int first = 1;
		int second = 1;
		int result = 1;
		for (int i = 3; i <= month; i++) {
			result = first + second;
			first = second;
			second = result;
		}
		cout << result << endl;
	}
	return 0;
}


//杨辉三角的变形
#include <iostream>
#include <vector>
using namespace std;

int main() {
	int n, m;
	while (cin >> n) {
		m = 2 * n - 1;
		vector<vector<int>> map(n, vector<int>(m, 0));
		map[0][0] = 1;
		for (int i = 1; i < n; i++) {
			map[i][0] = map[i][2 * i] = 1;
			for (int j = 1; j < 2 * i; j++) {
				if (j == 1) { //第二列
					map[i][j] = map[i - 1][j] + map[i - 1][j - 1];
				}
				else { //其它列
					map[i][j] = map[i - 1][j] + map[i - 1][j - 1] + map[i - 1][j - 2];
				}
			}
		}
		int result = 0;
		for (int k = 0; k < m; k++) {
			if (map[n - 1][k] % 2 == 0) {
				result = k + 1;
				break;
			}
		}
		cout << result << endl;
	}
	return 0;
}



//超长正整数想加
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

string addStrings(string str1, string str2) {
	//由低位向高位想加
	int i = str1.size() - 1;
	int j = str2.size() - 1;
	string result = "";
	int carry = 0;//进位
	while (i >= 0 || j >= 0) {
		if (i >= 0) {
			carry += str1[i] - '0';
		}
		if (j >= 0) {
			carry += str2[i] - '0';
		}
		result += (char)(carry % 10 + '0');
		carry /= 10;
		i--;
		j--;
	}
	if (carry == 1) {
		result += '1';
	}
	//整体逆置
	reverse(result.begin(), result.end());
	return result;
}
int main() {
	string str1, str2;
	while (cin >> str1 >> str2) {
		cout << addStrings(str1, str2) << endl;
	}
	return 0;
}