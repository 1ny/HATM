#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

#define MAX 20
#define X first
#define Y second

int n, m, f;	// 미지의 공간 길이 n, 시간의 벽 길이 m, 시간 이상 현상의 개수 f
int dx[4] = { 0, 0, 1, -1 };
int dy[4] = { 1, -1, 0, 0 };
int bottom[MAX][MAX];
int timeWall[5][MAX][MAX];	// 동서남북위
int ri[10], ci[10], di[10], vi[10];	// 각 시간 이상 현상 초기 위치, 확산 방향, 확산 상수
int nextWall[MAX * 3][MAX * 3];
int dist_isang[MAX][MAX];
int dist_next[MAX*3][MAX*3];
int startX, startY; // nextWall 상의 타임머신 시작위치
int startWX = -1, startWY; // bottom 상의 시간의 벽 시작위치
int linkBX, linkBY, linkWX, linkWY, linkWD;
int dist[MAX][MAX];
int val;

void input() {
    scanf("%d %d %d", &n, &m, &f);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &bottom[i][j]);
        }
    }

    for (int p = 0; p < 5; p++) {
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < m; j++) {
                scanf("%d", &timeWall[p][i][j]);
            }
        }
    }

    for (int i = 0; i < f; i++) {
        scanf("%d %d %d %d", &ri[i], &ci[i], &di[i], &vi[i]);
    }

#if 0
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", bottom[i][j]);
        }
        printf("\n");
    }

    for (int p = 0; p < 5; p++) {
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < m; j++) {
                printf("%d ", timeWall[p][i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }

    for (int i = 0; i < f; i++) {
        printf("%d %d %d %d\n", ri[i], ci[i], di[i], vi[i]);
    }
#endif
}
void bfs(int x, int y, int d, int v) {
    queue<pair<int, int>> Q;
    Q.push({ x, y });
    dist_isang[x][y] = 0;
    while (!Q.empty()) {
        auto cur = Q.front();
        Q.pop();
        int nx = cur.X + dx[d];
        int ny = cur.Y + dy[d];
        if (bottom[nx][ny] == 4) continue;
        if (nx < 0 || nx >= n || ny < 0 || ny >= n || bottom[nx][ny] == 1) return;
        if (dist_isang[nx][ny] != -1 && dist_isang[nx][ny] < dist_isang[cur.X][cur.Y] + v) continue;
        dist_isang[nx][ny] = dist_isang[cur.X][cur.Y] + v;
        Q.push({ nx, ny });
    }
}

int bfs_next() {
    queue<pair<int, int>> Q;
    Q.push({ startX, startY });
    dist_next[startX][startY] = 0;
    while (!Q.empty()) {
        auto cur = Q.front();
        Q.pop();
        if (cur.X == linkWX && cur.Y == linkWY) return dist_next[cur.X][cur.Y];
        for (int i = 0; i < 4; i++) {
            int nx = cur.X + dx[i];
            int ny = cur.Y + dy[i];
            if (nx < 0 || nx >= m * 3 || ny < 0 || ny >= m * 3) continue;
            if (nextWall[nx][ny] == -1) {
                int tx, ty;
                if ((cur.X < m * 3 / 2 && cur.Y < m * 3 / 2) || (cur.X > m * 3 / 2 && cur.Y > m * 3 / 2))
                {
                    tx = cur.Y;
                    ty = cur.X;
                }
                else
                {
                    tx = m * 3 - cur.Y - 1;
                    ty = m * 3 - cur.X - 1;
                }
                if (nextWall[tx][ty] == 1 || dist_next[tx][ty] >= 0) continue;
                    dist_next[tx][ty] = dist_next[cur.X][cur.Y] + 1;
                    Q.push({ tx, ty });
                    printf("test: (%d %d) %d -> (%d %d) %d\n", cur.X, cur.Y, dist_next[cur.X][cur.Y], tx, ty, dist_next[tx][ty]);
            }
            else 
            {
                if (nextWall[nx][ny] == 1 || dist_next[nx][ny] >= 0) continue;
                    dist_next[nx][ny] = dist_next[cur.X][cur.Y] + 1;
                    Q.push({ nx, ny });
                    printf("test: (%d %d) %d -> (%d %d) %d\n", cur.X, cur.Y, dist_next[cur.X][cur.Y], nx, ny, dist_next[nx][ny]);
            }
        }
    }
    return -1;
}

int bfs_bottom() {
    queue<pair<int, int>> Q;
    Q.push({linkBX, linkBY});
    printf("X,Y : %d %d\n", linkBX, linkBY);
    dist[linkBX][linkBY] = val + 1;
    while (!Q.empty()) {
        auto cur = Q.front();
        Q.pop();
        if (bottom[cur.X][cur.Y] == 4) return dist[cur.X][cur.Y];
        for (int i = 0; i < 4; i++) {
            int nx = cur.X + dx[i];
            int ny = cur.Y + dy[i];
            if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
            if (bottom[nx][ny] == 1 || bottom[nx][ny] == 3) continue;
            if( (dist_isang[nx][ny] != -1) && (dist[cur.X][cur.Y] + 1 >= dist_isang[nx][ny])) continue;
            if (dist[nx][ny] >= 0) continue;
            dist[nx][ny] = dist[cur.X][cur.Y] + 1;
            Q.push({ nx,ny });
        }
    }
    return -1;
}

int main() {
    input();

    // 시간 이상 현상 확산 BFS
    memset(dist_isang, -1, sizeof(dist_isang));
    for (int i = 0; i < f; i++) {
        bfs(ri[i], ci[i], di[i], vi[i]);
    }

    // bottom 상의 시간의 벽 시작 위치 찾기
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (bottom[i][j] == 3) {
                startWX = i;
                startWY = j;
                break;
            }
        }
        if (startWX != -1) break;
    }
    printf("시간의 벽 : %d %d\n", startWX, startWY);

    // 연결된 미지의 공간과 시간의 벽 위치 찾기
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (bottom[i][j] == 0)
            {
                for (int d = 0; d < 4; d++) {
                    int nx = i + dx[d];
                    int ny = j + dy[d];
                    if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
                    if (bottom[nx][ny] == 3) {
                        linkBX = i;
                        linkBY = j;
                        if (d == 0) linkWD = 1, linkWX = i - startWX + m, linkWY = 0;
                        else if (d == 1) linkWD = 0, linkWX = i - startWX + m, linkWY = m * 3 - 1;
                        else if (d == 2) linkWD = 3, linkWX = 0, linkWY = j - startWY + m;
                        else linkWD = 2, linkWX = m*2 + 1, linkWY = j - startWY + m;
                    }
                }
            }
        }
    }
    printf("연결된 부분: (%d %d) -> (%d %d) %d\n", linkBX, linkBY, linkWX, linkWY, linkWD);

    // 시간의 벽을 펼치고 bfs 실행
    memset(nextWall, -1, sizeof(nextWall));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            nextWall[i + m][j + m * 2] = timeWall[0][j][m - 1 - i];
            nextWall[i + m][j] = timeWall[1][m - 1 - j][i];
            nextWall[i + m * 2][j + m] = timeWall[2][i][j];
            nextWall[i][j + m] = timeWall[3][m - 1 - i][m - 1 - j];
            nextWall[i + m][j + m] = timeWall[4][i][j];
            if (timeWall[4][i][j] == 2) {
                startX = i + m;
                startY = j + m;
                //printf("start: %d %d\n", startX, startY);
            }
        }
    }
    memset(dist_next, -1, sizeof(dist_next));
    val = bfs_next();
    printf("val = %d\n", val);

    for (int i = 0; i < m * 3; i++) {
        for (int j = 0; j < m * 3; j++) {
            printf("%3d ", nextWall[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    for (int i = 0; i < m * 3; i++) {
        for (int j = 0; j < m * 3; j++) {
            printf("%3d ", dist_next[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    memset(dist, -1, sizeof(dist));
    int ret = bfs_bottom();

    printf("Printf isang\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%3d ", dist_isang[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    printf("Printf bottom\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%3d ", bottom[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    printf("Printf dist\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%3d ", dist[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    printf("%d\n", ret);

    return 0;
}