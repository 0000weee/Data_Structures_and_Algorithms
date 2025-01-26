/*
Dijkstra's Algorithm 的基本步驟
初始化距離陣列，將起點的距離設為 0，其餘節點設為無窮大（∞）。
使用優先佇列（Priority Queue）來選擇當前距離最短的未處理節點。
更新其相鄰節點的最短距離，如果通過當前節點的路徑比原本更短，就更新。
重複以上過程，直到所有節點都處理完畢或找不到新的可達節點。
*/

// 採用鄰接表的圖結構和最小堆（Min-Heap）來實現 Dijkstra 演算法。
// 每次提取/更新的時間複雜度為 𝑂(log 𝑉)，整體演算法時間複雜度為 𝑂((𝑉+𝐸)log 𝑉)。

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

// 儲存邊的結構
typedef struct Edge {
    int to, weight;
    struct Edge* next;
} Edge;

// 圖結構（鄰接表）
typedef struct Graph {
    int num_nodes;
    Edge** adj_list; // 指向鄰接表的指標陣列
} Graph;

// 優先佇列的節點結構
typedef struct MinHeapNode {
    int vertex, distance;
} MinHeapNode;

// 優先佇列（最小堆）
typedef struct MinHeap {
    MinHeapNode* nodes;
    int* position; // 儲存每個節點在堆中的位置
    int size, capacity;
} MinHeap;

// 初始化圖
Graph* createGraph(int num_nodes) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->num_nodes = num_nodes;
    graph->adj_list = (Edge**)malloc(num_nodes * sizeof(Edge*));
    for (int i = 0; i < num_nodes; i++) {
        graph->adj_list[i] = NULL;
    }
    return graph;
}

// 添加邊 (u -> v, weight)
void addEdge(Graph* graph, int u, int v, int weight) {
    Edge* edge = (Edge*)malloc(sizeof(Edge));
    edge->to = v;
    edge->weight = weight;
    edge->next = graph->adj_list[u];
    graph->adj_list[u] = edge;
}

// 初始化優先佇列
MinHeap* createMinHeap(int capacity) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->nodes = (MinHeapNode*)malloc(capacity * sizeof(MinHeapNode));
    heap->position = (int*)malloc(capacity * sizeof(int));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

// 交換優先佇列中的兩個節點
void swapMinHeapNodes(MinHeapNode* a, MinHeapNode* b) {
    MinHeapNode temp = *a;
    *a = *b;
    *b = temp;
}

// 堆化操作（向下調整）
void minHeapify(MinHeap* heap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < heap->size && heap->nodes[left].distance < heap->nodes[smallest].distance) {
        smallest = left;
    }

    if (right < heap->size && heap->nodes[right].distance < heap->nodes[smallest].distance) {
        smallest = right;
    }

    if (smallest != idx) {
        // 更新位置
        heap->position[heap->nodes[smallest].vertex] = idx;
        heap->position[heap->nodes[idx].vertex] = smallest;

        // 交換節點
        swapMinHeapNodes(&heap->nodes[smallest], &heap->nodes[idx]);

        minHeapify(heap, smallest);
    }
}

// 從優先佇列中提取最小值
MinHeapNode extractMin(MinHeap* heap) {
    MinHeapNode root = heap->nodes[0];
    MinHeapNode last = heap->nodes[--heap->size];

    heap->nodes[0] = last;

    heap->position[last.vertex] = 0;
    minHeapify(heap, 0);

    return root;
}

// 更新優先佇列中的值
void decreaseKey(MinHeap* heap, int vertex, int distance) {
    int i = heap->position[vertex];
    heap->nodes[i].distance = distance;

    while (i > 0 && heap->nodes[i].distance < heap->nodes[(i - 1) / 2].distance) {
        heap->position[heap->nodes[i].vertex] = (i - 1) / 2;
        heap->position[heap->nodes[(i - 1) / 2].vertex] = i;
        swapMinHeapNodes(&heap->nodes[i], &heap->nodes[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// 檢查優先佇列是否為空
bool isEmpty(MinHeap* heap) {
    return heap->size == 0;
}

// Dijkstra 演算法
void dijkstra(Graph* graph, int source) {
    int num_nodes = graph->num_nodes;
    int* distances = (int*)malloc(num_nodes * sizeof(int));
    MinHeap* heap = createMinHeap(num_nodes);

    // 初始化距離和優先佇列
    for (int i = 0; i < num_nodes; i++) {
        distances[i] = INT_MAX;
        heap->nodes[i].vertex = i;
        heap->nodes[i].distance = INT_MAX;
        heap->position[i] = i;
    }

    // 起點的距離為 0
    distances[source] = 0;
    decreaseKey(heap, source, 0);

    heap->size = num_nodes;

    // 處理所有節點
    while (!isEmpty(heap)) {
        MinHeapNode min_node = extractMin(heap);
        int u = min_node.vertex;

        // 遍歷相鄰節點
        Edge* edge = graph->adj_list[u];
        while (edge != NULL) {
            int v = edge->to;
            int weight = edge->weight;

            // 如果找到更短的路徑，更新距離
            if (heap->position[v] < heap->size && distances[u] != INT_MAX && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                decreaseKey(heap, v, distances[v]);
            }

            edge = edge->next;
        }
    }

    // 打印結果
    printf("Vertex\tDistance from Source\n");
    for (int i = 0; i < num_nodes; i++) {
        printf("%d\t%d\n", i, distances[i]);
    }

    free(distances);
    free(heap->nodes);
    free(heap->position);
    free(heap);
}

// 主函數
int main() {
    int num_nodes = 6;
    Graph* graph = createGraph(num_nodes);

    // 添加邊
    addEdge(graph, 0, 1, 4);
    addEdge(graph, 0, 2, 4);
    addEdge(graph, 1, 2, 2);
    addEdge(graph, 1, 3, 5);
    addEdge(graph, 2, 3, 8);
    addEdge(graph, 2, 4, 2);
    addEdge(graph, 3, 4, 6);
    addEdge(graph, 4, 5, 3);

    dijkstra(graph, 0);

    // 清理記憶體
    for (int i = 0; i < num_nodes; i++) {
        Edge* edge = graph->adj_list[i];
        while (edge) {
            Edge* temp = edge;
            edge = edge->next;
            free(temp);
        }
    }
    free(graph->adj_list);
    free(graph);

    return 0;
}
