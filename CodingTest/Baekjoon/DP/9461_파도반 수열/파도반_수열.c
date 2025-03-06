#include <stdio.h>

#define MAX 101

int t, n;
long long int dp[MAX];

int main() {
    scanf("%d", &t);
    for(int j=0; j<t; j++) {
        scanf("%d", &n);

        dp[1] = 1;
        dp[2] = 1;
        dp[3] = 1;
        dp[4] = 2;
        dp[5] = 2;
        for(int i=6; i<=n; i++) {
            dp[i] = dp[i-5] + dp[i-1];
        }

        printf("%lld\n", dp[n]);
    }
}