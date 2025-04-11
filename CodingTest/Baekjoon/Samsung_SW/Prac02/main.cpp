#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

#define MAX 20
#define MAX_F 10

#define X first
#define Y second

int n, m, f; // 시간 이상 현상 개수 f
int board[MAX][MAX];	// 바닥 보드
int dist_err[MAX][MAX];	// 시간 이상 현상 확산 상태 (v에 따름)
int dist[MAX][MAX];
int dist_wall[5][MAX][MAX];
int wall_board[5][MAX][MAX]; // 동서남북위
int dx[4] = { 0, 0, 1, -1 };
int dy[4] = { 1, -1, 0, 0 };
int ri[MAX_F], ci[MAX_F], di[MAX_F], vi[MAX_F]; // 확산 상수 vi
int mX, mY;	// 첫 시작 위치 (시간의 벽 위)
int wX, wY;	// 시간의 벽의 왼쪽 맨위 시작 좌표
int bX = -1, bY, bD;	// 시간의 벽에서 미지의 공간으로 빠져나갈 수 있는 출구의 좌표
int wall[MAX * 3][MAX * 3];

void bfs_err(int x, int y, int d, int v) {
	queue<pair <int, int>> Q;
	Q.push({x, y});
	dist_err[x][y] = 0;
	while (!Q.empty()) {
		auto cur = Q.front();
		Q.pop();
		int nx = cur.X + dx[d];
		int ny = cur.Y + dy[d];
		if (nx < 0 || nx >= n || ny < 0 || ny >= n || board[nx][ny] != 0) return;
		if (dist_err[nx][ny] < dist_err[cur.X][cur.Y] + v && dist_err[nx][ny] != -1) continue;	// 이전에 먼저 확산되어 있었으면 continue;
		dist_err[nx][ny] = dist_err[cur.X][cur.Y] + v;
		Q.push({ nx, ny });
	}
}

void bfs_up() {
	queue<tuple <int, int, int>> Q;
	Q.push({ mX, mY, 4 });
	dist_wall[4][mX][mY] = 0;
	while (!Q.empty()) {
		auto [x, y, w] = Q.front();
		Q.pop();
		if (x == bX && y == bY && w == bD) return;
		
		if (x == 0 && y == 0)
		{
			dist_wall[3][0][m - 1] = dist_wall[4][0][0] + 1;
			dist_wall[1][0][0] = dist_wall[4][0][0] + 1;
		}
		else if (x == 0 && y == m - 1)
		{
			dist_wall[3][0][0] = dist_wall[4][0][m-1] + 1;
			dist_wall[0][0][m - 1] = dist_wall[4][0][m-1] + 1;
		}
		else if (x == m - 1 && y == 0)
		{
			dist_wall[1][0][m-1] = dist_wall[4][m-1][0] + 1;
			dist_wall[2][0][0] = dist_wall[4][m-1][0] + 1;
		}
		else if (x == m - 1 && y == m - 1)
		{
			dist_wall[0][0][0] = dist_wall[4][m-1][m-1] + 1;
			dist_wall[2][0][m-1] = dist_wall[4][m-1][m-1] + 1;
		}
		else if (x == 0 || y == 0)
		{
			dist_wall[0][0][0] = dist_wall[4][m - 1][m - 1] + 1;
			dist_wall[0][0][0] = dist_wall[4][m - 1][m - 1] + 1;
		}

		/*
		1. 윗면 
			if(모서리면) 두 인접한 면에 체크
			else if(가장자리면) 인접한 한 면에 체크
			else 상하좌우 모두 체크
		2. 동쪽 면
			if(모서리면) 두 인접한 면에 체크, 단 아래로는 안봄
			else if(가장자리면) 인접한 한 면에 체크
			else 상하좌우 모두 체크
		3. 서쪽 면
			//
		*/

		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			int nd = 0;
			if (nx < 0 || nx >= m || ny < 0 || ny >= m) continue;
			if (dist_wall[4][nx][ny] < dist_wall[4][x][y] + 1 && dist_wall[4][nx][ny] != -1) continue;
			if (wall_board[4][nx][ny] == 1) continue;
			dist_wall[4][nx][ny] = dist_wall[4][x][y] + 1;
			Q.push({ nx, ny, nd });
		}
	}
}

int main() {
	memset(dist_err, -1, sizeof(dist_err));
	memset(dist_wall, -1, sizeof(dist_wall));
	memset(wall, -1, sizeof(wall));

	scanf("%d %d %d", &n, &m, &f);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d", &board[i][j]);
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (board[i][j] == 0) {
				for (int p = 0; p < 4; p++) {
					int nx = i + dx[p];
					int ny = j + dy[p];
					if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
					if (board[nx][ny] == 3) {
						bX = nx;
						bY = ny;
						bD = p;
						break;
					}
				}
			}
			if (bX != -1) break;
		}
		if (bX != -1) break;
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (board[i][j] == 3) {
				wX = i;
				wY = j;
				//printf("ttt: %d %d\n", i, j);
				break;
			}
		}
		if (wX != 0) break;
	}
	//printf("time machine : %d %d %d\n", bX, bY, bD);

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < m; j++) {
			for (int k = 0; k < m; k++) {
				scanf("%d", &wall_board[i][j][k]);
				if (wall_board[i][j][k] == 2) {
					mX = j;
					mY = k;
				}
			}
		}
	}
	printf("time machine : %d %d\n", mX, mY);

	// 시간 이상 현상의 초기 위치, 확산 방향, 확산상수
	for (int i = 0; i < f; i++) {
		scanf("%d %d %d %d", &ri[i], &ci[i], &di[i], &vi[i]);
	}

	for (int i = 0; i < f; i++) {
		bfs_err(ri[i], ci[i], di[i], vi[i]);
	}

	//bfs_up();

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			wall[i + m][j + m] = wall_board[4][i][j];
		}
	}
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			wall[i][j + m] = wall_board[3][i][j];
		}
	}
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			wall[i + (m*2)][j + m] = wall_board[2][i][j];
		}
	}
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			wall[i + m][j] = wall_board[1][i][j];
		}
	}
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			wall[i + m][j + (m*2)] = wall_board[0][j][m-1-i];
		}
	}
	for (int i = 0; i < m*3; i++) {
		for (int j = 0; j < m*3; j++) {
			printf("%3d ", wall[i][j]);
		}
		printf("\n");
	}

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			printf("%3d ", dist_wall[4][i][j]);
		}
		printf("\n");
	}
	printf("\n");

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			printf("%3d ", dist_wall[0][i][j]);
		}
		printf("\n");
	}

	/*
	빈공간 : 0, 장애물 : 1
	- 첫 타임머신 위치는 항상 시간의 벽 윗면 단면도에.


	1. 타임머신 이동 한칸씩 - timemachine
	2. 시간 이상 현상 확산 - bfs_isang
	*/

	return 0;
}

#if 0
for (int i = 0; i < n; i++) {
	for (int j = 0; j < n; j++) {
		printf("%3d ", dist_err[i][j]);
	}
	printf("\n");
}
#endif