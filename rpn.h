#ifndef RPNH 
#define RPNH 

/* flag used to parse multiple digits numbers */
extern int flag;
/* to use push both for itop and eval */
extern int mode;
/* convert infix notation to postfix notation */
void itop(char *src, char *dst, int srclen);
/* return priority of el token */
int prio(char el);

#endif
