#ifndef KERNEL_SYSTEM_H
#define KERNEL_SYSTEM_H

#include <raykernel.h>
#include <rdm/rdm.h>

namespace Kernel
{

	class System
	{
	public:
		static RDM::RAY_TDM HardReset(UINT32 method);
	};

}

#endif
