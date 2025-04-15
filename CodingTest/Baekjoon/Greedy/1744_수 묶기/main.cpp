#include <iostream>
#include <algorithm>
using namespace std;
#define MAX 50

int main() {
	int n;
	int arr[MAX];
	int ret = 0;
	int cntZero = 0;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
		if (arr[i] == 0) cntZero;
	}
	sort(arr, arr + n);
	for (int i = 0; i < n; i++) {
		if (arr[i] < 0 && cntZero != 0) cntZero--;
		else if (arr[i] < 0 && cntZero == 0) ret -= arr[i];
		else if (arr[i] == 0) 
	}
}