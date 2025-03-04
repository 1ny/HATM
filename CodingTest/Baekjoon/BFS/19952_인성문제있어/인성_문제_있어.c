#include <stdio.h>
#include <stdbool.h>

#define MAX 1000

int t;
int h, w, o, f; // 세로 h, 가로 w, 장애물 개수 o, 초기 힘 f
int Xs, Ys, Xe, Ye; // 출발지 좌표와 목적지 좌표 x, y
int arr[MAX][MAX];
int queue[MAX*MAX][2];
int visited[MAX][MAX];
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

int bfs() {
    if(Xs == Xe && Ys == Ye) return 1;
    push(Xs, Ys);
    visited[Xs][Ys] = f;
    while(!is_empty()) {
        int curX, curY;
        pop(&curX, &curY);
        if(visited[curX][curY] == 0) continue;
        for(int i=0; i<4; i++) {
            int nx = curX + dx[i];
            int ny = curY + dy[i];
            if(nx <= 0 || nx > h || ny <= 0 || ny > w) continue;
            if(visited[nx][ny] || arr[nx][ny] - arr[curX][curY] > visited[curX][curY]) continue;
            push(nx, ny);
            visited[nx][ny] = visited[curX][curY] - 1;
            if(nx == Xe && ny == Ye) return 1;
        }
    }
    return 0;
}

int main() {
    scanf("%d", &t);

    for(int p=0; p<t; p++) {
        memset(arr, 0, sizeof(arr));
        memset(visited, 0, sizeof(visited));
        scanf("%d %d %d %d %d %d %d %d", &h, &w, &o, &f, &Xs, &Ys, &Xe, &Ye);

        for(int i=0; i<o; i++) {
            int x, y, l;
            scanf("%d %d %d", &x, &y, &l);
            arr[x][y] = l;
        }

        int result = bfs();

        // for(int i=1; i<=w; i++) {
        //     for(int j=1; j<=h; j++) {
        //         printf("%d ", visited[i][j]);
        //     }
        //     printf("\n");
        // }

        if(result) printf("잘했어!!\n");
        else printf("인성 문제있어??\n");
    }
}