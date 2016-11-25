#include "response.h"
#include <string.h>
#include <stdio.h>
void setMsgBodyLen() {
	char clen[20];
	sprintf(clen,"%d",bodylen);
	strcpy(contlen,"Content-Length: ");
	strcat(contlen,clen);
	strcat(contlen,"\r\n");
}
void setMsgHead(const char* value) {
	strcpy(response.msghead,value);
}
void initResponse() {
	strcpy(response.version,"HTTP/1.1 ");
	//msgbody= (char*)malloc(sizeof(char));
	//memset(contlen,0,300);
	strcpy(status,"200 OK\r\n");
}
void contentResponse(char* sendbuf) {
	strcat(sendbuf,response.version);
	strcat(sendbuf,status);
	strcat(sendbuf,response.msghead);

	strcat(sendbuf,contlen);
	strcat(sendbuf,"\r\n");
	strcat(sendbuf,msgbody);
}