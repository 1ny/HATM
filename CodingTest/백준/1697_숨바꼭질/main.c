#include <stdio.h>

#define MAX 100000

int n, k; // 수빈이 위치 n, 동생 위치 k
int queue[MAX];
int front, rear;

void bfs(int n) {
    queue[rear++] = n;
    
}

int main() {
    scanf("%d %d", &n, &k);

    while(1) { // k 에 도착할 때까지
        int dir[3] = {n-1, n+1, n*2};

        for(int i=0; i<3; i++) {
            // -1, +1, *2 다 가보고 가장 가까운 곳으로 이동

        }
    }

    // printf("%d", cnt);

    return 0;
}