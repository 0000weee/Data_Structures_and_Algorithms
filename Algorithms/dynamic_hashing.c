/*
Note:
    1.初始大小設定：開始時使用小的哈希表大小，通常是質數。
    2.動態擴展與縮小：
    3.當負載因子（Load Factor，填充率）超過閾值時，將哈希表擴展為更大的大小。
    4.當負載因子過低時，可以選擇縮小哈希表。
    5.重新散列 (Rehashing)：在表大小改變時，重新計算所有元素的哈希值並插入新表。
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_SIZE 4     // 初始哈希表大小
#define LOAD_FACTOR 0.75   // 負載因子的上限
#define SHRINK_FACTOR 0.25 // 負載因子的下限

// 哈希表節點
typedef struct Node {
    char *key;
    int value;
    struct Node *next; // 處理碰撞的鏈結
} Node;

// 哈希表結構
typedef struct HashTable {
    Node **buckets;   // 指向哈希桶的陣列
    int size;         // 當前哈希表的大小（桶數量）
    int count;        // 當前儲存的元素數量
} HashTable;

// 函數宣告
HashTable *createHashTable(int size);
void freeHashTable(HashTable *table);
unsigned int hashFunction(const char *key, int size);
void insert(HashTable *table, const char *key, int value);
int search(HashTable *table, const char *key, int *value);
void deleteKey(HashTable *table, const char *key);
void resize(HashTable *table, int newSize);

// 主函數
int main() {
    HashTable *table = createHashTable(INITIAL_SIZE);

    insert(table, "Alice", 25);
    insert(table, "Bob", 30);
    insert(table, "Charlie", 35);
    insert(table, "David", 40);

    int value;
    if (search(table, "Bob", &value)) {
        printf("Bob's value: %d\n", value);
    } else {
        printf("Bob not found.\n");
    }

    deleteKey(table, "Charlie");
    if (search(table, "Charlie", &value)) {
        printf("Charlie's value: %d\n", value);
    } else {
        printf("Charlie not found.\n");
    }

    freeHashTable(table);
    return 0;
}

// 創建哈希表
HashTable *createHashTable(int size) {
    HashTable *table = (HashTable *)malloc(sizeof(HashTable));
    table->size = size;
    table->count = 0;
    table->buckets = (Node **)calloc(size, sizeof(Node *));
    return table;
}

// 釋放哈希表
void freeHashTable(HashTable *table) {
    for (int i = 0; i < table->size; i++) {
        Node *node = table->buckets[i];
        while (node) {
            Node *temp = node;
            node = node->next;
            free(temp->key);
            free(temp);
        }
    }
    free(table->buckets);
    free(table);
}

// 哈希函數 (簡單的字串哈希)
unsigned int hashFunction(const char *key, int size) {
    unsigned int hash = 0;
    while (*key) {
        hash = (hash * 31 + *key) % size; // 31 是質數
        key++;
    }
    return hash;
}

// 插入元素
void insert(HashTable *table, const char *key, int value) {
    if ((float)table->count / table->size > LOAD_FACTOR) {
        resize(table, table->size * 2); // 擴展
    }

    unsigned int index = hashFunction(key, table->size);
    Node *node = table->buckets[index];
    while (node) {
        if (strcmp(node->key, key) == 0) {
            node->value = value; // 更新值
            return;
        }
        node = node->next;
    }

    // 新節點
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->key = strdup(key);
    newNode->value = value;
    newNode->next = table->buckets[index];
    table->buckets[index] = newNode;
    table->count++;
}

// 搜索元素
int search(HashTable *table, const char *key, int *value) {
    unsigned int index = hashFunction(key, table->size);
    Node *node = table->buckets[index];
    while (node) {
        if (strcmp(node->key, key) == 0) {
            *value = node->value;
            return 1; // 找到
        }
        node = node->next;
    }
    return 0; // 未找到
}

// 刪除元素
void deleteKey(HashTable *table, const char *key) {
    unsigned int index = hashFunction(key, table->size);
    Node *node = table->buckets[index];
    Node *prev = NULL;

    while (node) {
        if (strcmp(node->key, key) == 0) {
            if (prev) {
                prev->next = node->next;
            } else {
                table->buckets[index] = node->next;
            }
            free(node->key);
            free(node);
            table->count--;
            if ((float)table->count / table->size < SHRINK_FACTOR && table->size > INITIAL_SIZE) {
                resize(table, table->size / 2); // 縮小
            }
            return;
        }
        prev = node;
        node = node->next;
    }
}

// 調整哈希表大小
void resize(HashTable *table, int newSize) {
    Node **oldBuckets = table->buckets;
    int oldSize = table->size;

    table->buckets = (Node **)calloc(newSize, sizeof(Node *));
    table->size = newSize;
    table->count = 0;

    for (int i = 0; i < oldSize; i++) {
        Node *node = oldBuckets[i];
        while (node) {
            insert(table, node->key, node->value);
            Node *temp = node;
            node = node->next;
            free(temp->key);
            free(temp);
        }
    }
    free(oldBuckets);
}
