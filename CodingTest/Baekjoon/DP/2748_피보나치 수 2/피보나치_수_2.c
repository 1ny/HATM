#include <stdio.h>

#define MAX 91

int n;
long long dp[MAX];

int main() {
    scanf("%d", &n);

    dp[0] = 0;
    dp[1] = 1;
    if(n==0) {
        printf("0");
        return 0;
    }
    for(int i=2; i<=n; i++) {
        dp[i] = dp[i-2] + dp[i-1];
    }

    printf("%lld", dp[n]);
}