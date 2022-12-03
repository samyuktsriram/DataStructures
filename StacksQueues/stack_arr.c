//Implemented with an array with realloc

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


typedef struct stackType{
    int* data;
    int end;
    int size;
}* StackAddress;

StackAddress create_stack(){

    StackAddress s = malloc(sizeof(struct stackType));
    s->end = 0;
    s->size = 4;
    s->data = malloc(s->size * sizeof(int)); //Might realloc later for bigger

    return s;
}

StackAddress insert_stack(StackAddress s, int val){

    assert(val>=0); //we only want +ve values
    //Case where stack is full, we need to realloc here only
    if (s->size == s->end){
        s->data = realloc(s->data, 2*s->size);
        s->size = 2*s->size;
        printf("Reallocated to %d\n", s->size);
    }
    s->data[s->end++] = val;
    return s;
}

int pop_stack(StackAddress s){

    //Might need to edit this
    if (s->end == 0){return -1;}
    return s->data[--s->end];

}

void free_stack(StackAddress s){
    free(s->data);
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