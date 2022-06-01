#ifndef __ECC_H__
#define __ECC_H__


#include "top.h"
#include "Communication.h"
#include <math.h>

typedef struct point {
	int x;
	int y;
}point;

__declspec(dllexport) int Key_Gender_ECC(SOCKET sock, int *key, int mul);

#endif