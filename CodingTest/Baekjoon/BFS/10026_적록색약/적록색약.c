#include <stdio.h>
#include <stdbool.h>

#define MAX 101

int n;
char board[MAX][MAX];
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

int bfs(int x, int y) {
    push(x, y);
    while(!is_empty()) {
        int curX, curY;
        pop(&curX, &curY);
        for(int i=0; i<4; i++) {
            int nx = curX + dx[i];
            int ny = curY + dy[i];
            if(nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
            if(visited[nx][ny] || board[nx][ny] != board[curX][curY]) continue;
            push(nx, ny);
        }
    }
}

int main() {
    scanf("%d ", &n);
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            scanf("%c ", &board[i][j]);
        }
    }

    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            if(visited[i][j]) continue;
            cnt++;
            bfs(i, j);
        }
    }
    printf("%d ", cnt);
    cnt = 0;
    front = 0, rear = 0;
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            visited[i][j] = 0;
            if(board[i][j] == 'R') board[i][j] = 'G';
        }
    }
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            if(visited[i][j]) continue;
            cnt++;
            bfs(i, j);
        }
    }
    printf("%d", cnt);
}