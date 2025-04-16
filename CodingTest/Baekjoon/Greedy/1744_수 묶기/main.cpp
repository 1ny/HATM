#if 0
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
		if (arr[i] == 1) ret++;
	}
	sort(arr, arr + n);
	int first = 0;
	for (int i = 0; i < n; i++) {
		if (arr[i] > 0) {
			if (i % 2 == 1) ret += first;
			break;
		}
		if (i % 2 == 0) {
			first = arr[i];
			if (i == n - 1) ret += first;
			continue;
		}
		ret += first * arr[i];
	}

	first = 0;
	for (int i = n - 1; i >= 0; i--)
	{
		if (arr[i] <= 1) {
			if ((n - i) % 2 == 0) ret += first;
			break;
		}
		if ((n - i) % 2 == 1) {
			first = arr[i];
			if (i == 0) ret += first;
			continue;
		}
		ret += first * arr[i];
	}

	cout << ret;
}
#endif

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n;
vector<int> numP;
vector<int> numM;
int sum;

int cal(vector<int> vect) {
	int ret = 0;
	while(!vect.empty()) {
	//for(int i=0; i<vect.size(); i++) {
		if (vect.size() > 1) {
			ret += *(vect.end() - 1) * *(vect.end() - 2);
			vect.pop_back();
			vect.pop_back();
		}
		else if (vect.size() == 1) {
			ret += vect[0];
			vect.pop_back();
		}
		else
		{
			break;
		}
	}
	return ret;
}

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		int x = 0;
		cin >> x;
		if (x == 1) sum++;
		else if (x > 0) numP.push_back(x);
		else numM.push_back(x);
	}

	sort(numP.begin(), numP.end());
	sort(numM.begin(), numM.end(), greater<>());

	sum += cal(numM);
	sum += cal(numP);

	cout << sum;
}