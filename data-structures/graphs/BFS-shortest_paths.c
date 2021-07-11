#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Definition:
//     The shortest-path distance δ(s,v) from s to v as the minimum number
//     of edges in any path from vertex s to vertex v; if there is no path from s to v,
//     then δ(s,v) = ♾.
//
// Lemma 1:
//     Let G = (V,E) be a directed or undirected graph, and let s ∈ V be an arbitrary
//     vertex. Then, for any edge (u,v) ∈ E, 
//     δ(s,v) <= δ(s,u) + 1.
//
// Lemma 2:
//     Let G = (V,E) be a directed or undirected graph, and suppose that BFS is run
//     on G from a given source vertex s ∈ V . Then upon termination, for each vertex
//     v ∈ V , the value v.d (or v.distance) computed by BFS satisfies v.d >= δ(s,v).
//
// Lemma 3:
//     Suppose that during the execution of BFS on a graph G = (V,E), the queue Q
//     contains the vertices (v1, v2,...,vr), where v1 is the head of Q and vr is the tail.
//     Then, vr.d <= v1.d + 1 and vi.d <= v(i+1).d for i = 1,2,...,r - 1.
//
// Corollary:
//     Suppose that vertices vi and vj are enqueued during the execution of BFS, and
//     that vi is enqueued before vj. Then vi.d <= vj.d at the time that vj is enqueued.
//
// Theorem:
//     Let G = (V,E) be a directed or undirected graph, and suppose that BFS is run
//     on G from a given source vertex s ∈ V . Then, during its execution, BFS discovers
//     every vertex v ∈ V that is reachable from the source s, and upon termination,
//     v.d = δ(s,v) for all v ∈ V . Moreover, for any vertex v != s that is reachable
//     from s, one of the shortest paths from s to v is a shortest path from s to v.p
//     (or v.parent) followed by the edge (v.p, v).
