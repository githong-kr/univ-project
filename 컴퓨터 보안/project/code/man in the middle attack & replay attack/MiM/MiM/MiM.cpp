#include <Make_Server.h>
#pragma comment(lib, "DLL.lib")

int main()
{

	SOCKET listen_sock;
	listen_sock = Make_Server(10000);			// 클라이언트가 접속할 릴레이 서버를 만듦
	SOCKET client_sock;
	SOCKADDR_IN clientaddr;
	int addrlen;


	
	
	addrlen = sizeof(clientaddr);
	client_sock = accept(listen_sock, (SOCKADDR*)&clientaddr, &addrlen);
	if (client_sock == INVALID_SOCKET)
	{
		printf("Accept Fail! \n");
	}

	printf("\n[TCP 서버] 클라이언트 접속 : IP주소=%s, 포트번호=%d \n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

	INFO *information = (INFO *)malloc(sizeof(INFO));

	char buf[BUFSIZE];
	
	printf("Nonce 입력 : ");
	scanf("%s", buf);
	F_Send(client_sock, buf);

	if (F_Recv(client_sock, information->id) == -1) return -1;
	if (F_Recv(client_sock, information->pw) == -1) return -1;

	printf("Encrypted Bob's ID ; %s\nEncrypted Bob's PW : %s \n", information->id, information->pw);

	closesocket(client_sock);
	free(information);

	return 0;
}