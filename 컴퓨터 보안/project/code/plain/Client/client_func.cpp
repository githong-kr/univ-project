#include "client.h"

int Menu_1()			// �޴��� ���ùް� ���ð� ��ȯ
{
	int select;

	system("cls");
	printf("1. �α��� \n");
	printf("2. ��� \n");
	printf("3. ���� \n");
	printf("��� ����: ");
	scanf("%d", &select);

	return select;
}

int Menu_2()
{
	int select;

	system("cls");
	printf("1. �ܾ� ��ȸ \n");
	printf("2. �Ա� \n");
	printf("3. ��� \n");
	printf("4. �α׾ƿ� \n");
	printf("��� ����: ");
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

	printf("%s���� ���� �ܾ��� %s���Դϴ�. \n", name, buf);
	printf("\n���ư��÷��� �ƹ� Ű�� ��������. \n");
	getch();
}

void Deposit(SOCKET sock, int select, INFO* information)
{
	long money;
	char buf[BUFSIZE];

	system("cls");

	while (1)
	{
		printf("�Ա��� �ݾ��� �Է��ϼ��� : ");
		scanf("%ld", &money);
		if (money <= 0)
		{
			printf("\n�߸��Է��ϼ̽��ϴ�. \n");
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
		printf("����� �ݾ��� �Է��ϼ��� : ");
		scanf("%ld", &money);

		if (information->money < money)
		{
			printf("\n�߸��Է��ϼ̽��ϴ�. \n");
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

int Menu_2_Action(SOCKET sock, int select, INFO* information)			// ���ð��� �Ű������� �޾� ���� �ൿ ����
{
	char buf[BUFSIZE];

	if (select == 1)
	{
		//��ȸ
		View(sock, information);
	}
	else if (select == 2)
	{
		//�Ա�
		Deposit(sock, select, information);
	}
	else if (select == 3)
	{
		//���
		Withdraw(sock, select, information);
	}
	else if (select == 4)
	{
		printf("\n�α׾ƿ� �Ǿ����ϴ�.");
		Sleep(500);
		return false;
	}
	else
	{
		printf("\n�ٽ� �Է��Ͻʽÿ�");
		Sleep(500);
	}

	return true;
}


int Menu_1_Action(SOCKET sock, int select, INFO* information)			// ���ð��� �Ű������� �޾� ���� �ൿ ����
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
		printf("\n�ٽ� �Է��Ͻʽÿ�");
		Sleep(500);
	}

	return true;
}


void Register(SOCKET sock, int select, INFO* information)
{
	char buf[BUFSIZE];

	system("cls");
	
	printf("��� ȭ���Դϴ�. \n\n");
	printf("���̵� : ");
	scanf("%s", information->id);
	printf("��й�ȣ : ");
	PW_scanf(information->pw);
	printf("�̸� : ");
	scanf("%s", information->name);

	fp = fopen("Log_Client.txt", "a");
	char log[BUFSIZE];
	sprintf(log, "���\nid:%s\npw:%s\nname:%s\n", information->id, information->pw, information->name);
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

	printf("�α��� ȭ���Դϴ�. \n\n");
	printf("���̵� : ");
	scanf("%s", information->id);
	printf("��й�ȣ : ");
	PW_scanf(information->pw);

	fp = fopen("Log_Client.txt", "a");
	char log[BUFSIZE];
	sprintf(log, "�α���\nid:%s\npw:%s\n", information->id, information->pw);
	Write_Log(fp, log);
	fclose(fp);

	A5_1(information->id, Key);
	F_Send(sock, information->id);
	A5_1(information->pw, Key);
	F_Send(sock, information->pw);

	F_Recv(sock, buf);			// �α��� ��� ����
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