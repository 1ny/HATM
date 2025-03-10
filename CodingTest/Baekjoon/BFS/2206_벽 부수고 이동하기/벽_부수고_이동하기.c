#include <stdio.h>
#include <stdbool.h>

#define MAX 1000

int n, m;
int arr[MAX][MAX];
int queue[MAX*MAX][2];
int dist[MAX][MAX];
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
int front, rear;
int wallCnt;
int wall[MAX*MAX][2];

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
    front = 0, rear = 0;
    push(0, 0);
    dist[0][0] = 1;

    while(!is_empty()) {
        int curX, curY;
        pop(&curX, &curY);

        if(curX == n-1 && curY == m-1) return dist[curX][curY];
        
        for(int i=0; i<4; i++) {
            int nx = curX + dx[i];
            int ny = curY + dy[i];
            
            if(nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
            if(dist[nx][ny] != -1 || arr[nx][ny]) continue;
            
            dist[nx][ny] = dist[curX][curY] + 1;
            push(nx, ny);
        }
    }
    return -1;
}

int main() {
    scanf("%d %d", &n, &m);
    
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            scanf("%1d", &arr[i][j]);
            dist[i][j] = -1;
            if(arr[i][j] == 1) {
                wall[wallCnt][0] = i;
                wall[wallCnt][1] = j;
                wallCnt++;
            }
        }
    }

    int origin = bfs();

    int min = MAX*MAX;
    int flag = 1;
    for(int i=0; i<wallCnt; i++) {
        int x = wall[i][0];
        int y = wall[i][1];
        arr[x][y] = 0;

        for(int k=0; k<n; k++) {
            for(int p=0; p<m; p++) {
                dist[k][p] = -1;
            }
        }

        int result = bfs();
        arr[x][y] = 1;
        if(result != -1 && result < min) min = result;

        if(result != -1) flag = 0;
    }

    if(origin != -1 && origin < min) min = origin;

    if(origin == -1 && flag) printf("-1");
    else printf("%d", min);
}