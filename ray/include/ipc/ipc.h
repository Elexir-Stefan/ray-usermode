#ifndef IPC_H
#define IPC_H

#include "ipc_int.h"

extern const _IPCMessage IPCMessage;

void* operator new(long unsigned int sizeInBytes, const _IPCMessage& ipcm);
void* operator new[](long unsigned int sizeInBytes, const _IPCMessage& ipcm);
void operator delete(void* address, const _IPCMessage& ipcm);
void operator delete[](void* address, const _IPCMessage& ipcm);

#define ipcnew new(IPCMessage)
#define ipcdelete(obj) operator delete(obj, IPCMessage)

#endif