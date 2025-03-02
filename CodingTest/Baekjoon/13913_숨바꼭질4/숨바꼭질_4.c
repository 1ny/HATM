#include <stdio.h>
#include <stdbool.h>

#define MAX 100001

int n, k;
int queue[MAX];
int dist[MAX];
int linked[MAX];
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
    push(n);
    dist[n] = 1;
    linked[n] = n;
    while(!is_empty()) {
        int curX;
        pop(&curX);
        int dx[3] = {curX+1, curX-1, curX*2};
        for(int i=0; i<3; i++) {
            int nx = dx[i];
            if(nx < 0 || nx >= MAX) continue;
            if(dist[nx]) continue;
            dist[nx] = dist[curX] + 1;
            linked[nx] = curX;
            push(nx);
        }
    }
}

int main() {
    scanf("%d %d", &n, &k);
    memset(dist, 0, sizeof(dist));
    bfs();

    printf("%d\n", dist[k]-1);

    int p = k;
    int result[MAX];
    int idx = 0;
    while (p != n) {
        result[idx++] = p;
        p = linked[p];
    }

    printf("%d ", n);
    for(int i=1; i<=idx; i++) {
        printf("%d ", result[idx-i]);
    }
    
}