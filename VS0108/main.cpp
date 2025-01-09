#include <iostream>

#if 0
// �ƺ�: Base
//   ��: Derived
class �ƺ� {
private:
	int a;
public:
	�ƺ�() : a{ 0 } { std::cout << "�ƺ�() ȣ��" << std::endl; }
	�ƺ�(int a) : a{ a } { std::cout << "�ƺ�(int) ȣ��" << std::endl; }
	~�ƺ�() { std::cout << "~�ƺ�() ȣ��" << std::endl; }
};

class �� : public �ƺ� {
private:
	int b;
public:
	��() : b{ 0 } { std::cout << "��() ȣ��" << std::endl; }
	��(int b) : b{ b } { std::cout << "��(int) ȣ��" << std::endl; }
	~��() { std::cout << "~��() ȣ��" << std::endl; }

};


int main() {
	�� ����; // �ƺ� �����ڰ� ���� ȣ��ɱ�? �� �����ڰ� ���� ȣ��ɱ�? ����
	�� ����(11); // �ƺ�(int)�� ȣ��ɱ�? �ƺ�()�� ȣ��ɱ�? ����

	return (0);
}
#endif

#if 0
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
		major{ major }, number{ number }
	{ // (4) ���⼭ ���� ��ü�� ����Ʈ �����ڸ� ȣ���Ϸ��� �Ѵ�. error �߻�

	}
};

int main(void) {
	Person p2 = { "������", 11 }; // (1) Person�� �ƹ��� ������ ���µ�...
	Student s1 = { "��ǻ�Ͱ���", 92 }; // (2) Student�� �̷��� ������� ����
	return (0);
}
#endif

#if 0
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
#endif

#if 1
#include <iostream>

class Base {
public:
	Base() { std::cout << "Base()" << std::endl; }
	~Base() { std::cout << "~Base()" << std::endl; }	// �̷��� ��ĳ�������� ��ü �������� ��, ���� ��� ������ �����.
	//virtual ~Base() { std::cout << "~Base()" << std::endl; }
};

class Derived : public Base {
public:
	Derived() { std::cout << "Derived()" << std::endl; }
	~Derived() { std::cout << "~Derived()" << std::endl; }
};

int main(void) {
	//Base* b = new Base();
	//delete b;

	//std::cout << std::endl;
	//Derived* d = new Derived();
	//delete d;

	Base* e = new Derived(); // ��ĳ���� (�ݴ븦 �ٿ�ĳ�����̶�� ��)
	delete e;

	return (0);
}
#endif