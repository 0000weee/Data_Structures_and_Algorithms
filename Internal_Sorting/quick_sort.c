#include <stdio.h>
#define MAX_NUM 100

int partition(int array[], int left, int right, int pivot_index);
void swap(int* a, int* b);
void quick_sort(int array[], int left, int right);

int main() {
    // handle input
    printf("quick sort, please enter n: \n");
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
    
    quick_sort(sequence, 0, n - 1);
    
    printf("sorted sequence: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", sequence[i]);
    }
    printf("\n");

    return 0;
}

int partition(int array[], int left, int right, int pivot_index) {
    int pivot_value = array[pivot_index];
    swap(&array[pivot_index], &array[right]); // Move pivot to end
    int store_index = left;
    for (int i = left; i < right; i++) {
        if (array[i] < pivot_value) {
            swap(&array[store_index], &array[i]);
            store_index++;
        }
    }
    swap(&array[right], &array[store_index]); // Move pivot to its final place
    return store_index;
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void quick_sort(int array[], int left, int right) {
    if (left < right) {
        int pivot_index = (left + right) / 2; // Choose middle element as pivot
        int new_pivot = partition(array, left, right, pivot_index);
        quick_sort(array, left, new_pivot - 1);
        quick_sort(array, new_pivot + 1, right);
    }
}
