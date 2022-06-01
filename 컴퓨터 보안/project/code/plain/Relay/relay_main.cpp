#include "relay.h"

FILE* CtoS;
FILE* StoC;

int Key_client[BUFSIZE];
int Key_server[BUFSIZE];

int main()
{

	SOCKET listen_sock;
	listen_sock = Make_Server(RELAY_PORT);			// 클라이언트가 접속할 릴레이 서버를 만듦
	SOCKET client_sock;
	SOCKADDR_IN clientaddr;
	int addrlen;

	system("title Relay Server");

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

/*
	int Bob_Exponent = 22;										// ECC
	int Symmetric_Key[BUFSIZE];

	Key_Gender_ECC(client_sock, Symmetric_Key, Bob_Exponent);

	printf("Symmetric_Key : ");
	for (int i = 0; i < BUFSIZE; i++)
		printf("%d", Symmetric_Key[i]);
	puts("");
	Sleep(5464984);
*/

	int exponent_client = 22;
	Key_Gender_ECC(client_sock, Key_client, exponent_client);
	

	char msg[BUFSIZE];
	int select;

	CtoS = fopen("CtoS.txt", "a");
	StoC = fopen("StoC.txt", "a");
	fclose(CtoS);
	fclose(StoC);

	SOCKET server_sock;
	server_sock = Make_Client(SERVER_PORT, "127.0.0.1");			// 서버로 접속하는 클라이언트 소켓 생성
				
	int exponent_server = 15;
	Key_Gender_ECC(server_sock, Key_server, exponent_server);

	// 이하 통신은 client_sock => 클라이언트  server_sock => 서버

	INFO information;
	int alert;
	do
	{
		if (F_Recv(client_sock, msg) == -1) return;
		A5_1(msg, Key_client);	
		information.select = atoi(msg);
		A5_1(msg, Key_server);
		F_Send(server_sock, msg);

		alert = Menu_1_Action(client_sock, server_sock, &information);
		if (alert == -1)
			return;
	} while (alert);

}
