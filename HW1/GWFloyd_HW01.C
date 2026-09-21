#include <stdio.h>
#include <ctype.h>
int sumOfDigits(int N){
    if (N <= 0){
        return -1;
    }
    int sum = 0;
    int temp = 0;
    while(N != 0){
        temp = N % 10;
        sum = sum + temp;
        N = (N - temp)/10; 
    }
    return sum;
}
int UABMaxMinDiff(int *arr, int length){
    int Lower;
    int Higher;
    if (arr[0] < arr[1]){
        Lower = arr[0];
        Higher = arr[1];
    }else{
        Lower = arr[1];
        Higher = arr[0];
    }
    int i;
    for (i = 2; i < length; i++){
        if (arr[i] < Lower){
            Lower = arr[i];
        }
        if (arr[i] > Higher){
            Higher = arr[i];
        }
    }
    return (Higher - Lower);
}
void replaceEvenWithZero(int *arr, int length){
    int i;
    for (i = 0; i < length; i++){
        if (arr[i] % 2 == 0){
            arr[i] = 0;
        }
    }
}
const char* perfectSquare(int n){
    int i = 0;
    while(i * i <= n){
        if(i * i == n){
            return "True";
        }
        i++;
    }
    return "False";
}
int countVowels(char *s, int length){
    int count = 0;
    char vowels[] = {'a', 'e', 'i' , 'o' ,'u'};
    int i = 0;
    for (i=0;i< length; i++){
        int v = 0;
        for(v=0; v< 5;v++){
            if (tolower(s[i]) == vowels[v]){
                count++;
            }
        }
    }
    return count;
}
int main(){
    int i;
    printf("%d\n",sumOfDigits(123));
    printf("%d\n",sumOfDigits(405));
    printf("%d\n",sumOfDigits(0));
    printf("%d\n",sumOfDigits(7));
    printf("%d\n",sumOfDigits(-308));
    int GivenArray1[] = {3, 7, 2, 9};
    printf("%d\n", UABMaxMinDiff(GivenArray1, 4));
    int GivenArray2[] = {5, 5, 5, 5, 5, 5};
    printf("%d\n", UABMaxMinDiff(GivenArray2, 6));
    int GivenArray3[] = {-2, 4, -1, 6, 5};
    printf("%d\n", UABMaxMinDiff(GivenArray3, 5));
    int GivenArray4[] = {1, 2, 3, 4};
    printf("[");
    replaceEvenWithZero(GivenArray4, 4);
    for (i = 0; i < 4; i++){
        printf("%d", GivenArray4[i]);
        if (i != 4-1){
            printf(", ");
        }
    }
    printf("]\n");
    int GivenArray5[] = {2, 4, 6};
    printf("[");
    replaceEvenWithZero(GivenArray5, 3);
    for (i = 0; i < 3; i++){
        printf("%d", GivenArray5[i]);
        if (i != 3-1){
            printf(", ");
        }
    }
    printf("]\n");
    int GivenArray6[] = {1, 3, 5};
    printf("[");
    replaceEvenWithZero(GivenArray6, 3);
    for (i = 0; i < 3; i++){
        printf("%d", GivenArray6[i]);
        if (i != 3-1){
            printf(", ");
        }
    }
    printf("]\n");
    printf("%s\n", perfectSquare(16));
    printf("%s\n", perfectSquare(15));
    printf("%s\n", perfectSquare(25));
    printf("%s\n", perfectSquare(36));
    char TestCase1[] = "Hello World";
    printf("%d\n", countVowels(TestCase1, 11));
    char TestCase2[] = "UAB CS";
    printf("%d\n", countVowels(TestCase2, 6));
    char TestCase3[] = "Python";
    printf("%d\n", countVowels(TestCase3, 6));
    char TestCase4[] = "aeiou";
    printf("%d\n", countVowels(TestCase4, 5));
    return 0;
}