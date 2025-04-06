#include <stdio.h>

int n, m, k;
int note[40][40];
int indiv[10][10];
int r, c;

void rotate() {
    int tmp[10][10];
    memcpy(tmp, indiv, sizeof(indiv));

    for(int i=0; i<c; i++) {
        for(int j=0; j<r; j++) {
            indiv[i][j] = tmp[r-j-1][i];
        }
    }

    int tmp_r = r;
    r = c;
    c = tmp_r;
}

int checkNote(int x, int y) {
    for(int i=0; i<r; i++) {
        for(int j=0; j<c; j++) {
            if(note[x+i][y+j] == 1 && indiv[i][j] == 1) return 0;   // 붙일 수 없음
        }
    }

    for(int i=0; i<r; i++) {
        for(int j=0; j<c; j++) {
            if(indiv[i][j]) note[x+i][y+j] = 1;
        }   
    }
    return 1;
}

int main() {
    scanf("%d %d %d", &n, &m, &k);
    for(int sNum=0; sNum<k; sNum++) {
        scanf("%d %d", &r, &c);
        for(int i=0; i<r; i++) {
            for(int j=0; j<c; j++) {
                scanf("%d", &indiv[i][j]);
            }
        }

        // note 왼쪽 위부터 스티커 붙일 수 있는지 판단
        for(int rot=0; rot<4; rot++) {
            int state = 0;
            for(int x=0; x<=n-r; x++) {
                for(int y=0; y<=m-c; y++) {
                    if(state) break;
                    if(checkNote(x, y))
                    {
                        state = 1;
                        break;
                    }
                }
            }
            if(state) break;
            rotate();
        }
    }

    int cnt = 0;
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            if(note[i][j]) cnt++;
        }
    }

    // for(int i=0; i<n; i++) {
    //     for(int j=0; j<m; j++) {
    //         printf("%d ", note[i][j]);
    //     }
    //     printf("\n");
    // }

    printf("%d", cnt);
}