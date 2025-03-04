#include <stdio.h>
#include <string.h>

#define MAX_N 100005

int arr[MAX_N];
int state[MAX_N];
int n;

const int NOT_VISITED = 0;
const int CYCLE_IN = -1;

void run(int x) {
    int cur = x;
    while (1) {
        state[cur] = x;
        cur = arr[cur];
        // 이번 방문에서 지나간 학생에 도달했을 경우
        if (state[cur] == x) {
            while (state[cur] != CYCLE_IN) {
                state[cur] = CYCLE_IN;
                cur = arr[cur];
            }
            return;
        }
        // 이전 방문에서 지나간 학생에 도달했을 경우
        else if (state[cur] != 0) return;
    }
}

int main(void) {
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        memset(state, 0, (n + 1) * sizeof(int));
        for (int i = 1; i <= n; i++) {
            scanf("%d", &arr[i]);
        }

        for (int i = 1; i <= n; i++) {
            if (state[i] == NOT_VISITED) run(i);
        }
        
        int cnt = 0;
        for (int i = 1; i <= n; i++) {
            if (state[i] != CYCLE_IN) cnt++;
        }
        printf("%d\n", cnt);
    }
    return 0;
}
