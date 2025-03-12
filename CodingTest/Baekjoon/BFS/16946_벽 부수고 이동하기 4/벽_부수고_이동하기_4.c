#include <stdio.h>
#include <stdbool.h>

#define MAX 1001

int n, m;
int arr[MAX][MAX];
int queue[MAX*MAX][2];
int visited[MAX][MAX];
int visited_area[MAX][MAX];
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
int front, rear;
int area_check[MAX*MAX];
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
    visited[x][y] = 1;
    visited_area[x][y] = area;
    while(!is_empty()) {
        // printf("front = %d, rear = %d\n", front, rear);
        int curX, curY;
        pop(&curX, &curY);
        // printf("(%d, %d)\n", curX, curY);
        for(int i=0; i<4; i++) {
            int nx = curX + dx[i];
            int ny = curY + dy[i];
            if(nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
            if(visited[nx][ny] || arr[nx][ny]) continue;
            
            push(nx, ny);
            visited[nx][ny] = 1;
            visited_area[nx][ny] = area;
            cnt++;
        }
    }

    while(front > 0) {
        front--;
        int trX, trY;
        pop(&trX, &trY);
        visited[trX][trY] = cnt;
        front--;            
    }

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

    
    // for(int i=0; i<n; i++) {
    //     for(int j=0; j<m; j++) {
    //         printf("%d", visited_area[i][j]);
    //     }
    //     printf("\n");
    // }
    // printf("\n");

    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            memset(area_check, 0, sizeof(area_check));
            if(arr[i][j]) {
                for(int p=0; p<4; p++) {
                    int nx = i + dx[p];
                    int ny = j + dy[p];
                    if(nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
                    if(visited[nx][ny] == 0 || arr[nx][ny] || area_check[visited_area[nx][ny]]) continue;
                    arr[i][j] += visited[nx][ny];
                    area_check[visited_area[nx][ny]] = 1;
                }
            }
        }
    }

    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            printf("%d", arr[i][j]);
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