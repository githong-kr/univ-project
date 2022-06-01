#ifndef __RSA_H__
#define __RSA_H__

#include "top.h"
#include <math.h>
#include "Communication.h"

/*
__declspec(dllexport)
int Key_Gender_RSA(int *public_key, int *private_key);

__declspec(dllexport)
void Enc_Sign(char *source, char *dest, int Public_key, int Private_key, unsigned long your_n, unsigned long my_n);

__declspec(dllexport)
void Sign_Dec(char *source, char *dest, int Public_key, int Private_key, unsigned long your_n, unsigned long my_n);
*/

 typedef struct _key
 {
	 BigUnsigned Public_key;
	 BigUnsigned your_Public_key;
	 BigUnsigned Private_key;
	 BigUnsigned your_n;
	 BigUnsigned my_n;
 } KEY;

 typedef struct _array_overflow
 {
	 int array_overflow[3][BUFSIZE];

 }ARRAY_OVERFLOW;

 __declspec(dllexport)
BigUnsigned rsa_enc(char *msg, BigUnsigned public_key, BigUnsigned m);

 __declspec(dllexport)
BigUnsigned rsa_dec(char *msg, BigUnsigned private_key, BigUnsigned m);

 __declspec(dllexport)
BigUnsigned Key_Gender_RSA(BigUnsigned *public_key, BigUnsigned *private_key);

 __declspec(dllexport)
	 void Enc_Sign(char *source, char *dest, KEY k, ARRAY_OVERFLOW *arr);

 __declspec(dllexport)
	 void Sign_Dec(char *source, char *dest, KEY k, ARRAY_OVERFLOW *arr);

 __declspec(dllexport)
	 BigUnsigned mod(const BigUnsigned a, const BigUnsigned ex, const BigUnsigned b); // residue = n^e (mod m)을 수행한다.
 
 __declspec(dllexport)
	 int Key_Exchange_RSA(SOCKET sock, KEY *k);




#endif