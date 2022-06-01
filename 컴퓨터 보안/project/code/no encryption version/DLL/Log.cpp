#include "Log.h"

void Write_Log(FILE *fp, char *msg)			// �ش� ���Ͽ� msg ���� �ð��� �Բ� �ۼ�
{
	time_t t;
	char log[BUFSIZE];
	time(&t);
	sprintf(log, "%s*%s\n", ctime(&t), msg);
	fputs(log, fp);
}

void Menu_1_Log(char *msg, int select)			// �Է°��� ���� �α� �޼��� ����
{
	if (select == 1)
		sprintf(msg, "�α��� �õ�\n");
	else if (select == 2)
		sprintf(msg, "��� �õ�\n");
	else if (select == 3)
		sprintf(msg, "���α׷� ����\n");
	else
		sprintf(msg, "�߸��� �Է�\n");
}

void Menu_2_Log(char *msg, int select)			// �Է°��� ���� �α� �޼��� ����
{
	if (select == 1)
		sprintf(msg, "���� ��ȸ\n");
	else if (select == 2)
		sprintf(msg, "�Ա�\n");
	else if (select == 3)
		sprintf(msg, "���\n");
	else if (select == 4)
		sprintf(msg, "�α׾ƿ�\n");
	else
		sprintf(msg, "�߸��� �Է�\n");
}
