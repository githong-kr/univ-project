#ifndef __SERVER_PFS_H__
#define __SERVER_PFS_H__

#pragma comment(lib, "DLL.lib")

#include "rsa.h"
#include "ECC.h"

__declspec(dllexport) int Server_PFS(SOCKET client_sock, KEY k, int *key);

#endif