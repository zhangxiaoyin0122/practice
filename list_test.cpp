#include <iostream>
#include <string>
#include <list>
using namespace std;


void test() {
	list<int> lst;
	lst.push_back(1);
	lst.push_back(2);
	lst.push_back(4);
	lst.push_back(4);
	lst.push_back(6);
	lst.push_back(6);
	lst.push_back(7);
	list<int>::iterator it = lst.begin();
	while (it != lst.end()) {
		cout << *it << " ";
		++it;
	}
	cout << endl;
	lst.unique();
	list<int>::iterator t = lst.begin();
	while (t != lst.end()) {
		cout << *t << " ";
		++t;
	}
	cout << endl;
}
void test1() {
	string str1 = "abcdabcd";
	size_t s = str1.find('a');
	cout << s << endl;

	string str2 = "abc";
	str2.append("abc");
	str2.append(str1);
	cout << str2 << endl;

	string str3;
	getline(cin, str3);
	cout << str3 << endl;


}




int main() {
	test1();
	return 0;
}