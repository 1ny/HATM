#include <stdio.h>

#define MAX 1001

int dp[MAX];
int arr[MAX];

int main() {
    int n, result = 0;
    scanf("%d", &n);

    for(int i=1; i<=n; i++) {
        scanf("%d", &arr[i]);
    }

    dp[1] = arr[1];
    for(int i=2; i<=n; i++) {
        int max = 0;
        for(int j=1; j<i; j++) {
            // j를 포함하는 부분 수열 중 가장 큰 수가 i보다 작고
            // 합이 가장 큰 부분 수열의 합
            if(arr[i] > arr[j] && dp[j] > max) {
                max = dp[j];
            }
        }
        dp[i] = max + arr[i];
    }

    for(int i=1; i<=n; i++) {
        if(dp[i] > result) result = dp[i];
    }

    printf("%d", result);
}