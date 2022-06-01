#include "Server_PFS.h"

int Server_PFS(SOCKET client_sock, KEY k, int *key)
{
	srand(time(NULL));

	char msg[BUFSIZE];
	int Nonce_C, Nonce_S, mul;
	ARRAY_OVERFLOW arr;
	point x = { 2, 7 };
	mul = rand() % 10 + 1;

	Set_ECC(11, 19, 167, x);
	Nonce_S = rand() % 987456 + 123456;


	if(F_Recv(client_sock, msg) == -1) return -1;
	Nonce_C = atoi(msg);


	x = Perfect_P(x, mul, PUBLIC_POINT);
	sprintf(msg, "%d,%d,%d", Nonce_C, x.x, x.y);
	char buf[BUFSIZE];


	Enc_Sign(msg, buf, k, &arr);
	int len = strlen(msg);
	for (int i = 0; i < len; i++)
	{
		msg[i] = (arr.array_overflow[0][i] + 48);
	}
	F_Send(client_sock, msg);
	for (int i = 0; i < len; i++)
	{
		msg[i] = (arr.array_overflow[1][i] + 48);
	}
	F_Send(client_sock, msg);

	for (int i = 0; i < len; i++)
	{
		msg[i] = (arr.array_overflow[2][i] + 48);
	}
	F_Send(client_sock, msg);

	F_Send(client_sock, buf);


	sprintf(msg, "%d", Nonce_S);
	F_Send(client_sock, msg);

	if (F_Recv(client_sock, msg) == -1) return -1;
	for (int i = 0; i < BUFSIZE; i++)
	{
		arr.array_overflow[0][i] = msg[i] - 48;
	}
	if (F_Recv(client_sock, msg) == -1) return -1;
	for (int i = 0; i < BUFSIZE; i++)
	{
		arr.array_overflow[1][i] = msg[i] - 48;
	}
	if (F_Recv(client_sock, msg) == -1) return -1;
	for (int i = 0; i < BUFSIZE; i++)
	{
		arr.array_overflow[2][i] = msg[i] - 48;
	}
	if (F_Recv(client_sock, msg) == -1) return -1;
	Sign_Dec(msg, buf, k, &arr);

	int i = 0, j = 0;
	char data1[20];
	char data2[5];
	char data3[5];

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

	if (Nonce_S != atoi(data1))
	{
		printf("인증 오류! Nonce 불일치! \n");
		exit(1);
	}

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