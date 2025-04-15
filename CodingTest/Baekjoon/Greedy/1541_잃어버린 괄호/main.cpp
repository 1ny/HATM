#include <iostream>
#include <cstring>
#include <vector>
#include <string>
using namespace std;
#define MAX 50

string oper;

int main() {
	cin >> oper;
	string buf;
	vector<int> num;
	int ret = 0;
	int flag = 0;

	for (int i = 0; i < oper.length(); i++) {
		if (oper[i] >= '0' && oper[i] <= '9')
		{
			buf += oper[i];
		}
		else // 사칙연산일 경우
		{
			if(flag == 0) ret += stoi(buf);
			else ret -= stoi(buf);
			if (oper[i] == '-')
			{
				flag = 1;
			}
			buf.clear();
		}
		if (i == oper.length() - 1) {
			if (flag == 0) ret += stoi(buf);
			else ret -= stoi(buf);
		}
	}

	cout << ret;

	return 0;
}