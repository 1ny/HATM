#include <stdio.h>
#include <stdbool.h>

#define MAX  1000

int n;
int arr[MAX][MAX];
int stack[MAX*MAX][2];
int visited[MAX][MAX];
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
int top;
int cnt;
int homeCnt[MAX];

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

int dfs() {
    int area = 1;
    while(!is_empty()) {
        int curX, curY;
        pop(&curX, &curY);
        for(int i=0; i<4; i++) {
            int nx = curX + dx[i];
            int ny = curY + dy[i];
            if(nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
            if(visited[nx][ny] || !arr[nx][ny]) continue;
            push(nx, ny);
            area++;
        }
    }

    return area;
}

int main() {
    scanf("%d", &n);

    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            scanf("%1d", &arr[i][j]);
        }
    }

    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            if(visited[i][j] || !arr[i][j]) continue;
            push(i, j);
            homeCnt[cnt] = dfs(i, j);
            cnt++;
        }
    }

    printf("%d\n", cnt);

    for(int i=0; i<cnt; i++) {
        for(int j=i+1; j<cnt; j++) {
            if(homeCnt[i] > homeCnt[j]) {
                int temp = homeCnt[i];
                homeCnt[i] = homeCnt[j];
                homeCnt[j] = temp;
            }
        }
    }

    for(int i=0; i<cnt; i++) {
        printf("%d\n", homeCnt[i]);
    }
}