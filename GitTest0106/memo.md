
## C++의 OOP(객체 지향) 특징
1. 캡슐화 -> 보일지, 안보일지 결정하는 접근 지정자가 있다. public/private(default) (+정보은닉)
2. 다형성
3. 상속
4. 추상화

C에서 중요한거? 함수 포인터, C는 절차지향인데, 함수 포인터로 객체 지향을 구현해서
객체 지향의 장점을 이용할 수 있기 때문.

class vs struct
class에서는 함수를 클래스안에 넣기도 한다.

클래스와 인스턴스 차이?
선언과 정의의 차이다. 클래스는 선언으로 메모리 할당 X, 인스턴스는 정의로 메모리 할당 O
인스턴스 : Foo foo;

클래스 내에서만 쓰는 static 변수, 즉 클래스 변수도 있다. (static?)

멤버 변수는 인스턴스마다 독립적이지만, 멤버함수는 모든 인스턴스가 공유한다.
이게 뭔소리야. 진짜로?

클래스는 스택 or 힙? -> 스택에 만드는 것이 좋다. 힙은 메모리 관리하기 귀찮으니까~~
C++에서는 힙에 할당하는 게 malloc 말고 new 도 있대~
malloc - free  // new - delete
근데 주로 new를 쓴대 -> 생성자 호출 가능, 메모리 재조정 가능, 예외 처리도 가능
malloc은 NULL 반환해서 NULL 처리를 해줘야된대

## 인스턴스 생성 방법
```cs
Sample s1;	// 주로 이걸 씀.
Sample* s2 = new Sample;
Sample* s3 = new Sample();	// 함수가 아닌게 확실하다? 그래서 가능하긴 함.
```
this pointer -> 붕어빵 내의 참조? 붕어빵 자신을 가리키는 포인터?

C++에서 :: 연산자 우선순위가 가장 높다.

using namespace Test; -> 매번 Test를 안써도 된다.

어떤 namespace에도 속해있지 않은, 함수/변수를 글로벌 namespace라고 한다.
```cs
void init();
```

typedef도 써도 되지만, using을 쓰자.

C++ 에서도 C 함수를 사용할 수 있는데, (cstdio, cmat, cstring 처럼) 하지만 안쓰는게 좋다.


### Auto와 decletype
auto는 값에 따라 자동으로 데이터타입을 지정해준다.
auto는 선언/정의할 때, decletype은 반환 받을 때.
```cs
decletype(11) b = 22;
```

### 배열 vs vector
vector는 동적 배열로, 크기가 자동으로 늘어남?

## 유니폼 초기화
어떤 데이터타입의 변수든 a{0}, b{0,0}, cl{0,0} 이런식으로 초기화할 수 있는 방식
```cs
struct test t0 {0,0};
struct test t1 (0,0);	// error
test_class t2 {0,0};
test_class t3 (0,0); // 구조체는 안되지만 클래스는 소괄호로도 유니폼 초기화가 가능하다._
```
### C++ 에서의 구조체
struct 생략 가능
structure binding
```cs
struct pStr{
	int x;
	int y;
};

pStr pt;
auto [a, b] = pt; // a와 b 값에 x와 y 값이 들어간대 신기
// 데이터형과 개수가 같아야 binding이 된다.
```

### C++은 string 타입이 있다.
아래와 같이 직관적인 연산이 가능하다. without strcpy!!!!
==, +, =
```cs
string s1 = "test";
string s2;
string s3 = "cat";
string s4 = est;

s2 = s1;
s4 = s1 + s3;
if(s1 == s4) ...
```

### C++에서는 bool 에 1,0을 넣으면 warning 뜬다.
```cs
bool a = 1;	// C에서는 아무말도 안하지만, C++은 waning
```

