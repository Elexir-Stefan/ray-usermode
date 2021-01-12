/**
 * @file reboot.cpp
 *
 * @date Apr 3 2012
 * @author stefan
 * @brief Rebooting / System reset
 */

#include <raykernel.h>
#include <video/VideoStream.h>
#include <video/KernelVideo.h>
#include <rdm/rdm.h>
#include <system.h>
#include <string.h>

using namespace Kernel;

void Reboot(String argument)
{
	UINT32 method = 0;

	UINT32 len = strlen(argument);
	for(UINT32 i = 0; i < len; i++)
	{
		switch(argument[i])
		{
		case 'i':
			method |= 1;
			kout << "Resetting using 8042 keyboard controller to pulse the CPU's RESET pin..." << VideoStream::endl;
			break;
		case 't':
			method |= 2;
			kout << "Resetting by generating an uncaught triple fault... " << VideoStream::endl;
			break;
		case 'h':
			method |= 4;
			kout << "Halting the CPU forever (This will save power ;-) )" << VideoStream::endl;
			break;
		case ' ':
			// formatting space
			break;
		default:
			kout << "Unknown reboot method!" << VideoStream::endl;
			return;
			break;
		}

	}

	if (method == 0)
	{
		kout << "No reset method selected. Using i8042..." << VideoStream::endl;
		method = 1;
	}

	if (Kernel::System::HardReset(method) == RDM::TDM_SUCCESS)
	{
		kout << "Rebooting...";
	}
	else
	{
		kout << "We are still alive. The selected reboot method did not work." << VideoStream::endl;
	}
}
