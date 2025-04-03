#include <stdio.h>

int n, m, k;
int note[40][40];
int indiv[10][10];
int r, c;

int checkNote(int x, int y) {
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            if(note[x+i][y+j] == 1 && indiv[i][j] == 1) return 0;   // 붙일 수 없음
        }
    }

    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
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
        for(int i=0; i<n; i++) {
            for(int j=0; j<m; j++) {
                checkNote(i, j);
            }
        }
    }
}