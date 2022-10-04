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

    printf("Here's your linked list \n");

    //Printing all the elements
    int count;
    count = 0; //just to know the length
    temp = head;
    while(1){
        printf("%d\n", temp->data);
        count = count+1;
        if (temp->next == NULL){break;}
        temp = temp->next;
    }


    printf("Here's the first half of the linked list\n");
    //printing half the elements with the tortoise and rabbit algo
    Node* rab = head;
    Node* tort = head;
    while(1){
        printf("%d\n", tort->data);
        if (rab->next == NULL){break;} else if (rab->next->next == NULL){break;}
        rab = rab->next->next;
        tort = tort->next;
    }

    //Creating a loop, this assumes there are more than 6 elements in the list

    //head->next->next->next->next->next->next = head->next;

    // Detecting a loop function -> works if there is a loop. Segment fault if there isn't, figure it out

    rab = head;
    tort = head;
    while(1){
        printf("%d\n", tort->data);
        if (rab->next == NULL){printf("No Loops here");break;} else if (rab->next->next == NULL){printf("No Loops here");break;}
        rab = rab->next->next;
        tort = tort->next;
        if (rab->next == tort->next | rab->next->next == tort->next){printf("LOOP ALERT LOOP ALERT");break;}
    }

    return 0;
}