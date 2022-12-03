#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include<assert.h>

//Helper functions and code from my github profile, and q 3-a
//Including a parent pointer, to help find the successor element easily.
//To find distance in sorted order.
//Given x, and x<y, find consecutive successor elements, until you reach y. -> O(nlogn) -> not as efficient

//O(n) solution algo:
    /* 
    1. Traverse inorder, count elements greater than x, elements greater than y.
    4. Subtract the indices to find the number in between, (-1 if not inclusive of x,y)
    */
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

//used in slow_sortedDistance()
int mod_successorReverseBST(NodeAddress root, int k){

    //This is O(log n) -> a few cases but all are basically searches.
    //Greatest element in the left subtree
    //If there is no left subtree, find next parent that is greater.
    NodeAddress node = search(k, root);

    //This base case doesn't get checked when called under sortedDistance, we can safely ignore
    //if (node==NULL){return 0;}


    if (node->left == NULL){
        NodeAddress temp = node;
        while (temp->parent != NULL){
            temp = temp->parent;
            if (temp->val > node->val){
                return temp->val;
            }
        }
        //Now temp = root
        if (temp->val > node->val){
                return temp->val;
            } 
            //This line will never happen
            //else {printf("We are out");}
    }
    //Check left subtree
    else {
        //Biggest element in left subtree
        NodeAddress temp = node;
        temp = temp->left;
        while(temp->right != NULL){
            temp=temp->right;
        }
    return temp->val;
    }
}

void traverse_inorder(NodeAddress root, int* a, int x, int y){
    //a is an array that stores the number of elements greater than x, and greater than y. 
    //This lets the count stay outside the scope of this function so it can be recrsively called.
    if (root != NULL){ //Base case checking
        traverse_inorder(root->left, a, x,y);
        //printf("%d ", root->val);
        if (root->val > x){a[0] += 1;}
        if (root->val > y){a[1] += 1;}
        traverse_inorder(root->right, a, x,y);
    }
}

int sortedDistance(NodeAddress root, int x, int y){
    if ((search(x,root)==NULL) || (search(y,root)==NULL)){return -1;}
    if (y<x){return sortedDistance(root, y, x);}

    assert(x<=y);

    //Array to hold the number of elements > x and y separately. This stays outside the scope of traverse_inorder.
    int count[2] = {0,0};

    //Traverse in descending order, keep track of number of elements greater than x, y individually and return the difference.:
    traverse_inorder(root, count, x,y);

    //Subtracting 1 to get the elements in between
    //count[0] has the number of elements greater than x, count[1] has the number of elements greater than y.
    return count[0] - count[1] -1;
}
// Accidentally made a more inefficient version, here it is. Incase we could not use another datastructure.
int slow_sortedDistance(NodeAddress root, int x, int y){

    //This is O(nlogn)
    //Covering base cases. We're given x,y must be unique.

    //O(log n)
    if ((search(x,root)==NULL) || (search(y,root)==NULL)){return -1;}
    if (y<x){return slow_sortedDistance(root, y, x);}

    assert(x<y);

    int distance = 0;
    int temp = x;
    
    //This is O(nlogn)
    //Loop runs n times, successor is O(log n)
    while (temp != y){
        //This is O(log n)
        temp = mod_successorReverseBST(root, temp);
        distance += 1;
    }
    //question asks for number of elements between, I'm assuming this is exclusive, so subtracting 1
    return distance-1;
}


int main(){

    srand(time(NULL));

    int n = 10;
    //int* a = create_array_rand(n);

    int a[10] = {5,4,15,3,9,8,1,2,11,10};
    
    //print_array(n,a);
    NodeAddress root = arrayToReverseBST(a,n);
    //prefixPrint(root);
    //printf("\n");
    print_inorder(root);
    printf("\nSorted distance: ");
    printf("%d", sortedDistance(root, 1,10));

    return 0;
}