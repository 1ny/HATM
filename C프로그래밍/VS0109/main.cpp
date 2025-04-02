#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using namespace std;

#if 0
// �θ� Ŭ����
class Animal {
public:
    // ���� �Լ� (Virtual Function)
    virtual void speak() {
        std::cout << "Animal makes a sound." << std::endl;
    }
};

// �ڽ� Ŭ���� (Animal Ŭ������ ��ӹ���)
class Dog : public Animal {
public:
    // �θ� Ŭ������ �Լ��� �������̵�
    void speak() override {
        std::cout << "Dog barks." << std::endl;
    }
};

// �� �ٸ� �ڽ� Ŭ���� (Animal Ŭ������ ��ӹ���)
class Cat : public Animal {
public:
    // �θ� Ŭ������ �Լ��� �������̵�
    void speak() override {
        std::cout << "Cat meows." << std::endl;
    }
};

int main() {
    Animal* animal1 = new Dog();
    Animal* animal2 = new Cat();

    // ���������� �����ϴ� �޼���
    animal1->speak();  // ���: Dog barks.
    animal2->speak();  // ���: Cat meows.

    // ���� �Ҵ��� �޸� ����
    delete animal1;
    delete animal2;

    return 0;
}
#endif

#if 0
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
#endif

#if 0
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
#endif

#if 0
class ICamera {
public:
    virtual ~ICamera() = default;
    virtual void take() const = 0;
};

class HDCamera : public ICamera{
public:
    void take() const override {
        cout << "��ȭ�� ����" << endl;
    }
};

class XHDCamera : public ICamera{
public:
    void take() const override {
        cout << "�ʰ�ȭ�� ����" << endl;
    }
};

class Photographer {
public:
    void useCamera(const ICamera* camera) const {
        camera->take();
    }
};

int main() {
    Photographer p;
    HDCamera hdCamera;
    XHDCamera xhdCamera;

    p.useCamera(&hdCamera);
    p.useCamera(&xhdCamera);
}
#endif

#if 0
/* ������ �����ε� of string */
#include <cstring>

class MyString {
private:
    char* str;
    size_t len;

public:
    MyString() : str(nullptr), len(0) {}
    MyString(char* pStr) {
        str = new char[strlen(pStr) + 1];   // ���� null ���� +1
        strcpy(str, pStr);
        len = strlen(pStr);
    }

    void print() const {
        cout << str << endl;
    }

#if 0
    MyString operator+(const MyString& other) const {
        char* temp = new char[this->len + other.len];

        strcpy(temp, this->str);
        strcat(temp, other.str);

        return temp;
    }
#endif
    friend MyString operator+(const MyString& lhs, const MyString& rhs);
    friend void operator+=(const MyString& lhs, const MyString& rhs);
    friend bool operator==(const MyString& lhs, const MyString& rhs);
};

MyString operator+(const MyString& lhs, const MyString& rhs) {
    char* temp = new char[lhs.len + rhs.len];

    strcpy(temp, lhs.str);
    strcat(temp, rhs.str);

    return temp;
}

void operator+=(const MyString& lhs, const MyString& rhs) {
    strcat(lhs.str, rhs.str);
}

bool operator==(const MyString& lhs, const MyString& rhs) {
    bool retValue = strcmp(lhs.str, rhs.str);

    if (retValue == 1) return 0;
    else return 1;
}

int main() {
    MyString myStr1("Hello ");
    MyString myStr2("World!");
    MyString myStr5("Hello ");

    myStr1.print();
    myStr2.print();

    MyString myStr3 = myStr1 + myStr2;
    myStr1 += myStr2;

    cout << "+ : ";
    myStr3.print();
    cout << "+= : ";
    myStr1.print();

    if (myStr2 == myStr5) {
        cout << "�� ���ڿ��� ����." << endl;
    }
    else {
        cout << "�� ���ڿ��� ���� �ʴ�." << endl;
    }
}
#endif

#if 0
class Point {
private:
    int a;
    int b;
    
public:
    Point() : a(0), b(0) {}
    Point(int pa, int pb) {
        a = pa;
        b = pb;
    }

    void print() const {
        cout << "(" << a << "," << b << ")" << endl;
    }

#if 0
    Point operator+(const Point& other) const {
        Point ret = { this->a + other.a, this->b + other.b };
        return ret;
    }
#endif

    friend Point operator+(const Point& lhs, const Point& rhs);
};

Point operator+(const Point& lhs, const Point& rhs) {
    Point ret = { lhs.a + rhs.a, lhs.b + rhs.b };
    return ret;
}

int main() {
    Point pt1(11, 22);
    Point pt2(33, 44);

    int a = 999;

    pt1.print();
    pt2.print();

    Point pt3 = pt1 + pt2;
    pt3.print();

    return 0;
}
#endif

#if 0
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
#endif

#if 0
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// functor 
class cmp {

public:
    int value = 0;
    bool operator()(int a, int b) {
        return a > b;
    }
    void operator()(int a) {
        value += a;
    }
};
int main() {
    auto t = cmp();
    t(3);
    t(7);
    cout << t.value;
    cout << endl;

    std::vector<int> arr = { 1,5,2,1,3 };
    sort(arr.begin(), arr.end(), cmp());
    for (int ele : arr) {
        std::cout << ele << ", ";
    }


    return 0;
}

#endif

