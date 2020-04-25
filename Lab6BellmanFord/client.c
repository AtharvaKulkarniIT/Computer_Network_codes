#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h> 
#include<netinet/in.h>

int main() { 
    int client_socket = socket(AF_INET,SOCK_STREAM,0);
    if(client_socket <0){
        printf("Cannot creat the socket\n");
    } 
else {
        printf("Socket created\n");
    } 
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(8888);
    int connection_staus = connect(client_socket,(struct sockaddr *) &server_address, sizeof(server_address));
    if(connection_staus <0){
        printf("Can't connect to sever\n");
    } 
else {
        printf("connection established\n");
    }
    int V,edge[20][2],G[20][20],i,j,k=0,S;
    printf("\nEnter no. of vertices: ");
    scanf("%d",&V);
    printf("Enter graph in matrix form:\n");
    for(i=0;i<V;i++){
        for(j=0;j<V;j++)
        {
            scanf("%d",&G[i][j]);
            if(G[i][j]!=0)
                edge[k][0]=i,edge[k++][1]=j;
        }
    }
    printf("\nEnter source: ");
    scanf("%d",&S);
    if(send(client_socket, &V ,sizeof(V),0) < 0){
        printf("Couldn't send vertices");
        exit(0);
    } 
    if(send(client_socket, &k ,sizeof(k),0) < 0){
        printf("Couldn't send vertices");
        exit(0);
    } 
    if(send(client_socket, &G ,sizeof(G),0) < 0){
        printf("Couldn't send graph");
        exit(0);
    }
    if(send(client_socket, &edge ,sizeof(edge),0) < 0){
        printf("Couldn't send edge");
        exit(0);
    }
    if(send(client_socket, &S ,sizeof(S),0) < 0){
        printf("Couldn't send source");
        exit(0);
    }
    printf("\n\nData sent to Server for Applying Bellman Ford Algorithm.\n\n");
    int flag, distance[20], parent[20];
    if(recv(client_socket, &flag ,sizeof(flag),0) < 0){
        printf("Couldn't recieve flag");
        exit(0);
    }
    if(recv(client_socket, &distance ,sizeof(distance),0) < 0){
        printf("Couldn't recieve distance");
        exit(0);
    }
    if(recv(client_socket, &parent ,sizeof(parent),0) < 0){
        printf("Couldn't recieve parent");
        exit(0);
    }
    printf("Recieved Result:\n");
    if(flag)
        for(i=0;i<V;i++)
            printf("Vertex %d -> cost = %d parent = %d\n",i+1,distance[i],parent[i]+1);
     if(flag)
        printf("\nNo negative weight cycle\n");
    else 
        printf("\nNegative weight cycle exists\n");
    printf("Program ended!!\n");
    close(client_socket);
    return 0;
}
