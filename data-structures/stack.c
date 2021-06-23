#include <stdio.h>
#include <stdlib.h>

// Stack is a dynamic set, which implemenets LIFO policy (last-in, first-out)
// The INSERT operation on a stack is often called PUSH, and the DELETE operation,
// which does not take an element argument, is often called POP. These names
// are allusions to physical stacks, such as the spring-loaded stacks of plates used
// in cafeterias. The order in which plates are popped from the stack is the reverse
// of the order in which they were pushed onto the stack, since only the top plate is
// accessible. 
// In every implementation of stack there is an attribute TOP, that indexes (or points to)
// the most recently inserted (pushed) element.
 
// Here we have 2 implementations: via a linked list and via an array.

typedef struct Node{
    int data;
    struct Node *link;
} node;

void push(node **top, int value){
    node *newNode = malloc(sizeof(node));
    if(newNode != NULL){
        newNode->data = value;
        newNode->link = *top;
        *top = newNode;
    }
}
void pop(node **top){
    node *temp;
    if(*top != NULL){
        temp = *top;
        *top = (*top)->link;
        temp->link = NULL;
        free(temp);
    }
}
void display(node **top){
    if(*top != NULL){
        for(node *temp = *top; temp != NULL; temp = temp->link){
            printf("%d --> ", temp->data);
        }
        printf("NULL\n");
    }
}


#define MAXSIZE 5
typedef struct Stack{
    int stk[MAXSIZE];
    int top;
} stack;

void push_(stack *s){
    int num = 0;
    if(s->top == (MAXSIZE - 1)){
        printf("Stack is Full\n");
        return;
    }
    else{
        printf("Enter the number to be pushed: ");
        scanf("%d", &num);
        ++(s->top);
        s->stk[s->top] = num;
    }
}
int pop_(stack *s){
    int num = 0;
    if(s->top == -1){
        printf("Stack is Empty\n");
        return s->top;
    }
    else{
        num = s->stk[s->top];
        printf("Popped element = %d \n", num);
        --(s->top);
    }
    return num;
}
void display_(stack *s){
    if(s->top == -1){
        printf("Stack is Empty\n");
        return;
    }
    else{
        printf("The stack is:\n");
        for(int i = s->top; i >= 0; i--){
            printf("%d --> ", s->stk[i]);
        }
        printf("NULL\n");
    }
}


int main(int argc, char* argv[]){
    
//     node *top = NULL;
//     push(&top, 1);
//     push(&top, 2);
//     push(&top, 3);
//     push(&top, 4);
//     display(&top);
//     pop(&top);
//     pop(&top);
//     display(&top);

  
//     stack myStack;
//     myStack.top = -1;
//     push_(&myStack);
//     push_(&myStack);
//     push_(&myStack);
//     push_(&myStack);
//     display_(&myStack);
//     pop_(&myStack);
//     pop_(&myStack);
//     display_(&myStack);
    
}
