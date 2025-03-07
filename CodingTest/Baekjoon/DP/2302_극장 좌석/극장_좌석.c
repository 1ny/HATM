#include <stdio.h>

#define MAX 41

int n, m;
int arr[MAX];
long long int dp[MAX];

int main() {
    long long int result = 1;
    int preIdx = 0;
    scanf("%d %d", &n, &m);

    for(int i=1; i<=m; i++) {
        int x;
        scanf("%d", &x);
        arr[x] = 1;
    }

    dp[0] = 1;
    dp[1] = 1;
    dp[2] = 2;
    for(int i=3; i<=n; i++) {
        dp[i] = dp[i-2] + dp[i-1];
    }

    for(int i=1; i<=n+1; i++) {
        if(arr[i] || i == n+1) {
            // printf("%d\n", i-preIdx- 1);
            result *= dp[i-preIdx- 1];
            preIdx = i;
        }
    }

    printf("%lld", result);
}

/*
1 2 3 4 5 6 7 8 9 10
[1] = 1
[1 2] = 2 
[1 2 3] = 3
 1 2 3

 2 1 3
 1 3 2

[1 2 3 4] = 5
 1 2 3 4

 2 1 3 4
 1 2 4 3
 1 3 2 4
 
 2 1 4 3

[1 2 3 4 5] = 8
 1 2 3 4 5

 2 1 3 4 5
 1 3 2 4 5
 1 2 4 3 5
 1 2 3 5 4
 
 2 1 4 3 5
 1 3 2 5 4
 2 1 3 5 4

[1 2 3 4 5 6] = 13
 1 2 3 4 5 6

 2 1 3 4 5 6
 ... => 5

 2 1 4 3 5 6
 ... => 6

 2 1 4 3 6 5
*/