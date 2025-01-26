#include <stdio.h>
#include <stdlib.h>

// 定義堆疊結構
typedef struct stack_t {
    int* data;       // 儲存堆疊元素的陣列
    int capacity;    // 堆疊的容量
    int top;         // 指向堆疊頂部元素的索引
} stack_t;

stack_t* stack_create(int capacity) {
    stack_t* stack = (stack_t*)malloc(sizeof(stack_t));
    stack->data = (int*)malloc(sizeof(int) * capacity);
    stack->capacity = capacity;
    stack->top = -1; // 空堆疊時，`top` 設為 -1
    return stack;
}

int stack_is_full(stack_t* stack) {
    return stack->top == stack->capacity - 1;
}

int stack_is_empty(stack_t* stack) {
    return stack->top == -1;
}

void stack_push(stack_t* stack, int value) {
    if (stack_is_full(stack)) {
        printf("Stack is full, cannot push %d.\n", value);
        return;
    }
    stack->data[++stack->top] = value; // 將元素壓入堆疊
}

int stack_pop(stack_t* stack) {
    if (stack_is_empty(stack)) {
        printf("Stack is empty, cannot pop.\n");
        return -1; // 特殊值，表示失敗
    }
    return stack->data[stack->top--];
}

int stack_peek(stack_t* stack) {
    if (stack_is_empty(stack)) {
        printf("Stack is empty, nothing to peek.\n");
        return -1; // 特殊值，表示失敗
    }
    return stack->data[stack->top];
}

void stack_free(stack_t* stack) {
    free(stack->data);
    free(stack);
}

// 測試程式
int main() {
    stack_t* stack = stack_create(5); // 創建容量為 5 的堆疊

    // 測試壓入
    stack_push(stack, 10);
    stack_push(stack, 20);
    stack_push(stack, 30);
    stack_push(stack, 40);
    stack_push(stack, 50);

    // 嘗試push超出容量
    stack_push(stack, 60);

    // 查看堆疊頂部元素
    printf("Top element: %d\n", stack_peek(stack));

    // 測試pop
    while (!stack_is_empty(stack)) {
        printf("Popped: %d\n", stack_pop(stack));
    }

    // 嘗試pop空堆疊
    stack_pop(stack);

    // 釋放堆疊
    stack_free(stack);

    return 0;
}
