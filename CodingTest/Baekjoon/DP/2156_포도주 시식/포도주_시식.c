#include <stdio.h>

#define MAX 10001
#define max(x, y) ((x>y) ? x : y)

int n; 
int arr[MAX];
int dp[MAX][2];

int main() {
    int result = 0;

    scanf("%d", &n);
    for(int i=1; i<=n; i++) {
        scanf("%d", &arr[i]);
    }

    if(n == 1) {
        printf("%d", arr[1]);
        return 0;
    }

    dp[1][0] = dp[1][1] = arr[1];
    dp[2][0] = arr[2];
    dp[2][1] = dp[1][0] + arr[2];
    for(int i=3; i<=n; i++) {
        dp[i][0] = max(dp[i-2][0], dp[i-2][1]);
        dp[i][0] = max(dp[i-3][0], dp[i][0]);
        dp[i][0] = max(dp[i-3][1], dp[i][0]) + arr[i];
        dp[i][1] = dp[i-1][0] + arr[i];
    }

    for(int i=1; i<=n; i++) {
        for(int j=0; j<2; j++) {
            if(dp[i][j] > result) result = dp[i][j];
        }
    }

    printf("%d", result);

    // for(int i=1; i<=n; i++) {
    //     printf("%3d", dp[i][0]);
    // }

    // printf("\n");
    // for(int i=1; i<=n; i++) {
    //     printf("%3d", dp[i][1]);
    // }
}

/*
    1       2       3                     4                    5       6
    6       10      13                    9                    8       1

[1] 6       10      [1][1]+13 / [1][2]+13 [2][2]+9 / [2][1]+9
[2]         [1]+10  [2][1]+13   [3][1]+9

*/