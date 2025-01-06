#include <iostream>

#if 0
#include <iostream>

using namespace std;	// cout, endl in standard library (std)
						// 변수명, 함수명 등의 중복을 방지하기 위해 namespace를 사용

class point_t {
public:	// 접근 지정자 class는 default가 private 이다.
	int x;
	int y;

	void set_x(int a) {
		x = a;
	}
	void set_y(int b) {
		y = b;
	}
};

int main() {
	point_t pt1 = { 22, 33 };

	printf("point(x,y)=(%d,%d)\n", pt1.x, pt1.y);
	
	//printf("Hello world\n"); // printf 도 가능하긴 하다.
	
	return 0;
}
#endif


#if 0
#include <stdio.h>

/* C++ 에서는 typedef 없이도 구조체변수 선언할 때 struct 생략 가능 */
struct point_t {
	int x;
	int y;

	void set_x(int a) {
		x = a;
	}
	void set_y(int b) {
		y = b;
	}
};

int main() {
	point_t pt1;

	pt1.set_x(11);
	pt1.set_y(22);

	// print_T pt1 = {11, 22} // uniform 초기화, 만들면서 초기화시키는 게 좋다.

	printf("ponint(x,y)=(%d,%d)\n", pt1.x, pt1.y);
}
#endif

#if 0
/* 사각형 넓이 */
#include <iostream>

struct rectangel_t {
	int x1;
	int x2;
	int y1;
	int y2;
};

class rect_t {
public:
	int x1;
	int x2;
	int y1;
	int y2;

	int get_area() {
		return (x2 - x1) * (y2 - y1);
	}
};

int get_area_rect(rectangel_t* r) {
	return (r->x2 - r->x1) * (r->y2 - r->y1);
}

int main() {
	rectangel_t r = { 10, 20, 10, 20 };
	rect_t r2 = { 10, 30, 10, 30 };
	int area = 0;

	area = get_area_rect(&r);
	printf("사각형의 넓이는 %d입니다. \n", area);

	area = r2.get_area();
	printf("사각형의 넓이는 %d입니다. \n", area);
}
#endif

#if 0
/* C에서 함수 포인터를 구조체 변수로 쓸수 있다는 거 */
#include <stdio.h>
#include <conio.h>

int add(int x, int y) {
	return (x + y);
}

int sub(int x, int y) {
	return (x - y);
}

typedef struct _calculator_t {
	int x;
	int y;
	int (*p_add)(int a, int b); // 함수 포인터가 올수 있다.
	int (*p_sub)(int a, int b);

} calculator_t;

typedef int (*fp_calc)(int, int);


int main() {
	calculator_t calc;
	//calc.x = 11;
	//calc.y = 22;
	//printf("%d,%d", calc.x, calc.y);

	int a = 7;
	int b = 3;
	float r = 0;

	calc.p_add = &add;
	r = calc.p_add(a, b);
	printf("%d%c%d=%3.1f\r\n", a, '+', b, (float)r);

	calc.p_sub = &sub;
	r = calc.p_sub(a, b);
	printf("%d%c%d=%3.1f\r\n", a, '+', b, (float)r);


	return 0;
}
#endif

#if 0
/* 접근 지정자 priate, public, protected*/
class Foo {
private:
	int a;
public:
	int b;
	int c;

private:
	void func1() {
		std::cout << "func1" << std::endl;
	}
public:
	void func2() {
		std::cout << "func2" << std::endl;
	}
	void func3() {
		std::cout << "func3" << std::endl;
	}

	void func4();
};

/* 이거는 선언이 Foo 클래스에 있으므로, 클래스 안에 속하는 걸로 친다. */
void Foo::func4() { 
		std::cout << "func2" << std::endl;
}

int main() {
	Foo foo;

	foo.b = 22;
	foo, c = 33;

	//foo.func1();
	foo.func2();
	foo.func3();
}
#endif

#if 0
/* static 변수, 클래스 변수 */
class Foo {
public:
	int a;
	int b;

	static int x;

	void func1();

	static void sfunc1() {
		std::cout << "sfunc1()" << std::endl;
	}
};

int Foo::x = 88; // static 변수는 이렇게 정의?

int main() {
	Foo foo;

	foo.a = 33;
	foo.b = 44;

	Foo::sfunc1();
}
#endif

#if 0
/* static 변수는 새로운 인스턴스로 접근해도 값이 저장되어 있어서 연동된다? */

class Fishbun {
public:
	int cnt1;

	static int cnt2;

	Fishbun() :
		cnt1{ 0 }
	{
		++cnt1;
		++cnt2;
	}
};

int Fishbun::cnt2 = 0;

int main() {
	Fishbun f1;
	std::cout << f1.cnt1 << "," << Fishbun::cnt2 << std::endl;

	Fishbun f2;
	std::cout << f1.cnt1 << "," << Fishbun::cnt2 << std::endl;

	Fishbun f3;
	std::cout << f1.cnt1 << "," << Fishbun::cnt2 << std::endl;


	return (0);
}
#endif

#if 0
/* free로 메모리 해제 후 접근 가능? */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct _car_t {
	uint8_t fuel;
	uint8_t speed;
} car_t;

int main() {
	car_t* my_car = (car_t*)malloc(sizeof(car_t));
	car_t* your_car = (car_t*)malloc(sizeof(car_t));

	if (my_car == NULL) {
		printf("my_car create error\r\n");
		return 0;
	}
	else {
		printf("my_car create ok\r\n");
	}

	if (your_car == NULL) {
		printf("your_car create error\r\n");
		return 0;
	}
	else {
		printf("your_car create ok\r\n");

	}

	my_car->fuel = 11;
	my_car->speed = 22;

	your_car->fuel = 33;
	your_car->speed = 44;

	printf("%d, %d\r\n", my_car->fuel, my_car->speed);
	printf("%d, %d\r\n", your_car->fuel, your_car->speed);

	free(my_car); // (1) ★★★ 난 분명히 free를 했다? 했다고!
	free(your_car);

	// 여기서 문제가 생겨야되는데, 이게 되네?
	// free를 한다고 해서 메모리가 사리지는 건 아니다.
	// 힙은 다른 애가 해당 메모리를 접근하지 못하도록 보장을 해주는데, free를 해버리면 보장을 안해주는 거다.
	// 즉, free를 한 후 값을 넣으면 운 좋게 값이 나올 순 있지만, 보장은 안된다. 위험하다. 쓰지말자.
	// 이런 위험한 접근을 방지하려면? NULL인지 판단, free한 이후에는 nullptr로 초기화.
	if (my_car != NULL) {
		my_car->fuel = 55; // (2) 여기서 값을 넣으면 어떻게 될까?
		my_car->speed = 66;
	}

	my_car = nullptr;
	your_car = nullptr;

	printf("%d, %d\r\n", my_car->fuel, my_car->speed);

	return 0;
}
#endif

#if 0
/* this pointer? -> 자기 자신의 참조를 돌려주는 것. */
// static 함수에서는 객체가 없을 수도 있기에 this를 사용할 수 없다?
// this 포인터 왜 사용???
class Point {
private:
	int x{ 0 };
	int y{ 0 };

public: 
	void set(int a, int b) {
		x = a;
		y = b;
		std::cout << this << std::endl; // pt1.set의 참조를 돌려줌. 즉, 함수를 호출할 때 사용한 객체 pt1, pt2의 주소를 가리킴.
	}
};

int main() {
	Point pt1;
	Point pt2;

	std::cout << &pt1 << std::endl;
	std::cout << &pt2 << std::endl;

	pt1.set(11, 22);	// 객체 pt1의 주소 출력
	pt2.set(33, 44);	// 객체 pt2의 주소 출력
}
#endif

#if 1
#include <iostream>

class Counter {
public:
	int count;
public:
	void reset(int count = 0) {
		this->count = count;
	}

	Counter* increment() {
		++count;
		return this;
	}

	Counter& decrement() {
		--count;
		return *this;
	}
};

int main() {
	Counter c;

	c.reset();
	c.increment()->increment()->increment()->increment();
	/* 위랑 같은 거 
	c.increment();
	c.increment();
	c.increment();
	c.increment();
	c.increment();
	*/

	std::cout << c.count << std::endl;
	c.decrement().decrement().decrement();
	std::cout << c.count << std::endl;

	return 0;
}
#endif
/*
 * C++의 OOP(객체 지향) 특징
 * 1. 캡슐화 -> 보일지, 안보일지 결정하는 접근 지정자가 있다. public/private(default) (+정보은닉)
 * 2. 다형성
 * 3. 상속
 * 4. 추상화
 * 
 * 
 * C에서 중요한거? 함수 포인터, C는 절차지향인데, 함수 포인터로 객체 지향을 구현해서
 * 객체 지향의 장점을 이용할 수 있기 때문.
 * 
 * class vs struct
 * class에서는 함수를 클래스안에 넣기도 한다.
 * 
 * 클래스와 인스턴스 차이?
 * 선언과 정의의 차이다. 클래스는 선언으로 메모리 할당 X, 인스턴스는 정의로 메모리 할당 O
 * 인스턴스 : Foo foo;
 * 
 * 클래스 내에서만 쓰는 static 변수, 즉 클래스 변수도 있다. (static?)
 * 
 * 멤버 변수는 인스턴스마다 독립적이지만, 멤버함수는 모든 인스턴스가 공유한다.
 * 이게 뭔소리야. 진짜로?
 * 
 * 클래스는 스택 or 힙? -> 스택에 만드는 것이 좋다. 힙은 메모리 관리하기 귀찮으니까~~
 * C++에서는 힙에 할당하는 게 malloc 말고 new 도 있대~
 * malloc - free  // new - delete
 * 근데 주로 new를 쓴대 -> 생성자 호출 가능, 메모리 재조정 가능, 예외 처리도 가능
 * malloc은 NULL 반환해서 NULL 처리를 해줘야된대
 * 
 * # 인스턴스 생성 방법
 * Sample s1;	// 주로 이걸 씀.
 * Sample* s2 = new Sample;
 * Sample* s3 = new Sample();	// 함수가 아닌게 확실하다? 그래서 가능하긴 함.
 * 
 * this pointer -> 붕어빵 내의 참조? 붕어빵 자신을 가리키는 포인터?
 */


