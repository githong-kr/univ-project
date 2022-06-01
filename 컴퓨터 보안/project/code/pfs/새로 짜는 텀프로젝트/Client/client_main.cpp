#include "client.h"

FILE* fp;

int main()
{
	SOCKET sock;
	int select;
	char msg[BUFSIZE];
	char log[BUFSIZE];
	INFO information;
	KEY k;
	
	system("title Client");
	FILE *fp;


	int Key[BUFSIZE];
/*
	Key_Gender_A5_1(Key);									// A5_1
	printf("Key Stream : ");
	for (int i = 0; i < BUFSIZE; i++)
		printf("%d", Key[i]);
	puts(""); puts("");
	strcpy(msg, "Hi, my name is Bob."); // 평문
	printf("PlainText : %s \n\n", msg);
	A5_1(msg, Key);						// 암호화
	printf("CipherText : %s \n\n", msg);
	A5_1(msg, Key);						// 복호화
	printf("Decrypted Message : %s \n\n", msg);
*/
/*
	Key_Gender_Feistel(Key);								// Feistel
	printf("Key Stream : ");
	for (int i = 0; i < 4; i++)
		printf("%d ", Key[i]);
	puts(""); puts("");
	strcpy(msg, "Hi, my name is Bob."); // 평문
	printf("PlainText : %s \n\n", msg);
	Feistel(msg, Key, ENC);				// 암호화
	printf("CipherText : %s \n\n", msg);
	Feistel(msg, Key, DEC);				// 암호화
	printf("Decrypted Message : %s \n\n", msg);
*/
/*
	int public_key, private_key;							// RSA

	Key_Gender_RSA(&public_key, &private_key);
	printf("Public Key  : %d\n", public_key);
	printf("Private Key : %d\n", private_key);
	puts("");
	strcpy(msg, "Hi, my name is Bob."); // 평문
	printf("PlainText : %s \n\n", msg);
	rsa_enc(msg, public_key);			// 암호화
	printf("CipherText : %s \n\n", msg);
	rsa_dec(msg, private_key);			// 암호화
	printf("Decrypted Message : %s \n\n", msg);
	Sleep(65481651);
*/
/*
	strcpy(msg, "HongGilDong");
	printf("Plain Text : %s\n", msg);
	SHA256_Encrpyt((BYTE*)msg, strlen(msg), (BYTE*)log);	// SHA256
	printf("Hashed Text : %s\n\n", log);

	memset(log, 0, sizeof(log));
	sprintf(msg, "Password");
	printf("Plain Text : %s\n", msg);
	SHA256_Encrpyt((BYTE*)msg, strlen(msg), (BYTE*)log);
	printf("Hashed Text : %s\n\n", log);

	Sleep(6546841);
*/
	
	sock = Make_Client(RELAY_PORT, "127.0.0.1");			// 로컬 RELAY_PORT로 접속

/*
	int Alice_Exponent = 15;								// ECC
	int Symmetric_Key[BUFSIZE];
	
	Key_Gender_ECC(sock, Symmetric_Key, Alice_Exponent);

	printf("Symmetric_Key : ");
	for (int i = 0; i < BUFSIZE; i++)
		printf("%d", Symmetric_Key[i]);
	puts("");

	Sleep(6546841);
*/

	Key_Exchange_RSA(sock, &k);

	cout << "Public : " << k.Public_key << " Private : " << k.Private_key << " your Public : " << k.your_Public_key << endl;

	int key1[BUFSIZE];
	if(Client_PFS(sock, k, key1) == -1) return -1;

	for (int i = 0; i < 30; i++)
	{
		printf("%d", key1[i]);
	}
	puts("");

	if (Client_PFS(sock, k, key1) == -1) return -1;

	for (int i = 0; i < 30; i++)
	{
		printf("%d", key1[i]);
	}
	puts("");

	//Sleep(651685168);

	do
	{
		select = Menu_1();

		fp = fopen("Log_Client.txt", "a");
		Menu_1_Log(log, select);
		Write_Log(fp, log);
		fclose(fp);

		sprintf(msg, "%d", select);
		F_Send(sock, msg);

	} while (Menu_1_Action(sock, select, &information));

		
	return 0;
}

