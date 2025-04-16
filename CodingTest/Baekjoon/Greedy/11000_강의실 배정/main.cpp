#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define MAX 20

int main() {
	int n;
	vector<pair<long, long>> sch;
	vector<long> endT;

	cin >> n;
	for (int i = 0; i < n; i++) {
		long si, ti;
		cin >> si >> ti;
		sch.push_back({ si, ti });
	}

	endT.push_back(sch[0].second);
	int cnt = 1;
	for (int i = 1; i < n; i++) {
		
	}

	cout << cnt;
}