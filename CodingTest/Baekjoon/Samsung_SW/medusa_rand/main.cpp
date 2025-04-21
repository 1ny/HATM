#include <iostream>
#include <ctime>
#include <cstring>

using namespace std;

int getRandom(int a, int b) {
	return a + rand() % (b - a + 1);
}

int main() {
	srand(time(0));

	int n = 6;
	int m = 5;
	cout << n << " " << m << "\n";

	int sr = getRandom(0, n - 1);
	int sc = getRandom(0, n - 1);
	int er = getRandom(0, n - 1);
	int ec = getRandom(0, n - 1);
	cout << sr << " " << sc << " " << er << " " << ec << endl;

	for (int i = 0; i < m; i++) {
		int mr = getRandom(0, n - 1);
		int mc = getRandom(0, n - 1);
		cout << mr << " " << mc << " ";
	}
	cout << endl;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int num = getRandom(0, 1);
			if ((i == sr && j == sc) || (i == er && j == ec)) num = 0;
			cout << num << " ";
		}
		cout << endl;
	}

}