#include <stdio.h>
#define MAX_NUM 100

// 建立最大堆
void heapify(int array[], int n, int i) {
    int largest = i; // 初始化 largest 為根節點
    int left = 2 * i + 1; // 左子節點
    int right = 2 * i + 2; // 右子節點

    // 如果左子節點比根節點大
    if (left < n && array[left] > array[largest]) {
        largest = left;
    }

    // 如果右子節點比根節點大
    if (right < n && array[right] > array[largest]) {
        largest = right;
    }

    // 如果 largest 不是根節點
    if (largest != i) {
        // 交換根節點和 largest
        int temp = array[i];
        array[i] = array[largest];
        array[largest] = temp;

        // 重新調整堆積
        heapify(array, n, largest);
    }
}

// 堆積排序
void heap_sort(int array[], int n) {
    // 建立最大堆
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(array, n, i);
    }

    // 反覆交換堆頂元素與最後一個元素
    for (int i = n - 1; i > 0; i--) {
        // 交換根節點（最大值）和最後一個元素
        int temp = array[0];
        array[0] = array[i];
        array[i] = temp;

        // 重新調整堆積
        heapify(array, i, 0);
    }
}

int main() {
    // handle input
    printf("Heap sort, please enter n: \n");
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

    // Heap Sort
    heap_sort(sequence, n);

    printf("Sorted sequence: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", sequence[i]);
    }
    printf("\n");

    return 0;
}
