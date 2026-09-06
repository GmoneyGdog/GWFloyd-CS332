#include <stdio.h>
int isPrime(int N){
    for (int i = 2; i < N; i++){
        if (N %i==0){
            return 0;
        }
    }
    return 1;
}
int main(){
    int given_number;
    scanf("%d", &given_number);
    if(isPrime(given_number)){
        printf("The number is prime");
    }
    else{
        printf("The number is not prime");
    }
}
