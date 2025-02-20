#include <stdio.h>

#define MAX 100000

int n, k; // 수빈이 위치 n, 동생 위치 k
int cnt = 0;

int main() {
    scanf("%d %d", &n, &k);

    while(n != k-1 || n != k+1) {
        if(((n + 2*n)/2) < k || n*2 < k) {   // 2를 곱해줌
            n = 2*n;
        } else if(n < k) {
            n++;
        } else {
            n--;
        }
        cnt++;
        printf("testN: %d\n", n);
        printf("testCnt: %d\n", cnt);
    }

    printf("%d", cnt);

    return 0;
}