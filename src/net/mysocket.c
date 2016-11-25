#include "mysocket.h"
#include <pthread.h>
#include <time.h>
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
		printf("socket bind error!\n");
		return RT_ERR_BIND;
	}
	rt=listen(serverSock,10);
	if(rt<0) {
		close(serverSock);
		return RT_ERR_LISTEN;
	}
	return RT_OK;
}
//int END=0;
pthread_mutex_t mut;
void do_thread(SOCKET connSock){
	char recvBuf[BUFMAX];
	char sendBuf[BUFMAX];
	memset(recvBuf,0,BUFMAX);
	int rt=recv(connSock,recvBuf,BUFMAX,0);
    //printf("now in thread2\n");
	if(rt<0) {
		//END=1;
		close(connSock);
		pthread_exit(NULL);
		return ;
	} else if(!rt) {
		close(connSock);
		pthread_exit(NULL);
		return ;
	}
	memset(sendBuf,0,BUFMAX);
	doWork(recvBuf,sendBuf);
    printf("now in thread\n");
	rt=send(connSock,sendBuf,strlen(sendBuf),0);
	
	pthread_mutex_lock(&mut);
	writeLog(recvBuf);
	writeLog(sendBuf);
	pthread_mutex_unlock(&mut);
	
	close(connSock);
	pthread_exit(NULL);//结束一个线程
	return ;
}

void work(){
    while(1){
        struct sockaddr_in clientAddr;
        int size = sizeof(struct sockaddr);

        SOCKET connSock;
        connSock = accept(serverSock,(struct sockaddr*)&clientAddr,&size);
        pthread_t tmp_th;
        pthread_mutex_init(&mut,NULL);//
        int ret = pthread_create(&tmp_th,NULL,(void *)do_thread,connSock);//创建一个线程
        //printf("thread is start!\n");
        if(ret == -1){
        	printf("Pthread create fail!\n");
        	continue;
            //writeLog("Pthread create fail!\n");
        }
        //if(END) break;
        pthread_join(tmp_th,NULL); //等待一个线程的结束
    }
}
