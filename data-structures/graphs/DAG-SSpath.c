#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <inttypes.h>

// By relaxing the edges of a weighted dag (directed acyclic graph) G = (V,E)
// according to a topological sort of its vertices, we can compute shortest paths from
// a single source in θ(V + E) time. Shortest paths are always well defined in a dag,
// since even if there are negative-weight edges, no negative-weight cycles can exist.
//
// Theorem:
// If a weighted, directed graph G = (V,E) has source vertex s and no cycles, then
// at the termination of the DAG-SHORTEST-PATHS procedure, v.d = 𝛿(s,v) for all
// vertices v ∈ V , and the predecessor subgraph G' is a shortest-paths tree (consisits of v.parent's).


#define CAPACITY 10

typedef struct Node {
    int data;
    int discover;
    int finish;
    int color;
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

// topological sort is called inside DFS and takes θ(V + E) time
void topologicalSort(node* vertex) {
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
    topologicalSort(u);  // here it is
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

void display(topNode** head) {
    topNode* current = *head;
    if (current == NULL) {
        printf("List is empty.\n\n");
    }
    else {
        printf("The list is:\n");
        for (int i = 0; current != NULL; current = current->next, i++) {
            printf("%d |%d --> ", current->data->data, i);   // display the vertex and i is the index [0, n)
        }
        printf("NULL\n\n");
    }
}

void deltaPathDAG(graph* graph, int source) {
    DFS(graph);
    initSingleSource(graph, source);
    for (topNode* curr = myList; curr != NULL; curr = curr->next) {
        for (node* temp = curr->data->next; temp != NULL; temp = temp->next) {
            relax(graph, curr->data, temp);
        }
    }
}


int main(int argc, char* argv[]) {
    graph* myGraph = newGraph();

    insert(myGraph, 1, 2, 5);   
    insert(myGraph, 1, 3, 3);
    insert(myGraph, 2, 3, 2);
    insert(myGraph, 2, 4, 6);   // --> Directed acyclic graph test
    insert(myGraph, 3, 4, 7);
    insert(myGraph, 3, 5, 4);
    insert(myGraph, 3, 6, 2);
    insert(myGraph, 4, 5, -1);
    insert(myGraph, 4, 6, 1);
    insert(myGraph, 5, 6, -2);

    // if you need a vertex in directed graph that points to nowhere, or in undirected graph a totally separate vertex, then:
    // insertNodeAtEnd(&myGraph->adjl[i], i), where i should be the of the same value 

    deltaPathDAG(myGraph, 2);

    display(&myList);

    dumpGraph(myGraph);

}
