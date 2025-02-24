#include <stdio.h>
#include <stdbool.h>

#define MAX 1000002

int f, s, g; // 층수 f, 강호 s, 스타트링크 g
int u, d;
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

int bfs() {
    while(!is_empty()) {
        int curX;
        pop(&curX);
        int dx[2] = {u, -d};
        if(s == g) return 0;
        for(int i=0; i<2; i++) {
            int nx = curX + dx[i];
            if(nx <= 0 || nx > f) continue;
            if(dist[nx] >= 0) continue;
            dist[nx] = dist[curX] + 1;
            push(nx);
            if(nx == g) return 0;
        }
    }
    return -1;
}

int main() {
    scanf("%d %d %d %d %d", &f, &s, &g, &u, &d);

    for(int i=0; i<=f; i++) {
        dist[i] = -1;
    }

    dist[s] = 0;
    push(s);
    int result = bfs();

    if(result == -1) printf("use the stairs");
    else printf("%d", dist[g]);
}