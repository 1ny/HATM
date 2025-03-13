#include <stdio.h>

#define MAX 501

int n;
int arr[MAX][MAX];
int dp[MAX][MAX];

int max(int x, int y) {
    if(x > y) return x;
    else return y;
}

int main() {
    scanf("%d", &n);

    for(int i=1; i<=n; i++) {
        for(int j=1; j<=i; j++) {
            scanf("%d", &arr[i][j]);
        }
    }

    dp[1][1] = arr[1][1];
    for(int i=2; i<=n; i++) {
        for(int j=1; j<=i; j++) {
            dp[i][j] = max(dp[i-1][j-1], dp[i-1][j]) + arr[i][j];
        }
    }

    int max = 0;
    for(int i=1; i<=n; i++) {
        if(dp[n][i] > max) max = dp[n][i];
    }

    printf("%d", max);
}