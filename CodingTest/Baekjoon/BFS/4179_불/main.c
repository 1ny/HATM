#include <stdio.h>
#include <stdbool.h>

#define MAX 1000

int r, c;
char arr[MAX][MAX];
int queue[MAX*MAX][2];
int fire_minite[MAX][MAX];
int jihoon_minite[MAX][MAX];
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
int front, rear;

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
    front = 0, rear = 0;  // 큐 초기화
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (arr[i][j] == 'F') {
                push(i, j);
                fire_minite[i][j] = 0;
            }
        }
    }

    while (!is_empty()) {
        int curX, curY;
        pop(&curX, &curY);
        for (int i = 0; i < 4; i++) {
            int nx = curX + dx[i];
            int ny = curY + dy[i];

            if (nx < 0 || nx >= r || ny < 0 || ny >= c) continue;
            if (arr[nx][ny] == '#' || fire_minite[nx][ny] != -1) continue;

            fire_minite[nx][ny] = fire_minite[curX][curY] + 1;
            push(nx, ny);
        }
    }
}

int jihoon_bfs() {
    front = 0, rear = 0;  // 큐 초기화
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (arr[i][j] == 'J') {
                push(i, j);
                jihoon_minite[i][j] = 0;
            }
        }
    }

    while (!is_empty()) {
        int curX, curY;
        pop(&curX, &curY);
        for (int i = 0; i < 4; i++) {
            int nx = curX + dx[i];
            int ny = curY + dy[i];

            // 탈출 가능하면 즉시 반환
            if (nx < 0 || nx >= r || ny < 0 || ny >= c) {
                return jihoon_minite[curX][curY] + 1;
            }
            if (jihoon_minite[nx][ny] != -1 || arr[nx][ny] == '#') continue;

            // 불이 먼저 도착하지 않도록 확인
            if (fire_minite[nx][ny] != -1 && fire_minite[nx][ny] <= jihoon_minite[curX][curY] + 1) continue;

            jihoon_minite[nx][ny] = jihoon_minite[curX][curY] + 1;
            push(nx, ny);
        }
    }
    return -1;  
}

int main(void) {
    scanf("%d %d", &r, &c);
    getchar();  // 개행 문자 제거

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            scanf(" %c", &arr[i][j]);
        }
    }

    // 거리 배열 초기화
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            fire_minite[i][j] = -1;
            jihoon_minite[i][j] = -1;
        }
    }

    fire_bfs();
    int result = jihoon_bfs();

    if (result == -1) 
        printf("IMPOSSIBLE\n");
    else 
        printf("%d\n", result);

    return 0;
}
