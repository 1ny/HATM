#include <stdio.h>
#include <string.h>

int n, m, k;
int note[42][42];
int r, c;
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
int pastable(int x, int y) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (note[x + i][y + j] == 1 && paper[i][j] == 1)
                return 0;
        }
    }
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
                scanf("%d", &paper[i][j]);

        for (int rot = 0; rot < 4; rot++) {
            int is_paste = 0;
            for (int x = 0; x <= n - r; x++) {
                if (is_paste) break;
                for (int y = 0; y <= m - c; y++) {
                    if (pastable(x, y)) {
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
