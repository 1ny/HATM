#include <stdio.h>
#include <stdbool.h>

#define MAX 1000

int n;
int arr[MAX][3];
int price[MAX][3];

int min(int x, int y) {
    if(x < y) return x;
    else return y;
}

int main() {
    scanf("%d", &n);
    for(int i=0; i<n; i++) {
        for(int j=0; j<3; j++) {
            scanf("%d", &arr[i][j]);
        }
    }

    price[0][0] = arr[0][0];
    price[0][1] = arr[0][1];
    price[0][2] = arr[0][2];
    for(int i=1; i<n; i++) {
        price[i][0] = min(price[i-1][1], price[i-1][2]) + arr[i][0];
        price[i][1] = min(price[i-1][0], price[i-1][2]) + arr[i][1];
        price[i][2] = min(price[i-1][0], price[i-1][1]) + arr[i][2];
    }

    int min = n*MAX;
    for(int i=0; i<3; i++) {
        if(price[n-1][i] < min) min = price[n-1][i];
    }

    printf("%d", min);
}