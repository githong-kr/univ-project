#include "ECC.h"

enum {
	GREY = 0x7,
	WHITE = 0xF,
	GREEN = 0xA,
	CYAN = 0xB,
	RED = 0xc,
	YELLOW = 0xE
};



int mod(int num, int p, int flag);
int GetM(point p1, point p2, int a, int p);
void Set_Color_Console(WORD color);

point ECC(int a, int b, int p, point x, int key)
{
	point p1, p2, p3;
	int m;
	int y_2;
	int y_2_mod;

	int count = 0;

	printf("\n");

	memset(&p1, 0, sizeof(point));
	memset(&p2, 0, sizeof(point));
	memset(&p3, 0, sizeof(point));


	p1.x = x.x; p1.y = x.y;
	p2.x = x.x; p2.y = x.y;
	int index = 0;
	bool sw = FALSE;
	while (index < key-1)
	{
		if (p2.x - p1.x < 0)
		{
			point temp;
			temp.x = p2.x; temp.y = p2.y;
			p2.x = p1.x; p2.y = p1.y;
			p1.x = temp.x; p1.y = temp.y;
			sw = TRUE;
		}

		m = GetM(p1, p2, a, p);

		p3.x = m * m - p1.x - p2.x;
		p3.x = mod(p3.x, p, 0);
		p3.y = m * (p1.x - p3.x) - p1.y;
		p3.y = mod(p3.y, p, 0);

		y_2 = (p3.x * p3.x * p3.x) + (a * p3.x) + b;
		y_2_mod = mod(y_2, p, 0);

		if (sw == TRUE)
		{
			point temp;
			temp.x = p2.x; temp.y = p2.y;
			p2.x = p1.x; p2.y = p1.y;
			p1.x = temp.x; p1.y = temp.y;
			sw = FALSE;
		}
		p2.x = p3.x; p2.y = p3.y;

		index++;
	}

	return p3;
}

//(음수)^-1 처리는 안되어 있음
int mod(int num, int p, int flag)
{
	//+,- mod 연산
	if (flag == 0)
	{
		int count = 0;

		//- mod
		if (num < 0)
		{
			num *= -1;
			while (1)
			{
				if (((num + count++) % p) == 0)
				{
					num = --count;
					count = 1;
					break;
				}
			}
		}
		//+ mod
		else
			num %= p;

		return num;
	}
	//revers_mod 연산 ^-1 되어 있는 것
	else if (flag == 1)
	{
		int count = 1;

		//^-1 mod
		do
		{
			if ((num*count % p) == 1)
			{
				num = count;
				break;
			}
		} while (count++);

		return num;
	}

	return -1;
}

int GetM(point p1, point p2, int a, int p)
{
	int count = 0;

	if (p1.x == p2.x && p1.y == p2.y)
	{
		//입력 시 tmp2는 음수가 안되도록
		int tmp1 = 3 * (p1.x * p1.x) + a;
		int tmp2 = 2 * p1.y;

		tmp1 = mod(tmp1, p, 0);
		tmp2 = mod(tmp2, p, 1);

		return ((tmp1 * tmp2) % p);
	}
	else
	{
		//입력 시 tmp2는 음수가 안되도록. 즉, 두번째 x값이 첫번째 x값 보다 크게끔 입력
		int tmp1 = p2.y - p1.y;
		int tmp2 = p2.x - p1.x;

		tmp1 = mod(tmp1, p, 0);
		tmp2 = mod(tmp2, p, 1);

		return ((tmp1 * tmp2) % p);
	}

	return -1;
}

void Set_Color_Console(WORD color)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

int Key_Gender_ECC(SOCKET sock, int *key, int mul)
{
	int seed;
	point x = { 2, 7 };
	point s;
	char buf[BUFSIZE];

//	printf("\n y^2 = x^3 + 11x + 19 (mod 167) , P(2,7)\n\n");

	s = ECC(11, 19, 167, x, mul);
	
	sprintf(buf, "%d", s.x);
	F_Send(sock, buf);
	sprintf(buf, "%d", s.y);
	F_Send(sock, buf);

//	printf(" My Private Exopnent is %d\n\n", mul);
//	printf(" %d * (2, 7) = (%d, %d)\n", mul, s.x, s.y);

	if (F_Recv(sock, buf) == -1)
		return -1;
	s.x = atoi(buf);
	if (F_Recv(sock, buf) == -1)
		return -1;
	s.y = atoi(buf);

//	int a = s.x, b = s.y;

	s = ECC(11, 19, 167, s, mul);

//	printf(" %d * (%d, %d) = (%d, %d) \n\n", mul, a, b, s.x, s.y);

	seed = s.x;

	srand(seed);

	for (int i = 0; i < BUFSIZE; i++)
	{
		key[i] = rand() % 9;
	}

}