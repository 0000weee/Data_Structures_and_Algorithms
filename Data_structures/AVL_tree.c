// AVL Tree 是一種自平衡的二元搜尋樹，它確保任何節點的左右子樹高度差不超過 1
// 因此在插入和刪除操作後，能夠保持高效的搜尋時間。
/* TODO 1.節點插入
        2.高度更新
        3.平衡因子計算
        4.左旋、右旋操作
        5.AVL 特性維護
*/
#include <stdio.h>
#include <stdlib.h>

// 節點結構
typedef struct avl_node_t {
    int key;                     // 節點鍵值
    int height;                  // 節點高度
    struct avl_node_t* left;     // 左子節點
    struct avl_node_t* right;    // 右子節點
} avl_node_t;

// 函數宣告
avl_node_t* create_node(int key);
int get_height(avl_node_t* node);
int get_balance(avl_node_t* node);
avl_node_t* rotate_right(avl_node_t* y);
avl_node_t* rotate_left(avl_node_t* x);
avl_node_t* insert(avl_node_t* node, int key);
void inorder_traversal(avl_node_t* root);
void free_tree(avl_node_t* root);

// 主程式
int main() {
    avl_node_t* root = NULL;

    // 插入一些鍵值
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    // 輸出 AVL Tree 的中序遍歷
    printf("Inorder Traversal of AVL Tree: ");
    inorder_traversal(root);
    printf("\n");

    // 釋放記憶體
    free_tree(root);

    return 0;
}

// 創建節點
avl_node_t* create_node(int key) {
    avl_node_t* node = (avl_node_t*)malloc(sizeof(avl_node_t));
    node->key = key;
    node->height = 1; // 初始高度為 1
    node->left = node->right = NULL;
    return node;
}

// 獲取節點高度
int get_height(avl_node_t* node) {
    return (node == NULL) ? 0 : node->height;
}

// 計算平衡因子
int get_balance(avl_node_t* node) {
    return (node == NULL) ? 0 : get_height(node->left) - get_height(node->right);
}

// 右旋操作
avl_node_t* rotate_right(avl_node_t* y) {
    avl_node_t* x = y->left;
    avl_node_t* T2 = x->right;

    // 旋轉
    x->right = y;
    y->left = T2;

    // 更新高度
    y->height = 1 + ((get_height(y->left) > get_height(y->right)) ? get_height(y->left) : get_height(y->right));
    x->height = 1 + ((get_height(x->left) > get_height(x->right)) ? get_height(x->left) : get_height(x->right));

    return x; // 新的根節點
}

// 左旋操作
avl_node_t* rotate_left(avl_node_t* x) {
    avl_node_t* y = x->right;
    avl_node_t* T2 = y->left;

    // 旋轉
    y->left = x;
    x->right = T2;

    // 更新高度
    x->height = 1 + ((get_height(x->left) > get_height(x->right)) ? get_height(x->left) : get_height(x->right));
    y->height = 1 + ((get_height(y->left) > get_height(y->right)) ? get_height(y->left) : get_height(y->right));

    return y; // 新的根節點
}

// 插入節點
avl_node_t* insert(avl_node_t* node, int key) {
    // Step 1: 標準的 BST 插入
    if (node == NULL) {
        return create_node(key);
    }

    if (key < node->key) {
        node->left = insert(node->left, key);
    } else if (key > node->key) {
        node->right = insert(node->right, key);
    } else {
        return node; // 不允許重複鍵值
    }

    // Step 2: 更新節點高度
    node->height = 1 + ((get_height(node->left) > get_height(node->right)) ? get_height(node->left) : get_height(node->right));

    // Step 3: 計算平衡因子
    int balance = get_balance(node);

    // Step 4: 根據平衡因子進行旋轉調整
    // 左左情況
    if (balance > 1 && key < node->left->key) {
        return rotate_right(node);
    }

    // 右右情況
    if (balance < -1 && key > node->right->key) {
        return rotate_left(node);
    }

    // 左右情況
    if (balance > 1 && key > node->left->key) {
        node->left = rotate_left(node->left);
        return rotate_right(node);
    }

    // 右左情況
    if (balance < -1 && key < node->right->key) {
        node->right = rotate_right(node->right);
        return rotate_left(node);
    }

    return node; // 返回節點（無需旋轉）
}

// 中序遍歷
void inorder_traversal(avl_node_t* root) {
    if (root == NULL) return;

    inorder_traversal(root->left);
    printf("%d ", root->key);
    inorder_traversal(root->right);
}

// 釋放樹記憶體
void free_tree(avl_node_t* root) {
    if (root == NULL) return;

    free_tree(root->left);
    free_tree(root->right);
    free(root);
}
