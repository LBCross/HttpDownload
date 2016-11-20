#ifndef __MYSOCKET_H__
#define __MYSOCKET_H__
#include "../init/mydefine.h"
#include "../init/Config.h"
#include "../init/Log.h"
#include <unistd.h>/*close()*/
#include <netinet/in.h>/*struct sockaddr_in,struct in_addr*/
#include <sys/socket.h>/*socket(),bind(),listen(),accept(),recv()*/
#include <arpa/inet.h>/*inet_addr()*/
#include "../work/mywork.h"
#define SOCKET int

SOCKET serverSock;
char mSip[50];
int mPort;
struct sockaddr_in addr_in;

int initSocket(const char *sip,const int port);
int genSocket();
int	sockListen();
void work();


#endif
