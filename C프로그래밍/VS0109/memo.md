2025.01.09.

### ������
+ C++ ������ �����Լ�, ������ �����ε�, ���ø� ���� �ִ�.
+ ���Ŭ������ ��ü Ÿ���ε�, �Ļ�Ŭ������ ��ü�� �Ҵ���� ��.

### �������ε�(�Ϲ� �Լ�) vs �������ε�(���� �Լ�)
+ ���ε� : ���α׷� �ҽ����� �� �Ǵ� �Ӽ��� Ȯ���ϴ� ����.  
+ �Ϲ��Լ��� �������ε�����, ������ �� �� � �Լ��� ȣ����� �̹� �����Ǿ� �ִ�.  
+ �����Լ��� �������ε�����, ������ ������ �������� �ʰ�, ��Ÿ�� �� ��������.  
++ �������ε��� �����Ͱ� ����Ű�� ��ü�� ���� �Լ��� ȣ���Ѵ�.
+ �������̵� without �����Լ� -> ���Ŭ���� ����, �������ε�  
+ �������̵� with �����Լ� -> �Ļ�Ŭ���� ����, �������ε�  
++ ���Ŭ������ �����Լ��� �� �״�� ���� �ִ� �Լ���� �����ϸ� �� ��?  

- �������̵��� �Լ��� �Լ� �ڿ� override�� �ٿ��ִ� �� ����.
```cs
void func() override {}
```

---

### �߻�Ŭ���� & �������̽�
- ���������Լ��� �ϳ��� ������ �߻�Ŭ������� �Ѵ�.  
�ٵ�, ���������Լ��θ� �̷���� �ִ� �߻�Ŭ������ Ư���� �������̽���� �Ѵ�.  
- �߻�Ŭ������ ��ü�� ���� �� ���µ�, ����? 
���������Լ��� ��ü�� ����? �� �״�� �����Լ��ϱ� ���ٰ� �����ϳ�?  
```cs
Shape s;	// error!!
Shape* s1;	// ������ ������ �����ϴ�.
Shape* s2 = new Shape; // error!!
```

- ���� �Ļ�Ŭ���������� ���������Լ��� �������̵� �Լ��� �Ϲ��Լ�(�����Լ�X)�� ����.  
��, override �ٿ��ִ� �� ����.

### ��ü�� ������?
- Ŭ������ �����Լ��� �ϳ��� ������ ��ü ���������� �����Ͱ� �ϳ� �����.  
Ŭ���� ���� ���� ���̺��� ���ܼ� ������ �����Ͱ� ���� ���̺��� ����Ų��.  
�������̺��� Ŭ������ �����Լ��� ����Ų��.  
- ��ü - ���� ���̺� -> �����Լ� (2�� ������ ���)

```cs
/* example of interface */
#include <iostream>

using namespace std;

class Shape {
public:
    virtual void draw() = 0;
};

class Circle : public Shape{
public:
    void draw() override {
        cout << "circle" << endl;
    }
};

int main() {
    Shape* s = new Circle;

    s->draw();
}
```

- (����)�����Լ��� const��, �������̵� �Լ��鵵 const�� �ٿ����Ѵ�.
```cs
Phone() {}; // warning! �����Ϸ��� �˾Ƽ� �⺻ ������ ������ֱ� ������~
Phone() = default;  // oK!
```
```cs
class Phone {
public:
    // default �Ҹ���, �Ʒ����� ������ warning�� ���ֱ� ����. ���� default�� �ɰڴ� �ϰ� ����ϴ� ��?
    virtual ~Phone() = default; 
    // virtual ~Phone() {};    // �̰͵� default �Ҹ����ε�, �̰͵� warning ���. �Ʒ��� ���� ����.
    // Phone() {};//  �̰Ŵ� default �������ε�, �̷��� ������ warning ���. �⺻�� �����Ϸ��� �˾Ƽ� ������ֱ� ������.
    virtual void call() const = 0;
    // (����)�����Լ��� const�� �������̵� �Լ��鵵 const ���� �ȴ�.
};

class LandLinePhone : public Phone {
public:
    LandLinePhone() = default;  // default ������
    void call() const override {
        cout << "LandLinePhone" << endl;
    }
};

class CellPhone : public Phone {
public:
    CellPhone() = default;
    void call() const override {
        cout << "CellPhone" << endl;
    }
};

class Person {
public:
    void makeCall(const Phone* p) const {
        p->call();
    }
};

int main() {
    Person ps;
    LandLinePhone landlinePhone;
    CellPhone cellPhone;

    ps.makeCall(&landlinePhone);
    ps.makeCall(&cellPhone);
}
```

### ��� ��ĳ���� vs �������̽�
��� ��ĳ���� < �������̽�  
����� ���յ��� ���ϰ�, ���� ����� ��ƴ�.
�������̽��� ��ӿ� ���� ���յ��� ����, �� Ŭ������ ���� �������̽��� �����Ͽ� ���� ��� ȿ���� ���� �� �ִ�.  
������ �� ���� ���̼� ����  
But, �������̽� ���� �� �߰��ϸ� ���������.

### ������ �����ε�
�⺻��
```cs
int + int -> int operator+(int& other)
char + char -> char operator+(char& other)
int - int -> int operator-(int& other)
int + float -> int operator+(float& other)
```
```cs
/* Ŭ���� ������ ������ �����ε� */
class MyString {
private:
...

public:
...
    MyString operator+(const MyString& other) const {
        char* temp = new char[this->len + other.len];

        strcpy(temp, this->str);
        strcat(temp, other.str);

        return temp;
    }
};
```

���� ���� ¥�� ������� ���� ���� �׻� Ŭ������ü? ���� �Ѵ�. (return �������� ����)  
���� Ŭ���� �ܺο� ¥�°� ����.  
```cs
ComplexNumber operator+(const ComplexNumber& lhs, const ComplexNumber& rhs) {
    return ComplexNumber(lhs.getNum1() + rhs.getNum1(), lhs.getNum2() + rhs.getNum2());
}
```

friend�� �ٿ��� Ŭ���� ���� �����ϰ�, �ܺο��� �����ϴ� �� ���� ���� ����̴�.
```cs
/* ���Ҽ� */
class ComplexNumber {
private:
    int a;
    int b;

public:
    ComplexNumber() : a(0), b(0) {}
    ComplexNumber(int pa, int pb) : a(pa), b(pb) {}

    void print() const {
        cout << a << " + " << b << "i" << endl;
    }

    int getNum1() const {
        return a;
    }

    int getNum2() const {   // �Ʒ� �ܺ��Լ����� �Ķ���� ���������� const�̱� ������ const �Լ��� ȣ���� �� �ִ�.
        return b;
    }

    // ������ ����?�� ������ ��ü�̾�� �ϴ� �Ѱ� �߻�!!
    // ���� ��������� ����� �ͺ��� �ܺο� ����°� ����.
#if 0
    ComplexNumber operator+(const ComplexNumber& other) const {
        return ComplexNumber(this->a + other.a, this->b + other.b);
    }
#endif
    friend ComplexNumber operator+(const ComplexNumber& lhs, const ComplexNumber& rhs);
    friend ComplexNumber operator+(int a, const ComplexNumber& rhs);
    friend ComplexNumber operator+(const ComplexNumber& rhs, int a);
    friend ComplexNumber operator*(const ComplexNumber& lhs, const ComplexNumber& rhs);
};

ComplexNumber operator+(const ComplexNumber& lhs, const ComplexNumber& rhs) {
    return ComplexNumber(lhs.a + rhs.a, lhs.b + rhs.b);
}

ComplexNumber operator*(const ComplexNumber& lhs, const ComplexNumber& rhs) {
    int x = (lhs.a * rhs.a) - (lhs.b * rhs.b);
    int y = (lhs.a * rhs.b) + (lhs.b * rhs.a);
    return ComplexNumber(x, y);
}

ComplexNumber operator+(int a, const ComplexNumber& rhs) {
    return ComplexNumber(a + rhs.a, rhs.b);
}

ComplexNumber operator+(const ComplexNumber& rhs, int a) {
    return ComplexNumber(a + rhs.a, rhs.b);
}

int main() {
    ComplexNumber c1(1,2);
    ComplexNumber c2(3,4);

    c1.print();
    c2.print();

    ComplexNumber c3 = c1 + c2;
    ComplexNumber c4 = 1 + c1;
    ComplexNumber c5 = c1 + 2;
    ComplexNumber c6 = operator*(c1, c2);

    c3.print();
    c4.print();
    c5.print();
    c6.print();
}
```

������ �����ε��� �Ķ���ʹ� ��� �ϳ��� ����� ���� Ÿ���̾�� �Ѵ�.
```cs
int operator+(int a, int b) { // error
}
```

### ������ �����ε��� ����
������ �����ε��� �Լ�ó�� ���� ���� �ִ�.
```cs
int operator()(int a, int b){
    return a + b;
}
```

���ʹ� �Լ��� ���¸� ������ �� �ִ�.
```cs
class Plus {
public:
    int operator()(int a, int b)  {
        return a + b;
    }

    int operator()(int a, int b, int c) {
        return a + b +c;
    }
};

int main() {
    auto t = cmp(); // ����!
    t(3);
    t(7);   // ��� 10�� �ȴ�.
}
```

### ������������ �����ε�
```cs
// ���� ���� ������ (++Point)
Point& operator++() {
    ++x; // x ����
    ++y; // y ����
    return *this; // �ڱ� �ڽ� ��ȯ
}

// ���� ���� ������ (Point++)
Point operator++(int) {
    Point temp = *this; // ���� ���� ����
    ++(*this);          // ���� ���� ȣ��
    return temp;        // ����� ���� ��ȯ
}
```
##### [] ������(���͸� �迭��)�� �����ε��� �����ϴ�.

### friend Ŭ����, ��� �Լ�, ���� �Լ�
#### friend Ŭ����
class ��ü�� public���� ���� ����
#### friend ��� �Լ�
�ش� class���� ������ ��� �Լ��� ���� ����
#### friend ���� �Լ�
���� �����ڸ� �����ϰ� Ŭ���� ���� ����� ����  
