#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>   //inet_addr
#include<unistd.h>  //write

#include<netinet/in.h>

int main() {
    //Server message
    char msg[256] = "This is server talking to you";

    // socket creation
    int s_socket = socket(AF_INET,SOCK_STREAM,0);
    if(s_socket<0){
        printf("Socket creation failed!\n");
    } else {
        printf("Socket created successfully\n");
    }

    //Address specification
    struct sockaddr_in s_address;
    s_address.sin_family = AF_INET;
    s_address.sin_port = htons(9003);
    s_address.sin_addr.s_addr = INADDR_ANY;

    //Binding Address to Socket
    int status = bind(s_socket,(struct sockaddr *)&s_address,sizeof(s_address));
    if(status < 0){
        printf("Binging not successful\n");
    } else {
        printf("Successful Binding\n");
    }

    //Listening 
    int listen_status;
    listen_status = listen(s_socket,5);
    if(listen_status <0){
        printf("Listening problems\n");
    } else {
        printf("Waiting...\n");
    }

    //Accepting client sockets
    int client_socket, size = sizeof(struct sockaddr_in);
    struct sockaddr_in client_address;
    client_socket = accept(s_socket,(struct sockaddr *)&client_socket,&size);
    if(client_socket < 0){
        printf("Accept failed\n");
    } else {
        printf("Client accepted\n");
    }

    // int data;
    // char msg1[] = "Data recieved!!";
    // while(1){
    //     if(recv(client_socket, &data ,sizeof(data),0) < 0){
    //         printf("Couldn't recieve packet");
    //         break;
    //     } 

    //     printf("Recieved: %d\n", data);

    //     if(send(client_socket, &msg1 ,sizeof(msg1),0) < 0){
    //         printf("Couldn't send reply");
    //         break;
    //     }  
    // }

    int tp,tt,n,loss;

    if(recv(client_socket, &tp ,sizeof(tp),0) < 0){
        printf("Couldn't recieve tp");
        exit(0);

        // break;
    } 

    if(recv(client_socket, &tt ,sizeof(tt),0) < 0){
        printf("Couldn't recieve tt");
        exit(0);

        // break;
    }

    if(recv(client_socket, &n ,sizeof(n),0) < 0){
        printf("Couldn't recieve n");
        exit(0);

        // break;
    }
    if(recv(client_socket, &loss ,sizeof(n),0) < 0){
        printf("Couldn't recieve loss");
        exit(0);

        // break;
    }

    printf("TP: %d ", tp);
    printf("TT: %d ", tt);
    printf("N: %d\n\n", n);
    int packet;
    int expected = 0;
    int ack,i=0, flag=0, flag1=1,j=0;
    int arrived_time=0, arrived_time_copy=0;
    int arrived[n];
    while(1){
        if(recv(client_socket, &packet ,sizeof(packet),0) < 0){
            printf("Couldn't recieve packet");
            break;
        } 

        if(recv(client_socket, &arrived_time ,sizeof(arrived_time),0) < 0){
            printf("Couldn't recieve packet");
            break;
        }

        if(packet == loss){
            arrived_time_copy = arrived_time;
            // ack = -1;
            // if(send(client_socket, &ack ,sizeof(ack),0) < 0){
            //     printf("Couldn't send reply");
            //     break;
            // } 
            // arrived_time += tp;
            // if(send(client_socket, &arrived_time ,sizeof(arrived_time),0) < 0){
            //     printf("Couldn't send arrived time");
            //     break;
            // }
            // continue;

            for(j=loss+1; j<n; j++){
                printf("Dropped Packet: %d\n", j);
                arrived_time_copy += tt;
                printf("Arrival Time: %d\n\n", arrived_time_copy);
            }

            ack = -1;

            if(send(client_socket, &ack ,sizeof(ack),0) < 0){
                printf("Couldn't send reply");
                break;
            } 
            arrived_time += 2*(2*tp);
            if(send(client_socket, &arrived_time ,sizeof(arrived_time),0) < 0){
                printf("Couldn't send arrived time");
                break;
            }
            // expected++;
            loss = -1;
            continue;
        }
        
        if(packet == expected) {
            arrived[i] = packet;
            arrived_time += tp;
            printf("Recieved Packet: %d\n", packet);
            printf("Arrival Time: %d\n\n", arrived_time);
            i++;
            flag = 1;
            expected++;
        }
        //  else {
        //     arrived_time += tp;
        //     printf("Dropped Packet: %d\n", packet);
        //     printf("Arrival Time: %d\n\n", arrived_time);
        //     // flag1=1;
        // }
        if(expected != n){
            ack = 1;
        }else {
            ack = 0;

        }

        // if(flag1 == 1)
        //     ack = -2;

        if(send(client_socket, &ack ,sizeof(ack),0) < 0){
            printf("Couldn't send reply");
            break;
        } 

        if(flag == 1){
            if(send(client_socket, &arrived_time ,sizeof(arrived_time),0) < 0){
                printf("Couldn't send arrived time");
                break;
            }
        }

        if(ack == 0){
            printf("All packets recieved!!\n");
            break; 
        }
    }
        
    close(s_socket);
    return 0;
}