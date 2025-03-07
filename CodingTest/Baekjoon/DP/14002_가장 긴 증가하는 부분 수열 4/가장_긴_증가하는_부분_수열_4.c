#include <stdio.h>

#define MAX 1001

int n;
int arr[MAX];
int dp[MAX][2];
int ret[MAX];

int main() {
    int idx = 1;
    int result = 1;
    scanf("%d", &n);

    for(int i=1; i<=n; i++) {
        scanf("%d", &arr[i]);
    }

    dp[1][0] = 1;
    dp[1][1] = 0;
    for(int i=2; i<=n; i++) {
        int max = 0;
        for(int j=1; j<=i; j++) {
            if(arr[i] > arr[j] && dp[j][0] > max) {
                max = dp[j][0];
                dp[i][1] = j;
            }
        }
        dp[i][0] = max + 1;
        if(dp[i][0] > result) {
            result = dp[i][0];
            idx = i;
        }
    }

    int cnt = 0;
    while(idx != 0) {
        ret[cnt] = arr[idx];
        idx = dp[idx][1];
        cnt++;
    }

    printf("%d\n", result);
    for(int i=cnt-1; i>=0; i--) {
        printf("%d ", ret[i]);
    }

    // for(int i=1; i<=n; i++) {
    //     printf("%3d", dp[i][0]);
    // }
    // printf("\n");
    // for(int i=1; i<=n; i++) {
    //     printf("%3d", dp[i][1]);
    // }


}

/*
1  2  3  4  5  6   
10 20 10 30 20 50

1  2  1  3  2  4
0  1  0  2  1  4
*/