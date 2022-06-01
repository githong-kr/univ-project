#include "rsa.h"

unsigned long long n, message_length = 0;

unsigned long long mod(const unsigned long long a, const unsigned long long e, const unsigned long long m)// residue = n^e (mod m)을 수행한다.

{

	long long i, residue = 1;
	for (i = 1; i <= e; i++)
	{
		residue *= a;	//residue=residue*n
		residue %= m;
	}//residue=residue%n 오버플로를 방지하고자 mod연산을 이용하여 자릿수를 줄인다.
	return residue;

}

int Make_Cypher_text(char Plain_text[BUFSIZE], unsigned unsigned long long Cyper_text[BUFSIZE], unsigned long long m, int key)

{

	int i;

	message_length = strlen(Plain_text);

	for (i = 0; i < message_length; i++)	  //메세지 길이에 맞게 반복한다.

		Cyper_text[i] = (unsigned long long)mod(Plain_text[i], key, m);  //암호화

	Cyper_text[i] = '\0';		//종료 표시


	return 0;

}

int Make_Plain_text(unsigned long long Cyper_text[BUFSIZE], char Plain_text[BUFSIZE], unsigned long long m, int key)

{

	int  i;

	for (i = 0; i < message_length; i++) // 메세지 길이에 맞게 반복한다.

		Plain_text[i] = (char)mod(Cyper_text[i], key, m);	//복호화

	Plain_text[i] = '\0';	//종료 표시

	return 0;

}

int GCD(unsigned long long x, unsigned long long y)		//최대 공약수 검사

{
	return y == 0 ? x : GCD(y, x % y);
}

int rsa_enc(char *msg, int public_key, unsigned long long m)
{
	unsigned long long encrypt[BUFSIZE];

	char send_msg[BUFSIZE] = { 0 };

	Make_Cypher_text(msg, encrypt, public_key, m);

	memset(msg, 0, sizeof(msg));
	for (int i = 0; i < message_length; i++)
	{
		char temp[BUFSIZE] = { 0 };
		sprintf(temp, "%lld@", encrypt[i]);
		strcat(msg, temp);
	}
	message_length = 0;
	return 0;
}

int rsa_dec(char *msg, int private_key, unsigned long long m)
{
	unsigned long long decrypt[BUFSIZE];

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

		decrypt[i] = strtoull(temp, NULL, 10);
		j++;
	}


	Make_Plain_text(decrypt, msg, private_key, m);
	message_length = 0;
	return 0;

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

unsigned long long Make_Random_Prime_Number()// 랜덤 솟수(2개) 생성기

{
	UINT32 x, y, z, w;
	UINT32 t;
	t ^= t << 11;
	t ^= t >> 8;
	x = y; y = z; z = w;
	w ^= w >> 19;
	w ^= t;

	int i;
	static int select_algorithm = 0;
	int Prime[2]; // P와 Q 두개의 솟수는 공개키, 비밀키의 기본 소수

	time_t T;

	srand((unsigned int)time(&T)); //난수생성

	select_algorithm %= 2;

	if (select_algorithm == 0)
	{
		for (i = 0; i < 2; i++)				// 2개의 임의의 솟수 P와 Q를 생성한다. 

		{

			do {

				Prime[i] = (rand() % 1000); // 3자리수로 고정		

			} while (IsNotPrime(Prime[i]));	 //소수가 아니면 반복한다.

		}
		select_algorithm++;
	}
	else
	{
		for (i = 0; i < 2; i++)				// 2개의 임의의 솟수 P와 Q를 생성한다. 

		{

			do {

				UINT32 x, y, z, w;
				UINT32 t;
				t ^= t << 11;
				t ^= t >> 8;
				x = y; y = z; z = w;
				w ^= w >> 19;
				w ^= t;

				Prime[i] = (w % 1000); // 3자리수로 고정		

			} while (IsNotPrime(Prime[i]));	 //소수가 아니면 반복한다.

		}

		select_algorithm++;
	}


	n =  Prime[0] * Prime[1];		// 두개의 소수 p,q를 이용해 n값 생성

	return (Prime[0] - 1)*(Prime[1] - 1);  // 오일러 파이값;

}

int Make_Public_Key(unsigned long long e_pi)

{
	unsigned long long e;

	do
	{
		e = rand() % 1000;	//3자리로 제한	
		if ((e<e_pi) && (GCD(e, e_pi) == 1)) return e;	// 오일러 파이와 서로 소인 e를 리턴. 
	} while (1);

}

int Make_Private_Key(int e, unsigned long long e_pi)

{

		unsigned long long d = 0;
		while (((e*d) % e_pi) != 1)
	{
				d++;
	}

	return d;	//개인키를 리턴한다. 

}

int Key_Gender_RSA(int *public_key, int *private_key)
{
	unsigned long long e_pi = Make_Random_Prime_Number();

	*public_key = Make_Public_Key(e_pi);

	*private_key = Make_Private_Key(*public_key, e_pi);

	return n;
}

void Enc_Sign(char *source, char *dest, int Public_key, int Private_key, unsigned long long your_n, unsigned long long my_n)
{
	int i;
	unsigned long long enc[BUFSIZE];
	unsigned long long dec[BUFSIZE];
	memset(enc, 0, BUFSIZE);
	memset(dec, 0, BUFSIZE);
	memset(dest, 0, BUFSIZE);
	message_length = strlen(source);
	printf("\n암호화\n");
	for (i = 0; i < message_length; i++)	  //메세지 길이에 맞게 반복한다.
	{
		enc[i] = mod(source[i], Public_key, your_n);  //암호화
		printf("%lld ", enc[i]);
	}
	enc[i] = '\0';		//종료 표시

	printf("\n서명\n");
	for (i = 0; i < message_length; i++) // 메세지 길이에 맞게 반복한다.
	{
		dec[i] = mod(enc[i], Private_key, my_n);	//복호화
		printf("%lld ", dec[i]);
	}
	dec[i] = '\0';	//종료 표시

	printf("\n전송용 문자열\n");
	for (int j = 0; j < message_length; j++)
	{
		char temp[BUFSIZE] = {NULL};
		sprintf(temp, "%lld@", dec[j]);
		strcat(dest, temp);
	}
	printf("%s \n", dest);

}

void Sign_Dec(char *source, char *dest, int Public_key, int Private_key, unsigned long long your_n, unsigned long long my_n)
{
	int retval;
	unsigned long long dec[BUFSIZE];
	unsigned long long enc[BUFSIZE];
	memset(enc, 0, BUFSIZE);
	memset(dec, 0, BUFSIZE);
	memset(dest, 0, BUFSIZE);


	int j = 0;

	while (source[j] != '\0')
	{
		if (source[j] == '@')
			message_length++;
		j++;
	}
	j = 0;

	for (int i = 0; i < message_length; i++)
	{
		char temp[BUFSIZE] = { 0 };
		int k = 0;
		while (source[j] != '@')
		{
			temp[k] = source[j];
			j++;
			k++;
		}

		dec[i] = strtoull(temp, NULL, 10);
		j++;
	}

	int i;

	printf("\n서명 풀기 \n");
	for (i = 0; i < message_length; i++)	  //메세지 길이에 맞게 반복한다.
	{
		enc[i] = mod(dec[i], Public_key, your_n);  //암호화
		printf("%lld ", enc[i]);
	}
	enc[i] = '\0';		//종료 표시

	printf("\n복호화 \n");
	for (i = 0; i < message_length; i++) // 메세지 길이에 맞게 반복한다.
	{
		dest[i] = (char)mod(enc[i], Private_key, my_n);	//복호화		
	}
	dec[i] = '\0';	//종료 표시

	printf("%s \n", dest);
}