#include <stdio.h>
#include <stdbool.h>

#define MAX 1001

int n, m;
int arr[MAX][MAX];
int queue[MAX*MAX][2];
int visited[MAX][MAX];
// int visited_area[MAX][MAX];
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
int front, rear;
int area_table[MAX*MAX];
int area_visited[MAX*MAX];
int area = 1;

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

void bfs(int x, int y) {
    int cnt = 1;
    push(x, y);
    visited[x][y] = area;
    while(!is_empty()) {
        int curX, curY;
        pop(&curX, &curY);
        for(int i=0; i<4; i++) {
            int nx = curX + dx[i];
            int ny = curY + dy[i];
            if(nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
            if(visited[nx][ny] || arr[nx][ny]) continue;
            
            push(nx, ny);
            visited[nx][ny] = area;
            cnt++;
        }
    }

    area_table[area] = cnt;
    area++;
}

int main() {
    scanf("%d %d", &n, &m);

    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            scanf("%1d", &arr[i][j]);
        }
    }

    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            front = rear = 0;
            if(arr[i][j] || visited[i][j] > 0) continue;
            bfs(i, j);
        }
    }

    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
-            if(arr[i][j]) {
                for(int i=1; i<=area; i++) {
                    area_visited[i] = 0;
                }
                for(int p=0; p<4; p++) {
                    int nx = i + dx[p];
                    int ny = j + dy[p];
                    if(nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
                    if(visited[nx][ny] == 0 || arr[nx][ny] > 0 || area_visited[visited[nx][ny]]) continue;
                    arr[i][j] += area_table[visited[nx][ny]];
                    area_visited[visited[nx][ny]] = 1;
                }
            }
        }
    }

    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            printf("%d", arr[i][j]%10);
        }
        printf("\n");
    }
}

/*
00220
33000
30101
01010


46223
33732
30141
01413
*/