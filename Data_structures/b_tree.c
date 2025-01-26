#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//假設 B-Tree 的階數為 3（即每個節點最多有 3 個子節點和 2 個鍵值）。
#define MAX_KEYS 3         // B-Tree 階數 (階數為 t 時，最多鍵數為 2t-1)
#define MIN_KEYS (MAX_KEYS / 2)

// B-Tree 節點結構
typedef struct btree_node {
    int keys[MAX_KEYS];                 // 節點中的鍵值
    struct btree_node* children[MAX_KEYS + 1]; // 子節點指標
    int num_keys;                       // 節點中的有效鍵數
    bool is_leaf;                       // 是否為葉節點
} btree_node_t;

// 函數宣告
btree_node_t* create_node(bool is_leaf);
void insert_key(btree_node_t** root, int key);
void split_child(btree_node_t* parent, int index, btree_node_t* child);
void traverse(btree_node_t* root);
void free_tree(btree_node_t* root);

// 主程式
int main() {
    btree_node_t* root = NULL;

    // 插入一些鍵值
    insert_key(&root, 10);
    insert_key(&root, 20);
    insert_key(&root, 5);
    insert_key(&root, 6);
    insert_key(&root, 12);
    insert_key(&root, 30);
    insert_key(&root, 7);
    insert_key(&root, 17);

    // 遍歷 B-Tree
    printf("B-Tree Traversal: ");
    traverse(root);
    printf("\n");

    // 釋放記憶體
    free_tree(root);

    return 0;
}

// 創建新節點
btree_node_t* create_node(bool is_leaf) {
    btree_node_t* node = (btree_node_t*)malloc(sizeof(btree_node_t));
    node->is_leaf = is_leaf;
    node->num_keys = 0;
    for (int i = 0; i < MAX_KEYS + 1; i++) {
        node->children[i] = NULL;
    }
    return node;
}

// 插入鍵值到 B-Tree
void insert_key(btree_node_t** root, int key) {
    if (*root == NULL) {
        // 如果樹是空的，創建根節點
        *root = create_node(true);
        (*root)->keys[0] = key;
        (*root)->num_keys = 1;
        return;
    }

    btree_node_t* current = *root;

    // 如果根節點已滿，需進行分裂
    if (current->num_keys == MAX_KEYS) {
        btree_node_t* new_root = create_node(false); // 新的根節點
        new_root->children[0] = current;

        // 分裂子節點
        split_child(new_root, 0, current);

        // 決定插入到左子樹還是右子樹
        int i = (new_root->keys[0] < key) ? 1 : 0;
        insert_key(&new_root->children[i], key);

        *root = new_root; // 更新根節點
    } else {
        // 如果根節點未滿，直接插入鍵值
        if (current->is_leaf) {
            // 在葉節點插入鍵值
            int i = current->num_keys - 1;
            while (i >= 0 && current->keys[i] > key) {
                current->keys[i + 1] = current->keys[i];
                i--;
            }
            current->keys[i + 1] = key;
            current->num_keys++;
        } else {
            // 找到應插入的子節點
            int i = current->num_keys - 1;
            while (i >= 0 && current->keys[i] > key) {
                i--;
            }
            i++;

            // 如果子節點已滿，先分裂
            if (current->children[i]->num_keys == MAX_KEYS) {
                split_child(current, i, current->children[i]);

                // 確認插入到左還是右
                if (current->keys[i] < key) {
                    i++;
                }
            }
            insert_key(&current->children[i], key);
        }
    }
}

// 分裂子節點
void split_child(btree_node_t* parent, int index, btree_node_t* child) {
    int mid = MAX_KEYS / 2;

    // 創建新節點
    btree_node_t* new_child = create_node(child->is_leaf);
    new_child->num_keys = MAX_KEYS - mid - 1;

    // 將鍵值從子節點移到新節點
    for (int i = 0; i < new_child->num_keys; i++) {
        new_child->keys[i] = child->keys[mid + 1 + i];
    }

    // 如果不是葉節點，還需移動子指標
    if (!child->is_leaf) {
        for (int i = 0; i <= new_child->num_keys; i++) {
            new_child->children[i] = child->children[mid + 1 + i];
        }
    }

    child->num_keys = mid;

    // 在父節點插入新的鍵值
    for (int i = parent->num_keys; i > index; i--) {
        parent->children[i + 1] = parent->children[i];
        parent->keys[i] = parent->keys[i - 1];
    }
    parent->children[index + 1] = new_child;
    parent->keys[index] = child->keys[mid];
    parent->num_keys++;
}

// 遍歷 B-Tree
void traverse(btree_node_t* root) {
    if (root == NULL) return;

    for (int i = 0; i < root->num_keys; i++) {
        traverse(root->children[i]);
        printf("%d ", root->keys[i]);
    }
    traverse(root->children[root->num_keys]);
}

// 釋放 B-Tree 記憶體
void free_tree(btree_node_t* root) {
    if (root == NULL) return;

    for (int i = 0; i <= root->num_keys; i++) {
        free_tree(root->children[i]);
    }
    free(root);
}
