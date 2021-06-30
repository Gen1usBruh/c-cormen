#include <stdio.h>
#include <stdlib.h>

// Simple implementation of hash table with chaining using doubly linked list and array of constant size
// No operation (function) provided supports error-checking

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
node* search(unsigned key);
void delete(char* key);
void display(void);


int main(int argc, char* argv[]){
    
    insert("amir", 1);
    insert("mapelle", 2);
    insert("azim", 3);
    insert("dfgdfg", 4);
    insert("usyuvfs", 5);
    insert("amidfg", 6);
    insert("mapeldsfle", 7);
    insert("azidsfm", 8);
    insert("dfgddfgfg", 9);
    insert("usyuvdfvfs", 10);
    insert("amsdfir", 11);
    insert("mapsredfelle", 12);
    insert("azimfdg", 13);
    insert("dfewtgdfg", 14);
    insert("usyxcvbuvfs", 15);
    insert("amirfdg", 16);
    insert("mapserelle", 17);
    insert("azidgm", 18);
    insert("dfgdhdfsdfg", 19);
    insert("usywwruvfs", 20);

    display();
    
    printf("\n\n");

    delete("azim");
    delete("dfgddfgfg");

    printf("\n\n");

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
    printf("It's hash: %d\n", hashedKey);
    if(table[hashedKey] == NULL){
        node* slotHead = NULL;
        insertNodeAtEnd(&slotHead, value);
        table[hashedKey] = slotHead;
    }
    else{
        insertNodeAtEnd(&table[hashedKey], value);
    }
}

void delete(char* key){
    unsigned hashedKey = hash(key);
    node* temp = table[hashedKey];
    if(temp->next == NULL){
        table[hashedKey] = NULL;
        free(temp);
    }
    else{
        int num;
        printf("Enter the value of the key: ");
        scanf("%d", &num);
        temp = table[hashedKey];
        for(; temp != NULL; temp = temp->next){
            if(temp->data == num){
                break;
            }
        }
        if(temp == NULL){
            printf("No such value");
        }
        else if(temp == table[hashedKey]){
            temp->next->prev = NULL;
            table[hashedKey] = temp->next;
            temp->next = NULL;
        }
        else if(temp->next == NULL){
            temp->prev->next = NULL;
            temp->prev = NULL;
        }
        else{
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            temp->next = temp->prev = NULL;
        }
        free(temp);
    }

    printf("\n\nDeletion completed!\n\n");
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
