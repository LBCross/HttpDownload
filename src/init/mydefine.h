#ifndef __MYDEFINE_H__
#define __MYDEFINE_H__
#define BUFMAX 1024000
#define LOG(a) printf("%s\n",a)
#define N 100
#define LOG_SIZE 10240
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
enum {
	RT_ERR,
	RT_OK,
	RT_ERR_SOCKET,
	RT_ERR_BIND,
	RT_ERR_LISTEN
};
int findpos(const char * str,const char * substr);
char* substr(const char* str,int begin,int end);
#endif
