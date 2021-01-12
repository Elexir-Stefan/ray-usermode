/*
 * debug.cpp
 *
 *  Created on: May 28, 2010
 *      Author: stefan
 */

#include <raykernel.h>
#include <ray/sct.h>
#include <syscall.h>
#include <memory.h>
#include <debug.h>
#include <string.h>

using namespace Kernel;

void Debug::WriteDebugMsg(CString message)
{
	SysCallN(SCT::Debug::DebugMsg, &message);
}

void Debug::Break()
{
	SysCallN(SCT::Debug::Break, 0);
}

UINT32 Debug::Demangle(const char* mangled, char* demangled, UINT32 maxLength)
{
	UINT32 length = 0;
	UINT32 mangledLength = strlen(mangled);
	
	if (maxLength == 0)
	{
		return 0;
	}
	
	*demangled = 0;	// terminate
	
	bool numberStart = false;
	UINT32 currNumber = 0;
	for(UINT32 i = 0; i < mangledLength;)
	{
		// if it's a number, we need it. Otherwise we skip it
		if ((mangled[i] >= '0') && (mangled[i] <= '9'))
		{
			numberStart = true;
			currNumber *= 10;
			currNumber += mangled[i] - '0';
			
			i++;
		}
		else
		{
			// if it's after a number
			if (numberStart)
			{
				// currNumber holds the number of characters to copy
				if (i + currNumber > mangledLength)
				{
					// too long, cannot be
					return 0;
				}
				
				// if it's the first time, do nothing. But otherwise
				// add the standard delimiter (".")
				if (length > 0)
				{
					if (length + 1 >= maxLength)
					{
						// doesn't fit in the buffer
						return length;
					}
					
					demangled[length++] = '.';
				}
				
				// check length 
				if (length + currNumber >= maxLength)
				{
					// doesn't fit in the buffer
					return length;
				}
				
				// otherwise everything is ok - let's copy
				memcpy(demangled + length, mangled + i, currNumber);
				length += currNumber;
				i += currNumber;
				currNumber = 0;
				
				demangled[length] = 0;
				
				numberStart = false;
			}
			else
			{	
				// skip it otherwise 
				i++;
			}
		}
		
		
	}
	
	return length;
	
}

/* ************************** Profiler ****************************/

ProfilerException::ProfilerException(const ProfilerFailureReason& reason)
:_reason(reason)
{

}

const ProfilerException::ProfilerFailureReason& ProfilerException::GetReason()
{
	return this->_reason;
}

Profiler::Profiler(UINT32 profileDataSamples) throw (ProfilerException)
: _profileDataSamples(profileDataSamples), _started(false)
{
	SysCallN(SCT::Debug::Profile_Setup, &profileDataSamples);
}

/**
 * Starts the profiling in kernel space
 */
void Profiler::Start()
{
	if (!this->_started)
	{
		this->_started = true;
		SysCallN(SCT::Debug::Profile_Start, 0);
	}
}

/**
 * Stops the currently running profiling procedure, but keeps
 * the buffer intact, so that it can be engaged again later.
 */
void Profiler::Pause()
{
	if (this->_started)
	{
		this->_started = false;
		SysCallN(SCT::Debug::Profile_Stop, 0);
	}
}

/**
 * Rewinds the kernel profiling buffer. All data collected so
 * far will be lost
 */
void Profiler::Reset()
{
	SysCallN(SCT::Debug::Profile_Reset, 0);
}

void Profiler::FlushKernel()
{
	SysCallN(SCT::Debug::Profile_Flush, 0);
}

/**
 * Returns the usage of the buffer in bytes
 * @return
 */
UINT32 Profiler::GetUsage()
{
	UINT32 usage;
	SysCall(SCT::Debug::Profile_RCount, 0, usage);

	return usage;
}

/**
 * Returns the usage of the buffer in % (value between 0.0 and 1.0)
 * @return
 */
float Profiler::GetUsagePercent()
{
	return (float)GetUsage() / this->_profileDataSamples;
}

/**
 * Returns the profile data that has been collected by the kernel
 * @return
 */
std::vector<Profiler::FUNC_PROFILE_ENTRY>& Profiler::GetProfileData()
{
	UINT32 linearAddress;


	// Get the actual buffer
	SysCall(SCT::Debug::Profile_GetBuffer, 0, linearAddress);
	// build pointer to array of given length
	FUNC_PROFILE_ENTRY* plainCArray = (FUNC_PROFILE_ENTRY*)linearAddress;

	if(!plainCArray)
	{
		throw new ProfilerException(ProfilerException::BufferEmpty);
	}

	UINT32 count = GetMemBlockSize(plainCArray) / sizeof(FUNC_PROFILE_ENTRY);

	// and construct the vector
	std::vector<FUNC_PROFILE_ENTRY>* theVector = new std::vector<FUNC_PROFILE_ENTRY>(plainCArray, plainCArray + count);

	return *theVector;
}
