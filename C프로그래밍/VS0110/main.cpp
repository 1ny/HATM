#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#if 0
#include <iostream>

// constexpr 함수 정의
// compile 할 때 에러가 난다.
consteval int square_compile(int x) {
    return x * x;
}

// 일반 함수 정의
int square_runtime(int x) {
    return x * x;
}

constexpr int triangle(int b, int h) {
    return (b * h / 2);
}

int main() {
    // 컴파일 타임 평가
    constexpr int result1 = square_compile(5); // 컴파일 타임에 계산됨
    std::cout << "Compile-time result: " << result1 << std::endl;

    // 런타임 평가
    int value = 10;
    int result2 = square_compile(value); // 런타임에 계산됨
    std::cout << "Runtime result: " << result2 << std::endl;

    // 일반 함수는 항상 런타임에 실행됨
    int result3 = square_runtime(5);
    std::cout << "Runtime result (normal function): " << result3 << std::endl;

#if 0
    int a;
    std::cin >> a;
    // value가 컴파일 할 때 인자값이 결정이 아직 안났기 때문에 에러남.
    constexpr int result1 = square_compile(a); // 컴파일 타임에 계산됨
    std::cout << "Compile-time result: " << result1 << std::endl;
#endif

    int blength, height;
    cin >> blength >> height;
    cout << "Tri: " << triangle(blength, height) << endl;

    return 0;
}
#endif

#if 0
constexpr int arr_size(int s) {
    return s;
}

int main() {
    constexpr int size = 10;

#if 1
    int a = arr_size(size);
    int arr1[a];
#endif

    constexpr int b = arr_size(size);
    int arr2[b];
}

#endif

#if 0
int main() {
    int a = 11;
    constexpr int b = 22;   // 컴파일 할 때 값을 결정한다. -> 컴파일 상수
    //constexpr int a_runtime = a;    // 컴파일 상수 변수에 런타임 상수를 넣으려고 했기에 error
    int d = b;  // 런타임 변수에 컴파일 상수를 넣는 건 가능
    const int e = b;    // const는 컴파일/런타임 둘다 가능하므로 가능
    const int f = a;
    //consteval int b_runtime = 33;

}
#endif

#if 0
int add(int a, int b) {
    return a + b;
}

const int add_cst(int a, int b) {
    return a + b;
}

constexpr int add_expr(int a, int b) {
    return a + b;
}

consteval int add_eval(int a, int b) {
    return a + b;
}

consteval int test = 10;    // consteval 변수는 전역변수로만 정의할 수 있음.

int main() {
    constexpr int a_compile = 10;
    constexpr int b_compile = 20;
    int a_runtime = 22;
    int b_runtime = 33;

    int test_gen1 = add(a_compile, b_compile);
    int test_gen2 = add_cst(a_compile, b_compile);
    int test_gen3 = add_expr(a_compile, b_compile);
    int test_gen4 = add_eval(a_compile, b_compile);

    int test_gen5 = add(a_runtime, b_runtime);
    int test_gen6 = add_cst(a_runtime, b_runtime);
    int test_gen7 = add_expr(a_runtime, b_runtime);
    //int test_gen8 = add_eval(a_runtime, b_runtime); // error

    //constexpr int test_expr1 = add(a_compile, b_compile);     // error
    //constexpr int test_expr2 = add_cst(a_compile, b_compile); // error
    constexpr int test_expr3 = add_expr(a_compile, b_compile);  
    //constexpr int test_expr4 = add_eval(a_compile, b_compile); // error
    /* run_time은 다 안됨! */

    /* consteval 변수는 지역변수에 선언할 수 없음.*/
    //consteval int test_eval = add_eval(a_compile, b_compile);

#if 0
    // 컴파일 할 때 이미 a_compile와 b_compile이 결정이 되어있으므로
    int r = add_expr(a_compile, b_compile);
    // r은 컴파일, 런타임 둘다 변경될 수 있으므로 가능
    int r1 = add_eval(a_compile, b_compile);

    // 컴파일 할 때 a_runtime과 b_runtime 은 결정되어 있지 않으므로, 이 함수는 런타임 중에 호출되어 실행된다.
    int r2 = add_expr(a_runtime, b_runtime);
    // add_eval은 반드시 컴파일 때 실행되어야 하는데,런타임 변수를 넣어버림.
    //int r3 = add_eval(a_runtime, b_runtime);     // error

    // a_compile와 b_compile는 컴파일 상수이므로, 컴파일 상수에 반환값을 저장할 수 있게 된다.
    constexpr int R = add_expr(a_compile, b_compile);    
    // 컴파일 상수에 컴파일때만 실행되는 함수를 넣었기에 가능하다.
    constexpr int R1 = add_eval(a_compile, b_compile);
    // 컴파일 상수에 런타임에 실행되는 함수의 반환값을 넣으려고 했기 때문에 error!
    // constexpr int R2 = add(a_compile, b_compile); // error

    // 이게 문제인데, 컴파일 상수 R은 컴파일 할 때 결정이 나야하는 건데,
    // a_runtime과 b_runtime 은 런타임 상수로 함수의 반환값이 런타임 중에 결정되기 때문에 error!!!!
    //constexpr int R3 = add_expr(a_runtime, b_runtime);      // error!
    //constexpr int R4 = add_eval(a_runtime, b_runtime);        // error!

    // const는 컴파일 상수, 런타임 상수 둘다 가능하므로 이건 하능하다.
    const int m = add_expr(a_runtime, b_runtime); 
    // 이거는 함수 실행부터 안된다. add_eval은 런타임 전에 컴파일 할 때 인자값이 정해져야하기 때문.
    //const int m2 = add_eval(a_runtime, b_runtime);  // error
#endif

}
#endif

#if 0
int main() {
    int x = 3;
    int y = 5;

    int ret = [&x](int y) {
        x += y;
        return x;
    } (y);

    cout << ret << endl;
    cout << x;
}
#endif

#if 0
int main() {
    std::vector<int> vect = { 1, 2, 3, 4, 5 };
    // 벡터의 모든 요소를 출력하는 람다 함수
    std::for_each(vect.begin(), vect.end(), [](int n) {cout << n << ", "; });
    std::cout << std::endl;

    return 0;
}
#endif

#if 0
int main() {
    vector<int> number = { 1, 4, 6 ,8, 3 };
    int threshold = 5;

    for_each(number.begin(), number.end(), [threshold](int num) {
        if (num > threshold) {
            cout << num << ", ";
        }}
    );
}
#endif

#if 0
template <typename T>
T my_max(T a, T b) {
    if (a > b) return a;
    else return b;
}

int main() {
    int a = 3;
    int b = 4;
    double c = 1.1;
    double d = 2.2;
    auto r = 0;

    r = my_max<int>(a, b);
    cout << r << endl;
    double g = my_max<double>(c, d);
    cout << g << endl;

    string str1 = "AB";
    string str2 = "AC";
    string s = my_max<string>(str1, str2);
    cout << s << endl;
}

#endif

#if 0
template <class T>
T arraySum(T arr[], int size) {
    T sum = 0;

    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }

    // for(T val : arr) 이거는 왜 안되지?

    return sum;
}

int main() {
    int arr_int[3] = { 1, 2, 3 };
    float arr_float[3] = { 1.1, 2.2, 3.3 };

    int r = arraySum<int>(arr_int, 3);
    cout << r << endl;
}
#endif

#if 0
template <class T>
class Stack {
private:
    vector<T> elements;

public:
    void push(T a) {
        elements.push_back(a);
    }
    void pop() {
        if (!elements.empty()) {
            elements.pop_back();
        }
    }
    T top() {
        if (!elements.empty()) {
            return elements.back();
        }
    }
};

int main() {
    Stack<int> stack_int;
    stack_int.push(11);
    stack_int.push(22);
    stack_int.push(33);
    stack_int.push(44);
    cout << stack_int.top() << endl;
    stack_int.pop();
    stack_int.pop();
    cout << stack_int.top() << endl;

    Stack<double> stack_double;
    stack_double.push(1.1);
    stack_double.push(2.2);
    stack_double.push(3.3);
    stack_double.push(4.4);
    cout << stack_double.top() << endl;
    stack_double.pop();
    cout << stack_double.top() << endl;

    Stack<string> stack_string;
    stack_string.push("aaa");
    stack_string.push("bbb");
    stack_string.push("ccc");
    stack_string.push("ddd");
    cout << stack_string.top() << endl;
    stack_string.pop();
    cout << stack_string.top() << endl;
}
#endif

#if 0
template <class T>
class Sort {
private:
    T* arr;
public:
    void setArr(T* pArr) {
        this->arr = pArr;
    }
    void sort(T* arr, int n) {
        for (int j = 0; j < n; j++) {
            for (int i = 0; i < n-1; i++) {
                if (arr[i] > arr[i + 1]) { swap(arr[i], arr[i + 1]); }
            }
        }
    }
    void print(int n) {
        for (int i = 0; i < n; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    int arr_int[5] = { 4,1,5,7,2 };
    int n = 5;
    Sort<int> s;
    
    s.setArr(arr_int);
    s.print(n);
    s.sort(arr_int, n);
    s.print(n);

    string arr_str[7] = { "eee", "ddd", "ccc", "bbb", "ggg", "aaa","fff"};
    n = 7;
    Sort<string> s1;

    s1.setArr(arr_str);
    s1.print(n);
    s1.sort(arr_str, n);
    s1.print(n);
}
#endif

#if 0
template <class T>
class Queue {
private:
    vector<T> q;

public:
    void push(T a) {
        q.push_back(a);
    }
    void pop() {
        if (!q.empty()) {
            q.erase(q.begin());
        }
    }
    T top() {
        if (!q.empty()) return q.front();;
    }
};

int main() {
    Queue<int> q_int;

    q_int.push(11);
    q_int.push(22);
    q_int.push(33);
    q_int.push(44);
    q_int.pop();
    cout << q_int.top() << endl;
    q_int.pop();
    q_int.pop();
    cout << q_int.top() << endl;
}

#endif

#if 0
template <class T>
class Storage {
private:
    T data;

public:
    Storage() {};
    Storage(T a) : data(a) {};
    ~Storage() = default;

    void print() {
        cout << data << endl;
    }
};

template <>
class Storage<double> {
private:
    double data;

public:
    Storage() {};
    Storage(double a) : data(a) {};
    ~Storage() = default;

    void print() {
        cout << "double tpye 입니다." << endl;
    }
};

int main() {
    Storage<int> s1(10);
    s1.print();

    Storage<double> s2(1.1);
    s2.print();
}
#endif

#if 0
#include <iostream>
#include <vector>
#include <list>

int main() {
	std::vector<int> vect = { 1,2,3,4,5,6,7 };

	// range for
	// 요게 더 편리해서 많이 사용한다.
	// n은 일일이 복사해서 갖고 오는것이다.
	// 여기서 n +=1; 해봤자, 원래 벡터는 값이 그대로이다.
	// 그래서 vect의 값을 바꾸려면 참조로 갖고 와야 한다.

	for (int n : vect) { // (1)
		n += 1; // 갖고오는값을 +1 해주면 2,3,4.. 가출력되지만
		std::cout << n << ",";
	}
	std::cout << std::endl;

	for (int i = 0; i < vect.size(); i++) { //여전히 그대로다.
		std::cout << vect[i] << ",";
	}
    cout << endl;

    for (const auto& n : vect) { // (1)
        //n += 1; // 갖고오는값을 +1 해주면 2,3,4.. 가출력되지만
        std::cout << n << ",";
    }
    std::cout << std::endl;

    for (int i = 0; i < vect.size(); i++) { //여전히 그대로다.
        std::cout << vect[i] << ",";
    }
    cout << endl;

    for (int& n : vect) { // (1)
        n += 1; // 갖고오는값을 +1 해주면 2,3,4.. 가출력되지만
        std::cout << n << ",";
    }
    std::cout << std::endl;

    for (int i = 0; i < vect.size(); i++) { //여전히 그대로다.
        std::cout << vect[i] << ",";
    }
    return (0);
}
#endif

#if 0
#include <vector>

int main(void) {
    std::vector<int> v1 = { 1,2,3,4,5 }; // ok // 개인 추천
    std::vector      v2 = { 1,2,3,4,5 }; // ok C++ 17부터 초기값이 있다면 타입 인자 생략 가능
    // 컴파일러는 1,2,3..5가 int인지 알수 있기 때문

    //std::vector      v3; // error 초기값이 없는 경우 반드시 타입 인자를 전달해야 한다.
    // 초기값이 없어서 char인지 int인지 알길이 없다.
    std::vector<int> v4; // ok

    std::vector      v5(10, 3); // 10개를 3으로 초기화 하겠다는 의미, 타입 인자 생략 가능
    std::vector<int> v6(10); // 타입 인자가 필요하다. 
    // 10개가 int인지 double인지 알길이 없다.
    
    for (auto val : v5) {
        cout << val << " ";
    }
}
#endif

#if 0
#include <iostream>

class HugeClass {
public:
    int big_arr[1000000] = { 0, };

    HugeClass() {};
    ~HugeClass() {};
};

int main(void) {
    static int num = 0;

    while (1) {
        try {
            HugeClass* p = new HugeClass;
            std::cout << "HugeClass " << ++num << "개 생성" << std::endl;
        }
        catch (std::bad_alloc& exception) {
            std::cout << exception.what() << std::endl;
            break;
        }
    }
    return 0;
}
#endif

#if 0
class my_vector {
private:
    int* buffer;
    int size;

public:
    my_vector(int pSize) {
        size = pSize;

        buffer = new int[size];
        
        for (int i = 0; i < size; i++) {
            buffer[i] = 0;
        }
    }

    ~my_vector() {
        delete[] buffer;
    };

    void add(int data, int idx) {
        buffer[idx] = data;
    }
    
    void resize(int pSize) {
        int* tempBuf = new int[pSize];
        for (int i = 0; i < pSize; i++) {
            tempBuf[i] = 0;
        }

        memcpy(tempBuf, buffer, sizeof(buffer));

        delete[] buffer;
        buffer = tempBuf;

        size = pSize;
    }
    
    void print() {
        for (int i = 0; i < size; i++) {
            cout << buffer[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    my_vector vect(5);

    vect.add(3, 0);
    vect.add(5, 1);
    vect.print();

    vect.resize(8);
    vect.add(1, 7);
    vect.print();
    
    vect.resize(3);
    vect.print();

    vect.resize(10);
    vect.print();

    vect.resize(4);
    vect.print();
}
#endif

#if 1

#endif

#if 1

#endif