#include <iostream>
#include <vector>
#include <string>

using namespace std;

char arr[3][3] = {
	{'a', 'b', 'd'},
	{'e', 'w', 'z'},
	{'q','v', 'a'}
};

void Process(char a) {
	a = a + ('a' - 'A');

	for (auto& row : arr) {
		for (auto& val : row) {
			if (a == val) {

			}
		}
	}
}

void input() {
	char a;
	
	cin >> a;


}

int main() {



}

#if 0
int main() {
	char arr[3][3] = {
		{'a', 'b', 'E'},
		{'E', '2', 'W'},
		{'3', '2', '4'}
	};

	for (auto& row : arr) {
		for (auto& val : row) {
			if (val >= 'A' && val <= 'Z') cout << (char)(val + ('a' - 'A'));
			else if (val >= 'a' && val <= 'z') cout << (char)(val - ('a' - 'A'));
			else cout << (char)(val + 5);

			cout << " ";
		}
		cout << endl;
	}
}
#endif

#if 0
int main() {
	int arr[2][3];

	for (auto& row : arr) {
		for (auto& val : row) {
			cin >> val;
		}
	}

	for (auto& row : arr) {
		for (auto& val : row) {
			if (val == 0) cout << "#";
			else cout << val;
		}
		cout << endl;
	}
}
#endif

#if 0
int main() {
	char a;
	int cnt = 0;
	char arr[3][5] = {
		{'a', 'b', 'a', 'c', 'z'},
		{'c', 't', 'a', 'c', 'd'},
		{'c', 'c', 'c', 'c', 'a'}
	};

	cin >> a;

	for (auto& row : arr) {
		for (auto& val : row) {
			if (val == a) cnt++;
		}
	}

	if (cnt >= 7) cout << "세상에";
	else if (cnt >= 5) cout << "와우";
	else if (cnt >= 3) cout << "이야";
	else cout << "이런";
}
#endif

#if 0
int main() {
	char arr[] = { 'A', '1', '1', '1', '5', 'A', 'w', 'z' };
	char a;
	int cnt = 0;

	cin >> a;

	for (auto val : arr) {
		if (val == a) cnt++;
	}

	if (cnt >= 3) cout << "THREE";
	else if (cnt == 2) cout << "TWO";
	else if (cnt == 1) cout << "ONE";
	else cout << "NOTHING";

}
#endif

#if 0
int arr[3][3] = {
	{1, 1, 1},
	{1, 2, 1}, 
	{3, 6, 3}
};

int Count(int a) {
	int cnt = 0;

	for (auto& row : arr) {
		for (auto& val : row) {
			if (val == a) {
				cnt++;
			}
		}
	}

	return cnt;
}

int main() {
	int a;

	cin >> a;

	cout << Count(a);
}
#endif

#if 0
int main() {
	char a, b;
	char arr[] = { 'D', 'F', 'G', 'D', 'A', 'Q' };

	cin >> a >> b;

	for (auto& val : arr) {
		if (val >= a && val <= b) {
			cout << "발견!!!";
			return 0;
		}
	}

	cout << "미발견!!!";
}
#endif

#if 0
int main() {
	int arr[4][4] = {
		{1, 3, 6, 2},
		{4, 2, 4, 5},
		{6, 3, 7, 3},
		{1, 5, 4, 6}
	};
	int a;
	int valArr[100];
	int cnt = 0;

	cin >> a;

	for (auto& row : arr) {
		for (auto& val : row) {
			if (val > a) {
				valArr[cnt] = val;
				cnt++;
			}
		}
	}

	for(int i=0; i<cnt; i++) {
		cout << valArr[i] << " ";
	}
}
#endif

#if 0
int arr[2][5] = {
	{3, 2, 6, 2, 4},
	{1, 4, 2, 6, 5}
};

int KFC(int target) {
	for (auto& row : arr) {
		for (auto& val : row) {
			if (val == target) return 1;
		}
	}
	
	return 0;
}

int main() {
	int target;
	int retValue;

	cin >> target;

	retValue = KFC(target);

	if (retValue == 1) cout << "값이 존재합니다";
	else cout << "값이 없습니다";
}
#endif

#if 0
int main() {
	char str[8];
	char big[8] = {0,};
	char small[8] = {0,};
	int big_cnt = 0, small_cnt = 0;

	for (auto& val : str) {
		cin >> val;
	}

	for (auto& val : str) {
		if (val <= 'Z') {
			big[big_cnt] = val;
			big_cnt++;
		}
		else {
			small[small_cnt] = val;
			small_cnt++;
		}
	}

	cout << "big=" << big << endl;
	cout << "small=" << small << endl;
}
#endif

#if 0
int main() {
	string str = "StructPointer";
	char a;

	cin >> a;

	for (auto val : str) {
		if (val == a) {
			cout << "발견";
			return 0;
		}
	}

	cout << "미발견";
}
#endif

#if 0
int main() {
	int arr[7];
	int max, min;

	for (auto& val : arr) {
		cin >> val;
	}
	
	max = 0;
	min = arr[0];
	for (auto& val : arr) {
		if (val > max) max = val;
		if (val < min) min = val;
	}

	cout << "MAX=" << max << endl;
	cout << "MIN=" << min << endl;
}
#endif

#if 0
int main() {
	int arr[] = {3, 4, 1, 3, 2, 7, 3};
	int a;

	cin >> a;

	for (int i = 0; i < sizeof(arr) / sizeof(int); i++) {
		if (arr[i] == a) {
			cout << "발견";
			return 0;
		}
	}

	cout << "미발견";
}
#endif

#if 0
int main() {
	int a, b;
	int* p, * t;
	int temp;

	cin >> a >> b;

	p = &a;
	t = &b;

	temp = *p;
	*p = *t;
	*t = temp;

	cout << *p << " " << *t;
}
#endif

#if 0
int main() {
	char a, b, c;
	char* pa;
	char* pb;
	char* pc;

	cin >> a >> b >> c;

	pa = &a;
	pb = &b;
	pc = &c;

	*pa += 1;
	*pb += 1;
	*pc += 1;

	cout << *pa << " " << *pb << " " << *pc;
}
#endif

#if 0
int main() {
	int a;
	char gd;
	int* p;
	char* t;

	cin >> a >> gd;

	p = &a;
	t = &gd;

	cout << *p << " " << *t;
}
#endif

#if 0
int sum(int a, int b) {
	return a + b;
}

int comp(int a, int b) {
	return a - b;
}

void print(int t1, int t2) {
	cout << "합:" << t1 << endl;
	cout << "차:" << t2 << endl;
}

int main() {
	int a, b;

	cin >> a >> b;

	print(sum(a, b), comp(a, b));
}
#endif

#if 0
void input(int* a) {
	cin >> *a;
}

int main() {
	int a, b, c;
	int sum = 0;

	input(&a);
	input(&b);
	input(&c);

	sum = a + b + c;

	cout << sum;
}
#endif

#if 0
int yesOrNo() {
	int a;

	cin >> a;

	if (a % 3 == 0) return 7;
	else if (a % 3 == 1) return 35;
	else return 50;
}
int main() {
	cout << yesOrNo();
}
#endif

#if 0
void num(int a) {
	int arr[3][3];
	int cnt = 1;

	if (a < 10) {
		for (auto& row : arr) {
			for (auto& val : row) {
				val = cnt;
				cnt++;
			}
		}
	}
	else {
		for (int i = 0; i < 3; i++) {
			for (int j = 2; j >= 0; j--) {
				arr[i][j] = cnt;
				cnt++;
			}
		}
	}

	for (auto& row : arr) {
		for (auto& val : row) {
			cout << val;
		}
		cout << endl;
	}
}

int main() {
	int a;

	cin >> a;

	num(a);
}
#endif

#if 0
int arr[7][5] = {
	{1, 0, 0, 0 ,0},
	{1, 0, 1, 0, 0},
	{1, 1, 0, 1, 0},
	{1, 0, 1, 0, 0},
	{0, 1, 0, 0, 1},
	{0, 0, 0, 1, 0},
	{1, 1, 0, 0, 0}
};

void INPUT(int* a) {
	cin >> *a;
}

int PROCESS(int a) {
	int cnt = 0;

	for (int i = 0; i < 7; i++) {
		if (arr[i][a] == 1) {
			cnt++;
		}
	}

	return cnt;
}

int main() {
	int a;
	int cnt;

	INPUT(&a);
	cout << PROCESS(a);
}
#endif

#if 0
typedef struct {
	int x;
	int data[3];
} BBQ;

int main() {
	BBQ g;
	int sum = 0;

	cin >> g.x;
	for (auto& val : g.data) {
		cin >> val;
	}

	for (auto& val : g.data) {
		sum += val;
	}

	cout << sum << " " << g.x;
}
#endif

#if 0
char Calculator() {
	int score;

	cin >> score;

	if (score >= 90) return 'A';
	else if (score >= 80) return 'B';
	else if (score >= 70) return 'C';
	else return 'D';
}

int main() {
	cout << Calculator();
}
#endif

#if 0
void aToZ() {
	char a;

	cin >> a;

	if ((a - 'A') < ('Z' - a)) cout << 'A';
	else cout << 'Z';
}

int main() {
	aToZ();
}
#endif

#if 0
int main() {
	int a, b;
	int cnt = 10;
	vector<vector<int>> v(6, vector<int>(3, 0));

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 6; j++) {
			v[j][i] = cnt;
			cnt++;
		}
	}
	
	cin >> a >> b;
	
	for(int i=a; i<=b; i++) {
		v[i] = {7, 7, 7};
	}

	for (auto& row : v) {
		for (auto& val : row) {
			cout << val << " ";
		}
		cout << endl;
	}
}
#endif