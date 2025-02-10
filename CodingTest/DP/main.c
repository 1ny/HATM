#include <stdio.h>

#define MAX_X 2
#define MAX_N 1001
 
int N; // 숫자 쌍 개수 N
int num_pair[MAX_N][2]; // 숫자 쌍
 
int dp[MAX_N][MAX_X * MAX_N]; // N X (X 개수 * 쌍 개수수)

int max(int a, int b) {
    return (a > b) ? a : b;
}

int solve() {
    int ans = 0;

    // dp 초기화
    for (int i = 0; i < MAX_N; i++) {
        for (int j = 0; j < MAX_X * MAX_N; j++) {
            dp[i][j] = 0;
        }
    }

    // x 값들을 합산한다.
    for (int i = 0; i < N; i++) {
        ans += num_pair[i][0];
    }

    // ans = 1 + 1 + 2 + 2 + 2 = 8
    // dp 에 default로 -1 flag
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < ans; j++) {
            dp[i][j] = -1;
        }
    }

    // 첫번째 숫자 쌍의 x - y 인덱스에 x 값 저장?
    // dp[0][8] = 0
    // dp[0][8 - 1 - 12] = 1
    dp[0][ans] = 0;
    dp[0][ans - num_pair[0][0] - num_pair[0][1]] = num_pair[0][0];

    for (int i = 1; i < N; i++) {
        int sum = num_pair[i][0] + num_pair[i][1]; // sum = 4
        for (int j = 0; j <= ans; j++) {
            if (dp[i - 1][j] != -1) {
                int diff = j - sum;
                if (diff >= 0) {
                    dp[i][diff] = max(dp[i][diff], dp[i - 1][j] + num_pair[i][0]);
                }
                dp[i][j] = dp[i - 1][j];
            }
        }
    }
    int max_value = -1;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= ans; j++) {
            max_value = max(max_value, dp[i][j]);
        }
    }
    return ans - max_value;
 
}
 
int main(void)
{
    int T;
    scanf("%d", &T);
 
    for (int test_case = 1; test_case <= T; test_case++)
    {
        scanf("%d", &N);
 
        for (int i = 0; i < N; i++)
        {
            scanf("%d %d", &num_pair[i][0], &num_pair[i][1]);
        }
        printf("#%d %d\n", test_case, solve());
    }
    return 0;
}