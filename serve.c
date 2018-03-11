#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>
#define serve_port 6666

int main() 
{
  int lfd,cfd;	
  struct sockaddr_in  serve_addr,c_addr;
  int buf;
  char serve_ip[]="192.168.240.128"; 
  char buff[BUFSIZ];
  char arr[BUFSIZ]; 
  int n,i;
//建立套接字
lfd=socket(AF_INET,SOCK_STREAM,0);
//给套接字借口绑定IP和端口号
serve_addr.sin_family=AF_INET;
serve_addr.sin_port=htons(serve_port);
inet_pton(AF_INET,serve_ip,(void*)&buf);
serve_addr.sin_addr.s_addr=(int)buf;
bind(lfd,(struct sockaddr *)&serve_addr,sizeof(serve_addr)); 
//jianting
listen(lfd,5);
socklen_t socklen=sizeof(c_addr); 
cfd=accept(lfd,(struct sockaddr*)&c_addr,&socklen);
if(cfd==-1)
{
    perror("accept");
	exit(1); 
} 
printf("ip=%s,port=%d\n",inet_ntop(lfd,&c_addr.sin_addr.s_addr,arr,sizeof(arr)),ntohs(c_addr.sin_port)); 
while(1)
{
  n= read(cfd,buff,sizeof(buff));
  for(i=0;i<n;i++)
		  buff[i]=toupper(buff[i]);
  write(cfd,buff,n); 
} 
close(lfd);
close(cfd); 

   return 0;
} 
