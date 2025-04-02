#include <stdio.h>
#include <stdbool.h>

#define MAX 1001

int n, m, p;
int cnt[MAX];
char arr[MAX][MAX];
int point[MAX*MAX][3];
int queue[MAX*MAX][3];
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
int dist[MAX][MAX][10];
int front, rear;
int pCnt;
int idx = 1;

void push(int x, int y, int c) {   // cnt도 같이 저장해서 하면 될듯듯
    queue[rear][0] = x;
    queue[rear][1] = y;
    queue[rear++][2] = c;
}

void push_front(int x, int y, int c) {
    queue[--front][0] = x;
    queue[front][1] = y;
    queue[front][2] = c;
}

void pop(int* x, int* y, int* c) {
    *x = queue[front][0];
    *y = queue[front][1];
    *c = queue[front++][2];
}

bool is_empty() {
    return front == rear;
}

void bfs() {
    while(!is_empty()) {
        int count = 0;
        int curX, curY, curC;
        pop(&curX, &curY, &curC);
        for(int i=0; i<4; i++) {
            int nx = curX + dx[i];
            int ny = curY + dy[i];
            if(nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
            if(arr[nx][ny] != '.') continue;
            arr[nx][ny] = arr[curX][curY];
            
            if(curC == 1 || curC == count-1) push(nx, ny, curC);
            else {
                push_front(nx, ny, curC);
                count++;
            }

            for(int i=0; i<n; i++) {
                for(int j=0; j<m; j++) {
                    printf("%c", arr[i][j]);
                }
                printf("\n");
            }    
            printf("\n");
        }
    }
}

int main() {
    scanf("%d %d %d", &n, &m, &p);
    for(int i=1; i<=p; i++) {
        scanf("%d ", &cnt[i]);
    }

    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            scanf("%1c", &arr[i][j]);

            if(arr[i][j] != '.' && arr[i][j] != '#') {
                int ref = arr[i][j] - '0';
                point[pCnt][0] = i;
                point[pCnt][1] = j;
                point[pCnt++][2] = ref;
                // point[ref][0] = i;
                // point[ref++][1] = j;
            }
        }
        getchar();
    }

    for(int i=1; i<=p; i++) {
        for(int j=0; j<pCnt; j++) {
            if(point[j][2] == i) push(point[j][0], point[j][1], cnt[i]);
        }
    }

    bfs();
}

/*
1111
1112
1122
1222

4 4 2
2 1
1111
1111
1111
1122

4 4 2
3 1
1111
1111
1111
1122

*/