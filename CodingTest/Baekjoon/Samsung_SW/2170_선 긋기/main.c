#include <stdio.h>
#include <stdlib.h>

#define MAX 2000000

typedef struct {
	long long x;
	int type;
} Arr;

int compare(const void* a, const void* b) {
	const Arr* pa = (const Arr*)a;
	const Arr* pb = (const Arr*)b;
	if (pa->x == pb->x) return pa->type - pb->type;
	return pa->x - pb->x;
}


int main() {
	int n;
	Arr* arr = malloc(sizeof(Arr) * MAX);

	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		long long x=0, y=0;
		scanf("%lld %lld", &x, &y);
		arr[2*i] = (Arr){ x,1 };
		arr[2*i + 1] = (Arr){ y, -1 };
	}

	qsort(arr, 2*n, sizeof(Arr), compare);

	//for (int i = 0; i < n * 2; i++) {
	//	printf("%d, %d\n", arr[i].x, arr[i].type);
	//}

	long long cnt = 0;
	long long cur = arr[0].x;
	long long total = 0;
	for (int i = 0; i < n*2; i++) {
		if (cnt > 0) total += arr[i].x - cur;
		cur = arr[i].x;
		cnt += arr[i].type;
	}

	printf("%lld", total);

	return 0;
}