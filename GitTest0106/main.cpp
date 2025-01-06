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
/*
 * C++�� OOP(��ü ����) Ư¡
 * 1. ĸ��ȭ -> ������, �Ⱥ����� �����ϴ� ���� �����ڰ� �ִ�. public/private(default) (+��������)
 * 2. ������
 * 3. ���
 * 4. �߻�ȭ
 * 
 * 
 * C���� �߿��Ѱ�? �Լ� ������, C�� ���������ε�, �Լ� �����ͷ� ��ü ������ �����ؼ�
 * ��ü ������ ������ �̿��� �� �ֱ� ����.
 * 
 * class vs struct
 * class������ �Լ��� Ŭ�����ȿ� �ֱ⵵ �Ѵ�.
 * 
 * Ŭ������ �ν��Ͻ� ����?
 * ����� ������ ���̴�. Ŭ������ �������� �޸� �Ҵ� X, �ν��Ͻ��� ���Ƿ� �޸� �Ҵ� O
 * �ν��Ͻ� : Foo foo;
 * 
 * Ŭ���� �������� ���� static ����, �� Ŭ���� ������ �ִ�. (static?)
 * 
 * ��� ������ �ν��Ͻ����� ������������, ����Լ��� ��� �ν��Ͻ��� �����Ѵ�.
 * �̰� ���Ҹ���. ��¥��?
 * 
 * Ŭ������ ���� or ��? -> ���ÿ� ����� ���� ����. ���� �޸� �����ϱ� �������ϱ�~~
 * C++������ ���� �Ҵ��ϴ� �� malloc ���� new �� �ִ�~
 * malloc - free  // new - delete
 * �ٵ� �ַ� new�� ���� -> ������ ȣ�� ����, �޸� ������ ����, ���� ó���� ����
 * malloc�� NULL ��ȯ�ؼ� NULL ó���� ����ߵȴ�
 * 
 * # �ν��Ͻ� ���� ���
 * Sample s1;	// �ַ� �̰� ��.
 * Sample* s2 = new Sample;
 * Sample* s3 = new Sample();	// �Լ��� �ƴѰ� Ȯ���ϴ�? �׷��� �����ϱ� ��.
 * 
 * this pointer -> �ؾ ���� ����? �ؾ �ڽ��� ����Ű�� ������?
 */


