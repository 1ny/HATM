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

	// ������ C ��Ĵ�� ����ϱ�
	for (int i = 0; i < 5; i++) {
		printf("%d, ", arr[i]);
	}
	std::cout << std::endl;

	// for each�� ����ϱ�
	std::for_each(arr, arr + 5, print_one);
	std::cout << std::endl;

	// ���� ��� for ���� ����ؼ� ����ϱ�
	for (int ele : arr) {
		std::cout << ele << ", ";
	}
	std::cout << std::endl;

	// ���� ��� for ���� ���۷����� ����ؼ� ����ϱ�
	for (const int& ele : arr) {
		std::cout << ele << ", ";
	}

	std::cout << std::endl;

	// std::for_each(arr, arr + 5, print_two); // error ���� �Լ��� �ü� �ִ�. 
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

	// ����� �����ڴ�.
	for (auto e : std::views::reverse(x)) { std::cout << e << ","; }
	std::cout << std::endl;

	// ������ �����ڴ�
	for (auto e : std::views::take(x, 3)) { std::cout << e << ","; }
	std::cout << std::endl;

	// 3���� ���� �����ڴ�.
	for (auto e : std::views::drop(x, 3)) { std::cout << e << ","; }
	std::cout << std::endl;

	//������ ������, 3���� �����ڴ�.
	for (auto e : std::views::reverse(std::views::take(x, 3))) { std::cout << e << ","; }
	std::cout << std::endl;

	// ���͸� �����ϰڴ�.
	// ���� �Լ��� ��ȯ���� boolian Ÿ������.
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
	int& ra = a; // (2) ra�� a�� ���ٰ� ���� �ȴ�.
	ra = 33;
	a = ra;	// �̰͵� �ȴ�.
	// �� reference�� �ٲ� �� ����? �������
	int b = 999;
	ra = b;
	// �ּҴ� �ȹٲ�µ�, ���� �ٲ��.
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
	std::string name = ""; // �׻� �ʱ�ȭ ��Ű�� ������ ������.

private:
	int age = 0;

public:
	void setAge(int a) {
		if (a <= 0 || a > 130) cout << "���̸� �߸� �Է���." << endl;
		else age = a;
		getAge();
	}
	int getAge() const {
		return age;
	}
};

int main() {
	Person p;
	p.name = "������";
	p.setAge(190);
	std::cout << p.name << "�� ���̴� " << p.getAge() << "�Դϴ�." << std::endl;
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

	cout << "�Է�: ";
	cin >> a;

	b.T[0].setName(a);
	b.T[0].getName();

}
#endif