#include <iostream>
#include <algorithm>
using namespace std;

int main() {
	int n, k;
	int coin[10];
	int sum = 0;

	cin >> n >> k;
	for(int i=0; i<n; i++)
		cin >> coin[i];

	// 1000원, 500원, 100원을 최대로
	// 4 + 1 + 2 + 1 + 4 = 12

	int cnt = 0;
	for (int i = 0; i < n; i++) {
		if (k < coin[n - i - 1]) continue;
		int c = k / coin[n - i - 1];
		k -= c * coin[n-i-1];
		cnt += c;
	}

	cout << cnt;
}