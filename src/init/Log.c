#include "Log.h"
#include <time.h>
void logInit(char *_logfile){
	logfile = _logfile;	
}
int CNT = 0;
void writeLog(char *fmt, ...){
	memset(logBuf,0,LOG_SIZE);
	time_t t = time(NULL);
	struct tm *curTime = localtime(&t);
	char fmtbuf[255] = {0};
	sprintf(fmtbuf,"[%4d-%02d-%02d %02d:%02d:%02d]\n",
		curTime->tm_year + 1900,curTime->tm_mon + 1,
		curTime->tm_mday,curTime->tm_hour,
		curTime->tm_min,curTime->tm_sec);//将时间数据输入到fmtbuf字符串中
	FILE* file = NULL;
	file = fopen(logfile,"a");//在文件中追加数据
	fputs(fmtbuf,file);
	va_list arg;
	va_start(arg,fmt);// 函数在栈中排列的一堆参数的起始地址
	CNT = vsprintf(logBuf,fmt,arg);//函数的参数倒序压入栈中，能解析多个参数
	//printf("CNT= %d\n",CNT);
	
	va_end(arg);
	fputs(logBuf,file);
	fputs("\n",file);
	
	fclose(file);

}
