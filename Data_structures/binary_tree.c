#include <stdio.h>
#include <stdlib.h>

// 定義二元樹的節點結構
typedef struct binary_tree_node {
    int data;                           // 節點儲存的值
    struct binary_tree_node* left;      // 左子樹
    struct binary_tree_node* right;     // 右子樹
} binary_tree_node;

// 函數宣告
binary_tree_node* create_node(int data);
binary_tree_node* insert_node(binary_tree_node* root, int data);
void inorder_traversal(binary_tree_node* root);
void free_tree(binary_tree_node* root);

int main() {
    // 建立根節點並插入資料
    binary_tree_node* root = NULL;
    root = insert_node(root, 10);
    root = insert_node(root, 5);
    root = insert_node(root, 15);
    root = insert_node(root, 3);
    root = insert_node(root, 7);

    // 中序遍歷輸出
    printf("Inorder Traversal: ");
    inorder_traversal(root);
    printf("\n");

    // 釋放記憶體
    free_tree(root);

    return 0;
}

// 創建新節點
binary_tree_node* create_node(int data) {
    binary_tree_node* new_node = (binary_tree_node*)malloc(sizeof(binary_tree_node));
    if (!new_node) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

// 插入節點到二元樹
binary_tree_node* insert_node(binary_tree_node* root, int data) {
    if (root == NULL) {
        return create_node(data);  // 如果樹是空的，直接創建節點
    }
    if (data < root->data) {
        root->left = insert_node(root->left, data);  // 插入到左子樹
    } else {
        root->right = insert_node(root->right, data); // 插入到右子樹
    }
    return root;
}

// 中序遍歷 (Inorder Traversal)
void inorder_traversal(binary_tree_node* root) {
    if (root == NULL) {
        return;
    }
    inorder_traversal(root->left);       // 遍歷左子樹
    printf("%d ", root->data);          // 輸出當前節點
    inorder_traversal(root->right);     // 遍歷右子樹
}

// 釋放整棵樹的記憶體
void free_tree(binary_tree_node* root) {
    if (root == NULL) {
        return;
    }
    free_tree(root->left);  // 釋放左子樹
    free_tree(root->right); // 釋放右子樹
    free(root);             // 釋放當前節點
}
