#include <iostream>

using namespace std;

#if 0
inline int sum(int a, int b) {
	return a + b;
}

int main() {
	int r = sum(2, 3);

	cout << r << endl;
}
#endif

#if 0
/*
int square(int a) {
	return a * a;
}

double square(double a) {
	return a * a;
}
*/

template<typename Hey>
Hey square(Hey a) {
	return a * a;
}

int main() {
	/*
	int a = square(3);
	double b = square(3.2);

	cout << a << endl;
	cout << b << endl;
	*/

	int c = square<int>(2);
	double d = square<double>(3.2);
	cout << c << endl;
	cout << d << endl;

	return 0;
}
#endif

#if 0
#include <iostream>
#include <algorithm>

void print_one(int one) {
	std::cout << one << ", ";
}

void print_two(int one, int two) {
	std::cout << one << "," << two << std::endl;
}

int main(void) {
	int arr[5] = { 2,3,1,4,5 };

	// 기존의 C 방식대로 출력하기
	for (int i = 0; i < 5; i++) {
		printf("%d, ", arr[i]);
	}
	std::cout << std::endl;

	// for each로 출력하기
	std::for_each(arr, arr + 5, print_one);
	std::cout << std::endl;

	// 범위 기반 for 문을 사용해서 출력하기
	for (int ele : arr) {
		std::cout << ele << ", ";
	}
	std::cout << std::endl;

	// 범위 기반 for 문과 레퍼런스를 사용해서 출력하기
	for (const int& ele : arr) {
		std::cout << ele << ", ";
	}

	std::cout << std::endl;

	// std::for_each(arr, arr + 5, print_two); // error 단항 함수만 올수 있다. 
	return 0;
}
#endif

#if 0
#include <iostream>
#include <algorithm>
#include <ranges>

bool is_odd(int a) {
	return ((a % 2) == 1);

}

int main(void) {
	int x[5] = { 1,2,3,4,5 };

	for (auto e : x) { std::cout << e << ","; }
	std::cout << std::endl;

	// 뒤집어서 꺼내겠다.
	for (auto e : std::views::reverse(x)) { std::cout << e << ","; }
	std::cout << std::endl;

	// 세개만 꺼내겠다
	for (auto e : std::views::take(x, 3)) { std::cout << e << ","; }
	std::cout << std::endl;

	// 3개를 빼고 꺼내겠다.
	for (auto e : std::views::drop(x, 3)) { std::cout << e << ","; }
	std::cout << std::endl;

	//뒤집은 다음에, 3개만 꺼내겠다.
	for (auto e : std::views::reverse(std::views::take(x, 3))) { std::cout << e << ","; }
	std::cout << std::endl;

	// 필터를 적용하겠다.
	// 필터 함수의 반환값은 boolian 타입으로.
	for (auto e : std::views::filter(x, is_odd)) { std::cout << e << ","; }
	std::cout << std::endl;

	return (0);
}
#endif


#if 0
template<class T>
void swap(T* a, T* b) {
	T temp = 0;

	temp = *a;
	*a = *b;
	*b = temp;
}

template<class T>
void swap_ref(T& a, T& b) {
	T temp = 0;

	temp = a;
	a = b;
	b = temp;
}

void swap(int* a, int* b) {
	int temp = 0;

	temp = *a;
	*a = *b;
	*b = temp;
}

int main() {
	int a, b;
	double c, d;

	a = 11;
	b = 22;

	c = 1.1;
	d = 2.2;

	cout << "(a,b)=" << "(" << a << ", " << b << ")" << endl;
	cout << "(c,d)=" << "(" << c << ", " << d << ")" << endl;

	//swap_test(a, b);
	swap<int>(&a, &b);
	//swap<double>(&c, &d);
	swap_ref<double>(c, d);
	
	cout << "(a,b)=" << "(" << a << ", " << b << ")" << endl;
	cout << "(c,d)=" << "(" << c << ", " << d << ")" << endl;

	return 0;
}
#endif

#if 0
int main() {
	int a = 11;
	int* pa = &a; // pass by address
	*pa = 22;	// pass by value
	std::cout << "a=" << a << std::endl;
	std::cout << "*pa=" << *pa << std::endl;
	std::cout << "&a=" << &a << std::endl; 
	std::cout << "&pa=" << &pa << std::endl;
	std::cout << std::endl;

	// pass by reference
	int& ra = a; // (2) ra와 a는 같다고 보면 된다.
	ra = 33;
	a = ra;	// 이것도 된다.
	// 엥 reference는 바꿀 수 없어? 레전드네
	int b = 999;
	ra = b;
	// 주소는 안바뀌는데, 값은 바뀌네.
	std::cout << "&a=" << &a << std::endl; // 33
	std::cout << "&b=" << &b << std::endl; // 33
	std::cout << "&ra=" << &ra << std::endl; // 33
	std::cout << "ra=" << ra << std::endl; // 33
	std::cout << "a=" << a << std::endl; // 33
	std::cout << std::endl;
	return 0;
}
#endif

#if 0
#include <iostream>
#include <string>

class Person {
public:
	std::string name = ""; // 항상 초기화 시키는 습관을 들이자.

private:
	int age = 0;

public:
	void setAge(int a) {
		if (a <= 0 || a > 130) cout << "나이를 잘못 입력함." << endl;
		else age = a;
		getAge();
	}
	int getAge() const {
		return age;
	}
};

int main() {
	Person p;
	p.name = "정예림";
	p.setAge(190);
	std::cout << p.name << "의 나이는 " << p.getAge() << "입니다." << std::endl;
	return 0;
}
#endif

#if 1
class Test {
private:
	string name;

public:
	void setName(string pName) {
		this->name = pName;
	}
	void getName() {
		cout << name << endl;
	}
};

class Big {
public:
	Test T[5];
};

int main() {
	Big b;
	string a;

	cout << "입력: ";
	cin >> a;

	b.T[0].setName(a);
	b.T[0].getName();

}
#endif