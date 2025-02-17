#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 102

int n, m;
char arr[MAX][MAX] = {0,};
int dist[MAX][MAX] = {0,};  // 거리
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
int queue[MAX * MAX][2] = {0,};
int front = 0, rear = 0;

void push(int x, int y) {
    queue[rear][0] = x;
    queue[rear][1] = y;
    rear++;
}

void pop(int *x, int *y) {
    *x = queue[front][0];
    *y = queue[front][1];
    front++;
}

int is_empty() {
    return front == rear;
}

void bfs() {
    push(0, 0);     // (0,0) 에서 시작
    dist[0][0] = 1; // dist = 1 에서 시작
    
    while (!is_empty()) {
        int curX, curY;     // front 하나씩 꺼내기
        pop(&curX, &curY);
        
        for (int dir = 0; dir < 4; dir++) { // 상하좌우 탐색
            int nx = curX + dx[dir];
            int ny = curY + dy[dir];
            if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
            if (dist[nx][ny] > 0 || arr[nx][ny] != '1') continue;
            dist[nx][ny] = dist[curX][curY] + 1; // 거리를 하나씩 늘림.
            push(nx, ny);   // 하나씩 넣어서 탐색할 칸 추가
        }
    }
}

int main(void) {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%s", arr[i]);
    }
    
    bfs();
    
    printf("%d\n", dist[n-1][m-1]); // (N,M) 위치에서의 거리
    return 0;
}
