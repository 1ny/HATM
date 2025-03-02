#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF 0x7f7f7f7f
#define MAX_N 202
#define MAX_K 32

int board[MAX_N][MAX_N];
int vis[MAX_K][MAX_N][MAX_N];
int dmx[4] = { 0, 0, 1, -1 };
int dmy[4] = { 1, -1, 0, 0 };
int dkx[8] = { -2, -2, -1, -1, 1, 1, 2, 2 };
int dky[8] = { 1, -1, 2, -2, 2, -2, 1, -1 };

int queue[MAX_N * MAX_N * MAX_K][3];
int front = 0, rear = 0;

void push(int k, int x, int y) {
    queue[rear][0] = k;
    queue[rear][1] = x;
    queue[rear][2] = y;
    rear++;
}

void pop(int *k, int *x, int *y) {
    *k = queue[front][0];
    *x = queue[front][1];
    *y = queue[front][2];
    front++;
}

int is_empty() {
    return front == rear;
}

int bfs(int Kn, int bX, int bY) {
    memset(vis, 0, sizeof(vis));
    front = rear = 0;
    push(0, 0, 0);
    vis[0][0][0] = 1;
    
    while (!is_empty()) {
        int curK, curX, curY;
        pop(&curK, &curX, &curY);
        
        if (curK < Kn) {
            for (int i = 0; i < 8; i++) {
                int nx = curX + dkx[i], ny = curY + dky[i];
                if (nx < 0 || ny < 0 || nx >= bX || ny >= bY) continue;
                if (board[nx][ny]) continue;
                if (vis[curK + 1][nx][ny]) continue;
                vis[curK + 1][nx][ny] = vis[curK][curX][curY] + 1;
                push(curK + 1, nx, ny);
            }
        }
        
        for (int i = 0; i < 4; i++) {
            int nx = curX + dmx[i], ny = curY + dmy[i];
            if (nx < 0 || ny < 0 || nx >= bX || ny >= bY) continue;
            if (board[nx][ny]) continue;
            if (vis[curK][nx][ny]) continue;
            vis[curK][nx][ny] = vis[curK][curX][curY] + 1;
            push(curK, nx, ny);
        }
    }
    
    int ans = INF;
    for (int i = 0; i <= Kn; i++) {
        if (vis[i][bX - 1][bY - 1]) {
            if (vis[i][bX - 1][bY - 1] < ans) {
                ans = vis[i][bX - 1][bY - 1];
            }
        }
    }
    
    return (ans != INF) ? ans - 1 : -1;
}

int main() {
    int Kn, bX, bY;
    scanf("%d %d %d", &Kn, &bY, &bX);
    
    for (int i = 0; i < bX; i++) {
        for (int j = 0; j < bY; j++) {
            scanf("%d", &board[i][j]);
        }
    }
    
    printf("%d", bfs(Kn, bX, bY));
    
    return 0;
}
