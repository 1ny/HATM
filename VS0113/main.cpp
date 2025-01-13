#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

#if 0
int main() {
	std::unique_ptr<int> smart_ptr(new int(11));
	std::cout << *smart_ptr << std::endl;
	return 0;
}
#endif

#if 0
#include <iostream>
#include <memory>
#include <typeinfo>

class Book {
public:
	std::string str;
	Book(std::string str) : str{ str } {
		std::cout << "������ ȣ��" << std::endl;
	}
	~Book() {
		std::cout << "�Ҹ��� ȣ��" << std::endl;
	}
	std::string getTitle() {
		return this->str;
	}
};

int main() {

	try {
		//���� �����͸� ���� ����ϴ� ���
		auto pBook1 = new Book("ä��������");
		std::cout << pBook1->getTitle() << std::endl;
		throw std::runtime_error("�Ϻη� ���� �߻����Ѻ�"); // (1)
		delete pBook1;
	}
	catch (const std::exception& e) {
		std::cerr << "Error" << e.what() << std::endl;

	}

	//// ��ü ���� �� ������ �ο��� �ѹ��� ó���ϹǷ� ���� ������� ����.
	//auto upBook2 = std::make_unique<Book>("�ҳ��� �´�.");
	//std::cout << upBook2->getTitle() << std::endl;

	return 0;
}

#endif

#if 0
#include <iostream>
#include <memory>
#include <vector>

int main() {
	try {
		// ����Ʈ �����ͷ� ���� �޸� ����
		auto mem = std::make_unique<std::vector<int>>(5); // ũ�� 5�� ���� ����

		// �� ����
		for (size_t i = 0; i < mem->size(); ++i) {
			(*mem)[i] = static_cast<int>(i * 10);
		}

		// �� ���
		//throw std::runtime_error("�Ϻη� ���� �߻����Ѻ�"); // (1)
		for (size_t i = 0; i < mem->size(); ++i) {
			std::cout << "mem[" << i << "] = " << (*mem)[i] << std::endl;
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	// ����Ʈ �����Ͱ� �������� ����鼭 �ڵ����� �޸𸮸� ����
	return 0;
}
#endif

#if 0
#include <iostream>
#include <memory>

int main() {
	int* ptr = new int(10);
	//delete ptr;

	// �޸� �����ߴµ� ptr�� ������ ��� ���� �߻�
	*ptr = 20;
	std::unique_ptr<int> smart_ptr(new int (11));
	std::cout << *ptr << std::endl;
	return 0;
}
#endif

#if 0
#include <iostream>
#include <memory>

int main() {

	int a = 11;
	auto upa = std::make_unique<int>(a);

	int b = 22;
	auto upb = std::make_unique<int>(b);
	// upb = upa;   // error! ���� �Ұ���!
	upb = std::move(upa);   // �̵��� �����ϴ�.
	std::cout << *upb << std::endl;

	std::cout << upa << std::endl;
	std::cout << upb << std::endl;

	return 0;
}
#endif

#if 0
#include <iostream>

class Person {
public:
	char* name; // string name;
	int age;


	Person(const char* n, int a) : age{ a } {
		name = new char[strlen(n) + 1];
		strcpy(name, n);
	}

	Person(const Person& p) : age{ p.age } {
		age = p.age;
		name = p.name;
	}

	~Person() {
		delete[] name;
		std::cout << "�Ҹ��� ȣ��" << std::endl;
	}

};

int main() {
	Person p1("david", 30);
	Person p2{ p1 }; // ������ �̹� �Ǿ��µ�, �� �����Ϸ��� �ϱ� ������ ���� ������ ������ �߻�
	return 0;
}
#endif

#if 0
#include <iostream>
#include <memory>

int main() {

	int a = 11;
	auto upa = std::make_unique<int>(a);

	int b = 22;
	auto upb = std::make_unique<int>(a);
	//upb = upa;   // error! ���� �Ұ���!
	//upb = std::move(upa);   // �̵��� �����ϴ�.
	//std::cout << *upb << std::endl;

	std::cout << upa << std::endl;
	std::cout << upb << std::endl;

	return 0;
}
#endif

#if 0
int main() {
	int a = 11;
	int* pa;
	int* pb;

	pa = &a;
	pb = pa;
}
#endif

#if 0
/* ������ ����Ʈ������ with ���� ��� counter*/
class Book {
public:
	std::string str;
	Book(std::string str) : str{ str } {
		std::cout << "������ ȣ��" << std::endl;
	}
	~Book() {
		std::cout << "�Ҹ��� ȣ��" << std::endl;
	}
};

template <class T>
class MySmartPointer {
private:
	T* ptr;
	int* ref;

public:
	MySmartPointer(T* ptr) : ptr(nullptr), ref(new int(1)) {}
	MySmartPointer(const MySmartPointer& p) : ptr(p.ptr) {
		this.ref = p.ref;
		this.ref++;
	}

	!MySmartPointer() {
		if (this.ref == 0) {
			delete ptr;
		}
	}
};

int main() {
	MySmartPointer<Book> b1 = new Book("abc");
	MySmartPointer<Book> b2 = new Book("def");
	b1 = b2;
	//cout << b1->str << 
}
#endif

#if 0
/* ������ 1���� �Ҽ� ���ϱ� */
#include <iostream>
#include <vector>
#include <cmath>
#include <chrono> // ���� �ð� ������ ���� ���

// �Ҽ� �Ǻ� �Լ�
bool isPrime(int n) {
	if (n <= 1) return false;
	for (int i = 2; i <= std::sqrt(n); ++i) {
		if (n % i == 0) return false;
	}
	return true;
}

// �Ҽ� ã�� �۾�
void findPrimes(int start, int end, std::vector<int>& primes) {
	for (int i = start; i <= end; ++i) {
		if (isPrime(i)) {
			primes.push_back(i);
		}
	}
}

int main() {
	int rangeStart = 1, rangeEnd = 10000000; // ��� ����

	// ����� ������ ����
	std::vector<int> primes;

	// ���� �ð� ���� ����
	auto startTime = std::chrono::high_resolution_clock::now();

	// ���� ������� �Ҽ� ã��
	findPrimes(rangeStart, rangeEnd, primes);

	// ���� �ð� ���� ����
	auto endTime = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

	// ��� ���
	std::cout << "Total primes found: " << primes.size() << "\n";
	std::cout << "Execution time: " << duration.count() << " ms\n";

	return 0;
}

#endif

#if 0
/* ������ 5���� �Ҽ� ���ϱ� */
#include <iostream>
#include <vector>
#include <cmath>
#include <thread>
#include <mutex>
#include <chrono> // ���� �ð� ������ ���� ���

// �Ҽ� �Ǻ� �Լ�
bool isPrime(int n) {
	if (n <= 1) return false;
	for (int i = 2; i <= std::sqrt(n); ++i) {
		if (n % i == 0) return false;
	}
	return true;
}

// ���ؽ��� ����� ���� ���� ����ȭ
std::mutex mtx;

// �Ҽ� ã�� �۾�
void findPrimes(int start, int end, std::vector<int>& primes) {
	std::vector<int> localPrimes; // �� �����忡�� ����� ���� ����
	for (int i = start; i <= end; ++i) {
		if (isPrime(i)) {
			localPrimes.push_back(i);
		}
	}

	// ����� ���� ���Ϳ� ���� (���ؽ� ���)
	std::lock_guard<std::mutex> lock(mtx);
	primes.insert(primes.end(), localPrimes.begin(), localPrimes.end());
}

int main() {
	int rangeStart = 1, rangeEnd = 10000000; // ��� ����
	int numThreads = 1000; // ����� ������ ��
	int rangePerThread = (rangeEnd - rangeStart + 1) / numThreads;

	// ����� ������ ����
	std::vector<int> primes;

	// ������ ����
	std::vector<std::thread> threads;

	// ���� �ð� ���� ����
	auto startTime = std::chrono::high_resolution_clock::now();

	// ������ ���� �� �۾� �й�
	for (int i = 0; i < numThreads; ++i) {
		int start = rangeStart + i * rangePerThread;
		int end = (i == numThreads - 1) ? rangeEnd : start + rangePerThread - 1;
		threads.emplace_back(findPrimes, start, end, std::ref(primes));
	}

	// ��� �����尡 �Ϸ�� ������ ���
	for (auto& t : threads) {
		t.join();
	}

	// ���� �ð� ���� ����
	auto endTime = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

	// ��� ���
	std::cout << "Total primes found: " << primes.size() << "\n";
	std::cout << "Execution time: " << duration.count() << " ms\n";

	return 0;
}

#endif

#if 0
#include <thread>

void bts() {
	for (int i = 0; i < 5; i++) {
		std::cout << "bts: " << +i << std::endl;
		std::this_thread::sleep_for(100ms);
	}
}

int main() {
	cout << "thread started." << endl;
	thread th1(&bts);
	//th1.join();
	th1.detach();
	this_thread::sleep_for(3s);
	cout << "thread terminated." << endl;

	vector<thread> threads;
}
#endif

#if 0
#include <chrono>
#include <iostream>
#include <cmath>

void Test() {
	long double dummy = 0.0;
	for (long i = 0; i < 10000000; ++i) {
		dummy = std::sqrt(123.456L);
	}
}

int main() {
	// ���� �ð��� ������ start�� ���� ���� ��� 12��00��00��
	std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
	Test();
	// ���� �ð��� ������, 12��00��02�� - ���� �ð��� ���� �Լ� ����ð�
	std::chrono::duration<double> sec = std::chrono::system_clock::now() - start;
	std::cout << "time: " << sec.count() << " seconds" << std::endl;
	return 0;
}
#endif

#if 0
#include <chrono>
#include <iostream>
#include <cmath>
#include <thread>

void bts() {
	std::cout << "bts() called" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));
}

//void exo() {
//	std::cout << "exo() called" << std::endl;
//	std::this_thread::sleep_for(std::chrono::seconds(2));
//}

int main() {
	while (true) {
		bts(); // 1sec
		//exo(); // 2sec
	}
	return (0);
}
#endif

#if 0
#include <chrono>
#include <iostream>
#include <cmath>
void dummy_test() {
	long double dummy_ret = 0.0;
	for (long i = 0; i < 10000000; ++i) {
		dummy_ret = std::sqrt(123.456L);
	}
}
int main() {
	std::chrono::system_clock::time_point start_time = std::chrono::system_clock::now();
	dummy_test();
	std::chrono::system_clock::time_point end_time = std::chrono::system_clock::now();

	std::chrono::duration<double> default_sec = end_time - start_time;
	std::chrono::nanoseconds  ns = end_time - start_time;
	std::chrono::microseconds us = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
	std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
	std::chrono::seconds      sec = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time);
	std::chrono::minutes      min = std::chrono::duration_cast<std::chrono::minutes>(end_time - start_time);
	std::chrono::hours        hour = std::chrono::duration_cast<std::chrono::hours>(end_time - start_time);
	std::cout << "time(default:sec) : " << default_sec.count() << " sec(=default)" << std::endl;
	std::cout << "time(ns)          : " << ns.count() << " ns" << std::endl;
	std::cout << "time(us)          : " << us.count() << " us" << std::endl;
	std::cout << "time(ms)          : " << ms.count() << " ms" << std::endl;
	std::cout << "time(sec)         : " << sec.count() << " sec" << std::endl;
	std::cout << "time(min)         : " << min.count() << " min" << std::endl;
	std::cout << "time(hour)        : " << hour.count() << " hour" << std::endl;

	return (0);
}
#endif

#if 0
#include <iostream>
#include <thread>
#include <chrono>

using namespace std::literals;

struct Point {
	int x;
	int y;
};

void bts(int a, int b) {
	std::cout << a << "," << b << std::endl;
	for (int i = 0; i < 10; i++) {
		std::cout << "bts: " << +(i + 1) << std::endl;
		std::this_thread::sleep_for(200ms);
	}
}

void exo(Point& point, int a, int b) {
	std::cout << point.x << "," << point.y << std::endl;
	std::cout << a << "," << b << std::endl;
	for (int i = 0; i < 10; i++) {
		std::cout << "exo: " << +(i + 1) << std::endl;
		std::this_thread::sleep_for(200ms);
	}
}

int main() {
	std::thread th1(&bts, 11, 22);

	Point point = { 111,222 };
	//std::thread th2(&exo, point, 33, 44); error
	std::thread th2(&exo, std::ref(point), 33, 44);

	th1.join();
	th2.join();

	return (0);
}
#endif

#if 0
#include <iostream>
#include <thread>

void func() {
	std::cout << "Thread Function is running.ID:" << std::this_thread::get_id() << "\n";
}

int main() {
	std::thread t(func);

	// ������ �������� ID ��������
	std::cout << "Created Thread ID: " << t.get_id() << "\n";

	t.join(); // ������ ���� ���
	return 0;
}
#endif

#if 1
#include <iostream>
#include <thread>

void task1(const std::string& name) {
	for (int i = 0; i < 5; ++i) {
		std::cout << name << " �� �۾��� �������Դϴ�." << i << "\n";
		std::this_thread::yield(); // �ٸ� �����忡�� CPU �纸
	}
}

void task2(const std::string& name) {
	for (int i = 0; i < 5; ++i) {
		std::cout << name << " �� �۾��� �������Դϴ�." << i << "\n";
		 std::this_thread::yield(); // �ٸ� �����忡�� CPU �纸 (1)
	}
}

int main() {
	std::thread t1(task1, "Thread 1");
	std::thread t2(task2, "Thread 2");

	t1.join();
	t2.join();

	return 0;
}
#endif

#if 1

#endif

