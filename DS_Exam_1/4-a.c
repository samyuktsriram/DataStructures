#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

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

void thirdLargestNum(int* maxHeap, int n){

    //Checking to make sure there are atleast 3 elements
    //assert(n>=3);
    if (n<3){printf("Array is smaller than 3");}

    //Because it's a heap, we know the 3 largest elements will be root, left child and right child.
    //Also, 2nd and 3rd largest elements will be left child and right child.
    //So the solution is just comparing the left and right child of the root and printing the smaller one.

    //using 2p+1 and 2p+2 to find children, where p = 0 because it's the root
    //child1 is at index 1, child2 is at index 2.

    if (maxHeap[1] > maxHeap[2]){printf("%d\n",maxHeap[2]);}
    //Assuming equal elements still count as 3rd largest
    else {printf("%d\n",maxHeap[1]);}
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

    printf("3rd Largest element: ");
    thirdLargestNum(array, len);

    free(array);
    return 0;
}
