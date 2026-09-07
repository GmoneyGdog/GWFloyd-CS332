#include <stdio.h>
int main(){
    int N;
    printf("Enter the number of array elements\n");
    scanf("%d", &N);
    int i;
    int GivenArray[N];
    for(i = 0; i < N; i++){
        printf("Please enter array element %d\n", (i+1));
        scanf("%d", &GivenArray[i]);
    }
    printf("Given Array is: [");
    for(i = 0; i < N; i++){
        printf("(%d)", GivenArray[i]);
    }
    printf("]");
    int temp, current;
    for(int i=1; i<N; i++){
        current = i;
        while (current > 0 && GivenArray[current-1] > GivenArray[current])
        {
            temp = GivenArray[current];
            GivenArray[current] = GivenArray[current-1];
            GivenArray[current-1] = temp;
            current--;
        }
        
    }
    printf("Sorted Array is: [");
    for(i = 0; i < N; i++){
        printf("(%d)", GivenArray[i]);
    }
    printf("]\n");
    return 0;
}