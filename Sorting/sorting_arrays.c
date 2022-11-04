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

void swap2(int* x, int* y){
    int temp = *y;
    *y = *x;
    *x = temp;
}

void swap(int* array, int index1, int index2){
    int temp = array[index1];
    array[index1] = array[index2];
    array[index2] = temp;
}

int partition(int* array, int start, int stop){
    //returns an index, everything to the left is smaller and everything to the right is greater
    //This isn't the best way, find better ones

    //pick a random number between start and stop, swap to 0.
    int r = rand()%(stop-start) + start;

    //swap array[start] and array[r]
    //swap(array, start, r);
    swap2(&array[start], &array[r]);

    int pivot = array[start];
    int i = start+1;
    int j = stop;

    //INV: left of i <= pivot and right of j > pivot
    while (i<=j){
        if (array[i]>pivot){
            //swap(array, i, j);
            swap2(&array[i], &array[j]);
            j=j-1;
        } else{i++;}
    }
    //swap(array, j, start);
    swap2(&array[start], &array[j]);
    return j;
}

void quick_sort(int* array, int start, int stop){
    //We need a few base cases
    if (array == NULL || start>=stop){return;}
    if (start < 0 || stop < 0){return;}

    int p = partition(array, start, stop);

    quick_sort(array, start, p-1);
    quick_sort(array, p+1, stop);
}

void selection_sort(int length, int* array){

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
        printf("%d ", array[i]);
    }
    printf("\n");
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

void insertion_sort(int length, int* array){

    int i, current, j;

    //INV: a[0..i] is sorted and 0<i<length
    for(i=1; i<length; i++){

        current = array[i];
        j = i-1;

        //INV: array[0..j] < current and j>=0, j+1 is the insertion point
        while (j>=0 && array[j] > current){
            //push j up so there's space for current. This is where to insert
            array[j+1] = array[j];
            j--;
        }
        array[j+1] = current;
    }
}

void siftdown_max(int* array, int length, int index){
    
    if (index > length){return;}
    
    int child1 = 2*index + 1;
    int child2 = 2*index + 2;

    //assert: child1 and child2 are in the array

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
void max_heapify(int* array, int length){
    int node;
    for(node = length/2;node>=0;node--){
        siftdown_max(array, length, node);
    }   
}
void swapLastMax(int* array, int length){
    //assert: array is heapified.

    swap2(&array[0], &array[length-1]);
    siftdown_max(array, length-2, 0);
}

void heap_sort(int* array, int length){

    //This is selection sort, except we are using a heap to find the largest element.
    //O(n) to heapify, O(nlogn) to sort.

    max_heapify(array, length);
    for(int i=0; i<length; i++){
        //int p = findMaxPos(array, n-i); //Because we're adding the largest element at the end.
        //int p = 0; //since we've got a heap, we can do this
        //swap2(&array[p], &array[length-1-i]);



        //We're going to do those 2 steps together
        swapLastMax(array, length-i); // But this is something we do with heaps
    }
}


int main(){

    srand(time(NULL));

    int len;
    printf("Enter the length of the array\n");
    scanf("%d", &len);

    int* array = create_array_rand(len);

    print_array(len,array);
    //bubble_sort(len, array);
    //selection_sort(len,array);
    //insertion_sort(len, array);
    //quick_sort(array, 0, len-1);
    heap_sort(array, len);
    print_array(len, array);

    free(array);
    return 0;
}