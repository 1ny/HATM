#include <stdio.h>
#include <stdbool.h>

#define MAX 201
#define MAX_K 31

int k;
int w, h;
int arr[MAX][MAX];
int queue[MAX*MAX*MAX_K][3];
int dist[MAX_K][MAX][MAX];
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
int dkx[8] = {-1, 1, -1, 1, -2, 2, -2, 2};
int dky[8] = {2, 2, -2, -2, 1, 1, -1, -1};
int front, rear;
int min = MAX*MAX;

void push(int k, int x, int y) {
    queue[rear][0] = k;
    queue[rear][1] = x;
    queue[rear++][2] = y;
}

void pop(int* k, int* x, int* y) {
    *k = queue[front][0];
    *x = queue[front][1];
    *y = queue[front++][2];
}

bool is_empty() {
    return front == rear;
}

int bfs() {
    memset(dist, 0, sizeof(dist));
    front = 0, rear = 0;
    push(0, 0, 0);
    dist[0][0][0] = 1;

    while(!is_empty()) {
        int curK, curX, curY;
        pop(&curK, &curX, &curY);
        
        if(curK < k) {
            for(int i=0; i<8; i++) {
                int nx = curX + dkx[i];
                int ny = curY + dky[i];
                if(nx < 0 || nx >= h || ny < 0 || ny >= w) continue;
                if(arr[nx][ny]) continue;
                if(dist[curK+1][nx][ny]) continue;
                dist[curK + 1][nx][ny] = dist[curK][curX][curY] + 1;
                push(curK + 1, nx, ny);
            }
        }
        
        for(int i=0; i<4; i++) {
            int nx = curX + dx[i];
            int ny = curY + dy[i];
            if(nx < 0 || nx >= h || ny < 0 || ny >= w) continue;
            if(arr[nx][ny]) continue;
            if(dist[curK][nx][ny]) continue;
            dist[curK][nx][ny] = dist[curK][curX][curY] + 1;
            push(curK, nx, ny);
        }
    }

    for(int i=0; i<=k; i++) {
        if(dist[i][h-1][w-1]) {
            if(dist[i][h-1][w-1] < min) min = dist[i][h-1][w-1];
        }
    }

    if(min == MAX*MAX) return -1;
    else return min-1;
}

int main() {
    scanf("%d", &k);
    scanf("%d %d", &w, &h);
    for(int i=0; i<h; i++) {
        for(int j=0; j<w; j++) {
            scanf("%d", &arr[i][j]);
        }
    }

    int result = bfs();
    printf("%d", result);
}