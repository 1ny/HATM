/*
1   2   3   4   5   6   7   8   9   10
-   -   10  30  30 

0   0   10          20
0   0   10  30  30  45
0   0   10  30  30  45  45    70 

10  10  20  40  40  55  


1   2   3   4   5   6   7   8   9   10  11  12  13  14  15
5   4   3   2   1   1   2   3   4   5
50  40  30  20  10  10  20  30  40  50
0               50
0   0           50
0   0   0       50
0   0   0   0   50
0   0   0   0   50
0   0   0   0   50  60
0   0   0   0   50  60  60  80
0   0   0   0   50  60  60  80      90
0   0   0   0   50  60  60  80  80  90      120

*/

#include <stdio.h>

#define MAX 31

int n;
int t[MAX], p[MAX];
int dp[MAX];

int max(int x, int y) {
    if(x > y) return x;
    else return y;
}

int main() {
    int result = 0;
    scanf("%d", &n);

    for(int i=1; i<=n; i++) {
        scanf("%d %d", &t[i], &p[i]);
    }

    for(int i=1; i<=n; i++) {
        if(t[i] > 1) {
            int jump = i+t[i]-1;
            dp[i] = max(dp[i-1], dp[i]);
            dp[jump] = max(dp[i-1] + p[i], dp[jump]);
        } else {
            dp[i] = max(dp[i-1] + p[i], dp[i]);
        }
        
        // for(int i=1; i<=n; i++) {
        //     printf("%3d ", dp[i]);
        // }
        // printf("\n");

        if(dp[i] > result) result = dp[i];
    }

    printf("%d", result);
}