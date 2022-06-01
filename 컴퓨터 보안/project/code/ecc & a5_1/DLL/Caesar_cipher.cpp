#include "Caesar_cipher.h"
#include <ctype.h>

int Key_Gender_Caesar()
{
	srand(time(NULL));

	return (rand() % 25) + 1;
}

char Convert(char a, int key)
{
	if (key > 0)
	{
		if (islower(a))
		{
			for (int i = 0; i < key; i++)
			{
				a++;
				if (a > 'z')
					a = 'a';
			}
			return a;
		}
		else
		{
			for (int i = 0; i < key; i++)
			{
				a++;
				if (a > 'Z')
					a = 'A';
			}
			return a;
		}
	}

	else
	{
		if (islower(a))
		{
			for (int i = 0; i < -key; i++)
			{
				a--;
				if (a < 'a')
					a = 'z';
			}
			return a;
		}
		else
		{
			for (int i = 0; i < -key; i++)
			{
				a--;
				if (a < 'A')
					a = 'Z';
			}
			return a;
		}
	}
	
}

void Caesar(char* dest, const char* source, int key)
{
	char tmp;
	int index;

	for (index = 0; index < strlen(source); index++)
	{
		if (isalpha(source[index]))
			dest[index] = Convert(source[index], key);
		else
			dest[index] = source[index];
	}
	dest[index] = 0;
}

