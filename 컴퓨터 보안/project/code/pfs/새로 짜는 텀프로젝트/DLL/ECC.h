#ifndef __ECC_H__
#define __ECC_H__


#include "top.h"
#include "Communication.h"
#include <math.h>

#define PUBLIC_POINT 0
#define PRIVATE_POINT 1

typedef struct point {
	int x;
	int y;
}point;

__declspec(dllexport) int Key_Gender_ECC(SOCKET sock, int *key, int mul);

__declspec(dllexport) point Perfect_P(point x, int mul, int P);

__declspec(dllexport) void Set_ECC(int x_value, int y_value, int mod_value, point x);


#endif