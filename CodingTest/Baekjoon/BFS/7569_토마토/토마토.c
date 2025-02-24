#include <stdio.h>
#include <stdbool.h>

#define MAX 100

int m, n, h;
int tomato[MAX][MAX][MAX];
int queue[MAX*MAX*MAX][3];
int visited[MAX][MAX][MAX];
int dx[6] = {-1, 1, 0, 0, 0, 0};
int dy[6] = {0, 0, -1, 1, 0, 0};
int dz[6] = {0, 0, 0, 0, -1, 1};
int day[MAX][MAX][MAX];
int front, rear;
int cntZero;
int max;

void push(int x, int y, int z) {
    queue[rear][0] = z;
    queue[rear][1] = y;
    queue[rear++][2] = x;
    // visited[z][y][x]=1;
}

void pop(int* x, int* y, int* z) {
    *x = queue[front][2];
    *y = queue[front][1];
    *z = queue[front++][0];
}

bool is_empty() {
    return front == rear;
}

void bfs() {
    while(!is_empty()) {
        int curX, curY, curZ;
        pop(&curX, &curY, &curZ);
        for(int i=0; i<6; i++) {
            int nx = curX + dx[i];
            int ny = curY + dy[i];
            int nz = curZ + dz[i];
            if(nx < 0 || nx >= m || ny < 0 || ny >= n || nz < 0 || nz >= h) continue;
            if(day[nz][ny][nx] >= 0 || tomato[nz][ny][nx] == -1) continue;
            day[nz][ny][nx] = day[curZ][curY][curX] + 1;
            push(nx, ny, nz);
        }
    }
}

int main() {
    scanf("%d %d %d", &m, &n, &h);
    for(int i=0; i<h; i++) {
        for(int j=0; j<n; j++) {
            for(int k=0; k<m; k++) {
                day[i][j][k] = -1;
            }
        }
    }
    for(int i=0; i<h; i++) {
        for(int j=0; j<n; j++) {
            for(int k=0; k<m; k++) {
                scanf("%d ", &tomato[i][j][k]);
                if(tomato[i][j][k] == 1) {
                    push(k, j, i);
                    day[i][j][k] = 0;
                } else if(tomato[i][j][k] == 0) cntZero++;
            }
        }
    }

    if(cntZero == 0) {
        printf("0");
        return 0;
    }

    bfs();

    for(int i=0; i<h; i++) {
        for(int j=0; j<n; j++) {
            for(int k=0; k<m; k++) {
                if(day[i][j][k] == -1 && tomato[i][j][k] == 0) {
                    printf("-1");
                    return 0;
                }

                if(day[i][j][k] > max) max = day[i][j][k];
            }
        }
    }    

    printf("%d", max);

    return 0;
}