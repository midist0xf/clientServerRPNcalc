#include <stdio.h>
#include <sys/socket.h> /* socket, bind, listen, accept, connect */
#include <netinet/in.h> /* sockaddr_in */
#include <stdlib.h> /* exit */
#include <string.h> /* memset */
int main(int argc, char **argv)
{
   int sockfd;
   struct sockaddr_in servaddr;

   /* check the arguments */
   if(argc != 2)
   {
      printf("usage: a.out <IPaddress> \n");
      exit(EXIT_FAILURE);
   }

   printf("I am client...\n");
   
   /* socket */
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   if(sockfd < 0)
   {
      perror("socket error");
      exit(EXIT_FAILURE);
   }
  
   /* initialize sockaddr_in struct */
   memset(&servaddr, 0, sizeof(servaddr));
   servaddr.sin_family = AF_INET;
   servaddr.sin_port = htons(60000);
   /* convert argv[1] address in AF_INET format and saves it in sin-addr */
   if(inet_pton(AF_INET, argv[1], &servaddr.sin_addr.s_addr) <= 0)
   {
      perror("inet_pton");
      exit(EXIT_FAILURE);
   }

    /* connect */
    /* connect sockfd to servaddr */
    if((connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr))) < 0)
    {
       perror("connect");
       exit(EXIT_FAILURE);
    }
    printf("Connected with server...\n");

   char buf[50], buf1[50];
   /* keep communicating with server */
   while(1)
   {
      printf("Enter the expression...\n");
      fgets(buf, 50, stdin);
       
      /* remove trailing newline */
      if ((strlen(buf) > 0) && (buf[strlen (buf) - 1] == '\n'))
         buf[strlen(buf) - 1] = '\0';

      printf("Sent expression: %s  \n", buf);

      /* send a message to the server */
      if(send(sockfd,buf,50,0) < 0)
      {
         perror("send error");
         exit(EXIT_FAILURE);
      }

      /* receive (blocking) a reply from the server */
      if(recv(sockfd, buf1, 50, 0) < 0)
      {
         perror("recv error");
         exit(EXIT_FAILURE);
      }
      printf("Received result: %s\n", buf1);
   }

    close(sockfd);

    return 0;
}
