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
	N���� ����
	������ Ŭ������ ������ ���� �� -> �÷��̾��� ����
	���� ������ ����� �������� ������ ���� �޴� ���
	--> Ư�� ������ ������ ����
	��� ����? -1�� 1�� ������

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