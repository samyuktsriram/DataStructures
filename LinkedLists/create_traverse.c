// Creating a linked list, 
//references : https://cs50.harvard.edu/college/2019/fall/notes/5/


// I don't know what the scene here is lmao


#include <stdio.h>
#include <stdlib.h>

// Define what a house is
typedef struct Node {
    int data; //define person 1 and what they know
    struct Node * next; // define person 2 and what they know
}
Node;

int trial1(void){
    int i, val; // will be used in the interaction of the program

    // These two will help get the list started
    Node * head = NULL;
    Node * temp = NULL;

    i = 0; //This will be a length counter
    val = 1; // This starts off as non-zero to begin the loop
    while(val>0){
        printf("Enter the integer to add in the list. Enter -ve number to stop \n");
        val = 0;
        scanf("%d", & val);
        // if (inp_data<0){break;}
        if (val<0){return 1;}
        temp-> next = malloc(sizeof(Node));
        temp = temp-> next;
        if (i == 0){ //Condition checks if this is the first element, in which case we need to remember head's location
            head = temp;
        }
        temp->data = val;
        temp -> next = NULL;
        i = i + 1;
    }
    printf("Linked list created, it is %d long", i);
    return 0;
}

int add_elements(Node * temp){
    int i, val; // will be used in the interaction of the program

    i = 0; //This will be a length counter
    while(1){
        printf("Enter the integer to add in the list. Enter -ve number to stop \n");
        scanf("%d", &val);
        // if (inp_data<0){break;}
        if (val<0){return 1;}
        temp-> next = malloc(sizeof(Node));
        temp = temp-> next;
        temp->data = val;
        temp -> next = NULL;
        i = i+1;
    }
    printf("Linked list created, it is %d long", i);
    return 0;
}

int main(void){

    // Setting up the linked list

    Node * head = NULL;
    Node * temp = NULL;

    temp->next = malloc(sizeof(Node)); //This doesn't seem to work?
    temp = temp -> next;
    temp -> data = 9; // Just creating the Head node
    temp -> next = NULL;

    head = temp;

    add_elements(temp);

    return 0;
}