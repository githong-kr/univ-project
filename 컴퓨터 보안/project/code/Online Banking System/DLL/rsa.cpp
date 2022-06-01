#include "rsa.h"

int n, message_length = 0;

long long mod(long long n, long long e, long long m)// residue = n^e (mod m)�� �����Ѵ�.

{

	long long i, residue = 1;

	for (i = 1; i <= e; i++)

	{

		residue *= n;	//residue=residue*n

		residue %= m;

	}//residue=residue%n �����÷θ� �����ϰ��� mod������ �̿��Ͽ� �ڸ����� ���δ�.

	return residue;

}

int Make_Cypher_text(char Plain_text[BUFSIZE], long long Cyper_text[BUFSIZE], int key)

{

	int i;

	message_length = strlen(Plain_text);

	for (i = 0; i < message_length; i++)	  //�޼��� ���̿� �°� �ݺ��Ѵ�.

		Cyper_text[i] = (long long)mod(Plain_text[i], key, n);  //��ȣȭ

	Cyper_text[i] = '\0';		//���� ǥ��


	return 0;

}

int Make_Plain_text(long long Cyper_text[BUFSIZE], char Plain_text[BUFSIZE], int key)

{

	int  i;

	for (i = 0; i < message_length; i++) // �޼��� ���̿� �°� �ݺ��Ѵ�.

		Plain_text[i] = (char)mod(Cyper_text[i], key, n);	//��ȣȭ

	Plain_text[i] = '\0';	//���� ǥ��

	return 0;

}

int GCD(long long x, long long y)		//�ִ� ����� �˻�

{
	return y == 0 ? x : GCD(y, x % y);
}

int rsa_enc(char *msg, int public_key)
{
	int retval;
	long long encrypt[BUFSIZE];

	char send_msg[BUFSIZE ^ 2] = { 0 };

	Make_Cypher_text(msg, encrypt, public_key);

	memset(msg, 0, sizeof(msg));
	for (int i = 0; i < message_length; i++)
	{
		char temp[BUFSIZE] = { 0 };
		sprintf(temp, "%lld@", encrypt[i]);
		strcat(msg, temp);
	}
	message_length = 0;
	return retval;
}

int rsa_dec(char *msg, int private_key)
{
	int retval;
	long long decrypt[BUFSIZE];

	int j = 0;

	while (msg[j] != '\0')
	{
		if (msg[j] == '@')
			message_length++;
		j++;
	}
	j = 0;
	for (int i = 0; i < message_length; i++)
	{
		char temp[BUFSIZE] = { 0 };
		int k = 0;
		while (msg[j] != '@')
		{
			temp[k] = msg[j];
			j++;
			k++;
		}

		decrypt[i] = atoll(temp);
		j++;
	}

	

	Make_Plain_text(decrypt, msg, private_key);
	message_length = 0;
	return retval;

}

int IsNotPrime(int n)		//�Ҽ��� �ƴ��� �˻�

{

	int  i, limit;

	if (!(n % 2))  return (TRUE);	//¦���̸� �Ҽ��� �ƴϴ�.

	limit = (int)sqrt(n) + 1;	//n����+1�� �Ͽ� ���� ���� �Ҽ��� ã�´�.

	for (i = 3; i <= limit; i += 2) //3���� Ȧ�� ������ ������ ������ �Ѵ�. 

		if (!(n%i))  return (TRUE);

	return (FALSE);

}

long long Make_Random_Prime_Number()// ���� �ڼ�(2��) ������

{

	int i;

	int Prime[2]; // P�� Q �ΰ��� �ڼ��� ����Ű, ���Ű�� �⺻ �Ҽ�

	time_t t;

	srand((unsigned int)time(&t)); //��������

	for (i = 0; i < 2; i++)				// 2���� ������ �ڼ� P�� Q�� �����Ѵ�. 

	{

		do {

			Prime[i] = rand() % 1000; // 3�ڸ����� ����		

		} while (IsNotPrime(Prime[i]));	 //�Ҽ��� �ƴϸ� �ݺ��Ѵ�.

	}

	n = Prime[0] * Prime[1];		// �ΰ��� �Ҽ� p,q�� �̿��� n�� ����

	return (Prime[0] - 1)*(Prime[1] - 1);  // ���Ϸ� ���̰�;

}

int Make_Public_Key(long long e_pi)

{
	long long e;

	do
	{
		e = rand() % 100;	//3�ڸ��� ����	

		if ((e < e_pi) && (GCD(e, e_pi) == 1)) return e;	// ���Ϸ� ���̿� ���� ���� e�� ����. 

	} while (1);

}

int Make_Private_Key(int e, long long e_pi)

{

	int d = 0;

	while (((e*d) % e_pi) != 1) d++;		//����Ű ����

	return d;	//����Ű�� �����Ѵ�. 

}

void Key_Gender_RSA(int *public_key, int *private_key)
{
	long long e_pi = Make_Random_Prime_Number();

	*public_key = Make_Public_Key(e_pi);

	*private_key = Make_Private_Key(*public_key, e_pi);
}
