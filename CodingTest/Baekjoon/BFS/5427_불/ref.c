#include <stdio.h>
#include <stdbool.h>

#define MAX 1000

int r, c;
char arr[MAX][MAX] = {0,};
int queue[MAX*MAX][2] = {0,};
int fire_minite[MAX][MAX] = {0,};
int jihoon_minite[MAX][MAX] = {0,};
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
int front = 0, rear = 0;

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

void fire_bfs() {
    front = 0, rear = 0;
    for(int i=0; i<r; i++) {
        for(int j=0; j<c; j++) {
            if(arr[i][j] == 'F') {
                push(i, j);
                fire_minite[i][j] = 0;  // 불 시작점을 0으로 표시시
            }
        }
    }
    while(!is_empty()) {
        int curX, curY;
        pop(&curX, &curY);
        for(int i=0; i<4; i++) {
            int nx = curX + dx[i];
            int ny = curY + dy[i];
            if(nx < 0 || nx >= r || ny < 0 || ny >= c) continue;
            if(arr[nx][ny] == '#' || fire_minite[nx][ny] != -1) continue; 
            // fire가 0일 때, 즉 시작점이거나 이미 불이 난 칸일 때
            fire_minite[nx][ny] = fire_minite[curX][curY] + 1;
            push(nx, ny);
        }
    }
}

int jihoon_bfs() {
    front = 0, rear = 0;
    for(int i=0; i<r; i++) {
        for(int j=0; j<c; j++) {
            if(arr[i][j] == 'J') {
                push(i, j);
                jihoon_minite[i][j] = 0;    // 지훈 시작점을 0으로 표시
            }
        }
    }
    while(!is_empty()) {
        int curX, curY;
        pop(&curX, &curY);
        for(int i=0; i<4; i++) {
            int nx = curX + dx[i];
            int ny = curY + dy[i];
            if(nx < 0 || nx >= r || ny < 0 || ny >= c) {
                return jihoon_minite[curX][curY] + 1;
            }
            if(jihoon_minite[nx][ny] != -1 || arr[nx][ny] == '#') continue;
            if(fire_minite[nx][ny] != -1 && (fire_minite[nx][ny] <= jihoon_minite[curX][curY] + 1)) continue;
            // 이미 불이 난 경우
            jihoon_minite[nx][ny] = jihoon_minite[curX][curY] + 1;
            push(nx, ny);
        }
    }
    return -1;  
    // 다 돌아봤는데, 나갈 구멍 없이 탐색이 끝났을 때 -1(IMPOSSIBLE) 출력
}

int main(void) {
    scanf("%d %d\n", &r, &c);
    for(int i=0; i<r; i++) {
        for(int j=0; j<c; j++) {
            scanf("%c ", &arr[i][j]);
        }
    }

    for(int i=0; i<r; i++) {
        for(int j=0; j<c; j++) {
            fire_minite[i][j] = -1;
            jihoon_minite[i][j] = -1;
        }
    }

    fire_bfs();
    int result = jihoon_bfs();

    if(result == -1) printf("IMPOSSIBLE");
    else printf("%d", result);
}