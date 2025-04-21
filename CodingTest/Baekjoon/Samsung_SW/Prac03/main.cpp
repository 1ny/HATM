#include<iostream>
#include <vector>
#include <cstring>
#include <queue>

using namespace std;

#define MAX_W 12
#define MAX_H 15
#define X first
#define Y second

int n, w, h;  // w X h, n개의 구슬
int board[MAX_H][MAX_W];
int tmp[MAX_H][MAX_W];
int dx[4] = { 0, 0, -1, 1 };
int dy[4] = { -1, 1, 0, 0 };
vector<vector <int>> vect;
int minVal;

void init() {
	minVal = 12*15;
	vect.clear();
}
void input() {
	scanf("%d %d %d", &n, &w, &h);

	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			scanf("%d", &board[i][j]);
		}
	}
}

// 벽돌 부술 열 중복순열
void select(vector<int> b, int num) {
	if (num == n) {
		vect.push_back(b);
		return;
	}
	for (int j = 0; j < w; j++) {
		b[num] = j;
		select(b, num + 1);
	}
}

// 벽돌 깨뜨리기 -> 동서남북
void breakBrick(int x, int y) {
	queue < pair<int, int>> Q;
	Q.push({ x, y });
	while (!Q.empty()) {
		auto cur = Q.front();
		Q.pop();
		for (int i = 0; i < 4; i++) {
			for (int r = 1; r < tmp[cur.X][cur.Y]; r++) {
				int nx = cur.X + r*dx[i];
				int ny = cur.Y + r*dy[i];
				if (nx < 0 || nx >= h || ny < 0 || ny >= w) continue;
				if (tmp[nx][ny] == 0) continue;
				Q.push({ nx, ny });
			}
		}
		tmp[cur.X][cur.Y] = 0;
	}
}
// 벽돌 밑으로 떨어뜨리기
void fall() {
	for (int col = 0; col < w; col++) {
		for (int i = 0; i < h - 1; i++) {
			for (int j = 0; j < h - 1 - i; j++) {
				if (tmp[j][col] != 0 && tmp[j + 1][col] == 0) {
					tmp[j + 1][col] = tmp[j][col];
					tmp[j][col] = 0;
				}
			}
		}
	}
}
// 구슬 떨어뜨리기
int func(vector<int> c) {
	int cnt = 0;
	memcpy(tmp, board, sizeof(board));

	// c[i]번째 열에 구슬 떨어뜨림 - n번 반복
	for (int i = 0; i < n; i++) {
		for (int row = 0; row < h; row++) {
			if (tmp[row][c[i]] != 0) {
				// 동서남북으로 tmp-1 만큼씩 부수기
				breakBrick(row, c[i]);
				fall();
				break;
			}
		}
	}

	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			if (tmp[i][j] != 0) cnt++;
		}
	}

	return cnt;
}

int main() {
	int test_case;
	int T;
	scanf("%d", &T);
	//T = 1;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		init();
		input();

		vector<int> ref(n);
		select(ref, 0);
		//for (int i = 0; i < vect.size(); i++) {
		//	for (int j = 0; j < n; j++) {
		//		printf("%d ", vect[i][j]);
		//	}
		//	printf("\n");
		//}

		for (int i = 0; i < vect.size(); i++) {
			int ret = func(vect[i]);
			if (ret < minVal) {
				minVal = ret;
				if (minVal == 0) break;
			}
		}

		//for (int i = 0; i < h; i++) {
		//	for (int j = 0; j < w; j++) {
		//		printf("%d ", tmp[i][j]);
		//	}
		//	printf("\n");
		//}
		printf("#%d %d\n", test_case, minVal);
	}

	return 0;
}