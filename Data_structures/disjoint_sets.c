// 路徑壓縮（Path Compression）：在 find 函數中，將查詢過程中所有節點直接連接到根節點，減少未來的查詢深度。
// 按秩合併（Union by Rank）：在 union_sets 函數中，根據樹的高度（秩）決定合併方向，保持樹的平衡性。

#include <stdio.h>
#include <stdlib.h>

// Disjoint Sets 結構
typedef struct {
    int* parent;   // 父節點指標陣列
    int* rank;     // 節點的秩（用於優化合併）
    int size;      // 元素總數
} disjoint_sets_t;

// 函數宣告
disjoint_sets_t* create_disjoint_sets(int n);
int find(disjoint_sets_t* ds, int x);
void union_sets(disjoint_sets_t* ds, int x, int y);
void free_disjoint_sets(disjoint_sets_t* ds);

// 主程式
int main() {
    int n = 10; // 初始化 10 個元素
    disjoint_sets_t* ds = create_disjoint_sets(n);

    // 合併一些集合
    union_sets(ds, 1, 2);
    union_sets(ds, 3, 4);
    union_sets(ds, 2, 4);

    // 測試查詢
    printf("Find(1): %d\n", find(ds, 1));
    printf("Find(3): %d\n", find(ds, 3));
    printf("Find(5): %d\n", find(ds, 5));

    // 釋放記憶體
    free_disjoint_sets(ds);
    return 0;
}

// 創建 Disjoint Sets
disjoint_sets_t* create_disjoint_sets(int n) {
    disjoint_sets_t* ds = (disjoint_sets_t*)malloc(sizeof(disjoint_sets_t));
    ds->parent = (int*)malloc(n * sizeof(int));
    ds->rank = (int*)malloc(n * sizeof(int));
    ds->size = n;

    // 初始化每個元素為自己的父節點，秩為 0
    for (int i = 0; i < n; i++) {
        ds->parent[i] = i;
        ds->rank[i] = 0;
    }
    return ds;
}

// 查詢元素 x 所屬的集合（帶路徑壓縮）
int find(disjoint_sets_t* ds, int x) {
    if (ds->parent[x] != x) {
        // 路徑壓縮：將 x 直接連接到根節點
        ds->parent[x] = find(ds, ds->parent[x]);
    }
    return ds->parent[x];
}

// 合併兩個集合（按秩合併）
void union_sets(disjoint_sets_t* ds, int x, int y) {
    int root_x = find(ds, x);
    int root_y = find(ds, y);

    if (root_x != root_y) {
        // 按秩合併：將秩較低的樹連接到秩較高的樹
        if (ds->rank[root_x] < ds->rank[root_y]) {
            ds->parent[root_x] = root_y;
        } else if (ds->rank[root_x] > ds->rank[root_y]) {
            ds->parent[root_y] = root_x;
        } else {
            ds->parent[root_y] = root_x;
            ds->rank[root_x]++;
        }
    }
}

// 釋放 Disjoint Sets 的記憶體
void free_disjoint_sets(disjoint_sets_t* ds) {
    free(ds->parent);
    free(ds->rank);
    free(ds);
}
