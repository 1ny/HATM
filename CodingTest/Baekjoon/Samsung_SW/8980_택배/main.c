#include <stdio.h>
#include <stdlib.h>

#define MAX 10001

typedef struct {
	int send;
	int receive;
	int count;
} Box;

int compare(const Box* a, const Box* b)
{
	return a->receive - b->receive;
}

int main() {
	int n, c, m;
	Box* arr = malloc(sizeof(Box) * MAX);
	long long cntArr[MAX] = { 0, };
	long long ret = 0;
	scanf("%d %d", &n, &c);
	scanf("%d ", &m);
	for (int i = 0; i < m; i++) {
		int send, receive, count;
		scanf("%d %d %d", &arr[i].send, &arr[i].receive, &arr[i].count);
	}

	qsort(arr, m, sizeof(Box), compare);

	//for (int i = 0; i < m; i++) {
	//	printf("%d %d %d\n", arr[i].send, arr[i].receive, arr[i].count);
	//}

	int curN = 0;
	for (int i = 0; i < m; i++) {
		int max = 0;
		for (int j = arr[i].receive-1; j >= arr[i].send; j--)
		{
			if (cntArr[j] > max) max = cntArr[j];
		}

		//if (c <= max) continue;
		int comp = 0;	// ´õÇÒ °ª
		if (arr[i].count >= (c - max)) comp = c - max;
		else comp = arr[i].count;
		for (int j = arr[i].receive - 1; j >= arr[i].send; j--)
		{
			cntArr[j] += comp;
		}

		//for (int j = 1; j <= n; j++) {
		//	printf("%d ", cntArr[j]);
		//}
		//printf("\n");

		if(comp > 0) ret += comp;
	}

	printf("%lld", ret);

	return 0;
}