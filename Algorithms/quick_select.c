#include <stdio.h>
#include <stdlib.h>

// 交換兩個數值
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Lomuto Partition，將 pivot 放到正確位置，並回傳 index
int partition(int array[], int left, int right) {
    int pivot = array[right]; // 選擇最後一個元素作為 pivot
    int i = left; // i 是小於 pivot 的元素位置
    
    for (int j = left; j < right; j++) {
        if (array[j] < pivot) {
            swap(&array[i], &array[j]);
            i++;
        }
    }
    swap(&array[i], &array[right]); // 把 pivot 放到正確位置
    return i;
}

// Quickselect 主函式，找出第 k 小的元素
int quickselect(int array[], int left, int right, int k) {
    if (left == right) return array[left]; // 陣列只剩一個元素

    // 取得 partition 後 pivot 的位置
    int pivot_index = partition(array, left, right);

    if (pivot_index == k) {
        return array[pivot_index]; // 找到第 k 小的數字
    } else if (pivot_index > k) {
        return quickselect(array, left, pivot_index - 1, k); // 遞迴左半部
    } else {
        return quickselect(array, pivot_index + 1, right, k); // 遞迴右半部
    }
}

int main() {
    // 讀取輸入
    printf("Quickselect, please enter n: \n");
    int n;
    scanf("%d", &n);
    
    int array[n];
    printf("Please enter sequence: \n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &array[i]);
    }
    
    int k;
    printf("Enter k (1-based index): ");
    scanf("%d", &k);
    
    if (k < 1 || k > n) {
        printf("Error: k must be between 1 and %d\n", n);
        return -1;
    }

    // 呼叫 Quickselect 找出第 k 小的元素
    int result = quickselect(array, 0, n - 1, k - 1);

    printf("The %d-th smallest element is: %d\n", k, result);
    return 0;
}

/*
程式邏輯
選擇 pivot（基準值）

這裡使用 Lomuto Partition，選擇最後一個元素當 pivot。
分區（Partition）

小於 pivot 的值放左邊，大於 pivot 的值放右邊，並回傳 pivot 最終位置。
遞迴 Quickselect

若 pivot_index == k，表示找到了第 k 小的數字。
若 pivot_index > k，則只在左半部分搜尋。
若 pivot_index < k，則在右半部分搜尋。

時間與空間複雜度
最佳	平均	最差
O(n)	O(n)	O(n²)
平均時間複雜度 是 O(n)，因為我們每次只處理一半的資料。
最壞情況（已排序陣列 + 最小/最大 pivot）變成 O(n²)。
空間複雜度 是 O(1)（原地排序，不使用額外記憶體）。
優化方向
隨機選擇 Pivot

避免最壞情況（已排序陣列）。
swap(&array[right], &array[left + rand() % (right - left + 1)]);
Median-of-Three

選擇 (left, middle, right) 三個元素的中位數當 pivot。
非遞迴 Quickselect

用 while 迴圈代替遞迴，減少遞迴深度。
總結
Quickselect 適用於找出第 k 小的元素，而非完全排序。
比 QuickSort 更快，因為它 只遞迴一側，時間複雜度平均 O(n)。
可能的優化：隨機 pivot、median-of-three、非遞迴。
*/