#include<iostream>
#include <vector>
#include <cstring>
#include <queue>

using namespace std;

#define MAX 12

int n, w, h;  // w X h, n°³ÀÇ ±¸½½
int board[MAX][MAX];
int tmp[MAX][MAX];
int dx[4] = { 0, 0, -1, 1 };
int dy[4] = { -1, 1, 0, 0 };
vector<vector <int>> vect;

void init() {
	memset(board, 0, sizeof(board));
	memset(tmp, 0, sizeof(tmp));
}
void input() {
	scanf("%d %d %d", &n, &w, &h);

	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			scanf("%d", &board[i][j]);
		}
	}
}

// º®µ¹ ºÎ¼ú ¿­ ¼ø¿­
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

// º®µ¹ ±ú¶ß¸®±â
void broken(int x) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < x; j++) {

		}
	}
}

// ±¸½½ ¶³¾î¶ß¸®±â
void func(int col) {
	// col¹øÂ° ¿­¿¡ ±¸½½ ¶³¾î¶ß¸²
	int curX = 0;
	int curY = col;
	while (1) {
		if (board[curX][curY] > 0) {
			// º®µ¹ ±ú¶ß¸®±â

		}
	}
}

int main() {
	int test_case;
	int T;
	scanf("%d", &T);
	T = 1;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		init();
		input();
		vector<int> ref(n);

		select(ref, 0);

		for (int i = 0; i < vect.size(); i++) {
			for (int j = 0; j < n; j++) {
				printf("%d ", vect[i][j]);
			}
			printf("\n");
		}
	}

	return 0;
}