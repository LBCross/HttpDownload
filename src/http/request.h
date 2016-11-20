#ifndef __REQUEST_H__
#define __REQUEST_H__
#include "../init/mydefine.h"
#include "http.h"
struct Http request;
char method[20];
char head[100];
char uri[1024];
char path[1024];
int paresRequset(const char * recvbuff);
int paresResqusetHead();
int paresResqusetMsgHead();

#endif