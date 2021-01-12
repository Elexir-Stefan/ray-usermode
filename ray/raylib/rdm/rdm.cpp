/**
 * @file rdm.cpp
 * @author Stefan Nuernberger - stefan@nurnware.de
 * @brief Ray Driver Model (RDM) IRQ and IO implementations
 */

#include <raykernel.h>
#include <rdm/rdm.h>
#include <syscall.h>
#include <ray/sct.h>

using namespace Kernel::RDM;

/**
 * Excaption class in case of Ray Driver Model failure
 * @param reason
 * @return
 */
RDMException::RDMException(RDMFailure reason)
: reason(reason)
{

}

RDMFailure RDMException::GetReason()
{
	return this->reason;
}

IRQHandler::IRQHandler(UINT8 irqNum) throw(RDMException, OutOfMemoryException):
	interruptNumber(irqNum)
{
	// starts the thread (which in fact calls Run() )
	Start();
}

/**
 * Starting procedure of the thread.
 * This thread basically waits in a loop, so
 * that IRQs can be deferred to this thread.
 * @return
 */
SINT32 IRQHandler::Run()
{
	IRQ::RegisterIRQHandler(this->interruptNumber);

	// We have to block until an IRQ arrives
	while(true)
	{
		try {
			IRQ::AcknowledgeAndWaitForIRQ(this->interruptNumber);
			this->HandleIRQ();
		}
		catch (Exception& e)
		{
			this->CaughtException(e);
		}


	}

	// should never get here anyway
	return -1;

}


/**
 * Kernel interface to register a static irqHandler function
 * @param intNum
 * @param address
 */
void IRQ::RegisterIRQHandler(UINT32 intNum) throw(RDMException, OutOfMemoryException)
{
	RAY_TDM result;
	UINT32 arguments[] = {intNum};
	SysCall(SCT::RDM::RegisterIRQ, arguments, result);

	switch(result)
	{
	case TDM_SUCCESS:
		return;
	case TDM_INSUFFICIENT_RIGHTS:
		throw RDMException(InsufficientRights);
	case TDM_TRUSTED_ONLY:
		throw RDMException(TrustedOnly);
	case TDM_OUT_OF_MEMORY:
		throw OutOfMemoryException();
	case TDM_PARTNERSHIP_ONLY:
		throw RDMException(PartnershipOnlny);
	case TDM_ILLEGAL_ARGUMENT:
		throw RDMException(IllegalArgument);
	case TDM_IMPOSSIBLE:
		throw RDMException(Impossible);
	default:
		throw RDMException(Unknown);

	}
}

void IRQ::AcknowledgeAndWaitForIRQ(UINT8 irqNum) throw(RDMException, OutOfMemoryException)
{
	RAY_TDM result;
	UINT32 arguments[] = {irqNum};
	SysCall(SCT::RDM::IRQWait, &arguments, result);

	switch(result)
	{
	case TDM_SUCCESS:
		return;
	case TDM_INSUFFICIENT_RIGHTS:
		throw RDMException(InsufficientRights);
	case TDM_TRUSTED_ONLY:
		throw RDMException(TrustedOnly);
	case TDM_OUT_OF_MEMORY:
		throw OutOfMemoryException();
	case TDM_PARTNERSHIP_ONLY:
		throw RDMException(PartnershipOnlny);
	case TDM_ILLEGAL_ARGUMENT:
		throw RDMException(IllegalArgument);
	case TDM_IMPOSSIBLE:
		throw RDMException(Impossible);
	default:
		throw RDMException(Unknown);

	}
}

/**
 * Kernel interface used to request the use (read/write) of
 * an I/O hardware port
 * @param port
 */
void IOPort::RequestIOPort(UINT16 port)
{
	RAY_TDM result;
	SysCall(SCT::RDM::RequestIO, &port, result);

	switch(result)
	{
	case TDM_SUCCESS:
		return;
	case TDM_INSUFFICIENT_RIGHTS:
		throw RDMException(InsufficientRights);
	case TDM_TRUSTED_ONLY:
		throw RDMException(TrustedOnly);
	case TDM_OUT_OF_MEMORY:
		throw OutOfMemoryException();
	case TDM_PARTNERSHIP_ONLY:
		throw RDMException(PartnershipOnlny);
	case TDM_ILLEGAL_ARGUMENT:
		throw RDMException(IllegalArgument);
	case TDM_IMPOSSIBLE:
		throw RDMException(Impossible);
	default:
		throw RDMException(Unknown);

	}
}
