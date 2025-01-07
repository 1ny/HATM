### �����ε� ���� �ͱ۸� (name mangling, name decosration)
�����Ϸ��� �̸��� ���� �Լ����� �̸��� �˾Ƽ� �ٲ��ش�.  
��������� �����ƾ�� ���캸��, �Ʒ��� ���� �ٲ��. 
```cs
square@@YAHH@Z
square@@YANN@Z
```
�ٸ�, C�� C++ ȣȯ�� ������ �����. �ٵ� ��� C�� C++�� ���� ���� �� ������.  
  
### �ζ��� �Լ�
```cs
inline int sum(int a, int b) {
	return a + b;
}
```
��ũ�� �Լ��� ����ϰ� ġȯ�ȴ�.  
������, ��ó����� ó���ϴ� ��ũ�ο� �޸�, �ζ��� �Լ��� �����Ϸ��� ó���Ѵ�.  
�ζ��� �Լ��� �Ϲ� �Լ��� �޸� �ּҰ� ����.  
�Ϲ� �Լ��� ���� stack�� �ְ� ���� ������ ���⿡ ������?  

### �Լ� ���ø�
Body ������ ������, �Ķ���ͳ� ����Ÿ���� �ٸ� ���, �Լ� ���ø��� ����ϸ� ������ �� ���ϴ�.  
```cs
template<typename T>
T square(T a) {
	return a * a;
}

int main() {
	int c = square<int>(2);
	double d = square<double>(3.2);
	cout << c << endl;
	cout << d << endl;

	return 0;
}
```
#### typename ��� class�� ��� �ȴ�.
```cs
template<class T>
T square(T a) {
	return a * a;
};
```
�Լ� ���ø��� �Ϲ� �Լ��� �ƴϱ� ������ �ּҰ� ����.  

### for_each
```cs
// for_each(first, last, body func);
std::for_each(arr, arr + 5, print_one);
```

### range for ���� ��� for��
 ```cs
 	// ���� ��� for ���� ����ؼ� ����ϱ�
	for (int ele : arr) {
		std::cout << ele << ", ";
	}
	std::cout << std::endl;

	// ���� ��� for ���� ���۷����� ����ؼ� ����ϱ�
	for (const int& ele : arr) {
		std::cout << ele << ", ";
	}
```
### memory ���� �Ҵ� : new delete.

### c vs c++
call by value - pass by value (a = b)  
call by reference - pass by address (int* pa = &a;)  
' ' - pass by reference (int& ra = a;)  

reference�� NULL�� ����. ��, NULL���� �˻��� �ʿ䰡 ����.  
reference�� �ѹ� �ʱ�ȭ�ϸ� �� �ּҰ��� �ٲ� �� ����. 
���� pass by reference ���°� ����~
```cs
	int a = 11;
	int& ra = a; // ra�� a�� ���ٰ� ���� �ȴ�.
	ra = 33;
	a = ra;	// �̰͵� �ȴ�.
	// �ּҴ� �ȹٲ�µ�, ���� �ٲ��.
	int b = 999;
	ra = b;
```
���� �ٲ�� �� �����ϱ� ���ؼ� C++�� �Ʒ��� ���� pass by reference + const�� ���� ����.
```cs
void func(const int& a);
```

### c++ Ŭ������ ��������
private ���� �����Ͽ� �����͸� ���� �� �ִ�.
```cs
class FishBun {
private:
	int price;

public:
	void printPrice() {
		cout << price << endl;
	}
};
```
#### ���� ������ (setter, getter)
��� ������ �����ϴ� �Լ�, ���� ��� setAge, getAge �̷����� �Լ��� setter, getter ��� �Ѵ�.  

### encapsulation -> ĸ��ȭ~ C++/OOP�� Ư¡

### �Լ� �ڿ� const
�Լ� ���� const�� ������,  
1. ��ü ���� ���� �� ���� �Ұ�
2. const �Լ��� ȣ�� ����
```cs
class Number {
private:
	int num;
public:
	int GetNum() {
		return num;
	}
	bool IsNotZero() const {
		int r = GetNum();	// error! non-const function
		SetZero();	// call ok! const function and didn't change value
		return num != 0;
	}
	void SetZero() const {
		num = 0;	// error ! cannot change any value
	}
};
```

### �����ڿ� �Ҹ���
#### ������
�����ڴ� ��ü�� ������ �� �ڵ����� ����ȴ�.  
��, �ʱ�ȭ ��ų �� ���.
#### �Ҹ���
�Ҹ��ڴ� main �Լ��� ������ ���� ����ȴ�.
```cs
class Person {
private:
	std::string name;
	int age;

public:
	// ������
	Person() {
		name = "tom";
		age = 11;
		std::cout << "������ ȣ��" << endl;
	}
	// �Ҹ���
	~Person() {
		std::cout << "�Ҹ��� ȣ��" << endl;
	}
};

int main() {
	Person p1;
	std::cout << "main �Լ� ȣ��" << endl;
}
```

��� ����� ������ -> main -> �Ҹ���

�����ڿ� ���ڸ� ���� ���� �ִ�. �ٸ�, ���ڸ� ���� ��� ��ü�� ������ �� �׻� ���ڰ� �־�� �Ѵ�.
```cs
class Person {
...

public:
	Person(int a) {
		age = a;	
	}
}

int main() {
	Person p1(3);
	Person p2; // error
}
```

�Ҹ��ڴ� �Ҵ� ���� �ڿ��� �ݳ��Ҷ� ����Ѵ�.  
�Ҹ��ڰ� ������?? �ڵ����� �Ҹ��ڰ� ȣ��ȴ�...?  