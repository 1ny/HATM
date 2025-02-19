#include <stdio.h>
#include <stdbool.h>

#define MAX 1000

int r, c;
char arr[MAX][MAX] = {0,};
int queue[MAX*MAX][2] = {0,};
int minite[MAX][MAX] = {0,};
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
int front = 0, rear = 0;
int min = 0;

void push(int x, int y) {
    queue[rear][0] = x;
    queue[rear++][1] = y;
}

void pop(int* x, int* y) {
    *x = queue[front][0];
    *y = queue[front++][1];
}

bool is_empty() {
    return (front == rear);
}

void bfs() {
    while(!is_empty()) {
        int curX, curY;
        pop(&curX, &curY);
        
        for(int i=0; i<4; i++) {
            int nx = curX + dx[i];
            int ny = curY + dy[i];

            if(minite[nx][ny] == -1) continue;

            push(nx, ny);
            minite[nx][ny] = minite[curX][curY];
        }

        // 불 확산 -> minite = -1
        for(int i=0; i<r; i++) {
            for(int j=0; j<c; j++) {
                if(arr[i][j] == 'F') {
                    for(int k=0; k<4; k++) {
                        int mx = i + dx[i];
                        int my = j + dy[i];

                        if(minite[mx][my] == -1) continue;
                        if(mx < 0 || mx >= r || my < 0 || my >= c) continue;

                        minite[mx][my] = -1;
                    }
                }
            }
        }
    }
}

int main() {
    scanf("%d %d", &r, &c);
    for(int i=0; i<r; i++) {
        for(int j=0; j<c; j++) {
            scanf("%c", &arr[i][j]);
            if(arr[i][j] == 'J') push(i, j);
            // 불이 있거나 벽이면 이동할 수 없음을 표시시
            if(arr[i][j] == '#' || arr[i][j] == 'F') minite[i][j] = -1;
        }
    }

    bfs();

    // printf("%d", );
    return 0;
}