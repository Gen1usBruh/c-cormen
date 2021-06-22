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
// Here we implement operations on singly linked lists. 

typedef struct Node{
    char value;          // store the actual key
    struct Node *next;   // pointer to the next node
} node;


int llSize(node **);   // size of linked list, aka number of nodes with actual keys
void insertNodeAtFront(node**, int);
void insertNodeAtEnd(node**, int);
void insertNodeAtPos(node **, int, int);
void deleteNodeAtPos(node **, int);
void updateValues(node **, int, int);
void updateValueAtPos(node **, int, int);
void search(node **, int);   //prints the position of the first matched key
void display(node **);


int main(){

    node *head = NULL;

    insertNodeAtFront(&head, 10);
    insertNodeAtFront(&head, 7);
    insertNodeAtEnd(&head, 12);
    display(&head);
    insertNodeAtPos(&head, 5, 0);
    insertNodeAtPos(&head, 11, 3);
    display(&head);
    deleteNodeAtPos(&head, 0);
    deleteNodeAtPos(&head, 2);
    display(&head);
    updateValueAtPos(&head, 13, 0);
    updateValueAtPos(&head, 13, 2);
    display(&head);
    updateValues(&head, 13, 12);
    display(&head);
    search(&head, 10);
    search(&head, 12);
    
    return 0;
}

int llSize(node **head){
    int cnt = 0;
    for(node *tmp = *head; tmp != NULL; tmp = tmp->next, ++cnt);
    return cnt;
} 

void insertNodeAtFront(node **head, int val){
    node *newNode = malloc(sizeof(node));
    newNode->value = val;
    newNode->next = *head;
    *head = newNode;
}

void insertNodeAtEnd(node **head, int val){
    node *current = *head;

    if(current != NULL){
        while(current->next != NULL){
            current = current->next;
        }
        current->next = malloc(sizeof(node));
        current->next->value = val;
        current->next->next = NULL;
    }
    else{
        current = malloc(sizeof(node));
        current->value = val;
        current->next = NULL;
        *head = current;
    }
}

void insertNodeAtPos(node **head, int val, int pos){
    node *newNode = malloc(sizeof(node));
    newNode->value = val;
    if(pos == 0){
        if(*head == NULL){
            *head = newNode;
            (*head)->next = NULL;
        }
        else{
            node *temp = *head;
            *head = newNode;
            (*head)->next = temp;
        }
    }
    else if(pos > 0 && pos < llSize(head)){
        node *current = *head;
        node *prev = NULL;
        for(int i = 1; i <= pos; i++){
            prev = current;
            current = current->next;
        }
        prev->next = newNode;
        newNode->next = current;
    }
    else{
        printf("Position is out of range\n");
    }
}

void deleteNodeAtPos(node **head, int pos){
    if(*head == NULL){
        printf("List is empy\n");
    }
    else{
        node *ptr = *head;
        if(pos == 0){
            *head = ptr->next;
        }
        else{
            if(pos > 0 && pos < llSize(head)){
                ptr = *head;
                node *prev = NULL;
                for(int i = 1; i <= pos; i++){
                    prev = ptr;
                    ptr = ptr->next;
                }
                prev->next = ptr->next;
            }
            else{
                printf("Position is out of range ");
            }
            free(ptr);
        }
    }
}

void updateValueAtPos(node **head, int newVal, int pos){
    if(*head != NULL){
        if(pos >= 0 && pos < llSize(head)){
            node *ptr = *head;
            for(int i = 0; ptr != NULL; ptr = ptr->next, i++){
                if(i == pos){
                    ptr->value = newVal;
                }
            }
        }
        else{
            printf("Position is out of range\n");
        }
    }
    else{
        printf("List is empty\n");
    }
}

void updateValues(node **head, int oldVal, int newVal){
    int flag = 0;
    if(*head == NULL){
        printf("List is empty\n");
    }
    else{
        for(node *ptr = *head; ptr != NULL; ptr = ptr->next){
            if(ptr->value == oldVal){
                ptr->value = newVal;
                flag = 1;
            }
        }
        if(!flag){
            printf("\nValue is not found in the List");
        }
    }
}

void search(node **head, int key){
    int flag = 0, pos = -1;

    if(*head == NULL){
        printf("List is empty\n");
    }
    else{
        for(node *ptr = *head; ptr != NULL; ptr = ptr->next){
            ++pos;
            if(ptr->value == key){
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
            printf("%d |%d --> ", current->value, i);   // i is the index [0, n)
        }    
        printf("NULL\n\n");
    }
}
