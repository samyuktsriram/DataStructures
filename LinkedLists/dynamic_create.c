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

    temp = head;
    while(1){
        printf("%d\n", temp->data);
        if (temp->next == NULL){break;}
        temp = temp->next;
    }

    return 0;
}