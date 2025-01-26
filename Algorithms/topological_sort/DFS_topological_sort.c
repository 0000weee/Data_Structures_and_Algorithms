// DFS topological sort
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NODES 100 // 最大節點數

// 圖結構
typedef struct {
    int adj[MAX_NODES][MAX_NODES]; // 鄰接矩陣
    bool visited[MAX_NODES];      // 訪問標記
    int num_nodes;                // 節點數量
} Graph;

// 初始化圖
void initGraph(Graph *graph, int num_nodes) {
    graph->num_nodes = num_nodes;
    for (int i = 0; i < num_nodes; i++) {
        graph->visited[i] = false;
        for (int j = 0; j < num_nodes; j++) {
            graph->adj[i][j] = 0;
        }
    }
}

// 添加邊 (u -> v)
void addEdge(Graph *graph, int u, int v) {
    graph->adj[u][v] = 1;
}

// 深度優先搜索
void dfs(Graph *graph, int node, int *stack, int *top) {
    graph->visited[node] = true;

    for (int i = 0; i < graph->num_nodes; i++) {
        if (graph->adj[node][i] && !graph->visited[i]) {
            dfs(graph, i, stack, top);
        }
    }

    stack[(*top)++] = node; // 在遞歸結束時將節點壓入堆疊
}

// 拓撲排序
void topologicalSort(Graph *graph, int result[]) {
    int stack[MAX_NODES];
    int top = 0;

    // 對所有未訪問的節點進行 DFS
    for (int i = 0; i < graph->num_nodes; i++) {
        if (!graph->visited[i]) {
            dfs(graph, i, stack, &top);
        }
    }

    // 從堆疊中彈出節點，形成拓撲排序結果
    for (int i = 0; i < top; i++) {
        result[i] = stack[top - i - 1];
    }
}

// 主函數
int main() {
    Graph graph;
    initGraph(&graph, 6);

    // 添加邊
    addEdge(&graph, 5, 2);
    addEdge(&graph, 5, 0);
    addEdge(&graph, 4, 0);
    addEdge(&graph, 4, 1);
    addEdge(&graph, 2, 3);
    addEdge(&graph, 3, 1);

    int result[MAX_NODES];
    topologicalSort(&graph, result);

    printf("Topological Sort: ");
    for (int i = 0; i < graph.num_nodes; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    return 0;
}
