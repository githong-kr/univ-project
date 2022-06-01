#ifndef __RSA_H__
#define __RSA_H__

#include "top.h"
#include <math.h>

extern "C" __declspec(dllexport)
int rsa_enc(char *msg, int public_key);

extern "C" __declspec(dllexport)
int rsa_dec(char *msg, int private_key);

extern "C" __declspec(dllexport)
void Key_Gender_RSA(int *public_key, int *private_key);


#endif