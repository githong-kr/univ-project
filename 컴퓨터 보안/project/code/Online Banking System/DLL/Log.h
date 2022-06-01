#ifndef __LOG_H__
#define __LOG_H__

#include "top.h"

__declspec(dllexport) void Write_Log(FILE *fp, char *msg);
__declspec(dllexport) void Menu_1_Log(char *msg, int select);
__declspec(dllexport) void Menu_2_Log(char *msg, int select);

#endif