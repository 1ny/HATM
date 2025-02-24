#include <stdio.h>
#include <stdbool.h>

#define MAX 1000

int n, m;
int arr[MAX][MAX] = {0,};
int queue[MAX*MAX][2] = {0,};
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
int front = 0, rear = 0;
int day[MAX][MAX] = {0,};

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
            if(day[nx][ny] >= 0) continue;
            if(nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
            day[nx][ny] = day[curX][curY] + 1;
            push(nx, ny);
        }
    }
}

int main() {
    int max = 0;
    scanf("%d %d", &m, &n);
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            scanf("%d", &arr[i][j]);
            if(arr[i][j] == 1) push(i, j);  // 익은 토마토는 push
            if(arr[i][j] == 0) day[i][j] = -1;
            // 익지 않은 토마토일 경우 -1
        }
    }
    
    bfs();

    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            if(day[i][j] == -1) { // 익지 않은 토마토가 남아있을 경우
                printf("-1");
                return 0;
            }
            if(day[i][j] > max) max = day[i][j];
        }
    }

    printf("%d", max);

    return 0;
}