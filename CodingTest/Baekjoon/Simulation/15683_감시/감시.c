#include <stdio.h>
#include <string.h>

#define MAX 10
#define X first
#define Y second

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, -1, 0, 1}; // 어찌됐든 시계/반시계 방향 순서대로 여야함.

int n, m;
int board1[MAX][MAX];
int board2[MAX][MAX];

typedef struct {
    int X, Y;
} CCTV;

CCTV cctv[8]; // 최대 CCTV 개수는 8개
int cctv_count = 0;

void upd(int x, int y, int dir) {
    dir %= 4;
    while (1) {
        x += dx[dir];
        y += dy[dir];
        if(x < 0 || x >= n || y < 0 || y >= m || board2[x][y] == 6) return;
        if(board2[x][y] != 0) continue;
        board2[x][y] = 7;
    }
}

int main() {
    scanf("%d %d", &n, &m);
    int mn = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &board1[i][j]);
            if (board1[i][j] != 0 && board1[i][j] != 6) {
                cctv[cctv_count].X = i;
                cctv[cctv_count].Y = j;
                cctv_count++;
            }
            if (board1[i][j] == 0) mn++;
        }
    }

    for (int tmp = 0; tmp < (1 << (2 * cctv_count)); tmp++) {
        memcpy(board2, board1, sizeof(board1));
        int brute = tmp;

        for (int i = 0; i < cctv_count; i++) {
            int dir = brute % 4;
            brute /= 4;
            int x = cctv[i].X;
            int y = cctv[i].Y;

            if (board1[x][y] == 1) {
                upd(x, y, dir);
            } else if (board1[x][y] == 2) {
                upd(x, y, dir);
                upd(x, y, dir + 2);
            } else if (board1[x][y] == 3) {
                upd(x, y, dir);
                upd(x, y, dir + 1);
            } else if (board1[x][y] == 4) {
                upd(x, y, dir);
                upd(x, y, dir + 1);
                upd(x, y, dir + 2);
            } else { // board1[x][y] == 5
                upd(x, y, dir);
                upd(x, y, dir + 1);
                upd(x, y, dir + 2);
                upd(x, y, dir + 3);
            }
        }

        int val = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (board2[i][j] == 0) val++;

        if (val < mn) mn = val;
    }

    printf("%d\n", mn);
    return 0;
}
