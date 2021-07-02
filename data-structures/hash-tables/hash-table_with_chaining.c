#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simple implementation of hash table with chaining using doubly linked list and array of constant size
// No operation (function) provided supports error-checking

// Implementation of hash table with string value instead and singly linked list: https://github.com/engineer-man/youtube/blob/master/077/hashtable.c

#define CAPACITY 701

typedef struct Node{
    char *key;
    int data;        
    struct Node *next;  
    struct Node *prev;  
} node;

typedef struct HashTable{
    node** entries;
} hashTable;


unsigned int hash(const char *key) {
    unsigned long int value = 0;
    unsigned int i = 0;
    unsigned int key_len = strlen(key);
    for(; i < key_len; ++i){
        value = value * 37 + key[i];
    }
    value = value % CAPACITY;

    return value;
}

hashTable* newHashTable(){
    hashTable* table = malloc(sizeof(hashTable));
    table->entries = malloc(sizeof(node*) * CAPACITY);
    for(int i = 0; i < CAPACITY; i++){
        table->entries[i] = NULL;
    }

    return table; 
}

void insertNodeAtEnd(node **head, const char* key, int value){
    node *new_node = malloc(sizeof(node));
    node *last = *head;
    new_node->key = malloc(strlen(key) + 1);
    strcpy(new_node->key, key);
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

node* search(node* tryNode, const char* key){
    if(tryNode == NULL){
        return NULL;
    }

    for(node* temp = tryNode; temp != NULL; temp = temp->next){
        if(strcmp(temp->key, key) == 0){
            return temp;
        }
    }
}

void insert(hashTable* table, const char* key, int value){
    unsigned int slot = hash(key);
    
    node* entry = search(table->entries[slot], key);

    if(entry == NULL){
        insertNodeAtEnd(&table->entries[slot], key, value);
    }
    else{
        entry->data = value;
    }  
}

int popKey(hashTable* table, const char* key){
    unsigned int slot = hash(key);
    node* entry = search(table->entries[slot], key);
    if(entry == NULL){
        return 0;
    }
    else{
        return entry->data;
    }
}

void deleteKey(hashTable* table, const char* key){
    unsigned int slot = hash(key);
    node* entry = table->entries[slot];
    if(entry == NULL) {
        return;
    }
    int idx = 0;

    while(entry != NULL) {
        if(strcmp(entry->key, key) == 0) {
            // first item and no next entry
            if(entry->next == NULL && idx == 0) {
                table->entries[slot] = NULL;
            }
            // first item with a next entry
            if(entry->next != NULL && idx == 0) {
                table->entries[slot] = entry->next;
                entry->next->prev = table->entries[slot];
                entry->prev = entry->next = NULL;
            }
            // last item
            if(entry->next == NULL && idx != 0) {
                entry->prev->next = NULL;
                entry->prev = NULL;
            }
            // middle item
            if(entry->next != NULL && idx != 0) {
                entry->prev->next = entry->next;
                entry->next->prev = entry->prev;
                entry->prev = entry->next = NULL;
            }

            free(entry->key);
            free(entry);

            return;
        }

        entry = entry->next;
        ++idx;
    }
}

void dumpHashTable(hashTable* table) {
    for (int i = 0; i < CAPACITY; ++i) {
        node* entry = table->entries[i];

        if (entry == NULL) {
            continue;
        }

        printf("slot[%4d]: ", i);

        for(;;) {
            printf("%s = %d ", entry->key, entry->data);

            if (entry->next == NULL) {
                break;
            }

            entry = entry->next;
        }

        printf("\n");
    }
}


int main(int argc, char* argv[]){
    hashTable* myTable = newHashTable();
    
    insert(myTable, "name1", 1);
    insert(myTable, "name2", 2);
    insert(myTable, "name3", 3);
    insert(myTable, "name4", 4);
    insert(myTable, "name5", 5);
    insert(myTable, "name6", 6);
    insert(myTable, "name7", 7);

    dumpHashTable(myTable);
    printf("\n");

    insert(myTable, "name1", 8);
    
    deleteKey(myTable, "name1");
    dumpHashTable(myTable);
    printf("\n");

    insert(myTable, "name1", 1);

    dumpHashTable(myTable);

    printf("%d", popKey(myTable, "name1"));

}
