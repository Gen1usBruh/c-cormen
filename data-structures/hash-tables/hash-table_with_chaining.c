#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 23

typedef struct Node{
    int data;        
    struct Node *next;  
    struct Node *prev;  
} node;

node* table[MAXSIZE] = {NULL};

unsigned hash(char* key);
void insertNodeAtEnd(node **head, int value);
void insert(char* key, int value);
void display(void);


int main(int argc, char* argv[]){
    
    insert("amir", 12);
    insert("mapelle", 13);
    insert("azim", 17);
    insert("dfgdfg", 19);
    insert("usyuvfs", 15);
    insert("amidfg", 12);
    insert("mapeldsfle", 13);
    insert("azidsfm", 17);
    insert("dfgddfgfg", 19);
    insert("usyuvdfvfs", 15);
    insert("amsdfir", 12);
    insert("mapsredfelle", 13);
    insert("azimfdg", 17);
    insert("dfewtgdfg", 19);
    insert("usyxcvbuvfs", 15);
    insert("amirfdg", 12);
    insert("mapserelle", 13);
    insert("azidgm", 17);
    insert("dfgdhdfsdfg", 19);
    insert("usywwruvfs", 15);

    display();

}


unsigned hash(char *key){
    unsigned hval;
    for(hval = 0; *key != '\0'; key++){
        hval = *key + 31 * hval;
    }
    return hval % MAXSIZE;
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

void insert(char* key, int value){
    printf("User key: %s --> ", key);
    unsigned hashedKey = hash(key);
    printf("It's hash: %d\n", key);
    if(table[hashedKey] == NULL){
        node* slotHead = NULL;
        insertNodeAtEnd(&slotHead, value);
        table[hashedKey] = slotHead;
    }
    else{
        insertNodeAtEnd(&table[hashedKey], value);
    }
}

void display(void){
    for(int i = 0; i < MAXSIZE; i++){
        if(table[i] != NULL){
            printf("[ %d ] --> ", i);
            for(node* temp = table[i]; temp != NULL; temp = temp->next){
                printf("| %d | -- ", temp->data);
            }
            printf("NULL\n");
            printf("||\n");
        }
    }
}
