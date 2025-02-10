#include <stdio.h>
#include <stdlib.h>

// 2025 상반기 오토에버 코테 문제 #1
// 내 풀이 -> n=100000 에서 시간 터짐
// 개선.ver -> vscode랑 vs에서는 안됨. 근데 왜 소프티어에서는 되지? 이상함
// 각 노드는 0~2개의 간선을 가질 수 있음
// 서로 인접한 두 노드는 동시에 선택 불가
// 최대로 선택할 수 있는 노드 수는?
#define MAX_N 100000

int n, m;
int x, y;
int visited[MAX_N + 1] = {0,};
int max = 0;

// 정점과 정점을 잇는 포인터 선언언
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

// 인접 리스트 선언 및 초기화
Node* graph[MAX_N+1] = {NULL};

// 간선 추가 함수
void addEdge(int u, int v) {
    // 새 노드 v를 생성하고, vertex에 v를 저장
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;

    // 새 노드 v 의 next에 u 정점의 인접리스트를 넣는다.
    // 즉, u 정점의 인접리스트 맨 처음에 v 정점을 삽입한다. ?? 이거 맞나?
    newNode->next = graph[u];

    // u 정점의 인접리스트에 newNode 포인터를 할당한다. 그러면 u 정점의 인접리스트가 업데이트됨!
    graph[u] = newNode;
}

// 해당 node의 인접리스트에 있는 node는 선택하면 안됨! 
int check(int node) {
    Node* g = graph[node];

    while(g != NULL) {
        if(visited[g->vertex]) return 0;
        g = g->next;
    }

    return 1;
}

void dfs(int node, int selCnt) {
    if(node > n) {
        if(selCnt > max) max = selCnt;
        return ;
    }

    if(check(node)) {
        visited[node] = 1;
        dfs(node+1, selCnt+1);
        visited[node] = 0;
    }
    else dfs(node+1, selCnt);
}

int main() {
    scanf("%d %d", &n, &m);

    for(int i=0; i<m; i++) {
        scanf("%d %d", &x, &y);
        addEdge(x, y);
        addEdge(y, x); // 양(무)방향
    }

    dfs(1, 0);

    printf("%d", max);

    return 0;
}