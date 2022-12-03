#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include<assert.h>

//Helper functions and code from my github profile


struct nodeType {
    int val;
    struct nodeType * left; //larger
    struct nodeType * right; //smaller
};
typedef struct nodeType* NodeAddress;


// Creating a Tree, given a number of elements.
NodeAddress arrayToReverseBST(int* a, int n){
    int i;
    NodeAddress helper, root, temp;
    //Get an element, put it in the right place?
    for(i=0;i<n;i++){

        helper = (NodeAddress)malloc(sizeof(struct nodeType));
        helper->val = a[i];

        //If the tree is empty,
        if (i == 0){
            root = helper;
        }
        //INV: All elements to the left of temp are smaller or equal, all elements to the right are greater.
        else {
            temp = root;

            //Check where to add, you'll need to use a while loop and break out when you find a null spot
            //Finding the right place
            while(1){
                if (helper->val > temp->val ){
                    if (temp->left == NULL) {
                        temp->left = helper;
                        break;
                        } else {temp = temp->left;} //the while loop continues
                } 
                else { // The case where the val is less than temp
                    if (temp->right == NULL){
                        temp->right = helper;
                        break;
                    } else {temp = temp->right;}
                }
            }
        }
    }
    return root;
}

//Root Left Right

void prefixPrint(NodeAddress root){
    if (root != NULL){ //Base case checking
        printf("%d ", root->val);
        prefixPrint(root->left);
        prefixPrint(root->right);
    }
}

//Left Root Right
void print_inorder(NodeAddress root){
    if (root != NULL){ //Base case checking
        print_inorder(root->left);
        printf("%d ", root->val);
        print_inorder(root->right);
    }
}

int* create_array_rand(int length){

    int* ptr = malloc(length * sizeof(int));
    for(int i=0; i<length; i++){
        ptr[i] = rand()%100;
    }
    return ptr;
}
void print_array(int length, int* array){

    //printf("Here's your array! \n");

    for(int i = 0; i<length; i++){
        printf("%d ", array[i]);
    }
    printf("\n");
}



int main(){

    srand(time(NULL));

    int n = 12;
    int* a = create_array_rand(n);
    
    //print_array(n,a);
    NodeAddress root = arrayToReverseBST(a,n);
    prefixPrint(root);
    //printf("\n");
    //print_inorder(root);

    return 0;
}