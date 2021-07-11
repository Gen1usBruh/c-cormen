#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// The adjacency-list representation of a graph G = (V,E) consists of an array
// Adj of |V| lists, one for each vertex in V. For each u ∈ V , the adjacency list
// Adj[u] contains all the vertices v such that there is an edge (u,v) ∈ E. That is,
// Adj[u] consists of all the vertices adjacent to u in G. (Alternatively, it may contain
// pointers to these vertices.)
//
// If G is a directed graph, the sum of the lengths of all the adjacency lists is |E|,
// since an edge of the form (u,v) is represented by having v appear in Adj[u]. If G is
// an undirected graph, the sum of the lengths of all the adjacency lists is 2|E|, since
// if (u,v) is an undirected edge, then u appears in v's adjacency list and vice versa.
// For both directed and undirected graphs, the adjacency-list representation has the
// desirable property that the amount of memory it requires is θ(V + E).
//
// A potential disadvantage of the adjacency-list representation is that it provides
// no quicker way to determine whether a given edge (u,v) is present in the graph
// than to search for v in the adjacency list Adj[u]. An adjacency-matrix representation
// of the graph remedies this disadvantage, but at the cost of using asymptotically
// more memory.
//
// For the adjacency-matrix representation of a graph G = (V,E), we assume
// that the vertices are numbered 1,2,...,|V| in some arbitrary manner. Then the
// adjacency-matrix representation of a graph G consists of a |V| x |V| matrix
// A = (aij) such that aij = 1, if (i, j) ∈ E, otherwise, aij = 0.
// The adjacency matrix of a graph requires θ(V^2) memory, independent of the 
// number of edges in the graph.
