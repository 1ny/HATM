#include <stdio.h>
#include <stdbool.h>

#define MAX 1000000

int n;
int arr[MAX];

int main() {
    scanf("%d", &n);
    arr[1] = 0;

    for(int i=2; i<=n; i++) {
        arr[i] = arr[i-1] + 1;
        if(i % 3 == 0) {
            if(arr[i] > arr[i/3] + 1) arr[i] = arr[i/3] + 1;
        }
        if(i % 2 == 0) {
            if(arr[i] > arr[i/2] + 1) arr[i] = arr[i/2] + 1;
        }
    }

    printf("%d", arr[n]);
}