#include <iostream>
#include <cstring>

using namespace std;

#define MAX 20

int n;
int arr[MAX][MAX];
int arr2[MAX][MAX];

void init(){
    n = 0;
    memset(arr, 0, sizeof(arr));
    memset(arr2, 0, sizeof(arr2));
}

void rotate() {
    int tmp[MAX][MAX];
    memcpy(tmp, arr2, sizeof(tmp));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            arr2[i][j] = tmp[n - 1 - j][i];
        }
    }
}

void rotate_l() {
    int tmp[MAX][MAX];
    memcpy(tmp, arr2, sizeof(tmp));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            arr2[i][j] = tmp[j][n - i - 1];
        }
    }
}

/*
func() 위로 밀기
1. 위에서부터 연속 같은 수 2개씩 합
2. 다 위로 올리기
*/

void func() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n-1; j++) {
            for (int k = j + 1; k < n; k++) {
                if ((arr2[j][i] != 0) && (arr2[j][i] != arr2[k][i]) && (arr2[k][i] != 0)) break;
                if ((arr2[j][i] != 0) && (arr2[j][i] == arr2[k][i])) {
                    arr2[j][i] *= 2;
                    arr2[k][i] = 0;
                    j = k;
                }
            }
        }
    }

    for (int k = 0; k < n; k++) {
        for (int i = 1; i < n-k; i++) {
            for (int j = 0; j < n; j++) {
                if (arr2[i][j] && arr2[i - 1][j] == 0) {
                    arr2[i - 1][j] = arr2[i][j];
                    arr2[i][j] = 0;
                }
            }
        }
    }
}

int main() {
    int test = 1;
    while (test--) {
        init();
        //freopen("input.txt", "r", stdin);

        scanf("%d", &n);

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
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
        for (int k = 0; k < 1024; k++) {
            memcpy(arr2, arr, sizeof(arr));
            int temp = k;   // rotate 횟수
            for (int i = 0; i < 5; i++) {
                int dir = temp % 4; // 0~4
                temp /= 4;

                for (int j = 0; j < dir; j++) {
                    rotate();
                }
                func();
                for (int j = 0; j < dir; j++) {
                    rotate_l();
                }

                printf("num: %d\n", i);
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++) {
                        printf("%d ", arr2[i][j]);
                    }
                    printf("\n");
                }
                printf("\n");
            }
            if (k == 10) break;

            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (arr2[i][j] > max) max = arr2[i][j];
                }
            }
        }

        printf("%d\n", max);
    }
    return 0;
}