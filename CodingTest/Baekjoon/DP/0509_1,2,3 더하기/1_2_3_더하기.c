#include <stdio.h>
#include <stdbool.h>

#define MAX 100

int t, n;
int dp_table[MAX];

int main() {
    scanf("%d", &t);
    
    for(int i=0; i<t; i++) {
        scanf("%d", &n);

        dp_table[1] = 1;
        dp_table[2] = 2;
        dp_table[3] = 4;
        for(int j=4; j<=n; j++) {
            dp_table[j] = dp_table[j-1] + dp_table[j-2] + dp_table[j-3];
        }

        printf("%d\n", dp_table[n]);
    }
}