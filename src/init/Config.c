#include "Config.h"
#include "mydefine.h"
#include <string.h>
#include <stdio.h>

void conInit(char *_filename){
	//strcpy(filename,_filename);
	filename = _filename;	
	KEY_NUM = 0;
	parseFile();
}
void parseFile(){
	FILE* file=NULL;
	file = fopen(filename,"r");
	if(file==NULL){
		printf("文件为空！\n");
		return ;
	} 
	char s[N];
	char s1[N],s2[N];
	int j=0,len,i,len1=0,len2=0;
	while(fgets(s,N,file)!=NULL){
		len=strlen(s);
		if(len<=1) continue;
		for(i=0;i<len;i++){
			if(s[i]=='=') break;
			s1[len1++]=s[i];
		}i++;	
		for(;i<len;i++) s2[len2++]=s[i];	
		j=0;
		KEY_NUM++;
		for(i=0;i<len1;i++) {
			if(s1[i]=='\n') break;
			if(s1[i]!=' ') Key[KEY_NUM][j++]=s1[i];
		}
		j=0;
		for(i=0;i<len2;i++){
			if(s2[i]=='\n') break;
			if(s2[i]!=' ') Value[KEY_NUM][j++]=s2[i];
		}	
		len=len1=len2=i=j=0;
	}
	fclose(file);
}
void print_Key_Value(){
	for(int i=1;i<=KEY_NUM;i++){
		printf("[%s] --> [%s] \n",Key[i],Value[i]);
	}
}
int getValue(char *KEY){
	int len=0,num;
	for(int i=1;i<=KEY_NUM;i++){
		len=strlen(Key[i]);num=0;
		if(strlen(KEY)!=len) continue;
		for(int j=0;j<len;j++){
			if(KEY[j]!=Key[i][j]) break;
			num++;
		}
		if(num==len) return i;
	}
	return 0;	
}




