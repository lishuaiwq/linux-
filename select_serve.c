#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <sys/socket.h>
#include<stdio.h>
#include<unistd.h>
#define ip "192.168.240.128"
#define port 9527
int main() 
{
		int sfd,maxfd,maxi,cfd,fd;
   int i,n,nready;
   int client[BUFSIZ];
   char  buf[BUFSIZ];
   char readd[BUFSIZ]; 
  socklen_t servelen,clientlen;
  struct sockaddr_in s_serve,c_client;  
  sfd=socket(AF_INET,SOCK_STREAM,0); 
 fd_set refd,allfd;
 s_serve.sin_family=AF_INET;
 s_serve.sin_port=htons(port);//套接字
 inet_pton(AF_INET,ip,(void *)&s_serve.sin_addr.s_addr);//地址
 servelen=sizeof(s_serve); 
 int b=bind(sfd,(struct sockaddr*)&s_serve,servelen);
 listen(sfd,128); 
 if(b<0)
 {
    perror("use bind");
	exit(1); 
 } 
 maxi=-1;
 maxfd=sfd;
 for(i=0;i<BUFSIZ;i++)
		 client[i]=-1;
 FD_ZERO(&allfd);
 FD_ZERO(&refd); 
 FD_SET(sfd,&allfd); 
 while(1)
 {
    refd=allfd;       
   nready=select(maxfd+1,&refd,NULL,NULL,NULL);//对sfd进行监听
   if(nready<0)
   {
      perror("use nready");
	  exit(1); 
   } 
   if(FD_ISSET(sfd,&refd))//如果sfd有动静的话,就建立连接
   {
       clientlen=sizeof(c_client);
	   cfd=accept(sfd,(struct sockaddr*)&c_client,&clientlen);//返回新的文件描述符用来通信
	printf("ip=%s  port=%d\n",inet_ntop(AF_INET,&c_client.sin_addr.s_addr,buf,sizeof(buf)),ntohs(c_client.sin_port)); 
      //将返回的文件描述符保存在client[]里面 
	  for(i=0;i<BUFSIZ;i++)
	  {
	       if(client[i]<0)//meifangjinqu
		   {
		   client[i]=cfd; 
		   break;
		   } 
	  } 
	  if(i==BUFSIZ)
	  {
	      printf("too many cfd\n");
		  exit(1); 
	  } 
     FD_SET(cfd,&allfd);
	 if(cfd>maxfd)
	     maxfd=cfd;
	if(i>maxi)
	  maxi=i;
	if(--nready==0)
			continue;
   }  
  //下面来检测哪个读数据的套接字满足条件，在自己定义的client里面搜索
   for(i=0;i<=maxi;i++)
   {
       if((fd=client[i])<0)
			   continue;
	   if(FD_ISSET(fd,&refd))//有写的动作的时候
	   {   	  
	      if((n=read(fd,readd,sizeof(readd)))==0)
		  {
		     close(fd);
			 FD_CLR(fd,&allfd);
			 client[i]=-1; 
		  } 
		  else
		  {
	              int j;
				  for(j=0;j<n;j++)
						  readd[j]=toupper(readd[j]);
				  write(fd,readd,n); 
		  } 
		  if(--nready==0)
				  break;
	   } 
   
   } 
  }
 close(fd);
 close(sfd); 
return 0; 
}
