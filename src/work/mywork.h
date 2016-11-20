#ifndef __MYWORK_H__
#define __MYWORK_H__

#include "../init/mydefine.h"
#include "../init/Log.h"
#include "../http/request.h"
#include "../http/response.h"
#include <dirent.h>
void doWork( const char * recvbuf,char *sendbuf);
void setResponStaticPage();
void setFileName();
void getFileName();
void addMsgBody();
#endif
