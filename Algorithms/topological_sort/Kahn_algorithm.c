// Kahn's Algorithm
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NODES 100 // 最大節點數

// 圖結構
typedef struct {
    int adj[MAX_NODES][MAX_NODES]; // 鄰接矩陣
    int in_degree[MAX_NODES];     // 入度數組
    int num_nodes;                // 節點數量
} Graph;

// 初始化圖
void initGraph(Graph *graph, int num_nodes) {
    graph->num_nodes = num_nodes;
    for (int i = 0; i < num_nodes; i++) {
        graph->in_degree[i] = 0;
        for (int j = 0; j < num_nodes; j++) {
            graph->adj[i][j] = 0;
        }
    }
}

// 添加邊 (u -> v)
void addEdge(Graph *graph, int u, int v) {
    if (graph->adj[u][v] == 0) { // 防止重複邊
        graph->adj[u][v] = 1;
        graph->in_degree[v]++;
    }
}

// 拓撲排序
bool topologicalSort(Graph *graph, int result[]) {
    int queue[MAX_NODES];
    int front = 0, rear = 0;
    int count = 0; // 計算已排序的節點數

    // 將所有入度為 0 的節點加入隊列
    for (int i = 0; i < graph->num_nodes; i++) {
        if (graph->in_degree[i] == 0) {
            queue[rear++] = i;
        }
    }

    // 開始排序
    while (front < rear) {
        int current = queue[front++];
        result[count++] = current;

        // 遍歷當前節點的相鄰節點
        for (int i = 0; i < graph->num_nodes; i++) {
            if (graph->adj[current][i]) {
                graph->in_degree[i]--;
                if (graph->in_degree[i] == 0) {
                    queue[rear++] = i;
                }
            }
        }
    }

    // 如果排序的節點數少於圖中的節點數，說明存在環
    return count == graph->num_nodes;
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
    if (topologicalSort(&graph, result)) {
        printf("Topological Sort: ");
        for (int i = 0; i < graph.num_nodes; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
    } else {
        printf("The graph has a cycle and cannot be topologically sorted.\n");
    }

    return 0;
}
