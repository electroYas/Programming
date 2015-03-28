#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

#include "colour.h"
 
int main(void)
{
	
	int port=5000;
	int sockfd = 0;
	char recvBuff[1024];
	struct sockaddr_in serv_addr;
 
	memset(recvBuff, '0' ,sizeof(recvBuff));
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	if(sockfd < 0)
    {
		printf("\n Error : Could not create socket \n");
		return 1;
    }
    
	memset(&serv_addr,'0',sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
 
	if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0)
    {
      printf(RED " Error : Connect Failed \n" RESET);
      return 1;
    }
 
	int n;
	while((n = read(sockfd, recvBuff, sizeof(recvBuff)-1)) > 0)
    {
		recvBuff[n] = 0;
		printf("%s\n",recvBuff);		
    } 
	return 0;
}
