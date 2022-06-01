#include "Feistel.h"

int Bit_to_Int(int *bit, int len)
{
	int result = 0;
	int x = 1;

	for (int i = len - 1; i >= 0; i--)
	{
		if (bit[i] == 1)
		{
			result += x;
		}
		x *= 2;
	}

	return result;
}

void Reverse(int *Left, int *Right)
{
	int tmp_left[4];
	int tmp_right[4];
	int j = 3;

	for (int i = 0; i < 4; i++)
	{
		tmp_left[i] = Left[i];
		tmp_right[i] = Right[i];
	}
	for (int i = 0; i < 4; i++)
	{
		Left[i] = tmp_left[j];
		Right[i] = tmp_right[j--];
	}
}

int Combine(const int *Left, const int *Right)
{
	int Result[8];

	for (int i = 0; i < 4; i++)
	{
		Result[i] = Left[i];
	}
	for (int i = 4; i < 8; i++)
	{
		Result[i] = Right[i - 4];
	}

	return Bit_to_Int(Result, 8);
}

void Devide(char a, int *Left, int *Right)
{
	for (int i = 0; i < 4; i++)
	{
		Right[i] = a & 1;
		a = a >> 1;
	}
	for (int i = 0; i < 4; i++)
	{
		Left[i] = a & 1;
		a = a >> 1;
	}

	Reverse(Left, Right);
}

int Func(int Left, int Key)
{
	return Left ^ Key;
}

void Key_Gender_Feistel(int *key)
{
	srand(time(NULL));

	for (int i = 0; i < 4; i++)
	{
		key[i] = rand() % 2;
	}
}

void Feistel(char *msg, int *Key, int Enc_Dec)
{
	//int len = strlen(msg);

	int Left[4], Right[4];
	int Tmp[4];

	if (Enc_Dec == ENC)
	{
		for (int i = 0; i < /*len*/BUFSIZE; i++)
		{
			Devide(msg[i], Left, Right);

			// 쪼개진 반으로 처리할 것
			for (int j = 0; j < 3; j++)
			{
				for (int k = 0; k < 4; k++)			// Left 임시 저장
				{
					Tmp[k] = Left[k];
				}

				for (int k = 0; k < 4; k++)			// Right를 Left에 저장
				{
					Left[k] = Right[k];
				}

				for (int k = 0; k < 4; k++)			// Left를 Func와 함께 Right에 저장
				{
					Right[k] = Func(Tmp[k], Key[k]);
				}

			}
			msg[i] = Combine(Left, Right);
		}
	}
	else if (Enc_Dec == DEC)
	{
		for (int i = 0; i < /*len*/BUFSIZE; i++)
		{
			Devide(msg[i], Left, Right);

			// 쪼개진 반으로 처리할 것
			for (int j = 0; j < 3; j++)
			{
				for (int k = 0; k < 4; k++)			// Left 임시 저장
				{
					Tmp[k] = Left[k];
				}

				for (int k = 0; k < 4; k++)			// Right를 Func와 함께 Left에 저장
				{
					Left[k] = Func(Right[k], Key[k]);
				}

				for (int k = 0; k < 4; k++)			// Left를 Right에 저장
				{
					Right[k] = Tmp[k];
				}

			}
			msg[i] = Combine(Left, Right);
		}
	}

}
