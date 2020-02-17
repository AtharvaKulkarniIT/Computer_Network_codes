//Client											
#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h> /* Provides support for 3rd party protocol stack*/
void main(void)
{
	//declaration
	
	int clifd;
	int bytesReceived=0;
	struct sockaddr_in clientaddr;
	char recvBuff[256];
	
	//socket
	
	clifd=socket(AF_INET,SOCK_STREAM,0); //0 indicates optional. AF :- All families	
	if(clifd==-1)
		perror("\n Socket is not created.");
	else
		printf("\n Socket created successfully.");
	
	//sockaddr_in
	
	clientaddr.sin_family=AF_INET; //sin:- sockaddr_in
	clientaddr.sin_addr.s_addr=inet_addr("192.168.43.211");
	clientaddr.sin_port=htons(7616);
	
	// bind
	
	if(bind(clifd,(struct sockaddr *)&clientaddr,sizeof(clientaddr))==-1)
		perror("\n Bind unsuccessful");
	else
		printf("\n Bind successful.");
	
	//connect
	
	if(connect(clifd,(struct sockaddr *)&clientaddr,sizeof(clientaddr))==-1) //clientaddr must have the values of server.
		perror("\n Connection failed ");
	else
		printf("\n Connection established ");
		
	//receive
	
	FILE *fp;
    fp = fopen("output.txt", "ab"); 
    if(NULL == fp)
    {
        printf("Error opening file");
        
    }

    /* Receive data in chunks of 256 bytes */
    while((bytesReceived = read(clifd, recvBuff, 256)) > 0)
    {
        printf("Bytes received %d\n",bytesReceived);    
        // recvBuff[n] = 0;
        fwrite(recvBuff, 1,bytesReceived,fp);
        // printf("%s \n", recvBuff);
    }

    if(bytesReceived < 0)
    {
        printf("\n Read Error \n");
    }


	
	//send
	
	//close
	close(clifd);
}
