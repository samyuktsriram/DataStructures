// Reference: https://www.digitalocean.com/community/tutorials/hash-table-in-c-plus-plus#putting-it-all-together

/* Following the broad structure of the reference, but doing a few things differently:
1. Implementing a more complex hash function -> using function pointers to switch
2. Table doubling - did not work so commented out
3. More comprehensive testing protocol
4. Where possible, I'm including time and space complexity calculations / comments about what I think can be done better

I'm writing each function myself based on the reference.
*/


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h> //String comparison and manipulation commands


int CAPACITY = 10000; // Starting small to see if table doubling is possible

int hash_function_basic(char* string){
    unsigned long sum = 0;
    for(int i = 0; string[i] != NULL; i++){
        sum += string[i]; //Just adds all the ascii values, maybe another operation could be interesting
    }
    return sum % CAPACITY; // Prevents creating indexes greater than the size of the table. 
}

//https://stackoverflow.com/questions/7666509/hash-function-for-string
//http://www.cse.yorku.ca/~oz/hash.html
//Modified to fit the reqiurements. Unclear on exactly what's going on here, but some bit manipulation on an integer and addition based on a given string
int hash_function_complex(char *str)
{
    int hash = 5381;
    int c;
    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return abs(hash % CAPACITY);
}


//Creating the data structures

struct ht_item {
    char* key;
    char* value;
};
typedef struct ht_item ht_item;

//used for separate chaining handling of collisions in overflow buckets
struct LinkedList {
    ht_item* item;
    struct LinkedList* next;
};
typedef struct LinkedList LinkedList;


struct ht {
    //size is the max size, count is how many elements are in the table
    //Using separate chaining to create overflow buckets

    int size;
    int count;
    ht_item** items; //This is an array of pointers, that each point to each item in the hash table
    LinkedList** overflow; //again, an array of pointers that correspond to each item for its overflow
};
typedef struct ht ht;

// Functions to support
/*
1. Create and free
2. Insert
3. Search
4. Delete
5. Print
*/
ht* create_hashtable(int size){
    ht* ht = malloc(sizeof(ht));
    ht->size = size;
    ht->items = (ht_item**) calloc(ht->size, sizeof(ht_item*)); //creates the array of pointers
    ht->count = 0;
    
    //initializing all the pointers to NULL
    for(int i = 0; i<ht->size;i++){
        ht->items[i] = NULL;
    }

    //Creating overflow buckets
    LinkedList** buckets = (LinkedList**) calloc (ht->size, sizeof(LinkedList*));
    for (int i=0; i<ht->size; i++){
        buckets[i] = NULL;
    }
    ht->overflow = buckets;

    return ht;
    //O(n) time -> n+n, O(n) space -> n+n
}


ht_item* create_item(char* key, char* value){
    ht_item* item = (ht_item*) malloc (sizeof(ht_item));

    /*
    So assigning strings like this doesn't work in C, we have to use the string library for this

    item->key = key;
    item->value = value;
    */
    
    item->key = (char*) calloc (strlen(key)+1, sizeof(char));
    item->value = (char*) calloc (strlen(value)+1, sizeof(char)); //We do +1 bc each string has \0 that isn't counted in len

    strcpy(item->key, key);
    strcpy(item->value, value);

    return item;
    //O(n) time, bc we're copying 2 strings using strcpy
}

//Free functions

void free_linkedlist(LinkedList* node){
    if (node == NULL){return;}
    LinkedList* temp = node;
    while(node != NULL){
        temp = node;
        node = node->next;
        free(temp->item->key);
        free(temp->item->value);
        free(temp->item);
        free(temp);
    }
}

void free_item(ht_item* item){
    free(item->key);
    free(item->value);
    free(item);
}

void free_hashtable(ht* ht){

    //This free function doesn't run properly on my computer. Runs fine on an online compiler.

    //goes to each pointer and frees the corresponding item / overflow bucket
    for (int i = 0; i<ht->size; i++){
        if(ht->items[i]!= NULL){free_item(ht->items[i]);}
        if(ht->overflow[i] != NULL) {free_linkedlist(ht->overflow[i]);}
    }
    free(ht->items);
    free(ht->overflow);
    free(ht);
}

void print_hashtable(ht* ht){
    //Goes through all the indexes and prints the non-null ones
    printf("\n \nHere's the entire hashtable: \n");
    for (int i=0; i<ht->size; i++){
        if (ht->items[i] != NULL){
            printf("Key: %s, Value: %s, Index: %d \n", ht->items[i]->key, ht->items[i]->value, i);
            //Printing out overflow buckets:
            if (ht->overflow[i] != NULL){
                LinkedList* temp = ht->overflow[i];
                while(temp != NULL){
                    printf("Overflow bucket: Key: %s, Value: %s \n", temp->item->key, temp->item->value);
                    temp = temp->next;
                }
            }
        }
    }
}

void ht_insert(ht* ht, char* key, char* value, int (*hashfun) (char*)){
    
    //Check if table is full, possible table doubling feature here
    //Create an index for the key
    //If the index is empty, put the key value pair in
    //If the index is full, 
        //if the key is the same, we update the value
        //else put the key value pair in the overflow

    if(ht->count == ht->size){
        printf("This table is full \n");
        //ht->items = realloc(ht->items, 2*ht->size);
        //ht->overflow = realloc(ht->overflow, 2*ht->size);
        //ht->size = 2*ht->size;
        //printf("Reallocated to %d\n", ht->size);
        //So this doubles the table, but the hashing still is based on the old value. That's why overflows are there.
        //CAPACITY = CAPACITY*2;
        return;
    }

    int index = (*hashfun)(key);

    if(ht->items[index] == NULL){
        ht->items[index] = create_item(key, value);
        ht->count++;
        return;
    }
    else {
        if (strcmp(key, ht->items[index]->key) == 0){ //If the key is the same, we update the value
            free(ht->items[index]->value);
            ht->items[index]->value = (char*) calloc (strlen(value)+1, sizeof(char));
            strcpy(ht->items[index]->value, value);
        }

        else{//Collision case!
            //This is a naive way to do handle_collision, reference uses a bunch of embedded functions.
        LinkedList* temp = ht->overflow[index];
        if (temp == NULL){
            //Creating the first overflow bucket
            LinkedList* head = (LinkedList*)malloc(sizeof(LinkedList));
            temp = head;
            ht->overflow[index] = temp;
            temp->item = create_item(key, value);
            ht->count++;
            return;
        }
        while (temp->next != NULL){
            if (strcmp(key, temp->item->key) == 0){ //If the key is the same, we update the value
            free(temp->item->value);
            temp->item->value = (char*) calloc (strlen(value)+1, sizeof(char));
            strcpy(temp->item->value, value);
            }
            temp = temp->next;
            //This will go to the last full overflow bucket in the chain
        }
        //creating the next overflow bucket
        temp->next = (LinkedList*)malloc(sizeof(LinkedList));
        temp->next->item = create_item(key, value);
        ht->count++;
        return;
        }
    }
}

char* search_hashtable(ht* ht, char* key, int (*hashfun) (char*)){
    int index = (*hashfun)(key);

    if (ht->items[index] == NULL){
        printf("This key doesn't exist in the table.\n");
        return NULL;
    }

    if (strcmp(ht->items[index]->key, key)==0){
        printf("Found the element!\n");
        printf("Key: %s, Value: %s, Index: %d \n", ht->items[index]->key, ht->items[index]->value, index);
        return ht->items[index]->value;
    }
    else {//They share indexes, so the required key must be in the overflow buckets, and the buckets must exist.
        if (ht->overflow[index] != NULL){
            LinkedList* temp = ht->overflow[index];

            while (temp != NULL){
                temp = temp->next;
            }
            printf("This key doesn't exist in the table, overflows checked\n");
            return NULL;
        }
    }
}

void delete_element(ht* ht, char* key, int (*hashfun) (char*)){
    
    //Can copy from the search function and alter where needed.
    //Cases:
        /*
        1. if the index is empty, the key is not there so move on
        2. if index is there but key is not, it must be in overflow chain
            1. if the head of the chain is the element to delete, reattach head->next to ht->overflow[index] and delete head
            2. if it's not the head, look through the rest of teh chain and delete it, attach the previous to the next.
        */

    int index = (*hashfun)(key);
    ht_item* temp_item = ht->items[index];
    LinkedList* overflow_head = ht->overflow[index];

    if (ht->items[index] == NULL){
        printf("This key doesn't exist in the table, cannot delete.");
        return;
    }

    if (overflow_head == NULL && strcmp(ht->items[index]->key, key)==0){ //Empty overflows, matching index and key
        printf("Found the element!, Deleting %s\n",ht->items[index]->key);
        ht->items[index] = NULL;
        free_item(temp_item);
        return;
    }
    else if (overflow_head != NULL) {
        if (strcmp(overflow_head->item->key, key) == 0){
            printf("Found the element as overflow_head!, Deleting\n");
            ht->overflow[index] = overflow_head->next;
            free_item(overflow_head->item);
            free(overflow_head);
            ht->count--;
            return;
        }
        else if (strcmp(ht->items[index]->key, key)==0){
            //delete item and put first element from overflow chain in here.
            printf("Found the element in table!, Deleting and moving overflow head into table\n");
            free_item(temp_item);
            ht->items[index] = create_item(overflow_head->item->key, overflow_head->item->value);
            ht->overflow[index] = overflow_head->next;
            ht->count--;
            return;
        }
        else { // case where it's somewhere in the chain, after the head

            LinkedList* current = overflow_head->next;
            LinkedList* prev = overflow_head;
            while (current != NULL){
                if (strcmp(current->item->key, key)==0){
                    printf("Found the element in overflows!, Deleting\n");
                    prev->next = current->next;
                    free_item(current->item);
                    free(current);
                    ht->count--;
                    return;
                }
                prev = current;
                current = current->next;
            }
            //The index was generated, but the the key didn't get matched in the search
            printf("The index exists, but the key does not exist \n");
        }
    }
}


//Additional Testing routines

//https://stackoverflow.com/questions/8257714/how-to-convert-an-int-to-string-in-c
//Useful for generating a lot of unique keys, see size_test function below.
char* int_to_string(int n){
    int x = n;
    int length = snprintf(NULL, 0, "%d", x);
    char* str = malloc(length + 1);
    snprintf(str, length + 1, "%d", x);
    return str;
}

void size_test(ht* ht){
    printf("Filling the entire table, and trying to insert beyond max size. Should return 'table is full' message\n");
    int size_max = ht->size;
    for (int j=0; j<size_max+5; j++){
        ht_insert(ht, int_to_string(j), "Testing", hash_function_basic);
        //printf("Count: %d", ht->count);
    }
    //print_hashtable(ht);
}

void insert_test(ht* ht, int (*hashfun) (char*)){
    ht_insert(ht, "Potato", "Delicious", (*hashfun));
    ht_insert(ht, "second entry", "banana", (*hashfun));

    //"Cau" and "Hel" have the same index when hashed with hash_function_basic()
    ht_insert(ht, "Cau", "Crash 1", (*hashfun));
    ht_insert(ht, "Hel", "Crash 2", (*hashfun));
    ht_insert(ht, "Hdm", "Crash 3", (*hashfun));
    ht_insert(ht, "Cau", "This is the replaced element, success!", (*hashfun));
    print_hashtable(ht);

    printf("Searching Test \n");
    search_hashtable(ht, "Potato", (*hashfun));
    search_hashtable(ht, "Hel", (*hashfun));
}

void insert_delete_test(ht* hashtable, int (*hashfun) (char*)){

    printf("==============================\n This test will add elements according to the testing specification \n based on the uncommented elements below, deletion for all cases can be checked. Search is also tested with insert.\n==================================\n");

    insert_test(hashtable, (*hashfun));
    delete_element(hashtable, "Bbu",(*hashfun));
    //delete_element(hashtable, "Cau", (*hashfun));
    delete_element(hashtable, "Hdm", (*hashfun));
    //delete_element(hashtable, "Hel",(*hashfun));
    print_hashtable(hashtable);
}

int main(){

    ht* hashtable = create_hashtable(CAPACITY);
    //insert_test(hashtable);
    //print_hashtable(hashtable);

    //Using a simple hash function that leads to collisions
    insert_delete_test(hashtable, hash_function_basic);


    ht* ht = create_hashtable(CAPACITY);

    //Using a complex refactored hash function, will have no overflow bins
    insert_delete_test(ht, hash_function_complex);

    size_test(ht);

    free_hashtable(hashtable);
    free_hashtable(ht);
    return 0;
}