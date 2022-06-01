#ifndef __COMMUNICATION_H__
#define __COMMUNICATION_H__



#include "top.h"

__declspec(dllexport) int F_Send(int s, char *msg);
__declspec(dllexport) int F_Recv(int s, char *msg);
__declspec(dllexport) void Public_Key_Exchange(SOCKET sock, int my_Public_Key, int *other_Public_Key);

#endif