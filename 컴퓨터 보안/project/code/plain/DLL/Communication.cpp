#include "Communication.h"

 int F_Send(int s, char *msg)			// Communication.h�� ���ǵ� BUFSIZE ���̸�ŭ ���ڿ��� ���� �޼��� ����
{
	int len = strlen(msg);

	for (int i = len; i < BUFSIZE; i++)
		msg[i] = '!';
	msg[BUFSIZE - 1] = NULL;

	return send(s, msg, BUFSIZE, 0);
}

 int F_Recv(int s, char *msg)			// Communication.h�� ���ǵ� BUFSIZE ���̸�ŭ ���ڿ��� ���� �� �޼��� �߶󳻾� ����
{
	char buf[BUFSIZE];
	int recv_len = 0;
	int index = 0;

	memset(msg, 0, sizeof(msg));

	while (true)
	{
		int len;
		len = recv(s, buf, BUFSIZE, 0);
		if (len == -1)
			return -1;

		strcat(msg, buf);

		recv_len += len;
		if (recv_len == BUFSIZE)
			break;
	}

	while (msg[index] != '!') index++;

	msg[index] = NULL;

	return true;
}
