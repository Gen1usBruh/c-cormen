#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAPACITY 10

typedef struct Node {
    int data;
    int discover;
    int color;
    int finish;
    struct Node* parent;
    struct Node* next;
    struct Node* prev;
} node;

typedef struct Graph {
    node** adjl;   // adjacent list
} graph;

graph* newGraph() {
    graph* initGraph = malloc(sizeof(graph));
    initGraph->adjl = malloc(sizeof(node*) * CAPACITY);
    for (int i = 0; i < CAPACITY; i++) {
        initGraph->adjl[i] = NULL;
    }

    return initGraph;
}

void insertNodeAtEnd(node** head, int value) {
    node* new_node = malloc(sizeof(node));
    node* last = *head;
    new_node->data = value;
    new_node->next = NULL;
    if (*head == NULL) {
        new_node->prev = NULL;
        *head = new_node;
        return;
    }
    while (last->next != NULL) {
        last = last->next;
    }
    new_node->prev = last;
    last->next = new_node;
}

void insert(graph* graph, int vertexIndex, int vertexAdj) {
    if (graph->adjl[vertexIndex] == NULL) {
        insertNodeAtEnd(&graph->adjl[vertexIndex], vertexIndex);   // head of the dl-list points to the actual vertex
    }
    insertNodeAtEnd(&graph->adjl[vertexIndex], vertexAdj);   // add adjacent(neighbouring) vertices after at the end
}

void dumpGraph(graph* graph) {
    for (int i = 1; i < CAPACITY; ++i) {
        node* entry = graph->adjl[i];
        if (entry == NULL) {
            continue;
        }
        printf("\nN(%d): ", i);
        for (;;) {
            entry = entry->next;
            if (entry == NULL) {
                break;
            }
            printf("%d ", entry->data);
        }
        printf("\tDiscovered: %d", graph->adjl[i]->discover);
        if (graph->adjl[i]->parent != NULL) {
            printf("   Parent: %d", graph->adjl[i]->parent->data);
        }
        printf("   Color: %d", graph->adjl[i]->color);
        printf("   Finished: %d", graph->adjl[i]->finish);
    }
}

typedef struct TopNode {
    node* data;
    struct TopNode* next;
    struct TopNode* prev;
} topNode;

topNode* myList = NULL;

void insertNodeAtFront(topNode** head, node* value) {
    topNode* new_node = malloc(sizeof(topNode));
    new_node->data = value;
    new_node->next = *head;
    new_node->prev = NULL;
    if (*head != NULL) {
        (*head)->prev = new_node;
    }
    *head = new_node;
}

void topologicalSort(node* vertex) {
    insertNodeAtFront(&myList, vertex);
}

//N(1) : 2 4 
//N(2) : 3 8 	
//N(3) : 4 	
//N(4) : 3 7 	
//N(5) : 1 2 	
//N(6) : 3 	
//N(7) : 
//N(8) : 5
void transpose(graph* oldGraph, graph* newGraph) {
    for (int i = 1; i < CAPACITY; i++) {
        if (oldGraph->adjl[i] != NULL) {
            insertNodeAtEnd(&newGraph->adjl[i], i);
            node* entry = oldGraph->adjl[i]->next;
            for (; entry != NULL; entry = entry->next) {
                insert(newGraph, entry->data, i);
                newGraph->adjl[entry->data]->finish = oldGraph->adjl[entry->data]->finish;
            }
        }
    }
    
}

int time = 0;
void DFSVisit(graph* graph, node* u) {
    ++time;
    u->discover = time;
    u->color = 1;   //gray

    node* entry = u;
    for (; entry != NULL; entry = entry->next) {
        if (graph->adjl[entry->data]->color == 0) {
            graph->adjl[entry->data]->parent = u;
            DFSVisit(graph, graph->adjl[entry->data]);
        }
    }

    u->color = 2;   //black
    ++time;
    u->finish = time;
    topologicalSort(u);
}
void DFS(graph* graph) {
    for (int i = 0; i < CAPACITY; i++) {
        if (graph->adjl[i] != NULL) {
            graph->adjl[i]->color = 0;   //white
            graph->adjl[i]->parent = NULL;
        }
    }
    for (int i = 0; i < CAPACITY; i++) {
        if (graph->adjl[i] != NULL) {
            if (graph->adjl[i]->color == 0) {
                DFSVisit(graph, graph->adjl[i]);
            }
        }
    }

}

void DFSVisitTrans(graph* graph, node* u) {
    ++time;
    u->discover = time;
    u->color = 1;   //gray

    node* entry = u;
    for (; entry != NULL; entry = entry->next) {
        if (graph->adjl[entry->data]->color == 0) {
            graph->adjl[entry->data]->parent = u;
            DFSVisit(graph, graph->adjl[entry->data]);
        }
    }

    u->color = 2;   //black
    ++time;
    u->finish = time;
}

void strongCC(graph* oldGraph, graph* newGraph) {
    DFS(oldGraph);
    transpose(oldGraph, newGraph);
    time = 0;
    for (int i = 0; i < CAPACITY; i++) {
        if (newGraph->adjl[i] != NULL) {
            newGraph->adjl[i]->color = 0;
            newGraph->adjl[i]->parent = NULL;
        }
    }
    topNode* current = myList;
    for (; current != NULL; current = current->next) {
        if (newGraph->adjl[current->data->data] != NULL) {
            if (newGraph->adjl[current->data->data]->color == 0) {
                DFSVisitTrans(newGraph, newGraph->adjl[current->data->data]);
            }
        }
    }
}


int main(int argc, char** argv) {
    graph* myGraph = newGraph();

    graph* trans = newGraph();

     insert(myGraph, 1, 5);
     insert(myGraph, 2, 1);   
     insert(myGraph, 2, 3);
     insert(myGraph, 2, 8);
     insert(myGraph, 3, 2);   
     insert(myGraph, 3, 4);
     insert(myGraph, 4, 1);   // --> Directed graph test
     insert(myGraph, 4, 7);
     insert(myGraph, 5, 8);
     insert(myGraph, 6, 3);  
     insert(myGraph, 6, 6);
     insert(myGraph, 6, 7);
     insert(myGraph, 7, 4);   
     insert(myGraph, 8, 1);

    //insert(myGraph, 1, 2);
    //insert(myGraph, 1, 4);
    //insert(myGraph, 2, 3);
    //insert(myGraph, 2, 8);
    //insert(myGraph, 3, 4);
    //insert(myGraph, 4, 3);
    //insert(myGraph, 4, 7);   // --> Directed graph test
    //insert(myGraph, 5, 1);
    //insert(myGraph, 5, 2);
    //insert(myGraph, 6, 3);
    //insert(myGraph, 8, 5);
    //insertNodeAtEnd(&myGraph->adjl[7], 7);   //create an empty node, since vertex at 7 points to nowhere 

    DFS(myGraph);

    strongCC(myGraph, trans);

    dumpGraph(myGraph);

    printf("\n\n");

    dumpGraph(trans);

    printf("\n\n");

}
