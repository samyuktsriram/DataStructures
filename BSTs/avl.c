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



struct TreeNode{
    int val;
    int height;
    int balance;
    struct TreeNode * left;
    struct TreeNode * right;
    struct TreeNode * parent;
};
//Can also include int balance = 1, 0 or -1, so we know if node is left heavy or right heavy or balanced.
typedef struct TreeNode TreeNode;