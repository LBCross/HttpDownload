#include "mysocket.h"
int initSocket(const char *sip,const int port) {
	strcpy(mSip,sip);
	mPort=port;
	int rt=genSocket();
	if(rt!=RT_OK) return rt;
	rt=sockListen();
	if(rt!=RT_OK) return rt;
	printf("socket init success ip = %s port = %d\n",mSip,mPort);
	return RT_OK;
}
int genSocket() {
	serverSock=socket(AF_INET,SOCK_STREAM,0);
	if(serverSock<0) return RT_ERR_SOCKET;
	return RT_OK;
}
int sockListen() {  
	//addr_in.sin_addr.s_addr=htonl(INADDR_ANY);//ANY IP;
	addr_in.sin_addr.s_addr=inet_addr(mSip);//能够把一个用数字和点表示IP地址的 字符串转换成一个无符号长整形。
	addr_in.sin_family=AF_INET;
	addr_in.sin_port=htons(mPort);
	int rt=bind(serverSock,(struct sockaddr*)&addr_in,sizeof(struct sockaddr));
	if(rt<0) {
		close(serverSock);
		return RT_ERR_BIND;
	}
	rt=listen(serverSock,10);
	if(rt<0) {
		close(serverSock);
		return RT_ERR_LISTEN;
	}
	return RT_OK;
}
void work() {
	char recvBuf[BUFMAX];
	char sendBuf[BUFMAX];
	while(1) {
		struct sockaddr_in clientAddr;
		int len=sizeof(struct sockaddr);
		SOCKET connSock=accept(serverSock,(struct sockaddr*)&clientAddr,&len);
		memset(recvBuf,0,BUFMAX);
		int rt=recv(connSock,recvBuf,BUFMAX,0);
		writeLog(recvBuf);
		if(rt<0) {
			close(connSock);
			return ;
		} else if(!rt) {
			close(connSock);
			continue;
		}
		memset(sendBuf,0,BUFMAX);
		doWork(recvBuf,sendBuf);
		rt=send(connSock,sendBuf,strlen(sendBuf),0);
		close(connSock);
	}
}
