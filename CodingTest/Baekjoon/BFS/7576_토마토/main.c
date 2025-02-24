#include <stdio.h>

#define MAX 1002

int board[MAX][MAX];
int dist[MAX][MAX];
int n, m;
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

int queueX[MAX * MAX];
int queueY[MAX * MAX];
int front = 0, rear = 0;

void push(int x, int y) {
    queueX[rear] = x;
    queueY[rear] = y;
    rear++;
}

void pop(int *x, int *y) {
    *x = queueX[front];
    *y = queueY[front];
    front++;
}

int is_empty() {
    return front == rear;
}

void bfs() {
    while (!is_empty()) {
        int curX, curY;
        pop(&curX, &curY);
        for (int dir = 0; dir < 4; dir++) {
            int nx = curX + dx[dir];
            int ny = curY + dy[dir];
            if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
            if (dist[nx][ny] >= 0) continue;
            dist[nx][ny] = dist[curX][curY] + 1;
            push(nx, ny);
        }
    }
}

int main(void) {
    scanf("%d %d", &m, &n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &board[i][j]);
            if (board[i][j] == 1) {
                push(i, j);
            }
            if (board[i][j] == 0) {
                dist[i][j] = -1;
            }
        }
    }
    
    bfs();
    
    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (dist[i][j] == -1) {
                printf("-1\n");
                return 0;
            }
            if (dist[i][j] > ans) {
                ans = dist[i][j];
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}
