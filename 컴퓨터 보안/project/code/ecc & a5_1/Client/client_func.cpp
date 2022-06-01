#include "client.h"

int Menu_1()			// 메뉴를 선택받고 선택값 반환
{
	int select;

	system("cls");
	printf("1. 로그인 \n");
	printf("2. 등록 \n");
	printf("3. 종료 \n");
	printf("기능 선택: ");
	scanf("%d", &select);

	return select;
}

int Menu_2()
{
	int select;

	system("cls");
	printf("1. 잔액 조회 \n");
	printf("2. 입금 \n");
	printf("3. 출금 \n");
	printf("4. 로그아웃 \n");
	printf("기능 선택: ");
	scanf("%d", &select);

	return select;
}

void View(SOCKET sock, INFO* information)
{
	char buf[BUFSIZE];
	char name[BUFSIZE];
	system("cls");

	F_Recv(sock, buf);
	A5_1(buf, Key);
	strcpy(name, buf);
	F_Recv(sock, buf);
	A5_1(buf, Key);

	information->money = atol(buf);

	printf("%s님의 계좌 잔액은 %s원입니다. \n", name, buf);
	printf("\n돌아가시려면 아무 키나 누르세요. \n");
	getch();
}

void Deposit(SOCKET sock, int select, INFO* information)
{
	long money;
	char buf[BUFSIZE];

	system("cls");

	while (1)
	{
		printf("입금할 금액을 입력하세요 : ");
		scanf("%ld", &money);
		if (money <= 0)
		{
			printf("\n잘못입력하셨습니다. \n");
			Sleep(500);
			system("cls");
		}
		else
			break;
	}

	sprintf(buf, "%ld", money);
	A5_1(buf, Key);
	F_Send(sock, buf);

	View(sock, information);
}

void Withdraw(SOCKET sock, int select, INFO* information)
{
	long money;
	char buf[BUFSIZE];

	system("cls");

	while (1)
	{
		printf("출금할 금액을 입력하세요 : ");
		scanf("%ld", &money);

		if (information->money < money)
		{
			printf("\n잘못입력하셨습니다. \n");
			Sleep(500);
			system("cls");
		}
		else
			break;
	}
	sprintf(buf, "%ld", money);
	A5_1(buf, Key);
	F_Send(sock, buf);

	View(sock, information);
}

int Menu_2_Action(SOCKET sock, int select, INFO* information)			// 선택값을 매개변수로 받아 취할 행동 정함
{
	char buf[BUFSIZE];

	if (select == 1)
	{
		//조회
		View(sock, information);
	}
	else if (select == 2)
	{
		//입금
		Deposit(sock, select, information);
	}
	else if (select == 3)
	{
		//출금
		Withdraw(sock, select, information);
	}
	else if (select == 4)
	{
		printf("\n로그아웃 되었습니다.");
		Sleep(500);
		return false;
	}
	else
	{
		printf("\n다시 입력하십시오");
		Sleep(500);
	}

	return true;
}


int Menu_1_Action(SOCKET sock, int select, INFO* information)			// 선택값을 매개변수로 받아 취할 행동 정함
{
	if (select == 1)
	{
		Login(sock, select, information);
	}
	else if (select == 2)
	{
		Register(sock, select, information);
	}
	else if (select == 3)
	{
		system("del .\\Log_Client.txt");
		exit(1);
	}
	else
	{
		printf("\n다시 입력하십시오");
		Sleep(500);
	}

	return true;
}


void Register(SOCKET sock, int select, INFO* information)
{
	char buf[BUFSIZE];

	system("cls");
	
	printf("등록 화면입니다. \n\n");
	printf("아이디 : ");
	scanf("%s", information->id);
	printf("비밀번호 : ");
	PW_scanf(information->pw);
	printf("이름 : ");
	scanf("%s", information->name);

	fp = fopen("Log_Client.txt", "a");
	char log[BUFSIZE];
	sprintf(log, "등록\nid:%s\npw:%s\nname:%s\n", information->id, information->pw, information->name);
	Write_Log(fp, log);
	fclose(fp);

	A5_1(information->id, Key);
	F_Send(sock, information->id);
	A5_1(information->pw, Key);
	F_Send(sock, information->pw);
	A5_1(information->name, Key);
	F_Send(sock, information->name);
	
	F_Recv(sock, buf);
	A5_1(buf, Key);
	printf("%s", buf);
	fp = fopen("Log_Client.txt", "a");
	Write_Log(fp, buf);
	fclose(fp);
	Sleep(500);
	
}

void Login(SOCKET sock, int select, INFO* information)
{
	char buf[BUFSIZE];

	system("cls");

	printf("로그인 화면입니다. \n\n");
	printf("아이디 : ");
	scanf("%s", information->id);
	printf("비밀번호 : ");
	PW_scanf(information->pw);

	fp = fopen("Log_Client.txt", "a");
	char log[BUFSIZE];
	sprintf(log, "로그인\nid:%s\npw:%s\n", information->id, information->pw);
	Write_Log(fp, log);
	fclose(fp);

	A5_1(information->id, Key);
	F_Send(sock, information->id);
	A5_1(information->pw, Key);
	F_Send(sock, information->pw);

	F_Recv(sock, buf);			// 로그인 결과 수신
	A5_1(buf, Key);
	printf("%s", buf);
	fp = fopen("Log_Client.txt", "a");
	Write_Log(fp, buf);
	Sleep(500);
	fclose(fp);

	F_Recv(sock, buf);
	A5_1(buf, Key);
	int Login_result = atoi(buf);

	if (Login_result == 1)
	{
		int select;

		do
		{
			select = Menu_2();

			fp = fopen("Log_Client.txt", "a");
			Menu_2_Log(log, select);
			Write_Log(fp, log);
			fclose(fp);

			sprintf(buf, "%d", select);
			A5_1(buf, Key);
			F_Send(sock, buf);

		} while (Menu_2_Action(sock, select, information));

	}

}