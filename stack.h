#ifndef STACKH 
#define STACKH 

#define MAX 20

/* stack data structure */
struct Stack
{
  int data[MAX];
  int top;
};
typedef struct Stack Stack;

/* stack operations */
void init(Stack *s);
int pop(Stack *s);
void push(Stack *s, int el);
int empty(Stack *s);
int full(Stack *s);
int top(Stack *s);

#endif
