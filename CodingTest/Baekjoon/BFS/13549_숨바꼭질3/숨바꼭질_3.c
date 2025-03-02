#include <stdio.h>
#include <stdbool.h>

#define MAX 100002

int n, k;
int arr[MAX];
int queue[MAX];
int dist[MAX];
int front, rear;

void push(int x) {
    queue[rear++] = x;
}

void pop(int* x) {
    *x = queue[front++];
}

bool is_empty() {
    return front == rear;
}

void bfs() {
    while(!is_empty()) {
        int curX;
        pop(&curX);
        if(curX == k) return ;
        int dx[3] = {curX-1, curX+1, curX*2};
        for(int i=0; i<3; i++) {
            int nx = dx[i];
            if(nx < 0 || nx >= MAX) continue;
            if((dist[nx] != -1 && i != 2 && dist[curX] + 1 >= dist[nx]) 
                    || (dist[nx] != -1 && i == 2 && dist[curX] >= dist[nx])) continue;
            if(i != 2) dist[nx] = dist[curX] + 1;
            else dist[nx] = dist[curX];
            push(nx);
        }
    }
}

int main() {
    scanf("%d %d", &n, &k);
    memset(dist, -1, sizeof(dist));

    dist[n] = 0;
    push(n);
    bfs();
    printf("%d", dist[k]);
}