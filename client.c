#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#define s_port 6666
#define s_ip "192.168.240.128"
int main()
{
   int cfd,n;
   char buf[BUFSIZ]; 
   char buff[BUFSIZ]; 
   struct sockaddr_in s_addr;
   cfd=socket(AF_INET,SOCK_STREAM,0);//创建socket
    if(cfd==-1)
  {
     perror("socket");
     exit(1); 
  } 
   bzero(&s_addr,sizeof(s_addr)); 
   //不需要绑定的话系统会为我们自己绑定一个端口号和ip
   s_addr.sin_family=AF_INET;
   s_addr.sin_port=htons(s_port);
   inet_pton(AF_INET,s_ip,&s_addr.sin_addr.s_addr); 
  int co= connect(cfd,(struct sockaddr*)&s_addr,sizeof(s_addr));
  if(co==-1)
  {
	perror("connect"); 	  
     exit(1); 
  } 
  
   while(1) 
   {
		   fgets(buf,sizeof(buf),stdin);//从键盘输入
   write(cfd,buf,strlen(buf));
   n=read(cfd,buff,sizeof(buff)); 
   write(STDOUT_FILENO,buff,n);
   }
   close(cfd); 
   return 0;
}
