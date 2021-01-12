/**
 * @file stress.cpp
 *
 * @date Apr 3 2012
 * @author stefan
 * @brief Stress tests
 */

#include <raykernel.h>
#include <video/VideoStream.h>
#include <video/KernelVideo.h>
#include <processes/processes.h>

#include <string.h>
#include <stdlib.h>

using namespace Kernel;
using namespace Kernel::Processes;

class AllocationThread;
class TestThread;
class StatisticsThread;

static const UINT32 fairnessThreads = 4;
static UINT64 fairnessRunTime[fairnessThreads];
static TestThread* fairThreads[fairnessThreads];
static StatisticsThread* statistics;
static bool fairnessRunning = false;
static Semaphore fairnessSemaphore(1, false);
static Semaphore limitSemaphore(1, false);
static UINT32 limitsStarted = 0;

inline UINT64 ReadTSC() {
	UINT32 eax, edx;
	UINT64 result;
	
	__asm__ __volatile__("rdtsc":"=a"(eax), "=d"(edx));
	result = edx;
	result <<= 32;
	return result + eax;
}

class AllocationThread: public Processes::Thread
{
	protected:
	virtual SINT32 Run(void)
	{
		while(TRUE)
		{
			UINT32 sizeInMB = 1048576 * ((rand() % 10) + 1);	// 1 to 10 MB
			UINT32 pause = 50 + (rand() % 2000); // 30 ms to 2 s
			UINT8* buffer = new UINT8[sizeInMB]; // 1 MB
			
			
			Thread::Pause(pause);
			delete[] buffer;
		}
		return 0;
	}
};

class StatisticsThread: public Processes::Thread
{
	protected:
	virtual SINT32 Run(void)
	{
		while(TRUE)
		{
			// we need to acquire the lock, as we read the values multiple times
			fairnessSemaphore.Enter();
			UINT32 sum = 0;
			for(UINT32 n = 0; n < fairnessThreads; n++)
			{
				sum += fairnessRunTime[n];
			}
			
			if (sum > 0)
			{
			
				// print the inforamtion
				kout << "Statistics: ";
				for(UINT32 n = 0; n < fairnessThreads; n++)
				{
					UINT32 perCent = fairnessRunTime[n] * 100 / sum;
					fairnessRunTime[n] = 0;
					kout << "Thread #" << n << " [" << perCent << "%] ";
				}
				kout << VideoStream::endl;
			}
			fairnessSemaphore.Leave();
				
			Thread::Pause(1000);
		}
		return 0;
	}
};

class LimitThread: public Processes::Thread
{
	protected:
	virtual SINT32 Run(void)
	{
		limitSemaphore.Enter();
		limitsStarted++;
		limitSemaphore.Leave();
		
		return 0;
	}
};

class TestThread: public Processes::Thread
{
	private:
		UINT32 _uniqueNumber;
	public:
		TestThread(UINT32 uniqueNumber):
		_uniqueNumber(uniqueNumber)
		{
		}
		
	protected:
	virtual SINT32 Run(void)
	{
		kout << "Thread #" << _uniqueNumber << " started." << VideoStream::endl;
		while(TRUE)
		{
			// very intesive task
			UINT32 a, b, c;
			a = 1;
			for(UINT32 i = 0; i < 99999; i++)
			{
				
				a = i / 2;
				b += i / 3;
				c = a + b;
				b = c - a;
			}
			
			// update the statistics
			fairnessSemaphore.Enter();
			fairnessRunTime[_uniqueNumber]++;
			fairnessSemaphore.Leave();
			
		}
		return 0;
	}
};



static void StressTestMem(UINT32 size)
{
	UINT8* memBlock;
	UINT32 count = 0;

	kout << "Allocating blocks of " << size << " bytes (" << (size >> 10) << " KB / " << (size >> 20) << " MB) in size. They will NOT be de-allocated!" << VideoStream::endl;
	
	while( (memBlock = new UINT8[size]) )
	{
		// write some data to it in order to actually test the write permission
		for(UINT32 i = 0; i < size; i++)
		{
			memBlock[i] = (UINT8)(i % 255);
		}

		count++;
		kout << "\rAllocated " << count << " blocks [" << ((count * size) >> 10 ) << " KB / " << ((count * size) >> 20 ) << " MB ]";
	}
	kout << VideoStream::endl << "Could not allocate any more." << VideoStream::endl;
}

static void StressTestMem(void)
{
	UINT32 size = 1048576; // 1 MB

	kout << "The kernel should run out of physical pages without depleting the allocating hash map." << VideoStream::endl;
	
	StressTestMem(size);
}

static void StressTestMemHash(void)
{
	UINT32 size = 4096; // 1 MB

	kout << "The kernel should exeed the allocating hash map before hitting the" << VideoStream::endl;
	kout << "limit of physical pages." << VideoStream::endl;
	
	StressTestMem(size);
}


static void StressTestMemBig(void)
{
	UINT8* memBlock;
	UINT32 count = 0;
	UINT32 size, largeStart = 1 << 31;
	UINT32 total = 0;
	
	kout << "Allocating large blocks blocks until it succeeds" << VideoStream::endl;
	
	for(size = largeStart; size > 4096; size -= 4096)
	{
		count = 0;
		while( (memBlock = new UINT8[size]) )
		{
			count++;
			total += size;
		}
		kout << "Allocated " << count << " blocks of size " << (size >> 10) << " KB (" << (size >> 20) << " MB)." << VideoStream::endl;
	}
	
	kout << "Allocated " << (total >> 10) << " KB (" << (total >> 20) << " MB) in total." << VideoStream::endl;
}

static void StressTestMemCongest(void)
{

	UINT64 tsc = ReadTSC();
	UINT32 seed = (UINT32) (tsc & 0xffffffff);
	
	srand(seed);
	
	AllocationThread* allocThread = new AllocationThread();
	
	allocThread->Start();
}


static void StressTestThreads(void)
{
	UINT32 n = 0;
	limitsStarted = 0;
	
	while(true)
	{
		try
		{
			n++;
			LimitThread* someThread = new LimitThread();
			someThread->Start();
			kout << "\r Started " << n << " Threads. " << limitsStarted << " up and running so far.";
		}
		catch (ThreadCreationException& e)
		{
			kout <<  "Could not start last thread." << VideoStream::endl;
			break;
		}
	}
}

static void StressTestScheduler(void)
{
	if (fairnessRunning)
	{
		kout << "Stress test still running. Stopping...";
		// Abort all the threads statistics
		for(UINT32 n = 0; n < fairnessThreads; n++)
		{
			fairThreads[n]->Abort();
		}
		statistics->Abort();
		kout << " done." << VideoStream::endl;
		
		fairnessRunning = false;
	}
	else
	{
	
		statistics = new StatisticsThread();
	
		// Initialize statistics
		for(UINT32 n = 0; n < fairnessThreads; n++)
		{
			fairnessRunTime[n] = 0;
			fairThreads[n] = new TestThread(n);
			fairThreads[n]->Start(1 + n);
		}
	
		statistics->Start(PRIO_HIGHEST);
		kout << "Background threads have been started." << VideoStream::endl;
		
		fairnessRunning = true;
	}
}


void StressTest(String type)
{
	if (strcmp(type, "mem") == 0)
	{
		StressTestMem();

	}
	else if (strcmp(type, "membig") == 0)
	{
		StressTestMemBig();
	}
	else if (strcmp(type, "memhash") == 0)
	{
		StressTestMemHash();
	}
	else if (strcmp(type, "congest") == 0)
	{
		StressTestMemCongest();
	}
	else if (strcmp(type, "thread") == 0)
	{
		StressTestThreads();
	}
	else if (strcmp(type, "sched") == 0)
	{
		StressTestScheduler();
	}
	else
	{
		kout << "Unknown stress test: " << type << VideoStream::endl;
	}
}

#include "stress.h"

