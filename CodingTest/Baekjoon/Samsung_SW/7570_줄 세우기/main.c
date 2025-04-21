#include <stdio.h>

#define MAX 1000001

int main() {
	int n;
	int dp[MAX] = {0,};
	int max = 0;
	scanf("%d", &n);

	for (long i = 1; i <= n; i++) {
		int x;
		scanf("%d", &x);
		dp[x] = dp[x - 1] + 1;
		if (dp[x] > max) max = dp[x];
	}

	int ret = n - max;
	printf("%d", ret);

	return 0;
}