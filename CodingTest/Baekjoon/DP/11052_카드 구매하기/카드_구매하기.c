#include <stdio.h>

#define MAX 1001
#define max(x, y) ((x>y) ? x : y)

int n;
int arr[MAX];
int dp[MAX];

int main() {
    scanf("%d", &n);
    for(int i=1; i<=n; i++) {
        scanf("%d", &dp[i]);
    }

    for(int i=1; i<=n; i++) {
        for(int j=1; j<=i; j++) {
            dp[i] = max(dp[i-j]+dp[j], dp[i]);
            // for(int i=1; i<=n; i++) {
            //     printf("%d ", dp[i]);
            // }
            // printf("\n");
        }
    }

    printf("%d", dp[n]);
}

/*
[1] = (10, 10) = 10
[2] = (10+10, 9) (0+9, 20) = 20
[3] = (20+10, 8) (10+20, 30) (30, 30) = 30
[4] = (30+10, 8) () = 40
[5] = () 50
*/