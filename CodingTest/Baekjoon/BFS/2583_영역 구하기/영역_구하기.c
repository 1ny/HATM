#include <stdio.h>
#include <stdbool.h>

#define MAX 100

int m, n, k; // 가로길이 m, 세로길이 n, 직사각형 개수 k
int arr[MAX][MAX];
int queue[MAX*MAX][2];
int visited[MAX][MAX];
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
int front, rear;
int cnt;
int area[MAX];

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

int bfs() {
    cnt++;
    int area = 1;
    while(!is_empty()) {
        int curX, curY;
        pop(&curX, &curY);
        for(int i=0; i<4; i++) {
            int nx = curX + dx[i];
            int ny = curY + dy[i];
            if(nx < 0 || nx >= m || ny < 0 || ny >= n) continue;
            if(visited[nx][ny] || arr[nx][ny]) continue;
            push(nx, ny);
            area++;
        }
    }
    return area;
}

int main() {
    scanf("%d %d %d", &m, &n, &k);
    for(int i=0; i<k; i++) {
        int leftX, leftY, rightX, rightY;
        scanf("%d %d %d %d", &leftX, &leftY, &rightX, &rightY);
        for(int j=0; j<rightY-leftY; j++) {
            for(int p=0; p<rightX-leftX; p++) {
                arr[leftY+j][leftX+p] = 1;
            }
        }
    }

    // for(int i=0; i<m; i++) {
    //     for(int j=0; j<n; j++) {
    //         printf("%d ", arr[i][j]);
    //     }
    //     printf("\n");
    // }

    for(int i=0; i<m; i++) {
        for(int j=0; j<n; j++) {
            front = 0, rear = 0;
            if(arr[i][j] == 1 || visited[i][j]) continue;
            push(i,j);
            area[cnt] = bfs();
        }
    }

    for(int i=0; i<cnt; i++) {  
        for(int j=i+1; j<cnt; j++) {
            if(area[i] > area[j]) {
                int temp = area[i];
                area[i] = area[j];
                area[j] = temp;
            }
        }
    }

    printf("%d\n", cnt);
    for(int i=0; i<cnt; i++) {
        printf("%d ", area[i]);
    }


    return 0;
}