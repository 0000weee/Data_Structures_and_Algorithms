#include <stdio.h>
#define MAX_NUM 100
//stable sort algorithm
//時間複雜度為 𝑂(𝑑⋅(𝑛+𝑘))，其中 𝑑 是數字的最大位數，𝑛 是元素個數，𝑘 是基數

void counting_sort_for_radix(int array[], int n, int exp) {
    int output[MAX_NUM];  // 暫存排序結果
    int count[10] = {0};  // 計數陣列，範圍為 0-9

    // 計算每個數字的出現次數
    for (int i = 0; i < n; i++) {
        int digit = (array[i] / exp) % 10;
        count[digit]++;
    }

    // 更新計數陣列，使其包含位置資訊
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    // 將數字按當前位數排序，填入暫存陣列
    for (int i = n - 1; i >= 0; i--) {
        int digit = (array[i] / exp) % 10;
        output[count[digit] - 1] = array[i];
        count[digit]--;
    }

    // 將排序結果複製回原陣列
    for (int i = 0; i < n; i++) {
        array[i] = output[i];
    }
}

// 基數排序
void radix_sort(int array[], int n) {
    // 找到最大值，確定最大位數
    int max_value = array[0];
    for (int i = 1; i < n; i++) {
        if (array[i] > max_value) {
            max_value = array[i];
        }
    }

    // 從最低有效位 (LSB) 到最高有效位 (MSB) 依次排序
    for (int exp = 1; max_value / exp > 0; exp *= 10) {
        counting_sort_for_radix(array, n, exp);
    }
}

int main() {
    // handle input
    printf("Radix sort, please enter n: \n");
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

    // Radix Sort
    radix_sort(sequence, n);

    printf("Sorted sequence: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", sequence[i]);
    }
    printf("\n");

    return 0;
}
