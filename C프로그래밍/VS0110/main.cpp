#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#if 0
#include <iostream>

// constexpr �Լ� ����
// compile �� �� ������ ����.
consteval int square_compile(int x) {
    return x * x;
}

// �Ϲ� �Լ� ����
int square_runtime(int x) {
    return x * x;
}

constexpr int triangle(int b, int h) {
    return (b * h / 2);
}

int main() {
    // ������ Ÿ�� ��
    constexpr int result1 = square_compile(5); // ������ Ÿ�ӿ� ����
    std::cout << "Compile-time result: " << result1 << std::endl;

    // ��Ÿ�� ��
    int value = 10;
    int result2 = square_compile(value); // ��Ÿ�ӿ� ����
    std::cout << "Runtime result: " << result2 << std::endl;

    // �Ϲ� �Լ��� �׻� ��Ÿ�ӿ� �����
    int result3 = square_runtime(5);
    std::cout << "Runtime result (normal function): " << result3 << std::endl;

#if 0
    int a;
    std::cin >> a;
    // value�� ������ �� �� ���ڰ��� ������ ���� �ȳ��� ������ ������.
    constexpr int result1 = square_compile(a); // ������ Ÿ�ӿ� ����
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
    constexpr int b = 22;   // ������ �� �� ���� �����Ѵ�. -> ������ ���
    //constexpr int a_runtime = a;    // ������ ��� ������ ��Ÿ�� ����� �������� �߱⿡ error
    int d = b;  // ��Ÿ�� ������ ������ ����� �ִ� �� ����
    const int e = b;    // const�� ������/��Ÿ�� �Ѵ� �����ϹǷ� ����
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

consteval int test = 10;    // consteval ������ ���������θ� ������ �� ����.

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
    /* run_time�� �� �ȵ�! */

    /* consteval ������ ���������� ������ �� ����.*/
    //consteval int test_eval = add_eval(a_compile, b_compile);

#if 0
    // ������ �� �� �̹� a_compile�� b_compile�� ������ �Ǿ������Ƿ�
    int r = add_expr(a_compile, b_compile);
    // r�� ������, ��Ÿ�� �Ѵ� ����� �� �����Ƿ� ����
    int r1 = add_eval(a_compile, b_compile);

    // ������ �� �� a_runtime�� b_runtime �� �����Ǿ� ���� �����Ƿ�, �� �Լ��� ��Ÿ�� �߿� ȣ��Ǿ� ����ȴ�.
    int r2 = add_expr(a_runtime, b_runtime);
    // add_eval�� �ݵ�� ������ �� ����Ǿ�� �ϴµ�,��Ÿ�� ������ �־����.
    //int r3 = add_eval(a_runtime, b_runtime);     // error

    // a_compile�� b_compile�� ������ ����̹Ƿ�, ������ ����� ��ȯ���� ������ �� �ְ� �ȴ�.
    constexpr int R = add_expr(a_compile, b_compile);    
    // ������ ����� �����϶��� ����Ǵ� �Լ��� �־��⿡ �����ϴ�.
    constexpr int R1 = add_eval(a_compile, b_compile);
    // ������ ����� ��Ÿ�ӿ� ����Ǵ� �Լ��� ��ȯ���� �������� �߱� ������ error!
    // constexpr int R2 = add(a_compile, b_compile); // error

    // �̰� �����ε�, ������ ��� R�� ������ �� �� ������ �����ϴ� �ǵ�,
    // a_runtime�� b_runtime �� ��Ÿ�� ����� �Լ��� ��ȯ���� ��Ÿ�� �߿� �����Ǳ� ������ error!!!!
    //constexpr int R3 = add_expr(a_runtime, b_runtime);      // error!
    //constexpr int R4 = add_eval(a_runtime, b_runtime);        // error!

    // const�� ������ ���, ��Ÿ�� ��� �Ѵ� �����ϹǷ� �̰� �ϴ��ϴ�.
    const int m = add_expr(a_runtime, b_runtime); 
    // �̰Ŵ� �Լ� ������� �ȵȴ�. add_eval�� ��Ÿ�� ���� ������ �� �� ���ڰ��� ���������ϱ� ����.
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
    // ������ ��� ��Ҹ� ����ϴ� ���� �Լ�
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

    // for(T val : arr) �̰Ŵ� �� �ȵ���?

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
        cout << "double tpye �Դϴ�." << endl;
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
	// ��� �� ���ؼ� ���� ����Ѵ�.
	// n�� ������ �����ؼ� ���� ���°��̴�.
	// ���⼭ n +=1; �غ���, ���� ���ʹ� ���� �״���̴�.
	// �׷��� vect�� ���� �ٲٷ��� ������ ���� �;� �Ѵ�.

	for (int n : vect) { // (1)
		n += 1; // ������°��� +1 ���ָ� 2,3,4.. ����µ�����
		std::cout << n << ",";
	}
	std::cout << std::endl;

	for (int i = 0; i < vect.size(); i++) { //������ �״�δ�.
		std::cout << vect[i] << ",";
	}
    cout << endl;

    for (const auto& n : vect) { // (1)
        //n += 1; // ������°��� +1 ���ָ� 2,3,4.. ����µ�����
        std::cout << n << ",";
    }
    std::cout << std::endl;

    for (int i = 0; i < vect.size(); i++) { //������ �״�δ�.
        std::cout << vect[i] << ",";
    }
    cout << endl;

    for (int& n : vect) { // (1)
        n += 1; // ������°��� +1 ���ָ� 2,3,4.. ����µ�����
        std::cout << n << ",";
    }
    std::cout << std::endl;

    for (int i = 0; i < vect.size(); i++) { //������ �״�δ�.
        std::cout << vect[i] << ",";
    }
    return (0);
}
#endif

#if 0
#include <vector>

int main(void) {
    std::vector<int> v1 = { 1,2,3,4,5 }; // ok // ���� ��õ
    std::vector      v2 = { 1,2,3,4,5 }; // ok C++ 17���� �ʱⰪ�� �ִٸ� Ÿ�� ���� ���� ����
    // �����Ϸ��� 1,2,3..5�� int���� �˼� �ֱ� ����

    //std::vector      v3; // error �ʱⰪ�� ���� ��� �ݵ�� Ÿ�� ���ڸ� �����ؾ� �Ѵ�.
    // �ʱⰪ�� ��� char���� int���� �˱��� ����.
    std::vector<int> v4; // ok

    std::vector      v5(10, 3); // 10���� 3���� �ʱ�ȭ �ϰڴٴ� �ǹ�, Ÿ�� ���� ���� ����
    std::vector<int> v6(10); // Ÿ�� ���ڰ� �ʿ��ϴ�. 
    // 10���� int���� double���� �˱��� ����.
    
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
            std::cout << "HugeClass " << ++num << "�� ����" << std::endl;
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