#include <stdio.h>
#include <stdbool.h>

#define MAX 3000

int n; // 계단의 개수 n
int score[MAX];
int dp[MAX][2];

int main() {
    scanf("%d", &n);
    for(int i=1; i<=n; i++) {
        scanf("%d", &score[i]);
    }

    if(n == 1) {
        printf("%d", score[1]);
        return 0;
    }
    
    dp[1][0] = score[1];
    dp[2][0] = score[2];
    dp[2][1] = dp[1][0] + score[2];
    for(int i=3; i<=n; i++) {
        if(dp[i-2][0] > dp[i-2][1]) dp[i][0] = dp[i-2][0] + score[i];
        else dp[i][0] = dp[i-2][1] + score[i];
        dp[i][1] = dp[i-1][0] + score[i];
    }

    // for(int i=0; i<2; i++) {
    //     for(int j=1; j<=n; j++) {
    //         printf("%d ", dp[j][i]);
    //     }
    //     printf("\n");
    // }

    if(dp[n][0] > dp[n][1]) printf("%d", dp[n][0]);
    else printf("%d", dp[n][1]);
}