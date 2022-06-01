#ifndef __CLIENT_PFS_H__
#define __CLIENT_PFS_H__

#pragma comment(lib, "DLL.lib")

#include "rsa.h"
#include "ECC.h"

__declspec(dllexport) int Client_PFS(SOCKET server_sock, KEY k, int *key);

#endif