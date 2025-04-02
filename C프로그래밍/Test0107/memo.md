### 오버로딩 네임 맹글링 (name mangling, name decosration)
컴파일러가 이름이 같은 함수들의 이름을 알아서 바꿔준다.  
어셈블리에서 서브루틴을 살펴보면, 아래와 같이 바뀐다. 
```cs
square@@YAHH@Z
square@@YANN@Z
```
다만, C와 C++ 호환에 문제가 생긴다. 근데 사실 C랑 C++를 섞어 쓰는 건 안좋다.  
  
### 인라인 함수
```cs
inline int sum(int a, int b) {
	return a + b;
}
```
매크로 함수와 비슷하게 치환된다.  
하지만, 전처리기로 처리하는 매크로와 달리, 인라인 함수는 컴파일러로 처리한다.  
인라인 함수는 일반 함수와 달리 주소가 없다.  
일반 함수에 비해 stack에 넣고 빼는 과정이 없기에 빠르다?  

### 함수 템플릿
Body 내용은 같은데, 파라미터나 리턴타입이 다른 경우, 함수 템플릿을 사용하면 수정할 때 편하다.  
```cs
template<typename T>
T square(T a) {
	return a * a;
}

int main() {
	int c = square<int>(2);
	double d = square<double>(3.2);
	cout << c << endl;
	cout << d << endl;

	return 0;
}
```
#### typename 대신 class라 적어도 된다.
```cs
template<class T>
T square(T a) {
	return a * a;
};
```
함수 템플릿은 일반 함수가 아니기 때문에 주소가 없다.  

### for_each
```cs
// for_each(first, last, body func);
std::for_each(arr, arr + 5, print_one);
```

### range for 범위 기반 for문
 ```cs
 	// 범위 기반 for 문을 사용해서 출력하기
	for (int ele : arr) {
		std::cout << ele << ", ";
	}
	std::cout << std::endl;

	// 범위 기반 for 문과 레퍼런스를 사용해서 출력하기
	for (const int& ele : arr) {
		std::cout << ele << ", ";
	}
```
### memory 동적 할당 : new delete.

### c vs c++
call by value - pass by value (a = b)  
call by reference - pass by address (int* pa = &a;)  
' ' - pass by reference (int& ra = a;)  

reference는 NULL이 없다. 즉, NULL인지 검사할 필요가 없다.  
reference는 한번 초기화하면 그 주소값이 바뀔 수 없다. 
따라서 pass by reference 쓰는게 좋다~
```cs
	int a = 11;
	int& ra = a; // ra와 a는 같다고 보면 된다.
	ra = 33;
	a = ra;	// 이것도 된다.
	// 주소는 안바뀌는데, 값은 바뀌네.
	int b = 999;
	ra = b;
```
값이 바뀌는 걸 방지하기 위해서 C++은 아래와 같이 pass by reference + const를 많이 쓴다.
```cs
void func(const int& a);
```

### c++ 클래스의 정보은닉
private 으로 지정하여 데이터를 감출 수 있다.
```cs
class FishBun {
private:
	int price;

public:
	void printPrice() {
		cout << price << endl;
	}
};
```
#### 접근 지정자 (setter, getter)
멤버 변수가 접근하는 함수, 예를 들면 setAge, getAge 이런식의 함수를 setter, getter 라고 한다.  

### encapsulation -> 캡슐화~ C++/OOP의 특징

### 함수 뒤에 const
함수 뒤의 const가 붙으면,  
1. 객체 내부 변수 값 변경 불가
2. const 함수만 호출 가능
```cs
class Number {
private:
	int num;
public:
	int GetNum() {
		return num;
	}
	bool IsNotZero() const {
		int r = GetNum();	// error! non-const function
		SetZero();	// call ok! const function and didn't change value
		return num != 0;
	}
	void SetZero() const {
		num = 0;	// error ! cannot change any value
	}
};
```

### 생성자와 소멸자
#### 생성자
생성자는 객체가 생성될 떄 자동으로 실행된다.  
즉, 초기화 시킬 때 사용.
#### 소멸자
소멸자는 main 함수가 끝나고 나서 실행된다.
```cs
class Person {
private:
	std::string name;
	int age;

public:
	// 생성자
	Person() {
		name = "tom";
		age = 11;
		std::cout << "생성자 호출" << endl;
	}
	// 소멸자
	~Person() {
		std::cout << "소멸자 호출" << endl;
	}
};

int main() {
	Person p1;
	std::cout << "main 함수 호출" << endl;
}
```

출력 결과는 생성자 -> main -> 소멸자

생성자에 인자를 적을 수도 있다. 다만, 인자를 적을 경우 객체를 생성할 때 항상 인자가 있어야 한다.
```cs
class Person {
...

public:
	Person(int a) {
		age = a;	
	}
}

int main() {
	Person p1(3);
	Person p2; // error
}
```

소멸자는 할당 받은 자원을 반남할때 사용한다.  
소멸자가 없으면?? 자동으로 소멸자가 호출된다...?  