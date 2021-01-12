/**
 * @file ps.cpp
 *
 * @date Apr 3 2012
 * @author stefan
 * @brief Process info display
 */

#include <raykernel.h>
#include <video/VideoStream.h>
#include <video/KernelVideo.h>
#include <processes/processes.h>

#include "ps.h"

using namespace Kernel;
using namespace Kernel::Processes;

void PrintThreadInfo(THREAD_INFO *info, BOOL extended) {
    const char *states[5] = {"RUN", "IDLE", "WAIT", "MSG", "EVENT"};
	
    if (extended) {
	kout << info->pid << "\t" << info->threadNum << "\t";

	kout << (info->usedPages << 2) << "K\t" << info->memAllocs;
	kout << "\t" << info->lastFitPointerCode << ":" << info->lastFitPointerData;
	kout << "\t" << states[info->state];
	kout << "\t" << info->ident << VideoStream::endl;
    } else {

    	kout << info->pid;
		kout << "\t" << info->threadNum;
		kout << "\t\t\t\t" << states[info->state];
		kout << "\t" << info->ident << VideoStream::endl;
    }
}

void PrintProcessInfo(UINT32 pid)
{
	THREAD_INFO_LIST *info;
	UINT32 i, j;

	info = Process::GetProcessesInfo(pid);

	if (info) {
		kout << info->numThreads << " threads currently running.\nKernel Memory " << info->kernelMemory << " bytes.\n\n";
		kout << "PID\tTID\tMEM\tALLOCS\t\tSTATUS\tNAME\n";
		kout << "======= ======= ======= =============== ======= =======================\n";
		for (i = 0; i < info->numThreads; i++) {
			// if it's a parent thread (process)
			if (info->thread[i].threadNum == 0) {
			    PrintThreadInfo(info->thread + i, TRUE);

			    // print all the threads
			    for (j = 0; j < info->numThreads; j++) {
					if ((info->thread[i].pid == info->thread[j].pid) && (info->thread[j].threadNum > 0)) {
						PrintThreadInfo(info->thread + j, FALSE);
					}
			    }
			    kout << VideoStream::endl;
			}
		}
		kout << "Memory usage: " << info->memUsageTotal << " bytes ("<< info->memFree <<" Bytes free)\n";
		UINT32 memTotal = info->memUsageTotal + info->memFree;
		double perCUSEDd = (double)info->memUsageTotal / (double)memTotal;
		UINT32 perCUsed = (UINT32)(perCUSEDd * 100.0);
		kout << "              " << (memTotal >> 20) << " MB total (" << perCUsed << "% used)" << VideoStream::endl;

		delete info;
	} else {
		kout  << "Error getting process information!" << VideoStream::endl;
	}
}

