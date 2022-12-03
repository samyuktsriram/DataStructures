#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>


//Helper functions from my github and 2-a, skip_chunk was very heplful.

struct Node {
    int val; 
    int k;
    struct Node* next;
    struct Node* nextk;
};
typedef struct Node* NodeAddress;

int* create_array_rand(int length){

    int* ptr = malloc(length * sizeof(int));
    for(int i=0; i<length; i++){
        ptr[i] = rand()%100;
    }
    return ptr;
}


void print_linkedlist(NodeAddress head){
    NodeAddress temp = NULL;
    //printf("Here's your linked list \n");

    //Printing all the elements
    int count;
    count = 0; //just to know the length
    temp = head;
    while(1){
        printf("%d, k=%d ||", temp->val, temp->k);
        count = count+1;
        if (temp->next == NULL){printf("Count: %d \n",count); break;}
        temp = temp->next;
    }
}

void print_linkedlist_k(NodeAddress head){
    NodeAddress temp = NULL;
    //printf("Here's your linked list \n");

    //Printing all the elements
    int count;
    count = 0; //just to know the length
    temp = head;
    while(temp){
        printf("%d ", temp->val);
        count = count+1;
        if (temp->nextk == NULL){printf("Count: %d \n",count); break;}
        temp = temp->nextk;
    }
}

void print_array(int length, int* array){

    //printf("Here's your array! \n");

    for(int i = 0; i<length; i++){
        printf("%d ", array[i]);
    }
    printf("\n");
}

NodeAddress skip_chunk(int k, NodeAddress temp){
    while(k>0){
        if(!(temp->next)){return NULL;}
        temp = temp->next;
        k = k-1;
    }
    return temp;
}

NodeAddress arrayToLLWithNextK(int* a, int n){

    //Initializing head element
    NodeAddress head = malloc(sizeof(struct Node));
    head->val = a[0];
    head->next = NULL;
    head->k = rand()%4 + 2;
    head->nextk = NULL;

    //1 loop for next pointer, another loop for next2 pointer
    NodeAddress temp = head;
    for (int i = 1; i<n; i++){
        temp->next = malloc(sizeof(struct Node));
        temp = temp->next;
        temp->val = a[i];
        temp->k = rand()%4 + 2;
        temp->next = NULL;
    }

    temp = head;

    while (temp->next != NULL){
        temp -> nextk = skip_chunk(temp->k, temp);
        temp = temp->next;
    }
    return head;
}

void free_linkedlist(NodeAddress head){

    NodeAddress current = head;
    NodeAddress temp;

    while(current){
        temp = current-> next;
        free(current);
        current = temp;
    }

}

int main(){

    srand(time(NULL));
    int n = 12;

    printf("Random array: ");
    int* a = create_array_rand(n);
    print_array(n,a);

    printf("\n");
    NodeAddress head = arrayToLLWithNextK(a,n);
    printf("Linked List: ");
    print_linkedlist(head);

    printf("\n");
    printf("Traversing with nextk: ");
    print_linkedlist_k(head->next);

    free_linkedlist(head);
    

    return 0;
}