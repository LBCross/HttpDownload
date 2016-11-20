#ifndef _LOG_H_
#define _LOG_H_
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include "mydefine.h"
char logBuf[10240];
void logInit(char *_logfile);
void writeLog(char *fmt, ...);
char *logfile;

#endif
