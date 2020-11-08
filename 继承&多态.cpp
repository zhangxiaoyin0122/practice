#include <iostream>
#include <string>
using namespace std;


class Person {
public:
	void Print() {
		cout << _id << "\t" << _age << endl;
	}
protected:
	int _id = 12;
	int _age = 20;
};
class Student :public Person {
public:
	void show() {
		cout << _id << "\t" << _age << endl;
	}
private:
	int _num;
};

void test2() {
	Person p;
	Student s;
	p = s;

	Person* rp = &s;
	Person& rpq = s;
}

class Person {
public:
	Person() {
		_count++;
	}
protected:
	string _name;
public:
	static int _count; //
};
int Person::_count = 0;

class Student : public Person {
protected:
	int _StuNum;
};
class Graduate : public Student {
public:
	string _s;
};

class Tire {
protected:
	string _brand = "Michelin";
	size_t _size = 17;
};

class Car {
protected:
	string _color = "��ɫ";
	string _num = "��A0RX11";
	Tire _t;
};



//class Person {
//public:
//	virtual void BuyTicket() {
//		cout << "ȫ��Ʊ" << endl;
//	}
//};
//class Student : public Person {
//public:
//	void BuyTicket() {
//		cout << "���Ʊ" << endl;
//	}
//};

//void test(){
	/*Person* p = new Person();
	Person* s = new Student();
	p->BuyTicket();
	s->BuyTicket();
}*/
//Э��:
class A {

};
class B :public A{

};
class Person {
public:
	virtual A* BuyTicket() {
		cout << "ȫ��Ʊ" << endl;
	}

};
class Student : public Person {
public:
	virtual B* BuyTicket() {
		cout << "���Ʊ" << endl;
	}
};

//������������д
class Person {
public:
	virtual ~Person() {
		cout << "Person" << endl;
	}
};
class Student : public Person {
public:
	virtual ~Student() {
		cout << "Student" << endl;
	}
};

class Car {
public:
	virtual void Dirve()final {
		cout << "lisi" << endl;
	}
};
class Benz :public Car {
	virtual void Dirve() { //����,��������д
		cout << "zhangsan" << endl; 
	}
};

class Car {
public:
	virtual void Dirve() {
		cout << "lisi" << endl;
	}
};
class Benz : public Car {
public:
	virtual void Dirve()override { //����Ƿ���д����ĳ������,���û���򱨴�
		cout << "zhangsan" << endl;
	}
};

class Car {
public:
	virtual void Dirve() = 0;//���麯��
};
class Benz : public Car {
public:
	//��д���麯��
	virtual void Dirve() {
		cout << "zhangsan" << endl;
	}
};

class Base {
public:
	virtual void func() {
		cout << "1" << endl;
	}
};
class Dirve : public Base {
public:
	virtual void func() {
		cout << "2" << endl;
	}
};

void test() {
	Base b;
	Dirve d;
	Base& ra = b;
	Base& rb = d;
	ra.func();
	rb.func();
}

int main() {
	test();
	return 0;
}