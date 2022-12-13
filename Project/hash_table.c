// Reference: https://www.digitalocean.com/community/tutorials/hash-table-in-c-plus-plus#putting-it-all-together

/* Following the broad structure of the reference, but doing a few things differently:
1. Implementing a more complex hash function
2. More comprehensive testing protocol
3. Where possible, I'm including time and space complexity calculations / comments about what I think can be done better

I'm writing each function myself based on the reference.
*/


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h> //String comparison and manipulation commands


#define CAPACITY 1000 // Starting small to see if table doubling is possible

unsigned long hash_function_basic(char* string){
    unsigned long sum = 0;
    for(int i = 0; string[i] != NULL; i++){
        sum += string[i]; //Just adds all the ascii values, maybe another operation could be interesting
    }
    return sum % CAPACITY; // Prevents creating indexes greater than the size of the table. 
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
    //Using separate chaining to create overflow buckets -> first testing without

    int size;
    int count;
    ht_item** items; //This is an array of pointers, that each point to each item in the hash table
    LinkedList** overflow; //again, an array of pointers that correspond to each item for its overflow? CHECK AGAIN
};
typedef struct ht ht;

// Functions to support
//1. Create and free


ht* create_hashtable(int size){
    ht* ht = malloc(sizeof(ht));
    ht->size = size;
    ht->items = (ht_item**) calloc(ht->size, sizeof(ht_item*)); //creates the array of pointers
    
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
    printf("\n \n Here's the entire hashtable: \n");
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

void ht_insert(ht* ht, char* key, char* value){
    
    //Check if table is full, possible table doubling feature here
    //Create an index for the key
    //If the index is empty, put the key value pair in
    //If the index is full, 
        //if the key is the same, we update the value
        //else put the key value pair in the overflow

    if(ht->count == ht->size){
        printf("This table is full \n");
        //table doubling feature
        return;
    }

    int index = hash_function_basic(key);

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

char* search_hashtable(ht* ht, char* key){
    int index = hash_function_basic(key);

    if (ht->items[index] == NULL){
        printf("This key doesn't exist in the table.");
        return NULL;
    }

    if (strcmp(ht->items[index]->key, key)==0){
        printf("Found the element!\n");
        printf("Key: %s, Value: %s, Index: %d \n", ht->items[index]->key, ht->items[index]->value, index);
        return ht->items[index]->value;
    }
    else {//They share indexes, so the required key must be in the overflow buckets, and the buckets must exist. REVIEW
        if (ht->overflow[index] != NULL){
            LinkedList* temp = ht->overflow[index];
            while (temp->next != NULL){
                if (strcmp(ht->items[index]->key, key)==0){
                    printf("Found the element in overflow!\n");
                    printf("Key: %s, Value: %s, \n", temp->item->key, temp->item->value);
                    return temp->item->value;
                }
                temp = temp->next;
            }
            printf("This key doesn't exist in the table, overflows checked");
            return NULL;
        }
    }
}

void delete_element(ht* ht, char* key){
    
}

int main(){

    ht* hashtable = create_hashtable(CAPACITY);
    ht_insert(hashtable, "Potato", "Delicious");
    ht_insert(hashtable, "second entry", "banana");

    //"Cau" and "Hel" have the same index when hashed with hash_function_basic()
    ht_insert(hashtable, "Cau", "Crash 1");
    ht_insert(hashtable, "Hel", "Crash 2");


    search_hashtable(hashtable, "Potato");
    search_hashtable(hashtable, "Hel");
    print_hashtable(hashtable);
    free_hashtable(hashtable);
    return 0;
}

