#include "relay.h"

int View(SOCKET client_sock, SOCKET server_sock)
{
	char buf[BUFSIZE];
	char name[BUFSIZE];
	long money;

	if (F_Recv(server_sock, buf) == -1) return -1;
	strcpy(name, buf);
	if (F_Recv(server_sock, buf) == -1) return -1;
	money = atol(buf);

	INFO information;
	information.select = 3;
	strcpy(information.name, name);
	information.money = money;

	StoC = fopen("StoC.txt", "w");
	Write_Data(StoC, information);
	fclose(StoC);

	StoC = fopen("StoC.txt", "r");
	Read_Data(StoC, &information);
	fclose(StoC);

	F_Send(client_sock, information.name);
	sprintf(buf, "%ld", information.money);
	F_Send(client_sock, buf);
}

int Menu_2_Action(SOCKET client_sock, SOCKET server_sock, int select, INFO* information)			// 선택값을 매개변수로 받아 취할 행동 정함
{
	char buf[BUFSIZE];

	if (select == 1)
	{
		//조회
		View(client_sock, server_sock);

	}
	else if (select == 2)
	{
		//입금
		if (F_Recv(client_sock, buf) == -1) return -1;
		F_Send(server_sock, buf);

		View(client_sock, server_sock);
	}
	else if (select == 3)
	{
		//출금
		if (F_Recv(client_sock, buf) == -1) return -1;
		F_Send(server_sock, buf);

		View(client_sock, server_sock);
	}
	else if (select == 4)
	{
		return false;
	}

	return true;
}

int Login(SOCKET client_sock, SOCKET server_sock, INFO* information)
{
	char buf[BUFSIZE];
	int alert;

	if (F_Recv(client_sock, information->id) == -1) return -1;
	if (F_Recv(client_sock, information->pw) == -1) return -1;

	CtoS = fopen("CtoS.txt", "w");
	Write_Data(CtoS, *information);
	fclose(CtoS);

	// 데이터 변조 테스트 하려면
	// Sleep(1000*30)

	CtoS = fopen("CtoS.txt", "r");
	Read_Data(CtoS, information);
	fclose(CtoS);

	F_Send(server_sock, information->id);
	F_Send(server_sock, information->pw);

	if (F_Recv(server_sock, buf) == -1) return -1;
	F_Send(client_sock, buf);
	if (F_Recv(server_sock, buf) == -1) return -1;
	F_Send(client_sock, buf);

	if (atoi(buf) == 1)
	{
		int select;

		do
		{
			if (F_Recv(client_sock, buf) == -1) return -1;
			select = atoi(buf);
			F_Send(server_sock, buf);

			alert = Menu_2_Action(client_sock, server_sock, select, information);
			if (alert == -1)
				return -1;
		} while (alert);
	}
}

int Register(SOCKET client_sock, SOCKET server_sock, INFO* information)
{
	char buf[BUFSIZE];

	if (F_Recv(client_sock, information->id) == -1) return -1;
	if (F_Recv(client_sock, information->pw) == -1) return -1;
	if (F_Recv(client_sock, information->name) == -1) return -1;
	information->money = 0;

	CtoS = fopen("CtoS.txt", "w");
	Write_Data(CtoS, *information);
	fclose(CtoS);

	// 데이터 변조 테스트 하려면
	// Sleep(1000*30)

	CtoS = fopen("CtoS.txt", "r");
	Read_Data(CtoS, information);
	fclose(CtoS);

	F_Send(server_sock, information->id);
	F_Send(server_sock, information->pw);
	F_Send(server_sock, information->name);
	sprintf(buf, "%ld", information->money);
	F_Send(server_sock, buf);

	if (F_Recv(server_sock, buf) == -1) return -1;
	F_Send(client_sock, buf);
}

int Menu_1_Action(SOCKET client_sock, SOCKET server_sock, INFO* information)			// 선택값을 매개변수로 받아 취할 행동 정함
{
	int alert;

	if (information->select == 1)
	{
		alert = Login(client_sock, server_sock, information);
		if (alert == -1)
			return -1;
	}
	else if (information->select == 2)
	{
		alert = Register(client_sock, server_sock, information);
		if (alert == -1)
			return -1;
	}

	else if (information->select == 3)
	{
		system("del .\\CtoS.txt");
		system("del .\\StoC.txt");
	}

	return true;
}

int Key_Exchange(SOCKET client_sock, SOCKET server_sock)
{ // 키 교환 돕기
	char server_msg[2][BUFSIZE], client_msg[2][BUFSIZE];
	char msg[BUFSIZE];

	if (F_Recv(client_sock, msg) == -1) return -1;
	strcpy(client_msg[0], msg);
	if (F_Recv(client_sock, msg) == -1) return -1;
	strcpy(client_msg[1], msg);

	if (F_Recv(server_sock, msg) == -1) return -1;
	strcpy(server_msg[0], msg);
	if (F_Recv(server_sock, msg) == -1) return -1;
	strcpy(server_msg[1], msg);

	F_Send(client_sock, server_msg[0]);
	F_Send(client_sock, server_msg[1]);

	F_Send(server_sock, client_msg[0]);
	F_Send(server_sock, client_msg[1]);
}

int Generate_Session_Key(SOCKET client_sock, SOCKET server_sock)
{ // 세션키 만들기 돕기
	
	char msg[BUFSIZE];

	if (F_Recv(client_sock, msg) == -1) return -1;
	F_Send(server_sock, msg);

	if (F_Recv(server_sock, msg) == -1) return -1;
	F_Send(client_sock, msg);
	if (F_Recv(server_sock, msg) == -1) return -1;
	F_Send(client_sock, msg);
	if (F_Recv(server_sock, msg) == -1) return -1;
	F_Send(client_sock, msg);
	if (F_Recv(server_sock, msg) == -1) return -1;
	F_Send(client_sock, msg);

	if (F_Recv(server_sock, msg) == -1) return -1;
	F_Send(client_sock, msg);

	if (F_Recv(client_sock, msg) == -1) return -1;
	F_Send(server_sock, msg);
	if (F_Recv(client_sock, msg) == -1) return -1;
	F_Send(server_sock, msg);
	if (F_Recv(client_sock, msg) == -1) return -1;
	F_Send(server_sock, msg);
	if (F_Recv(client_sock, msg) == -1) return -1;
	F_Send(server_sock, msg);


}