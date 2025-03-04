#include <stdio.h>
#include <stdbool.h>

#define MAX 201
#define MAX_K 31

int k, w, h;
int arr[MAX][MAX];
int queue[MAX*MAX*MAX_K][3];
int dist[MAX_K][MAX][MAX];
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
int dkx[8] = {2, 1, };
int dky[8] = {1, 2, -1, 1, 0, 0, 0, 0};
int front, rear;

void push(int k, int x, int y) {
    queue[rear][0] = k;
    queue[rear][1] = x;
    queue[rear++][2] = y;
}

void pop(int* k, int* x, int* y) {
    *k = queue[front][0];
    *x = queue[front][1];
    *y = queue[front++][2];
}

bool is_empty() {
    return front == rear;
}

void bfs() {
    while(!is_empty()) {
        int curK, curX, curY;
        pop(&curK, &curX, &curY);
        for(int )
    }
}

int main() {
    scanf("%d", &k);
    scanf("%d %d", &w, &h);

    for(int i=0; i<h; i++) {
        for(int j=0; j<w; j++) {
            scanf("%d", &arr[i][j]);
        }
    }


}