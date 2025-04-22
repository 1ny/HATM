#include <iostream>
#include <queue>
#include <stdlib.h>

using namespace std;

#define MAX 50
#define MAX_M 300
#define X first
#define Y second

int n, m;
int sr, sc, er, ec;
int board[MAX][MAX];
int junsaBoard[MAX][MAX];
int dist[MAX][MAX];
int junsa[MAX_M][2];
int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };
int dx2[4] = { 0, 0, -1, 1 };
int dy2[4] = { -1, 1, 0, 0 };
int tmpJunsaBoard[MAX][MAX];
int vision[4][MAX][MAX];
int rotateDir[4] = { 0, 2, 1, 3 };
int maxVision;	// 메두사의 시선 방향 (0~3: 상하좌우)
int maxJunsa;	// 돌이 된 전사 수
int attackNum;
int moveNum;

void init() {
	memset(board, 0, sizeof(board));
	memset(dist, -1, sizeof(dist));
}
void input() {
	cin >> n >> m;
	cin >> sr >> sc >> er >> ec;
	for (int i = 0; i < m; i++) {
		cin >> junsa[i][0] >> junsa[i][1];
		junsaBoard[junsa[i][0]][junsa[i][1]] = 1;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> board[i][j];
		}
	}
	//cout << n << " " << m << endl;
	//cout << sr << " " << sc << " " << er << " " << ec << " " << endl;
	//for (int i = 0; i < m; i++) {
	//	cout << junsa[i][0] << " " << junsa[i][1] << " ";
	//}
	//cout << endl;
	//for (int i = 0; i < n; i++) {
	//	for (int j = 0; j < n; j++) {
	//		cout << board[i][j] << " ";
	//	}
	//	cout << endl;
	//}
}

void rotate() { // 시계방향으로 돌리기
	int tmp[MAX][MAX];
	memcpy(tmp, tmpJunsaBoard, sizeof(tmpJunsaBoard));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			tmpJunsaBoard[i][j] = tmp[n-1-j][i];
		}
	}
}
void rotate_l() { // 반시계방향으로 돌리기 -> 원래대로
	int tmp[MAX][MAX];
	memcpy(tmp, tmpJunsaBoard, sizeof(tmpJunsaBoard));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			tmpJunsaBoard[i][j] = tmp[j][n-1-i];
		}
	}
}
void rotate_vision(int dir) { // 시계방향으로 돌리기
	int tmp[MAX][MAX];
	memcpy(tmp, vision[dir], sizeof(vision[dir]));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			vision[dir][i][j] = tmp[n - 1 - j][i];
		}
	}
}
void rotate_vision_l(int dir) { // 반시계방향으로 돌리기 -> 원래대로
	int tmp[MAX][MAX];
	memcpy(tmp, vision[dir], sizeof(vision[dir]));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			vision[dir][i][j] = tmp[j][n - 1 - i];
		}
	}
}
void rotate_s(int* x, int* y) { // 시계방향으로 돌리기
	int tmpX = *x;
	int tmpY = *y;
	*x = tmpY;
	*y = n - 1 - tmpX;
}
void rotate_s_l(int* x, int* y) { // 반시계방향으로 돌리기 -> 원래대로
	int tmpX = *x;
	int tmpY = *y;
	*x = n - 1- tmpY;
	*y = tmpX;
}

void bfs() {
	queue<pair<int, int>> Q;
	Q.push({ er,ec });
	dist[er][ec] = 0;
	while (!Q.empty()) {
		auto cur = Q.front();
		Q.pop();
		for (int i = 0; i < 4; i++) {
			int nx = cur.X + dx[i];
			int ny = cur.Y + dy[i];
			if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
			if (dist[nx][ny] != -1 || board[nx][ny] != 0) continue;
			Q.push({ nx, ny });
			dist[nx][ny] = dist[cur.X][cur.Y] + 1;
		}
	}
}
void medusaMove() {
	// 메두사 한칸 이동
	int tmpX = sr, tmpY = sc;
	int minDist = dist[sr][sc];
	for (int i = 0; i < 4; i++) {
		int nx = sr + dx[i];
		int ny = sc + dy[i];
		if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
		if (dist[nx][ny] == -1) continue;
		if (dist[nx][ny] < minDist) {
			tmpX = nx, tmpY = ny;
			minDist = dist[nx][ny];
		}
	}
	sr = tmpX;
	sc = tmpY;
	for (int i = 0; i < m; i++) {
		if (sr == junsa[i][0] && sc == junsa[i][1]) {
			junsaBoard[junsa[i][0]][junsa[i][1]]--;
			junsa[i][0] = -1;
			junsa[i][1] = -1;
		}
	}
	//printf("(sr, sc) : %d %d", sr, sc);
}
int medusaVision() {
	// 메두사 시선 처리
	memset(vision, 0, sizeof(vision));
	maxJunsa = 0;	// 돌로 만든 전사 수 최대
	int maxDir = 0;
	for (int dir = 0; dir < 4; dir++) {
		memcpy(tmpJunsaBoard, junsaBoard, sizeof(junsaBoard));
		int junsaNum = 0;
		int nx, ny;
		int nsr = sr;
		int nsc = sc;

		for (int i = 0; i < rotateDir[dir]; i++) {
			rotate();
			rotate_s(&nsr, &nsc);
		}
		// 중앙
		for (int i = 1; i < n; i++) {
			nx = nsr - i;
			ny = nsc;
			if (nx < 0 || nx >= n || ny < 0 || ny >= n) break;
			vision[dir][nx][ny] = 1;
			if (tmpJunsaBoard[nx][ny] > 0) {
				junsaNum += tmpJunsaBoard[nx][ny];
				break;
			}
		}

		// 메두사를 기준으로 왼쪽
		for (int i = 1; i < n; i++) {
			for (int j = 1; j < n; j++) {
				nx = nsr - j - i + 1;
				ny = nsc - i;
				if (nx < 0 || nx >= n || ny < 0 || ny >= n) break;
				if (vision[dir][nx][ny] == -1) break;
				vision[dir][nx][ny] = 1;
				if (tmpJunsaBoard[nx][ny] > 0) {
					junsaNum += tmpJunsaBoard[nx][ny];
					for (int x = 1; x < n; x++) {
						if ((nx - x) < 0 || (nx - x) >= n || (ny - x) < 0 || (ny - x) >= n) break;
						vision[dir][nx - x][ny - x] = -1;
					}
					break;
				}
			}
		}

		// 메두사를 기준으로 오른쪽
		for (int i = 1; i < n; i++) {
			for (int j = 1; j < n; j++) {
				nx = nsr - j - i + 1;
				ny = nsc + i;
				if (nx < 0 || nx >= n || ny < 0 || ny >= n) break;
				if (vision[dir][nx][ny] == -1) break;
				vision[dir][nx][ny] = 1;
				if (tmpJunsaBoard[nx][ny] > 0) {
					junsaNum += tmpJunsaBoard[nx][ny];
					for (int x = 1; x < n; x++) {
						if ((nx - x) < 0 || (nx - x) >= n || (ny + x) < 0 || (ny + x) >= n) break;
						vision[dir][nx - x][ny + x] = -1;
					}
					break;
				}
			}
		}

		for (int i = 0; i < rotateDir[dir]; i++) {
			rotate_l();
			rotate_s_l(&nsr, &nsc);
			rotate_vision_l(dir);
		}
		
		if (junsaNum > maxJunsa) {
			maxJunsa = junsaNum;
			maxDir = dir;
		}
	}
	return maxDir;
}
void junsaMove() {
	for (int i = 0; i < m; i++) {
		int minDist;
		int minX = -1, minY = -1;
		int curX = junsa[i][0];
		int curY = junsa[i][1];
		minDist = abs(sr - curX) + abs(sc - curY);
		if (vision[maxVision][curX][curY] == 1) continue;
		if (curX == -1) continue;
		// 맨해튼 거리에 따라 이동
		// 첫번째, 상하좌우 우선순위로
		for (int dir = 0; dir < 4; dir++) {
			int nx = curX + dx[dir];
			int ny = curY + dy[dir];
			if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
			if (vision[maxVision][nx][ny] == 1) continue;
			int junsaToMedu = abs(sr - nx) + abs(sc - ny);

			if (junsaToMedu < minDist) {
				minDist = junsaToMedu;
				minX = nx;
				minY = ny;
			}
		}

		// 두번째, 좌우상하 우선순위로
		if (minX == -1) continue;
		moveNum++;
		if (minX == sr && minY == sc) {	// 메두사를 만나면 사라짐
			junsaBoard[junsa[i][0]][junsa[i][1]]--;
			attackNum++;
			junsa[i][0] = -1;
			junsa[i][1] = -1;
			continue;
		}
		cout << "첫번째 바꾼 전사 좌표 : " << junsa[i][0] << " " << junsa[i][1] << " -> " << minX << " " << minY << "\n";
		// 사라지지 않았다면 더해주기
		junsaBoard[junsa[i][0]][junsa[i][1]]--;
		junsa[i][0] = minX;
		junsa[i][1] = minY;
		junsaBoard[junsa[i][0]][junsa[i][1]]++;
		//cout << "더할 전사 위치: " << junsa[i][0] << " " << junsa[i][1] << "\n";
		curX = junsa[i][0];
		curY = junsa[i][1];
		minDist = abs(sr - minX) + abs(sc - minY);
		minX = -1, minY = -1;
		for (int dir = 0; dir < 4; dir++) {
			int nx2 = curX + dx2[dir];
			int ny2 = curY + dy2[dir];
			if (nx2 < 0 || nx2 >= n || ny2 < 0 || ny2 >= n) continue;
			if (vision[maxVision][nx2][ny2] == 1) continue;
			int junsaToMedu2 = abs(sr - nx2) + abs(sc - ny2);
			if (junsaToMedu2 < minDist) {
				minDist = junsaToMedu2;
				minX = nx2;
				minY = ny2;
			}
		}

		// 그대로면 그대로
		if (minX == -1) continue;
		moveNum++;
		junsaBoard[junsa[i][0]][junsa[i][1]]--;
		if (minX == sr && minY == sc) {
			attackNum++;
			junsa[i][0] = -1;
			junsa[i][1] = -1;
			continue;
		}
		junsa[i][0] = minX;
		junsa[i][1] = minY;
		junsaBoard[junsa[i][0]][junsa[i][1]]++;
	}
}

int main() {
	init();
	input();

	// 공원 -> 메두사 거리 계산 (dist 배열 생성)
	bfs();
	if (dist[sr][sc] == -1) {
		cout << "-1";
		return 0;
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%3d ", dist[i][j]);
		}
		cout << "\n";
	}
	cout << "\n";

	int test = 5;
	while (1) {
		attackNum = 0;
		moveNum = 0;

		// 메두사 한칸 이동
		medusaMove();
		if (sr == er && sc == ec) {
			cout << "0";
			break;
		}

		cout << "메두사 위치" << sr << " " << sc << "\n";
		cout << "전사 이동 전" << "\n";
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				printf("%3d ", junsaBoard[i][j]);
			}
			cout << "\n";
		}
		cout << "\n";

		// 메두사의 시선 처리
		maxVision = medusaVision();
		// 전사들의 이동
		junsaMove();

		cout << "vision" << "\n";
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				printf("%3d ", vision[maxVision][i][j]);
			}
			cout << "\n";
		}
		cout << "\n";

		cout << "전사 이동 후" << "\n";
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				printf("%3d ", junsaBoard[i][j]);
			}
			cout << "\n";
		}
		cout << "\n";

		printf("moveNum : %d\n", moveNum);
		printf("maxJunsa : %d\n", maxJunsa);
		printf("attackNum : %d\n", attackNum);
		cout << "\n";
	}
	/*
	1. 메두사 이동
		- 공원까지 최단경로 -> bfs
		- 전사를 만날 경우, 그 전사는 그냥 사라짐
		- 우선순위 : 상하좌우

	2. 메두사의 시선
		- 90도 시야각 -> 사진참고...
		- 사각지대 생길 수 있음 -> 사진참고...
		- 돌로 만든 전사들은 해당 턴에 움직일 수 없음.
		- 가장 많이 바라보는 방향으로!
		- 우선순위 : 상하좌우
	
	3. 전사들의 이동
		- 총 두 번 이동, 시야로는 이동 불가능
		- 메두사와의 거리는 맨해튼 거리를 기준으로 한다. -> 가로 세로 길이의 합
		- 첫번째 이동
			- 메두사와 거리를 줄일 수 있는 방향으로
			- 우선순위 : 상하좌우
		- 두번째 이동
			- 동일하게, but 우선순위 : 좌우상하
	
	4. 전사의 공격
		- 메두사와 만나면 메두사를 공격하고 사라진다.
	*/

	return 0;
}