#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>   
#include<unistd.h>  
#include<netinet/in.h>

int main() 
{
    char msg[256] = "This is server talking to you";
    int s_socket = socket(AF_INET,SOCK_STREAM,0);
    if(s_socket<0){
        printf("Socket creation failed!\n");
 } 
else {
        printf("Socket created successfully\n");
    }

    struct sockaddr_in s_address;
    s_address.sin_family = AF_INET;
    s_address.sin_port = htons(8888);
    s_address.sin_addr.s_addr = INADDR_ANY;
 
   int status = bind(s_socket,(struct sockaddr *)&s_address,sizeof(s_address));
    if(status < 0){
        printf("Binging not successful\n");
    } 
else {
        printf("Successful Binding\n");
    }

    
    int listen_status;
    listen_status = listen(s_socket,5);
    if(listen_status <0){
        printf("Listening problems\n");
    } 
else {
        printf("Waiting...\n");
    }

    int client_socket, size = sizeof(struct sockaddr_in);
    struct sockaddr_in client_address;
    client_socket = accept(s_socket,(struct sockaddr *)&client_socket,&size);
    if(client_socket < 0){
        printf("Accept failed\n");
    } 
else {
        printf("Client accepted\n");
    }
    int G[20][20];
    int V;
    int E;
    int edge[20][2];
    int i,u,v,k,distance[20],parent[20],S,flag=1;
   
    printf("\nReceving data from client..\n");
    if(recv(client_socket, &V ,sizeof(V),0) < 0){
        printf("Couldn't recieve packet");
        exit(0);
    } 
    if(recv(client_socket, &E ,sizeof(E),0) < 0){
        printf("Couldn't recieve packet");
        exit(0);
    } 
    if(recv(client_socket, &G ,sizeof(G),0) < 0){
        printf("Couldn't recieve packet");
        exit(0);
    }
    if(recv(client_socket, &edge ,sizeof(edge),0) < 0){
        printf("Couldn't recieve packet");
        exit(0);
    }
    if(recv(client_socket, &S ,sizeof(S),0) < 0){
        printf("Couldn't recieve packet");
        exit(0);
    }
    printf("data recieved from client.\n");

    printf("\nPerforming Bellman Ford Algorithm...\n");
    for(i=0;i<V;i++)
        distance[i] = 1000 , parent[i] = -1 ;

    distance[S-1]=0 ;
    for(i=0;i<V-1;i++)
    {
        for(k=0;k<E;k++)
        {
            u = edge[k][0] , v = edge[k][1] ;
            if(distance[u]+G[u][v] < distance[v])
                distance[v] = distance[u] + G[u][v] , parent[v]=u ;
        }
    }
    for(k=0;k<E;k++)
    {
        u = edge[k][0] , v = edge[k][1] ;
        if(distance[u]+G[u][v] < distance[v])
            flag = 0 ;
    }
    printf("Algorithm Applied Successfully.\n");

    printf("\nSending back to the client...\n");
    if(send(client_socket, &flag ,sizeof(flag),0) < 0){
        printf("Couldn't send flag");
        exit(0);
    }
    if(send(client_socket, &distance ,sizeof(distance),0) < 0){
        printf("Couldn't send distance");
        exit(0);
    }
    if(send(client_socket, &parent ,sizeof(parent),0) < 0){
        printf("Couldn't send parent");
        exit(0);
    }
    printf("All data sent to the client.\n");
    close(s_socket);
    return 0;
}
