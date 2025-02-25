#include <stdio.h>
#include <stdbool.h>

#define MAX 1000

int n, m;
int arr[MAX][MAX];
int queue[MAX*MAX][2];
int wallQueue[MAX*MAX][2];
int dist[MAX][MAX];
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
int front, rear;
int wallCnt;

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

void bfs() {
    while(!is_empty()) {
        int curX, curY;
        pop(&curX, &curY);
        for(int i=0; i<4; i++) {
            int nx = curX + dx[i];
            int ny = curY + dy[i];
            if(nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
            if(dist[nx][ny] >= 0 || arr[nx][ny]) continue;
            dist[nx][ny] = dist[curX][curY] + 1;
            push(nx, ny);
        }
    }
}
#if 0
int main() {
    scanf("%d %d ", &n, &m);

    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            scanf("%d", &arr[i][j]);
            if(arr[i][j]) {
                wallQueue[wallCnt][0] = i;
                wallQueue[wallCnt][1] = j;
                wallCnt++;
            }
        }
        getchar();
    }

    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            dist[i][j] = -1;
        }
    }

    int min = MAX*MAX;
    for(int i=0; i<wallCnt; i++) {
        front = 0, rear = 0;
        arr[wallQueue[i][0]][wallQueue[i][1]] = 0;
#if 1
        for(int i=0; i<n; i++) {
            for(int j=0; j<n; j++) {
                printf("%d", arr[i][j]);
            }
            printf("\n");
        }
#endif
        push(0, 0);
        dist[0][0] = 1;
        bfs();
        if(dist[n][m] < min) min = dist[n][m];
        arr[wallQueue[i][0]][wallQueue[i][1]] = 1;
    }

    printf("%d", min);
}
#endif

typedef unsigned int uint32_t;

typedef struct{
	volatile uint32_t MODER;
	volatile uint32_t OTYPER;
	volatile uint32_t OSPEEDR;
	volatile uint32_t PUPDR;
	volatile uint32_t ODR;
} GPIO_ADDR_OFFSET;

#define GPIOA_BASE  0x50000000
#define GPIOA       ((GPIO_ADDR_OFFSET *)GPIOA_BASE)

int main() {
    // GPIOA->MODER = 0x50000000;  // 특정 하드웨어 레지스터에 값 설정
    printf("0x%08x\n", &GPIOA->MODER);
    printf("0x%08x\n", &GPIOA->OTYPER);
}