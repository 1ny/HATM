## ����Ʈ ������
- �ڵ� �޸� ���� (delete ����)   
    - main �Լ� �Ǵ� �Լ� ( {}�� ���� �� ) ���� ��
    - (Scope ��� ��) �Ҹ��� ȣ��� ��
    - exception �߻��� ��
    - delete ���� �ʾƵ� �ڵ� �޸� ����
    - etc.
- ���� �����ʹ� ���������Ͷ�� �θ���.
```cs
#include <iostream>
#include <memory>

int main() {
	std::unique_ptr<int> smart_ptr(new int (11));
	std::cout << *smart_ptr << std::endl;
	return 0;
}
```
main �Լ��� ������ ����Ʈ������ smart_ptr�� ������鼭 �ڵ����� ���� �޸𸮸� �����Ѵ�.  

### ����
- std::unique_ptr
    - ���� ������   
	(���簡 �Ұ����ϴ�. ��, ���� �ٸ� unique_ptr �����Ͱ� ���� �ּҸ� ���� �� ������ �ǹ�? ���� �ּҸ� ����ų ���� ����.)  
    - ���� �Ұ���, �̵��� ����
```cs
#include <iostream>
#include <memory>

int main() {

	int a = 11;
	auto upa = std::make_unique<int>(a);
	
	int b = 22;
	auto upb = std::make_unique<int>(b);
	// upb = upa;   // error! ���� �Ұ���!
	upb = std::move(upa);   // �̵��� �����ϴ�.
    // �������� �̵��ϸ� ������ upa�� empty�� �ȴ�. (null)
	// ��, ���������Ϳ� ����Ʈ������ ���� �̵��� �Ұ���!
    std::cout << *upb << std::endl;

	std::cout << upa << std::endl;
	std::cout << upb << std::endl;

	return 0;
}
```
    - ���������͸� ����Ʈ �����ͷ� ���δ� ����� �ִ�.
    ```cs
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

		//auto pBook1 = std::make_unique<Book>(new Book("ä��������"));
		std::unique_ptr<Book> upBook1(new Book("ä��������"));
		//auto upBook1(new Book("ä��������"));
		std::cout << upBook1->getTitle() << std::endl;
		throw std::runtime_error("�Ϻη� ���� �߻����Ѻ�");
		//delete pBook1;
	}
	catch (const std::exception& e) {
		std::cerr << "Error" << e.what() << std::endl;

	}

	return 0;
}
```
    - double free �̽� -> ���� ��� ������� �ذ���.
```cs
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
	Book* pBook1 = new Book("ä��������"); // ���� ������ ����
	std::unique_ptr<Book> upBook1(pBook1); // ù��° unque_ptr�� ������ �ο� -> �ڵ� �޸� ������?
	std::unique_ptr<Book> upBook2(pBook1); // �ι�° unique_ptr�� ������ ������ �ο�(�߸��� ������ �޸𸮿� ������.)

	// ���α׷� ����� upBook1�� �����ϰ�
	// upBook2�� �����Ϸ��� �ϴµ�, upBook1�� str�� �̹� ������ �Ǿ�����
	// double free
	return 0;
}

```
- std::shared_ptr
    - ���� ��� ��� (reference counting) ���� �ϳ��� �����Ͱ� ������� �ϴ��� ����Ų �޸𸮰� �������� �ʵ��� �Ѵ�.  
    - ��, �����͸� ���� ��� count�� �����صΰ� �̰� 0�� ���� �� �ڿ��� �����ȴ�.  
    - �ٵ�, �Ʒ��� ���� ��ȯ ����. ��, ���� �ٸ� shared_ptr�� ���θ� ����ų �� ��ȯ ���� ������ main�� ���� ������ �޸� ������ �ȵ� ���� �ִ�.  
```cs
#include <iostream>
#include <memory>

class Node {
public:
    std::shared_ptr<Node> next; // ���� ��带 ����Ű�� shared_ptr
    std::shared_ptr<Node> prev; // ���� ��带 ����Ű�� shared_ptr

    Node() {
        std::cout << "Node created\n";
    }
    ~Node() {
        std::cout << "Node destroyed\n";
    }
};

int main() {
    // �� ���� Node ��ü ����
    auto node1 = std::make_shared<Node>();
    auto node2 = std::make_shared<Node>();

    // ��ȯ ���� ����
    node1->next = node2; // node2�� ���� ī��Ʈ ����
    node2->prev = node1; // node1�� ����Ű�� node1�� ���� ī��Ʈ ����
    // ��� ������ ���� ī��Ʈ�� 0�� ���� �ʾ� �Ҹ�� �ʴ´�.

    // main �Լ� ���� �ÿ��� Node ��ü�� �Ҹ���� ���� (��ȯ ����)
    return 0;
}
```
- std::weak
    - shared_ptr�� ��ȯ ���� �̽��� �ذ��ϱ� ���� ������ ������..?


### WHY??
```cs
void func() {
	int* temp = new int(1000);
	// �ڵ�...
	//delete temp; // �����Ѵٸ�?
}

int main() {
	return 0;
}
```
�޸� ������ ���ϸ� �޸� ���� �߻�  
������ func �Լ��� ������ ������ ������ �� ���⿡ �޸𸮸� ������ �� ����.  

### RAII �ڿ� ȹ�� ���� ��Ģ? ����ϸ� �ȵǳ�? (����������)
```cs

#include <iostream>
#include <memory>
#include <typeinfo>

class Book {
private:
    char* buffer; // ���� �޸� �ڿ��� �Ҵ���� ������
    size_t size;  // ���� ũ��

public:
    std::string str;

    // ������: �ڿ� �Ҵ�
    Book(std::string str, size_t bufferSize) : str{ str }, size{ bufferSize } {
        std::cout << "������ ȣ��: " << str << std::endl;
        buffer = new char[size]; // ���� �޸� �Ҵ�
        std::cout << "���� " << size << " ����Ʈ �Ҵ� �Ϸ�" << std::endl;
    }

    // �Ҹ���: �ڿ� ����
    ~Book() {
        delete[] buffer; // ���� �޸� ����
        std::cout << "�Ҹ��� ȣ��: " << str << std::endl;
        std::cout << "���� ���� �Ϸ�" << std::endl;
    }

    // ���� ��ȯ
    std::string getTitle() const {
        return this->str;
    }
};

int main() {
    try {
        // ���� �����͸� ���� ����ϴ� ���
        auto pBook1 = new Book("ä��������", 1024); // 1024 ����Ʈ ���� �Ҵ�
        std::cout << pBook1->getTitle() << std::endl;

        throw std::runtime_error("�Ϻη� ���� �߻����Ѻ�"); // (1)

        delete pBook1; // �� ���� ������� ���� (���� �߻����� ����)
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    // ����Ʈ �����͸� ����ϴ� ��� (RAII ����)
    try {
        auto upBook2 = std::make_unique<Book>("�ҳ��� �´�.", 2048); // 2048 ����Ʈ ���� �Ҵ�
        std::cout << upBook2->getTitle() << std::endl;

        throw std::runtime_error("�� �ٸ� ���� �߻�"); // (2)
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
```
- ���� ���� �����ڰ� ���� �޸� �Ҵ��ϰ�, �Ҹ��ڿ��� �޸𸮸� �����ϴ� ����� �ִ�.  
- ������, �Ҹ��ڰ� ȣ��Ǳ� ���� ���ܰ� �߻��ϸ� �Ҹ��ڰ� ȣ����� �ʱ� ������ ������ ���ϴ� ������ �߻��Ѵ�.  
```cs
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
```

�ݸ�, ����Ʈ�����ʹ� ���ܰ� �߻��ص� �޸𸮸� ���������ش�.  
```cs
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
        throw std::runtime_error("�Ϻη� ���� �߻����Ѻ�"); // (1)
        for (size_t i = 0; i < mem->size(); ++i) {
            std::cout << "mem[" << i << "] = " << (*mem)[i] << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    // ����Ʈ �����Ͱ� �������� ����鼭 �ڵ����� �޸𸮸� ����
    return 0;
}
```

### ��۸� ������ ����(�߸��� ����) �� �������.
delete �ߴ� ���� �޸𸮸� �߸� ������ ���� ���� ��!

