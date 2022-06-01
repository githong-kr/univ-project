#include "relay.h"

FILE* CtoS;
FILE* StoC;


int main()
{

	SOCKET listen_sock;
	listen_sock = Make_Server(RELAY_PORT);			// Ŭ���̾�Ʈ�� ������ ������ ������ ����
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

		printf("\n[TCP ����] Ŭ���̾�Ʈ ���� : IP�ּ�=%s, ��Ʈ��ȣ=%d \n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

		_beginthread((_beginthread_proc_type)Thread_Proc, 0, (void*)client_sock);
	}



	return 0;
}



void Thread_Proc(void* sock)
{
	SOCKET client_sock = (SOCKET)sock;
	KEY k;

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

	char msg[BUFSIZE];
	int select;

	CtoS = fopen("CtoS.txt", "a");
	StoC = fopen("StoC.txt", "a");
	fclose(CtoS);
	fclose(StoC);

	SOCKET server_sock;
	server_sock = Make_Client(SERVER_PORT, "127.0.0.1");			// ������ �����ϴ� Ŭ���̾�Ʈ ���� ����
									
	// ���� ����� client_sock => Ŭ���̾�Ʈ  server_sock => ����

	Key_Exchange(client_sock, server_sock);

	Generate_Session_Key(client_sock, server_sock);

	Generate_Session_Key(client_sock, server_sock);




	INFO information;
	int alert;
	do
	{
		if (F_Recv(client_sock, msg) == -1) return;
		information.select = atoi(msg);
		F_Send(server_sock, msg);

		alert = Menu_1_Action(client_sock, server_sock, &information);
		if (alert == -1)
			return;
	} while (alert);

}
