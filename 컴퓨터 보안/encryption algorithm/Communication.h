#ifndef __COMMUNICATION_H__
#define __COMMUNICATION_H__

#define LENGTH 100

int F_Send(int s, char *msg);
int F_Recv(int s, char *msg);

#endif