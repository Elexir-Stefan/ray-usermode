#include <raykernel.h>
#include <syscall.h>

#include <system.h>
#include <ray/sct.h>

using namespace Kernel;
using namespace Kernel::RDM;

RAY_TDM System::HardReset(UINT32 method)
{
	RAY_TDM result;
	SysCall(SCT::HardSystemReset, &method, result);
	
	return result;
}

