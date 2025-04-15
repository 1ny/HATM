#include <iostream>
#include <algorithm>
using namespace std;

int main() {
	int n;
	int a[1000];

	cin >> n;

	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}

	sort(a, a + n);
	int sum[1000];
	int sumA = 0;
	for (int i = 0; i < n; i++) {
		sumA += a[i];
		sum[i] = sumA;
	}

	int ret = 0;
	for (int i = 0; i < n; i++) {
		ret += sum[i];
	}

	cout << ret;
}