#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int* create_array_input(int length){

    int* ptr = malloc(length * sizeof(int));
    for(int i=0; i<length; i++){
        printf("Enter the %d th element\n", i);
        scanf("%d", &ptr[i]);
    }
    return ptr;
}

int* create_array_rand(int length){

    int* ptr = malloc(length * sizeof(int));
    for(int i=0; i<length; i++){
        ptr[i] = rand()%1000;
    }
    return ptr;
}

void selection_sort(int length, int* array){

//Doesn't work lmao

    //INV: 0-k is sorted, 0<=k<length-1
    for(int k = 0; k < length - 1; k++){

        //int smallest = array[k];

        int smallest_index = k;
        //INV: array[j] is the smallest element in array[k..length]
        for(int j = k+1; j<length;j++){

            //If condition to find index of smallest
            if(array[j] < array[smallest_index]){
                //swap
                smallest_index = j;
            }
        }
        int temp = array[k];
        array[k] = array[smallest_index];
        array[smallest_index] = temp;
    }
}

void print_array(int length, int* array){

    printf("Here's your array! \n");

    for(int i = 0; i<length; i++){
        printf("%d\n", array[i]);
    }
}

void bubble_sort(int length, int* array){

    //INV: array[0..k] is unsorted, 1<=k<=length
    for(int i = 0; i<length; i++){
        for(int k = 0; k<length-i-1;k++){
            if(array[k]>array[k+1]){
                int temp = array[k];
                array[k] = array[k+1];
                array[k+1] = temp;
            }
        }
    }

}

int main(){

    srand(time(NULL));

    int len;
    printf("Enter the length of the array\n");
    scanf("%d", &len);

    int* array = create_array_rand(len);

    print_array(len,array);
    bubble_sort(len, array);
    print_array(len, array);

    free(array);
    return 0;
}