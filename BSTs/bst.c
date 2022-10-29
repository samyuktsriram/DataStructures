// http://www.btechsmartclass.com/data_structures/binary-search-tree.html
// Also using Professor's code

#include<stdio.h>
#include<stdlib.h>

struct nodeType {
    int val;
    struct nodeType * left; //smaller
    struct nodeType * right; //smaller
};
typedef struct nodeType* NodeAddress;

// Creating a Tree, given a number of elements.
NodeAddress create_bst(int count){
    int i;
    NodeAddress helper, root, temp;
    //Get an element, put it in the right place?
    for(i=0;i<count;i++){

        helper = (NodeAddress)malloc(sizeof(struct nodeType));
        printf("Enter the element to add \n");
        scanf("%d", &helper->val);

        //If the tree is empty,
        if (i == 0){
            root = helper;
        }
        //INV: All elements to the left of temp are smaller or equal, all elements to the right are greater.
        else {
            temp = root;
            //printf("Enter the element to add");
            //scanf("%d", &temp->val);

            //Check where to add, you'll need to use a while loop and break out when you find a null spot
            //Finding the right place
            while(1){
                if (helper->val <= temp->val ){
                    if (temp->left == NULL) {
                        temp->left = helper;
                        break;
                        } else {temp = temp->left;} //the while loop continues
                } 
                else { // The case where the val is bigger than temp
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

//Left Root Right
void print_inorder(NodeAddress root){
    if (root != NULL){ //Base case checking
        print_inorder(root->left);
        printf("%d", root->val);
        print_inorder(root->right);
    }
}

int main(){
    int length;
    printf("Enter the number elements \n");
    scanf("%d", &length);

    NodeAddress root;
    root = create_bst(length);
    print_inorder(root);
    return 0;
}