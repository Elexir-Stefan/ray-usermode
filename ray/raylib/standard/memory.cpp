#include <raykernel.h>
#include <memory.h>

#include <syscall.h>
#include <ray/sct.h>

using namespace Kernel;

POINTER malloc(UINT32 size) {
	UINT32 result;
	SysCall(SCT::Memory::MAlloc, &size, result);
	return (POINTER)result;
}

POINTER free(POINTER pointer) {
	UINT32 result;
	SysCall(SCT::Memory::Free, &pointer, result);
	return (POINTER)result;
}

UINT32 GetMemBlockSize(POINTER ptr) {
	UINT32 result;
	SysCall(SCT::Memory::MemSize, &ptr, result);
	return result;
}
