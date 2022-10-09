// Creating a linked list, 
//references : https://cs50.harvard.edu/college/2019/fall/notes/5/
//Also used class notes 5

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data; //define person 1 and what they know
    struct Node* next; // define person 2 and what they know
}
Node;

Node* reverse_linkedlist(Node* head){

    Node* current = head;
    Node* prev = NULL;
    Node* temp = NULL;

    while(current) {
        temp = current -> next;
        current-> next = prev;
        prev = current;
        current = temp;
    }
    return prev; //current is now null, prev is what is the new head

}

void print_linkedlist(Node* head){
    Node* temp = NULL;
    printf("Here's your linked list \n");

    //Printing all the elements
    int count;
    count = 0; //just to know the length
    temp = head;
    while(1){
        printf("%d\n", temp->data);
        count = count+1;
        if (temp->next == NULL){printf("Count: %d \n",count); break;}
        temp = temp->next;
    }
}

void print_half_tr(Node* head){
    printf("Here's the first half of the linked list\n");
    //printing half the elements with the tortoise and rabbit algo
    int c;
    c=0;
    Node* rab = head;
    Node* tort = head;
    while(1){
        printf("%d\n", tort->data);
        c = c+1;
        if (rab->next == NULL){printf("Count: %d \n",c);break;} else if (rab->next->next == NULL){printf("Count: %d \n",c);break;}
        rab = rab->next->next;
        tort = tort->next;
    }
}

void loop_tester(Node* head){

    Node* rabbit = head;
    Node* tortoise = head;
    while(1){
        //printf("%d\n", tortoise->data);
        if (rabbit->next == NULL){printf("No Loops here \n"); break;} else if (rabbit->next->next == NULL){printf("No Loops here\n"); break;}
        rabbit = rabbit->next->next;
        tortoise = tortoise->next;
        if (rabbit->next == tortoise | rabbit == tortoise){printf("LOOP ALERT LOOP ALERT \n");break;}
    }

}

Node* rec_reverse_linkedlist(Node* head){

    if((!head) || !(head->next)){return head;}
    Node* rest = rec_reverse_linkedlist(head->next);
    head->next->next = head;
    head->next = NULL;
    return rest;
}

Node* create_linkedlist(void){

    Node* head = malloc(sizeof(Node));
    int val_head;
    printf("Enter the head element, enter -ve number to end\n");
    scanf("%d",&val_head);
    if(val_head<0){return head;}
    head->data = val_head;
    head-> next = NULL;

    Node* temp;
    temp = head;

    while(1){
        int val;
        printf("Enter the element to add, enter -1 to end \n");
        scanf("%d", &val);

        if (val<0){break;}

        //Doing the thing
        temp->next = malloc(sizeof(Node));
        temp = temp->next;
        temp->data = val;
        temp->next = NULL;
        
    }

    return head;

}

Node* skip_chunk(int k, Node* temp){
    while(k>0){
        temp = temp->next;
        if(!(temp->next)){return NULL;}
        k = k-1;
    }
    return temp;
}

Node* chunk_reverse(int chunk, Node* head){
    Node* current = head;
    Node* prev = NULL;
    Node* temp = NULL;

    while(current){
        temp = skip_chunk(chunk,current);
        current-> next = prev;
        prev = current;
        current = temp;

    }
    return prev;
}

int main(void){


    //Creating the Head
    Node* head = create_linkedlist();

    
    print_linkedlist(head);
    print_half_tr(head);

    loop_tester(head);

    //Creating a loop, this assumes there are more than ~6 elements in the list

    //head->next->next->next->next->next->next = head->next;

    // Detecting a loop function -> works if there is a loop.

    Node* tail = NULL;
    tail = reverse_linkedlist(head);
    print_linkedlist(tail);
    Node* rec_tail = rec_reverse_linkedlist(tail);
    print_linkedlist(rec_tail);
    loop_tester(rec_tail);

    Node* chunked = chunk_reverse(4,rec_tail);
    print_linkedlist(chunked);


    return 0;
}