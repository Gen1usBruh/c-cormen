#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// In a shortest-paths problem, we are given a weighted, directed graph
// G = (V,E), with weight function w : E -> R mapping edges to real-valued
// weights. The weight w(p) of path p is the sum of the weights of its constituent edges.
//
// We define the shortest-path weight 𝛿(u,v) (delta) from u to v by 
//     min{w(p) for path from u to v}, if there is a path from u to v,
//     ♾ - infinity, otherwise.
//
//A shortest path from vertex u to vertex v is then defined as any path p with weight
// w(p) = 𝛿(u,v).


// Single-source shortest-paths problem: 
//     given a graph G = (V,E), we want to find a shortest path from a given source vertex
//     s ∈ V to each vertex v ∈ V . The algorithm for the single-source problem can
//     solve many other problems, including the following variants.

// Single-destination shortest-paths problem: 
//     Find a shortest path to a given destination
//     vertex t from each vertex v. By reversing the direction of each edge in
//     the graph, we can reduce this problem to a single-source problem.

// Single-pair shortest-path problem: 
//     Find a shortest path from u to v for given
//     vertices u and v. If we solve the single-source problem with source vertex u,
//     we solve this problem also. Moreover, all known algorithms for this problem
//     have the same worst-case asymptotic running time as the best single-source
//     algorithms.
// All-pairs shortest-paths problem: 
//     Find a shortest path from u to v for every pair
//     of vertices u and v. Although we can solve this problem by running a singlesource
//     algorithm once from each vertex, we usually can solve it faster.


// Properties of shortest paths and relaxation:
//     Triangle inequality:
//         For any edge (u,v) ∈ E, we have 𝛿(s,v) <= 𝛿(s,u) + w(u,v).
//     Upper-bound property:
//         We always have v.d >= 𝛿(s,v) for all vertices v ∈ V , and once v.d achieves the
//         value 𝛿(s,v), it never changes.
//     No-path property:
//         If there is no path from s to v, then we always have v.d = 𝛿(s,v) = ♾ (infinity).
//     Convergence property:
//         If s for u -> v is a shortest path in G for some (u,v) ∈ V, and if u.d = 𝛿(s,u) = ♾ at
//         any time prior to relaxing edge (u,v), then v.d = 𝛿(s,v) at all times afterward.
//     Path-relaxation property:
//         If p = (v0, v1,...,v|k|) is a shortest path from s = v0 to v|k|, and we relax the
//         edges of p in the order (v0,v1), (v1,v2),...,(v|k-1|, v|k|), then v|k|.d = 𝛿(s,v|k|).
//         This property holds regardless of any other relaxation steps that occur, even if
//         they are intermixed with relaxations of the edges of p.
//     Predecessor-subgraph property:
//         Once v.d = 𝛿(s,v) for all v ∈ V, the predecessor subgraph is a shortest-paths
//         tree rooted at s.
