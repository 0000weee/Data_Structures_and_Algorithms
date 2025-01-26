#include<stdio.h>
#include<stdlib.h>

typedef struct {
    int* data;      // 用於存放堆資料的陣列
    int capacity;   // 堆的容量
    int size;       // 堆中已使用的元素數
} min_heap_t;

min_heap_t* heap_create(int capacity) {
    min_heap_t* heap = (min_heap_t*)malloc(sizeof(min_heap_t));
    heap->data = (int*)malloc(sizeof(int) * capacity);
    heap->capacity = capacity;
    heap->size = 0;
    return heap;
}

void heap_insert(min_heap_t* heap, int key) {
    if (heap->size == heap->capacity) {
        printf("Heap overflow\n");
        return;
    }

    // 插入新元素到末尾
    heap->data[heap->size] = key;
    int i = heap->size;
    heap->size++;

    // 上浮調整
    while (i > 0 && heap->data[i] < heap->data[(i - 1) / 2]) {
        int temp = heap->data[i];
        heap->data[i] = heap->data[(i - 1) / 2];
        heap->data[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}

int heap_extract_min(min_heap_t* heap) {
    if (heap->size <= 0) {
        printf("Heap underflow\n");
        return -1;
    }

    int min = heap->data[0];
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;

    // 下沉調整
    int i = 0;
    while (2 * i + 1 < heap->size) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;

        if (heap->data[left] < heap->data[smallest]) {
            smallest = left;
        }
        if (right < heap->size && heap->data[right] < heap->data[smallest]) {
            smallest = right;
        }
        if (smallest == i) {
            break;
        }

        int temp = heap->data[i];
        heap->data[i] = heap->data[smallest];
        heap->data[smallest] = temp;
        i = smallest;
    }

    return min;
}


int main() {
    min_heap_t* heap = heap_create(10);

    heap_insert(heap, 5);
    heap_insert(heap, 3);
    heap_insert(heap, 8);
    heap_insert(heap, 1);

    printf("Extracted min: %d\n", heap_extract_min(heap));
    printf("Extracted min: %d\n", heap_extract_min(heap));

    free(heap->data);
    free(heap);

    return 0;
}
