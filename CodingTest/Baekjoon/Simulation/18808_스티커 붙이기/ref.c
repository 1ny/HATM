#include <stdio.h>
#include <string.h>

int n, m, k;    // 노트북 행, 열 너비, 스티커 개수
int note[42][42];
int r, c;   // 스티커 행, 열 너비
int paper[12][12];

// paper를 90도 회전하는 함수
void rotate() {
    int tmp[12][12];
    
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            tmp[i][j] = paper[i][j];

    for (int i = 0; i < c; i++)
        for (int j = 0; j < r; j++)
            paper[i][j] = tmp[r - 1 - j][i];

    int tmp_rc = r;
    r = c;
    c = tmp_rc;
}

// note의 (x, y)에 paper의 (0, 0)이 올라가게 스티커를 붙일 수 있는지 판단하는 함수
int pastable(int x, int y) { // 노트북 위의 시작위치: x, y
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            // 이미 노트북에 붙여져 있으면 return 0
            if (note[x + i][y + j] == 1 && paper[i][j] == 1)
                return 0;
        }
    }
    
    // 붙일 수 있으면 note에 1 표시 & return 1
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (paper[i][j] == 1)
                note[x + i][y + j] = 1;
        }
    }
    return 1;
}

int main(void) {
    scanf("%d %d %d", &n, &m, &k);

    while (k--) {
        scanf("%d %d", &r, &c);
        for (int i = 0; i < r; i++)
            for (int j = 0; j < c; j++)
                scanf("%d", &paper[i][j]);  // 스티커

        for (int rot = 0; rot < 4; rot++) {
            int is_paste = 0;
            for (int x = 0; x <= n - r; x++) {
                if (is_paste) break;
                for (int y = 0; y <= m - c; y++) {
                    if (pastable(x, y)) {   // 스티커 붙였으면 회전 안함
                        is_paste = 1;
                        break;
                    }
                }
            }
            if (is_paste) break;
            rotate();
        }
    }

    int cnt = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cnt += note[i][j];
            
    printf("%d\n", cnt);
    return 0;
}
