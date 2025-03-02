#include <stdio.h>
#include <stdbool.h>

#define MAX 1001
#define MAX_K 21

int n, m;
char arr[MAX][MAX];
int queue[MAX*MAX][2];
int dist[MAX_K][MAX][MAX];
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
int front, rear;
int cnt;

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
    int sum = 0;
    while(!is_empty()) {
        int curX, curY;
        pop(&curX, &curY);
        for(int i=0; i<4; i++) {
            int nx = curX + dx[i];
            int ny = curY + dy[i];
            if(nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
            if(arr[nx][ny] == 'K') {
                cnt++;
                sum += dist[cnt][nx][ny];
            }
            if(dist[cnt][nx][ny] >= 0 || arr[nx][ny] == 'X') continue;
            dist[cnt][nx][ny] = dist[cnt][curX][curY] + 1;
            if(cnt == 5) return sum;
            push(nx, ny);
        }
        // for(int i=0; i<n; i++) {
        //     for(int j=0; j<m; j++) {
        //         printf("%3d ", dist[i][j]);
        //     }
        //     printf("\n");
        // }
        // printf("\n");
    }
    return -1;
}

int main() {
    memset(dist, -1, sizeof(dist));
    scanf("%d %d ", &n, &m);
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            scanf("%1c ", &arr[i][j]);
            if(arr[i][j] == 'S') {
                push(i, j);
                dist[i][j] = 0;
            }
        }
    }

    int result = bfs();

    printf("%d\n", result);

}