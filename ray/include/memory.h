#ifndef MEMORY_H
#define MEMORY_H

#include <ray/typedefs.h>

extern "C" {
	POINTER malloc(UINT32 size);
	POINTER free(POINTER pointer);
	UINT32 GetMemBlockSize(POINTER ptr);
}

#endif
