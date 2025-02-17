#include <stdio.h>
#include <stdbool.h>

int board[502][502]; // 1이 파란 칸, 0이 빨간 칸에 대응
bool vis[502][502]; // 해당 칸을 방문했는지 여부를 저장
int n, m;
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

int bfs(int startX, int startY) {
    // BFS를 위한 큐
    int queue[250000][2];
    int front = 0, rear = 0;
    
    vis[startX][startY] = true;
    queue[rear][0] = startX;
    queue[rear++][1] = startY;
    
    int area = 0;
    
    while (front < rear) {
        area++;
        int curX = queue[front][0];
        int curY = queue[front++][1];
        
        for (int dir = 0; dir < 4; dir++) {
            int nx = curX + dx[dir];
            int ny = curY + dy[dir];
            
            if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
            if (vis[nx][ny] || board[nx][ny] != 1) continue;
            
            vis[nx][ny] = true;
            queue[rear][0] = nx;
            queue[rear++][1] = ny;
        }
    }
    
    return area;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &board[i][j]);
        }
    }
    
    int mx = 0; // 그림의 최댓값
    int num = 0; // 그림의 수
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (board[i][j] == 0 || vis[i][j]) continue;
            
            num++; // 새로운 그림 발견
            int area = bfs(i, j);
            if (area > mx) mx = area;
        }
    }
    
    printf("%d\n%d\n", num, mx);
    return 0;
}
