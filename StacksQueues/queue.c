//This code is going to be pretty much the same as my stack, only small changes to pop and insert
//Bc I used a doubly linked list

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

struct queueType {
    Node* head;
    Node* tail;
};
typedef struct queueType* QueueAddress;


void free_linkedlist(Node* head){

    Node* current = head;
    Node* temp;

    while(current){
        temp = current-> next;
        free(current);
        current = temp;
    }

}

QueueAddress create_queue(){

    //head is the LL, tail needs to keep moving up and spitting out. 
    //A better way could be just doing the opposite, but it doesn't make a diff bc doubly linked list

    QueueAddress q = malloc(sizeof(struct queueType));
    q->head = malloc(sizeof(Node));
    q->tail = q->head; // Probably need to edit

    return q;
}

QueueAddress insert_queue(QueueAddress q, int val){

//EDITT
    //We only want positive values
    assert(val >= 0);

    Node* temp = q->tail;

    q->tail->data = val; //initially this is head

    q->tail->next = malloc(sizeof(Node));
    q->tail = q->tail->next;
    q->tail->prev = temp;
    temp->next = q->tail;

    return q; //could just make this a void function

}

int pop_queue (QueueAddress s){


    if (s->head == s->tail){return -1;}

    int val = s->head->data;

    s->head = s->head->next;
    free(s->head->prev);

    return val;
}


void free_queue(QueueAddress q){
    free_linkedlist(q->head);
    free(q);
}


int main(){

    QueueAddress q = create_queue();
    insert_queue(q, 10);
    insert_queue(q, 20);
    insert_queue(q, 30);
    insert_queue(q, 40);
    insert_queue(q, 33);

    printf("%d ", pop_queue(q));
    printf("%d ", pop_queue(q));
    

    insert_queue(q, 30);
    insert_queue(q, 40);
    insert_queue(q, 33);

    printf("%d ", pop_queue(q));
    printf("%d ", pop_queue(q));
    printf("%d ", pop_queue(q));
    printf("%d ", pop_queue(q));
    printf("%d ", pop_queue(q));
    printf("%d ", pop_queue(q));
    printf("%d ", pop_queue(q));
    printf("%d ", pop_queue(q));


    free_queue(q);
    return 0;
}