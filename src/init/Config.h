#ifndef _CONFIG_H_
#define _CONFIG_H_

#include "mydefine.h"


char* filename;
char Key[N][N];
char Value[N][N];
int KEY_NUM;
void conInit(char *_filename);
void parseFile();
void print_Key_Value();
int getValue(char *KEY);


#endif
