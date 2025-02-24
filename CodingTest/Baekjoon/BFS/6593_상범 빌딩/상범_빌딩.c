#include <stdio.h>
#include <stdbool.h>

#define MAX 31

int l, r, c; // 층수 l, 행과 열 r, c
char arr[MAX][MAX][MAX];
int queue[MAX*MAX*MAX][3];
int dist[MAX][MAX][MAX];
int dx[6] = {-1, 1, 0, 0, 0, 0};
int dy[6] = {0, 0, -1, 1, 0, 0};
int dz[6] = {0, 0, 0, 0, -1, 1};
int front, rear;

void push(int x, int y, int z) {
    queue[rear][0] = z;
    queue[rear][1] = y;
    queue[rear++][2] = x;
}

void pop(int* x, int* y, int* z) {
    *x = queue[front][2];
    *y = queue[front][1];
    *z = queue[front++][0];
}

bool is_empty() {
    return front == rear;
}

int bfs() {
    while(!is_empty()) {
        int curX, curY, curZ;
        pop(&curX, &curY, &curZ);
        for(int i=0; i<6; i++) {
            int nx = curX + dx[i];
            int ny = curY + dy[i];
            int nz = curZ + dz[i];
            if(nx < 0 || nx >= c || ny < 0 || ny >= r || nz < 0 || nz >= l) continue;
            if(dist[nz][ny][nx] >= 0|| arr[nz][ny][nx] == '#') continue;
            dist[nz][ny][nx] = dist[curZ][curY][curX] + 1;
            if(arr[nz][ny][nx] == 'E') return dist[nz][ny][nx];
            push(nx, ny, nz);
        }
    }
    return -1;
}

int main() {
    while(1) {
        scanf("%d %d %d ", &l, &r, &c);
        if(l == 0) break;

        front = 0, rear = 0;
        for(int i=0; i<l; i++) {
            for(int j=0; j<r; j++) {
                for(int k=0; k<c; k++) {
                    dist[i][j][k] = -1;
                }
            }
        }

        for(int i=0; i<l; i++) {
            for(int j=0; j<r; j++) {
                for(int k=0; k<c; k++) {
                    scanf("%c", &arr[i][j][k]);
                    if(arr[i][j][k] == 'S') {
                        push(k, j, i);
                        dist[i][j][k] = 0;
                    }
                }
                getchar();
            }
            getchar();
        }

        int result = bfs();

        if(result == -1) printf("Trapped!\n");
        else printf("Escaped in %d minute(s).\n", result);
    }
}