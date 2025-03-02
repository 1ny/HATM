#include <stdio.h>
#include <stdbool.h>

#define MAX 101

int n;
int arr[MAX][MAX];
int queue[MAX*MAX][2];
int dist[MAX][MAX];
int arrNum[MAX][MAX];
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
int landNum = 1;
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

void bfs_idx() {
    while(!is_empty()) {
        int curX, curY;
        pop(&curX, &curY);
        for(int i=0; i<4; i++) {
            int nx = curX + dx[i];
            int ny = curY + dy[i];
            if(nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
            if(arrNum[nx][ny]|| !arr[nx][ny]) continue;
            arrNum[nx][ny] = landNum;
            push(nx, ny);
        }
    }
}

int bfs(int comp) {
    while(!is_empty()) {
        int curX, curY;
        pop(&curX, &curY);
        for(int i=0; i<4; i++) {
            int nx = curX + dx[i];
            int ny = curY + dy[i];
            if(nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
            if(dist[nx][ny] != -1 || arrNum[nx][ny] == comp) continue;
            dist[nx][ny] = dist[curX][curY] + 1;
            if(arrNum[nx][ny] != comp && arrNum[nx][ny] > 0) return dist[curX][curY];
            push(nx, ny);
        }
    }
    return 0;
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
            if(arrNum[i][j] || !arr[i][j]) continue;
            push(i, j);
            arrNum[i][j] = landNum;
            bfs_idx();
            landNum++;
        }
    }
    
    for(int k=0; k<n; k++) {
        for(int p=0; p<n; p++) {
            dist[k][p] = -1;
        }
    }

    int min = MAX*MAX;
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            front = rear = 0;

            memset(dist, -1, sizeof(dist));

            if(dist[i][j] >= 0 || !arrNum[i][j]) continue;
            push(i, j);
            dist[i][j] = 0;
            int result = bfs(arrNum[i][j]);;

            if(result != 0 && result < min) min = result;
        }
    }

    printf("%d", min);
}