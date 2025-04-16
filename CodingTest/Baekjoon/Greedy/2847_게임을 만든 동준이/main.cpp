#if 1
#include <iostream>
using namespace std;
#define MAX 100

int n;
int lev[MAX];
long int sum;

int main() {
	cin >> n;

	for (int i = 0; i < n; i++) {
		cin >> lev[i];
	}

	int paral = 1;
	for (int i = 0; i < n-1; i++) {
		if (lev[i] >= lev[i + 1])
		{
			sum += lev[i] - lev[i+1] + 1;
			lev[i] = lev[i + 1] - 1;
			for (int j = i; j > 0; j--) {
				if (lev[j] <= lev[j - 1])
				{
					sum += lev[j - 1] - lev[j] + 1;
					lev[j - 1] = lev[j] - 1;
				}
			}
		}
		else
		{
			//paral = 1;
		}
	}

	cout << sum;
	/*
	N개의 레벨
	레벨을 클리어할 때마다 점수 합 -> 플레이어의 점수
	쉬운 레벨이 어려운 레벨보다 점수를 많이 받는 경우
	--> 특정 레벨의 점수를 감소
	몇번 감소? -1이 1번 감소임

	*/
}
#endif

#if 0
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
	srand(time(0));
	int n = 5;
	int x;
	for (int i = 0; i < n; i++) {
		x = 1 + rand() % 9;
		cout << x << endl;
	}
}
#endif