// http://www.btechsmartclass.com/data_structures/binary-search-tree.html
// Also using Professor's code
//Delete reference: https://www.youtube.com/watch?v=hL9RUD33nYs&ab_channel=GateSmashers

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

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
//Couple of cases to consider
NodeAddress delete_element(NodeAddress node, NodeAddress root){
    //Base case
    if (node == NULL){return NULL;} //If the value isn't even in the tree we want to do nothing.

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
        
        //connect the grandparent to the found element
        find_parent(node,root)->left = dummy;
        dummy->left = node->left;
        dummy->right = node->right;

        //call delete_element on it
        delete_element(biggest, root);

        free(node);
        return root;
    }
    
}

//helper function to find predecessor element

NodeAddress find_predecessor(NodeAddress node){
    //Biggest element in left subtree
    NodeAddress temp = node;
    temp = temp->left;
    while(temp->right != NULL){
        temp=temp->right;
    }
    return temp;
}
NodeAddress find_successor(NodeAddress node){

    //Finds the successor element in the tree. Smallest element in the right subtree
    NodeAddress temp = node;
    temp = temp->right;
    while(temp->left != NULL){
        temp=temp->left;
    }
    return temp;
}

//This function will delete a value
//Works, but doesn't work for smallest and biggest value in the tree? how
//Based on this link: https://www.codewithharry.com/videos/data-structures-and-algorithms-in-hindi-78/
//https://www.geeksforgeeks.org/deletion-in-binary-search-tree/

//Print statement debugging

//So there's some weird behaviour here. It cannot delete the smallest element of the largest element in the tree.
NodeAddress delete_element2(NodeAddress root, int value){
    if (root == NULL){return root;}

    //Now we find the value and call delete on the appropriate child tree
    if (value < root->val){delete_element2(root->left, value);}
    
    else if (value > root->val){delete_element2(root->right, value);}

    //Only reaches here once we've found the element. Algo:
    //Find inorder predecessor (biggest element in left subtree)
    //Swap values ipre and root-> val
    //Delete ipre's val from the left subtree recursively
    else {

        //Cases based on children
        //if ((root->left == NULL && root->right == NULL)){free(root);printf("This WORKS!");return NULL;}

        //These 2 return temp to connect back to parent. if it is NULL it behaves like the above code
        if (root->left == NULL){
            NodeAddress temp = root->right;
            free(root);
            printf("Left Null deletion");
            return temp;
        }

        else if (root->right == NULL){
            NodeAddress temp = root->left;
            free(root);
            printf("Right NULL deletion");
            return temp;
        }
        
        NodeAddress succ = find_successor(root);
        root->val = succ->val;
        root->right = delete_element2(root->right, succ->val);
        
    }
    return root;
}


int main(){
    int length;
    printf("Enter the number of elements \n");
    scanf("%d", &length);

    NodeAddress root;
    root = create_bst(length);
    print_inorder(root);
    printf("\n");

    //print_inorder(search(7, root));
    NodeAddress dummy;
    dummy = insert_element(50, dummy);
    dummy = insert_element(30, dummy);
    dummy = insert_element(20, dummy);
    dummy = insert_element(40, dummy);
    dummy = insert_element(70, dummy);
    dummy = insert_element(60, dummy);
    dummy = insert_element(80, dummy);
    //dummy = insert_element(8, root);
    //dummy = insert_element(6, root);

    print_inorder(dummy);
    printf("\n");


    //Testing helper functions
    //printf("%d\n", search(3,root)?(search(3,root)->val): NULL);
    //printf("%d\n", find_parent(search(400,root), root)->val);
    //printf("%d\n", find_biggest_element(root)->val);


    dummy = delete_element2(dummy, 20);

    print_inorder(dummy);
    printf("\n");

    return 0;
}