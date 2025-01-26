#include <stdio.h>
#define MAX_NUM 100

void merge(int array[], int temp[], int left, int mid, int right);

void bottom_up_merge_sort(int array[], int n) {
    int temp[MAX_NUM]; // 暫存陣列

    for (int width = 1; width < n; width *= 2) {
        for (int i = 0; i < n; i += 2 * width) {
            int left = i;
            int mid = i + width - 1;
            int right = (i + 2 * width - 1 < n) ? (i + 2 * width - 1) : (n - 1);

            if (mid < right) {
                merge(array, temp, left, mid, right);
            }
        }
    }
}

void merge(int array[], int temp[], int left, int mid, int right) {
    int i = left;      // 左子陣列起始點
    int j = mid + 1;   // 右子陣列起始點
    int k = left;      // 暫存陣列起始點

    // 合併左右子陣列
    while (i <= mid && j <= right) {
        if (array[i] <= array[j]) {
            temp[k++] = array[i++];
        } else {
            temp[k++] = array[j++];
        }
    }

    // 複製左子陣列剩餘元素
    while (i <= mid) {
        temp[k++] = array[i++];
    }

    // 複製右子陣列剩餘元素
    while (j <= right) {
        temp[k++] = array[j++];
    }

    // 將排序結果複製回原陣列
    for (i = left; i <= right; i++) {
        array[i] = temp[i];
    }
}

int main() {
    // handle input
    printf("Merge sort, please enter n: \n");
    int sequence[MAX_NUM] = {0};
    int n;
    scanf("%d", &n);

    if (n > MAX_NUM) {
        printf("Error: n exceeds maximum limit of %d\n", MAX_NUM);
        return -1;
    }

    printf("please enter sequence: \n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &sequence[i]);
    }

    // Bottom-Up Merge Sort
    bottom_up_merge_sort(sequence, n);

    printf("sorted sequence: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", sequence[i]);
    }
    printf("\n");

    return 0;
}
