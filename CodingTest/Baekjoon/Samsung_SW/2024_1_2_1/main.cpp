#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

#define MAX 75
#define MAX_K 1000
#define X first
#define Y second

int r, c, k;	// 숲의 크기, 정령의 수 k
int ci[MAX_K], di[MAX_K];
int board[MAX][MAX];
int exitLoc[MAX][MAX];
int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0, -1 };
int cnt = 1;
int visit[MAX][MAX];

void input() {
	scanf("%d %d %d", &r, &c, &k);
	for (int i = 0; i < k; i++) {
		scanf("%d %d", &ci[i], &di[i]);
	}
}

void rotate_90(int* d) {
	if (*d == 3) *d = 0;
	else *d = *d + 1;
}
void rotate_270(int* d) {
	if (*d == 0) *d = 3;
	else *d = *d - 1;
}

// 골렘 남쪽 탐색
int nam_check(int x, int y) {	// 골렌의 중앙 위치
	if (x == r + 1) return -1;
	if (board[x + 1][y - 1] == 0 && board[x + 2][y] == 0 && board[x + 1][y + 1] == 0) {
		return 1;
	}
	return 0;
}
int seo_check(int x, int y) {	// 골렌의 중앙 위치
	if (y == 1) return 0;
	if (board[x - 1][y - 1] == 0 && board[x][y - 2] == 0 && board[x + 1][y - 1] == 0
		&& board[x + 1][y - 2] == 0 && board[x + 2][y - 1] == 0) {
		return 1;
	}
	return 0;
}
int dong_check(int x, int y) {	// 골렌의 중앙 위치
	if (y == c - 2) return 0;
	if (board[x - 1][y + 1] == 0 && board[x][y + 2] == 0 && board[x + 1][y + 1] == 0
		&& board[x + 1][y + 2] == 0 && board[x + 2][y + 1] == 0) {
		return 1;
	}
	return 0;
}

int bfs(int x, int y) {
	int ret = x;
	queue<pair<int, int>> Q;
	Q.push({ x, y });
	visit[x][y] = 1;
	while (!Q.empty()) {
		auto cur = Q.front();
		Q.pop();
		for (int i = 0; i < 4; i++) {
			int nx = cur.X + dx[i];
			int ny = cur.Y + dy[i];
			if (nx < 3 || nx >= r + 3 || ny < 0 || ny >= c) continue;
			if (visit[nx][ny] == 1 || board[nx][ny] == 0) continue;
			if (exitLoc[cur.X][cur.Y] == 0 && board[nx][ny] != board[cur.X][cur.Y]) continue;
			visit[nx][ny] = 1;
			Q.push({ nx, ny });
			printf("PUSH: (%d, %d)\n", nx, ny);
			if (nx > ret) ret = nx;
		}
	}
	return ret - 2;
}

int tamsa(int x, int y, int d) {
	int nx = x;
	int ny = y;
	int nd = d;
	int flag = 0;
	while (1) {
		if (nx == r + 1) break;
		if (nam_check(nx, ny)) {
			// 남쪽으로 한칸 내려가기
			if (nam_check(nx, ny) == -1) break;
			nx++;
			flag = 0;
			continue;
		}
		else if (seo_check(nx, ny)) {
			//if (nx <= 1) return -1;
			// 서쪽으로 한칸 이동
			ny--;
			// 왼쪽으로 90도 회전
			rotate_270(&nd);
			if (flag == 3) break;
			if (flag == 0 || flag == 1 || flag == 2) flag++;
			continue;
		}
		else if (dong_check(nx, ny)) {
			//if (nx <= 1) return -1;
			ny++;
			rotate_90(&nd);
			if (flag == 3) break;
			if (flag == 1 || flag == 0 || flag == 2) flag++;
			continue;
		}
		break;
	}
	printf("최종 [%d]: (%d %d, %d)\n", cnt, nx, ny, nd);
	// 최종 위치가 board 밖이면 

	exitLoc[nx + dx[nd]][ny + dy[nd]] = cnt; // 출구 위치를 cnt로 표시
	// board에 cnt 표시
	board[nx][ny] = cnt;
	for (int i = 0; i < 4; i++) {
		int nextX = nx + dx[i];
		int nextY = ny + dy[i];
		board[nextX][nextY] = cnt;
	}
	cnt++;

	if (nx <= 3) return -1;

	int ret = bfs(nx, ny);

	printf("가장 맨 아래 행: %d\n\n", ret);

	return ret;
}

int main() {
	input();
	int sum = 0;

	for (int i = 0; i < k; i++) {
		memset(visit, 0, sizeof(visit));
		int ret = tamsa(1, ci[i] - 1, di[i]);
		if (ret == -1) {
			for (int i = 0; i < r + 3; i++) {
				for (int j = 0; j < c; j++) {
					printf("%3d ", board[i][j]);
				}
				printf("\n");
			}
			printf("\n");

			printf("exitLoc : \n");
			for (int i = 0; i < r + 3; i++) {
				for (int j = 0; j < c; j++) {
					printf("%3d ", exitLoc[i][j]);
				}
				printf("\n");
			}
			printf("\n");
			memset(exitLoc, 0, sizeof(exitLoc));
			memset(board, 0, sizeof(board));
		}
		else {
			sum += ret;
		}
	}

	for (int i = 0; i < r + 3; i++) {
		for (int j = 0; j < c; j++) {
			printf("%3d ", board[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	printf("exitLoc : \n");
	for (int i = 0; i < r + 3; i++) {
		for (int j = 0; j < c; j++) {
			printf("%3d ", exitLoc[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	printf("%d", sum);

	return 0;
}