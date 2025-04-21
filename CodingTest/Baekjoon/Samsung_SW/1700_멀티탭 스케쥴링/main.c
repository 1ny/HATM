#include <stdio.h>
#include <string.h>

#define MAX 101

int main() {
	int n, k;
	int arr[MAX];
	int plug[MAX] = { 0, };
	int cnt = 0;
	int ret = 0;
	int idx[MAX] = { 0, };
	scanf("%d %d", &n, &k);

	for (int i = 0; i < k; i++) {
		scanf("%d", &arr[i]);
	}

	for (int i = 0; i < k; i++) {
		for (int j = 1; j <= k; j++) {
			printf("%d ", plug[j]);
		}
		printf("\n");
		if (plug[arr[i]] == 1) continue;
		if (cnt == n) {
			memset(idx, 0, sizeof(idx));
			for (int j = 1; j <= k; j++) {
				if (plug[j] == 0) continue;
				for (int p = i + 1; p < k; p++) {
					idx[j] = k;
					if (arr[p] == j)
					{
						idx[j] = p;
						break;
					}
				}
			}

			int max = 0;
			int maxIdx = 0;
			for (int j = 1; j <= k; j++) {
				if (idx[j] > max) {
					maxIdx = j;
					max = idx[j];
				}
			}

			plug[maxIdx] = 0;
			plug[arr[i]] = 1;
			ret++;
		}
		else
		{
			plug[arr[i]] = 1;
			cnt++;
		}
	}

	printf("%d", ret);

	return 0;
}