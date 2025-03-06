#include <stdio.h>

#define MAX 1001

int n;
int dp[MAX];
int arr[MAX];

int main() {
    int result = 0;
    scanf("%d", &n);

    for(int i=1; i<=n; i++) {
        scanf("%d", &arr[i]);
    }

    dp[1] = 1;
    for(int i=2; i<=n; i++) {
        int max = 0;
        for(int j=1; j<i; j++) {
            if(arr[i] > arr[j] && dp[j] > max) max = dp[j];
        }
        dp[i] = max + 1;
    }

    for(int i=1; i<=n; i++) {
        if(dp[i] > result) result = dp[i];
    }

    printf("%d", result);
}