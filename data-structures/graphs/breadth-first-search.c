#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Breadth-first search is one of the simplest algorithms for searching a graph and
// the archetype for many important graph algorithms.
// Given a graph G = (V,E) and a distinguished source vertex s, breadth-first
// search systematically explores the edges of G to "discover" every vertex that is
// reachable from s. It computes the distance (smallest number of edges) from s
// to each reachable vertex. It also produces a "breadth-first tree" with root s that
// contains all reachable vertices (attribute "parent"). For any vertex v reachable from s, the simple path
// in the breadth-first tree from s to v corresponds to a "shortest path" from s to v
// in G, that is, a path containing the smallest number of edges. The algorithm works
// on both directed and undirected graphs.
// Breadth-first search is so named because it expands the frontier between discovered
// and undiscovered vertices uniformly across the breadth (width) of the frontier. That
// is, the algorithm discovers all vertices at distance k from s before discovering any
// vertices at distance k + 1.
// To keep track of progress, breadth-first search colors each vertex white, gray, or
// black. All vertices start out white and may later become gray and then black. A
// vertex is discovered the first time it is encountered during the search, at which time
// it becomes nonwhite. If (u,v) ∈ E and vertex u is black, then vertex v
// is either gray or black; that is, all vertices adjacent to black vertices have been
// discovered. Gray vertices may have some adjacent white vertices; they represent
// the frontier between discovered and undiscovered vertices.
//
// Time complexity of the BFS procedure is O(V + E)
// where G = (V,E).


#define CAPACITY 10

typedef struct Node {
    int data;        // "data" argument is required to store the actual values of graph vertices and access them later on
    int path;        // length of path from the source vertex to another
    int color;
    struct Node* parent;   
    struct Node* next;
    struct Node* prev;
} node;

typedef struct Graph {
    node** adjl;   // adjacent list itself
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
        printf("\tPath: %d", graph->adjl[i]->path);
        if(i > 1){
            printf("   Parent: %d", graph->adjl[i]->parent->data);
        }
        printf("   Color: %d", graph->adjl[i]->color);
    }
}

typedef struct Queue_ {
    node* qArr[CAPACITY];
    int head, tail;
} queue_;

void initQueue(queue_* q) {
    for (int i = 0; i < CAPACITY; i++) {
        q->qArr[i] = NULL;
    }
}
void enQueue_(queue_* q, node* key) {
    if (q->tail == CAPACITY - 1) {
        printf("Queue overflow\n");
    }
    else {
        if (q->head == -1) {
            q->head = 0;
        }
        ++(q->tail);
        q->qArr[q->tail] = key;
    }
}
node* deQueue_(queue_* q) {
    if (q->head == -1 || q->head > q->tail) {
        printf("Queue underflow\n");
        return NULL;
    }
    else {
        ++(q->head);
        node* temp = q->qArr[q->head - 1];  
        q->qArr[q->head - 1] = NULL;        
        return temp;     
    }
}
node* isEmptyQ(queue_* q) {               // weird implementation of this function - head and tail do not correctly tell anything
    for(int i = 0; i < CAPACITY; i++){    // so I used this trick -> overhead (could not think of anything better \ö/)
        if(q->qArr[i] != NULL){
            return q->qArr[i];
        }        
    }
    return NULL;
}

void BFS(graph* graph, int vertexIndex) {
    for (int i = 0; i < CAPACITY; i++) {
        if (graph->adjl[i] != NULL) { 
            graph->adjl[i]->color = 0;   //white
            graph->adjl[i]->path = INT_MAX;
            graph->adjl[i]->parent = NULL;
        }
    }
    graph->adjl[vertexIndex]->color = 1;   //gray
    graph->adjl[vertexIndex]->path = 0;
    graph->adjl[vertexIndex]->parent = NULL;
    queue_ q;
    q.head = q.tail = -1;
    initQueue(&q);
    enQueue_(&q, graph->adjl[vertexIndex]);
    while(isEmptyQ(&q) != NULL){
        node* u = deQueue_(&q);
        node* entry = u;
        for(; entry != NULL; entry = entry->next) {
            if(graph->adjl[entry->data]->color == 0){
                graph->adjl[entry->data]->color = 1;
                graph->adjl[entry->data]->path = u->path + 1;
                graph->adjl[entry->data]->parent = u;
                enQueue_(&q, graph->adjl[entry->data]);
            }
            u->color = 2;  //black
        }
    }
}

// Analysis:
//   The operations of
//   enqueuing and dequeuing take O(1) time, and so the total time devoted to queue
//   operations is O(V). Because the procedure scans the adjacency list of each vertex
//   only when the vertex is dequeued, it scans each adjacency list at most once. Since
//   the sum of the lengths of all the adjacency lists is θ(E), the total time spent in
//   scanning adjacency lists is O(E). The overhead for initialization is O(V), and
//   thus the total running time of the BFS procedure is O(V + E). Thus, breadth-first
//   search runs in time linear in the size of the adjacency-list representation of G.
//
//   But in my implementation not all things are as they've been stated above


int main(int argc, char* argv[]) {
    graph* myGraph = newGraph();

    // insert(myGraph, 1, 2);
    // insert(myGraph, 1, 5);
    // insert(myGraph, 2, 1);
    // insert(myGraph, 2, 5);
    // insert(myGraph, 2, 3);
    // insert(myGraph, 2, 4);
    // insert(myGraph, 3, 2);       ---> First graph for test
    // insert(myGraph, 3, 4);
    // insert(myGraph, 4, 2);
    // insert(myGraph, 4, 5);
    // insert(myGraph, 4, 3);
    // insert(myGraph, 5, 4);
    // insert(myGraph, 5, 1);
    // insert(myGraph, 5, 2);
    
    // if you need a node in directed graph that points to nowhere, or in undirected graph a totally separate vertex, then:
    // insertNodeAtEnd(&myGraph->adjl[i], i), where i should be the of the same value 

    insert(myGraph, 1, 4);   // second argument is the source vertex, third is the neighbour
    insert(myGraph, 1, 9);
    insert(myGraph, 1, 7);
    insert(myGraph, 2, 4);
    insert(myGraph, 2, 9);
    insert(myGraph, 3, 5);
    insert(myGraph, 4, 1);
    insert(myGraph, 4, 2);
    insert(myGraph, 4, 9);
    insert(myGraph, 5, 3);      // ---> Second graph for test
    insert(myGraph, 5, 8);
    insert(myGraph, 7, 1);
    insert(myGraph, 7, 8);
    insert(myGraph, 7, 9);
    insert(myGraph, 8, 5);
    insert(myGraph, 8, 7);
    insert(myGraph, 9, 1);
    insert(myGraph, 9, 4);
    insert(myGraph, 9, 2);
    insert(myGraph, 9, 7);

    BFS(myGraph, 1);

    dumpGraph(myGraph);

}
