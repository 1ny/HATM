#include <stdio.h>

#define MAX 8

int n, m;
int board1[MAX][MAX];
int board2[MAX][MAX];
int dx[4] = {0, -1, 0, 1};
int dy[4] = {1, 0, -1, 0};
int cctv[8][2];
int cntCCTV;

void check(int x, int y, int dir) {
    dir %= 4; // 나머지 값을 뽑아야됨
    while(1) {
        x += dx[dir];
        y += dy[dir];
        if(x < 0 || x >= n || y < 0 || y >= m || board2[x][y] == 6) return;
        // 6은 벽이니까 움직일 수 없어!
        if(board2[x][y] != 0) continue; // 0이어야 해. 즉, 빈칸이어야 해!
        board2[x][y] = 7; // 감시했음을 표시
    }
}

int main() {
    int minZ = 0;

    scanf("%d %d", &n, &m);
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            scanf("%d", &board1[i][j]);

            if(board1[i][j] == 0) minZ++;
            else if(board1[i][j] <= 5) {
                cctv[cntCCTV][0] = i;
                cctv[cntCCTV][1] = j;
                cntCCTV++;
            }
        }
    }

    for(int myCase=0; myCase<(1<<(2 * cntCCTV)); myCase++) { // 4의 지수승을 나타내기 위해 쉬프트연산
        memcpy(board2, board1, sizeof(board1));
        int tmp = myCase;
        
        for(int i=0; i<cntCCTV; i++) {
            int dir = tmp % 4;  // 4로 나눈 나머지값 0 0 0 (cctv 개수만큼) 1 0 0 | 2 0 0 | 3 0 0 | 0 1 0
            tmp /= 4;           // 4로 나누자       0 0 0 (cctv 개수만큼) 0 0 0 | 0 0 0 | 0 0 0 | 1 0 0
            int x = cctv[i][0];
            int y = cctv[i][1];
            // printf("dir=%d tmp=%d\n", dir, tmp);
            
            if(board1[x][y] == 1) { // 한 방향
                check(x, y, dir);
            } else if(board1[x][y] == 2) { // 마주보는 두 방향
                check(x, y, dir);
                check(x, y, dir+2); // 더해도 상관없는 이유: check 함수에서 다시 모듈러 연산함!
            } else if(board1[x][y] == 3) { // 인접한 두 방향
                check(x, y, dir);
                check(x, y, dir+1);
            } else if(board1[x][y] == 4) { // 세 방향
                check(x, y, dir);
                check(x, y, dir+1);
                check(x, y, dir+2);
            } else if(board1[x][y] == 5) { // 모든 방향
                check(x, y, dir);
                check(x, y, dir+1);
                check(x, y, dir+2);
                check(x, y, dir+3);
            }
        }

        int comp = 0;
        for(int i=0; i<n; i++) {
            for(int j=0; j<m; j++) {
                if(board2[i][j] == 0) comp++;
            }
        }

        if(comp < minZ) minZ = comp;
    }

    printf("%d", minZ);
}