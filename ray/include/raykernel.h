#ifndef _RAY_KERNEL_H
#define _RAY_KERNEL_H

/**
 * include other files
 */
#include <ray/typedefs.h>
#include <rayexception.h>
#include <standard.h>

/**
 * optimization hints
 */
#define RAYENTRY void __attribute__ ((noreturn))
#define SYSTEM __attribute__ ((noinline))
#define INLINE __attribute__ ((always_inline))
#define CALLBACK void __attribute__ ((stdcall))

/**
 * Entry points for drivers and applications
 */

extern "C" int UserProgramEntry(CString arguments);

namespace Kernel {
	class OutOfMemoryException : public Exception
	{
	public :
		OutOfMemoryException();
	};

}

#endif
