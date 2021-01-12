#ifndef KERNEL_PROCESS_H
#define KERNEL_PROCESS_H

#include <raykernel.h>
#include <processes/privileges.h>
#include <processes/arguments.h>
#include <ipc/ipc_int.h>

#define EXIT_CODE_ABORT		-32760
#define EXIT_CODE_CHILD		-32761
#define EXIT_CODE_RMIRESULT	-32762
#define EXIT_CODE_NO_THREAD	-32763

#define THREAD_IDENT_LENGTH	64

namespace Kernel {
namespace Processes {

	typedef UINT32 PID;
	typedef UINT32 TID;

	typedef struct {
		PID pid;
		TID tid;
		BOOL isProcessParent;
		UINT32 handle;
	} PID_HANDLE;
	
	typedef enum {
		T_RUNNING = 0,
		T_IDLE = 1,
		T_WAITING = 2,
		T_MSG_RECV = 3,
		T_EXITING = 5
	} __attribute__((packed)) THREAD_STATE;
	

	typedef struct {
		UINT32 pid;
		IPC::RMISERIAL serial;
		UINT32 numExports;

		UINT32 usedMemory;
		UINT32 usedPages;
		UINT32 memAllocs;
		UINT32 lastFitPointerCode;
		UINT32 lastFitPointerData;

		UINT64 contextSwitches;
		UINT64 cpuCycles;
		UINT64 privCycles;
		THREAD_STATE state;

		UINT32 threadNum;
		BOOL isParent;
		char ident[THREAD_IDENT_LENGTH];
		
	} THREAD_INFO;

	typedef struct {
		UINT32 numThreads;
		UINT32 kernelMemory;
		UINT32 memUsageTotal;
		UINT32 memFree;
		THREAD_INFO *thread;
	} THREAD_INFO_LIST;

	class ThreadCreationException : public Exception
	{
		public:
		ThreadCreationException();

	};
	
	class ThreadStateException : public Exception
	{
		public:
	ThreadStateException();

	};

	class Process
	{
		public:
			static const UINT32 ShowAllThreads = 0;

			static void SetReturnFromThread(void* address);
			/**
			 * Get process/thread information
			 * @param pid of the process you want to get information for, 0 for all processes
			 * @return list of process information
			 */
			static THREAD_INFO_LIST* GetProcessesInfo(UINT32 pid);

			static PID GetPID();
	};
	
	class Thread
	{
	public:
		Thread();

		void Start(PRIORITY prio) throw(ThreadCreationException);
		void Start() throw(ThreadCreationException);
		SINT32 Join() throw(ThreadStateException);
		BOOL IsAlive() throw(ThreadStateException);
		void Notify() throw(ThreadStateException);
		void Abort() throw(ThreadStateException);
		static void Sleep();
		static void Pause(UINT32 msecs);
		virtual SINT32 Run() = 0;


	private:
		static void KernelThreadCallback(Thread* obj);
		static void ExitThread(SINT32 exitCode);

		bool threadStarted;

	protected:
		PID_HANDLE pidHandle;
	};

	class Sync
	{
		public:
			Sync(CString name, BOOL othersAllowed);
			Sync(CString name);
			BOOL Arrive();
			BOOL Go(BOOL wakeForeignProcesses);
			BOOL Close();

		private:
			static BOOL BarrierCreate(CString barrierName, BOOL othersAllowed);
			static BOOL BarrierArrive(CString barrierName);
			static BOOL BarrierGo(CString barrierName, BOOL wakeForeignProcesses);
			static BOOL BarrierClose(CString barrierName);

			CString name;
	};


	typedef enum {
		SEMAPHORE_IN_USE = 0,
		SEMAPHORE_ILLEGAL = 1,
		SEMAPHORE_MISUSE = 2,
		SEMAPHORE_DENIED = 3,
		SEMAPHORE_READY = 4
	} SEMAPHORE_STATUS;
	
	typedef UINT32 IPLOCK;

	class Semaphore
	{
	public:
		Semaphore(UINT32 initialValue, bool othersAllowed) throw(ThreadStateException);
		Semaphore(CString explicitName, UINT32 initialValue, bool othersAllowed) throw(ThreadStateException);

		void Enter() throw(ThreadStateException);
		void Leave() throw(ThreadStateException);
		SEMAPHORE_STATUS Status();

		~Semaphore();
		
	private:
		static IPLOCK Create(CString explicitName, UINT32 initialValue, bool othersAllowed);
		static String MakeStringFromAddress(void* address, String buffer);
		IPLOCK handle;
		char _stringBuffer[20];
	};
}
}

#endif
