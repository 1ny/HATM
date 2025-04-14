#include <iostream>
#include <algorithm>
using namespace std;

int main() {
	int n;
	int loop[100000];

	cin >> n;
	for(int i=0; i<n; i++)
		cin >> loop[i];

	sort(loop, loop+n);

	int maxRet = 0;
	for (int i = 1; i <= n; i++) {
		int comp = loop[n - i] * i;
		if (comp > maxRet) maxRet = comp;
	}

	cout << maxRet;
}