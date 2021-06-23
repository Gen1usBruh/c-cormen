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


typedef struct queueNode {
    int key;
    struct queueNode* next;
} qNode;

typedef struct Queue {
    qNode *head, *tail;
} queue;

queue* createQueue(){
    queue *tempQ = malloc(sizeof(queue));
    tempQ->head = tempQ->tail = NULL;
    return tempQ;
}
void enQueue(queue *q, int k){
    qNode *temp = malloc(sizeof(qNode));
    temp->key = k;
    temp->next = NULL;

    if(q->tail == NULL){
        q->head = q->tail = temp;
        return;
    }

    q->tail->next = temp;
    q->tail = temp;
}
qNode* deQueue(queue *q){
    if(q->head == NULL){
        return NULL;
    }

    qNode *temp = q->head;
    q->head = q->head->next;

    if(q->head == NULL){
        q->tail = NULL;
    }
    return temp;
}
void display(queue *q){
    if(q->head == NULL && q->tail == NULL){
        printf("Queue is empty\n");
    }
    else{
        printf("Head: ");
        for(qNode *tmp = q->head; tmp != NULL; tmp = tmp->next){
            printf("%d", tmp->key);
            if(tmp->next != NULL){
                printf(" --> ");
            }
        }
        printf(" :Tail\n");
    }
}


#define MAXSIZE 10
typedef struct Queue_ {
    int qArr[MAXSIZE];
    int head, tail;
} queue_;

void enQueue_(queue_ *q, int key){
    if(q->tail == MAXSIZE - 1){
        printf("Queue overflow\n");
    }
    else{
        if(q->head == -1){
            q->head = 0;
        }
        ++(q->tail);
        q->qArr[q->tail] = key;
    }
}
void deQueue_(queue_ *q){
    if(q->head == -1 || q->head > q->tail){
        printf("Queue underflow\n");
        return;
    }
    else{
        printf("Element deleted from queue: %d\n", q->qArr[q->head]);
        ++(q->head);
    }
}
void display_(queue_ *q){
    if(q->head == -1){
        printf("Queue is empty\n");
    }
    else{
        printf("Head: ");
        for(int i = q->head; i <= q->tail; i++){
            printf("%d", q->qArr[i]);
            if((i + 1) != (q->tail + 1)){
                printf(" --> ");
            }    
        }
        printf(" :Tail\n");
    }
}


int main(int argc, char* argv[]){

//     queue *q = createQueue();
//     enQueue(q, 1);
//     enQueue(q, 2);
//     enQueue(q, 3);
//     enQueue(q, 4);
//     display(q);   
//     deQueue(q);   // we can still use the returned node
//     deQueue(q);
//     display(q);


//     queue_ q;
//     q.head = q.tail = -1;
//     enQueue_(&q, 1);
//     enQueue_(&q, 2);
//     enQueue_(&q, 3);
//     enQueue_(&q, 4);
//     display_(&q);
//     deQueue_(&q);
//     deQueue_(&q);
//     display_(&q);

}
