#include <stdio.h>
#include <stdlib.h>

#define MAX 3001

int r, c;   // 세로 길이 R, 가로 길이 C
int n;      // 연료 보관소 수 n
int x[MAX], y[MAX], f[MAX];
int arr[MAX];

int main() {
    scanf("%d %d", &r, &c);
    scanf("%d", &n);
    for(int i=0; i<n; i++) {
        scanf("%d %d %d", &x[i], &y[i], &f[i]);
        arr[i] = i;
    }

    x[n] = 0, y[n] = 0, f[n] = 0;
    arr[n] = n;
    
}