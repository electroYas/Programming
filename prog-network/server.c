#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include "colour.h"

int listenfd = 0,connfd = 0;
struct sockaddr_in serv_addr;
  
char sendBuff[1025];  
int connect_network();
int port = 5000;
int main(void)
{
	 
  int status;
  
  status = connect_network();
  
  if(status == -1){
    printf(RED "Connection Error!\n" RESET);
    return -1;
  }
  
  memset(sendBuff, '0', sizeof(sendBuff));  
  sprintf(sendBuff,"Hello from server\n\r");
  
  while(1){
    connfd = accept(listenfd, (struct sockaddr*)NULL ,NULL); // accept awaiting request
    write(connfd, sendBuff, strlen(sendBuff));
    close(connfd);    
  }
  
  return 0;
}
/*
 * create a socket and bind
 */
int connect_network(){
  int val;
  listenfd = socket(AF_INET, SOCK_STREAM, 0);//TCP
  
  if (listenfd == -1) return -1;
  
  memset(&serv_addr, '0', sizeof(serv_addr));//clear struct

  serv_addr.sin_family = AF_INET;    
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); 
  serv_addr.sin_port = htons(port);    //port number
 
  val = bind(listenfd, (struct sockaddr*)&serv_addr,sizeof(serv_addr));
  
  if(val == -1) return -1;
  
  listen(listenfd, 1);//queue upto 10 pending connections
  
  return 0;
  
}
