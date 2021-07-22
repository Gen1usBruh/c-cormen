#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <inttypes.h>

// The Bellman-Ford algorithm solves the single-source shortest-paths problem in
// the general case in which edge weights may be negative. Given a weighted, directed
// graph G = (V,E) with source s and weight function w : E -> R, the
// Bellman-Ford algorithm returns a boolean value indicating whether or not there is
// a negative-weight cycle that is reachable from the source. If there is such a cycle,
// the algorithm indicates that no solution exists. If there is no such cycle, the
// algorithm produces the shortest paths and their weights.
//
// The Bellman-Ford algorithm runs in time O(VE), where E = O(V^2)
//
// Lemma:
//     Let G = (V,E) be a weighted, directed graph with source s and weight function
//     w : E -> R, and assume that G contains no negative-weight cycles that are
//     reachable from s. Then, after the |V| - 1 iterations of the very first for loop
//     of BELLMAN-FORD, we have v.d = 𝛿(s,v) for all vertices v that are reachable
//     from s (If we have more than |V| - 1, we will get into cycle). 

#define CAPACITY 10

typedef struct Node {
    int data;
    long long upperBound;   // shortest-path estimate (or current weight, so it can be updated)
    struct Node* parent;   // define sequnce of vertices that corresponds to min-weight path
    struct Node* next;
    struct Node* prev;
    int weight;
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

void insertNodeAtEnd(node** head, int value, int weight_) {
    node* new_node = malloc(sizeof(node));
    node* last = *head;
    new_node->data = value;
    new_node->weight = weight_;
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

// here the data each vertex represents is reflected on
// the position in array
void insert(graph* graph, int vertexIndex, int vertexAdj, int weight_) {
    if (graph->adjl[vertexIndex] == NULL) {
        insertNodeAtEnd(&graph->adjl[vertexIndex], vertexIndex, 0);
    }
    if (graph->adjl[vertexAdj] == NULL) {
        insertNodeAtEnd(&graph->adjl[vertexAdj], vertexAdj, 0);
    }
    insertNodeAtEnd(&graph->adjl[vertexIndex], vertexAdj, weight_);
}

void initSingleSource(graph* graph, int source) {
    for (int i = 0; i < CAPACITY; i++) {
        if (graph->adjl[i] != NULL) {
            graph->adjl[i]->upperBound = INT_MAX;
            graph->adjl[i]->parent = NULL;
        }
    }
    graph->adjl[source]->upperBound = 0;
}

void relax(graph* graph, node* u, node* v) {
    if (graph->adjl[v->data]->upperBound > u->upperBound + v->weight) {
        graph->adjl[v->data]->upperBound = u->upperBound + v->weight;
        graph->adjl[v->data]->parent = u;
    }
}

int bellmanFord(graph* graph, int source) {
    initSingleSource(graph, source);
    for (int i = 1; i < CAPACITY - 1; i++) {  // this loop is not bounded with the number of vertices
        if (graph->adjl[i] != NULL) {         // rather with the data a vertex is represented with
            for (int j = 0; j < CAPACITY; j++) {
                if (graph->adjl[j] != NULL) {
                    for (node* curr = graph->adjl[j]->next; curr != NULL; curr = curr->next) {
                        relax(graph, graph->adjl[j], curr);
                    }
                }
            }
        }
    }
    for (int j = 0; j < CAPACITY; j++) {
        if (graph->adjl[j] != NULL) {
            for (node* curr = graph->adjl[j]->next; curr != NULL; curr = curr->next) {
                if (graph->adjl[curr->data]->upperBound > graph->adjl[j]->upperBound + curr->weight) {
                    return 0;
                }
            }
        }
    }
    return 1;
}

void dumpGraph(graph* graph) {
    for (int i = 1; i < CAPACITY; ++i) {
        node* entry = graph->adjl[i];
        if (entry == NULL) {
            continue;
        }
        printf("V(%d): ", i);
        for (;;) {
            entry = entry->next;
            if (entry == NULL) {
                break;
            }
            printf("%d ", entry->data);
        }
        printf("\n  |___");
        printf("UpperBound : %"PRId64"", graph->adjl[i]->upperBound);
        if (i != 7) {  // source has no parent
            printf(" | Parent : %d", graph->adjl[i]->parent->data);
        }
        printf("\n\n");
    }
}

int main(int argc, char* argv[]) {
    graph* myGraph = newGraph();

    insert(myGraph, 1, 3, 8);   // Edge from 1 to 3 only
    insert(myGraph, 1, 5, 5);
    insert(myGraph, 1, 9, -4);
    insert(myGraph, 3, 5, -3);
    insert(myGraph, 3, 9, 9);   // --> Directed graph test
    insert(myGraph, 5, 1, -2);
    insert(myGraph, 7, 1, 6);
    insert(myGraph, 7, 3, 7);
    insert(myGraph, 9, 5, 7);
    insert(myGraph, 9, 7, 2);

    // if you need a totally separate vertex in directed and undirected graphs:
    // insertNodeAtEnd(&myGraph->adjl[i], i, 0)  ,where i should be the of the same value 

    printf("%d\n\n", bellmanFord(myGraph, 7));   // follow the parents and get a scheme in your head
                                                 // each Upperbound is the shortest path to that vertex
    dumpGraph(myGraph);

}
