#include <stdio.h>

#define MAX 41

int t;
int dp[MAX][2];

int main() {
    scanf("%d", &t);

    for(int j=0; j<t; j++) {
        int n;
        scanf("%d", &n);
        memset(dp, 0, sizeof(dp));

        dp[0][0] = 1;
        dp[0][1] = 0;
        dp[1][0] = 0;
        dp[1][1] = 1;
        for(int i=2; i<=n; i++) {
            dp[i][0] = dp[i-1][0] + dp[i-2][0];
            dp[i][1] = dp[i-1][1] + dp[i-2][1];
        }

        printf("%d %d\n", dp[n][0], dp[n][1]);
    }
}