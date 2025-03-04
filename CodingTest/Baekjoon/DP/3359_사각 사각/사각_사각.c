#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX 1000

int n;
int rects[MAX][2];
int length[MAX][2];

int max(int x, int y) {
    if(x > y) return x;
    else return y;
}

int main() {
    scanf("%d", &n);
    for(int i=0; i<n; i++) {
        scanf("%d %d", &rects[i][0], &rects[i][1]);
    }

    length[0][0] = rects[0][0];
    length[0][1] = rects[0][1];
    for(int i=1; i<n; i++) {
        length[i][0] = rects[i][0] + max(length[i-1][0] + abs(rects[i][1]-rects[i-1][1]), length[i-1][1] + abs(rects[i][1] - rects[i-1][0]));
        length[i][1] = rects[i][1] + max(length[i-1][0] + abs(rects[i][0]-rects[i-1][1]), length[i-1][1] + abs(rects[i][0] - rects[i-1][0]));
    }

    // for(int i=0; i<n; i++) {
    //     printf("%d %d\n", length[i][0], length[i][1]);
    // }

    printf("%d", max(length[n-1][0], length[n-1][1]));
}