2025.01.09.

### 다형성
+ C++ 에서는 가상함수, 연산자 오버로딩, 템플릿 등이 있다.
+ 기반클래스의 객체 타입인데, 파생클래스의 객체가 할당됐을 때.

### 정적바인딩(일반 함수) vs 동적바인딩(가상 함수)
+ 바인딩 : 프로그램 소스에서 값 또는 속성을 확정하는 과정.  
+ 일반함수는 정적바인딩으로, 컴파일 할 때 어떤 함수가 호출될지 이미 결정되어 있다.  
+ 가상함수는 동적바인딩으로, 컴파일 시점에 정해지지 않고, 런타임 때 정해진다.  
++ 동적바인딩은 포인터가 가리키는 객체에 따라 함수를 호출한다.
+ 오버라이딩 without 가상함수 -> 기반클래스 실행, 정적방인딩  
+ 오버라이딩 with 가상함수 -> 파생클래스 실행, 동적바인딩  
++ 기반클래스의 가상함수는 말 그대로 가상에 있는 함수라고 생각하면 될 듯?  

- 오버라이딩된 함수는 함수 뒤에 override를 붙여주는 게 좋다.
```cs
void func() override {}
```

---

### 추상클래스 & 인터페이스
- 순수가상함수가 하나라도 있으면 추상클래스라고 한다.  
근데, 순수가상함수로만 이루어져 있는 추상클래스를 특별히 인터페이스라고 한다.  
- 추상클래스는 객체를 만들 수 없는데, 왜지? 
순수가상함수는 본체가 없다? 말 그대로 가상함수니까 없다고 봐야하나?  
```cs
Shape s;	// error!!
Shape* s1;	// 포인터 선언은 가능하다.
Shape* s2 = new Shape; // error!!
```

- 보통 파생클래스에서는 순수가상함수의 오버라이딩 함수는 일반함수(가상함수X)로 쓴다.  
단, override 붙여주는 게 좋음.

### 객체의 포인터?
- 클래스에 가상함수가 하나라도 있으면 객체 내부적으로 포인터가 하나 생긴다.  
클래스 전용 가상 테이블이 생겨서 생성된 포인터가 가상 테이블을 가리킨다.  
가상테이블은 클래스의 가상함수를 가리킨다.  
- 객체 - 가상 테이블 -> 가상함수 (2중 포인터 방식)

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

- (순수)가상함수가 const면, 오버라이딩 함수들도 const를 붙여야한다.
```cs
Phone() {}; // warning! 컴파일러가 알아서 기본 생성자 만들어주기 때문에~
Phone() = default;  // oK!
```
```cs
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
```

### 상속 업캐스팅 vs 인터페이스
상속 업캐스팅 < 인터페이스  
상속은 결합도가 강하고, 다중 상속이 어렵다.
인터페이스는 상속에 비해 결합도가 낮고, 한 클래스가 여러 인터페이스를 구현하여 다중 상속 효과를 얻을 수 있다.  
유연성 및 협업 용이성 증가  
But, 인터페이스 수정 및 추가하면 곤란해진다.

### 연산자 오버로딩
기본형
```cs
int + int -> int operator+(int& other)
char + char -> char operator+(char& other)
int - int -> int operator-(int& other)
int + float -> int operator+(float& other)
```
```cs
/* 클래스 내에서 연산자 오버로딩 */
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

위와 같이 짜면 연산식의 왼쪽 항이 항상 클래스객체? 여야 한다. (return 데이터형 때문)  
따라서 클래스 외부에 짜는게 좋다.  
```cs
ComplexNumber operator+(const ComplexNumber& lhs, const ComplexNumber& rhs) {
    return ComplexNumber(lhs.getNum1() + rhs.getNum1(), lhs.getNum2() + rhs.getNum2());
}
```

friend를 붙여서 클래스 내에 선언하고, 외부에서 정의하는 게 가장 좋은 방법이다.
```cs
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
```

연산자 오버로딩의 파라미터는 적어도 하나는 사용자 정의 타입이어야 한다.
```cs
int operator+(int a, int b) { // error
}
```

### 연산자 오버로딩과 펑터
연산자 오버로딩을 함수처럼 만들 수도 있다.
```cs
int operator()(int a, int b){
    return a + b;
}
```

펑터는 함수의 상태를 저장할 수 있다.
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
    auto t = cmp(); // 펑터!
    t(3);
    t(7);   // 결과 10이 된다.
}
```

### 증감연산자의 오버로딩
```cs
// 전위 증가 연산자 (++Point)
Point& operator++() {
    ++x; // x 증가
    ++y; // y 증가
    return *this; // 자기 자신 반환
}

// 후위 증가 연산자 (Point++)
Point operator++(int) {
    Point temp = *this; // 현재 상태 저장
    ++(*this);          // 전위 증가 호출
    return temp;        // 저장된 상태 반환
}
```
##### [] 연산자(벡터를 배열로)의 오버로딩도 가능하다.

### friend 클래스, 멤버 함수, 전역 함수
#### friend 클래스
class 전체를 public으로 접근 가능
#### friend 멤버 함수
해당 class에서 지정한 멤버 함수만 접근 가능
#### friend 전역 함수
접근 지정자를 무시하고 클래스 내부 멤버에 접근  
