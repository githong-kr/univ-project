#include "A5_1.h"

int maj(int x, int y, int z)
{
	if (x == 0)
	{
		if (y == 0)
		{
			return 0;
		}
		else
		{
			if (z == 0)
				return 0;
			else
				return 1;
		}
	}
	else
	{
		if (y == 1)
		{
			return 1;
		}
		else
		{
			if (z == 1)
				return 1;
			else
				return 0;
		}
	}
}

void X(int* x)
{
	int t = x[13] ^ x[16] ^ x[17] ^ x[18];

	for (int i = 18; i > 0; i--)
	{
		x[i] = x[i - 1];
	}
	x[0] = t;
}

void Y(int* y)
{
	int t = y[20] ^ y[21];

	for (int i = 21; i > 0; i--)
	{
		y[i] = y[-1];
	}
	y[0] = t;
}

void Z(int* z)
{
	int t = z[7] ^ z[20] ^ z[21] ^ z[22];

	for (int i = 22; i > 0; i--)
	{
		z[i] = z[i - 1];
	}
	z[0] = t;
}

int Bit_to_Int(int *bit)
{
	int result = 0;
	int x = 1;

	for (int i = 7; i >= 0; i--)
	{
		if (bit[i] == 1)
		{
			result += x;
		}
		x *= 2;
	}

	return result;
}

void Init(int* x, int* y, int* z)
{
	for (int i = 0; i < 19; i++)
		x[i] = rand() % 2;
	for (int i = 0; i < 22; i++)
		y[i] = rand() % 2;
	for (int i = 0; i < 23; i++)
		z[i] = rand() % 2;
}

void Key_Gender_A5_1(int* s)
{
	int x[19];
	int y[22];
	int z[23];
	int m;

	srand(time(NULL));

	Init(x, y, z);

	int bit[8];

	for (int j = 0; j < BUFSIZE; j++)
	{
		for (int i = 0; i < 8; i++)
		{
			m = maj(x[8], y[10], z[10]);

			if (x[8] == m)
			{
				X(x);
			}
			else if (y[10] == m)
			{
				Y(y);
			}
			else if (z[10] == m)
			{
				Z(z);
			}

			bit[i] = x[18] ^ y[21] ^ z[22];
		}
		s[j] = Bit_to_Int(bit);
	}

}

void A5_1(char *msg, int* key)
{
	int len = strlen(msg);
	for (int i = 0; i < len; i++)
	{
		msg[i] = msg[i] ^ key[i];
	}
}