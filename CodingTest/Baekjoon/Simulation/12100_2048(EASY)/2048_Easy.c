#include <stdio.h>

#define MAX 20

int n;
int arr[MAX][MAX];
int ref[MAX][MAX];

void rotate() {
    int tmp[MAX][MAX];
    memcpy(tmp, ref, sizeof(tmp));

    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            ref[i][j] = tmp[n-1-j][i];
        }
    }
}

void rotate_l() {
    int tmp[MAX][MAX];
    memcpy(tmp, ref, sizeof(tmp));

    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            ref[i][j] = tmp[j][n-i-1];
        }
    }
}

/*
func() 위로 밀기
1. 위에서부터 연속 같은 수 2개씩 합
2. 다 위로 올리기
*/

void func() {
    for(int i=0; i<n; i++) {
        for(int j=0; j<n-1; j++) {
            if(ref[j][i] != 0 && ref[j][i] == ref[j+1][i]) {
                ref[j][i] *= 2;
                ref[j+1][i] = 0;
            }
        }
    }

    for(int k=0; k<n; k++) {
        for(int i=1; i<n-k; i++) {
            for(int j=0; j<n; j++) {
                if(ref[i][j] && ref[i-1][j] == 0) {
                    ref[i-1][j] = ref[i][j];
                    ref[i][j] = 0;
                }
            }
        }
    }
}

int main() {
    scanf("%d", &n);

    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            scanf("%d", &arr[i][j]);

    //4^5 * 400 = 2^10 * 400

    /*
    for(a,b,c,d,e 0~4)
    상 - origin
    우 - rotate_l -> rotate_r
    하 - rotate_l*2 -> rotate_r*2
    좌 - rotate_r - > rotate_l
    func();

    for(i,j 0~n)
    max = ?
    */

    int max = 0;
    for(int k=0; k<1024; k++) {
        memcpy(ref, arr, sizeof(arr));
        int temp = k;   // rotate 횟수
        for(int i=0; i<5; i++) {
            int dir = temp % 4; // 0~4
            temp /= 4;

            for(int j=0; j<dir; j++) {
                rotate();
            }
            func();
        }

        for(int i=0; i<n; i++) {
            for(int j=0; j<n; j++) {
                if(ref[i][j] > max) max = ref[i][j];
            }
        }
    }

    printf("%d", max);
}

/*
0 0 0 2
0 0 0 2
0 0 4 2
0 2 0 2

0 0 0 2
0 0 0 2
0 0 4 2
0 0 0 4

0 0 4 4
0 0 0 2
0 0 0 4
0 0 0 0

0 0 0 8
0 0 0 2
0 0 0 4
0 0 0 0


0 2 4 4
0 0 0 4
0 0 0 0
0 0 0 0
*/