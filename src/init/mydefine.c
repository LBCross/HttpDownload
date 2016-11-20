#include "mydefine.h"
char* substr(const char* str,int begin,int end){
   int n = end - begin;
   char* stbuf=(char*)calloc(n+1,sizeof(char*));
   strncpy(stbuf, str + begin, n);
   stbuf[n] = 0;
   return stbuf;
}
int findPos(const char * str,const char * substr) {
	return strstr(str,substr)-str;
}
