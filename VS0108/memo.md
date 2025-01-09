### pubilc vs private vs protected
protected는 자식 클래서에서만 접근 가능하며, 외부에서는 접근 불가능
public: 외부 접근 가능
private: 외부 접근, 자식 클래스에서도 접근 불가능

### 상속 관계가 있을 때 생성자, 소멸자는?
생성자 : Base 클래스 -> 파생 클래스 순으로 호출된다.
소멸자 : 파생 클래스 -> Base 클래스 순으로 호출된다.

### 파생 클래스의 생성자를 호출했을 때, Base 클래스 생성자가 없다는 에러는 왜 뜨나?
```cs
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
		major{ major }, number{number}
	{ // (4) 여기서 상위 객체의 디폴트 생성자를 호출하려고 한다. error 발생

	}
};

int main(void) {
	Person p2 = { "정상훈", 11 }; // (1) Person은 아무런 문제가 없는데...
	Student s1 = { "컴퓨터공학", 92 }; // (2) Student를 이렇게 만드려다 보니
	return (0);
}
```
어떻게 해결?  
객체 생성할 때, Student s1; 이거보다는 Student s1(name, age, ...); 이렇게 만드는 게 좋다.  
파생, Base 클래스 둘다 생성자가 없으면 default 생성자가 있어서 객체 생성은 가능하다.  
하지만, 생성자를 만드는게 좋다.  

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
```
### Base 클래스의 소멸자는 반드시 가상으로 만들어야 한다.
업캐스팅 이후 파생 객체를 지울 때 문제가 생길 수 있기 때문이다.  
```cs
/* 업캐스팅?? */
Base* b = new Derived();

/* 다운캐스팅 (불가능하다) */
Derived* b2 = new Base();
```

```cs
class Base {
public:
	Base() { std::cout << "Base()" << std::endl; }
	~Base() { std::cout << "~Base()" << std::endl; }	// 이러면 업캐스팅으로 객체 생성했을 때, 지울 경우 문제가 생긴다.
	//virtual ~Base() { std::cout << "~Base()" << std::endl; }
};
```

virtual은 이 함수를 오버라이딩해라 라는 의미이므로, ~Base가 오버라이딩이 안돼서 파생클래스의 소멸자가 호출이 안된다.

### 다중 상속 가능
근데 거의 안씀
```cs
class Mother {
	smash();
}

class Father {
	smash();
}

class Me: public Father, public Mother {
	smash(); // 엄마의 등짝스매쉬인가? 아빠의 등짝스매쉬인가?
}
```

### virtual는 우선순위가 낮다?
```cs
class Father {
	void test();
	// virtual void test();
}

class Daughter : public Father{
	void test();
}

int main() {
	Father* a = new Daughter; // 업캐스팅
	a.test();	// 어떤 클래스의 test가 호출되나?
}