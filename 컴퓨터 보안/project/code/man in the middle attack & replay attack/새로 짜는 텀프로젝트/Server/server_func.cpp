#include "server.h"


void Init_List(List* myList)
{
	myList->head = NULL;
	myList->cur = NULL;
	myList->tail = NULL;
	myList->length = 0;
}
void Add_List(List* myList, INFO information)
{
	Node *new_node = (Node*)malloc(sizeof(Node));

	strcpy(new_node->id, information.id);
	strcpy(new_node->pw, information.pw);
	strcpy(new_node->name, information.name);
	new_node->money = information.money;
	new_node->rLink = NULL;

	if (myList->head == NULL)
	{
		myList->head = new_node;
		myList->tail = new_node;
	}
	else
	{
		myList->tail->rLink = new_node;
		myList->tail = myList->tail->rLink;
	}

	myList->length++;
}
void Make_List(List* myList)
{
	fp = fopen("Database.txt", "rb");
	char buf[BUFSIZE];
	if (fp == NULL)
	{
		fp = fopen("Database.txt", "w");
		fclose(fp);
		return;
	}

	
	INFO tmp;
	char money[BUFSIZE];
	while(!feof(fp))
	{
		tmp.money = atol(money);
		fscanf(fp, "%s\t%s\t%s\t%ld\n", tmp.id, tmp.pw, tmp.name, &tmp.money);
//		printf("makelist\nID : %s \n", tmp.id);
//		printf("PW : %s \n", tmp.pw);
		Add_List(myList, tmp);
	}
	fclose(fp);
}
void Make_File(List* myList)
{
	fp = fopen("Database.txt", "w");
	myList->tail = myList->head;

	Node tmp;
	char money[BUFSIZE];

	for (int i = 0; i < myList->length; i++)
	{
		strcpy(tmp.id, myList->tail->id);
		strcpy(tmp.pw, myList->tail->pw);
		strcpy(tmp.name, myList->tail->name);
		tmp.money = myList->tail->money;

//		printf("makefile\nID : %s \n", tmp.id);
//		printf("PW : %s \n", tmp.pw);

		fprintf(fp, "%s\t%s\t%s\t%ld\n",tmp.id, tmp.pw, tmp.name, tmp.money);
		myList->tail = myList->tail->rLink;
	}
	fclose(fp);
}
int Check_id(List *myList, INFO info)
{
	myList->cur = myList->head;

	for (int i = 0; i < myList->length; i++)
	{
		if (!strcmp(myList->cur->id, info.id))
			return false;
		myList->cur = myList->cur->rLink;
	}

	return true;
}

void View(SOCKET client_sock, INFO information)
{
	char buf[BUFSIZE];

	A5_1(information.name, Key);
	F_Send(client_sock, information.name);
	sprintf(buf, "%ld", information.money);
	A5_1(buf, Key);
	F_Send(client_sock, buf);
}
int Menu_1_Action(SOCKET client_sock, int select, INFO* information, List *myList)			// 선택값을 매개변수로 받아 취할 행동 정함
{
	char buf[BUFSIZE];
	int alert;
	if (select == 1)
	{
		alert = Login(client_sock, select, information, myList);
		if (alert == -1)
			return -1;
	}
	else if (select == 2)
	{
		alert = Register(client_sock, select, information, myList);
		if (alert == -1)
			return -1;
	}

	return true;
}

int Menu_2_Action(SOCKET client_sock, int select, INFO* information)			// 선택값을 매개변수로 받아 취할 행동 정함
{
	char buf[BUFSIZE];

	if (select == 1)
	{
		//조회
		View(client_sock, *information);

	}
	else if (select == 2)
	{
		//입금
		if (F_Recv(client_sock, buf) == -1) return -1;
		A5_1(buf, Key);

		information->money += atol(buf);

		View(client_sock, *information);

	}
	else if (select == 3)
	{
		//출금
		if (F_Recv(client_sock, buf) == -1) return -1;
		A5_1(buf, Key);

		information->money -= atol(buf);

		View(client_sock, *information);
	}
	else if (select == 4)
	{
		return false;
	}

	return true;
}

int Login(SOCKET client_sock, int select, INFO* information, List *myList)
{
	char buf[BUFSIZE];
	int alert;
	INFO tmp;
	
	srand(time(NULL));
	int Nonce_S = 19; // rand() % 100;
	sprintf(buf, "%d", Nonce_S);
	printf("NONCE_S = %d \n", Nonce_S);
	F_Send(client_sock, buf);

	if (F_Recv(client_sock, information->id) == -1) return -1;
	A5_1(information->id, Key);
	if (F_Recv(client_sock, information->pw) == -1) return -1;
	printf("수신 데이터 : %s \n", information->pw);

	A5_1(information->pw, Key);
	printf("복호화 데이터 : %s \n", information->pw);


	int index;
	for (index = 0; index < BUFSIZE; index++)
	{
		if (information->pw[index] == ',')
			break;
	}
	char cmp[BUFSIZE];
	int cmp_index = 0;
	for (int i = index+1; i < BUFSIZE; i++)
	{
		if (information->pw[i] == '\0')
		{
			break;
		}
		cmp[cmp_index++] = information->pw[i];
	}
	if (Nonce_S != atoi(cmp))
	{
		printf("인증 실패! NONCE가 다름 \n");
		sprintf(buf, "-1");
		F_Send(client_sock, buf);
		return -1;
	}

	information->pw[index] = '\0';
	memcpy(information->pw, information->pw, index);

	printf("PW : %s\nNonce_S : %d \n\n", information->pw, atoi(cmp));

//	if (F_Recv(client_sock, tmp.id) == -1) return -1;
//	if (F_Recv(client_sock, tmp.pw) == -1) return -1;
/*
	memset(information->id, 0, BUFSIZE);
	memset(information->pw, 0, BUFSIZE);
	SHA256_Encrpyt((BYTE*)tmp.id, strlen(tmp.id), (BYTE*)information->id);
	SHA256_Encrpyt((BYTE*)tmp.pw, strlen(tmp.pw), (BYTE*)information->pw);
	Remove_Tab(information->id);
	Remove_Tab(information->pw);
*/
	if (!Check_id(myList, *information))
	{
//		printf("login\nID : %s \n", information->id);
//		printf("PW : %s \n", information->pw);

		if (!strcmp(myList->cur->pw, information->pw))
		{
			sprintf(buf, "로그인 성공\n");
			A5_1(buf, Key);
			F_Send(client_sock, buf);
			sprintf(buf, "1");
			A5_1(buf, Key);
			F_Send(client_sock, buf);

			INFO Client;
			strcpy(Client.name, myList->cur->name);
			Client.money = myList->cur->money;
			do
			{
				myList->cur->money = Client.money;
				if (F_Recv(client_sock, buf) == -1) return -1;
				A5_1(buf, Key);
				select = atoi(buf);
				Make_File(myList);

				alert = Menu_2_Action(client_sock, select, &Client);
				if (alert == -1)
					return -1;
			} while (alert);

		}
		else
		{
			sprintf(buf, "비밀번호 불일치\n");
			A5_1(buf, Key);
			F_Send(client_sock, buf);
			sprintf(buf, "0");
			A5_1(buf, Key);
			F_Send(client_sock, buf);
		}
	}
	else
	{
		sprintf(buf, "아이디 불일치\n");
		A5_1(buf, Key);
		F_Send(client_sock, buf);
		sprintf(buf, "0");
		A5_1(buf, Key);
		F_Send(client_sock, buf);
	}
}

int Register(SOCKET client_sock, int select, INFO* information, List *myList)
{
	char buf[BUFSIZE];
	INFO tmp;

	if (F_Recv(client_sock, information->id) == -1) return -1;
	A5_1(information->id, Key);
	if (F_Recv(client_sock, information->pw) == -1) return -1;
	A5_1(information->pw, Key);
//	if (F_Recv(client_sock, tmp.id) == -1) return -1;
//	if (F_Recv(client_sock, tmp.pw) == -1) return -1;
	if (F_Recv(client_sock, information->name) == -1) return -1;
	A5_1(information->name, Key);
	if (F_Recv(client_sock, buf) == -1) return -1;
	A5_1(buf, Key);
	long money = atol(buf);
	information->money = money;
	information->select = select;
/*
	memset(information->id, 0, BUFSIZE);
	memset(information->pw, 0, BUFSIZE);
	SHA256_Encrpyt((BYTE*)tmp.id, strlen(tmp.id), (BYTE*)information->id);
	SHA256_Encrpyt((BYTE*)tmp.pw, strlen(tmp.pw), (BYTE*)information->pw);
	Remove_Tab(information->id);
	Remove_Tab(information->pw);
*/	
//	printf("register\nID : %s \n", information->id);
//	printf("PW : %s \n", information->pw);
	if (Check_id(myList, *information))
	{
		Add_List(myList, *information);
		sprintf(buf, "등록 성공\n");
		A5_1(buf, Key);
		F_Send(client_sock, buf);
		Make_File(myList);
	}
	else
	{
		sprintf(buf, "아이디 중복\n");
		A5_1(buf, Key);
		F_Send(client_sock, buf);
	}
}

void Remove_Tab(char *msg)
{
	int i;

	for (i = 0; i < strlen(msg); i++)
	{
		if (msg[i] == '\t' || msg[i] == '\0')
			msg[i] = '?';
	}
}