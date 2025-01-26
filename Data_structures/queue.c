#include <stdio.h>
#include <stdlib.h>

// 透過「 循環陣列（circular buffer）」來避免資料移動

typedef struct queue_t {
    int* data;       // 儲存隊列資料的陣列
    int capacity;    // 總容量
    int size;        // 目前隊列大小
    int front;       // 指向隊首的索引
    int rear;        // 指向隊尾的索引
} queue_t;

queue_t* queue_create(int capacity) {
    queue_t* queue = (queue_t*)malloc(sizeof(queue_t));
    queue->data = (int*)malloc(sizeof(int) * capacity);
    queue->capacity = capacity;
    queue->size = 0;
    queue->front = 0;
    queue->rear = -1;
    return queue;
}

int queue_is_full(queue_t* queue) {
    return queue->size == queue->capacity;
}

int queue_is_empty(queue_t* queue) {
    return queue->size == 0;
}

// 入列 (Enqueue)
void queue_enqueue(queue_t* queue, int value) {
    if (queue_is_full(queue)) {
        printf("Queue is full, cannot enqueue %d.\n", value);
        return;
    }

    queue->rear = (queue->rear + 1) % queue->capacity; // 環繞到起始位置
    queue->data[queue->rear] = value;
    queue->size++;
}

// 出列 (Dequeue)
int queue_dequeue(queue_t* queue) {
    if (queue_is_empty(queue)) {
        printf("Queue is empty, cannot dequeue.\n");
        return -1; // 特殊值，表示失敗
    }

    int value = queue->data[queue->front];
    queue->front = (queue->front + 1) % queue->capacity; // 環繞到起始位置
    queue->size--;
    return value;
}

// 讀取第一個元素，但不刪除它
int queue_peek(queue_t* queue) {
    if (queue_is_empty(queue)) {
        printf("Queue is empty, nothing to peek.\n");
        return -1; // 特殊值，表示失敗
    }

    return queue->data[queue->front];
}

void queue_free(queue_t* queue) {
    free(queue->data);
    free(queue);
}

// 測試
int main() {
    queue_t* queue = queue_create(5); // 創建容量為 5 的隊列

    queue_enqueue(queue, 10);
    queue_enqueue(queue, 20);
    queue_enqueue(queue, 30);
    queue_enqueue(queue, 40);
    queue_enqueue(queue, 50);

    // 嘗試插入超出容量
    queue_enqueue(queue, 60);

    // 印出隊首元素
    printf("Front element: %d\n", queue_peek(queue));

    // 逐一移除元素
    while (!queue_is_empty(queue)) {
        printf("Dequeued: %d\n", queue_dequeue(queue));
    }

    // 嘗試在空隊列中出列
    queue_dequeue(queue);

    // 釋放隊列
    queue_free(queue);

    return 0;
}
