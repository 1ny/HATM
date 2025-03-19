#include <stdio.h>

#define MAX 8

int n, m;
char arr[MAX][MAX];
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
int cnt, min;

int main() {
    scanf("%d %d ", &n, &m);
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            scanf("%c ", &arr[i][j]);
        }
    }

    for(int p=5; p>=1; p--) {
        for(int i=0; i<n; i++) {
            for(int j=0; j<m; j++) {
                if(arr[i][j] == (p+'0')) {
                    if(p == 5) {
                        for(int v=0; v<n; v++) {
                            if(arr[v][j] == '0') arr[v][j] = '#';
                        }
                        for(int v=0; v<m; v++) {
                            if(arr[i][v] == '0') arr[i][v] = '#';
                        }
                    } else if(p == 4) {
                        
                    }
                }
            }
        }
    }

    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            printf("%c ", arr[i][j]);
        }
        printf("\n");
    }
    // printf("%d", 5-'0')

}

/*
0 1 2 3 4 5 6
# 1 2 3 4 5 6

4 # # # # # #
# # # 2 0 0 #
# # # # # # 4

6 6
1 # # # # #
0 1 # # # #
# # 1 5 # #
# # 5 1 # #
# # # # 1 0
# # # # # 1

6 6
1 # # # # #
0 1 # # # #
0 0 1 # # #
# # # 1 0 0
# # # # 1 0
# # # # # 1

6 6
0 0 0 0 0 #
# 2 # # # #
0 0 0 0 6 #
0 6 # # 2 #
0 0 0 0 0 #
# # # # # 5
*/