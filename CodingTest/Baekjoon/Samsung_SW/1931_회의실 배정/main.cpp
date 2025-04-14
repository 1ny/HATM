#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

#define MAX 100000

#define START second
#define END	first

int n;
pair<int, int> meet[MAX];

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> meet[i].START >> meet[i].END;
	}

	sort(meet, meet+n);

	//for (int i = 0; i < n; i++) {
	//	cout << meet[i].START << " " << meet[i].END << endl;
	//}
	//cout << endl;

	int ret = 0;
	int curT = 0;
	for (int i = 0; i < n; i++) {
		if (meet[i].START >= curT)
		{
			//cout << meet[i].START << " " << meet[i].END << endl;
			ret++;
			curT = meet[i].END;
		}
	}

	cout << ret;

	return 0;
}