#ifndef __FEISTEL_H__
#define __FEISTEL_H__


#include "top.h"

#define ROUND 16
#define ENC 0
#define DEC 1


__declspec(dllexport) void Key_Gender_Feistel(int *key);
__declspec(dllexport) void Feistel(char *msg, int *Key, int Enc_Dec);

#endif