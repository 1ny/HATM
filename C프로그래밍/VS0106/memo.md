
### C++�� OOP(��ü ����) Ư¡
1.ĸ��ȭ -> ������, �Ⱥ����� �����ϴ� ���� �����ڰ� �ִ�. public/private(default) (+��������)  
2.������  
3.���  
4.�߻�ȭ  

+ C���� �߿��Ѱ�?  
+ �Լ� ������, C�� ���������ε�, �Լ� �����ͷ� ��ü ������ �����ؼ� ��ü ������ ������ �̿��� �� �ֱ� ����.

### class vs struct
class������ �Լ��� Ŭ�����ȿ� �ֱ⵵ �Ѵ�.
```cs
class Calc {
	int a;
	int b;

	int sum(int a, int b) {
		return a+b;
	}
};
```

### Ŭ������ �ν��Ͻ� ����?
����� ������ ���̴�. Ŭ������ �������� �޸� �Ҵ� X, �ν��Ͻ��� ���Ƿ� �޸� �Ҵ� O  
�ν��Ͻ���? Foo foo; ���� foo.

### static ����
Ŭ���� �������� ���� static ����, �� Ŭ���� ������ �ִ�
```cs

class Fishbun {
public:
	int cnt1;
	static int cnt2;

	Fishbun():cnt1{ 0 } {
		++cnt1;
		++cnt2;
	}
};

int Fishbun::cnt2 = 0;	// static ���� �ʱ�ȭ ���

int main() {
	Fishbun f1;
	std::cout << f1.cnt1 << "," << Fishbun::cnt2 << std::endl;
	Fishbun f2;
	std::cout << f1.cnt1 << "," << Fishbun::cnt2 << std::endl;
	Fishbun f3;
	std::cout << f1.cnt1 << "," << Fishbun::cnt2 << std::endl;


	return (0);
}
```
��� ������ �ν��Ͻ����� ������������, ����Լ��� ��� �ν��Ͻ��� �����Ѵ�.
�̰� ���Ҹ���. ��¥��?

### Ŭ������ ���� or ��?
-> ���ÿ� ����� ���� ����. ���� �޸� �����ϱ� �������ϱ�~~  
C++������ ���� �Ҵ��ϴ� �� malloc ���� new �� �ִ�~  
malloc - free  // new - delete  
�ٵ� �ַ� new�� ���� -> ������ ȣ�� ����, �޸� ������ ����, ���� ó���� ����  
malloc�� NULL ��ȯ�ؼ� NULL ó���� ����ߵȴ� 

## �ν��Ͻ� ���� ���
```cs
Sample s1;	// �ַ� �̰� ��.
Sample* s2 = new Sample;
Sample* s3 = new Sample();	// �Լ��� �ƴѰ� Ȯ���ϴ�? �׷��� �����ϱ� ��.
```
this pointer -> �ؾ ���� ����? �ؾ �ڽ��� ����Ű�� ������?

C++���� :: ������ �켱������ ���� ����.

using namespace Test; -> �Ź� Test�� �Ƚᵵ �ȴ�.

� namespace���� �������� ����, �Լ�/������ �۷ι� namespace��� �Ѵ�.
```cs
void init();
```

typedef�� �ᵵ ������, using�� ����.

C++ ������ C �Լ��� ����� �� �ִµ�, (cstdio, cmat, cstring ó��) ������ �Ⱦ��°� ����.


### Auto�� decletype
auto�� ���� ���� �ڵ����� ������Ÿ���� �������ش�.  
auto�� ����/������ ��, decletype�� ��ȯ ���� ��.
```cs
decletype(11) b = 22;
```

### �迭 vs vector
vector�� ���� �迭��, ũ�Ⱑ �ڵ����� �þ?

## ������ �ʱ�ȭ
� ������Ÿ���� ������ a{0}, b{0,0}, cl{0,0} �̷������� �ʱ�ȭ�� �� �ִ� ���
```cs
struct test t0 {0,0};
struct test t1 (0,0);	// error
test_class t2 {0,0};
test_class t3 (0,0); // ����ü�� �ȵ����� Ŭ������ �Ұ�ȣ�ε� ������ �ʱ�ȭ�� �����ϴ�._
```
### C++ ������ ����ü
struct ���� ����
structure binding
```cs
struct pStr{
	int x;
	int y;
};

pStr pt;
auto [a, b] = pt; // a�� b ���� x�� y ���� ���� �ű�
// ���������� ������ ���ƾ� binding�� �ȴ�.
```

### C++�� string Ÿ���� �ִ�.
�Ʒ��� ���� �������� ������ �����ϴ�. without strcpy!!!!
==, +, =
```cs
string s1 = "test";
string s2;
string s3 = "cat";
string s4 = est;

s2 = s1;
s4 = s1 + s3;
if(s1 == s4) ...
```

### C++������ bool �� 1,0�� ������ warning ���.
```cs
bool a = 1;	// C������ �ƹ����� ��������, C++�� waning
```

### default parameter
```cs
void bts(int a = 1, int b = 2, int c = 3) {
	std::cout << a << "," << b << "," << c <<std::endl;
}

int main() {
	bts(11, 22, 33); // (1)
	bts(11, 22); //(2)
	bts(); //(3)
	return (0);
}
```
```cs
void bts(int a = 1, int b = 2, int c = 3);
void bts(int a, int b, int c) {
	std::cout << a << "," << b << "," << c <<std::endl;
}
```
### �Լ� �����ε� vs �������̵�
�������̵��� ��ӹ��� Ŭ���� �Լ��� �ڽ� Ŭ�������� �����ϴ� ��.  
�����ε��� �Լ����� ������, �Ķ������ ������ Ÿ���� �ٸ��� �Ͽ� �������ϴ� ��.  
C++������ �����ε��� �����ϴ�.  
�ٸ�, ��ȯ Ÿ�����δ� ������ �ȵȴ�. �Ķ������ Ÿ���̳� ������ �����ؾ��Ѵ�.  
```cs
/* overriding example */
class Father {
public:
	void draw() {
		cout << "Father" << endl;
	}
}

class Daughter:public Father {
public:
	void draw() {
		cout << "Daughter" << endl;
	}
}
```
```cs
/* overloading example */
class Father {
public:
	void draw() {
		cout << "Father" << endl;
	}
	void draw(string a) {
		cout << "Father " + a << endl;
	}
}
```