## thread 의 생성과 종료
```cs
#include <iostream>
#include <thread> // (1) thread 헤더가 필요하다.

void bts() { // (2) 함수를 하나 만들고
	std::cout << "bts " << std::endl;
}

int main() {
	std::cout << "thread started." << std::endl;
	std::thread th1(&bts); // (2) 스레드 생성자에 함수로 전달하면 끗이다.
	th1.join(); // (3) 스레드 종료, 스레드가 끝날때까지 기다린다.
	std::cout << "thread terminated." << std::endl;

	return 0;
}
```
### 스레드 종료 (join, detach, stop, terminate...)
#### <span style='background-color:yellow'>join vs detach</span>
- - 스레드를 종료하기 전에 main 함수가 끝나면 main 함수는 해당 스레드가 완료되기를 기다리지 않고 그냥 종료해버려서 런타임 예외가 발생한다.  
- join은 스레드가 종료되기를 main 함수가 기다리는 것!  
- join 말고 detach를 사용하여 main 이 해당 스레드를 관리하지 않도록 할 수도 있다.  
detach는 해당 스레드가 main 스레드와 분리되어 독립적으로 실행하게 된다?  
해당 스레드(th1) 가 언제 완료되는 지를 신경써야 한다.  
```cs
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
}
```
- detach 보단, join이 더 좋다.

#### <span style='background-color:yellow'> stop & terminate</span>
- 스레드 강제 종료. 되도록 쓰지 말자.  

## 동시성 vs 병렬성
- 동시성은 동시에 실행된다는 게 아니라,  
싱글코어에서 여러 작업을 분할하여 실행하는 것을 동시에 실행하는 것처럼 보이는 것.  
- 병렬성은 실제로 멀티코어로 여러 작업을 동시에 실행할 수 있음.  

## 멀티스레드의 장단점
- 빨라질 수도 있다. (단, 피보나치 수열 같이 연산 관계의 의존도가 높은 경우는 그렇지 않음.)
- 응답성이 빠름.

## 스레드의 파라미터
```cs
typdef struct {
	int x;
	int y;
} Point;

void f1() {...}
void f2(int a, int b) {...}
void f3(Point& point, int a, int b) {...}

int main() {
	Point point = {1, 2};

	std::thread th1(&f1);
	std::thread th2(&f2, 11, 22);
	std::thread th3(&f3, std::ref(point), 33, 44);
}
```

## 시간 관련 라이브러리, chrono
```cs
std::chrono::hours			h(12);
std::chrono::minutes		m(34);
std::chrono::seconds		s1(56);
std::chrono::milliseconds	s2(11);
std::chrono::nanoseconds	s3(22);

cout << h.count() << endl;
```

```cs
// 함수 실행 시간
std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
func();	// 어떤 함수 실행
std::chrono::duration<double> sec =	std::chrono::system_clock::now() - start;
std::cout << "time: " << sec.count() << " seconds" << std::endl;
```

```cs
/* prefix 변환도 가능~! */
std::chrono::duration<double> default_sec = end_time - start_time;
std::chrono::nanoseconds  ns   = end_time - start_time;
std::chrono::microseconds us   = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
std::chrono::milliseconds ms   = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
std::chrono::seconds      sec  = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time);
std::chrono::minutes      min  = std::chrono::duration_cast<std::chrono::minutes>(end_time - start_time);
std::chrono::hours        hour = std::chrono::duration_cast<std::chrono::hours>(end_time - start_time);
std::cout << "time(default:sec) : " << default_sec.count() << " sec(=default)" << std::endl;
std::cout << "time(ns)          : " << ns.count()  << " ns" << std::endl;
std::cout << "time(us)          : " << us.count()  << " us" << std::endl;
std::cout << "time(ms)          : " << ms.count()  << " ms" << std::endl;
std::cout << "time(sec)         : " << sec.count() << " sec" << std::endl;
std::cout << "time(min)         : " << min.count() << " min" << std::endl;
std::cout << "time(hour)        : " << hour.count()<< " hour" << std::endl;
```
```cs
sleep_for(std::chrono::seconds(n)) // n초 동안 자라
sleep_for(몇ms)	// prefix로 적어도 됨.
```

## 멀티 스레드
그냥 두 개 만들면 됨.
```cs
int main() {
	std::thread th1(&bts);
	std::thread th2(&exo);

	th1.join();
	th2.join();

	return (0);
}
```
## 관련 라이브러리
### get_id, 스레드 식별자 get
- thread::get_id : 해당 스레드의 식별자  
- this_thread::get_id : 현재 실행중인 스레드의 식별자  
- thread::sleep_for ; 지정된 시간 동안 일시 정지
- thread::sleep_until ; 특정 시간까지 일시 정지  
- this_thread::yield ; 해당 스레드가 CPU를 다른 스레드에게 양보하도록 함.
```cs
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
        // std::this_thread::yield(); // 다른 스레드에게 CPU 양보 (1)
    }
}

int main() {
    std::thread t1(task1, "Thread 1");
    std::thread t2(task2, "Thread 2");

    t1.join();
    t2.join();

    return 0;
}
```

MCU는 내부 타이머(GPT랑은 다른건가? 다르대. tick은 systick timer 로 보통 생성한대.)를 (tick) 가지고 있어서 그 일정 시간 안에 처리를 하는데,  
우선순위에 따라 수행하는데, tick 범위를 벗어나는 일은 영원히 못할 수도 있다.
반면, CPU는 우선순위가 낮아서 실행을 못했던 일일수록 우선순위를 높여줘서 결국 실행할 수 있게 해줌.

MCU는 대부분 Round Robin 스케줄링 방식을 사용한다.

### Race condition
#### 해결방법 -> atomic operation 보장
- MUTEX  
lock(), unlock()  
c++ 에서는 lock guard가 있어서 unlock을 안하면 제대로 동작 X
unique_lock (like unique_ptr)

### 데드락 문제 -> 그 교차로에서 교착상태

---

## C++ 형변환
- static_cast
- dynamic_cast
- reinterpret_cast
- const_cast

보통 static이랑 dynamic을 많이 사용한다.  

