#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

#define X first
#define Y second

#define MAX 50
#define MAX_M 300

int n, m; // ���� ũ�� n, ���� �� m
int board[MAX][MAX];
int dist[MAX][MAX];
int sr, sc, er, ec; // �޵λ� ���� ������ ��ġ ��ǥ
int a[MAX_M][MAX_M]; // ������� ��ǥ
int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };
int board2[MAX][MAX];
int distCnt, stone, attack;
int rotateCnt[4] = { 0, 2, 1, 3 };
int seeBoard[MAX][MAX];
int stoneMax, rotMax, boardMax[MAX][MAX];
int stoneLoc[MAX_M][2];
int j_X, j_Y;
int boardJunsaNum[MAX][MAX];

void init() {
    distCnt = 0;
    stone = 0;
    attack = 0;
    stoneMax = 0;
    memset(stoneLoc, 0, sizeof(stoneLoc));
}

void rotate() {
    int tmp[MAX][MAX];
    memcpy(tmp, board2, sizeof(board2));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            board2[i][j] = tmp[n - j - 1][i];
        }
    }
}

void rotate_l() {
    int tmp[MAX][MAX];
    memcpy(tmp, board2, sizeof(board2));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            board2[i][j] = tmp[j][n - 1 - i];
        }
    }
}

void rotate_max() {
    int tmp[MAX][MAX];
    memcpy(tmp, boardMax, sizeof(boardMax));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            boardMax[i][j] = tmp[j][n - 1 - i];
        }
    }
}

void rotate_l_max() {
    int tmp[MAX][MAX];
    memcpy(tmp, boardMax, sizeof(boardMax));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            boardMax[i][j] = tmp[j][n - 1 - i];
        }
    }
}

void rotate_junsa() {
    int tmp[MAX][MAX];
    memcpy(tmp, boardJunsaNum, sizeof(boardJunsaNum));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            boardJunsaNum[i][j] = tmp[n - j - 1][i];
        }
    }
}

void rotate_l_junsa() {
    int tmp[MAX][MAX];
    memcpy(tmp, boardJunsaNum, sizeof(boardJunsaNum));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            boardJunsaNum[i][j] = tmp[j][n - 1 - i];
        }
    }
}

void shade_left(int x, int y) {
    int nx = x;
    int ny = y;
    while (nx--) {
        seeBoard[nx][ny] = -1;
        seeBoard[nx][ny - 1] = -1;
    }

    nx = x;
    while (--ny >= 0) {
        for (int i = nx - (y - ny); i >= 0; i--) {
            seeBoard[i][ny] = -1;
        }
    }
}

void shade_right(int x, int y) {
    int nx = x;
    int ny = y;
    while (nx--) {
        seeBoard[nx][ny] = -1;
        seeBoard[nx][ny + 1] = -1;
    }

    nx = x;
    while (ny++ <= n) {
        for (int i = nx - (ny - y); i >= 0; i--) {
            seeBoard[i][ny] = -1;
        }
    }
}

void makeStone(int rotCnt) {
    memset(seeBoard, 0, sizeof(seeBoard));

    //printf("boardJunsaNum\n");
    //for (int i = 0; i < n; i++) {
    //    for (int j = 0; j < n; j++) {
    //        printf("%3d ", boardJunsaNum[i][j]);
    //    }
    //    printf("\n");
    //}
    //printf("\n");

    int stoneCnt = 0;
    int nx = 0, ny = 0;
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (board2[i][j] == 2) {
                nx = i;
                ny = j;
                break;
            }
        }
    }
    int tmp_nx = nx;
    int tmp_ny = ny;

    // �߰���
    while (nx--) {
        //printf("�߰�: %d %d\n", nx, ny);
        seeBoard[nx][ny] = 1; // ���� ���� �� �ִ� ��
        if (board2[nx][ny] == 4) {
            stoneCnt += boardJunsaNum[nx][ny];
            break;
        }
    }

    // �߰����� �������� ����
    nx = tmp_nx;
    ny = tmp_ny;
    while (--ny >= 0) {
        for (int i = nx - (tmp_ny - ny); i >= 0; i--) {
            if (seeBoard[i][ny] == -1) continue;   // ������ �κ�
            //printf("����: %d %d\n", i, ny);
            seeBoard[i][ny] = 1; // ���� ���� �� �ִ� ��
            if (board2[i][ny] == 4) {
                stoneCnt += boardJunsaNum[i][ny];
                shade_left(i, ny);
            }
        }
    }

    nx = tmp_nx;
    ny = tmp_ny;
    // �߰����� �������� ������
    while (++ny < n) {
        for (int i = nx - (ny - tmp_ny); i >= 0; i--) {
            if (seeBoard[i][ny] == -1) continue;   // ������ �κ�
            //printf("������: %d %d\n", i, ny);
            seeBoard[i][ny] = 1; // ���� ���� �� �ִ� ��
            if (board2[i][ny] == 4) {
                stoneCnt += boardJunsaNum[i][ny];
                shade_right(i, ny);
            }
        }
    }

    //for (int i = 0; i < n; i++) {
    //    for (int j = 0; j < n; j++) {
    //        printf("%3d ", seeBoard[i][j]);
    //    }
    //    printf("\n");
    //}
    //printf("\n");
    //printf("stoneCnt: %d\n", stoneCnt);

    //for (int j = 0; j < rotCnt; j++) rotate_l();
    if (stoneCnt > stoneMax) {
        stoneMax = stoneCnt;
        //printf("stoneMax: %d\n", stoneMax);
        int idx = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (seeBoard[i][j] == 1 && board2[i][j] == 4) {
                    //printf("���� ���� ����: %d %d\n", i, j);
                    stoneLoc[idx][0] = i;
                    stoneLoc[idx][1] = j;
                    idx++;
                    rotMax = rotCnt;
                }
                boardMax[i][j] = seeBoard[i][j];
            }
        }
    }

}

int bfs() {
    queue<pair<int, int>> Q;
    Q.push({ er, ec });
    dist[er][ec] = 0;
    while (!Q.empty()) {
        auto cur = Q.front();
        Q.pop();
        for (int i = 0; i < 4; i++) {
            int nx = cur.X + dx[i];
            int ny = cur.Y + dy[i];
            if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
            if (dist[nx][ny] >= 0 || board[nx][ny] == 1) continue;
            dist[nx][ny] = dist[cur.X][cur.Y] + 1;
            if (nx == sr && ny == sc) return 0;
            Q.push({ nx, ny });
        }
    }

    return -1;
}

void junsa_first(int x, int y) {
    int djx[4] = { -1, 1, 0, 0 };
    int djy[4] = { 0, 0, -1, 1 };
    int min = abs(sr - x) + abs(sc - y);
    j_X = x;
    j_Y = y;
    for (int i = 0; i < 4; i++) {
        int nx = x + djx[i];
        int ny = y + djy[i];
        if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
        if (boardMax[nx][ny] == 1) continue;
        int dist = abs(sr - nx) + abs(sc - ny);
        if (dist < min || (dist == min && nx == sr && ny == sc)) {
            min = dist;
            j_X = nx;
            j_Y = ny;
        }
    }
}

void junsa_second(int x, int y) {
    int dsx[4] = { 0, 0, -1, 1 };
    int dsy[4] = { -1, 1, 0, 0 };
    int min = abs(sr - x) + abs(sc - y);
    j_X = x;
    j_Y = y;
    for (int i = 0; i < 4; i++) {
        int nx = x + dsx[i];
        int ny = y + dsy[i];
        if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
        if (boardMax[nx][ny] == 1) continue;
        int dist = abs(sr - nx) + abs(sc - ny);
        if (dist < min || (dist == min && nx == sr && ny == sc)) {
            min = dist;
            j_X = nx;
            j_Y = ny;
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    init();
    scanf("%d %d", &n, &m);
    scanf("%d %d %d %d", &sr, &sc, &er, &ec);
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &a[i][0], &a[i][1]);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &board[i][j]);
        }
    }
    memcpy(board2, board, sizeof(board));

    board2[sr][sc] = 2;
    board2[er][ec] = 3;
    for (int i = 0; i < m; i++) {
        board2[a[i][0]][a[i][1]] = 4;
    }

    int tt = 3;
    while (1) {
        stoneMax = 0;
        rotMax = 0;
        memset(boardMax, 0, sizeof(boardMax));
        memset(stoneLoc, 0, sizeof(stoneLoc));

        memset(boardJunsaNum, 0, sizeof(boardJunsaNum));
        init();
        distCnt = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (board2[i][j] == 5) board2[i][j] = 4;
            }
        }

        // 1. �޵λ� ��ĭ �̵�
        memset(dist, -1, sizeof(dist));
        int check = bfs();      // ���� -> �޵λ� �Ÿ� ���
        if (check == -1) {
            printf("-1\n");
            break;
        }

        printf("dist_print\n");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                printf("%3d ", dist[i][j]);
            }
            printf("\n");
        }
        printf("\n");

        // �޵λ� ���� ��ġ�� �������� �����¿� Ž�� �� �̵�
        for (int i = 0; i < 4; i++) {
            int nx = sr + dx[i];
            int ny = sc + dy[i];
            if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
            if (board[nx][ny] == 1) continue;
            if (dist[nx][ny] == dist[sr][sc] - 1) {
                board2[sr][sc] = board[sr][sc];
                sr = nx;
                sc = ny;
                if (board2[sr][sc] == 4) {
                    for (int j = 0; j < m; j++) {
                        if (a[j][0] == sr && a[j][1] == sc) {
                            a[j][0] = -1;
                            a[j][1] = -1;
                        }
                    }
                }
                board2[sr][sc] = 2;
                break;
            }
        }

        // ������ �����ϸ� 0 ��� �� return 
        if (sr == er && sc == ec) {
            printf("0\n");
            break;
        }

        for (int i = 0; i < m; i++) {
            //printf("���� ��ġ: (%d, %d)\n", a[i][0], a[i][1]);
            int nx = a[i][0];
            int ny = a[i][1];
            boardJunsaNum[nx][ny]++;
        }

        printf("boardJunsaNum_print\n");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                printf("%3d ", boardJunsaNum[i][j]);
            }
            printf("\n");
        }
        printf("\n");

        // 2. �޵λ��� �ü�
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < rotateCnt[i]; j++) rotate();
            for (int j = 0; j < rotateCnt[i]; j++) rotate_junsa();
            makeStone(rotateCnt[i]);
            for (int j = 0; j < rotateCnt[i]; j++) rotate_l();
            for (int j = 0; j < rotateCnt[i]; j++) rotate_l_junsa();
        }

        printf("Board2_print\n");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                printf("%3d ", board2[i][j]);
            }
            printf("\n");
        }
        printf("\n");

        for (int j = 0; j < rotMax; j++) rotate();
        for (int j = 0; j < rotMax; j++) rotate_junsa();
        for (int i = 0; i < stoneMax; i++) {
            int nx = stoneLoc[i][0];
            int ny = stoneLoc[i][1];
            if(boardJunsaNum[nx][ny] >= 1) board2[nx][ny] = 5;
            //stone++;
        }
        for (int j = 0; j < rotMax; j++) rotate_l();
        for (int j = 0; j < rotMax; j++) rotate_l_junsa();

        for (int j = 0; j < rotMax; j++) rotate_max();
        printf("BoardMax_print\n");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                printf("%3d ", boardMax[i][j]);
            }
            printf("\n");
        }
        printf("\n");
        //for (int j = 0; j < rotMax; j++) rotate_l_max();


        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (board2[i][j] == 5 && boardJunsaNum[i][j] > 0) stone += boardJunsaNum[i][j];
            }
        }

        // 3. ������ �̵� - ù��° (�����¿�)
        for (int i = 0; i < m; i++) {
            int nx = a[i][0];
            int ny = a[i][1];
            if (boardMax[nx][ny] == 1 || nx == -1 || ny == -1) continue;
            junsa_first(nx, ny);
            board2[nx][ny] = board[nx][ny];
            if (j_X == nx && j_Y == ny) continue;
            int move_dist = abs(j_X - nx) + abs(j_Y - ny);
            distCnt += move_dist;
            printf("����[%d] �̵�: (%d,%d) -> (%d,%d) �Ÿ�: %d\n",
                i, nx, ny, j_X, j_Y, abs(j_X - nx) + abs(j_Y - ny));
            if (j_X == sr && j_Y == sc) {
                attack++;
                a[i][0] = a[i][1] = -1;
                continue;
            }
            a[i][0] = j_X;
            a[i][1] = j_Y;
        }

        // ������ �̵� - �ι�° (�¿����)
        for (int i = 0; i < m; i++) {
            int nx = a[i][0];
            int ny = a[i][1];
            if (boardMax[nx][ny] == 1 || nx == -1 || ny == -1) continue;

            junsa_second(nx, ny);
            board2[nx][ny] = board[nx][ny];
            if (j_X == nx && j_Y == ny) continue;

            int move_dist = abs(j_X - nx) + abs(j_Y - ny);
            distCnt += move_dist;

            printf("����[%d] �̵�: (%d,%d) -> (%d,%d) �Ÿ�: %d\n",
                i, nx, ny, j_X, j_Y, abs(j_X - nx) + abs(j_Y - ny));
            if (j_X == sr && j_Y == sc) {
                attack++;
                a[i][0] = a[i][1] = -1;
                continue;
            }
            a[i][0] = j_X;
            a[i][1] = j_Y;
        }

        for (int i = 0; i < m; i++) {
            int nx = a[i][0];
            int ny = a[i][1];
            if (board2[nx][ny] == 1 || board2[nx][ny] == 0) board2[nx][ny] = 4;
        }

        printf("board2print ������\n");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                printf("%3d ", board2[i][j]);
            }
            printf("\n");
        }
        printf("\n");

        printf("%d %d %d\n", distCnt, stoneMax, attack);
    }
    //pair<int, int> p = backTracking({er, ec});
    //printf("%d %d\n", p.X, p.Y);

    /*
    1. �޵λ� ��ĭ �̵�
        - ����(0)�� �̵�����
        - �����¿� �켱����
        - �������� �ִܰ�� bfs
        - ���� ������ ���� -> ������ ���� ���� ī��Ʈ X
    2. �޵λ��� �ü�
        - 90�� �þ߰�
        - �����¿� �켱����
        - ����� ���� ����, ����� �ٸ� ���翡 ������ �� ����
    3. ������ �̵�
        - �޵λ���� ����ư �ִ� �Ÿ�
        - ù��° ��ĭ�� �����¿�, �ι�° ��ĭ�� �¿���� �켱����
        - �޵λ� ������ �����ϰ� �����

    !! ������ �����ϸ� 0 ����ϰ� ����
    printf(������ �̵��Ÿ� ����, ��, ����)
    */
    //}

    return 0;
}

#if 0
for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
        printf("%3d ", dist[i][j]);
    }
    printf("\n");
}
printf("\n");
#endif