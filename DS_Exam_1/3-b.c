#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include<assert.h>

//Helper functions and code from my github profile, and q 3-a
//Including a parent pointer, to help find the successor element easily.
//To find next largest element for a given k
//pseudocode: smallest element in left subtree, or first parent > k


struct nodeType {
    int val;
    struct nodeType * left; //larger
    struct nodeType * right; //smaller
    struct nodeType * parent; 
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
            root->parent = NULL;
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
                        helper->parent = temp;
                        break;
                        } else {temp = temp->left;} //the while loop continues
                } 
                else { // The case where the val is less than temp
                    if (temp->right == NULL){
                        temp->right = helper;
                        helper->parent = temp;
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

NodeAddress search(int val, NodeAddress node){
    //O(logn)
    if (node==NULL){return NULL;}
    if (val == node->val){return node;}
    else if (val > node->val){return search(val, node->left);}
    else // (val > node->val) This doesn't get checked i guess
    {return search(val, node->right);}
}

void successorReverseBST(NodeAddress root, int k){

    //Greatest element in the left subtree
    //If there is no left subtree, find next parent that is greater.
    NodeAddress node = search(k, root);

    if (node==NULL){printf("Pudding"); return;}


    if (node->left == NULL){
        NodeAddress temp = node;
        while (temp->parent != NULL){
            temp = temp->parent;
            if (temp->val > node->val){
                printf("%d ", temp->val); return;
            }
        }
        //Now temp = root
        if (temp->val > node->val){
                printf("%d ", temp->val);
            } else {printf("Hamburger"); return;}
    }
    //Check left subtree
    else {
        //Biggest element in left subtree
        NodeAddress temp = node;
        temp = temp->left;
        while(temp->right != NULL){
            temp=temp->right;
        }
    printf("%d ", temp->val); return;
    }
}


int main(){

    srand(time(NULL));

    int n = 10;
    //int* a = create_array_rand(n);

    int a[10] = {5,4,7,3,9,8,1,2,6,10};
    
    //print_array(n,a);
    NodeAddress root = arrayToReverseBST(a,n);
    //prefixPrint(root);
    //printf("\n");
    print_inorder(root);
    printf("\nSuccessor element: ");
    successorReverseBST(root, 4);

    return 0;
}