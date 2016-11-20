#include "request.h"
/*GET / HTTP/1.1
Host: 127.0.0.1:9888
Connection: keep-alive
Upgrade-Insecure-Requests: 1
User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Ubuntu Chromium/53.0.2785.143 Chrome/53.0.2785.143 Safari/537.36
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,×/×;q=0.8
Accept-Encoding: gzip, deflate, sdch
Accept-Language: zh-CN,zh;q=0.8,zh-TW;q=0.6,en;q=0.4
*/
char str[BUFMAX];
int paresRequset(const char* recvbuff) {
	strcpy(str,recvbuff);
	int rt=paresResqusetHead();
	rt=paresResqusetMsgHead();
	return rt;
}

int paresResqusetHead() {
	int end=findPos(str,"\r\n");
	strcpy(head,substr(str,0,end));
	strcpy(method,strtok(head," "));
	strcpy(uri,strtok(NULL," "));
	strcpy(path,uri);
	strcpy(request.version,strtok(NULL," "));
	//printf("%sxxx %sxxx %sxxx\n",method,uri,request.version);
	return RT_OK;
}
int paresResqusetMsgHead() {
	int begin=findPos(str,"\r\n");
	int end=findPos(str,"\r\n\r\n");
	strcpy(request.msghead,substr(str,begin+2,end));
	return RT_OK;
}
