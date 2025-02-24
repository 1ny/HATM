#include <stdio.h>

#define N 7
#define M 10
#define STACK_SIZE 100

int board[N][M] = {
    {1,1,1,0,1,0,0,0,0,0},
    {1,0,0,0,1,0,0,0,0,0},
    {1,1,1,0,1,0,0,0,0,0},
    {1,1,0,0,1,0,0,0,0,0},
    {0,1,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0}
};

int vis[N][M] = {0}; // 방문 여부
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

// 스택 구현
int stack[STACK_SIZE][2];
int top = 0;

void push(int x, int y) {
    if (top < STACK_SIZE) {
        stack[top][0] = x;
        stack[top][1] = y;
        top++;
    }
}

void pop(int *x, int *y) {
    if (top > 0) {
        top--;
        *x = stack[top][0];
        *y = stack[top][1];
    }
}

int isEmpty() {
    return top == 0;
}

int main() {
    vis[0][0] = 1;
    push(0, 0);
    
    while (!isEmpty()) {
        int cur_x, cur_y;
        pop(&cur_x, &cur_y);
        printf("(%d, %d) -> ", cur_x, cur_y);
        
        for (int dir = 0; dir < 4; dir++) {
            int nx = cur_x + dx[dir];
            int ny = cur_y + dy[dir];
            
            if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
            if (vis[nx][ny] || board[nx][ny] != 1) continue;
            
            vis[nx][ny] = 1;
            push(nx, ny);
        }
    }
    
    return 0;
}
