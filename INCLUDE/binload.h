#ifndef __MyBinaryLoadH__
#define __MyBinaryLoadH__

#ifdef MINIWIN
#include "miniwin/windows.h"
#else
#include <windows.h>
#endif

typedef struct _MyBinaryHandle
{
	LPVOID	BinaryStart;
	int Flag;
	struct _MyBinaryHandle *Next;
}*Handle;

LPVOID LoadVertex(Handle Binary,long No,LPVOID Buffer);
LPVOID LoadTriangle(Handle Binary,long No,LPVOID Buffer);
Handle CreateBinary(LPSTR FileName);
DWORD GetSize(Handle Binary,long No);
DWORD GetVCount(Handle hBin,long No);
DWORD GetTCount(Handle hBin,long No);
BOOL DeleteBinary(Handle Binary);

#endif