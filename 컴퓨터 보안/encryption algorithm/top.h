#ifndef __TOP_H__
#define __TOP_H__

#include "Communication.h"
#include "rsa.h"
#include "make_client.h"

#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <process.h>
#include <time.h>

#define BUFSIZE 512
#define RELAY_PORT 9000
#define SERVER_PORT 9001

void Init_String(char *msg);

#endif
