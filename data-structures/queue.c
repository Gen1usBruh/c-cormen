#include <stdio.h>
#include <stdlib.h>

// Queue is a dynamic set, which implemenets FIFO policy (first-in, first-out)
// We call the INSERT operation on a queue ENQUEUE, and we call the DELETE
// operation DEQUEUE. The FIFO property of a queue causes it to operate like a line of customers
// waiting to pay a cashier. The queue has a head and a tail. When an element is enqueued,
// it takes its place at the tail of the queue, just as a newly arriving customer
// takes a place at the end of the line. The element dequeued is always the one at
// the head of the queue, like the customer at the head of the line who has waited the
// longest.
//
// Here we have 2 implementations: via a linked list and via an array.

