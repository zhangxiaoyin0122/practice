//#include <iostream>
//#include <string>
//#include <vector>
//#include <algorithm>
//using namespace std;
//
//int main() {
//	string str;
//	while (getline(cin, str)) {
//		vector<string> vec;
//		string path = "";
//		for (int i = 0; i < str.size(); i++) {
//			if (str[i] == ' ') {
//				vec.push_back(path);
//				path.clear();
//				continue;
//			}
//			path += str[i];
//		}
//		vec.push_back(path);
//		cout << vec.size() << endl;
//		int i = 0;
//		int j = vec.size() - 1;
//		while (i < j) {
//			swap(vec[i], vec[j]);
//			i++;
//			j--;
//		}
//		//sort(vec.begin(),vec.end());
//		for (int i = 0; i < vec.size() - 1; i++) {
//			cout << vec[i] << " ";
//		}
//		cout << vec[vec.size() - 1] << endl;
//	}
//	return 0;
//}
#include <iostream>
#include <vector>
using namespace std;

int main() {
	int num;
	cin >> num;
	vector<int> vec;
	vec.resize(num);
	for (int i = 0; i < num; i++) {
		cin >> vec[i];
	}
	int i = 0;
	int count = 0;
	while (i < num) {
		//递增
		if (vec[i] < vec[i + 1]) {
			while (i < num && vec[i] <= vec[i + 1]) {
				i++;
			}
			i++;
			count++;
			//递减
		}
		else if (vec[i] > vec[i + 1]) {
			while (i < num && vec[i] >= vec[i + 1]) {
				i++;
			}
			i++;
			count++;
		}
		else {
			i++;
		}
	}
	cout << count << endl;
	return 0;
}

//ListNode* removeNthFromEnd(ListNode* head, int n) {
//	//利用快慢指针的方法去写
//	ListNode* fast = nullptr;
//	ListNode* slow = nullptr;
//	while (n--) {
//		if (fast == nullptr)
//			fast = head;
//		else
//			fast = fast->next;
//	}
//	while (fast->next) {
//		if (slow == nullptr) {
//			slow = head;
//			fast = fast->next;
//		}
//		else {
//			fast = fast->next;
//			slow = slow->next;
//		}
//	}
//	if (slow == nullptr) {
//		ListNode* tmp = head;
//		head = head->next;
//		delete tmp;
//	}
//	else {
//		ListNode* tmp = slow->next;
//		slow->next = tmp->next;
//		delete tmp;
//	}
//	return head;
//}
//};