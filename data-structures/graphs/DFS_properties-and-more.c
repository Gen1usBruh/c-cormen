#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


// Properties of depth-first search:
//    u = v.parent if and only if DFS-VISIT(G, v) was called during a search of u’s adjacency
//    list. Additionally, vertex v is a descendant of vertex u in the depth-first
//    forest if and only if v is discovered during the time in which u is gray.
//    Another important property of depth-first search is that discovery and finishing
//    times have parenthesis structure. If we represent the discovery of vertex u with
//    a left parenthesis "(u" and represent its finishing by a right parenthesis "u)", then
//    the history of discoveries and finishings makes a well-formed expression in the
//    sense that the parentheses are properly nested (because of the recursion, verily).
//   
// Theorem:
//   In any depth-first search of a (directed or undirected) graph G = (V,E), for any
//   two vertices u and v, (where .d = .discover and .f = .finish)
//   exactly one of the following three conditions holds:
//   - the intervals [u.d, u.f] and [v.d, v.f] are entirely disjoint, and neither u nor v
//     is a descendant of the other in the depth-first forest,
//   - the interval [u.d, u.f] is contained entirely within the interval [v.d, v.f], and u
//     is a descendant of v in a depth-first tree, or
//   - the interval [v.d, v.f] is contained entirely within the interval [u.d, u.f], and v
//     is a descendant of u in a depth-first tree.
//
// Corollary:
//   Vertex v is a proper descendant of vertex u in the depth-first forest for a (directed
//   or undirected) graph G if and only if u.d < v.d < v.f < u.f
//
// Theorem (White-path theorem):
//   In a depth-first forest of a (directed or undirected) graph G = (V,E), vertex v is
//   a descendant of vertex u if and only if at the time u:d that the search discovers u,
//   there is a path from u to v consisting entirely of white vertices.




 












