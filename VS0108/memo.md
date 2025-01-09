### pubilc vs private vs protected
protected�� �ڽ� Ŭ���������� ���� �����ϸ�, �ܺο����� ���� �Ұ���
public: �ܺ� ���� ����
private: �ܺ� ����, �ڽ� Ŭ���������� ���� �Ұ���

### ��� ���谡 ���� �� ������, �Ҹ��ڴ�?
������ : Base Ŭ���� -> �Ļ� Ŭ���� ������ ȣ��ȴ�.
�Ҹ��� : �Ļ� Ŭ���� -> Base Ŭ���� ������ ȣ��ȴ�.

### �Ļ� Ŭ������ �����ڸ� ȣ������ ��, Base Ŭ���� �����ڰ� ���ٴ� ������ �� �߳�?
```cs
#include <string>

class Person {
public:
	std::string name;
	int age;
	// �⺻ �����ڰ� ������
	Person(const std::string& name, int age)  // (1) �䷸�� �����ε� ����, ����Ʈ �����ڰ� �����
		: name{ name }, age{ age }
	{

	}
};

class Student : public Person {
public:
	std::string major;
	int number; // �й�

	Student(std::string major, int number) : // (3)�� ���� �����ڸ� �߰��ؾ� �Ǵµ�
		major{ major }, number{number}
	{ // (4) ���⼭ ���� ��ü�� ����Ʈ �����ڸ� ȣ���Ϸ��� �Ѵ�. error �߻�

	}
};

int main(void) {
	Person p2 = { "������", 11 }; // (1) Person�� �ƹ��� ������ ���µ�...
	Student s1 = { "��ǻ�Ͱ���", 92 }; // (2) Student�� �̷��� ������� ����
	return (0);
}
```
��� �ذ�?  
��ü ������ ��, Student s1; �̰ź��ٴ� Student s1(name, age, ...); �̷��� ����� �� ����.  
�Ļ�, Base Ŭ���� �Ѵ� �����ڰ� ������ default �����ڰ� �־ ��ü ������ �����ϴ�.  
������, �����ڸ� ����°� ����.  

```cs
#include <iostream>
#include <string>

class Person {
public:
	std::string name;
	int age;
};

class Student : public Person {
public:
	std::string major;
	int number; // �й�

	Student(std::string major, int number, std::string name, int age) :
		Person{ name, age }, // (1) ���� ������ü �����ڸ� ���� ȣ���ؾ� �Ѵ�.
		major{ major }, number{ number } // (2) ���Ŀ� �� ��ü�� �ʱ�ȭ ����.
	{

	}
};

class Professor : public Person {
public:
	std::string major;
	int grade;

	Professor(std::string major, int grade, std::string name, int age) :
		Person{ name, age }, // (1) ���⵵ ��������
		major{ major }, grade{ grade } // (2) ���Ŀ� �� ��ü�� �ʱ�ȭ ����.
	{

	}
};

int main(void) {
	Student s1 = { "computer", 12, "������", 22 };
	Professor p1 = { "history", 1, "������", 33 };
	std::cout << s1.major << "," << s1.number << "," << s1.name << "," << s1.age << std::endl;
	std::cout << p1.major << "," << p1.grade << "," << p1.name << "," << p1.age << std::endl;
	return (0);
}
```
### Base Ŭ������ �Ҹ��ڴ� �ݵ�� �������� ������ �Ѵ�.
��ĳ���� ���� �Ļ� ��ü�� ���� �� ������ ���� �� �ֱ� �����̴�.  
```cs
/* ��ĳ����?? */
Base* b = new Derived();

/* �ٿ�ĳ���� (�Ұ����ϴ�) */
Derived* b2 = new Base();
```

```cs
class Base {
public:
	Base() { std::cout << "Base()" << std::endl; }
	~Base() { std::cout << "~Base()" << std::endl; }	// �̷��� ��ĳ�������� ��ü �������� ��, ���� ��� ������ �����.
	//virtual ~Base() { std::cout << "~Base()" << std::endl; }
};
```

virtual�� �� �Լ��� �������̵��ض� ��� �ǹ��̹Ƿ�, ~Base�� �������̵��� �ȵż� �Ļ�Ŭ������ �Ҹ��ڰ� ȣ���� �ȵȴ�.

### ���� ��� ����
�ٵ� ���� �Ⱦ�
```cs
class Mother {
	smash();
}

class Father {
	smash();
}

class Me: public Father, public Mother {
	smash(); // ������ ��¦���Ž��ΰ�? �ƺ��� ��¦���Ž��ΰ�?
}
```

### virtual�� �켱������ ����?
```cs
class Father {
	void test();
	// virtual void test();
}

class Daughter : public Father{
	void test();
}

int main() {
	Father* a = new Daughter; // ��ĳ����
	a.test();	// � Ŭ������ test�� ȣ��ǳ�?
}