#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h> 

#include<netinet/in.h>

#include <math.h>


/* Returns the log to the base b of y. */

int power (int a, int b)
{
  int res = 1, i;
  for (i=0;i<b;i++) {
    res = res * a;
  }
  return res;
}

int logs (int n)
{
  return (n > 1) ? 1 + logs(n / 2) : 0; 
}

int logbase (int y, int b)
{
  int lg;
  lg = logs(y)/logs(b);
  return(lg);
}

int min(int a, int b){
    return a > b ? b : a;
}

int main() {

    //Creating client socket
    int client_socket = socket(AF_INET,SOCK_STREAM,0);
    if(client_socket <0){
        printf("Cannot create the socket\n");
    } else {
        printf("Socket created\n");
    }

    //Creating sever Address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(9003);
    

    //Connection to the Server
    int connection_staus = connect(client_socket,(struct sockaddr *) &server_address, sizeof(server_address));
    if(connection_staus <0){
        printf("Can't connect to sever\n");
    } else {
        printf("connection established\n");
    }
    int data;
    char msg[1000];
    int server_reply;
    int tp=5, tt=1, n=10, loss=2;

    printf("Enter TP: ");
    scanf("%d", &tp);
    printf("Enter TT: ");
    scanf("%d", &tt);
    printf("Enter Number packets to trasmit: ");
    scanf("%d", &n);
    printf("Enter packet to be lost: ");
    scanf("%d", &loss);
    int i,j;
    int a = tp/tt;
    int max_packet = 1+(2*a);
    int no_of_bits = power(2, logbase(max_packet,2));
    int ws = min(max_packet, no_of_bits);
    printf("Window Size: %d\n\n", ws);
    int window[100], outstanding[100];
    int packets[n];

    for(i=0; i<n; i++){
        packets[i] = i;
    }

    if(send(client_socket, &tp ,sizeof(tp),0) < 0){
        printf("Couldn't send tp");
        exit(0);
        // break;
    } 
    if(send(client_socket, &tt ,sizeof(tt),0) < 0){
        printf("Couldn't send tt");
        exit(0);
        // break;
    }
    if(send(client_socket, &n ,sizeof(n),0) < 0){
        printf("Couldn't send n");
        exit(0);

        // break;
    }
    if(send(client_socket, &loss ,sizeof(n),0) < 0){
        printf("Couldn't send loss");
        exit(0);

        // break;
    }

    for(i=0; i<ws; i++){
            window[i] = packets[i];
    }
    int nCopy = i;
    for(i=0; i<(n-ws); i++){
        outstanding[i]=packets[nCopy];
        nCopy++;
    }

    int transmission_time=0, ack_time = 0,arrived_time, counter=0, temp = tt;
    int flag=0;
    while(1) {
        printf("Packet: %d\n",window[0]);
        
        if(counter == 0){
            transmission_time = temp;
        }else {
            transmission_time += tt;
        }
        
        printf("Trasmission Time: %d\n",transmission_time);
   
        if(send(client_socket, &window[0] ,sizeof(window[0]),0) < 0){
            printf("Couldn't send packet");
            break;
        }  
        if(send(client_socket, &transmission_time ,sizeof(transmission_time),0) < 0){
            printf("Couldn't send packet");
            break;
        }
        
        if(recv(client_socket, &server_reply ,sizeof(server_reply),0) < 0){
            printf("Couldn't recieve server reply");
            break;
        }

        if(server_reply == 1){
            for(i=0; i<ws-1; i++){
                    window[i] = window[i+1];
            }
            window[i] = outstanding[0];
            int nCopy = i+1;
            for(i=0; i<(n-ws)-1; i++){
                outstanding[i]=outstanding[i+1];
                nCopy++;
            }
            if(recv(client_socket, &arrived_time ,sizeof(arrived_time),0) < 0){
                printf("Couldn't recieve arrived time");
                break;
            }
            ack_time = arrived_time + tp;
            temp = ack_time;

            printf("Acknowledge Time: %d\n\n",ack_time);
            if(counter == 0)
                temp = ack_time;
            counter++;

            if(counter == ws)
                counter = 0;
        } else if(server_reply == 0) {
            if(recv(client_socket, &arrived_time ,sizeof(arrived_time),0) < 0){
                printf("Couldn't recieve arrived time");
                break;
            } 
            ack_time = arrived_time + tp;
            temp = ack_time;

            printf("Acknowledge Time: %d\n\n",ack_time);
            printf("All packets are trasmitted!!\n");
            break;
        } else if(server_reply == -1){
            if(recv(client_socket, &arrived_time ,sizeof(arrived_time),0) < 0){
                printf("Couldn't recieve arrived time");
                break;
            }
            ack_time = arrived_time + (2*tp);
            temp = ack_time;

            transmission_time = ack_time;
            printf("Waited Time: %d\n\n",ack_time);
        }

    }

    close(client_socket);
    return 0;
}
