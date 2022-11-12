//This is actually a struct, tree with pointers and stuff.
//IMPORTANT FOR INTERVIEWS

//Has a parent also, so each tree has a parent also. Maybe redo BST with this?

//in a bst. How do you find the next biggest element? let's say i just say here is 4, where is the next biggest element
//This is called find the predecessor or successor


//in a bst, there isn't just 1 valid tree. You can also have rubbish trees that aren't helpful -> degenerate and unbalanced
//These suck because now searching is not log (n), it's O(n)

//AVL trees is base golden ratio (as opposed to base 2)


//How to find balance? look at relative heights of subtrees

//Node* findRoot(Node* x){
//    if x == NULL, return NULL
//    while x-> parent {
//    x = x->parent
//  }
//  return x;
//}

//When trying to balance BSTs, they realised perfect balance is really hard.

//AVL Tree

//HEIGHTS
//Height of leaf node = 0
//Height of a node = 1 + (height of taller child)
//height = longest path to a leaf downwards

//Note that if you insert something now, you might have to edit the heights of all the parents walking up the tree

//For AVL: height diff of Left subtree and Right subtree is AT MOST 1
//For any node, the height diff between 2 children should not be more than 1

//Cases to balance. - 
//Left rotation
//Right rotation

//insert is exactly like BST, but we need to maintain the AVL condition each time as we update the heights

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

struct TreeNode{
    int val;
    int height;
    int balance;
    struct TreeNode * left;
    struct TreeNode * right;
    struct TreeNode * parent;
};
//Can also include int balance = 1, 0 or -1, so we know if node is left heavy or right heavy or balanced.
typedef struct TreeNode* NodeAddress;

//Helper function: max
//Can't believe this isn't inbuilt? check again.
int max_int(int x, int y){
    if (x>y){
        return x;
    }
    else {return y;}
}

void height_balance_update(NodeAddress node){

    //This will only be called on non leaves, turns out that's not true

    if (node->left == NULL && node->right == NULL){
        node->height = 0;
        node->balance = 0;
        return;
    }

    //assert((node->left!=NULL) || (node->right!=NULL));

    if (node->left == NULL){
        node->height = node->right->height + 1;
        node->balance = 0 - node->right->height;
    }
    else if (node->right == NULL){
        node->height = node->left->height + 1;
        node->balance = node->left->height - 0;
    }
    else {
        assert((node->left!=NULL) && (node->right!=NULL));
        node->height = max_int(node->left->height, node->right->height) + 1;
        node->balance = node->left->height - node->right->height;
    }
}

//https://www.programiz.com/dsa/avl-tree#:~:text=Balance%20factor%20of%20a%20node,right%20subtree%20of%20that%20node.&text=The%20self%20balancing%20property%20of,1%2C%200%20or%20%2B1.
NodeAddress left_rotate(NodeAddress node){

    NodeAddress help_right = node->right;
    NodeAddress T2 = help_right->left;
    NodeAddress root = node->parent;

    //Make help_right point to node
    //make node->right point to help_left

    help_right->parent = node->parent;

    help_right->left = node;
    node->parent = help_right;

    node->right = T2;
    if (T2 != NULL){T2->parent = node;}
    
    if (root != NULL){
        if (root->left == node){
        root->left = help_right;
        }
        else {root->right = help_right;}
    }

    //Just going to call rebalance on these guys again, because it will update the heights as needed
    //Then call appropriate_shift, but that won't do anything because the balances will be fine.
    //Could have to fix this later
    height_balance_update(node);
    height_balance_update(help_right);
    return help_right;
}
NodeAddress right_rotate(NodeAddress node){

    NodeAddress help_left = node->left;
    NodeAddress T2 = help_left->right;
    NodeAddress root = node->parent;

    //Make help_right point to node
    //make node->right point to help_left

    help_left->parent = node->parent;

    help_left->right = node;
    node->parent = help_left;

    node->left = T2;
    if (T2 != NULL){T2->parent = node;}
    
    if (root != NULL){
        if (root->left == node){
        root->left = help_left;
        }
        else {root->right = help_left;}
    }

    //Just going to call rebalance on these guys again, because it will update the heights as needed
    //Then call appropriate_shift, but that won't do anything because the balances will be fine.
    //Could have to fix this later
    height_balance_update(node);
    height_balance_update(help_left);
    return help_left;
}

void appropriate_shift(NodeAddress node){

    //does left rotate if node's balance is -2, and node->right->balance is -1
    //does right rotate if node's balance is 2, and node->right->balance is 1

    //if node's balance is -2 and node->right->balance is 1, do right rotate on node->right and then left rotate on node
    //if node's balance is 2 and node->left->balance is -1, do left rotate on node->left and then right rotate on node

    //BASE CASES
    //The left_rotate and right_rotate functions take care of this.
    //assert: there is atleast 1 child
    //No left child, No right child.


    //This is not keeping base cases in mind. Be careful.
    if ((node->left==NULL) && (node->right==NULL)){return;}
    //assert((node->left!=NULL) || (node->right!=NULL));

    //There's an implicit bit of math here: parent will only be unbalanced if children have a non zero balance.
    if (node->balance<-1 || node->balance>1){
        //Unsure whether these not null conditions are causing a problem.
        if ((node->right!=NULL) && (node->balance<-1 && node->right->balance == -1)){
            left_rotate(node);
        }
        else if ((node->right!=NULL) && (node->balance>1 && node->left->balance == 1)){
            right_rotate(node);
        }
        else if ((node->right!=NULL) && (node->balance < -1 && node->right->balance==1)){
            node->right = right_rotate(node->right);
            //you need to connect these nodes here
            left_rotate(node);
        }
        else if ((node->right!=NULL) && (node->balance > 1 && node->left->balance==-1)){
            node->left = left_rotate(node->left);
            //You need to connect the nodes here
            right_rotate(node);
        }
    }
}
void rebalance(NodeAddress node){
    //CHECK if some of the updates in the while loop can happen here
    //update heights
    //calculate height diff, update balance.
    //do the appropriate lshift and rshift
    //go up and repeat

    //Check if either left or right is NULL, you can't call on their heights
    //assert: node will never be a leaf

    while (node!=NULL){
        height_balance_update(node);
        appropriate_shift(node);
        assert(node->balance>=-1 && node->balance<=1);
        node = node->parent;
        rebalance(node);
    }
}



// Creating an AVL Tree, given a number of elements.
NodeAddress create_avl(int count){
    int i;
    NodeAddress helper, root, temp;
    //Get an element, put it in the right place?
    for(i=0;i<count;i++){

        helper = (NodeAddress)malloc(sizeof(struct TreeNode));
        printf("Enter the element to add \n");
        scanf("%d", &helper->val);
        //Initializing these values

        helper->height = 0;
        helper->balance = 0;
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
                        helper->parent = temp;
                        //This updates all the heights. We call rebalance here at each stage
                        while(helper!=NULL){
                            //This height doesn't work, it has to be max of child subtrees. Do it in rebalance.
                            //temp->height +=1;
                            //temp->balance = temp->left->height - temp->right->height
                            //Since we know we are adding to temp->left, we can just +1 to the balance
                            //temp->balance += 1;
                            rebalance(helper);
                            assert(helper->balance>=-1 && helper->balance<=1);
                            //assert(AVL condition is met, BST condition is met)
                            helper = helper->parent;
                            }
                        break;
                        } else {temp = temp->left;} //the while loop continues
                } 
                else { // The case where the val is bigger than temp
                    if (temp->right == NULL){
                        temp->right = helper;
                        helper->parent = temp;
                        while (helper!=NULL){
                            //temp->height +=1;
                            //temp->balance -= 1;
                            rebalance(helper);
                            assert(helper->balance>=-1 && helper->balance<=1);
                            //assert(AVL condition is met, BST condition is met)
                            helper = helper->parent;
                        }
                        break;
                    } else {temp = temp->right;}
                }
                //Update all the heights going up to root? Let's do this in rebalance.
            }
        }
    }
    //For some reason, this isn't the root? Check it out
    return root;
}

//Left Root Right
void print_inorder_heights(NodeAddress root){
    if (root != NULL){ //Base case checking
        print_inorder_heights(root->left);
        printf("%d, balance: %d\n", root->val, root->balance);
        print_inorder_heights(root->right);
    }
}


int main(){

    int length;
    printf("Enter the number of elements \n");
    scanf("%d", &length);

    NodeAddress root;
    root = create_avl(length);
    print_inorder_heights(root);
    printf("\n");

    return 0;
}