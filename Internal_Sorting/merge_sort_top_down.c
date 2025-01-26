#include <stdio.h>
#define MAX_NUM 100

void merge_sort(int array[], int temp[], int left, int right);
void merge(int array[], int temp[], int left, int mid, int right);

int main() {
    // handle input
    printf("Merge sort, please enter n: \n");
    int sequence[MAX_NUM] = {0};
    int temp[MAX_NUM] = {0}; // 暫存陣列
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
    
    // Top-down merge sort
    merge_sort(sequence, temp, 0, n - 1);
    
    printf("sorted sequence: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", sequence[i]);
    }
    printf("\n");

    return 0;
}

void merge_sort(int array[], int temp[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort(array, temp, left, mid);      // Sort left half
        merge_sort(array, temp, mid + 1, right); // Sort right half
        merge(array, temp, left, mid, right);   // Merge the two halves
    }
}

void merge(int array[], int temp[], int left, int mid, int right) {
    int i = left;      // Starting index for left subarray
    int j = mid + 1;   // Starting index for right subarray
    int k = left;      // Starting index to place sorted elements in temp array

    // Merge the two subarrays into temp[]
    while (i <= mid && j <= right) {
        if (array[i] <= array[j]) {
            temp[k++] = array[i++];
        } else {
            temp[k++] = array[j++];
        }
    }

    // Copy remaining elements from left subarray, if any
    while (i <= mid) {
        temp[k++] = array[i++];
    }

    // Copy remaining elements from right subarray, if any
    while (j <= right) {
        temp[k++] = array[j++];
    }

    // Copy sorted elements back into the original array
    for (i = left; i <= right; i++) {
        array[i] = temp[i];
    }
}
