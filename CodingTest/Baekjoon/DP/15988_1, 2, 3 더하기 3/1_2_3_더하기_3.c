#include <stdio.h>

#define MAX 1000001

int t, n;
long long int dp[MAX];

int main() {
    scanf("%d", &t);

    for(int p=0; p<t; p++) {
        memset(dp, 0, sizeof(dp));
        scanf("%d", &n);

        dp[1] = 1;
        dp[2] = 2;
        dp[3] = 4;
        for(int i=4; i<=n; i++) {
            dp[i] = (dp[i-3] + dp[i-2] + dp[i-1]) % 1000000009;
        }

        printf("%lld\n", dp[n]);
    }
}

/*
[1] = 1

[2] = 2
1+1

2

[3] = 4
1+1+1
2+1

1+2

3


[4] = 7 = 4 + 2 + 1
1+1+1+1
2+1+1
1+2+1
3+1

1+1+2
2+2

1+3

[5] = 13 = 7+4+2
1+1+1+1+1
2+1+1+1
1+2+1+1
1+1+2+1
2+2+1
3+1+1
1+3+1

1+1+1+2
2+1+2
1+2+2
3+2

1+1+3
2+3
*/