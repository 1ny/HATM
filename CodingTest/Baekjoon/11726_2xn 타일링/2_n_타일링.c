#include <stdio.h>
#include <stdlib.h>

int n;
int cnt1, cnt2;
int caseNum;

int fact(int x) {
    if(x == 1 || x == 0)  return 1; 
    return x * fact(x-1);
}

int main() {
    scanf("%d", &n);

    while(cnt2*2 <= n) {
        cnt1 = n - cnt2*2;
        caseNum += fact(cnt1+cnt2) / (fact(cnt1) * fact(cnt2));
        // printf("[%d] %d\n", cnt2, caseNum);
        cnt2++;
    }

    printf("%d", caseNum%10007);
}

// 500*