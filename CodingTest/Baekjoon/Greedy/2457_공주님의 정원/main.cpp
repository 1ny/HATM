#include <iostream>
#include <vector>
using namespace std;

#define X first
#define Y second

int main() {
	int n;
	vector<pair<int, int>> date;	// 벡터 선언과 동시에 크기가 0인 벡터가 생긴거임 vector에 추가할 때 []로 접근하면 안되고 push_back으로 해야함
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
		// 301부터 시작해서 t보다 빨리 시작하고 t보다 늦게 끝나는 날짜 선택
		// 단 끝나는 시간이 가장 늦은 날짜로 하나만 선택해야된다. -> 모두 탐색
		for (int i = 0; i < n; i++) {
			if (date[i].X <= t && date[i].Y > nxt_t) {
				nxt_t = date[i].Y;
			}
		}
		if (nxt_t == t)	// 1130에 도달하지 않았는데 더 전진할 수 없으면 0 출력 후 끝내기
		{	// nxt_t 값, 즉 꽃이 지는 날짜가 변하지 않으면 전진하지 않았음을 의미하므로
			cout << "0";
			return 0;
		}
		cnt++;
		t = nxt_t;
	}

	cout << cnt;

	return 0;
}