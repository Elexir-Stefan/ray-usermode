/**
 * @file Command.cpp
 *
 * @date Jun 6, 2010
 * @author stefan
 * @brief (summary)
 */
#include <raykernel.h>
#include <video/VideoStream.h>
#include <video/KernelVideo.h>
#include <processes/processes.h>
#include <string.h>
#include <debug.h>
#include <stdlib.h>

#include "Command.h"
#include "benchmark.h"
#include "ps.h"
#include "reboot.h"
#include "stress.h"

using namespace Kernel;
using namespace Kernel::Processes;


void ShowUsage()
{
	kout << "Available commands are:" << VideoStream::endl;
	kout << "\tCOMMAND\tPARAM\tDESCRIPTION" << VideoStream::endl;
	kout << "\t======= ======= =======================================================" << VideoStream::endl;

	kout << "\tps\t\tProcess List" << VideoStream::endl;
	kout << "\t\t<PID>\tLimit information to only process <PID>" << VideoStream::endl << VideoStream::endl;

	kout << "\tver\t\tShow version" << VideoStream::endl << VideoStream::endl;

	kout << "\tpid\t\tShow own process ID (PID)" << VideoStream::endl << VideoStream::endl;

	kout << "\tbench\t\tStart micro benchmarks" << VideoStream::endl << VideoStream::endl;

	kout << "\tstress\t\tStress test the kernel. You must specify one of:" << VideoStream::endl;
	kout << "\t\tmem\tAllocate small blocks of mem until memory is depleted." << VideoStream::endl; 
	kout << "\t\tmembig\tAllocate the largest possible block(s)." << VideoStream::endl; 
	kout << "\t\tmemhash\tAllocate small chunks to poison allocation hash map." << VideoStream::endl; 
	kout << "\t\tcongest\tAllocate and de-allocate memory constantly" << VideoStream::endl; 
	kout << "\t\tthread\tStart as many threads as possible" << VideoStream::endl; 
	kout << "\t\tsched\tStart many threads with different priorities " << VideoStream::endl;
	kout << "\t\t\tand statistics of fairness and runtime." << VideoStream::endl << VideoStream::endl; 

	kout << "\tbreak\t\tBreak into the kernel debugger" << VideoStream::endl << VideoStream::endl;

	kout << "\texit\t\tExit (this) console process." << VideoStream::endl << VideoStream::endl;

	kout << "\treset\t\tForce hard reset of machine immediately" << VideoStream::endl;
	kout << "\t\ti\tReset via i8042 reset line" << VideoStream::endl;
	kout << "\t\tt\tReset via triple fault" << VideoStream::endl;
	kout << "\t\th\tHalt processor indefinetely" << VideoStream::endl << VideoStream::endl;

	
}

void Command::ExecuteCommand(String cmd)
{
	if (strcmp(cmd, "ps") == 0)
	{
		PrintProcessInfo(Process::ShowAllThreads);

	}
	else if (strncmp(cmd, "ps ", 3) == 0)
	{
		String argument = cmd + 3;
		UINT32 pid = atoi(argument);
		PrintProcessInfo(pid);
	}
	else if (strncmp(cmd, "stress ", 7) == 0)
	{
		String argument = cmd + 7;
		StressTest(argument);
	}
	else if (strcmp(cmd, "stress") == 0)
	{
		kout << "stress needs an additional parameter specifying the type of stress test. See 'help'." << VideoStream::endl;
	}

	else if (strcmp(cmd, "pid") == 0)
	{
		kout << "My PID is " << Process::GetPID() << VideoStream::endl;
	}
	else if (strcmp(cmd, "break") == 0)
	{
		Debug::Break();
	}
	else if (strcmp(cmd, "exit") == 0)
	{
		exit(0);
	}
	else if (strcmp(cmd, "bench") == 0)
	{
		Benchmark();
	}
	else if (strcmp(cmd, "help") == 0)
	{
		ShowUsage();
	}
	else if (strncmp(cmd, "reset", 5) == 0)
	{
		Reboot(cmd + 5);
	}
	else if (strcmp(cmd, "ver") == 0)
	{
		kout << "RAY C++ Console application. Built on " << __DATE__ << ", " << __TIME__ << VideoStream::endl;
	}
	else
	{
		kout << "Unknown command. Type 'help' to see a list of valid commands." << VideoStream::endl;
	}

}
