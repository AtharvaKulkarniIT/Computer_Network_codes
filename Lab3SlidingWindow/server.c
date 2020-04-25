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
	int sockfd,bytes_received,newsockfd,true=1,i=1,s,f=0,sin_size;
	char send_data[1024],data[1024],c,fr[30]=" ";
	struct sockaddr_in server_addr,client_addr;
	if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1)
	{
		perror("Socket not created!");
		exit(1);
	}
	if(setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&true,sizeof(int))==-1)
	{
		perror("Setsockopt");
		exit(1);
	}
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(17000);
	server_addr.sin_addr.s_addr=INADDR_ANY;
	if(bind(sockfd,(struct sockaddr *)&server_addr,sizeof(struct sockaddr))==-1)
	{
		perror("Unable to bind!");
		exit(1);
	}
	if(listen(sockfd,5)==-1)
	{
		perror("Listen Failed!");
		exit(1);
	}
	fflush(stdout);
	sin_size=sizeof(struct sockaddr_in);
	newsockfd=accept(sockfd,(struct sockaddr *)&client_addr,&sin_size);
	while(strcmp(fr,"exit")!=0)
	{
		printf("Enter Data Frame %d:(Enter exit for End): ",i);
		scanf("%s",fr);
		send(newsockfd,fr,strlen(fr),0);
		recv(sockfd,data,1024,0);
		if(strlen(fr)<10)
			printf("Acknowledgement Received.\n ");
		else{
			sleep(3);
			printf("Acknowledgement NOT Received. Frame Size too large!\n");
		}
		fflush(stdout);
		i++;
	}
	close(sockfd);
	return (0);
}


