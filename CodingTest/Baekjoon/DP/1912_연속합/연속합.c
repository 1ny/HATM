#include <stdio.h>

#define MAX 100001

int n;
int arr[MAX];
int dp[MAX];

int max(int x, int y) {
    if(x > y) return x;
    else return y;
}

int main() {
    int result = -1000;
    scanf("%d", &n);

    for(int i=1; i<=n; i++) {
        scanf("%d", &arr[i]);
    }

    dp[1] = arr[1];
    for(int i=2; i<=n; i++) {
        dp[i] = max(arr[i], dp[i-1] + arr[i]);
    }

    for(int i=1; i<=n; i++) {
        if(dp[i] > result) result = dp[i];
    }

    printf("%d", result);
}

/*1
1  2  3  4  5  6  7  8  9  10
2  1  -4 3  4 -4  6  5  -5 1
2  3  -1 3  7  3  9  14 9  10
*/