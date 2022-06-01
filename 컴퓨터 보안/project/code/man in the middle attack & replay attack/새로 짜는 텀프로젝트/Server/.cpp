#include "top.h"

int F_Send(int s, char *msg)			// Communication.h�� ���ǵ� LENGTH ���̸�ŭ ���ڿ��� ���� �޼��� ����
{
	int len = strlen(msg);

	for (int i = len; i < LENGTH; i++)
		msg[i] = '!';
	msg[LENGTH - 1] = NULL;

	return send(s, msg, LENGTH, 0);
}

int F_Recv(int s, char *msg)			// Communication.h�� ���ǵ� LENGTH ���̸�ŭ ���ڿ��� ���� �� �޼��� �߶󳻾� ����
{
	char buf[BUFSIZE];
	int recv_len = 0;
	int index = 0;

	Init_String(msg);

	while (true)
	{
		int len;
		len = recv(s, buf, LENGTH, 0);
		if (len == -1)
			return -1;

		strcat(msg, buf);

		recv_len += len;
		if (recv_len == LENGTH)
			break;
	}

	while (msg[index] != '!') index++;

	msg[index] = NULL;

	return true;
}
