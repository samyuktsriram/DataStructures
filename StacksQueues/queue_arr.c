//Implemented with an array with realloc 
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


struct queueType {
    int* data;
    int n; //number of elements in the queue -> will be helpful to know when to realloc
    int max;
    int start;
};
typedef struct queueType* QueueAddress;

QueueAddress create_queue(){

    QueueAddress q = malloc(sizeof(struct queueType));

    q->max = 2;
    q->start = 0;
    q->n = 0;
    q->data = malloc(q->max * sizeof(int));

    return q;

}

QueueAddress insert_queue(QueueAddress q, int val){
    assert(val>=0);
    
    if (q->n == q->max){
        q->data = realloc(q->data, 2 * q->max);
        q->max = 2* q->max;
        printf("Reallocating\n");
    }

    q->data[(q->n + q->start) % q->max] = val;
    q->n++;

    return q;
}

int pop_queue(QueueAddress q){

    if (q->n == 0){return -1;}

    int val = q->data[q->start % q->max];
    q->start++;
    q->n--;
    return val;
}


void free_queue(QueueAddress q){

    free(q->data);
    free(q);

}

int main(){

    QueueAddress q = create_queue();
    insert_queue(q, 1);
    insert_queue(q, 2);
    insert_queue(q, 3);
    insert_queue(q, 4);
    insert_queue(q, 5);

    printf("%d ", pop_queue(q));
    printf("%d ", pop_queue(q));
    

    insert_queue(q, 6);
    insert_queue(q, 7);
    insert_queue(q, 8);

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