#include <stdio.h>

#define MAX 500

int n, m;
int arr[MAX][MAX] = {0,};
int visited[MAX][MAX] = {0,};
int queue[MAX*MAX][2] = {0,};
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
int front = 0, rear = 0;
int area = 0;

int bfs(int x, int y) {
    area = 0;
    visited[x][y] = 1;
    queue[rear][0] = x;
    queue[rear++][1] = y;

    while(front < rear) {
        area++;
        for(int i=0; i<4; i++) {
            int nx = queue[front][0] + dx[i];
            int ny = queue[front][1] + dy[i];
            if(visited[nx][ny] || arr[nx][ny] == 0) continue;
            if(nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
            visited[nx][ny] = 1;
            queue[rear][0] = nx;
            queue[rear++][1] = ny;
        }
        front++;
    }
    return area;
}

int main() {
    int maxArea = 0, num = 0;
    scanf("%d %d", &n, &m);
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            scanf("%d", &arr[i][j]);
        }
    }

    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            if(visited[i][j] || arr[i][j] == 0) continue;
            num++;
            int area = bfs(i, j);
            if(area > maxArea) maxArea = area;
        }
    }
    printf("%d\n%d", num, maxArea);
    return 0;
}