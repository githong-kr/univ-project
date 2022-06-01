#ifndef __SERVER_H__
#define __SERVER_H__
#pragma comment(lib, "DLL.lib")

#include <Make_Server.h>
#include <Communication.h>
#include <Log.h>

typedef struct _node
{
	char id[BUFSIZE];
	char pw[BUFSIZE];
	char name[BUFSIZE];
	long money;
	struct _node* rLink;

}Node;

typedef struct _list
{
	Node *head;
	Node *cur;
	Node *tail;
	int length;
}List;

void Thread_Proc(void* sock);
int Menu_1_Action(SOCKET client_sock, int select, INFO* information, List* myList);
int Menu_2_Action(SOCKET client_sock, int select, INFO* information);
void Init_List(List* myList);
void Add_List(List* myList, INFO information);
void Make_List(List* myList);
void Make_File(List* myList);
int Check_id(List *myList, INFO info);
int Login(SOCKET client_sock, int select, INFO* information, List *myList);
int Register(SOCKET client_sock, int select, INFO* information, List *myList);
void View(SOCKET client_sock, INFO information);
void Remove_Tab(char *msg);

extern FILE* fp;
extern int Key[BUFSIZE];




#endif