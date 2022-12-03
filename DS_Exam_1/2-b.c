#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>


//Helper functions from my github and question 2-a

struct Node {
    int val; //define person 1 and what they know
    struct Node* next; // define person 2 and what they know
    struct Node* next2;
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
        printf("%d ", temp->val);
        count = count+1;
        if (temp->next == NULL){printf("Count: %d \n",count); break;}
        temp = temp->next;
    }
}

void print_linkedlist_2(NodeAddress head){
    NodeAddress temp = NULL;
    //printf("Here's your linked list \n");

    //Printing all the elements
    int count;
    count = 0; //just to know the length
    temp = head;
    while(1){
        printf("%d ", temp->val);
        count = count+1;
        if (temp->next2 == NULL){printf("Count: %d \n",count); break;}
        temp = temp->next2;
    }
}

void print_array(int length, int* array){

    //printf("Here's your array! \n");

    for(int i = 0; i<length; i++){
        printf("%d ", array[i]);
    }
    printf("\n");
}
NodeAddress arrayToLLWithNext2(int* a, int n){

    //Initializing head element
    NodeAddress head = malloc(sizeof(struct Node));
    head->val = a[0];
    head->next = NULL;
    head->next2 = NULL;

    //1 loop for next pointer, another loop for next2 pointer
    NodeAddress temp = head;
    for (int i = 1; i<n; i++){
        temp->next = malloc(sizeof(struct Node));
        temp = temp->next;
        temp->val = a[i];
        temp->next = NULL;
    }

    temp = head;

    while (temp->next->next != NULL){
        temp -> next2 = temp->next->next;
        temp = temp->next;
    }

    return head;
}

NodeAddress reverseLLWithNext2(NodeAddress head){

    //Algo: reverse next2 first, and then reverse next.
    //Because of how next2 works, you have to do it on head and head->next

    NodeAddress current = head;
    NodeAddress prev2 = NULL;
    NodeAddress temp2 = NULL;


    while(current) {
        temp2 = current -> next2;
        current-> next2 = prev2;
        prev2 = current;
        current = temp2;
    }

    current = head->next;
    prev2 = NULL;
    temp2 = NULL;

    while(current){
        temp2 = current -> next2;
        current-> next2 = prev2;
        prev2 = current;
        current = temp2;
    }

    current = head;
    NodeAddress prev = NULL;
    NodeAddress temp = NULL;

    while(current) {
        temp = current -> next;
        current-> next = prev;
        prev = current;
        current = temp;
    }
    return prev;
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
    NodeAddress head = arrayToLLWithNext2(a,n);
    printf("Linked List: ");
    print_linkedlist(head);

    head = reverseLLWithNext2(head);

    printf("\n");
    print_linkedlist(head);
    print_linkedlist_2(head);

    free_linkedlist(head);
    

    return 0;
}