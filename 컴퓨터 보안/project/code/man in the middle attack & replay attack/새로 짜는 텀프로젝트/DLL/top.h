#ifndef __TOP_H__
#define __TOP_H__


#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <process.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#define BUFSIZE 512
#define RELAY_PORT 9000
#define SERVER_PORT 9001

typedef struct _info
{
	int select;
	char name[BUFSIZE];
	char id[BUFSIZE];
	char pw[BUFSIZE];
	long money;
}INFO;

__declspec(dllexport) void Write_Data(FILE* fp, INFO info);
__declspec(dllexport) void Read_Data(FILE*fp, INFO *info);
__declspec(dllexport)void PW_scanf(char *pw);



#endif
