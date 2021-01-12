#include <raykernel.h>
#include <processes/processes.h>
#include <ray/sct.h>
#include <syscall.h>
#include <typeinfo>
#include <cxxabi.h>
#include <stdlib.h>
#include <debug.h>


using namespace Kernel::Processes;

extern "C" void _returnFromThread();

ThreadCreationException::ThreadCreationException()
{

}

ThreadStateException::ThreadStateException()
{

}

void Process::SetReturnFromThread(void* address)
{	
	SysCallN(SCT::Process::StandardReturn, &address);
}

THREAD_INFO_LIST* Process::GetProcessesInfo(UINT32 pid)
{
	UINT32 result;

	SysCall(SCT::Process::THREAD_INFO, &pid, result);

	return (THREAD_INFO_LIST*)result;
}

PID Process::GetPID()
{
	UINT32 result;
	UINT32 dummy[] = {};

	SysCall(SCT::Process::GetPID, &dummy, result);
	return (PID)result;
}

/* ************************** Sync ************************** */

Sync::Sync(CString barrierName, BOOL othersAllowed)
: name(barrierName)
{
	BarrierCreate(barrierName, othersAllowed);
}

Sync::Sync(CString barrierName)
: name(barrierName)
{

}

BOOL Sync::Arrive()
{
	return BarrierArrive(this->name);
}

BOOL Sync::Go(BOOL wakeForeignProcesses)
{
	return BarrierGo(this->name, wakeForeignProcesses);
}

BOOL Sync::Close()
{
	return BarrierClose(this->name);
}

BOOL SYSTEM Sync::BarrierCreate(CString barrierName, BOOL othersAllowed) {
	UINT32 result;
	SysCall(SCT::Sync::BarrierCreate, &barrierName, result);
	return (BOOL)result;
}

BOOL SYSTEM Sync::BarrierArrive(CString barrierName) {
	UINT32 result;
	SysCall(SCT::Sync::BarrierArrive, &barrierName, result);
	return (BOOL)result;
}

BOOL SYSTEM Sync::BarrierGo(CString barrierName, BOOL wakeForeignProcesses) {
	UINT32 result;
	SysCall(SCT::Sync::BarrierGo, &barrierName, result);
	return (BOOL)result;
}

BOOL SYSTEM Sync::BarrierClose(CString barrierName) {
	UINT32 result;
	SysCall(SCT::Sync::BarrierClose, &barrierName, result);
	return (BOOL)result;
}

String Semaphore::MakeStringFromAddress(void* address, String buffer)
{
	UINT32 number = reinterpret_cast<UINT32>(address);
	char localOneChar[2] = {0, 0};
	strcpy(buffer, "R");
	
	while(number)
	{
		localOneChar[0] = 'A' + (number % 26);
		number /= 26;
		strcat(buffer, localOneChar);
	}
	
	return buffer;
}

Semaphore::Semaphore(UINT32 initialValue, bool othersAllowed) throw(ThreadStateException)
{
	// come up with some unique random string value
	handle = Create(MakeStringFromAddress(this, _stringBuffer), initialValue, othersAllowed);
	if (handle == SEMAPHORE_IN_USE)
	{
		throw ThreadStateException();
	}
}

Semaphore::Semaphore(CString explicitName, UINT32 initialValue, bool othersAllowed) throw(ThreadStateException)
{
	handle = Create(explicitName, initialValue, othersAllowed);
	if (handle == SEMAPHORE_IN_USE)
	{
		throw ThreadStateException();
	}
	
}

Semaphore::~Semaphore()
{
	UINT32 result;
	UINT32 arguments[] = {handle};
	
	SysCall(SCT::Sync::IP_LOCK_DESTROY, &arguments, result);
}

IPLOCK Semaphore::Create(CString explicitName, UINT32 initialValue, bool othersAllowed)
{
	UINT32 result;
	UINT32 arguments[] = {reinterpret_cast<UINT32>(explicitName), initialValue, (UINT32)othersAllowed};
	
	SysCall(SCT::Sync::IP_LOCK_CREATE, &arguments, result);
	return (IPLOCK)result;
}

void Semaphore::Enter() throw(ThreadStateException)
{
	UINT32 result;
	UINT32 arguments[] = {handle};
	
	SysCall(SCT::Sync::IP_LOCK_ENTER, &arguments, result);
	if ((result != SEMAPHORE_READY) && (result != SEMAPHORE_IN_USE))
	{
		throw ThreadStateException();
	}
}

void Semaphore::Leave() throw(ThreadStateException)
{
	UINT32 result;
	UINT32 arguments[] = {handle};
	
	SysCall(SCT::Sync::IP_LOCK_LEAVE, &arguments, result);
	if ((result != SEMAPHORE_READY) && (result != SEMAPHORE_IN_USE))
	{
		throw ThreadStateException();
	}
}

SEMAPHORE_STATUS Semaphore::Status()
{
	UINT32 result;
	UINT32 arguments[] = {handle};
	
	SysCall(SCT::Sync::IP_LOCK_STATUS, &arguments, result);
	return (SEMAPHORE_STATUS)result;
}

/* **************************** Thread **********************/
Thread::Thread()
: threadStarted(false)
{

}

void Thread::Start(PRIORITY prio) throw(ThreadCreationException)
{
	char demangledName[64];
	
	Debug::Demangle(typeid(*this).name(), demangledName, 64);

	UINT32 thisPointer = (UINT32)this;
	UINT32 args[] = {
			(UINT32)&Thread::KernelThreadCallback,
			(UINT32)&_returnFromThread,
			prio,
			1,
			(UINT32)&thisPointer,
			(UINT32)demangledName,
			(UINT32)&this->pidHandle};
	UINT32 result;
	SysCall(SCT::Process::THREAD_CREATE, &args, result);

	BOOL success = (BOOL)result;

	if (!success)
	{
		throw ThreadCreationException();
	}

	this->threadStarted = true;
}

void Thread::Start() throw(ThreadCreationException)
{
	Start(PRIO_NORMAL);
}

void Thread::Abort() throw(ThreadStateException)
{
	if (!this->threadStarted)
	{
		throw ThreadStateException();
	}

	SINT32 result;
	UINT32 parameters[] = {(UINT32)&this->pidHandle};
	SysCall(SCT::Process::THREAD_ABORT, &parameters, result);
}

void Thread::ExitThread(SINT32 exitCode)
{
	SysCallN(SCT::Process::THREAD_EXIT, &exitCode);
}

void Thread::KernelThreadCallback(Thread* obj)
{
	Thread::ExitThread(obj->Run());
}

SINT32 Thread::Join() throw(ThreadStateException)
{
	if (!this->threadStarted)
	{
		throw ThreadStateException();
	}

	SINT32 result;
	UINT32 parameters[] = {(UINT32)&this->pidHandle};
	SysCall(SCT::Process::THREAD_JOIN, &parameters, result);

	if (result == EXIT_CODE_NO_THREAD)
	{
		throw ThreadStateException();
	}

	return result;
}

void Thread::Notify() throw(ThreadStateException)
{
	if (!this->threadStarted)
	{
		throw ThreadStateException();
	}

	SINT32 result;
	UINT32 parameters[] = {(UINT32)&this->pidHandle};
	SysCall(SCT::Process::THREAD_NOTIFY, &parameters, result);

	BOOL success = (BOOL)result;
	if (!success)
	{
		throw ThreadStateException();
	}
}

BOOL Thread::IsAlive() throw(ThreadStateException)
{
	if (!this->threadStarted)
	{
		throw ThreadStateException();
	}

	SINT32 result;
	UINT32 parameters[] = {(UINT32)&this->pidHandle};
	SysCall(SCT::Process::THREAD_ALIVE, &parameters, result);

	BOOL success = (BOOL)result;

	return success;
}

void Thread::Sleep()
{
	SysCallN(SCT::Process::Sleep, 0);
}

void Thread::Pause(UINT32 msecs)
{
	SysCallN(SCT::Process::Pause, &msecs);
}
