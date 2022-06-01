#include "top.h"

void Init_String(char *msg)
{
	int len = strlen(msg);

	for (int i = 0; i < len; i++)
		msg[i] = NULL;
}
