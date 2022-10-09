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
        printf("%d\n", tortoise->data);
        if (rabbit->next == NULL){printf("No Loops here \n"); break;} else if (rabbit->next->next == NULL){printf("No Loops here\n"); break;}
        rabbit = rabbit->next->next;
        tortoise = tortoise->next;
        if (rabbit->next == tortoise | rabbit == tortoise){printf("LOOP ALERT LOOP ALERT \n");break;}
    }

}

int main(void){


    //Hardcoding a start head node
    Node* head = malloc(sizeof(Node));
    head->data = 1;
    head->next = NULL;
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

    print_linkedlist(head);
    print_half_tr(head);

    loop_tester(head);

    //Creating a loop, this assumes there are more than ~6 elements in the list

    //head->next->next->next->next->next->next = head->next;

    // Detecting a loop function -> works if there is a loop. Segment fault if there isn't, figure it out

    Node* tail = NULL;
    tail = reverse_linkedlist(head);

    print_linkedlist(tail);


    return 0;
}