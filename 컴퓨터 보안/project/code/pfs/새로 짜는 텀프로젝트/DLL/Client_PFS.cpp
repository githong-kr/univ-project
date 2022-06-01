#include "Client_PFS.h"


int Client_PFS(SOCKET server_sock, KEY k, int *key)
{

	Sleep(1000);
	char msg[BUFSIZE];
	int Nonce_C, Nonce_S, mul;
	int alert;
	ARRAY_OVERFLOW arr;
	point x = { 2, 7 };
	mul = rand() % 10 + 1;

	Set_ECC(11, 19, 167, x);


	srand(time(NULL));
	Nonce_C = rand() % 12345;
	sprintf(msg, "%d", Nonce_C);
	F_Send(server_sock, msg);


	if(F_Recv(server_sock, msg) == -1) return -1;
	for (int i = 0; i < BUFSIZE; i++)
	{
		arr.array_overflow[0][i] = msg[i] - 48;
	}
	if (F_Recv(server_sock, msg) == -1) return -1;
	for (int i = 0; i < BUFSIZE; i++)
	{
		arr.array_overflow[1][i] = msg[i] - 48;
	}
	if (F_Recv(server_sock, msg) == -1) return -1;
	for (int i = 0; i < BUFSIZE; i++)
	{
		arr.array_overflow[2][i] = msg[i] - 48;
	}
	if (F_Recv(server_sock, msg) == -1) return -1;
	char buf[BUFSIZE];
	Sign_Dec(msg, buf, k, &arr);

	int i = 0, j = 0;
	char data1[20];
	char data2[10];
	char data3[10];
	while (buf[j] != ',')
	{
		data1[i++] = buf[j++];
	}
	data1[i] = '\0';
	i = 0;
	j++;
	while (buf[j] != ',')
	{
		data2[i++] = buf[j++];
	}
	data2[i] = '\0';
	i = 0;
	j++;
	while (buf[j] != '\0')
	{
		data3[i++] = buf[j++];
	}
	data3[i] = '\0';


	if (Nonce_C != atoi(data1))
	{
		printf("인증 오류! Nonce 불일치! \n");
		exit(1);
	}


	if (F_Recv(server_sock, msg) == -1) return -1;
	Nonce_S = atoi(msg);

	x = Perfect_P(x, mul, PUBLIC_POINT);

	sprintf(msg, "%d,%d,%d", Nonce_S, x.x, x.y);

	memset(arr.array_overflow, 0, sizeof(int)*BUFSIZE);

	Enc_Sign(msg, buf, k, &arr);
	int len = strlen(msg);
	for (int i = 0; i < len; i++)
	{
		msg[i] = (arr.array_overflow[0][i] + 48);
	}
	F_Send(server_sock, msg);
	for (int i = 0; i < len; i++)
	{
		msg[i] = (arr.array_overflow[1][i] + 48);
	}
	F_Send(server_sock, msg);
	for (int i = 0; i < len; i++)
	{
		msg[i] = (arr.array_overflow[2][i] + 48);
	}
	F_Send(server_sock, msg);
	F_Send(server_sock, buf);


	point result;

	result.x = atoi(data2); result.y = atoi(data3);
	result = Perfect_P(result, mul, PRIVATE_POINT);

	//printf("%d , %d\n", result.x, result.y);

	srand(result.x + result.y);

	for (int i = 0; i < BUFSIZE; i++)
	{
		key[i] = rand() % 2;
	}

	//puts("");
	return 0;
}