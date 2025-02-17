#include <stdio.h>

#define MAX 100

int n, m;
int arr[MAX][MAX] = {0,};
int queue[MAX * MAX][2] = {0,};
int visited[MAX][MAX] = {0,};
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
int front = 0, rear = 0;

int bfs(int x, int y) {
    int cnt = 0;
    
}

int main() {
    int min = 10000;
    scanf("%d %d", &n, &m);
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            scanf("%d", &arr[i][j]);
        }
    }

    printf("%d", min);
    return 0;
}