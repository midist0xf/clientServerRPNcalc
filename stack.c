#include "stack.h"
#include "stdio.h"
#include "stdlib.h"
#include "rpn.h" /* flag, mode */


int mode = 0;

/* POSTCONDITION: initialize empty stack  */
void init(Stack *s)
{
   s->top = -1;
}

/* POSTCONDITION: return the element at the top of the stack */
int pop(Stack *s)
{
   if(empty(s))
   {
      printf("Stack is empty \n");
      exit(1);
   }
   return(s->data[s->top--]);
}

/* POSTCONDITION: push el on the top of the stack */
/* mode 0: just push el on the top of the stack (used for itop) */
/* mode 1: if flag = 0 just push el on the top of the stack
 *         if flag = 1 pop the element on the top of the stack 
 *         multiplies it times 10 and add el to the result, 
 *         which is pushed back to the stack (used to parse 
 *         multi digits number in eval) */
void push(Stack *s, int el)
{
  if(full(s)) 
  {
    printf("Stack overflow \n");
    exit(1);
  }
  /* just push the token into the stack */
  if(mode == 0)
  {
    s->top++;
    s->data[s->top] = el;
  } else if (mode == 1)
  {
     if(flag == 1)
     {  
        int  num = pop(s);
        s->top++;
        s->data[s->top] = el+10*num;
     }else
     {
        s->top++;
        s->data[s->top] = el;
        flag = 1;
     }
  }
}

/* POSTCONDITION: return a value !=0 if the stack is empty,
a 0 otherwise */
int empty(Stack *s)
{
   return(s->top == -1);
}

/* POSTCONDITION: return a value !=0 if the stack is full,
0 otherwise */
int full(Stack *s)
{
   return(s->top == MAX-1);
}

/* POSTCONDITION: return the element on the top of the stack */
int top(Stack *s)
{
   return(s->data[s->top]);
}
