#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX 251

// 부분행렬의 최댓값과 최솟값의 차이를 묻는 질문
int n, b, k;    // 행렬너비 n, 부분행렬너비 b, 질문 개수 k
int arr[MAX][MAX];
int dp[MAX][MAX][2];    // max, min을 저장할 배열열

int main() {
    scanf("%d %d %d", &n, &b, &k);
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=n; j++) {
            scanf("%d", &arr[i][j]);
        }
    }

    for(int i=1; i<=n-b+1; i++) {
        for(int j=1; j<=n; j++) {
            dp[i][j][0] = 0, dp[i][j][1] = 250;

            for(int q=0; q<b; q++) {
                if(arr[i+q][j] > dp[i][j][0]) dp[i][j][0] = arr[i+q][j];
                if(arr[i+q][j] < dp[i][j][1]) dp[i][j][1] = arr[i+q][j];
            }
        }
    }

    for(int i=1; i<=n-b+1; i++) {
        for(int j=1; j<=n-b+1; j++) {
            for(int q=0; q<b; q++) {
                if(dp[i][j+q][0] > dp[i][j][0]) dp[i][j][0] = dp[i][j+q][0];
                if(dp[i][j+q][1] < dp[i][j][1]) dp[i][j][1] = dp[i][j+q][1];
            }
        }
    }

    // for(int i=1; i<=n; i++) {
    //     for(int j=1; j<=n; j++) {
    //         printf("%d ", dp[i][j][0]);
    //     }
    //     printf("\n");
    // }
    // printf("\n");

    // for(int i=1; i<=n; i++) {
    //     for(int j=1; j<=n; j++) {
    //         printf("%d ", dp[i][j][1]);
    //     }
    //     printf("\n");
    // }
    // printf("\n");

    for(int i=0; i<k; i++) {
        int x, y;   // 부분행렬의 가장 위쪽 행 번호 i, 열 번호 j
        scanf("%d %d", &x, &y); 

        printf("%d\n", dp[x][y][0] - dp[x][y][1]);
    }
}