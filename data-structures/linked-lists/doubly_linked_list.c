#include <stdio.h>
#include <stdlib.h>

// A linked list is a data structure in which the objects are arranged in a linear order.
// Unlike an array, however, in which the linear order is determined by the array
// indices, the order in a linked list is determined by a pointer in each object.
//
// A list may have one of several forms. It may be either singly linked or doubly
// linked, it may be sorted or not, and it may be circular or not. If a list is singly
// linked, we omit the pointer to the previous node in each element. If a list is sorted, the linear order
// of the list corresponds to the linear order of keys stored in elements of the list; the
// minimum element is then the head of the list, and the maximum element is the
// tail. If the list is unsorted, the elements can appear in any order. In a circular list,
// the pointer to the previous node of the head of the list points to the tail, and the next pointer of
// the tail of the list points to the head.
//
// Here we implement operations on doubly linked lists. 

typedef struct Node{
    int data;           // store the actual key
    struct Node *next;  // pointer to the next node
    struct Node *prev;  // pointer to the previous node
} node;

void insertNodeAtFront(node **, int);
void insertNodeAfter(node *, int);
void insertNodeAtEnd(node **, int);
void deleteNode(node** , node*);
void search(node **, int);
void display(node **);


int main(){

    node *head = NULL;

    search(&head, 10);
    insertNodeAtFront(&head, 10);
    insertNodeAtFront(&head, 7);
    insertNodeAtEnd(&head, 12);
    display(&head);
    insertNodeAfter(head->next, 5);
    insertNodeAfter(head->next->next->next, 11);
    display(&head);
    deleteNode(&head, head->next);
    deleteNode(&head, head);
    display(&head);
    search(&head, 10);
    search(&head, 12);
    
    return 0;
}

void insertNodeAtFront(node **head, int value){
    node *new_node = malloc(sizeof(node));
    new_node->data = value;
    new_node->next = *head;
    new_node->prev = NULL;
    if(*head != NULL){
        (*head)->prev = new_node;
    }
    *head = new_node;
}
void insertNodeAfter(node *current, int value){
    if(current == NULL){
        return;
    }
    node *new_node = malloc(sizeof(node));
    new_node->data = value;
    new_node->next = current->next;
    new_node->prev = current;
    current->next = new_node;
    if(new_node->next != NULL){
        new_node->next->prev = new_node;
    }
}
void insertNodeAtEnd(node **head, int value){
    node *new_node = malloc(sizeof(node));
    node *last = *head;
    new_node->data = value;
    new_node->next = NULL;
    if(*head == NULL){
        new_node->prev = NULL;
        *head = new_node;
        return;
    }
    while(last->next != NULL){
        last = last->next;
    }   
    new_node->prev = last;
    last->next = new_node;
}
void deleteNode(node** head, node* toBeDel){
    if(*head == NULL || toBeDel == NULL){
        return;
    }
    if(*head == toBeDel){
        *head = toBeDel->next;
    }
    if(toBeDel->next != NULL){
        toBeDel->next->prev = toBeDel->prev;
    }
    if(toBeDel->prev != NULL){
        toBeDel->prev->next = toBeDel->next;
    }
    free(toBeDel);
}
void search(node **head, int key){
    int flag = 0, pos = -1;

    if(*head == NULL){
        printf("List is empty\n");
    }
    else{
        for(node *ptr = *head; ptr != NULL; ptr = ptr->next){
            ++pos;
            if(ptr->data == key){
                flag = 1;
                break;
            }
        }
        if(flag){
            printf("\nElement %d found at %d position\n", key, pos);
        }
        else
        {
            printf("\nElement %d not found in list\n", key);
        }
    }
}
void display(node **head){
    node *current = *head;
    if(current == NULL){
        printf("List is empty.\n\n");
    }
    else{
        printf("The list is:\n");
        for(int i = 0; current != NULL; current = current->next, i++){
            printf("%d |%d --> ", current->data, i);   // i is the index [0, n)
        }    
        printf("NULL\n\n");
    }
}
