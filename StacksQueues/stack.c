#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


//Doubly linked list will be best for this
typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
}
Node;

struct stackType {
    Node* head;
    Node* tail;
};
typedef struct stackType* StackAddress;


void free_linkedlist(Node* head){

    Node* current = head;
    Node* temp;

    while(current){
        temp = current-> next;
        free(current);
        current = temp;
    }

}

StackAddress create_stack(){

    //head is the LL, tail needs to keep moving up and spitting out. 
    //A better way could be just doing the opposite, but it doesn't make a diff bc doubly linked list

    StackAddress s = malloc(sizeof(struct stackType));
    s->head = malloc(sizeof(Node));
    s->tail = s->head; // Probably need to edit

    return s;
}

StackAddress insert_stack(StackAddress s, int val){

    //We only want positive values
    assert(val >= 0);

    Node* temp = s->tail;

    s->tail->data = val; //initially this is head

    s->tail->next = malloc(sizeof(Node));
    s->tail = s->tail->next;
    s->tail->prev = temp;
    temp->next = s->tail;

    return s; //could just make this a void function

}

int pop_stack (StackAddress s){

    // We need to pop from s->tail->prev, bc insert creates the next empty node already.
    //if (s->tail->prev == NULL){return -3;}
    if (s->head == s->tail){return -1;}

    int val = s->tail->prev->data;
    
    s->tail->prev->next = NULL;
    s->tail = s->tail->prev;
    

    return val;
}


void free_stack(StackAddress s){
    free_linkedlist(s->head);
    free(s);
}


int main(){

    StackAddress s = create_stack();
    insert_stack(s, 10);
    insert_stack(s, 30);
    insert_stack(s, 20);
    insert_stack(s, 40);
    insert_stack(s, 400);

    printf("%d ", pop_stack(s));
    printf("%d ", pop_stack(s));
    printf("%d ", pop_stack(s));
    printf("%d ", pop_stack(s));
    printf("%d ", pop_stack(s));
    printf("%d ", pop_stack(s));

    printf("Emptied the stack, now readding and repopping \n");

    insert_stack(s, 20);
    insert_stack(s, 40);
    insert_stack(s, 10);
    insert_stack(s, 30);
    insert_stack(s, 20);


    printf("%d ", pop_stack(s));
    printf("%d ", pop_stack(s));
    printf("%d ", pop_stack(s));
    printf("%d ", pop_stack(s));
    printf("%d ", pop_stack(s));
    printf("%d ", pop_stack(s));
    printf("%d ", pop_stack(s));
    printf("%d ", pop_stack(s));


    free_stack(s);
    return 0;
}