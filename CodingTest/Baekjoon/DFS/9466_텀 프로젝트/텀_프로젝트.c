#include <stdio.h>
#include <stdbool.h>

#define MAX 1000001

int t, n;
int arr[MAX];
int state[MAX];

#define IS_CYCLE  -1    // cycle이면 -1로 체크

void check_cycle(int x) {
    int cur = x;
    while(1) {
        state[cur] = x;
        cur = arr[cur];
        if(state[cur] == x) {
            while(1) {
                state[cur] = IS_CYCLE;
                cur = arr[cur];
                if(state[cur] == IS_CYCLE) return;
            }
        }
        else if(state[cur] != 0) return;
    }
}

int main() {
    scanf("%d", &t);

    while(t--) {
        scanf("%d", &n);
        memset(state, 0, (n+1) * sizeof(int));
        for(int i=1; i<=n; i++) {
            scanf("%d", &arr[i]);
        }

        for(int i=1; i<=n; i++) {
            if(!state[i]) check_cycle(i);
        }

        int cnt = 0;
        for(int i=1; i<=n; i++) {
            if(state[i] != IS_CYCLE) cnt++;
        }
    
        printf("%d\n", cnt);
    }
}