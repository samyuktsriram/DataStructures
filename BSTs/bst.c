// http://www.btechsmartclass.com/data_structures/binary-search-tree.html
// Also using Professor's code
//Delete reference: https://www.youtube.com/watch?v=hL9RUD33nYs&ab_channel=GateSmashers

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

//This is useful in the deletion function. Assumes the node exists in the tree.
NodeAddress find_parent(NodeAddress node, NodeAddress root){

    //assert: node exists in the tree.
    //(temp->left or right is the node) or find_parent(temp, node->left or right) is called

    NodeAddress temp = node;

    if (node==NULL || root == NULL){return NULL;}
    //This is the first part of the invariant
    if ((root->left == temp) || (root->right == temp)){return root;}

    else if (temp->val <= root->val){return find_parent(node, root->left);}
    else // (val > node->val) This doesn't get checked i guess
    {return find_parent(node, root->right);}
}

//Finding the biggest element in a subtree

NodeAddress find_biggest_element(NodeAddress root){

    if (root==NULL){return NULL;}
    NodeAddress temp = root;
    while (temp->right != NULL)
    {
        temp = temp->right;
    }
    return temp;
}
//Delete
//INCOMPLETE and strange
//This function will delete based on NodeAddress, can be written to find a value with the search function.
//Couple of cases to conside
NodeAddress delete_element(NodeAddress node, NodeAddress root){
    //Base case
    if (node == NULL){return root;} //If the value isn't even in the tree we want to do nothing.

    //Case1: No children
    if ((node->left == NULL) && (node->right == NULL)) {free(node); return root;}

    //Case2: 1 child
    else if ((node->left != NULL) && (node->right == NULL)){
        NodeAddress temp = node;
        //Find Grandparent, connect the grandparent -> left to child
        find_parent(temp,root)->left = temp->left;
        free(node);
        return root;
    }
    else if ((node->left == NULL) && (node->right != NULL)){
        NodeAddress temp = node;
        //Find Grandparent, connect the grandparent -> right to child
        find_parent(temp,root)->right = temp->right;
        free(node);
        return root;
    }
    //Case3: 2 children
    else {
        //Find the biggest element in the left subtree
        NodeAddress biggest = find_biggest_element(node->left); //node->left must exist bc we've eliminated previous cases.
        NodeAddress dummy = biggest;
        //call delete_element on it
        delete_element(biggest, root);
        //connect the grandparent to the found element
        find_parent(node,root)->left = dummy;
        dummy->left = node->left;
        dummy->right = node->right;
        free(node);
        return root;
    }
    
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
    printf("\n");


    //Testing helper functions
    //printf("%d\n", search(3,root)?(search(3,root)->val): NULL);
    printf("%d\n", find_parent(search(400,root), root)->val);
    printf("%d\n", find_biggest_element(root)->val);


    dummy = delete_element(search(2,root), root);

    print_inorder(root);
    printf("\n");

    return 0;
}