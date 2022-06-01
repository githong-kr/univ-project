#ifndef __MAKE_SERVER_H__
#define __MAKE_SERVER_H__


#include "top.h"
#include "Log.h"
#include "A5_1.h"
#include "Feistel.h"
#include "ECC.h"
#include "rsa.h"
#include "sha256.h"
#include "Caesar_cipher.h"


__declspec(dllexport) SOCKET Make_Server(int port);

#endif