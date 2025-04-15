#include <iostream>
#include <vector>
using namespace std;

#define MAX 1000000

int main() {
	int T, N;

	cin >> T;
	for (int i = 0; i < T; i++) {
		cin >> N;
		long int sum = 0;
		int max = 0;
		vector<int> juga;
		for (int j = 0; j < N; j++) {
			int x;
			cin >> x;
			juga.push_back(x);
		}
		for (int j = N - 1; j >= 0; j--) {
			if (juga[j] >= max) max = juga[j];
			else {
				sum += max - juga[j];
				//cout << (max - juga[j]) << "만큼 더함\n";
			}
		}
		cout << sum << endl;
	}

	return 0;
}

/*
2+4+4 = 10
(2+2)+1 = 5
*/