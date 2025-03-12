#include <stdio.h>

#define MAX_T 1001
#define MAX_W 31
#define max(x, y) ((x > y) ? x : y)

int t, w;
int arr[MAX_T];
int dp[MAX_T][MAX_W];

int main() {
    scanf("%d %d", &t, &w);

    for(int i=1; i<=t; i++) {
        scanf("%d", &arr[i]);
    }

    int cnt = 0;
    for(int i=1; i<=t; i++) {
        if(arr[i] == 1) cnt++;
        dp[i][0] = cnt;
    }

    for(int i=1; i<=t; i++) {
        for(int j=1; j<=w; j++) {
            dp[i][j] = max(dp[i-1][j-1], dp[i-1][j]);
            if(j%2 == 0 && arr[i] == 1) dp[i][j]++;
            else if(j%2 == 1 && arr[i] == 2) dp[i][j]++;
        }
    }

    int result = 0;
    for(int i=0; i<=w; i++) {
        if(dp[t][i] > result) result = dp[t][i];
    }

    printf("%d", result);
}

/*
1  2  3  4  5  6  7
2  1  1  2  2  1  1

0  1  2  2  2  3  4
1  1  1  3  4  4  4

*/