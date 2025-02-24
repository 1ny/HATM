#include <stdio.h>
#include <stdbool.h>

#define MAX 301

int t, l; // 테스트케이스 개수 t, 체스판 한 변의 길이 l
int queue[MAX*MAX][2];
int dx[8] = {2, -2, 2, -2, 1, -1, 1, -1};
int dy[8] = {1, 1, -1, -1, 2, 2, -2, -2};
int cnt[MAX][MAX];
int front, rear;
int startX, startY;
int endX, endY;

void push(int x, int y) {
    queue[rear][0] = x;
    queue[rear++][1] = y;
    // visited[y][x] = 1;
}

void pop(int* x, int* y) {
    *x = queue[front][0];
    *y = queue[front++][1];
}

bool is_empty() {
    return front == rear;
}

void bfs() {
    while(!is_empty()) {
        int curX, curY;
        pop(&curX, &curY);
        for(int i=0; i<8; i++) {
            int nx = curX + dx[i];
            int ny = curY + dy[i];
            if(nx < 0 || nx >= l || ny < 0 || ny >= l) continue;
            if(cnt[nx][ny] >= 0) continue;
            cnt[nx][ny] = cnt[curX][curY] + 1;
            if(nx == endX && ny == endY) return;
            push(nx, ny);
        }
    }
}

int main() {
    scanf("%d", &t);
    for(int i=0; i<t; i++) {
        front = 0, rear = 0;
        scanf("%d ", &l);
        scanf("%d %d ", &startX, &startY);
        scanf("%d %d", &endX, &endY);

        for(int j=0; j<l; j++) {
            for(int k=0; k<l; k++) {
                cnt[j][k] = -1;
            }
        }

        cnt[startX][startY] = 0;
        push(startX, startY);
        bfs();
        
        // printf("t: %d\nl: %d\nstart: %d %d\nend: %d %d\n", t, l, startX, startY, endX, endY);
        printf("%d\n", cnt[endX][endY]);
    }

}