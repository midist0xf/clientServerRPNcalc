#include "stack.h" 
#include "rpn.h" 
#include "ctype.h" /* isdigit*/
#include "stdio.h"


int flag = 0;

/* POSTCONDITION: return the priority of el */
int prio(char el)
{
   switch(el)
   {
      case '(': return 0;
      case '+':
      case '-': 
                return 1;
      case '*':
      case '/':
      case '%':
                return 2;
      default:  return 0;
   }
}

/* PRECONDITION: src is an infix expression (e.g. (10 + 3) - 4 ) */
/* POSTCONDITION: converts src infix expression to postfix expression and
save the result in dst */
void itop(char *src, char *dst, int srclen)
{
   Stack s;
   init(&s);

   int c;
   int token;
   int i; 
   int j=0; 

   for(i=0; i < srclen && src[i] != '\0'; i++)
   {
     token = src[i];
     /* token is an operand */
     if(isdigit(token))
     {
        dst[j++] = token; 
     }else if (token == ' ')
     {
        dst[j++] = ' ';
     }
     else if(token == '(')
     {
        push(&s,'(');
     }
     else if(token == ')')
     {
        while((c=pop(&s))!='(')
        dst[j++] = c; 
     }
     else
     /* token is an operator: *,/,+,-  */
     {
       while(prio(token) <= prio(top(&s)) && !empty(&s))
       {
          c=pop(&s);
          dst[j++] = c; 
       }
       push(&s,token);
     }
   }
   /* pop all operators on the stack */
   while(!empty(&s))
   {
     c = pop(&s);
     dst[j++] = c; 
   }
   dst[j]='\0';
 }

int eval(char *src, int len){

   Stack s;
   init(&s);
   
   int token;
   int op1, op2;
   int i, res;
  
   flag = 0;
   for (i=0 ; i<len && src[i] != '\0'; i++)
   {
     token = src[i];
     /* token is an operand */
     if (isdigit(token))
     {
      push(&s, token - '0'); 
     } else if (token == ' ')
     {
        flag = 0;
     }else
     {
     /* token is an operator  */
       flag = 0;
       op2 = pop(&s);
       op1 = pop(&s);      
       res = calc(op1, op2, token);
       push(&s, res);
     }
   }
   return pop(&s);
}

/* POSTCONDITION: return the computation of op1 and op2 using token as operator */
int calc(int op1, int op2, int token){
   switch (token){
     case '+':  
       return (op1 + op2);
       break;
     case '-':
       return (op1 - op2);
       break;
     case '*':
       return (op1 * op2);
       break;
     case '/':
       return (op1 / op2);
     case '%':
       return (op1 % op2);
       break;
   }
}

