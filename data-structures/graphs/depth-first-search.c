#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

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
        insertNodeAtEnd(&graph->adjl[vertexIndex], vertexIndex);
    }
    insertNodeAtEnd(&graph->adjl[vertexIndex], vertexAdj);
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

int time = 0;   // helper variable
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


int main(int argc, char* argv[]) {
    graph* myGraph = newGraph();

    /*insert(myGraph, 1, 4);
    insert(myGraph, 1, 9);
    insert(myGraph, 1, 7);
    insert(myGraph, 2, 4);
    insert(myGraph, 2, 9);
    insert(myGraph, 3, 5);
    insert(myGraph, 4, 1);
    insert(myGraph, 4, 2);
    insert(myGraph, 4, 9);
    insert(myGraph, 5, 3);    --> Undirected graph test (add corrections to dumpGraph, if errors occur)
    insert(myGraph, 5, 8);
    insert(myGraph, 7, 1);
    insert(myGraph, 7, 8);
    insert(myGraph, 7, 9);
    insert(myGraph, 8, 5);
    insert(myGraph, 8, 7);
    insert(myGraph, 9, 1);
    insert(myGraph, 9, 4);
    insert(myGraph, 9, 2);
    insert(myGraph, 9, 7);*/

    insert(myGraph, 1, 3);   // Edge from 1 to 3 only
    insert(myGraph, 2, 1);
    insert(myGraph, 3, 2);
    insert(myGraph, 5, 1);   // --> Directed graph test
    insert(myGraph, 5, 2);
    insert(myGraph, 7, 3);
    insert(myGraph, 7, 8);
    insert(myGraph, 8, 8);

    DFS(myGraph);

    dumpGraph(myGraph);

}
