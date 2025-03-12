#include <stdio.h>
#include <stdbool.h>

#define MAX 1001
#define MAX_K 12
#define DAY 0
#define NIGHT 1

int n, m, k;
int board[MAX][MAX];
int queue[MAX*MAX*MAX_K*2][4];
int dist[MAX][MAX][MAX_K][2];
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
int day = DAY;
int front, rear;

void push(int x, int y, int k, int d) {
    queue[rear][0] = x;
    queue[rear][1] = y;
    queue[rear][2] = k;
    queue[rear++][3] = d;
}

void pop(int* x, int* y, int* k, int* d) {
    *x = queue[front][0];
    *y = queue[front][1];
    *k = queue[front][2];
    *d = queue[front++][3];
}

bool is_empty() {
    return front == rear;
}

int bfs() {
    while(!is_empty()) {
        int curX, curY, curK, curD;
        pop(&curX, &curY, &curK, &curD);
        if(curX == n-1 && curY == m-1) return dist[curX][curY][curK][curD];
        for(int i=0; i<4; i++) {
            int nx = curX + dx[i];
            int ny = curY + dy[i];
            int nk, nd = curD ^ 1;
            if(nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
            if(curK >= k && board[nx][ny]) continue;


            if(board[nx][ny] == 0) {
                nk = curK;
            }
            else {
                if(curD == DAY) {
                    nk = curK + 1;
                }
                else {
                    nx = curX;
                    ny = curY;
                    nk = curK;
                }
            }
            if(dist[nx][ny][nk][nd] != -1) continue;
            dist[nx][ny][nk][nd] = dist[curX][curY][curK][curD] + 1;
            push(nx, ny, nk, nd);
        }
    }
    return -1;
}

int main() {
    scanf("%d %d %d", &n, &m, &k);
    memset(dist, -1, sizeof(dist));
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            scanf("%1d", &board[i][j]);
        }
    }

    push(0, 0, 0, DAY);
    dist[0][0][0][0] = 1;
    int result = bfs();

    printf("%d", result);
}