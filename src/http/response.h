#ifndef __RESPONSE_H__
#define __RESPONSE_H__
#include "http.h"
#include "../init/mydefine.h"
struct Http response;
char status[50];
char* msgbody;
char contlen[300];
int bodylen;
void setMsgBodyLen();
void setMsgHead(const char* value);
void initResponse();
void contentResponse(char* sendbuf);
#endif