#include <iostream>
#include <vector>
using namespace std;

void test(){
	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);

	for (auto e : v){
		cout << e << " ";
	}
	cout << endl;
}

int main(){
	test();
	system("pause");
	return 0;
}