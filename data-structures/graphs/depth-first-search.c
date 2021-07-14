#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// The strategy followed by depth-first search is, as its name implies, to search
// "deeper" in the graph whenever possible.Depth-first search explores edges out
// of the most recently discovered vertex v that still has unexplored edges leaving it.
// Once all of v’s edges have been explored, the search "backtracks" to explore edges
// leaving the vertex from which v was discovered. This process continues until we
// have discovered all the vertices that are reachable from the original source vertex.
// If any undiscovered vertices remain, then depth-first search selects one of them as
// a new source, and it repeats the search from that source. The algorithm repeats this
// entire process until it has discovered every vertex.
// As in breadth-first search, whenever depth-first search discovers a vertex v during
// a scan of the adjacency list of an already discovered vertex u, it records this
// event by setting v’s predecessor attribute v.p (or v.parent) to u. Unlike breadth-first search,
// whose predecessor subgraph forms a tree, the predecessor subgraph produced by
// a depth-first search may be composed of several trees, because the search may
// repeat from multiple sources.
// As in breadth-first search, depth-first search colors vertices during the search to
// indicate their state. Each vertex is initially white, is grayed when it is discovered
// in the search, and is blackened when it is finished, that is, when its adjacency list
// has been examined completely. This technique guarantees that each vertex ends up
// in exactly one depth-first tree, so that these trees are disjoint.
// Besides creating a depth-first forest, depth-first search also timestamps each vertex.
// Each vertex v has two timestamps: the first timestamp v.d (or v.discover) records when v
// is first discovered (and grayed), and the second timestamp v.f (or v.finish) records when the
// search finishes examining v’s adjacency list (and blackens v).These timestamps
// provide important information about the structure of the graph and are generally
// helpful in reasoning about the behavior of depth-first search.
//
//The running time of DFS is θ(V + E).

#define CAPACITY 10

typedef struct Node {
    int data;
    int discover;            // The procedure DFS below records when it discovers vertex u in the attribute u.discover
    int finish;              // and when it finishes exploring vertex u in the attribute u.finish . These timestamps are integers
    int color;               // between 1 and 2|V|, since there is one discovery event and one finishing event for                             
    struct Node* parent;     // each of the |V| vertices.
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
    
    // if you need a vertex in directed graph that points to nowhere, or in undirected graph a totally separate vertex, then:
    // insertNodeAtEnd(&myGraph->adjl[i], i), where i should be the of the same value 

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
