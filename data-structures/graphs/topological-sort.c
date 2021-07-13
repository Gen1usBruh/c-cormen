#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// A topological sort of a a directed acyclic graph (dag), G = (V,E) is a linear ordering 
// of all its vertices such that if G contains an edge (u, v), then u appears before v in 
// the ordering. (If the graph contains a cycle, then no linear ordering is possible.) 
// We can view a topological sort of a graph as an ordering of its vertices along a 
// horizontal line so that all directed edges go from left to right.
    
// Lemma:
//     A directed graph G is acyclic if and only if a depth-first search of G yields no back edges.  

// Running time is θ(V + E).


#define CAPACITY 10

typedef struct Node {
    int data;
    int discover;            
    int finish;              
    int color;                                       
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


typedef struct TopNode {
    node* data;
    struct TopNode* next;
    struct TopNode* prev;
} topNode;

topNode* myList = NULL;

void insertNodeAtFront(topNode **head, node* value){
    topNode *new_node = malloc(sizeof(topNode));
    new_node->data = value;
    new_node->next = *head;
    new_node->prev = NULL;
    if(*head != NULL){
        (*head)->prev = new_node;
    }
    *head = new_node;
}

void topologicalSort(node* vertex){
    insertNodeAtFront(&myList, vertex);
}

int time = 0;   // helper variable for timestamping
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

void display(topNode **head){
    topNode *current = *head;
    if(current == NULL){
        printf("List is empty.\n\n");
    }
    else{
        printf("The list is:\n");
        for(int i = 0; current != NULL; current = current->next, i++){
            printf("%d |%d --> ", current->data->data, i);   // display the vertex and i is the index [0, n)
        }    
        printf("NULL\n\n");
    }
}


int main(int argc, char* argv[]) {
    graph* myGraph = newGraph();

    insert(myGraph, 1, 3);   // Edge from 1 to 3 only
    insert(myGraph, 2, 1);
    insert(myGraph, 3, 2);
    insert(myGraph, 5, 1);   // --> Directed graph test
    insert(myGraph, 5, 2);
    insert(myGraph, 7, 3);
    insert(myGraph, 7, 8);
    insert(myGraph, 8, 8);

    DFS(myGraph);

    display(&myList);

}
