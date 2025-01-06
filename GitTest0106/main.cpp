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

#if 0
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

#if 0
/* C++ 에서는 namespace를 이용하여 같은 이름의 함수 또는 변수를 정의할 수 있다. */
// 오 신기한게 namespace도 전역변수네 그냥/ 짱 신기해
namespace Audio {
	int num;

	void init() {
		printf("init Audio Module\r\n");
	}
}

namespace Video {
	int num;

	void init() {
		printf("init Video Module\r\n");
	}
}

int main() {
	Audio::init();
	Video::init();

	Audio::num = 11;
	Video::num = 22;

	printf("(Audio,Video) = (%d,%d)\n", Audio::num, Video::num);
}
#endif

#if 0
/* 
 * std:: 생략
 * cout이랑 cin도 마찬가지로 std::를 생략하기 위해
 * using namespace std; 를 쓰는거다.
 * 원래 형태는
 * std::cout << "Hello";
 */
#include <stdio.h>
#include <algorithm>

/* 이렇게 쓰면 main에서 std:: 를 생략해도 된다. */
//using std::max;
//using std::min;

// using namespace std;	// 이걸 써도 된다.

int main() {
	int a = 11;
	int b = 22;

	int max_val = std::max(a, b); // (1)
	int min_val = std::min(a, b);

	printf("(a,b)=(%d,%d)\r\n", a, b);
	printf("max = %d\r\n", max_val);
	printf("min = %d\r\n", min_val);
	return (0);
}
#endif

#if 0
/* 글로벌 네임스페이스 */
#include <stdio.h>

namespace Audio {
	void init() {
		printf("init Audio Module\r\n");
	}
}

namespace Video {
	void init() {
		printf("init Video Module\r\n");
	}
}

void init() { printf("init global Module\r\n"); } // (1) 추가됨

int main() {
	Video::init();
	Audio::init();
	init(); // (2)
	::init(); // (3)
}
#endif

#if 0
/* 중첩 네임스페이스 */
#include <iostream>

namespace big {
	namespace middle {
		namespace small {
			int a;
			int b;
		}
	}
}

int main() {
	big::middle::small::a = 123;
	big::middle::small::b = 456;

	std::cout << big::middle::small::a << std::endl;
	std::cout << big::middle::small::b << std::endl;

	return 0;
}
#endif

#if 0
/* namespace 별명 (중첩일 때 줄여서 쓸 수 있음.) */
std::filesystem::create_directories("c:/bts"); // (1)

namespace fs = std::filesystem; // (2) std::filesystem 이게 너무 기니까 별칭을 붙이자.
fs::create_directories("c:/exo");
#endif

#if 0
#include <iostream>

int main() {
	typedef int intger; // 지양
	intger a = 111;
	std::cout << a << std::endl;

	using real_number = double;	// 지향
	real_number b = 3.14;
	std::cout << b << std::endl;

	return 0;
}
#endif

#if 0
using namespace std;

int main() {
	int a = 3;
	int b = 5;
	int c = -1;
	int age;
	int sum = 0;

	cout << "세 개의 숫자는 " << a << ", " <<  b << ", " << c << endl;

	cout << "당신의 나이는 몇 살인가요? ";
	cin >> age;
	cout << "저는 " << age << " 살 입니다." << endl;

	cout << "숫자 3개를 입력하세요. ";
	cin >> a >> b >> c;
	sum = a + b + c;
	cout << "세 숫자의 합은 " << sum << " 입니다." << endl;
}
#endif

#if 0
/* 입출력 조정자, 별로 안쓴다. C로 치면 %5d, %.1f 뭐 이런식? */
#include <iostream>
#include <iomanip>

int main() {
	int a = 12345;
	std::cout << std::setw(10) << a << std::endl;
	std::cout << std::setw(10) << std::setfill('@') << a << std::endl;
	std::cout << std::setw(10) << std::setfill('@') << std::left << a << std::endl;

	return (0);
}
#endif

#if 0
#include <iostream>
#include <vector>
#include <string>

int main() {
	auto x = { 11, 22, 33 };
	// 배열이 아니다. 특별한 컨테이너인 std::initializer_list<int>
	// initializer_list가 제공하는 being(), end 함수 사용할것
	//std::cout << x << std::endl; // 이렇게 출력하면 안됀다!
	for (auto e : x) {
		std::cout << e << ", ";
	}
	std::cout << std::endl;

	std::initializer_list<int> y = { 44, 55, 66 };
	for (std::initializer_list<int>::iterator it = y.begin(); it != y.end(); ++it) {
		std::cout << *it << ", ";
	}
	std::cout << std::endl;
	return 0;
}
#endif

#if 1
struct point {
	int x;
	int y;
};

class rect {
public:
	int x1;
	int y1; // x2,y2를 넣어 2점을 만들어야 하지만, 
	// 클래스 초기화만 볼것이므로 x2, y2는 뺐다.
	rect(int a, int b) {
		x1 = a;
		y1 = b;
	}
};

int main(void) {
	// 초기화 방법이 다양해서 헷갈린다.
	int          a1 = 0;			//기본 데이터형은 =연산자로 초기화, 괄호가 없다.
	struct point b1 = { 0,0 };		// 구조체는 중괄호
	int          c1[3] = { 11,22,33 };	// 배열은 중괄호
	rect         r1(1, 2);				// 클래스는 소괄호

	int          a2 = { 0 };
	struct point b2 = { 0,0 };
	int          c2[3] = { 11,22,33 };
	rect         r2 = { 1,2 };

	int          a3{ 0 };
	int			 a4(11); // not good 생성자 스타일로 초기화 헷갈리니까 위에껄 쓰자
	struct point b3 { 0, 0 };
	//struct point b4(1, 2); // error
	int          c3[3]{ 11,22,33 };
	rect         r3{ 1,2 };
	rect         r4(1, 2);// 구조체는 안되지만 클래스는 가능
	return 0;
}
#endif

#include <cstdbool>

bool a = true;