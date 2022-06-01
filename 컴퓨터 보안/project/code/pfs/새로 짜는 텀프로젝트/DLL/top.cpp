#include "top.h"

void Write_Data(FILE* fp, INFO info)
{
	if (info.select == 1)
	{
		fprintf(fp, "%s\t%s\t0\t0\n", info.id, info.pw);
	}
	else if (info.select == 2)
	{
		fprintf(fp, "%s\t%s\t%s\t%ld\n", info.id, info.pw, info.name, info.money);
	}
	else if (info.select == 3)
	{
		fprintf(fp, "%s\t%ld\n", info.name, info.money);
	}
}

void Read_Data(FILE*fp, INFO *info)
{
	if (info->select == 1)
	{
		fscanf(fp, "%s\t%s\n", info->id, info->pw);
	}
	else if (info->select == 2)
	{
		fscanf(fp, "%s\t%s\t%s\t%ld\n", info->id, info->pw, info->name, &info->money);
	}
	else if (info->select == 3)
	{
		fscanf(fp, "%s\t%ld\n", info->name, &info->money);
	}
}

void gotoxy(int x, int y)
{
	COORD Pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void PW_scanf(char *pw)
{
	char key;
	int index = 0;
	while (1)
	{
		
		key = _getch();
		if (key == VK_BACK && index == 0)
			continue;
		
		if (key == 13)
			break;

		pw[index++] = key;

		if (key == VK_BACK && index > 0)
		{

			gotoxy(10 + index, 4);
			printf(" ");
			gotoxy(10 + index, 4);
			index -= 2;
		}
		else
		{
			printf("*");
		}
	
	}
	pw[index] = '\0';
	puts("");
}

