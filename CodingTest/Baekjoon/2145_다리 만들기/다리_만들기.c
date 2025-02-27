#include <stdio.h>
#include <stdbool.h>

#define MAX 101

int n;
int arr[MAX][MAX];
int queue[MAX*MAX][2];
int dist[MAX][MAX];
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
int landNum;
int front, rear;

void push(int x, int y) {
    queue[rear][0] = x;
    queue[rear++][1] = y;
}

void pop(int* x, int* y) {
    *x = queue[front][0];
    *y = queue[front++][1];
}

bool is_empty() {
    return front == rear;
}

int bfs() {
    while(!is_empty()) {
        int curX, curY;
        pop(&curX, &curY);
        for(int i=0; i<4; i++) {
            int nx = curX + dx[i];
            int ny = curY + dy[i];
            if(arr[nx][ny] == 0) return dist[curX][curY] + 1;
            if(nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
            if(dist[nx][ny] >= 0|| arr[nx][ny]) continue;
            dist[nx][ny] = dist[curX][curY] + 1;
            push(nx, ny);
        }
    }
}

int main() {
    scanf("%d", &n);
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            scanf("%d", &arr[i][j]);
        }
    }

    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            if(arr[i][j] == 1) dist[i][j] = 0;
            else dist[i][j] = -1;
        }
    }

    int min = MAX*MAX;
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            if(dist[i][j] != 0 || !arr[i][j]) continue;
            push(i, j);
            dist[i][j] = 0;
            int result = bfs();

            if(result < min) min = result;
        }
    }

    printf("%d", min);
}