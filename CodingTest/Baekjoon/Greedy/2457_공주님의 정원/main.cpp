#include <iostream>
#include <vector>
using namespace std;

#define X first
#define Y second

int main() {
	int n;
	vector<pair<int, int>> date;	// ���� ����� ���ÿ� ũ�Ⱑ 0�� ���Ͱ� ������� vector�� �߰��� �� []�� �����ϸ� �ȵǰ� push_back���� �ؾ���
	int sm, sd, em, ed;

	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> sm >> sd >> em >> ed;
		date.push_back({ sm * 100 + sd , em * 100 + ed });
	}

	int t = 301;
	int nxt_t;
	int cnt = 0;
	while (t < 1201)
	{
		nxt_t = t;
		// 301���� �����ؼ� t���� ���� �����ϰ� t���� �ʰ� ������ ��¥ ����
		// �� ������ �ð��� ���� ���� ��¥�� �ϳ��� �����ؾߵȴ�. -> ��� Ž��
		for (int i = 0; i < n; i++) {
			if (date[i].X <= t && date[i].Y > nxt_t) {
				nxt_t = date[i].Y;
			}
		}
		if (nxt_t == t)	// 1130�� �������� �ʾҴµ� �� ������ �� ������ 0 ��� �� ������
		{	// nxt_t ��, �� ���� ���� ��¥�� ������ ������ �������� �ʾ����� �ǹ��ϹǷ�
			cout << "0";
			return 0;
		}
		cnt++;
		t = nxt_t;
	}

	cout << cnt;

	return 0;
}