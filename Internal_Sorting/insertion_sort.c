#include<stdio.h>
#define MAX_NUM 100

int main(){
    // handle input
    printf("insertion sort, please scanf n: \n");
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
    
    // insertion sorting
    for(int i=1; i<n; i++){
        int key = sequence[i];
        int j = i-1;
        while((j > 0) && (sequence[j] > key)){
            sequence[j+1] = sequence[j]; // 挪出第 j 個空位
            j--;
        }
        sequence[j+1] = key;
    }
    
    printf("sorted sequence: ");
    for(int i=0; i<n; i++){
        printf("%d ", sequence[i]);
    }
    printf("\n");
}