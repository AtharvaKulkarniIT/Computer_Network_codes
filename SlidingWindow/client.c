#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<netdb.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>

int main()
{
	int sockfd,bytes_received,i=1;
	char receive[30];
	struct hostent *host;
	struct sockaddr_in server_addr;
	host=gethostbyname("127.0.0.1");
	if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1)
	{
		perror("Socket not created!");
		exit(1);
	}
	printf("Socket created");
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(17000);
	server_addr.sin_addr=*((struct in_addr *)host->h_addr);
	bzero(&(server_addr.sin_zero),8);
	if(connect(sockfd,(struct sockaddr *)&server_addr,sizeof(struct sockaddr))==-1)
	{
		perror("Connection Error!");
		exit(1);
	}
	while(1)
	{
		bytes_received=recv(sockfd,receive,20,0);
		receive[bytes_received]='\0';
		if(strcmp(receive,"exit")==0||strcmp(receive,"Exit")==0)
		{
			close(sockfd);
			break;
		}
		else
		{
			if(strlen(receive)<10)
			{
				printf("\n Frame %d data %s received\n",i,receive);
				send(0,receive,strlen(receive),0);
			}
			else
			{
				send(0,"Negative\n Frame not received!",10,0);
			}
			i++;
		}
	}
	close(sockfd);
	return(0);
}