#include <stdio.h>
#include <stdlib.h>

#define MAX 100001

int n, m;   // 수의 개수 n, 합을 구해야 하는 횟수 m
int num[MAX];
int dp[MAX];

int main() {
    scanf("%d %d", &n, &m);
    for(int i=1; i<=n; i++) {
        scanf("%d", &num[i]);
    }

    dp[0] = 0;
    for(int i=1; i<=n; i++) {
        dp[i] = dp[i-1] + num[i];
    }

    for(int i=0; i<m; i++) {
        int x, y;   // 구간
        scanf("%d %d", &x, &y);

        printf("%d\n", dp[y] - dp[x-1]);
    }
}