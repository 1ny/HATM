#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int getRandom(int a, int b) { // a부터 b까지의 난수 생성
	return a + rand() % (b - a + 1);
}
//
//// 벽돌 밑으로 떨어뜨리기
//void fall() {
//	for (int col = 0; col < w; col++) {
//		for (int i = 0; i < h - 1; i++) {
//			for (int j = 0; j < h-1-i; j++) {
//				if (tmp[j][col] != 0 && tmp[j + 1][col] == 0) {
//					tmp[j + 1][col] = tmp[j][col];
//					tmp[j][col] = 0;
//				}
//			}
//		}
//	}
//}

int main() {
	srand(time(0));
	const char colors[] = { 'R', 'G', 'B', 'C', 'M', 'Y', 'W' };

	int T = 50;
	int n = 50;
	int k = 15;

	cout << T << endl;
	while (T--) {
		cout << n << " " << k << endl;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				int a = getRandom(0, 6);
				cout << colors[a];
			}
			cout << endl;
		}

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				int e = getRandom(1, 100);
				cout << e << " ";
			}
			cout << endl;
		}
	}
}