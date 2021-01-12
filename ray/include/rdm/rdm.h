/**
 * @file rdm.h
 * @author Stefan Nuernberger [NURNware Technologies - stefan@nurnware.de]
 * @date May 9, 2010
 * @brief Ray Driver Model (RDM) functionality
 */

#ifndef RDM_H
#define RDM_H

#include <raykernel.h>
#include <rayexception.h>
#include <processes/processes.h>
#include <vector>

#define InPortB(port, ret) __asm__ __volatile__ ("inb %%dx, %%al" : "=a"(ret):"d"(port))
#define OutPortB(port, value) __asm__ __volatile__ ("outb %%al, %%dx"::"d"(port), "a" (value))
#define InPortW(port, ret) __asm__ __volatile__ ("inw %%dx, %%ax" : "=a"(ret):"d"(port))
#define OutPortW(port,value) __asm__ __volatile__ ("outw %%ax, %%dx"::"d"(port), "a" (value))
#define InPortL(port, ret) __asm__ __volatile__ ("inl %%dx, %%eax" : "=a"(ret):"d"(port));
#define OutPortL(port, value) __asm__ __volatile__ ("outl %%eax, %%dx"::"d"(port), "a" (value))

namespace Kernel {
namespace RDM {

	typedef enum {
		TDM_SUCCESS = 0,
		TDM_INSUFFICIENT_RIGHTS = 1,
		TDM_TRUSTED_ONLY = 2,
		TDM_OUT_OF_MEMORY = 3,
		TDM_PARTNERSHIP_ONLY = 4,
		TDM_ILLEGAL_ARGUMENT = 5,
		TDM_IMPOSSIBLE = 6
	} RAY_TDM;

	enum RDMFailure {
				InsufficientRights,
				TrustedOnly,
				PartnershipOnlny,
				IllegalArgument,
				Impossible,
				AlreadyInUse,
				Unknown
	};

	class RDMException : public Exception
	{
	public:
		RDMException(RDMFailure reason);
		RDMFailure GetReason();
	private:
		RDMFailure reason;
	};

	class IOPort
	{
	public:
		static void RequestIOPort(UINT16 port);
	};

	class IRQHandler : public Processes::Thread
	{
	public:
			IRQHandler(UINT8 irqNum) throw(RDMException, OutOfMemoryException);
			virtual void HandleIRQ() = 0;
			virtual void CaughtException(Exception& ex) = 0;

	protected:
		UINT8 interruptNumber;

		virtual SINT32 Run();

		friend class IRQ;

	};

	/**
	 * Handles IRQs encapsulated in a class
	 */
	class IRQ {
	public:


		static void RegisterIRQHandler(UINT32 intNum) throw(RDMException, OutOfMemoryException);
		static void AcknowledgeAndWaitForIRQ(UINT8 irqNum) throw(RDMException, OutOfMemoryException);
	};
}
}

#endif
