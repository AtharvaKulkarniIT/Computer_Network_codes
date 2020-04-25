#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#define SERV_TCP_PORT 5035
int main(int argc, char **argv) {
  int sockfd,newsockfd,clength;
  struct sockaddr_in serv_addr,cli_addr;
  char a[30],b[30],c[30]={0},q[30],p[30]={0},np[30]={0},crc[10]={0},r[30]={0};
  int n,m,i=0,j=0,count=0,k=0,l=0,ir=0,ip=0,cou=0,u=0,w=0,nk=0;

  sockfd=socket(AF_INET,SOCK_STREAM,0);
  serv_addr.sin_family=AF_INET;
  serv_addr.sin_addr.s_addr=INADDR_ANY;
  serv_addr.sin_port=htons(SERV_TCP_PORT);
  
  printf("\n Binded...");
  bind(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
  listen(sockfd,5);
  clength=sizeof(cli_addr);
  newsockfd=accept(sockfd,(struct sockaddr*)&cli_addr,&clength);

  recv(newsockfd,a,30);
  printf("\nNo. of Frames :%s\n",a);

  for(i=0;i<a;i++) {
    if(recv(newsockfd,b,30)) {
      q="Success";
      write(newsockfd,q,30);
      printf("Data: %s",b);
    }
    else {
      q="Failure";
      write(newsockfd,q,30);
    }
  }

  /*write(newsockfd,q,30);
  write(newsockfd,r,30);
  write(newsockfd,crc,10);*/
  close(sockfd);
  return 0;
}