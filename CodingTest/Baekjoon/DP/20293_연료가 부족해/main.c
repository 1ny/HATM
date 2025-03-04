#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

int r, c, n;
int x[1005], y[1005], fuel[1005];
int v_size = 0;

int compare(const void* a, const void* b) {
    int ia = *(int*)a;
    int ib = *(int*)b;
    return (x[ia] + y[ia]) - (x[ib] + y[ib]);
}

// a -> b 거리 계산 함수
int f(int a, int b) {
    return abs(x[a] - x[b]) + abs(y[a] - y[b]);
}

// a -> b 이동 가능 여부 체크 함수
bool g(int a, int b) {
    return x[a] <= x[b] && y[a] <= y[b];
}

// 처음 연료량이 k일 때 도착 가능 여부 확인 함수
bool check(int n) {
    int dp[1005];
    for (int i = 0; i < v_size; i++) dp[i] = -1;
    dp[0] = n;
    
    for (int i = 1; i < v_size; i++) {
        for (int j = 0; j < i; j++) {
            if (!g(j, i)) continue;
            if (dp[j] < f(j, i)) continue;
            if (dp[i] < dp[j] - f(j, i) + fuel[i]) {
                dp[i] = dp[j] - f(j, i) + fuel[i];
            }
        }
    }
    return dp[v_size - 1] != -1;
}

int main() {
    scanf("%d %d %d", &r, &c, &n);
    
    int indices[1005];
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &x[i], &y[i], &fuel[i]);
        x[i]--, y[i]--;
        indices[i] = i;
    }
    
    x[n] = 0, y[n] = 0, fuel[n] = 0, indices[n] = n;
    x[n+1] = r - 1, y[n+1] = c - 1, fuel[n+1] = 0, indices[n+1] = n+1;
    v_size = n + 2;
    
    qsort(indices, v_size, sizeof(int), compare);
    
    int sorted_x[1005], sorted_y[1005], sorted_fuel[1005];
    for (int i = 0; i < v_size; i++) {
        sorted_x[i] = x[indices[i]];
        sorted_y[i] = y[indices[i]];
        sorted_fuel[i] = fuel[indices[i]];
    }
    for (int i = 0; i < v_size; i++) {
        x[i] = sorted_x[i];
        y[i] = sorted_y[i];
        fuel[i] = sorted_fuel[i];
    }
    
    int lo = 0, hi = 6000;
    while (lo + 1 < hi) {
        int mid = (lo + hi) / 2;
        if (!check(mid)) lo = mid;
        else hi = mid;
    }
    
    printf("%d\n", hi);
    return 0;
}
