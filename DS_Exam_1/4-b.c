#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

//helper functions from my github. Edited for min_heaps

//Solution: The smallest number has to be on the bottom row of the max heap. So we can just check there.
//min_heapify the 2nd half of the array and extract_min. -> This is O(n) if siftdown is used, couldn't get it to work
//I've implemented the siftup, so it is O(nlogn) but n/2 elements are being checked.
//We could also just be apes and min_heapify the whole thing and extract min.

//helper functions from my github
void swap2(int* x, int* y){
    int temp = *y;
    *y = *x;
    *x = temp;
}
int* create_array_rand(int length){

    int* ptr = malloc(length * sizeof(int));
    for(int i=0; i<length; i++){
        ptr[i] = rand()%1000;
    }
    return ptr;
}
void siftup_min(int* array, int length, int index){
    if (index > length || index <= 0 || (index - 1) / 2 < 0){return;}

    int parent = (index - 1) / 2;

    int diff1 = array[parent] - array[index];
    if (diff1>0){swap2(&array[parent], &array[index]);}

    siftup_min(array, length, ((index-1)/2));
}
void min_heapify(int* array, int length){
    //Bad approach - O(nlogn)
    
    int node;
    for(node = length-1;node>=0;node--){
        siftup_min(array, length, node);
    }
    
   /*
   //Fast - O(n)
    int node;
    for(node = length/2;node>=0;node--){
        siftdown_min(array, length, node);
    }
   */
     
}
void siftup_max(int* array, int length, int index){
    if (index > length || index <= 0 || (index - 1) / 2 < 0){return;}

    int parent = (index - 1) / 2;

    int diff1 = array[parent] - array[index];
    if (diff1<0){swap2(&array[parent], &array[index]);}

    siftup_max(array, length, ((index-1)/2));
}
void max_heapify(int* array, int length){
    /*
    int node;
    for(node = length/2;node>=0;node--){
        siftdown_max(array, length, node);
    }
    */
    
    int node;
    for(node = length-1;node>=0;node--){
        siftup_max(array, length, node);
    }   
}


void print_array(int length, int* array){

    //printf("Here's your array! \n");

    for(int i = 0; i<length; i++){
        printf("%d ", array[i]);
    }
    printf("\n");
}

void returnSmallestNum(int* maxHeap, int n){

    //only checking the bottom half of the maxheap:
    int half = n/2;
    //this is O(nlogn), sends in only the right half of the list.
    
    min_heapify(&maxHeap[n-half],half);
    printf("%d ", (maxHeap[n-half]));
    
    
    /*
    min_heapify(maxHeap, n);
    printf("%d ", (maxHeap[0]));
    */
    
}

int main(){

    srand(time(NULL));

    int len = 10;
    int* array = create_array_rand(len);

    //print_array(len, array);
    max_heapify(array, len);

    printf("This is the max heap: \n");
    print_array(len, array);

    //If you want to manually test it, edit the array below and remove the random array
    //int array[10] = {3,5,2,6,7,8,9,1,10,4};

    printf("Smallest number: ");
    returnSmallestNum(array, len);
    
    //print_array(len, array);

    free(array);
    return 0;
}
