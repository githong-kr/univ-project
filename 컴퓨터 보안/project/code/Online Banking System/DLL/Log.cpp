#include "Log.h"

void Write_Log(FILE *fp, char *msg)			// 해당 파일에 msg 내용 시간과 함께 작성
{
	time_t t;
	char log[BUFSIZE];
	time(&t);
	sprintf(log, "%s*%s\n", ctime(&t), msg);
	fputs(log, fp);
}

void Menu_1_Log(char *msg, int select)			// 입력값에 대한 로그 메세지 생성
{
	if (select == 1)
		sprintf(msg, "로그인 시도\n");
	else if (select == 2)
		sprintf(msg, "등록 시도\n");
	else if (select == 3)
		sprintf(msg, "프로그램 종료\n");
	else
		sprintf(msg, "잘못된 입력\n");
}

void Menu_2_Log(char *msg, int select)			// 입력값에 대한 로그 메세지 생성
{
	if (select == 1)
		sprintf(msg, "계좌 조회\n");
	else if (select == 2)
		sprintf(msg, "입금\n");
	else if (select == 3)
		sprintf(msg, "출금\n");
	else if (select == 4)
		sprintf(msg, "로그아웃\n");
	else
		sprintf(msg, "잘못된 입력\n");
}
