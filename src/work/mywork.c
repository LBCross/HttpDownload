#include "mywork.h"
#include <stdlib.h>
char dir[1024];
int flag=0;
void doWork(const char * recvbuf,char *sendbuf) {
	printf("this dowork\n");
	initResponse();
	paresRequset(recvbuf);
	if(!strcmp(method,"GET")) {
		printf("path = %s\n",path);
		flag=0;
		if(!strlen(path)||!strcmp(path,"/")) {
			strcpy(path,"/src/html/index.html");
			flag = 1;
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
			} else setFileName();
		} else setFileName();
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
void setFileName() {
	//printf("path DOWN = %s\n",path);
	int filebegin=strrchr(path,'/')-path;
	char* filename=substr(path,filebegin+1,strlen(path));
	strcat(filename,"\r\n");
	char tmp[1024]={0};
	strcpy(tmp,"Content-Type: application/octet-stream\r\n");
	strcat(tmp,"Content-Disposition: attachment;fileName=");
	setMsgHead(strcat(tmp,filename));
	//setMsgHead(strcat(tmp,path));
	//printf("fileName = %s\n", filename);
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
	msgbody= (char*)malloc(sizeof(char)*bodylen*10+1);
	bodylen=fread(msgbody,sizeof(char),bodylen,file);
	//printf("DOWN %s \n",msgbody);
	if(flag) {
		getFileName();
		bodylen = strlen(msgbody);
	}
	msgbody[bodylen]=0;
	fclose(file);
}
void getFileName(){	
	DIR *directory_pointer;
    struct dirent *entry;
	addMsgBody("<body>\n<h1>下载列表</h1>\n");
   	if((directory_pointer=opendir("../docroot/"))==NULL)
    	printf( "Error opening \n ");
    else{
        while((entry=readdir(directory_pointer))!=NULL) {
			if(entry->d_name[0] == '.') continue;
			//printf("%s\n",entry->d_name);
			char tmp[1024] = {0};
			sprintf(tmp,"%s%s%s%s%s\n","<a href=\"../docroot/",entry->d_name,"\">",entry->d_name,"</a>");
			addMsgBody(tmp);
		}
        closedir(directory_pointer);
    }
	addMsgBody("</body>\n</html>\n");	
}
void addMsgBody(char* fileName){
	strcat(msgbody,fileName);
}






