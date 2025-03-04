#include <stdio.h>
#include <stdlib.h>

#define MAX 100001

int n; // 박스의 개수 n
int Ai[MAX];
int dp[MAX];
int maxCnt = 1;

int main() {
    scanf("%d", &n);
    for(int i=1; i<=n; i++) {
        scanf("%d", &Ai[i]);
    }

    dp[1] = 1;
    for(int i=2; i<=n; i++) {   // [i]가 가장 큰 수인 수열을 만든다고 했을 때
        int max = 0;
        for(int j=1; j<i; j++) {    
            // 1부터 i번째까지 수열에 포함시킬 수 있는 숫자 개수를 dp에 저장한다.
            // 그러려면, 일단 [i]보다 작아야하고
            // dp는 그 아래 숫자들에서 조합할 수 있는 가장 긴 수열의 인자 개수를 의미하므로,
            // dp에서 가장 큰 숫자를 가능한 과대 포장 박수 개수가 된다.
            if(Ai[j] < Ai[i] && dp[j] > max) max = dp[j];
        }
        // 자기 자신을 포함시키고,
        dp[i] = max + 1;
        // 최종 결과물을 maxCnt랑 비교!
        if(dp[i] > maxCnt) maxCnt = dp[i];
    }

    for(int i=1; i<=n; i++) {
        printf("%d ", dp[i]);
    }

    printf("\n%d", maxCnt);
}