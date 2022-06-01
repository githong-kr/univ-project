#include "server.h"

int main()
{
	system("title Server");

	srand(time(NULL));

	SOCKET listen_sock, client_sock;
	listen_sock = Make_Server(SERVER_PORT);
	SOCKADDR_IN clientaddr;
	int addrlen;
	char msg[BUFSIZE];
	int Nonce_C, Nonce_S, mul;
	KEY k;
	ARRAY_OVERFLOW arr;
	point x = {2, 7};
	mul = rand() % 10 + 1;

	Set_ECC(11, 19, 167, x);
	Nonce_S = rand() % 987456 + 123456;
	
	k.my_n = Key_Gender_RSA(&k.Public_key, &k.Private_key);



	addrlen = sizeof(clientaddr);
	client_sock = accept(listen_sock, (SOCKADDR*)&clientaddr, &addrlen);
	if (client_sock == INVALID_SOCKET)
		printf("Accept Fail! \n");
	
	
	printf("\n[TCP 서버] 클라이언트 접속 : IP주소=%s, 포트번호=%d \n\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

	cout << "Public : " << k.Public_key << " Private : " << k.Private_key << "\n\n";


	F_Recv(client_sock, msg);
	k.your_Public_key = stringToBigUnsigned(msg);

	F_Recv(client_sock, msg);
	k.your_n = stringToBigUnsigned(msg);
	cout << "Client's Public Key : " << k.your_Public_key << "\n";
	cout << "Client's N : " << k.your_n << "\n";


	strcpy(msg, bigUnsignedToString(k.Public_key).c_str());
	F_Send(client_sock, msg);
	strcpy(msg, bigUnsignedToString(k.my_n).c_str());
	F_Send(client_sock, msg);


	F_Recv(client_sock, msg);
	Nonce_C = atoi(msg);
	printf("Nonce_S : %d \n", Nonce_S);
	printf("\nNonce_C : %d", Nonce_C);


	x = Perfect_P(x, mul, PUBLIC_POINT);
	sprintf(msg, "%d,%d,%d", Nonce_C, x.x, x.y);
	printf("평문\n");
	printf("%s ", msg);
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

	F_Recv(client_sock, msg);
	for (int i = 0; i < BUFSIZE; i++)
	{
		arr.array_overflow[0][i] = msg[i] - 48;
	}
	F_Recv(client_sock, msg);
	for (int i = 0; i < BUFSIZE; i++)
	{
		arr.array_overflow[1][i] = msg[i] - 48;
	}
	F_Recv(client_sock, msg);
	for (int i = 0; i < BUFSIZE; i++)
	{
		arr.array_overflow[2][i] = msg[i] - 48;
	}
	F_Recv(client_sock, msg);
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

	printf("%d , %d\n", result.x, result.y);


	puts("");
	return 0;
}