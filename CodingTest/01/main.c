#if 0
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

#define MAX_N 100000
int n, m;
int degree[MAX_N + 1] = {0}; // 각 노드의 차수 저장
int selected[MAX_N + 1] = {0}; // 노드 선택 여부
Node* graph[MAX_N+1] = {NULL};

void addEdge(int u, int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = graph[u];
    graph[u] = newNode;
    degree[u]++;
}

int solve() {
    int count = 0;

    for (int i = 1; i <= n; i++) {
        if (!selected[i]) {
            selected[i] = 1;
            count++;

            Node* g = graph[i];
            while (g) {
                selected[g->vertex] = 1;
                g = g->next;
            }
        }
    }
    
    return count;
}

int main() {
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        addEdge(x, y);
        addEdge(y, x);
    }

    printf("%d\n", solve());
    return 0;
}
#endif

#if 1
#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000

int n, m;
int edge[MAX_N][2] = {0,};
int degree[MAX_N] = {0,}; // 각 노드의 차수 저장
int* adj[MAX_N] = {0,};
int idx[MAX_N] = {0,}; // adj, 즉 각 노드에 연결된 노드를 추가할때마다 ++
int visited[MAX_N] = {0,};

int bfs() {
    int count = 0;

    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            visited[i] = 1;
            count++;
#if 0
            Node* g = graph[i];
            while (g) {
                visited[g->vertex] = 1;
                g = g->next;
            }
#endif
            for(int j=0; j<idx[i]; j++) {
                visited[i] = 1;
            }
        }
    }
    
    return count;
}

int main() {
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; i++) {
        scanf("%d %d", &edge[i][0], &edge[i][1]);
        degree[edge[i][0]]++;
        degree[edge[i][1]]++;
    }

    for(int i=0; i<n; i++) {
        adj[i] = (int*)malloc(degree[i] * sizeof(int));
    }
    
    for(int i=0; i<m; i++) {
        int x = edge[i][0];
        int y = edge[i][1];
        adj[x][idx[x]] = y;
        adj[y][idx[y]] = x;
        idx[x]++;
        idx[y]++;
    }

    printf("%d\n", bfs());
    return 0;
}
#endif