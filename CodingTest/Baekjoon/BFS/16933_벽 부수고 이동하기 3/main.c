#include <stdio.h>
#include <stdbool.h>

#define MAX 1001
#define MAX_K 11

int n, m, k;
int board[MAX][MAX];
int queue[MAX*MAX*MAX_K][3];
int dist[MAX][MAX][MAX_K];
// int visited[MAX][MAX];
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
int front, rear;

void push(int x, int y, int k) {
    queue[rear][0] = x;
    queue[rear][1] = y;
    queue[rear++][2] = k;
}

void pop(int* x, int* y, int* k) {
    *x = queue[front][0];
    *y = queue[front][1];
    *k = queue[front++][2];
}

bool is_empty() {
    return front == rear;
}

int bfs() {
    while(!is_empty()) {
        int curX, curY, curK;
        pop(&curX, &curY, &curK);
        if(curX == n-1 && curY == m-1) return dist[curX][curY][curK];
        for(int i=0; i<4; i++) {
            int nx = curX + dx[i];
            int ny = curY + dy[i];
            int nk;
            if(nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
            if(curK >= k && board[nx][ny] == 1) continue;
            
            if(board[nx][ny] == 0) nk = curK;
            else if(curK < k && board[nx][ny]) nk = curK + 1;

            if(dist[nx][ny][nk] != -1) continue;
            dist[nx][ny][nk] = dist[curX][curY][curK] + 1;
            push(nx, ny, nk);
            // visited[nx][ny] = dist[nx][ny][nk];
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

    push(0, 0, 0);
    dist[0][0][0] = 1;
    // visited[0][0] = 1;
    int result = bfs();

    // for(int i=0; i<k+1; i++) {
    //     for(int j=0; j<n; j++) {
    //         for(int l=0; l<m; l++) {
    //             printf("%3d", dist[j][l][i]);
    //         }
    //         printf("\n");
    //     }
    //     printf("\n\n");
    // }

    printf("%d", result);
}