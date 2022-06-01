#include "server.h"

FILE* fp;


int main()
{
	SOCKET listen_sock;
	listen_sock = Make_Server(SERVER_PORT);			// 릴레이 서버가 접속할 서버 생성
	SOCKET client_sock;
	SOCKADDR_IN clientaddr;
	int addrlen;

	system("title Server");

	while (1)
	{
		addrlen = sizeof(clientaddr);
		client_sock = accept(listen_sock, (SOCKADDR*)&clientaddr, &addrlen);
		if (client_sock == INVALID_SOCKET)
		{
			printf("Accept Fail! \n");
			continue;
		}

		printf("\n[TCP 서버] 클라이언트 접속 : IP주소=%s, 포트번호=%d \n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

		_beginthread((_beginthread_proc_type)Thread_Proc, 0, (void*)client_sock);
	}


	return 0;
}

void Thread_Proc(void* sock)
{
	SOCKET client_sock = (SOCKET)sock;
	char msg[BUFSIZE];
	int select;

	List myList;
	Init_List(&myList);
	Make_List(&myList);



	INFO information;
	int alert;

	do
	{
		F_Recv(client_sock, msg);
		select = atoi(msg);

		alert = Menu_1_Action(client_sock, select, &information, &myList);
		if (alert == -1)
			return;
	} while (alert);

}
