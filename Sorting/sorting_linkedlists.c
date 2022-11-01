//Using code from the linked list and sorting_arrays

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int data; //define person 1 and what they know
    struct Node* next; // define person 2 and what they know
}
Node;

void print_linkedlist(Node* head){
    Node* temp = NULL;
    printf("Here's your linked list \n");

    //Printing all the elements
    int count;
    count = 0; //just to know the length
    temp = head;
    while(1){
        printf("%d ", temp->data);
        count = count+1;
        if (temp->next == NULL){printf("\nCount: %d \n",count); break;}
        temp = temp->next;
    }
}
int len_linkedlist(Node* head){
    Node* temp = NULL;

    int count;
    count = 0;
    temp = head;
    while(1){
        if (temp->next == NULL){count = count+1; break;}
        temp = temp->next;
        count = count+1;;
    }
    return count;
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
Node* create_linkedlist_rand(int length){
    Node* head = malloc(sizeof(Node));
    head->data = rand() % 100;;
    head->next = NULL;

    Node* temp;
    temp=head;
    int i = length-1; //
    while (i>0){
        temp->next = malloc(sizeof(Node));
        temp = temp->next;
        temp->data = rand() % 100;
        temp->next = NULL;
        i--;
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

void quicksort(Node* head, Node* start, node* stop){
    
}

int main(){

    srand(time(NULL));
    int length = 10;

    Node* head;

    head = create_linkedlist_rand(length);
    print_linkedlist(head);
    //swap2(&(head->data), &(head->next->next->data));
    selection_sort_LL(head);
    print_linkedlist(head);
    free_linkedlist(head);
    return 0;
}
