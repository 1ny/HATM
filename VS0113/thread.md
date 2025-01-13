## thread �� ������ ����
```cs
#include <iostream>
#include <thread> // (1) thread ����� �ʿ��ϴ�.

void bts() { // (2) �Լ��� �ϳ� �����
	std::cout << "bts " << std::endl;
}

int main() {
	std::cout << "thread started." << std::endl;
	std::thread th1(&bts); // (2) ������ �����ڿ� �Լ��� �����ϸ� ���̴�.
	th1.join(); // (3) ������ ����, �����尡 ���������� ��ٸ���.
	std::cout << "thread terminated." << std::endl;

	return 0;
}
```
### ������ ���� (join, detach, stop, terminate...)
#### <span style='background-color:yellow'>join vs detach</span>
- - �����带 �����ϱ� ���� main �Լ��� ������ main �Լ��� �ش� �����尡 �Ϸ�Ǳ⸦ ��ٸ��� �ʰ� �׳� �����ع����� ��Ÿ�� ���ܰ� �߻��Ѵ�.  
- join�� �����尡 ����Ǳ⸦ main �Լ��� ��ٸ��� ��!  
- join ���� detach�� ����Ͽ� main �� �ش� �����带 �������� �ʵ��� �� ���� �ִ�.  
detach�� �ش� �����尡 main ������� �и��Ǿ� ���������� �����ϰ� �ȴ�?  
�ش� ������(th1) �� ���� �Ϸ�Ǵ� ���� �Ű��� �Ѵ�.  
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
- detach ����, join�� �� ����.

#### <span style='background-color:yellow'> stop & terminate</span>
- ������ ���� ����. �ǵ��� ���� ����.  

## ���ü� vs ���ļ�
- ���ü��� ���ÿ� ����ȴٴ� �� �ƴ϶�,  
�̱��ھ�� ���� �۾��� �����Ͽ� �����ϴ� ���� ���ÿ� �����ϴ� ��ó�� ���̴� ��.  
- ���ļ��� ������ ��Ƽ�ھ�� ���� �۾��� ���ÿ� ������ �� ����.  

## ��Ƽ�������� �����
- ������ ���� �ִ�. (��, �Ǻ���ġ ���� ���� ���� ������ �������� ���� ���� �׷��� ����.)
- ���伺�� ����.

## �������� �Ķ����
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

## �ð� ���� ���̺귯��, chrono
```cs
std::chrono::hours			h(12);
std::chrono::minutes		m(34);
std::chrono::seconds		s1(56);
std::chrono::milliseconds	s2(11);
std::chrono::nanoseconds	s3(22);

cout << h.count() << endl;
```

```cs
// �Լ� ���� �ð�
std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
func();	// � �Լ� ����
std::chrono::duration<double> sec =	std::chrono::system_clock::now() - start;
std::cout << "time: " << sec.count() << " seconds" << std::endl;
```

```cs
/* prefix ��ȯ�� ����~! */
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
sleep_for(std::chrono::seconds(n)) // n�� ���� �ڶ�
sleep_for(��ms)	// prefix�� ��� ��.
```

## ��Ƽ ������
�׳� �� �� ����� ��.
```cs
int main() {
	std::thread th1(&bts);
	std::thread th2(&exo);

	th1.join();
	th2.join();

	return (0);
}
```
## ���� ���̺귯��
### get_id, ������ �ĺ��� get
- thread::get_id : �ش� �������� �ĺ���  
- this_thread::get_id : ���� �������� �������� �ĺ���  
- thread::sleep_for ; ������ �ð� ���� �Ͻ� ����
- thread::sleep_until ; Ư�� �ð����� �Ͻ� ����  
- this_thread::yield ; �ش� �����尡 CPU�� �ٸ� �����忡�� �纸�ϵ��� ��.
```cs
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
        // std::this_thread::yield(); // �ٸ� �����忡�� CPU �纸 (1)
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

MCU�� ���� Ÿ�̸�(GPT���� �ٸ��ǰ�? �ٸ���. tick�� systick timer �� ���� �����Ѵ�.)�� (tick) ������ �־ �� ���� �ð� �ȿ� ó���� �ϴµ�,  
�켱������ ���� �����ϴµ�, tick ������ ����� ���� ������ ���� ���� �ִ�.
�ݸ�, CPU�� �켱������ ���Ƽ� ������ ���ߴ� ���ϼ��� �켱������ �����༭ �ᱹ ������ �� �ְ� ����.

MCU�� ��κ� Round Robin �����ٸ� ����� ����Ѵ�.

### Race condition
#### �ذ��� -> atomic operation ����
- MUTEX  
lock(), unlock()  
c++ ������ lock guard�� �־ unlock�� ���ϸ� ����� ���� X
unique_lock (like unique_ptr)

### ����� ���� -> �� �����ο��� ��������

---

## C++ ����ȯ
- static_cast
- dynamic_cast
- reinterpret_cast
- const_cast

���� static�̶� dynamic�� ���� ����Ѵ�.  

