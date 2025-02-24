#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#define MAX 50
#define MAX_K 2500

int t, m, n, k; // 테스트 케이스 개수 t, 가로길이 m, 세로길이 n, 배추가 심어진 칸 개수 k
int board[MAX][MAX];
int queue[MAX*MAX][2];
int visited[MAX][MAX];
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
int front, rear;
int cnt;

void push(int x, int y) {
    queue[rear][0] = x;
    queue[rear++][1] = y;
    visited[x][y] = 1;
}

void pop(int* x, int* y) {
    *x = queue[front][0];
    *y = queue[front++][1];
}

bool is_empty() {
    return front == rear;
}

void bfs(int x, int y) {
    push(x, y);
    while(!is_empty()) {
        int curX, curY;
        pop(&curX, &curY);
        for(int i=0; i<4; i++) {
            int nx = curX + dx[i];
            int ny = curY + dy[i];
            if(nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
            if(visited[nx][ny] || !board[nx][ny]) continue;
            push(nx, ny);
        }
    }
}

int main() {
    clock_t start, finish;
    double duration;
    
    start = clock();

    scanf("%d", &t);
    for(int c=0; c<t; c++) {
        scanf("%d %d %d", &m, &n, &k);
        for(int i=0; i<n; i++) {
            for(int j=0; j<m; j++) {
                visited[i][j] = 0;
                board[i][j] = 0;
            }
        }
        for(int p=0; p<k; p++) {
            int qX, qY;
            scanf("%d %d", &qY, &qX);
            board[qX][qY] = 1;
        }
        for(int i=0; i<n; i++) {
            for(int j=0; j<m; j++) {
                if(visited[i][j] || !board[i][j]) continue;
                cnt++;
                bfs(i,j);
            }
        }
        printf("%d\n", cnt);
        cnt = 0;
        front = 0, rear = 0;
        // for(int i=0; i<n; i++) {
        //     for(int j=0; j<m; j++) {
        //         printf("%d ", board[i][j]);
        //     }
        //     printf("\n");
        // }
    }

    finish = clock();
    
    duration = (double)(finish - start) / CLOCKS_PER_SEC;
    printf("%f초", duration);

    return 0;
}