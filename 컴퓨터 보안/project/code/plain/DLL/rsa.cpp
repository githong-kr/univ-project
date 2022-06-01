#include "rsa.h"

int n, message_length = 0;

long long mod(long long n, long long e, long long m)// residue = n^e (mod m)을 수행한다.

{

	long long i, residue = 1;

	for (i = 1; i <= e; i++)

	{

		residue *= n;	//residue=residue*n

		residue %= m;

	}//residue=residue%n 오버플로를 방지하고자 mod연산을 이용하여 자릿수를 줄인다.

	return residue;

}

int Make_Cypher_text(char Plain_text[BUFSIZE], long long Cyper_text[BUFSIZE], int key)

{

	int i;

	message_length = strlen(Plain_text);

	for (i = 0; i < message_length; i++)	  //메세지 길이에 맞게 반복한다.

		Cyper_text[i] = (long long)mod(Plain_text[i], key, n);  //암호화

	Cyper_text[i] = '\0';		//종료 표시


	return 0;

}

int Make_Plain_text(long long Cyper_text[BUFSIZE], char Plain_text[BUFSIZE], int key)

{

	int  i;

	for (i = 0; i < message_length; i++) // 메세지 길이에 맞게 반복한다.

		Plain_text[i] = (char)mod(Cyper_text[i], key, n);	//복호화

	Plain_text[i] = '\0';	//종료 표시

	return 0;

}

int GCD(long long x, long long y)		//최대 공약수 검사

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

int IsNotPrime(int n)		//소수가 아닌지 검사

{

	int  i, limit;

	if (!(n % 2))  return (TRUE);	//짝수이면 소수가 아니다.

	limit = (int)sqrt(n) + 1;	//n제곱+1을 하여 보다 빨리 소수를 찾는다.

	for (i = 3; i <= limit; i += 2) //3부터 홀수 단위로 나머지 연산을 한다. 

		if (!(n%i))  return (TRUE);

	return (FALSE);

}

long long Make_Random_Prime_Number()// 랜덤 솟수(2개) 생성기

{

	int i;

	int Prime[2]; // P와 Q 두개의 솟수는 공개키, 비밀키의 기본 소수

	time_t t;

	srand((unsigned int)time(&t)); //난수생성

	for (i = 0; i < 2; i++)				// 2개의 임의의 솟수 P와 Q를 생성한다. 

	{

		do {

			Prime[i] = rand() % 1000; // 3자리수로 고정		

		} while (IsNotPrime(Prime[i]));	 //소수가 아니면 반복한다.

	}

	n = Prime[0] * Prime[1];		// 두개의 소수 p,q를 이용해 n값 생성

	return (Prime[0] - 1)*(Prime[1] - 1);  // 오일러 파이값;

}

int Make_Public_Key(long long e_pi)

{
	long long e;

	do
	{
		e = rand() % 100;	//3자리로 제한	

		if ((e < e_pi) && (GCD(e, e_pi) == 1)) return e;	// 오일러 파이와 서로 소인 e를 리턴. 

	} while (1);

}

int Make_Private_Key(int e, long long e_pi)

{

	int d = 0;

	while (((e*d) % e_pi) != 1) d++;		//개인키 생성

	return d;	//개인키를 리턴한다. 

}

void Key_Gender_RSA(int *public_key, int *private_key)
{
	long long e_pi = Make_Random_Prime_Number();

	*public_key = Make_Public_Key(e_pi);

	*private_key = Make_Private_Key(*public_key, e_pi);
}
