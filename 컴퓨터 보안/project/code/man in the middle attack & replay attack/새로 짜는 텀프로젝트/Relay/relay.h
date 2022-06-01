#ifndef __RELAY_H__
#define __RELAY_H__
#pragma comment(lib, "DLL.lib")

#include <Make_Server.h>
#include <Communication.h>
#include <make_client.h>
#include <Log.h>

void Thread_Proc(void* sock);
int Menu_1_Action(SOCKET client_sock, SOCKET server_sock, INFO* information);
int Menu_2_Action(SOCKET client_sock, SOCKET server_sock, int select, INFO* information);
int View(SOCKET client_sock, SOCKET server_sock);

extern FILE* CtoS;
extern FILE* StoC;
extern int Key_client[BUFSIZE];
extern int Key_server[BUFSIZE];

#endif