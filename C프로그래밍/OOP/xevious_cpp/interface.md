### 추상클래스 및 인터페이스 in C++
순수 가상함수를 하나라도 가지면 추상 클래스라고 한다.  
추상 클래스는 해당 클래스의 인스턴스(객체)를 만들 수가 없다.  
즉, 오로지 자식 클래스를 통해서만 인스턴스(객체)를 만들 수 있다는 말!  
class IGame abstract {} 라고도 함

```cs
class Shape
{
    public:
        virtual void Draw() = 0;
};

class Rect : public Shape
{
    public:
        virtual void Draw() {} // 구현부
};
```

### 인터페이스는 뭘까??
interface는 public속성을 가지며 함수를 선언하면 특별히 지정하지 않아도 순수 가상함수로 선언된다.  
그러니까 인터페이스로 필요한 함수를 먼저 정의하고, 그걸 추상 클래스가 상속 받아서 자식 클래스에게 강제성을 부여하는 건가?  
근데 인터페이스는 아직 표준이 아니라서, 사실상 추상 클래스가 인터페이스라고 생각하면 된다?  

```cs
__interface C_ANIMAL_INTERFACE
{
    void move();
};
class C_ANIMAL abstract : public C_ANIMAL_INTERFACE
{
private:
    int m_nHp;
public:
    C_ANIMAL();
    void setHp(int nHp);
    int getHp();
};
class C_CAT : public C_ANIMAL
{
private:

public:
    virtual void move();
};
```

### 인터페이스를 추가하게 된다면?
만약 각 게임들이 이미 다 구현했는데, 인터페이스를 추가하고자 한다면?  
2000개의 게임을 다 변경하기는 쉽지 않으므로...  
추상 클래스, 즉 인터페이스의 자식 클래스를 만들어서 이미 구현한 사람들에게는   
추가 인터페이스 강제성을 부여하지 않도록 할 수 있다.