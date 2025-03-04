#include <stdio.h>
#include <stdbool.h>
#include <string.h> // memset 추가

#define MAX_N 300
#define MAX_M 300

int n, m;
int arr[MAX_N][MAX_M];
int arrCnt[MAX_N][MAX_M];
int queue[MAX_N * MAX_M][2];
int visited[MAX_N][MAX_M];
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
int front, rear;

void push(int x, int y) {
    queue[rear][0] = x;
    queue[rear++][1] = y;
    visited[x][y] = 1;
}

void pop(int* x, int* y) {
    *x = queue[front][0];
    *y = queue[front++][1];
}

bool is_empty() {
    return front == rear;
}

void bfs() {
    while (!is_empty()) {
        int curX, curY;
        pop(&curX, &curY);
        for (int i = 0; i < 4; i++) {
            int nx = curX + dx[i];
            int ny = curY + dy[i];
            if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
            if (visited[nx][ny] || arr[nx][ny] == 0) continue;
            push(nx, ny);
        }
    }
}

int main() {
    int year = 0;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &arr[i][j]);
        }
    }

    while (1) {
        int area = 0;
        memset(visited, 0, sizeof(visited)); // 방문 배열 초기화

        // 각 위치에서 녹을 빙산의 양 계산
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (arr[i][j] == 0) {
                    arrCnt[i][j] = 0;
                    continue;
                }

                int cnt = 0;
                for (int p = 0; p < 4; p++) {
                    int nx = i + dx[p];
                    int ny = j + dy[p];
                    if (nx >= 0 && nx < n && ny >= 0 && ny < m && arr[nx][ny] == 0) {
                        cnt++;
                    }
                }
                arrCnt[i][j] = cnt;
            }
        }

        // 빙산 녹이기
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                arr[i][j] -= arrCnt[i][j];
                if (arr[i][j] < 0) arr[i][j] = 0;
            }
        }

        // 빙산 개수 세기
        front = rear = 0; // 큐 초기화
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (!visited[i][j] && arr[i][j] > 0) {
                    push(i, j);
                    bfs();
                    area++;
                }
            }
        }

        // 빙산이 두 덩어리 이상이면 종료
        if (area >= 2) {
            printf("%d\n", year);
            return 0;
        }

        // 빙산이 모두 녹으면 종료
        if (area == 0) {
            printf("0\n");
            return 0;
        }

        year++;
    }
}
