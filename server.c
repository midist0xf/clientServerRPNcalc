#include <stdio.h>
#include <stdlib.h> /* exit */
#include <string.h> /* memset */
#include <errno.h> /* errno, perror */
#include <sys/socket.h> /* socket */
#include <sys/types.h> /* pid_t */
#include <netinet/in.h> /* sockaddr_in */

#include "stack.h"
#include "rpn.h"

int main(int argc, char **argv)
{
   int listenfd, connfd, len, n;
   char buf[50];
   struct sockaddr_in servaddr, cliaddr;
   pid_t pid;

   /* socket */
   /* creates IPv4, connection-oriented endpoint */
   listenfd = socket(AF_INET, SOCK_STREAM, 0);
   if(listenfd < 0)
   {
      perror("socket error");
      exit(EXIT_FAILURE);
   }
   printf("Socket created successfully... \n");

   /* initialize socket address structure */
   /* set all servaddr's fields to zero */
   memset(&servaddr, 0, sizeof(servaddr));
   /* set address family (IPv4) to communicate with */
   servaddr.sin_family = AF_INET;
   /* set IPv4 address */
   servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
   /* set port */
   servaddr.sin_port = htons(60000);

   /* bind */
   /* assigning an address (servaddr) to the socket referred to by listenfd */
   if((bind(listenfd , (struct sockaddr*)&servaddr, sizeof(servaddr))) < 0 )
   {
      perror("bind error");
      exit(EXIT_FAILURE);
   }
   printf("Binding done...\n");


   /* listen */
   /* marks the socket as a passive socket (will accept incoming connection request using accept) */
   if(listen(listenfd, 3) < 0 )
   {
      perror("listen error");
      exit(EXIT_FAILURE);
   } 
   printf("Listening for client...\n");

   for( ; ; )
   {
      /* accept */
      /* extract the first connection request on the queue of pending conn. for
       * listenfd and return a new created socket (not listening) */
     len = sizeof(cliaddr);
     if((connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &len)) < 0 )
     {
        perror("accept error");
        exit(EXIT_FAILURE);
     }
     printf("Connected to client...\n");
     
     /* creating child process */ 
     pid = fork();
     /* parent process closes connf and leave the usability to the child */
     if(pid != 0) close(connfd);
     else
     {
        /* child process */
        printf("Child process created...\n");
        /* close parent listening socket */
        close(listenfd);
         
        /* execute client request */ 
        /* receive a message from client */
        while((n = recv(connfd, buf, 50, 0) > 0)) 
        {
           char dst[128];
           char res[128];
           /* convert from infix to postfix notation */
           mode = 0;
           itop(buf, dst, 128);
           printf("Infix expression received from client: %s...\n", buf);
           printf("Postfix expression after conversion: %s...\n", dst);
           /* evaluate postfix expression */
           mode = 1;
           int a = eval(dst, 128); 
           printf("Result: %d \n", a);
           sprintf(res, "%d", a);
           /* send the result back to the client */
           send(connfd, res, 50, 0);
        }

        if(n == -1)
        {
           printf("Client disconnected");
        }
        else if(n == 0)
        {
           perror("recv error");
           exit(EXIT_FAILURE);
        }
         
        /* close connection with this client */
        close(connfd);
        
        /* terminate */ 
        return 0; 
     }      

   }
}
