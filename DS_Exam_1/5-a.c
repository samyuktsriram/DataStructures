#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

//Helper functions from my github
//bubble sort from github
//It's O(n^2) which is not great but it works and is also the most intuitive to code.

int* create_array_rand(int length){

    int* ptr = malloc(length * sizeof(int));
    for(int i=0; i<length; i++){
        ptr[i] = rand()%1000;
    }
    return ptr;
}
void print_array(int length, int* array){

    printf("Here's your array! \n");

    for(int i = 0; i<length; i++){
        printf("%d ", array[i]);
    }
    printf("\n");
}

void skip_bubble_sort(int length, int* array){

    for(int i = 2; i<length; i=i+3){
        for(int k = 2; k<length-i-1;k=k+3){
            if(array[k]>array[k+3]){
                int temp = array[k];
                array[k] = array[k+3];
                array[k+3] = temp;
            }
        }
    }
}

int* sortEveryThirdElement(int* a, int n){
    //This is bubble sort but the variables increment by 3 each time in the appropriate places.
    //O(n^2)
    skip_bubble_sort(n, a);
    return a;
}


int main(){

    srand(time(NULL));
    //If you want to manually test it, edit the array below and remove the random array
    //int a[10] = {3,5,2,6,7,8,9,1,10,4};
    int n = 11; 
    int* a = create_array_rand(n);

    printf("Unsorted:\n");
    print_array(n, a);
    a = sortEveryThirdElement(a,n);
    printf("Sorted:\n");
    print_array(n, a);
    free(a);
    return 0;
}