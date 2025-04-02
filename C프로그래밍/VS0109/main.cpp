#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using namespace std;

#if 0
// 부모 클래스
class Animal {
public:
    // 가상 함수 (Virtual Function)
    virtual void speak() {
        std::cout << "Animal makes a sound." << std::endl;
    }
};

// 자식 클래스 (Animal 클래스를 상속받음)
class Dog : public Animal {
public:
    // 부모 클래스의 함수를 오버라이드
    void speak() override {
        std::cout << "Dog barks." << std::endl;
    }
};

// 또 다른 자식 클래스 (Animal 클래스를 상속받음)
class Cat : public Animal {
public:
    // 부모 클래스의 함수를 오버라이드
    void speak() override {
        std::cout << "Cat meows." << std::endl;
    }
};

int main() {
    Animal* animal1 = new Dog();
    Animal* animal2 = new Cat();

    // 다형성으로 동작하는 메서드
    animal1->speak();  // 출력: Dog barks.
    animal2->speak();  // 출력: Cat meows.

    // 동적 할당한 메모리 해제
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
    // default 소멸자, 아래에서 설명한 warning을 없애기 위해. 내가 default를 걸겠다 하고 명시하는 거?
    virtual ~Phone() = default; 
    // virtual ~Phone() {};    // 이것도 default 소멸자인데, 이것도 warning 뜬대. 아래랑 같은 이유.
    // Phone() {};//  이거는 default 생성자인데, 이렇게 적으면 warning 뜬다. 기본은 컴파일러가 알아서 만들어주기 때문에.
    virtual void call() const = 0;
    // (순수)가상함수가 const면 오버라이딩 함수들도 const 여야 된다.
};

class LandLinePhone : public Phone {
public:
    LandLinePhone() = default;  // default 생성자
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
        cout << "고화질 사진" << endl;
    }
};

class XHDCamera : public ICamera{
public:
    void take() const override {
        cout << "초고화질 사진" << endl;
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
/* 연산자 오버로딩 of string */
#include <cstring>

class MyString {
private:
    char* str;
    size_t len;

public:
    MyString() : str(nullptr), len(0) {}
    MyString(char* pStr) {
        str = new char[strlen(pStr) + 1];   // 끝에 null 문자 +1
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
        cout << "두 문자열은 같다." << endl;
    }
    else {
        cout << "두 문자열은 같지 않다." << endl;
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
/* 복소수 */
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

    int getNum2() const {   // 아래 외부함수에서 파라미터 데이터형이 const이기 때문에 const 함수만 호출할 수 있다.
        return b;
    }

    // 연산의 왼항?이 무조건 객체이어야 하는 한계 발생!!
    // 따라서 멤버변수로 만드는 것보다 외부에 만드는게 좋다.
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

