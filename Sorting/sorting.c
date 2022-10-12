#include <stdio.h>
#include <stdlib.h>

int* create_array(int length){

    int* ptr = malloc(length * sizeof(int));
    for(int i=0; i<length; i++){
        printf("Enter the %d th element\n", i);
        scanf("%d", &ptr[i]);
    }
    return ptr;
}

void print_array(int length, int* array){

    printf("Here's your array! \n");

    for(int i = 0; i<length; i++){
        printf("%d\n", array[i]);
    }
}

int main(){

    int len;
    printf("Enter the length of the array\n");
    scanf("%d", &len);
    int* array = create_array(len);

    print_array(len,array);
    return 0;

}