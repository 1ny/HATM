#include <iostream>

#if 0
#include <iostream>

using namespace std;	// cout, endl in standard library (std)
						// ������, �Լ��� ���� �ߺ��� �����ϱ� ���� namespace�� ���

class point_t {
public:	// ���� ������ class�� default�� private �̴�.
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
	
	//printf("Hello world\n"); // printf �� �����ϱ� �ϴ�.
	
	return 0;
}
#endif


#if 0
#include <stdio.h>

/* C++ ������ typedef ���̵� ����ü���� ������ �� struct ���� ���� */
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

	// print_T pt1 = {11, 22} // uniform �ʱ�ȭ, ����鼭 �ʱ�ȭ��Ű�� �� ����.

	printf("ponint(x,y)=(%d,%d)\n", pt1.x, pt1.y);
}
#endif

#if 0
/* �簢�� ���� */
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
	printf("�簢���� ���̴� %d�Դϴ�. \n", area);

	area = r2.get_area();
	printf("�簢���� ���̴� %d�Դϴ�. \n", area);
}
#endif

#if 0
/* C���� �Լ� �����͸� ����ü ������ ���� �ִٴ� �� */
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
	int (*p_add)(int a, int b); // �Լ� �����Ͱ� �ü� �ִ�.
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
/* ���� ������ priate, public, protected*/
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

/* �̰Ŵ� ������ Foo Ŭ������ �����Ƿ�, Ŭ���� �ȿ� ���ϴ� �ɷ� ģ��. */
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
/* static ����, Ŭ���� ���� */
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

int Foo::x = 88; // static ������ �̷��� ����?

int main() {
	Foo foo;

	foo.a = 33;
	foo.b = 44;

	Foo::sfunc1();
}
#endif

#if 0
/* static ������ ���ο� �ν��Ͻ��� �����ص� ���� ����Ǿ� �־ �����ȴ�? */

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
/* free�� �޸� ���� �� ���� ����? */
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

	free(my_car); // (1) �ڡڡ� �� �и��� free�� �ߴ�? �ߴٰ�!
	free(your_car);

	// ���⼭ ������ ���ܾߵǴµ�, �̰� �ǳ�?
	// free�� �Ѵٰ� �ؼ� �޸𸮰� �縮���� �� �ƴϴ�.
	// ���� �ٸ� �ְ� �ش� �޸𸮸� �������� ���ϵ��� ������ ���ִµ�, free�� �ع����� ������ �����ִ� �Ŵ�.
	// ��, free�� �� �� ���� ������ �� ���� ���� ���� �� ������, ������ �ȵȴ�. �����ϴ�. ��������.
	// �̷� ������ ������ �����Ϸ���? NULL���� �Ǵ�, free�� ���Ŀ��� nullptr�� �ʱ�ȭ.
	if (my_car != NULL) {
		my_car->fuel = 55; // (2) ���⼭ ���� ������ ��� �ɱ�?
		my_car->speed = 66;
	}

	my_car = nullptr;
	your_car = nullptr;

	printf("%d, %d\r\n", my_car->fuel, my_car->speed);

	return 0;
}
#endif

#if 0
/* this pointer? -> �ڱ� �ڽ��� ������ �����ִ� ��. */
// static �Լ������� ��ü�� ���� ���� �ֱ⿡ this�� ����� �� ����?
// this ������ �� ���???
class Point {
private:
	int x{ 0 };
	int y{ 0 };

public: 
	void set(int a, int b) {
		x = a;
		y = b;
		std::cout << this << std::endl; // pt1.set�� ������ ������. ��, �Լ��� ȣ���� �� ����� ��ü pt1, pt2�� �ּҸ� ����Ŵ.
	}
};

int main() {
	Point pt1;
	Point pt2;

	std::cout << &pt1 << std::endl;
	std::cout << &pt2 << std::endl;

	pt1.set(11, 22);	// ��ü pt1�� �ּ� ���
	pt2.set(33, 44);	// ��ü pt2�� �ּ� ���
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
	/* ���� ���� �� 
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
/* C++ ������ namespace�� �̿��Ͽ� ���� �̸��� �Լ� �Ǵ� ������ ������ �� �ִ�. */
// �� �ű��Ѱ� namespace�� ���������� �׳�/ ¯ �ű���
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
 * std:: ����
 * cout�̶� cin�� ���������� std::�� �����ϱ� ����
 * using namespace std; �� ���°Ŵ�.
 * ���� ���´�
 * std::cout << "Hello";
 */
#include <stdio.h>
#include <algorithm>

/* �̷��� ���� main���� std:: �� �����ص� �ȴ�. */
//using std::max;
//using std::min;

// using namespace std;	// �̰� �ᵵ �ȴ�.

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
/* �۷ι� ���ӽ����̽� */
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

void init() { printf("init global Module\r\n"); } // (1) �߰���

int main() {
	Video::init();
	Audio::init();
	init(); // (2)
	::init(); // (3)
}
#endif

#if 0
/* ��ø ���ӽ����̽� */
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
/* namespace ���� (��ø�� �� �ٿ��� �� �� ����.) */
std::filesystem::create_directories("c:/bts"); // (1)

namespace fs = std::filesystem; // (2) std::filesystem �̰� �ʹ� ��ϱ� ��Ī�� ������.
fs::create_directories("c:/exo");
#endif

#if 0
#include <iostream>

int main() {
	typedef int intger; // ����
	intger a = 111;
	std::cout << a << std::endl;

	using real_number = double;	// ����
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

	cout << "�� ���� ���ڴ� " << a << ", " <<  b << ", " << c << endl;

	cout << "����� ���̴� �� ���ΰ���? ";
	cin >> age;
	cout << "���� " << age << " �� �Դϴ�." << endl;

	cout << "���� 3���� �Է��ϼ���. ";
	cin >> a >> b >> c;
	sum = a + b + c;
	cout << "�� ������ ���� " << sum << " �Դϴ�." << endl;
}
#endif

#if 0
/* ����� ������, ���� �Ⱦ���. C�� ġ�� %5d, %.1f �� �̷���? */
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
	// �迭�� �ƴϴ�. Ư���� �����̳��� std::initializer_list<int>
	// initializer_list�� �����ϴ� being(), end �Լ� ����Ұ�
	//std::cout << x << std::endl; // �̷��� ����ϸ� �ȉ´�!
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
	int y1; // x2,y2�� �־� 2���� ������ ������, 
	// Ŭ���� �ʱ�ȭ�� �����̹Ƿ� x2, y2�� ����.
	rect(int a, int b) {
		x1 = a;
		y1 = b;
	}
};

int main(void) {
	// �ʱ�ȭ ����� �پ��ؼ� �򰥸���.
	int          a1 = 0;			//�⺻ ���������� =�����ڷ� �ʱ�ȭ, ��ȣ�� ����.
	struct point b1 = { 0,0 };		// ����ü�� �߰�ȣ
	int          c1[3] = { 11,22,33 };	// �迭�� �߰�ȣ
	rect         r1(1, 2);				// Ŭ������ �Ұ�ȣ

	int          a2 = { 0 };
	struct point b2 = { 0,0 };
	int          c2[3] = { 11,22,33 };
	rect         r2 = { 1,2 };

	int          a3{ 0 };
	int			 a4(11); // not good ������ ��Ÿ�Ϸ� �ʱ�ȭ �򰥸��ϱ� ������ ����
	struct point b3 { 0, 0 };
	//struct point b4(1, 2); // error
	int          c3[3]{ 11,22,33 };
	rect         r3{ 1,2 };
	rect         r4(1, 2);// ����ü�� �ȵ����� Ŭ������ ����
	return 0;
}
#endif

#include <cstdbool>

bool a = true;