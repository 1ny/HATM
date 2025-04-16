#include <iostream>
#include <math.h>
#include <cstdlib>
#include <string>
using namespace std;

#define MAX 1000000

int arr[MAX];

int main() {
	string str;
	cin >> str;
	int one = 0, zero = 0;
	char comp = str[0];
	if (comp == '1') one++;
	else zero++;
	for (int i = 1; i < str.length(); i++) {
		if (str[i] != comp)
		{
			comp = str[i];
			if (str[i] == '1')
			{
				one++;
			}
			else
			{
				zero++;
			}
		}
	}

	if (one > zero) cout << zero;
	else cout << one;
}