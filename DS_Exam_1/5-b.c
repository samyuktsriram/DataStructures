#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

//Helper functions from my github
//Linked list functions from my github with small edits
//bubble sort from github, solution to 5-a.c
//It's O(n^2) which is not great but it works and is also the most intuitive to code.

//Pseudocode: put the required elements into a linked list -> sort it -> print out as many as needed.

//Reasoning: We don't know how many elements we need to sort through, so we use a linked list.
//It could be calculated but this was a more generalizable approach.
//Time complexity is still O(n^2), creating the linked list is O(n), sorting is O(n^2), printing is O(n).

typedef struct Node {
    int data;
    struct Node* next;
}
Node;
void kprint_linkedlist(Node* head, int k){
    Node* temp = NULL;
    //printf("Here's your linked list \n");

    //Printing all the elements
    int count;
    count = 0; //just to know the length
    temp = head;
    while(count<k){
        printf("%d ", temp->data);
        count = count+1;
        if (temp->next == NULL){
            //printf("\nCount: %d \n",count); 
            break;
            }
        temp = temp->next;
    }
}
Node* create_linkedlist_from_skip_array(int length_array, int* array){
    Node* head = malloc(sizeof(Node));
    head->data = array[0];
    head->next = NULL;

    Node* temp;
    temp=head;
    int i = 1; //added the head element
    while(i<length_array){
        if ((i+1)%3==0){i++;}
        else {
            temp->next = malloc(sizeof(Node));
            temp = temp->next;
            temp->data = array[i];
            temp->next = NULL;
            i++;
        }
    }
    return head;
}

void free_linkedlist(Node* head){

    Node* current = head;
    Node* temp;

    while(current){
        temp = current-> next;
        free(current);
        current = temp;
    }

}
void swap2(int* x, int* y){
    int temp = *y;
    *y = *x;
    *x = temp;
}

void selection_sort_LL(Node* head){

    Node* temp;

    for (temp=head; temp != NULL; temp = temp->next){
        Node* smallest_node = temp;
        Node* helper;
        if (temp->next == NULL){helper = temp;} else {helper=temp->next;} // This allows the last element to be compared
        for(helper; helper != NULL; helper = helper->next){
            if (helper->data < smallest_node->data){
                swap2(&(smallest_node->data), &(helper->data));
            }
        }

        swap2(&(temp->data), &(smallest_node->data));
    }

}

int* create_array_rand(int length){

    int* ptr = malloc(length * sizeof(int));
    for(int i=0; i<length; i++){
        ptr[i] = rand()%1000;
    }
    return ptr;
}
void print_array(int length, int* array){

    //printf("Here's your array! \n");

    for(int i = 0; i<length; i++){
        printf("%d ", array[i]);
    }
    printf("\n");
}

void skip_bubble_sort(int length, int* array){

    //INV: array[0..k] is unsorted, 1<=k<=length
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
    
    //Your code goes here

    //This is bubble sort but the variables increment by 3 each time in the appropriate places.
    skip_bubble_sort(n, a);
    return a;
}

void kSmallestAmongUntouched(int* a, int k, int n){

    //Pseudocode: put the required elements into a linked list -> sort it -> print out as many as needed.

    //Just to make sure we don't access outside the array. The actual number of untouched elements would be smaller than n
    assert(k<=n);

    Node* dummy_LL;

    //O(n)
    dummy_LL = create_linkedlist_from_skip_array(n,a);
    //O(n^2), could replace with another sorting algo to make it more efficient? Quicksort would make this O(nlogn)
    selection_sort_LL(dummy_LL);
    //O(n)
    kprint_linkedlist(dummy_LL, k);
    free_linkedlist(dummy_LL);
}

int main(){

    srand(time(NULL));
    //If you want to manually test it, edit the array below and remove the random array
    //int a[10] = {3,5,2,6,7,8,9,1,10,4};
    int n = 12; 
    int* a = create_array_rand(n);

    printf("Unsorted:\n");
    print_array(n, a);
    skip_bubble_sort(n, a);

    printf("Sorted:\n");
    print_array(n, a);

    int k = 7;
    printf("k smallest elements:\n");
    kSmallestAmongUntouched(a,k,n);
    return 0;
}