#ifndef __CLIENT_H__
#define __CLIENT_H__

#pragma comment(lib, "DLL.lib")
#include <make_client.h>
#include <Communication.h>


void Login(SOCKET sock, int select, INFO* information);
void Register(SOCKET sock, int select, INFO* information);
int Menu_1();
int Menu_2();
int Menu_1_Action(SOCKET sock, int select, INFO* information);
int Menu_2_Action(SOCKET sock, int select, INFO* information);
void View(SOCKET sock, INFO* information);
void Deposit(SOCKET sock, int select, INFO* information);
void Withdraw(SOCKET sock, int select, INFO* information);

extern FILE* fp;
extern int Key[BUFSIZE];

#endif