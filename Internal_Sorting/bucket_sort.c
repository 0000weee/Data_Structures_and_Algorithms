#include <stdio.h>
#include <stdlib.h>

#define MAX_NUM 100 // 最大數列大小
#define BUCKET_COUNT 10 // 預設桶子的數量

// 篩選桶子節點的結構
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// 將節點插入桶子中，並保持桶子內數據排序
void insert_sorted(Node** bucket, int value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = value;
    new_node->next = NULL;

    // 插入到適當位置，保持桶子內排序
    if (*bucket == NULL || (*bucket)->data >= value) {
        new_node->next = *bucket;
        *bucket = new_node;
    } else {
        Node* current = *bucket;
        while (current->next != NULL && current->next->data < value) {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}

// 釋放桶子的記憶體
void free_buckets(Node** buckets, int bucket_count) {
    for (int i = 0; i < bucket_count; i++) {
        Node* current = buckets[i];
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
}

// Bucket Sort 主函式
void bucket_sort(int array[], int n) {
    if (n <= 0) return;

    // 初始化桶子陣列
    Node* buckets[BUCKET_COUNT] = {NULL};

    // 找到陣列中的最大值和最小值以確定範圍
    int max_val = array[0];
    int min_val = array[0];
    for (int i = 1; i < n; i++) {
        if (array[i] > max_val) max_val = array[i];
        if (array[i] < min_val) min_val = array[i];
    }

    // 計算範圍內的桶子大小
    int range = max_val - min_val + 1;
    int bucket_size = (range + BUCKET_COUNT - 1) / BUCKET_COUNT; // 每個桶子的大小

    // 將元素分配到桶子中
    for (int i = 0; i < n; i++) {
        int bucket_index = (array[i] - min_val) / bucket_size; // 確定桶子索引
        insert_sorted(&buckets[bucket_index], array[i]);
    }

    // 合併所有桶子
    int index = 0;
    for (int i = 0; i < BUCKET_COUNT; i++) {
        Node* current = buckets[i];
        while (current != NULL) {
            array[index++] = current->data;
            current = current->next;
        }
    }

    // 釋放桶子的記憶體
    free_buckets(buckets, BUCKET_COUNT);
}

int main() {
    // 輸入
    printf("Bucket sort, please enter n: \n");
    int sequence[MAX_NUM] = {0};
    int n;
    scanf("%d", &n);

    if (n > MAX_NUM) {
        printf("Error: n exceeds maximum limit of %d\n", MAX_NUM);
        return -1;
    }

    printf("Please enter sequence: \n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &sequence[i]);
    }

    // Bucket Sort
    bucket_sort(sequence, n);

    printf("sorted sequence: ");
    for(int i=0; i<n; i++){
        printf("%d ", sequence[i]);
    }
    printf("\n");
}