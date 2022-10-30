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
        printf("%d ", root->val);
        print_inorder(root->right);
    }
}

//Find the first matching value
NodeAddress search(int val, NodeAddress node){
    if (node==NULL){return NULL;}
    if (val == node->val){return node;}
    else if (val <= node->val){return search(val, node->left);}
    else // (val > node->val) This doesn't get checked i guess
    {return search(val, node->right);}
}

//Insert a value
NodeAddress insert_element(int val, NodeAddress node){
    if (node == NULL){ //If it's empty then insert it there only
        NodeAddress newNode;
        newNode = (NodeAddress)malloc(sizeof(struct nodeType)); //Create a new node
        newNode->val = val;
        node = newNode;
    }
    else if (val <= node->val) {node->left = insert_element(val, node->left);}
    else {node->right = insert_element(val, node->right);}
    return node;
}

//Delete: reference: https://www.youtube.com/watch?v=hL9RUD33nYs&ab_channel=GateSmashers
//This function will delete based on NodeAddress, can be written to find a value with the search function.
//Couple of cases to consider
NodeAddress delete_element(NodeAddress node, NodeAddress root){
    //Base case
    if (node == NULL){return root;} //If the value isn't even in the tree we want to do nothing.

    //Case1: No children
    if ((node->left == NULL) && (node->right == NULL)) {free(node); return root;}

    //Case2: 1 child
    else if ((node->left != NULL) && (node->right == NULL)){
        NodeAddress temp = node;
        //Find Grandparent, connect the grandparent -> left to child
    }
    else if ((node->left == NULL) && (node->right != NULL)){
        NodeAddress temp = node;
        //Find Grandparent, connect the grandparent -> right to child
    }

    //Case3: 2 children
    //Find the biggest element in the left subtree
    //call delete_element on it
    //connect the grandparent to the found element
}
int main(){
    int length;
    printf("Enter the number elements \n");
    scanf("%d", &length);

    NodeAddress root;
    root = create_bst(length);
    print_inorder(root);

    printf("\n");

    //print_inorder(search(7, root));
    NodeAddress dummy;
    dummy = insert_element(4, root);
    dummy = insert_element(4, root);
    dummy = insert_element(400, root);

    print_inorder(root);
    return 0;
}