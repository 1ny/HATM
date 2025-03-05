#include <stdio.h>

#define MAX 1000001

int n;
int dp[MAX][2];

int min(int x, int y) {
    if(x < y) return x;
    else return y;
}

int main() {
    scanf("%d", &n);

    dp[1][0] = 0;
    dp[1][1] = 0;
    for(int i=2; i<=n; i++) {
        dp[i][0] = dp[i-1][0] + 1;
        dp[i][1] = i-1;
        if(i % 3 == 0) {
            dp[i][0] = min(dp[i][0], dp[i/3][0]+1);
            if(dp[i][0] == dp[i/3][0] + 1) dp[i][1] = i/3;
        }
        if(i % 2 == 0) {
            dp[i][0] = min(dp[i][0], dp[i/2][0] + 1);
            if(dp[i][0] == dp[i/2][0] + 1) dp[i][1] = i/2;
        }
    }

    // for(int i=1; i<=n; i++) {
    //     printf("%d ", dp[i][1]);
    // }

    printf("%d\n", dp[n][0]);
    printf("%d ", n);
    int i = n;
    while(1) {
        if(i == 1) break;
        printf("%d ", dp[i][1]);
        i = dp[i][1];
    }
}

/*
1  2  3  4  5  6  7  8  9  10
0  1  1  2  3  2  3  3  2  3
0  1  1  2  4  2  6  4  3  9
*/