#include <stdio.h>
#include <stdlib.h>

// A red-black tree is a binary search tree with one extra bit of storage per node: its
// color, which can be either RED or BLACK. By constraining the node colors on any
// simple path from the root to a leaf, red-black trees ensure that no such path is more
// than twice as long as any other, so that the tree is approximately balanced - 
// meaning that height is approximately O(lgn) for n nodes.

// A red-black tree is a binary tree that satisfies the following red-black properties:
//     1. Every node is either red or black.
//     2. The root is black.
//     3. Every leaf (NIL) is black.
//     4. If a node is red, then both its children are black.
//     5. For each node, all simple paths from the node to descendant leaves contain the
//     same number of black nodes.

// Lemma:
//     A red-black tree with n internal nodes has height at most 2lg(n + 1).


#define RED 0
#define BLACK 1

typedef struct Node {
    int data;
    int color;
    struct Node* parent;
    struct Node* leftTree;
    struct Node* rightTree;
} rbTree;

rbTree* NIL;

void leftRotate(rbTree** root, rbTree* x);
void rightRotate(rbTree** root, rbTree* x);
void insertRBFixUP(rbTree** root, rbTree* z);
void insertRB(rbTree** root, int value);
void inOrder(rbTree* subTree);
rbTree* searchTree(rbTree* tree, int value);
rbTree* minTree(rbTree* tree);
void transplantRB(rbTree** root, rbTree* u, rbTree* v);
void treeDeleteFixUpRB(rbTree** root, rbTree* x);
void treeDeleteRB(rbTree** root, rbTree* z);


int main(int argc, char* argv[]) {
    NIL = malloc(sizeof(rbTree));
    NIL->color = BLACK;
    NIL->leftTree = NIL->rightTree = NIL->parent = NULL;
    rbTree* root = NIL;

    insertRB(&root, 14);
    insertRB(&root, 16);
    insertRB(&root, 9);
    insertRB(&root, 17);
    insertRB(&root, 8);
    insertRB(&root, 13);
    insertRB(&root, 7);
    insertRB(&root, 11);

    inOrder(root);
    printf("\n");

    rbTree* z = searchTree(root, 9);
    treeDeleteRB(&root, z);

    inOrder(root);

    free(NIL);
}

// We change the pointer structure through rotation, which is a local operation in
// a search tree that preserves the binary-search-tree property.
void leftRotate(rbTree** root, rbTree* x) {
    rbTree* y = x->rightTree;     // When we do a left rotation on a node x, we assume
    x->rightTree = y->leftTree;   // that its right child y is not NIL; x may be any node in
    if (y->leftTree != NIL) {     // the tree whose right child is not NIL.
        y->leftTree->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NIL) {
        *root = y;
    }
    else if (x == x->parent->leftTree) {
        x->parent->leftTree = y;
    }
    else {
        x->parent->rightTree = y;
    }
    y->leftTree = x;
    x->parent = y;
}

void rightRotate(rbTree** root, rbTree* x) {
    rbTree* y = x->leftTree;     
    x->leftTree = y->rightTree;     
    if (y->leftTree != NIL) {       
        y->leftTree->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NIL) {
        *root = y;
    }
    else if (x == x->parent->leftTree) {
        x->parent->leftTree = y;
    }
    else {
        x->parent->rightTree = y;
    }
    y->leftTree = x;
    x->parent = y;
}
// Both LEFT-ROTATE and RIGHT-ROTATE
// run in O(1) time. Only pointers are changed by a rotation; all other
// attributes in a node remain the same.

//             |                                   |                  
//           -----                               -----
//           | Y |                               | X |
//           -----         Left-Rotate()         -----
//         /      \       <-------------        /      \
//      -----      G                           A      -----      
//      | X |              ------------->             | Y |
//      -----              Right-Rotate()             -----
//     /     \                                       /     \
//    A       B                                     B       G

void insertRBFixUP(rbTree** root, rbTree* z) {
    while (z->parent->color == RED) {   // solve the violation of the property 4
        if (z->parent == z->parent->parent->leftTree) {   // whether the parent is left child or right child of the grandparent
            rbTree* y = z->parent->parent->rightTree;   // uncle of z node
            if (y->color == RED) {   // uncle is red (which means z, z->parent and y are all red)
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;   
            }
            else {   // uncle is black
                if (z == z->parent->rightTree) {   // z is the right child (in such case double rotation is applied)
                    z = z->parent;
                    leftRotate(root, z);
                }   
                z->parent->color = BLACK;   
                z->parent->parent->color = RED;
                rightRotate(root, z->parent->parent);
            }
        }
        else {   // symmetric to the previous case
            rbTree* y = z->parent->parent->leftTree;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else {
                if (z == z->parent->leftTree) {
                    z = z->parent;
                    rightRotate(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(root, z->parent->parent);
            }
        }
    }
    (*root)->color = BLACK;   // solve the violation of the property 2
}

void insertRB(rbTree** root, int value) {
    rbTree* newNode = malloc(sizeof(rbTree));
    if (newNode == NULL) {
        printf("Houston, we have a problem\n");
        return;
    }
    newNode->data = value;
    rbTree* y = NIL;   // Trailing pointer maintained as the parent of x
    rbTree* temp = *root;
    while (temp != NIL) {
        y = temp;
        if (newNode->data < temp->data) {
            temp = temp->leftTree;
        }
        else {
            temp = temp->rightTree;
        }
    }
    newNode->parent = y;
    if (y == NIL) {  // Tree was empty
        *root = newNode;
    }
    else if (newNode->data < y->data) {
        y->leftTree = newNode;
    }
    else {
        y->rightTree = newNode;
    }
    newNode->leftTree = newNode->rightTree = NIL;
    newNode->color = RED;   // If we chose to set the color to black then we would be violating property 5 of being a red-black tree
    insertRBFixUP(root, newNode);   // Upon this call, only properties that might be violated are properties 2 and 4
                                    // Property 2 is violated if newNode is the root, and property 4 is violated if newNode’s parent is red.
}
// Since the height of a red-black tree on n nodes is O(lgn), lines up to call 
// to RB-INSERTFIXUP of RB-INSERT take O(lgn) time. In RB-INSERTFIXUP,
// the while loop repeats only if case 1 occurs, and then the pointer z moves
// two levels up the tree. The total number of times the while loop can be executed
// is therefore O(lgn). Thus, RB-INSERT takes a total of O(lgn) time. Moreover, it
// never performs more than two rotations, since the while loop terminates if case 2
// or case 3 is executed.

// On most computers, the iterative version is more efficient.
rbTree* searchTree(rbTree* tree, int value){
    while(tree != NIL && tree->data != value){
        if(value < tree->data){
            tree = tree->leftTree;
        }
        else{
            tree = tree->rightTree;
        }
    }
    return tree;
}

// Finds an element in a binary search tree whose key is a minimum
rbTree* minTree(rbTree* tree){
    while(tree->leftTree != NIL){
        tree = tree->leftTree;
    }
    return tree;
}

// v replaces u 
void transplantRB(rbTree** root, rbTree* u, rbTree* v){
    if(u->parent == NIL){
       *root = v;
    }
    else if(u == u->parent->leftTree){
        u->parent->leftTree = v;
    }else{
        u->parent->rightTree = v;
    }
    v->parent = u->parent;
}

// Within RB-TREE-DELETE-FIXUP, each of cases 1, 3, and 4
// lead to termination after performing a constant number of color changes and at
// most three rotations. Case 2 is the only case in which the while loop can be repeated,
// and then the pointer x moves up the tree at most O(lgn) times, performing
// no rotations.
void treeDeleteFixUpRB(rbTree** root, rbTree* x){
     while (x != *root && x->color == BLACK) {   // Restore properties 1 and 4
        if (x == x->parent->leftTree) {   
            rbTree* w = x->parent->rightTree;   
            if (w->color == RED) {   // case 1: x’s sibling w is red
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(root, x->parent);
                w = x->parent->rightTree;   
            }
            // case 2: x’s sibling w is black, and both of w’s children are black
            if(w->leftTree->color == BLACK && w->rightTree->color == BLACK){
                w->color = RED;
                x = x->parent;
            }
            else {
                if (w->rightTree->color == BLACK) {   // case 3: x’s sibling w is black, w’s left child is red, and w’s right child is black
                    w->leftTree->color = BLACK;
                    w->color = RED;
                    rightRotate(root, w);
                    w = x->parent->rightTree;
                }
                // case 4: x’s sibling w is black, and w’s right child is red
                w->color = x->parent->color;  
                x->parent->color = BLACK;
                w->rightTree->color = BLACK;
                leftRotate(root, x->parent);
                x = *root;
            }
        }
        else {    // symmetric to the previous case
            rbTree* w = x->parent->leftTree;   
            if (w->color == RED) {   
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(root, x->parent);
                w = x->parent->leftTree;   
            }
            if(w->rightTree->color == BLACK && w->leftTree->color == BLACK){
                w->color = RED;
                x = x->parent;
            }
            else {
                if (w->leftTree->color == BLACK) { 
                    w->rightTree->color = BLACK;
                    w->color = RED;
                    rightRotate(root, w);
                    w = x->parent->leftTree;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->leftTree->color = BLACK;
                leftRotate(root, x->parent);
                x = *root;
            }
        }
    }
    (*root)->color = BLACK;   // Restore property 2
}

// The procedure RB-DELETE-FIXUP takes O(lgn) time and performs
// at most three rotations, and the overall time for RB-DELETE is therefore
// also O(lgn).
void treeDeleteRB(rbTree** root, rbTree* z){
    rbTree* x;
    rbTree* y = z;   // y is removed from the tree if z has 0 or 1 children, otherwise moved within the tree
    int yOrigColor = y->color;
    if(z->leftTree == NIL){   // z has 1 or 0 children
        x = z->rightTree;
        transplantRB(root, z, z->rightTree);
    }
    else if(z->rightTree == NIL){
        x = z->leftTree;
        transplantRB(root, z, z->leftTree);
    }
    else{   // z has 2 children
        rbTree* y = minTree(z->rightTree);
        yOrigColor = y->color;
        x = y->rightTree;
        if(y->parent == z){   // if z has ONLY 2 children and no grandchildren
            x->parent = y;
        }
        else{
            transplantRB(root, y, y->rightTree);
            y->rightTree = z->rightTree;
            y->rightTree->parent = y;
        }
        transplantRB(root, z, y);
        y->leftTree = z->leftTree;
        y->leftTree->parent = y;
        y->color = z->color;
    }
    if(yOrigColor == BLACK){
        treeDeleteFixUpRB(root, x);
    }
    free(z);
}

// Prints out all the keys in a binary search tree in sorted order.
// Takes θ(n) time. 
void inOrder(rbTree* subTree) {
    if (subTree != NIL) {
        inOrder(subTree->leftTree);
        printf("%d ", subTree->data);
        inOrder(subTree->rightTree);
    }
}
