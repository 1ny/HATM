#include <stdio.h>
#include <stdbool.h>

#define MAX 1001

int t;
int w, h;
char arr[MAX][MAX];
int queue[MAX*MAX][2];
int fire[MAX][MAX];
int cnt_sanguen[MAX][MAX];
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

int bfs_sanguen() {
    front = 0, rear= 0 ;
    for(int j=0; j<w; j++) {
        for(int k=0; k<h; k++) {
            if(arr[j][k] == '@') {
                push(j, k);
                cnt_sanguen[j][k] = 0;
            }
        }
    }

    while(!is_empty()) {
        int curX, curY;
        pop(&curX, &curY);
        for(int i=0; i<4; i++) {
            int nx = curX + dx[i];
            int ny = curY + dy[i];
            if(nx < 0 || nx >= w || ny < 0 || ny >= h) return cnt_sanguen[curX][curY] + 1;
            if(arr[nx][ny] == '#' || cnt_sanguen[nx][ny] >= 0) continue;
            if(fire[nx][ny] >= 0 && cnt_sanguen[curX][curY] + 1 >= fire[nx][ny]) continue;
            cnt_sanguen[nx][ny] = cnt_sanguen[curX][curY] + 1;           
            push(nx, ny);
            // printf("sanguen[%d][%d]\n", nx, ny);
        }
    }
    return -1;
}

void bfs_fire() {
    front = 0, rear= 0;
    for(int j=0; j<w; j++) {
        for(int k=0; k<h; k++) {
            if(arr[j][k] == '*') {
                push(j, k);
                fire[j][k] = 0;
            }
        }
    }

    while(!is_empty()) {
        int curX, curY;
        pop(&curX, &curY);
        for(int i=0; i<4; i++) {
            int nx = curX + dx[i];
            int ny = curY + dy[i];
            if(nx < 0 || nx >= w || ny < 0 || ny >= h) continue;
            if(arr[nx][ny] == '#' || fire[nx][ny] >= 0) continue;
            fire[nx][ny] = fire[curX][curY] + 1;
            push(nx, ny);
            // printf("fire[%d][%d]\n", nx, ny);
        }
    }
}

int main() {
    scanf("%d ", &t);
    for(int i=0; i<t; i++) {
        scanf("%d %d ", &w, &h);
        
        for(int j=0; j<h; j++) {
            for(int k=0; k<w; k++) {
                scanf("%c ", &arr[k][j]);
            }
        }

        // for(int j=0; j<h; j++) {
        //     for(int k=0; k<w; k++) {
        //         printf("%c ", arr[j][k]);
        //     }
        //     printf("\n");
        // }

        for(int j=0; j<h; j++) {
            for(int k=0; k<w; k++) {
                cnt_sanguen[k][j] = -1;
                fire[k][j] = -1;
            }
        }
        
        bfs_fire();
        int result = bfs_sanguen();

        if(result == -1) printf("IMPOSSIBLE\n");
        else printf("%d\n", result);
    }
}