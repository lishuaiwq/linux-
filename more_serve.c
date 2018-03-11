#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<ctype.h>
#include<signal.h>
#include<sys/types.h>
#include<strings.h>
#include<arpa/inet.h>
#define ip "192.168.240.128"
#define port 8888
void sigan_wait(int n)
{
    while(waitpid(0,NULL,WNOHANG)>0);
	exit(-1); 
} 
int main()
{
  int sfd,cfd,n;
  socklen_t  blen,aclen;
  pid_t pid;
  char prt[BUFSIZ]; 
  char buf[BUFSIZ]; 
 sfd=socket(AF_INET,SOCK_STREAM,0);// 
 struct sockaddr_in s_ser,c_ser;
 bzero(&s_ser,sizeof(s_ser));
 s_ser.sin_family=AF_INET;
 s_ser.sin_port=htons(port);
inet_pton(AF_INET,ip,(void *)&s_ser.sin_addr.s_addr); 
blen=sizeof(s_ser);
 bind(sfd,(struct sockaddr*)&s_ser,blen); 
 listen(sfd,128); 		 
 while(1)
 {
	 aclen=sizeof(c_ser); 	 
     cfd=accept(sfd,(struct sockaddr*)&c_ser,&aclen);
	 printf("ip=%s,port=%d\n",inet_ntop(cfd,&c_ser.sin_addr.s_addr,prt,sizeof(prt)),ntohs(c_ser.sin_port)); 
	 pid=fork();
	 if(pid==0)
      {
			  close(sfd);
		 break;
	  }
	 else if(pid>=0) 
	 {
	       close(cfd);
		   signal(SIGCHLD,sigan_wait); 
	 } 
 } 
 if(pid==0)
 {
   int i;		 
   while(1)
   {
        n=read(cfd,buf,sizeof(buf));
		if(n==0)
		{
		   close(cfd);
		   exit(1); 
		} 	
		for(i=0;i<n;i++)
				buf[i]=toupper(buf[i]);
		write(cfd,buf,sizeof(buf)); 
   } 
 } 
   return 0;
} 
