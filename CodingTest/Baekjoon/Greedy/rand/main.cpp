#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
using namespace std;

int main() {
	srand(time(0));

	int n = 100000;
	for (int i = 0; i < n; i++) {
		int a = 1 + rand() % 12;
		int b = 1 + rand() % 28;
		int c = 1 + rand() % 12;
		int d = 1 + rand() % 28;
		cout << a << " " << b << " " << c << " " << d << endl;
	}
#if 0
	int sm, sd, em, ed;
	pair<pair<int, int>, pair<int, int>> date[10];
	for (int i = 0; i < 10; i++) {
		cin >> sm >> sd >> em >> ed;
		date[i].first = {sm, sd};
		date[i].second = { em, ed };
	}

	for (int i = 0; i < 10000; i++) {
		for (int j = 0; j < 10; j++) {
			cout << date[j].first.first << " ";
			cout << date[j].first.second << " ";
			cout << date[j].second.first << " ";
			cout << date[j].second.second << endl;
		}
	}
#endif
}