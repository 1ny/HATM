#include <iostream>

#if 0
// 아빠: Base
//   딸: Derived
class 아빠 {
private:
	int a;
public:
	아빠() : a{ 0 } { std::cout << "아빠() 호출" << std::endl; }
	아빠(int a) : a{ a } { std::cout << "아빠(int) 호출" << std::endl; }
	~아빠() { std::cout << "~아빠() 호출" << std::endl; }
};

class 딸 : public 아빠 {
private:
	int b;
public:
	딸() : b{ 0 } { std::cout << "딸() 호출" << std::endl; }
	딸(int b) : b{ b } { std::cout << "딸(int) 호출" << std::endl; }
	~딸() { std::cout << "~딸() 호출" << std::endl; }

};


int main() {
	딸 예림; // 아빠 생성자가 먼저 호출될까? 딸 생성자가 먼저 호출될까? 전자
	딸 예슬(11); // 아빠(int)가 호출될까? 아빠()가 호출될까? 후자

	return (0);
}
#endif

#if 0
#include <string>

class Person {
public:
	std::string name;
	int age;
	// 기본 생성자가 날라갔죠
	Person(const std::string& name, int age)  // (1) 요렇게 오버로딩 해줌, 디폴트 생성자가 사라짐
		: name{ name }, age{ age }
	{

	}
};

class Student : public Person {
public:
	std::string major;
	int number; // 학번

	Student(std::string major, int number) : // (3)과 같은 생성자를 추가해야 되는데
		major{ major }, number{ number }
	{ // (4) 여기서 상위 객체의 디폴트 생성자를 호출하려고 한다. error 발생

	}
};

int main(void) {
	Person p2 = { "정상훈", 11 }; // (1) Person은 아무런 문제가 없는데...
	Student s1 = { "컴퓨터공학", 92 }; // (2) Student를 이렇게 만드려다 보니
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
	int number; // 학번

	Student(std::string major, int number, std::string name, int age) :
		Person{ name, age }, // (1) 주의 상위객체 생성자를 먼저 호출해야 한다.
		major{ major }, number{ number } // (2) 이후에 내 객체를 초기화 하자.
	{

	}
};

class Professor : public Person {
public:
	std::string major;
	int grade;

	Professor(std::string major, int grade, std::string name, int age) :
		Person{ name, age }, // (1) 여기도 마찬가지
		major{ major }, grade{ grade } // (2) 이후에 내 객체를 초기화 하자.
	{

	}
};

int main(void) {
	Student s1 = { "computer", 12, "정상훈", 22 };
	Professor p1 = { "history", 1, "정예림", 33 };
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
	~Base() { std::cout << "~Base()" << std::endl; }	// 이러면 업캐스팅으로 객체 생성했을 때, 지울 경우 문제가 생긴다.
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

	Base* e = new Derived(); // 업캐스팅 (반대를 다운캐스팅이라고 함)
	delete e;

	return (0);
}
#endif