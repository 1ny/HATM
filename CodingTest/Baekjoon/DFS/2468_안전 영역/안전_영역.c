#include <stdio.h>
#include <stdbool.h>

#define MAX 102

int n; // 행과 열 길이
int arr[MAX][MAX];
int stack[MAX*MAX][2];
int visited[MAX][MAX];
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
int top;
int cnt;

void push(int x, int y) {
    stack[top][0] = x;
    stack[top++][1] = y;
    visited[x][y] = 1;
}

void pop(int* x, int* y) {
    *x = stack[--top][0];
    *y = stack[top][1];
}

bool is_empty() {
    return top == 0;
}

void dfs(int height) {
    while(!is_empty()) {
        int curX, curY;
        pop(&curX, &curY);
        for(int i=0; i<4; i++) {
            int nx = curX + dx[i];
            int ny = curY + dy[i];
            if(nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
            if(visited[nx][ny] || arr[nx][ny] <= height) continue;
            push(nx, ny);
        }
    }
}

int main() {
    int max = 0;
    scanf("%d", &n);

    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            scanf("%d", &arr[i][j]);
            if(arr[i][j] > max) max = arr[i][j];
        }
    }

    int maxCnt = 0;
    for(int i=0; i<=max; i++) {
        cnt = 0;
        for(int j=0; j<n; j++) {
            for(int k=0; k<n; k++) {
                visited[j][k] = 0;
            }
        }
        for(int j=0; j<n; j++) {
            for(int k=0; k<n; k++) {
                if(visited[j][k] || arr[j][k] <= i) continue;
                push(j, k);
                dfs(i);
                cnt++;
            }
        }
        // printf("cnt: %d\n", cnt);
        if(cnt > maxCnt) maxCnt = cnt; 
    }

    printf("%d", maxCnt);
}