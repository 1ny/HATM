#include <iostream>
#include <algorithm>
using namespace std;
#define MAX 50

int main() {
	int n;
	int a[MAX];
	int b[MAX];

	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}

	for (int i = 0; i < n; i++) {
		cin >> b[i];
	}
	
	sort(a, a + n);
	sort(b, b + n);
	int sum = 0;
	for (int i = 0; i < n; i++) {
		sum += a[i] * b[n-i-1];
	}

	cout << sum;
}