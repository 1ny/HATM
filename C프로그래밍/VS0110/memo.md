### constexpr & consteval
- constexpr 함수 : 컴파일할 때 값이 결정되어 있으면(인자가 컴파일 상수이면), 컴파일할 때 함수 바로 실행  
인자가 컴파일 상수가 아니면(런타임 상수면), 일반 함수로 동작한다? 즉, 런타임에 함수를 실행한다.  
그러면 반환값을 저장할 변수의 타입은 상관이 없나????
- consteval 함수 : constexpr 함수는 런타임 때와 컴파일 때 둘다 실행될 수 있는 반면, consteval 함수는 런타임 때 실행할 수 없다.  
즉, 인자값과 반환값이 둘다 컴파일 때 결정되어야 한다는 뜻!!
- 일반 함수 : 런타임 때 실행된다.
- const : 컴파일과 런타임 상수 둘다 가능.

근데, constexpr랑 consteval 은 그러면 언제 쓰이는 거지?  
변수는 뭐 런타임 중에 변경 불가능하도록 하려고 하는 건 이해가 되는데,  
함수는 뭐하러 쓰지..????

### 람다 함수
왜 쓰지?
함수가 한번만 쓰일 때? 굳이 함수를 정의하지 않고, 코드 안에 간결하게 쓸 수 있다?  
굳이...
```cs
[캡처 복사/참조] (param)->returnVal {
	...
} (param value);
```

[캡처 복사/참조]
- [변수] : 복사 -> 외부 변수 변경 X, 오 외부 변수 변경하려고 하면 에러
- [&변수] : 참조 -> 외부 변수에 변경내용 적용
- [=] : 전체 복사
- [&] : 전체 참조
```cs
int main() {
	int x = 3;
	int y = 5;

	int ret = [&x] (int y) {
		return x+y;
	} (y);

	cout << ret << endl;
}
```

### 템플릿
1. 함수
```cs
template <typename T>
T add(T a, T b) {
	return (a + b);
}

int main() {
	add<int>(11, 22);
}
```
+ 만약 리턴값과 파라미터 값의 타입이 다르면?


### 벡터, vector
- vector는 포인터가 아니다!
```cs
vector<int> vect = {1, 2, 3, 4};
int tt = *(vect+3);	// error
```
- vector의 인덱스
```cs
vect[i];
vect.at(i);
```

- vector 의 range for
```cs
for(auto val : vect) {
	cout << val << " ";
}

for(cont auto& val : vect) {
	// val += 1;	// error! 바꾸는게 아예 접근 불가능
	cout << val << " ";
}
```
```cs
/* 값을 바꿀 경우 */
for(auto& val : vect) {
	cout << val << " ";
}
```

### 컨테이너 특징
array, vector는 연속되어 있어 검색이 빠르지만, 넣고 빼는 건 느림  
array는 정해진 크기, vector는 동적 배열로 유연한 크기  
vector가 일렬로 되어있어서 캐쉬 히트가 높다는데, 뭔말인진...  
반면, list는 요소들이 떨어져 있어 요소 접근이 어렵지만, 삽입 삭제가 빠르다.  

### 반복자, iterator
```cs
for(it = vector명.begin(); it != vector명.end(); ++it) { }
```

### array 라이브러리
std::array<type, size> 변수명 = {};
변수명.(...) 로 멤버함수 사용 가능하다.

### vector의 resize와 capacitor
vector는 resizing 할 수 있는데, 실제로 메모리를 지우는 것이 아니라 사이즈만 줄일 뿐이다.  
따라서 capacitor로 출력해보면 원래 사이즈 크기로 나옴.  
linked list 처럼 그 연결되는 대가리?만 사라지는 거지, 실제 데이터는 남아있다.

메모리 공간 예약 -> reserve로  

### 예외 처리를 미루는 걸 Stack Unwinding 이라고 한다.
main -> bts -> exo -> ses 순으로 함수를 호출한다고 할 때  
ses에서 예외 처리가 발생했는데 처리를 안해주면 exo에 넘어가고,  
exo도 처리를 안해주면 bts에 넘어가고...  
예외를 던지는 함수는 아래와 같이 표시하는 게 좋다. (필수 아님)
```cs
int bts(int a, int b) throw(int) 
{
...
}
```

#### STL에서 기본으로 제공해주는 예외 클래스도 있다.
#### 사용자 정의 예외 클래스를 만드는 것도 가능하다.

