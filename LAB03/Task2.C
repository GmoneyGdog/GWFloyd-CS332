#include <stdio.h>
#include <stdlib.h>
//How to compile this program
//gcc –o Insert InsertionSort.c
//./Insert
void displayArray(int *arr, int size){
    int i;
    for(i = 0; i < size; i++){
        printf("(%d)", arr[i]);
    }
    printf("]\n");
}
void sortArray(int *arr, int size){
    int temp, current;
    for(int i=1; i<size; i++){
        current = i;
        while (current > 0 && arr[current-1] > arr[current])
        {
            temp = arr[current];
            arr[current] = arr[current-1];
            arr[current-1] = temp;
            current--;
        }
        
    }
}
int main(){
    int N;
    void displayArray(int *arr, int size);
    void sortArray(int *arr, int size);
    printf("Enter the number of array elements\n");
    scanf("%d", &N);
    int i;
    int *GivenArray = (int*) malloc(N * sizeof(int));
    for(i = 0; i < N; i++){
        printf("Please enter array element %d\n", (i+1));
        scanf("%d", &GivenArray[i]);
    }
    printf("Given Array is: [");
    displayArray(GivenArray, N);
    sortArray(GivenArray, N);
    printf("Sorted Array is: [");
    displayArray(GivenArray, N);
    return 0;
}