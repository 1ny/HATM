#include <stdio.h>
#include <stdbool.h>

#define MAX 1001    
#define WALL_LIMIT 1

int n, m;
int arr[MAX][MAX];
int queue[MAX*MAX*2][3]; 
int dist[MAX][MAX][WALL_LIMIT + 1];
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
int front, rear;
int wallCnt;
int wall[MAX*MAX][2];

void push(int x, int y, int walls_removed) {
    queue[rear][0] = x;
    queue[rear][1] = y;
    queue[rear++][2] = walls_removed;
}

void pop(int* x, int* y, int* walls_removed) {
    *x = queue[front][0];
    *y = queue[front][1];
    *walls_removed = queue[front++][2];
}

bool is_empty() {
    return front == rear;
}

int bfs() {
    front = 0, rear = 0;
    push(0, 0, 0); 
    dist[0][0][0] = 1;

    while(!is_empty()) {
        int curX, curY, walls_removed;
        pop(&curX, &curY, &walls_removed);

        if(curX == n - 1 && curY == m - 1) return dist[curX][curY][walls_removed];

        for(int i = 0; i < 4; i++) {
            int nx = curX + dx[i];
            int ny = curY + dy[i];

            if(nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
            if(dist[nx][ny][walls_removed] != -1) continue;

            if(arr[nx][ny] == 0) {
                dist[nx][ny][walls_removed] = dist[curX][curY][walls_removed] + 1;
                push(nx, ny, walls_removed);
            } else if(walls_removed < WALL_LIMIT) {
                dist[nx][ny][walls_removed + 1] = dist[curX][curY][walls_removed] + 1;
                push(nx, ny, walls_removed + 1);
            }
        }
    }
    return -1;
}

int main() {
    scanf("%d %d", &n, &m);

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            scanf("%1d", &arr[i][j]);
            for(int k = 0; k <= WALL_LIMIT; k++) {
                dist[i][j][k] = -1;
            }
        }
    }

    int origin = bfs();

    if(origin != -1) {
        printf("%d", origin);
    } else {
        printf("-1");
    }

    return 0;
}
