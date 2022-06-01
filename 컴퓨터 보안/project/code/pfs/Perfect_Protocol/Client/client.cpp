#include "client.h"

int main()
{
	system("title Client");


	Sleep(1000);
	SOCKET server_sock;
	char msg[BUFSIZE];
	int Nonce_C, Nonce_S, mul;
	KEY k;
	ARRAY_OVERFLOW arr;
	point x = { 2, 7 };
	mul = rand() % 10 + 1;

	Set_ECC(11, 19, 167, x);



	k.my_n = Key_Gender_RSA(&k.Public_key, &k.Private_key);
	cout << "Public : " << k.Public_key << " Private : " << k.Private_key << "\n\n";

	server_sock = Make_Client(SERVER_PORT, "127.0.0.1");

	strcpy(msg, bigUnsignedToString(k.Public_key).c_str());
	F_Send(server_sock, msg);

	strcpy(msg, bigUnsignedToString(k.my_n).c_str());
	F_Send(server_sock, msg);

	F_Recv(server_sock, msg);
	k.your_Public_key = stringToBigUnsigned(msg);
	F_Recv(server_sock, msg);
	k.your_n = stringToBigUnsigned(msg);

	cout << "Server's Public Key: " << k.your_Public_key << "\n";
	cout << "Server's N : " << k.your_n << "\n";


	srand(time(NULL));
	Nonce_C = rand() % 12345;
	printf("Nonce_C : %d \n", Nonce_C);
	sprintf(msg, "%d", Nonce_C);
	F_Send(server_sock, msg);

	
	F_Recv(server_sock, msg);
	for (int i = 0; i < BUFSIZE; i++)
	{
		arr.array_overflow[0][i] = msg[i] - 48;
	}
	F_Recv(server_sock, msg);
	for (int i = 0; i < BUFSIZE; i++)
	{
		arr.array_overflow[1][i] = msg[i] - 48;
	}
	F_Recv(server_sock, msg);
	for (int i = 0; i < BUFSIZE; i++)
	{
		arr.array_overflow[2][i] = msg[i] - 48;
	}
	F_Recv(server_sock, msg);
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

	
	F_Recv(server_sock, msg);
	Nonce_S = atoi(msg);
	printf("\n\nNonce_S : %d", Nonce_S);

	x = Perfect_P(x, mul, PUBLIC_POINT);

	sprintf(msg, "%d,%d,%d", Nonce_S, x.x, x.y);
	printf("평문\n");
	printf("%s ", msg);

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

	printf("%d , %d\n", result.x, result.y);

	puts("");
	return 0;
}