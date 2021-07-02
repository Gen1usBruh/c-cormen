#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAPACITY 701

typedef struct Slot{
    int deleteMe;
    char *key;
    int data;         
} slot;

typedef struct HashTable{
    slot** entries;
} hashTable;

hashTable* newHashTable(){
    hashTable* table = malloc(sizeof(hashTable));
    table->entries = malloc(sizeof(slot*) * CAPACITY);
    for(int i = 0; i < CAPACITY; i++){
        table->entries[i] = NULL;
    }

    return table;
}

// Simple linear probing
unsigned int hash(const char* key, int trialCount){
    unsigned long int value = 0;
    unsigned int i = 0;
    unsigned int key_len = strlen(key);
    for(; i < key_len; ++i){
        value = value * 37 + key[i];
    }
    value = (value + trialCount) % CAPACITY;

    return value;
}

void insert(hashTable* table, const char* key, int value){
    unsigned int hashedKey;
    int i = 0;
    for(; i <= CAPACITY; i++){
        hashedKey = hash(key, i);
        if(table->entries[hashedKey] == NULL){
            slot* newSlot = malloc(sizeof(slot));
            newSlot->key = malloc(strlen(key) + 1);
            strcpy(newSlot->key, key);
            newSlot->data = value;
            newSlot->deleteMe = 0;   
            table->entries[hashedKey] = newSlot;
            return;
        }
        else if(strcmp(table->entries[hashedKey]->key, key) == 0){
            table->entries[hashedKey]->data = value;
            return;
        }
        else{
            table->entries[hashedKey]->deleteMe = 1;
        }
    }
    printf("Hash Table Overflow\n");
}

void delete(hashTable* table, const char* key){
    int i = 0;
    for(; i <= CAPACITY; i++){
        if(table->entries[hash(key, i)] != NULL && table->entries[hash(key, i)]->deleteMe == 1){
            if(strcmp(table->entries[hash(key, i)]->key, key) == 0){
                free(table->entries[hash(key, i)]->key);
                free(table->entries[hash(key, i)]);
                table->entries[hash(key, i)] = NULL;
                return;
            }
            else{
                continue;
            }
        }
        else if(table->entries[hash(key, i)] != NULL && table->entries[hash(key, i)]->deleteMe == 0){

            free(table->entries[hash(key, i)]->key);
            free(table->entries[hash(key, i)]);
            table->entries[hash(key, i)] = NULL;
            return;
        }
        else{
            printf("No such element found\n");
            return;
        }
    }
}

int pop(hashTable* table, const char* key){
    int i = 0;
    for(; i <= CAPACITY; i++){
        if(table->entries[hash(key, i)] != NULL && table->entries[hash(key, i)]->deleteMe == 1){
            if(strcmp(table->entries[hash(key, i)]->key, key) == 0){
                return table->entries[hash(key, i)]->data;
            }
            else{
                continue;
            }
        }
        else if(table->entries[hash(key, i)] != NULL && table->entries[hash(key, i)]->deleteMe == 0){
            return table->entries[hash(key, i)]->data;
        }
        else{
            printf("No such element found. Exit status: ");
            return EXIT_FAILURE;
        }
    }
}

void dump(hashTable* table){
    for (int i = 0; i < CAPACITY; ++i) {
        slot* entry = table->entries[i];

        if (entry == NULL) {
            continue;
        }

        printf("slot[%4d]: ", i);

        printf("%s = %d ", entry->key, entry->data);

        printf("\n");
    }
}

// Search() subroutine can be implemented using the logic, like in delete() or pop() above

int main(int argc, char* argv[]){
    
    hashTable* myTable = newHashTable();

    insert(myTable, "amir", 17);
    insert(myTable, "azin", 24);   // hashed key is 1
    insert(myTable, "aZMZ", 42);   // hashed key is also 1
    insert(myTable, "munisa", 26);
    dump(myTable);

    printf("\n%d\n", pop(myTable, "aZMZ"));
    printf("%d", pop(myTable, "adsaa"));
    printf("\n\n");

    delete(myTable, "azin");
    // delete(myTable, "aZMZ");
    dump(myTable);

    printf("\n");
    insert(myTable, "azin", 24);
    // insert(myTable, "aZMZ", 42);
    dump(myTable);

}
