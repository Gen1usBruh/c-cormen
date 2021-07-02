#include <stdio.h>
#include <stdlib.h>

// Hash table solves the problems of direct-address table
// With direct addressing, an element with key k is stored in slot k. With hashing,
// this element is stored in slot h(k); that is, we use a hash function h to compute the
// slot from the key k. Here, h maps the universe U of keys into the slots of a hash
// table T[0..m - 1], where the size m of the hash table is typically much less than U
// We say that an element with key k hashes to slot h(k); we also say that h(k) is the 
// hash value of key k.
// There is one hitch: two keys may hash to the same slot. We call this situation
// a collision.


// Collision resolution by chaining.
// In chaining, we place all the elements that hash to the same slot into the same
// linked list. Slot j contains a pointer to the head of the list of all stored 
// elements that hash to j; if there are no such elements, slot j contains NIL.
// The worst-case running time for insertion is O(1). The insertion procedure is fast
// in part because it assumes that the element x being inserted is not already present in
// the table; if necessary, we can check this assumption (at additional cost) by searching
// for an element whose key is x.key before we insert.
// For searching, the worst-case running time is proportional to the length of the list;
// We can delete an element in O(1) time if the lists are doubly linked

// Analysis of hashing with chaining.
// Given a hash table T with m slots that stores n elements, we define the load
// factor α (alpha) for T as n/m, that is, the average number of elements stored in a chain.
// The worst-case behavior of hashing with chaining is terrible: all n keys hash
// to the same slot, creating a list of length n.

// Assumption - Simple uniform hashing: 
//     Any given element is equally likely to hash into any of the m slots, independently
//     of where any other element has hashed to.

// We shall consider two cases. In the first, the search is unsuccessful: no element in the
// table has key k. In the second, the search successfully finds an element with key k.
// Plus, we set aside the time reqiured to compure hash function to O(1).

// Theorem: 
// In a hash table in which collisions are resolved by chaining, an Unsuccessful search
// takes average-case time θ(1 + α), under the assumption of simple uniform hashing.

// Theorem:
// In a hash table in which collisions are resolved by chaining, a Successful search
// takes average-case time θ(1 + α), under the assumption of simple uniform hashing.


// Collision resolution by open addressing.
// In open addressing, all elements occupy the hash table itself. That is, each table
// entry contains either an element of the dynamic set or NIL.
// No lists and no elements are stored outside the table, unlike in chaining; 
// one consequence is that the load factor α can never exceed 1.
// To perform insertion using open addressing, we successively examine, or probe,
// the hash table until we find an empty slot in which to put the key. Instead of being
// fixed in the order 0, 1,...,m - 1 (which requires θ(n) search time), the sequence
// of positions probed depends upon the key being inserted. To determine which slots
// to probe, we extend the hash function to include the probe number (starting from 0)
// as a second input.

// Assumption - Simple uniform hashing: 
    // The probe sequence of each key is equally 
    // likely to be any of the m! permutations of {0, 1,...,m - 1}.

// Analysis of open-address hashing.
    // As in our analysis of chaining, we express our analysis of open addressing in terms
    // of the load factor α = n/m of the hash table. Of course, with open addressing, at
    // most one element occupies each slot, and thus n <= m, which implies α <= 1.
    // We assume that we are using uniform hashing. In this idealized scheme, the probe
    // sequence used to insert or search for each key k is equally likely to be any permutation.

// Theorem:
    // Given an open-address hash table with load factor α = n/m < 1, the expected number
    // of probes in an unsuccessful search is at most 1/(1 - α), assuming uniform hashing.

// Corollary:
    // Inserting an element into an open-address hash table with load factor α requires at
    // most 1/(1 - α) probes on average, assuming uniform hashing.

// Theorem:
    // Given an open-address hash table with load factor α < 1, the expected number of
    // probes in a successful search is at most 
    // (1/α)ln(1/(1 - α))
    // assuming uniform hashing and assuming that each key in the table is equally likely
    // to be searched for.


// Linear probing:
    // Given an ordinary hash function h' : U -> {0, 1,...,m - 1}, which we refer to as
    // an auxiliary hash function, the method of linear probing uses the hash function - 
    // h(k, i) = (h'(k) + i) mod m  (for i = 0, 1,...,m - 1)
// Drawback:
    // It suffers from a problem known as primary clustering. Long runs of occupied slots
    // build up, increasing the average search time. Clusters arise because an empty slot
    // preceded by i full slots gets filled next with probability (i + 1)/m. 
    // Long runs of occupied slots tend to get longer, and the average search time increases.

// Quadratic probing:
    // Uses a hash function of the form:
    // h(k, i) = (h'(k) + ci + d(i^2)) mod m  (where c and d are positive auxiliary constants)
    // The initial position probed is T[h'(k)]; later positions probed are 
    // offset by amounts that depend in a quadratic manner on the probe number i.
    // This method works much better than linear probing, but to make full use of
    // the hash table, the values of c, d, and m are constrained.
// Drawback:
    // This property leads to a milder form of clustering, called
    // secondary clustering. As in linear probing, the initial probe determines the entire
    // sequence, and so only m distinct probe sequences are used.

// Double hashing:
    // Double hashing offers one of the best methods available for open addressing because
    // the permutations produced have many of the characteristics of randomly
    // chosen permutations. Double hashing uses a hash function of the form:
    // h(k, i) = (h1(k) + ih2(k)) mod m  (where both h1 and h2 are auxiliary hash functions)
    // The initial probe goes to position T[h1(k)]; successive probe positions are offset 
    // from previous positions by the amount h2(k), modulo m.
    // The value h2(k) must be relatively prime to the hash-table size m for the entire
    // hash table to be searched. A convenient way to ensure this
    // condition is to let m be a power of 2 and to design h2 so that it always produces an
    // odd number. Another way is to let m be prime and to design h2 so that it always
    // returns a positive integer less than m.


