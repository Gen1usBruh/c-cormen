#include <stdio.h>
#include <stdlib.h>

// A binary search tree is organized, as the name suggests, in a binary tree.
// We can represent such a tree by a linked data structure in which
// each node is an object. In addition to a key and satellite data, each node contains
// attributes left, right, and p that point to the nodes corresponding to its left child,
// its right child, and its parent, respectively. If a child or the parent is missing, the
// appropriate attribute contains the value NIL. The root node is the only node in the
// tree whose parent is NIL.

// The keys in a binary search tree are always stored in such a way as to satisfy the
// binary-search-tree property:
//    Let x be a node in a binary search tree. If y is a node in the left subtree
//    of x, then y.key <= x.key. If y is a node in the right subtree of x, then
//    y.key >= x.key.  (We can also use strict comparison to eliminate duplicates, a.k.a "set")

// Basic operations on a binary search tree take time proportional to the height of
// the tree. For a complete binary tree with n nodes, such operations run in θ(lgn)
// worst-case time.

typedef struct Node{
    int data;
    struct Node* parent;
    struct Node* leftTree;
    struct Node* rightTree;
} bsTree;

// INORDER-TREE-WALK(x) algorithm prints out all the keys in a binary search tree 
// in sorted order. 
// Theorem:
    // If x is the root of an n-node subtree, then the call INORDER-TREE-WALK(x)
    // takes θ(n) time.
void inOrder(bsTree* subTree){
    if(subTree != NULL){
        inOrder(subTree->leftTree);
        printf("%d ", subTree->data);
        inOrder(subTree->rightTree);
    }
}

// Variation of INORDER-TREE-WALK - prints the root before the values in either subtree
void preOrder(bsTree* subTree){
    if(subTree != NULL){
        printf("%d ", subTree->data);
        inOrder(subTree->leftTree);
        inOrder(subTree->rightTree);
    }
}

// Variation of INORDER-TREE-WALK - prints the root after the values in its subtrees
void postOrder(bsTree* subTree){
    if(subTree != NULL){
        inOrder(subTree->leftTree);
        inOrder(subTree->rightTree);
        printf("%d ", subTree->data);
    }
}

// On most computers, the iterative version is more efficient.
bsTree* searchTree(bsTree* tree, int value){
    while(tree != NULL && tree->data != value){
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
bsTree* minTree(bsTree* tree){
    while(tree->leftTree != NULL){
        tree = tree->leftTree;
    }
    return tree;
}

// Find an element in a binary search tree whose key is a maximum
bsTree* maxTree(bsTree* tree){
    while(tree->rightTree != NULL){
        tree = tree->rightTree;
    }
    return tree;
}

// For node x finds the smallest key greater than x.key.
bsTree* successorTree(bsTree* tree){
    if(tree->rightTree != NULL){
        return minTree(tree->rightTree);
    }
    bsTree* temp = tree->parent;
    while(temp != NULL && tree == temp->rightTree){
        tree = temp;
        temp = temp->parent;
    }
    return temp;
}

// For node x finds the greatest key less than x.key.
bsTree* predecessorTree(bsTree* tree){
    if(tree->leftTree != NULL){
        return maxTree(tree->leftTree);
    }
    bsTree* temp = tree->parent;
    while(temp != NULL && tree == temp->leftTree){
        tree = temp;
        temp = temp->parent;
    }
    return temp;
}

// Theorem:
//     We can implement the dynamic-set operations SEARCH, MINIMUM, MAXIMUM,
//     SUCCESSOR, and PREDECESSOR so that each one runs in O(h) time on a binary
//     search tree of height h.

void insertNode(bsTree** root, int value){
    bsTree* newNode = malloc(sizeof(bsTree));
    if(newNode == NULL){
        printf("Houston, we have a problem\n");
        return;
    }
    newNode->data = value;
    newNode->leftTree = newNode->rightTree = NULL;
    bsTree* y = NULL;   // Trailing pointer maintained as the parent of x
    bsTree* temp = *root;
    while(temp != NULL){
        y = temp;
        if(newNode->data < temp->data){
            temp = temp->leftTree;
        }
        else{
            temp = temp->rightTree;
        }
    }
    newNode->parent = y;
    if(y == NULL){  // Tree was empty
        *root = newNode;
    }
    else if(newNode->data < y->data){
        y->leftTree = newNode;
    }else{
        y->rightTree = newNode;
    }
}

void transplant(bsTree** root, bsTree* u, bsTree* v){
    if(u->parent == NULL){
       *root = v;
    }
    else if(u == u->parent->leftTree){
        u->parent->leftTree = v;
    }else{
        u->parent->rightTree = v;
    }
    if(v != NULL){
        v->parent = u->parent;
    }
}

// Each line of TREE-DELETE, including the calls to TRANSPLANT, takes constant
// time, except for the call to MIN-TREE. Thus, TREE-DELETE runs
// in O(h) time on a tree of height h.
void treeDelete(bsTree** root, bsTree* z){
    if(z->leftTree == NULL){
        transplant(root, z, z->rightTree);
    }
    else if(z->rightTree == NULL){
        transplant(root, z, z->leftTree);
    }
    else{
        bsTree* y = minTree(z->rightTree);
        if(y->parent != z){
            transplant(root, y, y->rightTree);
            y->rightTree = z->rightTree;
            y->rightTree->parent = y;
        }
        transplant(root, z, y);
        y->leftTree = z->leftTree;
        y->leftTree->parent = y;
    }
    free(z);
}

// Theorem:
//     We can implement the dynamic-set operations INSERT and DELETE so that each
//     one runs in O(h) time on a binary search tree of height h.


int main(int argc, char* argv[]){
    bsTree* root = NULL;

    insertNode(&root, 14);
    insertNode(&root, 16);
    insertNode(&root, 9);
    insertNode(&root, 17);
    insertNode(&root, 8);
    insertNode(&root, 13);
    insertNode(&root, 7);
    insertNode(&root, 11);

    inOrder(root);
    printf("\n");

    bsTree* z = searchTree(root, 9);

    bsTree* a = predecessorTree(z);
    printf("%d\n", a->data);

    bsTree* b = successorTree(z);
    printf("%d\n", b->data);

    bsTree* c = minTree(root);
    printf("%d\n", c->data);

    bsTree* d = maxTree(root);
    printf("%d\n", d->data);

    treeDelete(&root, z);

    inOrder(root);
    printf("\n");
}

// In practice, we can’t always guarantee that binary search trees are built randomly,
// but we can design variations of binary search trees with good guaranteed
// worst-case performance on basic operations.
// As with quicksort, we can show that the behavior of the average case is much 
// closer to the best case than to the worst case.
// Theorem
//     The expected height of a randomly built binary search tree on n distinct keys is
//     O(lgn).
