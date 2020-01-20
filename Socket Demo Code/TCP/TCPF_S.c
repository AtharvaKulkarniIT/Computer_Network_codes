//Server
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
void main()
{
	//Decleration
	int listenfd,connfd,size=0;
	struct sockaddr_in servaddr,clientaddr;
	char sendBuff[1025];
    int numrv;
	//char sbuff[150]="Helo Client: A msg from Server!";
	
	//Socket
	listenfd = socket(AF_INET,SOCK_STREAM,0);
	if(listenfd == -1)
	{
		perror("\nSocket is not created\n");
	}
	else
	{
		printf("\nSocket is created\n");
	}
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("172.20.10.5");
	servaddr.sin_port = htons(7616);
	//bind
	if(bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr)) == -1)
	{
		perror("Bind Unsccessful\n");
	}
	else
	{
		printf("Bind Successful\n");
	}
	//listen
	listen(listenfd,9);
	//accept
	size = sizeof(struct sockaddr_in);
	while(1)
	{
	connfd = accept(listenfd,(struct sockaddr *)&clientaddr, &size);
	FILE *fp = fopen("/home/swapnil/Desktop/CompNet/input.txt","rb");
        if(fp==NULL)
        {
            printf("File opern error");
           // return 1;   
        }
        while(1)
        {
            /* First read file in chunks of 256 bytes */
            unsigned char buff[256]={0};
            int nread = fread(buff,1,256,fp);
            printf("Bytes read %d \n", nread);        

            /* If read was success, send data. */
            if(nread > 0)
            {
                printf("Sending \n");
                write(connfd, buff, nread);
            }

            /*
             * There is something tricky going on with read .. 
             * Either there was error, or we reached end of file.
             */
            if (nread < 256)
            {
                if (feof(fp))
                    printf("End of file\n");
                if (ferror(fp))
                    printf("Error reading\n");
                break;
            }


        }

        close(connfd);
        sleep(1);   
     }
	
	//recv

	//close

	//close
	
	close(listenfd);
}
