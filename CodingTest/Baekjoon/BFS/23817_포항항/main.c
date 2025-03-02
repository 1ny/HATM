#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX_N 1000
#define MAX_CNT 21
#define INF 1000000000

int n, m, cnt, dist[MAX_CNT][MAX_CNT];
int pos[MAX_CNT][2];
char board[MAX_N][MAX_N + 1];
int visited[MAX_N][MAX_N];
int queue[MAX_N * MAX_N][2];
int front, rear;

void enqueue(int x, int y) {
    queue[rear][0] = x;
    queue[rear][1] = y;
    rear++;
}

void dequeue(int *x, int *y) {
    *x = queue[front][0];
    *y = queue[front][1];
    front++;
}

int is_empty() {
    return front == rear;
}

void BFS(int st) {
    memset(visited, 0, sizeof(visited));
    front = rear = 0;
    enqueue(pos[st][0], pos[st][1]);
    visited[pos[st][0]][pos[st][1]] = 1;
    
    for (int d = 0; !is_empty(); d++) {
        int size = rear - front;
        for (int i = 0; i < size; i++) {
            int x, y;
            dequeue(&x, &y);
            
            if (board[x][y] < 20) dist[st][board[x][y]] = d;
            
            for (int j = 0; j < 4; j++) {
                int nx = x + "1012"[j] - '1';
                int ny = y + "2101"[j] - '1';
                
                if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
                if (board[nx][ny] == 'X' || visited[nx][ny]) continue;
                
                enqueue(nx, ny);
                visited[nx][ny] = 1;
            }
        }
    }
}

int DFS(int cur, int state) {
    if (__builtin_popcount(state) == 5) return 0;
    int ret = INF;
    
    for (int nxt = 1; nxt <= cnt; nxt++) {
        if ((state & (1 << nxt)) || dist[cur][nxt] == -1) continue;
        
        int new_state = state | (1 << nxt);
        int temp = DFS(nxt, new_state) + dist[cur][nxt];
        if (temp < ret) ret = temp;
    }
    return ret;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%s", board[i]);
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (board[i][j] == 'S') {
                board[i][j] = 0;
                pos[0][0] = i;
                pos[0][1] = j;
            } else if (board[i][j] == 'K') {
                board[i][j] = ++cnt;
                pos[cnt][0] = i;
                pos[cnt][1] = j;
            }
        }
    }
    
    memset(dist, -1, sizeof(dist));
    for (int i = 0; i <= cnt; i++) BFS(i);
    
    int res = DFS(0, 1);
    if (res == INF) res = -1;
    printf("%d\n", res);
    
    return 0;
}
