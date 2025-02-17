#include <stdio.h>
#include <stdbool.h>

#define MAX 500

int n, m;
int arr[MAX][MAX] = {0,};
int visited[MAX][MAX] = {0,};
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
int queue[MAX*MAX][2] = {0,};
int front=0, rear=0;

void push(int x, int y) {
    visited[x][y] = true;   // 방문 표시
    queue[rear][0] = x;     // 상하좌우 탐색의 기준 좌표 push in queue
    queue[rear++][1] = y;
}

void pop(int* x, int* y) {
    *x = queue[front][0];
    *y = queue[front++][1];
}

bool is_empty() {
    return (front == rear);
}

int bfs(int x, int y) {
    int area = 0;
    push(x, y);

    while(!is_empty()) {   // queue가 empty인지 확인
        area++;
        int curX, curY;
        pop(&curX, &curY);

        for(int dir=0; dir<4; dir++) {
            // 상하좌우 탐색
            int nx = curX + dx[dir];
            int ny = curY + dy[dir];
            // 범위를 나가면 다음 루프로 넘어감.
            // 방문했거나 0이면 넘어감.
            if(nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
            if(visited[nx][ny] || arr[nx][ny] == 0) continue;

            push(nx, ny);
        }
    }

    return area;
}

int main(void) {
    scanf("%d %d", &n, &m);
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            scanf("%d", &arr[i][j]);
        }
    }

    int mx = 0;  // 가장 넓은 그림의 넓이 
    int num = 0; // 그림의 개수

    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            // 0 이거나 방문했으면 다음 루프로 넘어간다.
            if(arr[i][j] == 0 || visited[i][j]) continue;

            num++;
            int area = bfs(i, j);
            if(area > mx) mx = area;
        }
    }

    printf("%d\n%d\n", num, mx);

    return 0;
}