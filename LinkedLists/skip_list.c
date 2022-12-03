//The code from the first midterm technically creates something like a skip list, trying to edit it to work
//This creates the highest connections, need a way to create the subsequent lower connections for each node

//Algo to try to implement this:
/*
1. Create a normal linked list
2. Go to each node and promote randomly, assign the tier to the node as a property
3. Connect each node of the same tier
4. Subtract 1 from each tier and repeat 3. Ignore if tier = 0.
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

struct Node {
    int val;
    struct Node* next;
    int level;
    struct Node* next_level;
};

typedef struct Node* NodeAddress;

void print_linkedlist(NodeAddress head){
    NodeAddress temp = NULL;
    printf("Here's your linked list \n");

    //Printing all the elements
    int count;
    count = 0; //just to know the length
    temp = head;
    while(1){
        printf("%d\n", temp->val);
        count = count+1;
        if (temp->next == NULL){printf("Count: %d \n",count); break;}
        temp = temp->next;
    }
}

NodeAddress skip_chunk(int k, NodeAddress temp){
    while(k>0){
        temp = temp->next;
        if(!(temp->next)){return NULL;}
        k = k-1;
    }
    return temp;
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


int* create_array_rand(int length){

    int* ptr = malloc(length * sizeof(int));
    for(int i=0; i<length; i++){
        ptr[i] = rand()%100;
    }
    return ptr;
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
        if (temp->next_level == NULL){printf("Count: %d \n",count); break;}
        temp = temp->next_level;
    }
}


NodeAddress arrayToLLWithNextk(int* a, int n){

    //Initializing head element
    NodeAddress head = malloc(sizeof(struct Node));
    head->val = a[0];
    head->next = NULL;
    head->level = rand()%4 + 2;
    head->next_level = NULL;

    //1 loop for next pointer, another loop for next2 pointer
    NodeAddress temp = head;
    for (int i = 1; i<n; i++){
        temp->next = malloc(sizeof(struct Node));
        temp = temp->next;
        temp->val = a[i];
        temp->level = rand()%4 + 2;
        temp->next_level = NULL;
    }

    temp = head;

    while (temp->next != NULL){
        temp -> next_level = skip_chunk(temp->level, temp);
        temp = temp->next;
    }
    return head;
}

int main(){

    srand(time(NULL));
    int n = 12;

    printf("Random array: ");
    int* a = create_array_rand(n);
    print_array(n,a);

    printf("\n");
    NodeAddress head = arrayToLLWithNextk(a,n);
    printf("Linked List: ");
    print_linkedlist(head);

    printf("\n");
    printf("Traversing with nextk: ");
    print_linkedlist_k(head);



    free_linkedlist(head);
    

    return 0;
}


