#include<stdio.h>
#define MAX_NUM 100

int main(){
    // handle input
    printf("bubble sort , please scanf n: \n");
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
    
    // bubble sorting
    for(int i=0; i<n; i++){
        for(int j=0; j<n-1-i; j++){
            if(sequence[j] > sequence[j+1]){
                int temp = sequence[j+1];
                sequence[j+1] = sequence[j];
                sequence[j] = temp;
            }
        }
    }
    
    printf("sorted sequence: ");
    for(int i=0; i<n; i++){
        printf("%d ", sequence[i]);
    }
    printf("\n");
}