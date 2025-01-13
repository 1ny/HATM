## 스마트 포인터
- 자동 메모리 해제 (delete 없이)   
    - main 함수 또는 함수 ( {}로 묶인 거 ) 끝날 때
    - (Scope 벗어날 때) 소멸자 호출될 때
    - exception 발생할 때
    - delete 하지 않아도 자동 메모리 해제
    - etc.
- 기존 포인터는 원시포인터라고 부른다.
```cs
#include <iostream>
#include <memory>

int main() {
	std::unique_ptr<int> smart_ptr(new int (11));
	std::cout << *smart_ptr << std::endl;
	return 0;
}
```
main 함수가 끝나면 스마트포인터 smart_ptr이 사라지면서 자동으로 동적 메모리를 해제한다.  

### 종류
- std::unique_ptr
    - 단일 소유권   
	(복사가 불가능하다. 즉, 서로 다른 unique_ptr 포인터가 같은 주소를 가질 수 없음을 의미? 같은 주소를 가리킬 수는 있음.)  
    - 복사 불가능, 이동만 가능
```cs
#include <iostream>
#include <memory>

int main() {

	int a = 11;
	auto upa = std::make_unique<int>(a);
	
	int b = 22;
	auto upb = std::make_unique<int>(b);
	// upb = upa;   // error! 복사 불가능!
	upb = std::move(upa);   // 이동은 가능하다.
    // 소유권을 이동하면 기존의 upa는 empty가 된다. (null)
	// 단, 원시포인터와 스마트포인터 간의 이동은 불가능!
    std::cout << *upb << std::endl;

	std::cout << upa << std::endl;
	std::cout << upb << std::endl;

	return 0;
}
```
    - 원시포인터를 스마트 포인터로 감싸는 방법도 있다.
    ```cs
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

		//auto pBook1 = std::make_unique<Book>(new Book("채식주의자"));
		std::unique_ptr<Book> upBook1(new Book("채식주의자"));
		//auto upBook1(new Book("채식주의자"));
		std::cout << upBook1->getTitle() << std::endl;
		throw std::runtime_error("일부러 예외 발생시켜봄");
		//delete pBook1;
	}
	catch (const std::exception& e) {
		std::cerr << "Error" << e.what() << std::endl;

	}

	return 0;
}
```
    - double free 이슈 -> 참조 계수 방식으로 해결함.
```cs
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
	Book* pBook1 = new Book("채식주의자"); // 원시 포인터 생성
	std::unique_ptr<Book> upBook1(pBook1); // 첫번째 unque_ptr에 소유권 부여 -> 자동 메모리 해제됨?
	std::unique_ptr<Book> upBook2(pBook1); // 두번째 unique_ptr에 동일한 소유권 부여(잘못됨 해제된 메모리에 접근함.)

	// 프로그램 종료시 upBook1을 해제하고
	// upBook2를 해제하려고 하는데, upBook1의 str은 이미 해제가 되어있음
	// double free
	return 0;
}

```
- std::shared_ptr
    - 참조 계수 방식 (reference counting) 으로 하나의 포인터가 사라진다 하더라도 가리킨 메모리가 해제되지 않도록 한다.  
    - 즉, 포인터를 참조 계수 count에 저장해두고 이게 0이 됐을 때 자원이 해제된다.  
    - 근데, 아래와 같이 순환 참조. 즉, 서로 다른 shared_ptr가 서로를 가리킬 때 순환 참조 문제로 main이 끝날 때까지 메모리 해제가 안될 수도 있다.  
```cs
#include <iostream>
#include <memory>

class Node {
public:
    std::shared_ptr<Node> next; // 다음 노드를 가리키는 shared_ptr
    std::shared_ptr<Node> prev; // 이전 노드를 가리키는 shared_ptr

    Node() {
        std::cout << "Node created\n";
    }
    ~Node() {
        std::cout << "Node destroyed\n";
    }
};

int main() {
    // 두 개의 Node 객체 생성
    auto node1 = std::make_shared<Node>();
    auto node2 = std::make_shared<Node>();

    // 순환 참조 설정
    node1->next = node2; // node2의 참도 카운트 증가
    node2->prev = node1; // node1을 가리키며 node1의 참도 카운트 증가
    // 어느 한쪽의 참조 카운트도 0이 되지 않아 소멸되 않는다.

    // main 함수 종료 시에도 Node 객체가 소멸되지 않음 (순환 참조)
    return 0;
}
```
- std::weak
    - shared_ptr의 순환 참조 이슈를 해결하기 위해 등장한 포인터..?


### WHY??
```cs
void func() {
	int* temp = new int(1000);
	// 코드...
	//delete temp; // 깜박한다면?
}

int main() {
	return 0;
}
```
메모리 해제를 안하면 메모리 누수 발생  
심지어 func 함수가 끝나면 참조에 접근할 수 없기에 메모리를 해제할 수 없다.  

### RAII 자원 획득 관련 규칙? 사용하면 안되나? (원시포인터)
```cs

#include <iostream>
#include <memory>
#include <typeinfo>

class Book {
private:
    char* buffer; // 동적 메모리 자원을 할당받을 포인터
    size_t size;  // 버퍼 크기

public:
    std::string str;

    // 생성자: 자원 할당
    Book(std::string str, size_t bufferSize) : str{ str }, size{ bufferSize } {
        std::cout << "생성자 호출: " << str << std::endl;
        buffer = new char[size]; // 동적 메모리 할당
        std::cout << "버퍼 " << size << " 바이트 할당 완료" << std::endl;
    }

    // 소멸자: 자원 해제
    ~Book() {
        delete[] buffer; // 동적 메모리 해제
        std::cout << "소멸자 호출: " << str << std::endl;
        std::cout << "버퍼 해제 완료" << std::endl;
    }

    // 제목 반환
    std::string getTitle() const {
        return this->str;
    }
};

int main() {
    try {
        // 원시 포인터를 직접 사용하는 경우
        auto pBook1 = new Book("채식주의자", 1024); // 1024 바이트 버퍼 할당
        std::cout << pBook1->getTitle() << std::endl;

        throw std::runtime_error("일부러 예외 발생시켜봄"); // (1)

        delete pBook1; // 이 줄은 실행되지 않음 (예외 발생으로 인해)
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    // 스마트 포인터를 사용하는 경우 (RAII 적용)
    try {
        auto upBook2 = std::make_unique<Book>("소년이 온다.", 2048); // 2048 바이트 버퍼 할당
        std::cout << upBook2->getTitle() << std::endl;

        throw std::runtime_error("또 다른 예외 발생"); // (2)
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
```
- 위와 같이 생성자가 동적 메모리 할당하고, 소멸자에서 메모리를 해제하는 방법도 있다.  
- 하지만, 소멸자가 호출되기 전에 예외가 발생하면 소멸자가 호출되지 않기 때문에 해제를 못하는 문제가 발생한다.  
```cs
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
```

반면, 스마트포인터는 예외가 발생해도 메모리를 해제시켜준다.  
```cs
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
        throw std::runtime_error("일부러 예외 발생시켜봄"); // (1)
        for (size_t i = 0; i < mem->size(); ++i) {
            std::cout << "mem[" << i << "] = " << (*mem)[i] << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    // 스마트 포인터가 스코프를 벗어나면서 자동으로 메모리를 해제
    return 0;
}
```

### 댕글링 포인터 문제(잘못된 참조) 가 사라진다.
delete 했던 동적 메모리를 잘못 참조할 일이 없는 것!

