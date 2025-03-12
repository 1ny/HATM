#include <stdio.h>

#define MAX 100001
#define max(x ,y) ((x>y) ? x : y)

int t, n;
int arr[3][MAX];
int dp[3][MAX];

int main() {
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        for(int i=1; i<=2; i++) {
            for(int j=1; j<=n; j++) {
                scanf("%d", &arr[i][j]);
            }
        }
    
        dp[1][1] = arr[1][1];
        dp[2][1] = arr[2][1];
        int result = max(dp[1][1], dp[2][1]);
        for(int i=2; i<=n; i++) {
            dp[1][i] = max(dp[1][i-2], dp[2][i-2]);
            dp[1][i] = max(dp[2][i-1], dp[1][i]) + arr[1][i];
            dp[2][i] = max(dp[1][i-2], dp[2][i-2]);
            dp[2][i] = max(dp[1][i-1], dp[2][i]) + arr[2][i];

            if(dp[1][i] > result) result = dp[1][i];
            if(dp[2][i] > result) result = dp[2][i];
        }

        printf("%d\n", result);
        // for(int i=1; i<=2; i++) {
        //     for(int j=1; j<=n; j++) {
        //         printf("%d ", dp[i][j]);
        //     }
        //     printf("\n");
        // }
    }
}

/*
50 40  200 140 250
30 100 120 210 260
*/