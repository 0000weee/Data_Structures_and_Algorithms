#include <stdio.h>
#include <stdlib.h>

// 定義單向鏈結串列的節點
typedef struct node_t {
    int data;              // 資料
    struct node_t* next;   // 指向下一個節點
} node_t;

// 定義鏈結串列結構
typedef struct linked_list_t {
    node_t* head;          // 指向第一個節點
    int size;              // 紀錄節點數量
} linked_list_t;

linked_list_t* list_create() {
    linked_list_t* list = (linked_list_t*)malloc(sizeof(linked_list_t));
    list->head = NULL;
    list->size = 0;
    return list;
}

void list_insert_front(linked_list_t* list, int value) {
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    new_node->data = value;
    new_node->next = list->head;
    list->head = new_node;
    list->size++;
}

void list_insert_back(linked_list_t* list, int value) {
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    new_node->data = value;
    new_node->next = NULL;

    if (list->head == NULL) {
        // 如果鏈結串列為空
        list->head = new_node;
    } else {
        // 找到最後一個節點
        node_t* current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
    list->size++;
}

void list_delete(linked_list_t* list, int value) {
    node_t* current = list->head;
    node_t* prev = NULL;

    while (current != NULL && current->data != value) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Value %d not found in the list.\n", value);
        return;
    }

    if (prev == NULL) {
        // 刪除頭部節點
        list->head = current->next;
    } else {
        // 刪除中間或尾部節點
        prev->next = current->next;
    }

    free(current);
    list->size--;
}

void list_print(linked_list_t* list) {
    node_t* current = list->head;
    printf("Linked List: ");
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

void list_free(linked_list_t* list) {
    node_t* current = list->head;
    while (current != NULL) {
        node_t* temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
}

int main() {
    linked_list_t* list = list_create();

    // 測試插入
    list_insert_front(list, 10);
    list_insert_front(list, 20);
    list_insert_back(list, 5);
    list_insert_back(list, 15);

    // 打印鏈結串列
    list_print(list);

    // 測試刪除
    list_delete(list, 10);  // 刪除中間節點
    list_delete(list, 20);  // 刪除頭部節點
    list_delete(list, 100); // 刪除不存在的值
    list_print(list);

    // 釋放記憶體
    list_free(list);

    return 0;
}