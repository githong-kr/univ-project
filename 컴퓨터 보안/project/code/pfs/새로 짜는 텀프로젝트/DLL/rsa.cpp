#include "rsa.h"

BigUnsigned n; int message_length = 0;

void init(int array[3][BUFSIZE])
{
	memset(array[0], 0, sizeof(int)*BUFSIZE);
	memset(array[1], 0, sizeof(int)*BUFSIZE);
	memset(array[2], 0, sizeof(int)*BUFSIZE);

}


BigUnsigned mod(const BigUnsigned a, const BigUnsigned ex, const BigUnsigned b)// residue = n^e (mod m)을 수행한다.

{
	/*
	BigUnsigned i, residue = 1;
	for (i = 1; i <= e; i++)
	{
		residue *= a;	//residue=residue*n
		residue %= m;
	}//residue=residue%n 오버플로를 방지하고자 mod연산을 이용하여 자릿수를 줄인다.

	return residue;
*/
	
	BigUnsigned result = stringToBigUnsigned("1");
	BigUnsigned temp = (a);
	BigUnsigned m = (b);
	BigUnsigned exp = (ex);
	BigUnsigned one = stringToBigUnsigned("1");
	temp = (BigUnsigned)(temp % m);


	while (exp > stringToBigUnsigned("0"))
	{
		if ((exp & one) != stringToBigUnsigned("0"))
		{
			result = result * temp;
			result = result % m;

		}
		temp = temp*temp;
		temp = temp % m;


		exp.bitShiftRight(exp,1);

		//cout << result << endl;
	}


	return result;

}

BigUnsigned Make_Cypher_text(char Plain_text[BUFSIZE], BigUnsigned Cyper_text[BUFSIZE], BigUnsigned m, BigUnsigned key)

{

	int i;
	
	message_length = (int)strlen(Plain_text);

	char buf[BUFSIZE];


	for (i = 0; i < message_length; i++)	  //메세지 길이에 맞게 반복한다.
	{

		Cyper_text[i] = (mod(Plain_text[i], (key), (m)));  //암호화
	}
	Cyper_text[i] = '\0';		//종료 표시


	return 0;

}

BigUnsigned Make_Plain_text(BigUnsigned Cyper_text[BUFSIZE], char Plain_text[BUFSIZE], BigUnsigned m, BigUnsigned key)

{

	int i;

	for (i = 0; i < message_length; i++) // 메세지 길이에 맞게 반복한다.
	{
		Plain_text[i] = mod((Cyper_text[i]), (key), (m)).toInt();	//복호화
	}
	Plain_text[i] = '\0';	//종료 표시

	return 0;

}

BigUnsigned GCD(BigUnsigned x, BigUnsigned y)		//최대 공약수 검사

{
	return y == stringToBigUnsigned("0") ? x : GCD(y, x % y);
}

BigUnsigned rsa_enc(char *msg, BigUnsigned public_key, BigUnsigned m)
{
	BigUnsigned encrypt[BUFSIZE];

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

BigUnsigned rsa_dec(char *msg, BigUnsigned private_key, BigUnsigned m)
{
	BigUnsigned decrypt[BUFSIZE];

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

		decrypt[i] = stringToBigUnsigned(temp);
		j++;
	}


	Make_Plain_text(decrypt, msg, private_key, m);
	message_length = 0;
	return 0;

}

BigUnsigned msqrt(BigUnsigned x)
{
	BigUnsigned tmp = stringToBigUnsigned("1");

	for (int i = 0; i < 10; i++)
		tmp = (tmp + (x / tmp)) / 2;

	return tmp;
}

int IsNotPrime(BigUnsigned n)		//소수가 아닌지 검사

{

	BigUnsigned i, limit;

	if (n % 2 == 0)  return (TRUE);	//짝수이면 소수가 아니다.

	limit = msqrt(n) + 1;	//n제곱+1을 하여 보다 빨리 소수를 찾는다.

	for (i = 3; i <= limit; i += 2) //3부터 홀수 단위로 나머지 연산을 한다. 

		if ((n%i) == 0)  return (TRUE);

	return (FALSE);

}

BigUnsigned Make_Random_Prime_Number()// 랜덤 솟수(2개) 생성기

{
	UINT32 x, y, z, w;
	UINT32 t;
	t ^= t << 11;
	t ^= t >> 8;
	x = y; y = z; z = w;
	w ^= w >> 19;
	w ^= t;

	int i;
	int select_algorithm = w;
	BigUnsigned Prime[2]; // P와 Q 두개의 솟수는 공개키, 비밀키의 기본 소수


	srand(time(NULL)); //난수생성

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


	n.multiply(Prime[0], Prime[1]);		// 두개의 소수 p,q를 이용해 n값 생성

	BigUnsigned ret;

	ret.multiply(Prime[0] - 1, Prime[1] - 1);

	return ret;  // 오일러 파이값;

}

BigUnsigned Make_Public_Key(BigUnsigned e_pi)

{
	BigUnsigned e;
	
	do
	{
		e = rand() % 1000;	//3자리로 제한	
		if ((e.compareTo(e_pi) == -1) && (gcd(e, e_pi)) == 1) return e;	// 오일러 파이와 서로 소인 e를 리턴. 
	} while (1);
	
	//e = 3;


	return e;
}

BigUnsigned Make_Private_Key(BigUnsigned e, BigUnsigned e_pi)

{

	BigUnsigned d = 0;

	while (((e*d) % e_pi) != 1)
	{
		d.add(d, 1);
	}

	return d;	//개인키를 리턴한다. 

}

BigUnsigned Key_Gender_RSA(BigUnsigned *public_key, BigUnsigned *private_key)
{
	BigUnsigned e_pi = Make_Random_Prime_Number();

	*public_key = Make_Public_Key(e_pi);

	*private_key = Make_Private_Key(*public_key, e_pi);

	return n;
}

void Enc_Sign(char *source, char *dest, KEY k, ARRAY_OVERFLOW *arr)
{
	int i;
	BigUnsigned enc[BUFSIZE];
	BigUnsigned dec[BUFSIZE];
	memset(enc, 0, BUFSIZE);
	memset(dec, 0, BUFSIZE);
	memset(dest, 0, BUFSIZE);
	message_length = strlen(source);
	char buf[BUFSIZE];

	

	printf("\n암호화\n");
	for (i = 0; i < message_length; i++)	  //메세지 길이에 맞게 반복한다.
	{
		enc[i] = mod(source[i], (k.your_Public_key), (k.your_n));  //암호화
		cout << enc[i] << " ";
	}
	//enc[i] = '\0';		//종료 표시

	printf("\n서명\n");
	init(arr->array_overflow);
	for (i = 0; i < message_length; i++) // 메세지 길이에 맞게 반복한다.
	{

		if (enc[i] >= k.my_n)
		{
			arr->array_overflow[0][i] += 1;
			enc[i] -= k.my_n;

			while (1)
			{
				arr->array_overflow[1][i] ++;
				if (enc[i] < k.my_n)
					break;
				enc[i] -= k.my_n;
			}
			
		}

		dec[i] = mod(enc[i], (k.Private_key), (k.my_n));	//복호화
		cout << dec[i] << " ";

		if (dec[i] >= k.my_n)
		{
			arr->array_overflow[0][i] += 2;
			dec[i] -= k.my_n;

			while (1)
			{
				arr->array_overflow[2][i] ++;
				if (dec[i] < k.my_n)
					break;
				dec[i] -= k.my_n;
			}
		}

	}
	//dec[i] = '\0';	//종료 표시


	printf("\n전송용 문자열\n");
	for (int j = 0; j < message_length; j++)
	{
		char temp[BUFSIZE] = { NULL };
		strcpy(temp, bigUnsignedToString(dec[j]).c_str());
		sprintf(temp, "%s@", temp);
		strcat(dest, temp);
	}
	cout << dest << " \n";

}

void Sign_Dec(char *source, char *dest, KEY k, ARRAY_OVERFLOW *arr)
{
	BigUnsigned dec[BUFSIZE];
	BigUnsigned enc[BUFSIZE];
	memset(enc, 0, BUFSIZE);
	memset(dec, 0, BUFSIZE);
	memset(dest, 0, BUFSIZE);


	int j = 0;
	message_length = 0;

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

		dec[i] = stringToBigUnsigned(temp);
		j++;
	}

	int i;

	printf("\n전달 받은 데이터 \n");
	for (i = 0; i < message_length; i++)	  //메세지 길이에 맞게 반복한다.
	{
		cout << dec[i] << " ";
	}

	printf("\n서명 풀기 \n");
	for (i = 0; i < message_length; i++)	  //메세지 길이에 맞게 반복한다.
	{
		if (arr->array_overflow[0][i] > 1)
		{
			dec[i] += k.your_n;
			arr->array_overflow[0][i] -= 2;

			while (1)
			{
				arr->array_overflow[2][i] --;
				if (arr->array_overflow[2][i] == 0)
					break;
				dec[i] += k.your_n;
			}

		}
		enc[i] = mod((dec[i]), (k.your_Public_key), (k.your_n));  //암호화
		cout << enc[i] << " ";
	}
	//enc[i] = '\0';		//종료 표시

	printf("\n복호화 \n");
	for (i = 0; i < message_length; i++) // 메세지 길이에 맞게 반복한다.
	{
		if (arr->array_overflow[0][i] == 1)
		{
			enc[i] += k.your_n;
			arr->array_overflow[0][i] -= 1;

			while (1)
			{
				arr->array_overflow[1][i] --;
				if (arr->array_overflow[1][i] == 0)
					break;
				enc[i] += k.your_n;
			}
		}
		dest[i] = atoi(bigIntegerToString(mod((enc[i]), (k.Private_key), (k.my_n))).c_str());	//복호화		
	}
	//dest[i] = '\0';	//종료 표시

	cout << dest << " \n";
}

int Key_Exchange_RSA(SOCKET sock, KEY *k)
{
	char msg[BUFSIZE];
	KEY *tmp;

	k->my_n = Key_Gender_RSA(&k->Public_key, &k->Private_key);

	strcpy(msg,bigUnsignedToString(k->my_n).c_str());
	F_Send(sock, msg);
	strcpy(msg, bigUnsignedToString(k->Public_key).c_str());
	F_Send(sock, msg);


	F_Recv(sock, msg);
	k->your_n = stringToBigUnsigned(msg);
	F_Recv(sock, msg);
	k->your_Public_key = stringToBigUnsigned(msg);

	return 0;
}