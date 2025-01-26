#include<stdio.h>
#define MAX_NUM 100

void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main(){
    // handle input
    printf("select sort , please scanf n: \n");
    int sequence[MAX_NUM] = {0};
    int n;
    scanf("%d", &n);
    printf("please scanf sequence: \n");

    if (n > MAX_NUM) {
        printf("Error: n exceeds maximum limit of %d\n", MAX_NUM);
        return -1;
    }

    for(int i=0; i<n; i++){
        scanf("%d", &sequence[i]);
    }
    
    // select sorting
    //首先在未排序序列中找到最小元素，存放到排序序列的起始位置
    //再從剩餘未排序元素中繼續尋找最小元素，然後放到已排序序列的末尾。*/
    for(int i=0; i<n; i++){
        int min_index = i;
        for(int j=i; j<n; j++){
            if(sequence[j] < sequence[min_index]){
                min_index = j;
            }
        }
        swap(&sequence[i], &sequence[min_index]);
    }
    
    
    printf("sorted sequence: ");
    for(int i=0; i<n; i++){
        printf("%d ", sequence[i]);
    }
    printf("\n");
}