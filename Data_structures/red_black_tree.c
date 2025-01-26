/*Red-Black Tree 是一種自平衡的二元搜尋樹，具有以下特性：

每個節點非紅即黑。
根節點必為黑色。
所有葉子節點（NIL 節點）為黑色。
紅色節點的子節點必為黑色（即，不能有兩個連續的紅色節點）。
任一節點到其每個葉子節點的所有簡單路徑，包含相同數量的黑色節點。*/
#include <stdio.h>
#include <stdlib.h>

// 節點顏色
typedef enum { RED, BLACK } color_t;

// 節點結構
typedef struct rb_node_t {
    int key;                   // 節點鍵值
    color_t color;             // 節點顏色
    struct rb_node_t* left;    // 左子節點
    struct rb_node_t* right;   // 右子節點
    struct rb_node_t* parent;  // 父節點
} rb_node_t;

// 樹結構
typedef struct rb_tree_t {
    rb_node_t* root;           // 根節點
    rb_node_t* nil;            // 樹的 NIL 節點
} rb_tree_t;

// 函數宣告
rb_tree_t* create_tree();
rb_node_t* create_node(rb_tree_t* tree, int key);
void left_rotate(rb_tree_t* tree, rb_node_t* x);
void right_rotate(rb_tree_t* tree, rb_node_t* y);
void insert(rb_tree_t* tree, int key);
void insert_fixup(rb_tree_t* tree, rb_node_t* z);
void inorder_traversal(rb_tree_t* tree, rb_node_t* root);
void free_tree(rb_tree_t* tree, rb_node_t* root);
void free_rb_tree(rb_tree_t* tree);

// 主程式
int main() {
    rb_tree_t* tree = create_tree();

    // 插入鍵值
    insert(tree, 10);
    insert(tree, 20);
    insert(tree, 30);
    insert(tree, 15);
    insert(tree, 25);
    insert(tree, 5);

    // 輸出中序遍歷
    printf("Inorder Traversal of Red-Black Tree: ");
    inorder_traversal(tree, tree->root);
    printf("\n");

    // 釋放記憶體
    free_rb_tree(tree);
    return 0;
}

// 創建紅黑樹
rb_tree_t* create_tree() {
    rb_tree_t* tree = (rb_tree_t*)malloc(sizeof(rb_tree_t));
    tree->nil = (rb_node_t*)malloc(sizeof(rb_node_t));
    tree->nil->color = BLACK;
    tree->root = tree->nil;
    return tree;
}

// 創建節點
rb_node_t* create_node(rb_tree_t* tree, int key) {
    rb_node_t* node = (rb_node_t*)malloc(sizeof(rb_node_t));
    node->key = key;
    node->color = RED; // 新節點預設為紅色
    node->left = node->right = node->parent = tree->nil;
    return node;
}

// 左旋
void left_rotate(rb_tree_t* tree, rb_node_t* x) {
    rb_node_t* y = x->right;
    x->right = y->left;
    if (y->left != tree->nil) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == tree->nil) {
        tree->root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

// 右旋
void right_rotate(rb_tree_t* tree, rb_node_t* y) {
    rb_node_t* x = y->left;
    y->left = x->right;
    if (x->right != tree->nil) {
        x->right->parent = y;
    }
    x->parent = y->parent;
    if (y->parent == tree->nil) {
        tree->root = x;
    } else if (y == y->parent->right) {
        y->parent->right = x;
    } else {
        y->parent->left = x;
    }
    x->right = y;
    y->parent = x;
}

// 插入節點
void insert(rb_tree_t* tree, int key) {
    rb_node_t* z = create_node(tree, key);
    rb_node_t* y = tree->nil;
    rb_node_t* x = tree->root;

    while (x != tree->nil) {
        y = x;
        if (z->key < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    z->parent = y;
    if (y == tree->nil) {
        tree->root = z;
    } else if (z->key < y->key) {
        y->left = z;
    } else {
        y->right = z;
    }

    z->left = z->right = tree->nil;
    insert_fixup(tree, z);
}

// 插入修正
void insert_fixup(rb_tree_t* tree, rb_node_t* z) {
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            rb_node_t* y = z->parent->parent->right;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    left_rotate(tree, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                right_rotate(tree, z->parent->parent);
            }
        } else {
            rb_node_t* y = z->parent->parent->left;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    right_rotate(tree, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                left_rotate(tree, z->parent->parent);
            }
        }
    }
    tree->root->color = BLACK;
}

// 中序遍歷
void inorder_traversal(rb_tree_t* tree, rb_node_t* root) {
    if (root == tree->nil) return;

    inorder_traversal(tree, root->left);
    printf("%d ", root->key);
    inorder_traversal(tree, root->right);
}

// 釋放記憶體
void free_tree(rb_tree_t* tree, rb_node_t* root) {
    if (root == tree->nil) return;

    free_tree(tree, root->left);
    free_tree(tree, root->right);
    free(root);
}

// 釋放整棵樹
void free_rb_tree(rb_tree_t* tree) {
    free_tree(tree, tree->root);
    free(tree->nil);
    free(tree);
}
