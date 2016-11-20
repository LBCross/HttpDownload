#include "mywork.h"
#include <stdlib.h>
char dir[1024];
void doWork(const char * recvbuf,char *sendbuf) {
	printf("this dowork\n");
	initResponse();
	paresRequset(recvbuf);
	if(!strcmp(method,"GET")) {
		if(!strlen(path)||!strcmp(path,"/")) {
			strcpy(path,"/src/html/index.html");
		}
		int dotpos=strrchr(path,'.')-path;
		int down=0;
		if(dotpos<strlen(path)) {
			char* suffix=substr(path,dotpos+1,strlen(path));
			//printf("%s ++++\n",suffix);
			if(!strcmp(suffix,"html")) {
				setMsgHead("Content-Type: text/html; charset=utf-8\r\n");
			} 
			else if(!strcmp(suffix,"css")) {
				setMsgHead("Content-Type: text/css\r\n");
			}
			else if(!strcmp(suffix,"js")){
				setMsgHead("Content-Type: application/x-javascript; charset=utf-8\r\n");
			} else getFile();
		} else getFile();
		setResponStaticPage();
		setMsgBodyLen();//Content-Length:bodylen
		//printf("%s\n**\n%s\n**\n%s\n**\n%s\n**\n%s\n**\n",response.version,status,response.msghead,contlen,msgbody);
		contentResponse(sendbuf);
		writeLog(sendbuf);
		printf("sendBuf : \n%s\n",sendbuf);
	} else {
		strcpy(status,"405 \r\n");
	}
}
void getFile() {
	int filebegin=strrchr(path,'/')-path;
	char* filename=substr(path,filebegin+1,strlen(path));
	strcat(filename,"\r\n");
	char tmp[1024]={0};
	strcpy(tmp,"Content-Type: application/octet-stream\r\n");
	strcat(tmp,"Content-Disposition: attachment;fileName=");
	setMsgHead(strcat(tmp,filename));
}
void setResponStaticPage(){
	strcpy(dir,"..");
	strcat(dir,path);
	FILE *file=NULL; 
	file=fopen(dir,"rb");
	if(file==NULL){//文件找不到,跳转到404
		printf("404 Not Found\n");
		setMsgHead("Content-Type: text/html; charset=utf-8\r\n");
		strcpy(status,"404 Not Found\r\n");
		strcpy(dir,"../src/html/404.html");
		file=fopen(dir,"rb");
	}
	if(file==NULL) return;
	fseek(file,0,SEEK_END);
	bodylen=ftell(file);
	rewind(file);
	free(msgbody);
	msgbody= (char*)malloc(sizeof(char)*bodylen+1);
	bodylen=fread(msgbody,sizeof(char),bodylen,file);
	msgbody[bodylen]=0;
	fclose(file);
}