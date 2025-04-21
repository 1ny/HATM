#include <iostream>
#include <cstring>
#include <queue>
#include <vector>

using namespace std;

#define MAX 50
#define MAX_K 15
#define X first
#define Y second

int n, k;
char color[MAX][MAX];
int energy[MAX][MAX];
int visit[MAX][MAX];
int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };
int attackSel[MAX][MAX];
vector<pair<int, int>> vectRGB;
vector<pair<int, int>> vectCMY;
vector<pair<int, int>> vectW;
int attacked[MAX][MAX];

void init() {
	memset(visit, 0, sizeof(visit));
	memset(attackSel, 0, sizeof(attackSel));
	memset(attacked, 0, sizeof(attacked));
	vectRGB.clear();
	vectCMY.clear();
	vectW.clear();
}
void input() {
	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> color[i][j];
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> energy[i][j];
		}
	}

	cout << "초기 색상\n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%3c ", color[i][j]);
		}
		cout << endl;
	}
	cout << endl;
	cout << "초기 에너지\n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%3d ", energy[i][j]);
		}
		cout << endl;
	}
	cout << endl;
}

void bfs_attackSel(int x, int y) {
	queue<pair<int, int>> Q;
	Q.push({ x,y });
	visit[x][y] = 1;
	int maxEng = energy[x][y];
	int maxX = x, maxY = y;
	int cnt = 1;
	energy[x][y]--;
	while (!Q.empty()) {
		auto cur = Q.front();
		Q.pop();
		for (int dir = 0; dir < 4; dir++) {
			int nx = cur.X + dx[dir];
			int ny = cur.Y + dy[dir];
			if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
			if (visit[nx][ny] == 1 || color[nx][ny] != color[cur.X][cur.Y]) continue;
			Q.push({ nx, ny });
			visit[nx][ny] = 1;
			cnt++;
			energy[nx][ny]--;
			if (energy[nx][ny] > maxEng) {
				maxX = nx;
				maxY = ny;
				maxEng = energy[nx][ny];
			}
		}
	}

	energy[maxX][maxY] += cnt;
	attackSel[maxX][maxY] = energy[maxX][maxY];
}

void arrangeAttack() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if ((color[i][j] == 'R' || color[i][j] == 'G' || color[i][j] == 'B')
				&& attackSel[i][j] > 0)
			{
				vectRGB.push_back({ i, j });
			}
		}
	}
	if (!vectRGB.empty()) {
		for (int i = 0; i < vectRGB.size() - 1; i++) {
			for (int j = i + 1; j < vectRGB.size(); j++) {
				if (energy[vectRGB[i].X][vectRGB[i].Y] < energy[vectRGB[j].X][vectRGB[j].Y])
				{
					int tmpX = vectRGB[i].X;
					int tmpY = vectRGB[i].Y;
					vectRGB[i] = vectRGB[j];
					vectRGB[j] = { tmpX, tmpY };
				}
				else if (energy[vectRGB[i].X][vectRGB[i].Y] == energy[vectRGB[j].X][vectRGB[j].Y])
				{
					if (vectRGB[i].X > vectRGB[j].X)
					{
						int tmpX = vectRGB[i].X;
						int tmpY = vectRGB[i].Y;
						vectRGB[i] = vectRGB[j];
						vectRGB[j] = { tmpX, tmpY };
					}
					else if (vectRGB[i].X == vectRGB[j].X)
					{
						if (vectRGB[i].Y > vectRGB[j].Y)
						{
							int tmpX = vectRGB[i].X;
							int tmpY = vectRGB[i].Y;
							vectRGB[i] = vectRGB[j];
							vectRGB[j] = { tmpX, tmpY };
						}
					}
				}
			}
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if ((color[i][j] == 'C' || color[i][j] == 'M' || color[i][j] == 'Y')
				&& attackSel[i][j] > 0)
			{
				vectCMY.push_back({ i, j });
			}
		}
	}
	if (!vectCMY.empty()) {
		for (int i = 0; i < vectCMY.size() - 1; i++) {
			for (int j = i + 1; j < vectCMY.size(); j++) {
				if (energy[vectCMY[i].X][vectCMY[i].Y] < energy[vectCMY[j].X][vectCMY[j].Y])
				{
					int tmpX = vectCMY[i].X;
					int tmpY = vectCMY[i].Y;
					vectCMY[i] = vectCMY[j];
					vectCMY[j] = { tmpX, tmpY };
				}
				else if (energy[vectCMY[i].X][vectCMY[i].Y] == energy[vectCMY[j].X][vectCMY[j].Y])
				{
					if (vectCMY[i].X > vectCMY[j].X)
					{
						int tmpX = vectCMY[i].X;
						int tmpY = vectCMY[i].Y;
						vectCMY[i] = vectCMY[j];
						vectCMY[j] = { tmpX, tmpY };
					}
					else if (vectCMY[i].X == vectCMY[j].X)
					{
						if (vectCMY[i].Y > vectCMY[j].Y)
						{
							int tmpX = vectCMY[i].X;
							int tmpY = vectCMY[i].Y;
							vectCMY[i] = vectCMY[j];
							vectCMY[j] = { tmpX, tmpY };
						}
					}
				}
			}
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (color[i][j] == 'W' && attackSel[i][j] > 0)
			{
				vectW.push_back({ i, j });
			}
		}
	}
	if (!vectW.empty()) {
		for (int i = 0; i < vectW.size() - 1; i++) {
			for (int j = i + 1; j < vectW.size(); j++) {
				if (energy[vectW[i].X][vectW[i].Y] < energy[vectW[j].X][vectW[j].Y])
				{
					int tmpX = vectW[i].X;
					int tmpY = vectW[i].Y;
					vectW[i] = vectW[j];
					vectW[j] = { tmpX, tmpY };
				}
				else if (energy[vectW[i].X][vectW[i].Y] == energy[vectW[j].X][vectW[j].Y])
				{
					if (vectW[i].X > vectW[j].X)
					{
						int tmpX = vectW[i].X;
						int tmpY = vectW[i].Y;
						vectW[i] = vectW[j];
						vectW[j] = { tmpX, tmpY };
					}
					else if (vectW[i].X == vectW[j].X)
					{
						if (vectW[i].Y > vectW[j].Y)
						{
							int tmpX = vectW[i].X;
							int tmpY = vectW[i].Y;
							vectW[i] = vectW[j];
							vectW[j] = { tmpX, tmpY };
						}
					}
				}
			}
		}
	}
}
void attack(int x, int y) {
	if (attacked[x][y] == 1) return;
	int dir = energy[x][y] % 4;
	int power = energy[x][y] - 1;
	energy[x][y] = 1;
	attacked[x][y] = 1;
	for (int i = 1; i < n; i++) {
		int nx = x + i * dx[dir];
		int ny = y + i * dy[dir];
		if (nx < 0 || nx >= n || ny < 0 || ny >= n) break;
		if (color[x][y] == color[nx][ny]) continue;
		if (power == 0) break;
		if (power > energy[nx][ny])
		{
			power = power - (energy[nx][ny] + 1);
			color[nx][ny] = color[x][y];
			energy[nx][ny]++;
			attacked[nx][ny] = 1;
			cout << "공격균: (" << x << " " << y << " ," << "방어균: (" << nx << " " << ny << endl;
		}
		else 
		{
			cout << "공격균: (" << x << " " << y << " ," << "흡수균: (" << nx << " " << ny << endl;
			energy[nx][ny] += power; // 흡수
			if (color[x][y] == 'R')
			{
				if (color[nx][ny] == 'G') color[nx][ny] = 'Y';
				else if (color[nx][ny] == 'B') color[nx][ny] = 'M';
				else if (color[nx][ny] == 'C') color[nx][ny] = 'W';
			}
			else if (color[x][y] == 'G')
			{
				if (color[nx][ny] == 'R') color[nx][ny] = 'Y';
				else if (color[nx][ny] == 'B') color[nx][ny] = 'C';
				else if (color[nx][ny] == 'M') color[nx][ny] = 'W';
			}
			else if (color[x][y] == 'B')
			{
				if (color[nx][ny] == 'R') color[nx][ny] = 'M';
				else if (color[nx][ny] == 'G') color[nx][ny] = 'C';
				else if (color[nx][ny] == 'Y') color[nx][ny] = 'W';
			}
			else if (color[x][y] == 'Y')
			{
				if (color[nx][ny] == 'R') color[nx][ny] = 'Y';
				else if (color[nx][ny] == 'G') color[nx][ny] = 'Y';
				else if (color[nx][ny] == 'B') color[nx][ny] = 'W';
				else if (color[nx][ny] == 'C') color[nx][ny] = 'W';
				else if (color[nx][ny] == 'M') color[nx][ny] = 'W';
			}
			else if (color[x][y] == 'C')
			{
				if (color[nx][ny] == 'R') color[nx][ny] = 'W';
				else if (color[nx][ny] == 'G') color[nx][ny] = 'C';
				else if (color[nx][ny] == 'B') color[nx][ny] = 'C';
				else if (color[nx][ny] == 'Y') color[nx][ny] = 'W';
				else if (color[nx][ny] == 'M') color[nx][ny] = 'W';
			}
			else if (color[x][y] == 'M')
			{
				if (color[nx][ny] == 'R') color[nx][ny] = 'M';
				else if (color[nx][ny] == 'G') color[nx][ny] = 'W';
				else if (color[nx][ny] == 'B') color[nx][ny] = 'M';
				else if (color[nx][ny] == 'Y') color[nx][ny] = 'W';
				else if (color[nx][ny] == 'C') color[nx][ny] = 'W';
			}
			else if (color[x][y] == 'W')
			{
				color[nx][ny] = 'W';
			}
			break;
		}
	}
}

int main() {
	int T;
	cin >> T;

	for (int test = 1; test <= T; test++) {
		input();
		cout << "#" << test << " ";

		for (int turn = 1; turn <= k; turn++) {
			init();
			// 1. 에너지 생성
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					energy[i][j]++;
				}
			}
			cout << "에너지 생성 후\n";
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					printf("%3d ", energy[i][j]);
				}
				cout << endl;
			}
			cout << endl;

			// 2. 공격균 선정
			// 균집에서 가장 큰 에너지의 세균에게 나머지 균들이 에너지 1씩 건네준다.
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					if (visit[i][j] == 1) continue;
					bfs_attackSel(i, j);
				}
			}
			cout << "공격균 선정 후 에너지\n";
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					printf("%3d ", energy[i][j]);
				}
				cout << endl;
			}
			cout << endl;
			cout << "공격균 선정 후 공격균 위치 표시\n";
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					printf("%3d ", attackSel[i][j]);
				}
				cout << endl;
			}
			cout << endl;

			// 3-1. 공격 순서 정하기
			arrangeAttack();

			printf("공격 순서 RGB\n");
			for (int i = 0; i < vectRGB.size(); i++) {
				printf("(%d %d)\n", vectRGB[i].X, vectRGB[i].Y);
			}
			printf("공격 순서 CMY\n");
			for (int i = 0; i < vectCMY.size(); i++) {
				printf("(%d %d)\n", vectCMY[i].X, vectCMY[i].Y);
			}
			printf("공격 순서 W\n");
			for (int i = 0; i < vectW.size(); i++) {
				printf("(%d %d)\n", vectW[i].X, vectW[i].Y);
			}
			cout << endl;

			// 3-2. 공격!!
			for (int i = 0; i < vectRGB.size(); i++) {
				attack(vectRGB[i].X, vectRGB[i].Y);
			}
			for (int i = 0; i < vectCMY.size(); i++) {
				attack(vectCMY[i].X, vectCMY[i].Y);
			}
			for (int i = 0; i < vectW.size(); i++) {
				attack(vectW[i].X, vectW[i].Y);
			}

			cout << "공격 후 색상\n";
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					printf("%3c ", color[i][j]);
				}
				cout << endl;
			}
			cout << endl;
			cout << "공격 후 에너지\n";
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					printf("%3d ", energy[i][j]);
				}
				cout << endl;
			}
			cout << endl;

			// 색상별 에너지 세기
			int cntC = 0, cntM = 0, cntY = 0, cntR = 0, cntG = 0, cntB = 0, cntW = 0;
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					if (color[i][j] == 'C') cntC += energy[i][j];
					else if (color[i][j] == 'M') cntM += energy[i][j];
					else if (color[i][j] == 'Y') cntY += energy[i][j];
					else if (color[i][j] == 'R') cntR += energy[i][j];
					else if (color[i][j] == 'G') cntG += energy[i][j];
					else if (color[i][j] == 'B') cntB += energy[i][j];
					else if (color[i][j] == 'W') cntW += energy[i][j];
				}
			}

			cout << "T" << turn << " " << cntC << " " << cntM << " " << cntY << " " << cntR << " " << cntG << " " << cntB << " " << cntW << " ";
			cout << endl;
			cout << "-------------------------------------------------------------------------------\n";
		}
		cout << endl;
	}

	return 0;
}