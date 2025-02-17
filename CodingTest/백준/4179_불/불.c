#include <stdio.h>
#include <stdbool.h>

#define MAX 1000

int r, c;
char arr[MAX][MAX] = {0,};
int queue[MAX*MAX][2] = {0,};
int front = 0, rear = 0;

void push(int x, int y) {
    queue[rear][0] = x;
    queue[rear++][1] = y;
}

void pop(int* x, int* y) {
    *x = queue[front][0];
    *y = queue[front++][1];
}

bool is_empty() {
    return (front == rear);
}

int main() {
    scanf("%d %d", &r, &c);
    for(int i=0; i<r; i++) {
        for(int j=0; j<c; j++) {
            scanf("%c", &arr[i][j]);
            if(arr[i][j] == 'J') push(i, j);
        }
    }

    return 0;
}