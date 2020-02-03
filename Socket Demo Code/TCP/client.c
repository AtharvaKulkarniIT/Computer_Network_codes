#include<stdio.h>   
#include<string.h>  
#include<sys/socket.h>  
#include<arpa/inet.h>

char crcg(char data[]) {
    int i,j,keylen,msglen;
    char key[30],temp[30],quot[100],rem[30],key1[30];

    printf("Enter Key: ");
    scanf(key);//stores divisor

    keylen=strlen(key);
    msglen=strlen(data);

    strcpy(key1,key);
    for (i=0;i<keylen-1;i++)
    {
        data[msglen+i]='0';//inserting 0s after the data entered
    }
    for (i=0;i<keylen;i++)
     temp[i]=data[i];//no of bits equivalent to divisor brought from input data to temp arr
    
    for (i=0;i<msglen;i++)
     {
        quot[i]=temp[0];
        if(quot[i]=='0')
         for (j=0;j<keylen;j++)
         key[j]='0';
        else
         for (j=0;j<keylen;j++)
         key[j]=key1[j];

        for (j=keylen-1;j>0;j--) 
        {//performing XOR
            if(temp[j]==key[j])
             rem[j-1]='0';
            else
             rem[j-1]='1';
        }
        rem[keylen-1]=data[i+keylen];
        strcpy(temp,rem);
    }

    strcpy(rem,temp);
    printf("\nQuotient is ");
    for (i=0;i<msglen;i++)
     printf("%c",quot[i]);
    printf("\nRemainder is ");
    for (i=0;i<keylen-1;i++)
     printf("%c",rem[i]);
    printf("\nFinal data is: ");
    for (i=0;i<msglen;i++)
     printf("%c",data[i]);

    return data;
}   

int main(int argc , char *argv[])
{
    int sock;
    struct sockaddr_in server;
    char server_reply[2000];

    //Create socket
    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");

    server.sin_addr.s_addr = inet_addr("192.168.43.193");
    server.sin_family = AF_INET;
    server.sin_port = htons( 8888 );

    //Connect to remote server
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("connect failed. Error");
        return 1;
    }

    puts("Connected\n");

    //keep communicating with server
    while(1)
    {
        int i,j,keylen,msglen;
        char input[1000], key[30],temp[30],quot[100],rem[30],key1[30];

        printf("Enter Data: ");
        gets(input);//stores data in input
        printf("Enter Key: ");
        gets(key);//stores divisor

        keylen=strlen(key);
        msglen=strlen(input);

        strcpy(key1,key);
        for (i=0;i<keylen-1;i++) {
            input[msglen+i]='0';//inserting 0s after the data entered
        }
        for (i=0;i<keylen;i++)
            temp[i]=input[i];//no of bits equivalent to divisor brought from input data to temp arr
    
        for (i=0;i<msglen;i++) {
            quot[i]=temp[0];
            if(quot[i]=='0')
                for (j=0;j<keylen;j++)
                    key[j]='0';
            else
                for (j=0;j<keylen;j++)
                    key[j]=key1[j];

            for (j=keylen-1;j>0;j--) {//performing XOR
                if(temp[j]==key[j])
                    rem[j-1]='0';
                else
                    rem[j-1]='1';
            }
            rem[keylen-1]=input[i+keylen];
            strcpy(temp,rem);
        }

        strcpy(rem,temp);
        printf("\nQuotient is ");
        for (i=0;i<msglen;i++)
            printf("%c",quot[i]);
        printf("\nRemainder is ");
        for (i=0;i<keylen-1;i++)
            printf("%c",rem[i]);
        printf("\nFinal data is: ");
        for (i=0;i<msglen;i++)
            printf("%c",input[i]);
        for (i=0;i<keylen-1;i++)
            printf("%c",rem[i]);

        //Send some data
        if( send(sock , input , strlen(input) , 0) < 0)
        {
            puts("Send failed");
            return 1;
        }

        //Receive a reply from the server
        if( recv(sock , server_reply , 2000 , 0) < 0)
        {
            puts("recv failed");
            break;
        }

        puts("Server reply :");
        puts(server_reply);
    }

    close(sock);
    return 0;
}