#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

#define MAX 300
#define X first
#define Y second

int k, m;
int board[5][5];
queue<int> newPiece;
int visit[5][5];
int sumWorth;	// °¢ ÅÏ¸¶´Ù È¹µæÇÑ À¯¹ÄÀÇ °¡Ä¡
int dx[4] = { 0, 0, -1, 1 };
int dy[4] = { -1, 1, 0, 0 };
int tamsaX, tamsaY, tamsaRot;
int visitZero[5][5];
int results;
int val;

void init() {
	memset(visit, 0, sizeof(visit));
	memset(visitZero, 0, sizeof(visitZero));
	sumWorth = 0;
	tamsaX = 0;
	tamsaY = 0;
	tamsaRot = 0;
	results = 0;
	val = 0;
}

void input() {
	int num;
	scanf("%d %d", &k, &m);
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			scanf("%d", &board[i][j]);
		}
	}

	for (int i = 0; i < m; i++) {
		scanf("%d", &num);
		newPiece.push(num);
	}

	//for (int i = 0; i < 5; i++) {
	//	for (int j = 0; j < 5; j++) {
	//		printf("%d ", board[i][j]);
	//	}
	//	printf("\n");
	//}
	//for (int i = 0; i < m; i++) {
	//	printf("%d ", newPiece[i]);
	//}
}

void rotate_90(int x, int y) {
	int tmp[3][3];	// unit
	int tmp2[3][3];

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			tmp[i][j] = board[x - 1 + i][y - 1 + j];
		}
	}

	memcpy(tmp2, tmp, sizeof(tmp));

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			tmp[i][j] = tmp2[3 - 1 - j][i];
		}
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			board[x - 1 + i][y - 1 + j] = tmp[i][j];
		}
	}
}
void rotate_180(int x, int y) {
	for (int i = 0; i < 2; i++) {
		rotate_90(x, y);
	}
}
void rotate_270(int x, int y) {
	int tmp[3][3];	// unit
	int tmp2[3][3];

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			tmp[i][j] = board[x - 1 + i][y - 1 + j];
		}
	}

	memcpy(tmp2, tmp, sizeof(tmp));

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			tmp[i][j] = tmp2[j][3 - 1 - i];
		}
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			board[x - 1 + i][y - 1 + j] = tmp[i][j];
		}
	}
}

int bfs(int x, int y) {
	int ret = 1;
	queue<pair<int, int>> Q;
	Q.push({ x, y });
	visit[x][y] = 1;
	while (!Q.empty()) {
		auto cur = Q.front();
		Q.pop();
		for (int i = 0; i < 4; i++) {
			int nx = cur.X + dx[i];
			int ny = cur.Y + dy[i];
			if (nx < 0 || nx >= 5 || ny < 0 || ny >= 5) continue;
			if (visit[nx][ny] != 0 || board[nx][ny] != board[cur.X][cur.Y]) continue;
			visit[nx][ny] = 1;
			Q.push({ nx,ny });
			ret++;
		}
	}
	return ret;
}
void unitFunc() {
	for (int a = 0; a < 5; a++) {
		for (int b = 0; b < 5; b++) {
			if (visit[a][b] == 1) continue;
			int num = bfs(a, b);
			if (num >= 3) {
				sumWorth += num;
			}
		}
	}
}
void unitFunc2(int com, int i, int j) {
	memset(visit, 0, sizeof(visit));
	sumWorth = 0;
	switch (com) {
	case 0:
		unitFunc();
		break;
	case 1:
		rotate_90(i, j);
		unitFunc();
		rotate_270(i, j);
		break;
	case 2:
		rotate_180(i, j);
		unitFunc();
		rotate_180(i, j);
		break;
	case 3:
		rotate_270(i, j);
		unitFunc();
		rotate_90(i, j);
		break;
	default:
		break;
	}
}
int tamsa() {
	results = 0;
	// (1,1) ~ (3,3) À» Áß½ÉÀ¸·Î
	for (int i = 1; i <= 3; i++) {
		for (int j = 1; j <= 3; j++) {
			for (int rot = 0; rot < 4; rot++) {
				unitFunc2(rot, i, j);
				if (sumWorth > results) {
					results = sumWorth;
					tamsaX = i;
					tamsaY = j;
					tamsaRot = rot;
				}
				else if (sumWorth == results) {
					if (rot < tamsaRot) {
						results = sumWorth;
						tamsaX = i;
						tamsaY = j;
						tamsaRot = rot;
					}
					else if (rot == tamsaRot) {
						if (j < tamsaY) {
							results = sumWorth;
							tamsaX = i;
							tamsaY = j;
							tamsaRot = rot;
						}
						else if (j == tamsaY) {
							if (i < tamsaX) {
								results = sumWorth;
								tamsaX = i;
								tamsaY = j;
								tamsaRot = rot;
							}
						}
					}
				}
			}
		}
	}

	return results;
}

void bfsZero(int x, int y) {
	int tmp[5][5];
	memcpy(tmp, board, sizeof(tmp));
	queue<pair<int, int>> Qz;
	Qz.push({ x, y });
	visitZero[x][y] = 1;
	board[x][y] = 0;
	while (!Qz.empty()) {
		auto cur = Qz.front();
		Qz.pop();
		for (int i = 0; i < 4; i++) {
			int nx = cur.X + dx[i];
			int ny = cur.Y + dy[i];
			if (nx < 0 || nx >= 5 || ny < 0 || ny >= 5) continue;
			if (visitZero[nx][ny] != 0 || tmp[nx][ny] != tmp[cur.X][cur.Y]) continue;
			Qz.push({ nx,ny });
			visitZero[nx][ny] = 1;
			board[nx][ny] = 0;
		}
	}
}
int unitresultsFunc() {
	int flag = 0;
	memset(visitZero, 0, sizeof(visitZero));
	memset(visit, 0, sizeof(visit));
	for (int a = 0; a < 5; a++) {
		for (int b = 0; b < 5; b++) {
			if (visit[a][b] == 1) continue;
			int num = bfs(a, b);
			if (num >= 3) {
				bfsZero(a, b);
				flag += num;
			}
		}
	}
	return flag;
}
void tamsaresults(int i, int j, int com) {
	switch (com) {
	case 0:
		unitresultsFunc();
		break;
	case 1:
		rotate_90(i, j);
		unitresultsFunc();
		break;
	case 2:
		rotate_180(i, j);
		unitresultsFunc();
		break;
	case 3:
		rotate_270(i, j);
		unitresultsFunc();
		break;
	default:
		break;
	}
}

void second() {
	int cnt = 2;
	while (1) {
		int flag = unitresultsFunc();

		//for (int i = 0; i < 5; i++) {
		//	for (int j = 0; j < 5; j++) {
		//		printf("%d ", board[i][j]);
		//	}
		//	printf("\n");
		//}
		//printf("\n");


		if (flag == 0) break;
		for (int i = 0; i < 5; i++) {
			for (int j = 4; j >= 0; j--) {
				if (board[j][i] == 0) {
					board[j][i] = newPiece.front();
					newPiece.pop();
				}
			}
		}

		//printf("À¯¹° %dÂ÷ È¹µæ\n", cnt);
		//for (int i = 0; i < 5; i++) {
		//	for (int j = 0; j < 5; j++) {
		//		printf("%d ", board[i][j]);
		//	}
		//	printf("\n");
		//}
		//printf("%d\n", flag);
		//printf("\n");

		val += flag;

		cnt++;
	}
}

int main() {
	input();
	while (k--) {
		init();

		// 1. Å½»ç ÁøÇà
		val = tamsa();
		if (val == 0) break;

		//printf("È¸Àü Áß½É, È¸Àü°¢%d %d %d\n", tamsaX, tamsaY, tamsaRot);
		tamsaresults(tamsaX, tamsaY, tamsaRot);

		//for (int i = 0; i < 5; i++) {
		//	for (int j = 0; j < 5; j++) {
		//		printf("%d ", board[i][j]);
		//	}
		//	printf("\n");
		//}
		//printf("\n");

		for (int i = 0; i < 5; i++) {
			for (int j = 4; j >= 0; j--) {
				if (board[j][i] == 0) {
					board[j][i] = newPiece.front();
					newPiece.pop();
				}
			}
		}

		//printf("À¯¹° 1Â÷ È¹µæ : %d\n", val);
		//for (int i = 0; i < 5; i++) {
		//	for (int j = 0; j < 5; j++) {
		//		printf("%d ", board[i][j]);
		//	}
		//	printf("\n");
		//}
		//printf("\n");

		second();
		printf("%d ", val);
	}

	return 0;
}

/*
for (int i = 0; i < 5; i++) {
	for (int j = 0; j < 5; j++) {
		printf("%d ", board[i][j]);
	}
	printf("\n");
}
*/