#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <inttypes.h>


// Dijkstra’s algorithm solves the single-source shortest-paths problem on a weighted,
// directed graph G = (V,E) for the case in which all edge weights are nonnegative.
// Dijkstra’s algorithm maintains a set S of vertices whose final shortest-path
// weights from the source s have already been determined. The algorithm repeatedly
// selects the vertex u ∈ V - S with the minimum shortest-path estimate, adds u
// to S, and relaxes all edges leaving u. In the following implementation, we use a
// min-priority queue Q of vertices, keyed by their d (upperBound) values.
// Because Dijkstra’s algorithm always chooses the "lightest" or "closest" vertex
// in V - S to add to set S, we say that it uses a greedy strategy.
//
// The running time of Dijkstra’s algorithm depends on how we implement the
// min-priority queue.
// Consider the case in which we maintain the min-priority.
// queue by taking advantage of the vertices being numbered 1 to |V|. We simply
// store v.d in the vth entry of an array. Total time of O(V^2 + E) = O(V^2).
//
// We can in fact achieve a running time of O(VlgV + E) by implementing the
// min-priority queue with a Fibonacci heap.

#define CAPACITY 10

typedef struct Node {
    int data;
    long long upperBound;
    int weight;
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
        if (graph->adjl[i]->parent != NULL) {
            printf(" | Parent : %d", graph->adjl[i]->parent->data);
        }
        printf("\n\n");
    }
}


void minHeapify(node** a, int i, int length) {
    int l = (i << 1) + 1;
    int r = (i << 1) + 2;
    int smallest = INT_MIN;
    if (l < length && a[l]->upperBound < a[i]->upperBound) {
        smallest = l;
    }
    else {
        smallest = i;
    }
    if (r < length && a[r]->upperBound < a[smallest]->upperBound) {
        smallest = r;
    }
    if (smallest != i) {
        node* tmp = a[i];
        a[i] = a[smallest];
        a[smallest] = tmp;
        minHeapify(a, smallest, length);
    }
}

void buildMinHeap(node** a, int length) {
    for (int i = length / 2; i >= 0; i--) {
        minHeapify(a, i, length);
    }
}

node* heapExtractMin(node** a, int length) {
    if (length < 1) {
        fprintf(stderr, "Heap underflow");
        exit(EXIT_FAILURE);
    }
    node* min = a[0];
    a[0] = a[length - 1];
    --length;
    minHeapify(a, 0, length);

    return min;
}

int isEmptyHeap(node** heap, int n) {
    for (int i = 0; i < n; i++) {
        if (heap[i] != NULL) {
            return 0;
        }
    }
    return 1;
}

int numOfV(graph* graph) {
    int j = 0;
    for (int i = 0; i < CAPACITY; i++) {
        if (graph->adjl[i] != NULL) {
            ++j;
        }
    }
    return j;
}

void dijkstra(graph* graph, int source) {
    initSingleSource(graph, source);
    int numVer = numOfV(graph);
    node* S[numVer];  
    node* heap[numVer];   
    for (int i = 0, j = 0; i < CAPACITY; i++) {
        if (graph->adjl[i] != NULL) {
            heap[j] = graph->adjl[i];
            ++j;
        }
    }
    buildMinHeap(heap, numVer);
    int k = 0;
    while (!isEmptyHeap(heap, numVer)) {
        node* u = heapExtractMin(heap, numVer);
        --numVer;
        S[k] = u;
        ++k;
        for (node* curr = u->next; curr != NULL; curr = curr->next) {
            relax(graph, u, curr);
        }
    }
}


int main(int argc, char* argv[]) {
    graph* myGraph = newGraph();

    // insert(myGraph, 1, 3, 8);   // Edge from 1 to 3 only
    // insert(myGraph, 1, 5, 5);
    // insert(myGraph, 1, 9, 4);
    // insert(myGraph, 3, 5, 3);
    // insert(myGraph, 3, 9, 9);   // --> Directed graph test
    // insert(myGraph, 5, 1, 2);
    // insert(myGraph, 7, 1, 6);
    // insert(myGraph, 7, 3, 7);
    // insert(myGraph, 9, 5, 7);
    // insert(myGraph, 9, 7, 2);

    insert(myGraph, 1, 3, 2);   // Edge from 1 to 3 only
    insert(myGraph, 1, 5, 1);
    insert(myGraph, 3, 1, 3);
    insert(myGraph, 3, 5, 9);
    insert(myGraph, 3, 9, 2);   // --> Directed graph test
    insert(myGraph, 5, 9, 4);
    insert(myGraph, 7, 1, 10);
    insert(myGraph, 7, 3, 5);
    insert(myGraph, 9, 5, 6);
    insert(myGraph, 9, 7, 7);

    // if you need a totally separate vertex in directed and undirected graphs:
    // insertNodeAtEnd(&myGraph->adjl[i], i), where i should be the of the same value 

    dijkstra(myGraph, 7);    // follow the parents and get a scheme in your head
                             // each Upperbound is the shortest path to that vertex
    dumpGraph(myGraph);

}
