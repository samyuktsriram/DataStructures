#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap2(int* x, int* y){
    int temp = *y;
    *y = *x;
    *x = temp;
}
// minimum binary heap, opposite stuff for Max Heap.

//2 Important functions
//insert
    //Add to last contiguous spot
    //Sift Up
//extract_min
    //Swap last contiguous spot with root of heap
    //Sift Down, ending before the last spot.


//Sift_Down method for extraction
void siftup_max(int* array, int length, int index){
    if (index > length || index < 0 || (index - 1) / 2 < 0){return;}

    int parent = (index - 1) / 2;

    int diff1 = array[parent] - array[index];
    if (diff1<0){swap2(&array[parent], &array[index]);}

    siftup_max(array, length, index-1);
}

void siftdown_max(int* array, int length, int index){
    
    if (index > length || index < 0){return;}
    
    int child1 = 2*index + 1;
    int child2 = 2*index + 2;

    //assert: child1 and child2 are in the array
    //Rest are base cases

    if (child1<=length && child2 <= length){
        int diff1 = array[index] - array[child1];
        int diff2 = array[index] - array[child2];

        if (abs(diff1) < abs(diff2) && diff2<0){swap2(&array[index], &array[child2]);}
        else if (abs(diff1) >= abs(diff2) && diff1<0){swap2(&array[index], &array[child1]);}
        
    }
    if (child1<= length && child2 > length){
        int diff1 = array[index] - array[child1];
        if (diff1<0){swap2(&array[index], &array[child1]);}
    }

    if (child2<= length && child1 > length){
        int diff2 = array[index] - array[child2];
        if (diff2<0){swap2(&array[index], &array[child1]);}
    }

    siftdown_max(array, length, child1);
    siftdown_max(array, length, child2);

}


//Sift_Up method for insertion


//Representing as a list, for any element at p, its left child is at 2p+1 and right child is at 2p+2s
//And you can go to the parents by reversing that math.


//How to build a heap from an array?

//Inefficient way: O(n logn)
//Create a new array, input each element 1 at a time, 
//swap up till it's a heap, comparing to PARENTS (2p+1 (or 2) formula)

//Note that anything only affects its path upwards


//Efficient way: Go bottom up -> start from the leaf nodes. This is O(n)

//Note: Bottom row is a heap! No children, so they're all heaps.
//So we just ignore them. 

//Sift down on each element in the penultimate row
//Then sift down on each element of the row above, and keep going till the root.

void max_heapify(int* array, int length){
    int node;
    for(node = length/2;node>=0;node--){
        siftdown_max(array, length, node);
    }   
}

void print_array(int length, int* array){

    printf("Here's your array! \n");

    for(int i = 0; i<length; i++){
        printf("%d ", array[i]);
    }
    printf("\n");
}

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
int* create_heap_input(int length){
    int* ptr = malloc(length * sizeof(int));
    for(int i=0; i<length; i++){
        printf("Enter the %d th element\n", i);
        scanf("%d", &ptr[i]);
        siftup_max(ptr, i, i);
    }
    return ptr;
}


int* insert_element(int* array, int length, int element){

    //Copy the array into bigger memory space,
    //Set last element as needed
    //Siftup to maintain heap
    //free old memory

    int* new_array = malloc((length+1) * sizeof(int));
    for (int i=0; i<length; i++){
        new_array[i] = array[i];
    }
    new_array[length] = element;
    siftup_max(new_array, length+1, length);
    free(array);
    return new_array;
}

int main(){

    srand(time(NULL));

    int len;
    printf("Enter the length of the array\n");
    scanf("%d", &len);

    int* array = create_array_rand(len);

    print_array(len, array);
    max_heapify(array, len);
    print_array(len, array);

    int* new = insert_element(array, len, 1002);
    print_array(len+1, new);


    free(new);
    return 0;
}
