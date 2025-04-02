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
		std::cout << "생성자 호출" << std::endl;
	}
	~Book() {
		std::cout << "소멸자 호출" << std::endl;
	}
	std::string getTitle() {
		return this->str;
	}
};

int main() {

	try {
		//원시 포인터를 직접 사용하는 경우
		auto pBook1 = new Book("채식주의자");
		std::cout << pBook1->getTitle() << std::endl;
		throw std::runtime_error("일부러 예외 발생시켜봄"); // (1)
		delete pBook1;
	}
	catch (const std::exception& e) {
		std::cerr << "Error" << e.what() << std::endl;

	}

	//// 객체 생성 및 소유권 부여를 한번에 처리하므로 위의 방법보다 좋다.
	//auto upBook2 = std::make_unique<Book>("소년이 온다.");
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
		// 스마트 포인터로 동적 메모리 관리
		auto mem = std::make_unique<std::vector<int>>(5); // 크기 5인 벡터 생성

		// 값 저장
		for (size_t i = 0; i < mem->size(); ++i) {
			(*mem)[i] = static_cast<int>(i * 10);
		}

		// 값 출력
		//throw std::runtime_error("일부러 예외 발생시켜봄"); // (1)
		for (size_t i = 0; i < mem->size(); ++i) {
			std::cout << "mem[" << i << "] = " << (*mem)[i] << std::endl;
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	// 스마트 포인터가 스코프를 벗어나면서 자동으로 메모리를 해제
	return 0;
}
#endif

#if 0
#include <iostream>
#include <memory>

int main() {
	int* ptr = new int(10);
	//delete ptr;

	// 메모리 해제했는데 ptr에 접근할 경우 문제 발생
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
	// upb = upa;   // error! 복사 불가능!
	upb = std::move(upa);   // 이동은 가능하다.
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
		std::cout << "소멸자 호출" << std::endl;
	}

};

int main() {
	Person p1("david", 30);
	Person p2{ p1 }; // 삭제가 이미 되었는데, 또 삭제하려고 하기 때문에 얕은 복사의 문제점 발생
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
	//upb = upa;   // error! 복사 불가능!
	//upb = std::move(upa);   // 이동은 가능하다.
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
/* 나만의 스마트포인터 with 참조 계수 counter*/
class Book {
public:
	std::string str;
	Book(std::string str) : str{ str } {
		std::cout << "생성자 호출" << std::endl;
	}
	~Book() {
		std::cout << "소멸자 호출" << std::endl;
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
/* 스레드 1개로 소수 구하기 */
#include <iostream>
#include <vector>
#include <cmath>
#include <chrono> // 실행 시간 측정을 위한 헤더

// 소수 판별 함수
bool isPrime(int n) {
	if (n <= 1) return false;
	for (int i = 2; i <= std::sqrt(n); ++i) {
		if (n % i == 0) return false;
	}
	return true;
}

// 소수 찾기 작업
void findPrimes(int start, int end, std::vector<int>& primes) {
	for (int i = start; i <= end; ++i) {
		if (isPrime(i)) {
			primes.push_back(i);
		}
	}
}

int main() {
	int rangeStart = 1, rangeEnd = 10000000; // 계산 범위

	// 결과를 저장할 벡터
	std::vector<int> primes;

	// 실행 시간 측정 시작
	auto startTime = std::chrono::high_resolution_clock::now();

	// 단일 스레드로 소수 찾기
	findPrimes(rangeStart, rangeEnd, primes);

	// 실행 시간 측정 종료
	auto endTime = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

	// 결과 출력
	std::cout << "Total primes found: " << primes.size() << "\n";
	std::cout << "Execution time: " << duration.count() << " ms\n";

	return 0;
}

#endif

#if 0
/* 스레드 5개로 소수 구하기 */
#include <iostream>
#include <vector>
#include <cmath>
#include <thread>
#include <mutex>
#include <chrono> // 실행 시간 측정을 위한 헤더

// 소수 판별 함수
bool isPrime(int n) {
	if (n <= 1) return false;
	for (int i = 2; i <= std::sqrt(n); ++i) {
		if (n % i == 0) return false;
	}
	return true;
}

// 뮤텍스를 사용해 벡터 접근 동기화
std::mutex mtx;

// 소수 찾기 작업
void findPrimes(int start, int end, std::vector<int>& primes) {
	std::vector<int> localPrimes; // 각 스레드에서 사용할 로컬 벡터
	for (int i = start; i <= end; ++i) {
		if (isPrime(i)) {
			localPrimes.push_back(i);
		}
	}

	// 결과를 메인 벡터에 병합 (뮤텍스 사용)
	std::lock_guard<std::mutex> lock(mtx);
	primes.insert(primes.end(), localPrimes.begin(), localPrimes.end());
}

int main() {
	int rangeStart = 1, rangeEnd = 10000000; // 계산 범위
	int numThreads = 1000; // 사용할 스레드 수
	int rangePerThread = (rangeEnd - rangeStart + 1) / numThreads;

	// 결과를 저장할 벡터
	std::vector<int> primes;

	// 스레드 벡터
	std::vector<std::thread> threads;

	// 실행 시간 측정 시작
	auto startTime = std::chrono::high_resolution_clock::now();

	// 스레드 생성 및 작업 분배
	for (int i = 0; i < numThreads; ++i) {
		int start = rangeStart + i * rangePerThread;
		int end = (i == numThreads - 1) ? rangeEnd : start + rangePerThread - 1;
		threads.emplace_back(findPrimes, start, end, std::ref(primes));
	}

	// 모든 스레드가 완료될 때까지 대기
	for (auto& t : threads) {
		t.join();
	}

	// 실행 시간 측정 종료
	auto endTime = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

	// 결과 출력
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
	// 현재 시각을 얻어오고 start로 저장 예를 들어 12시00분00초
	std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
	Test();
	// 현재 시각을 얻어오고, 12시00분02초 - 위의 시간을 빼면 함수 수행시간
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

	// 생성된 스레드의 ID 가져오기
	std::cout << "Created Thread ID: " << t.get_id() << "\n";

	t.join(); // 스레드 종료 대기
	return 0;
}
#endif

#if 1
#include <iostream>
#include <thread>

void task1(const std::string& name) {
	for (int i = 0; i < 5; ++i) {
		std::cout << name << " 가 작업을 수행중입니다." << i << "\n";
		std::this_thread::yield(); // 다른 스레드에게 CPU 양보
	}
}

void task2(const std::string& name) {
	for (int i = 0; i < 5; ++i) {
		std::cout << name << " 가 작업을 수행중입니다." << i << "\n";
		 std::this_thread::yield(); // 다른 스레드에게 CPU 양보 (1)
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

