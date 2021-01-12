#include <raykernel.h>
#include <syscall.h>

#include <ray/sct.h>

using namespace Kernel;

void exit(UINT32 result) {
	SysCallN(SCT::Exit, &result);
	for(;;);
}


