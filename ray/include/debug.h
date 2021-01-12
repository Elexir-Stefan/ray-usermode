/**
 * @file debug.h
 *
 * @date Jul 7, 2010
 * @author stefan
 * @brief Debugging and profiling function calls for the kernel
 */

#ifndef DEBUG_H_
#define DEBUG_H_

#include <vector>

namespace Kernel
{


	class ProfilerException : public Exception
	{
	public:
		enum ProfilerFailureReason
		{
			ProfilingAlreadyStarted,
			BufferEmpty,
			BufferFull
		};

		ProfilerException(const ProfilerFailureReason& reason);
		const ProfilerFailureReason& GetReason();

	private:
		const ProfilerFailureReason& _reason;
	};

	class Debug
	{
	public:
		static void WriteDebugMsg(CString message);
		static void Break();
		static UINT32 Demangle(const char* mangled, char* demangled, UINT32 maxLength);
	};

	class Profiler
	{
	public:

		typedef enum {
			PROF_FLG_FRAMEDROP = 1
		} __attribute__((packed)) SAMPLEFLAGS;


		struct FUNC_PROFILE_ENTRY{
			SAMPLEFLAGS flags;
			POINTER calleeAddress;
			POINTER callerAddress;
			UINT64 timeStamp;
		} __attribute__((packed)) ;

		/**
		 * Constructor
		 * @param profileDataSamples Amount of memory to reserve for the profile data
		 * (in FUNC_PROFILE_ENTRY structure units)
		 * @return
		 */
		Profiler(UINT32 profileDataSamples) throw (ProfilerException);

		/**
		 * Starts the profiling in kernel space
		 */
		void Start();

		/**
		 * Stops the currently running profiling procedure, but keeps
		 * the buffer intact, so that it can be engaged again later.
		 */
		void Pause();

		/**
		 * Rewinds the kernel profiling buffer. All data collected so
		 * far will be lost
		 */
		void Reset();

		/**
		 * Flushes the internal profiling via the kernels debug stub
		 * (usually COM2)
		 */
		void FlushKernel();

		/**
		 * Returns the usage of the buffer in bytes
		 * @return
		 */
		UINT32 GetUsage();

		/**
		 * Returns the usage of the buffer in % (value between 0.0 and 1.0)
		 * @return
		 */
		float GetUsagePercent();

		/**
		 * Returns the profile data that has been collected by the kernel
		 * @return
		 */
		std::vector<FUNC_PROFILE_ENTRY>& GetProfileData();

	private:
		UINT32 _profileDataSamples;
		bool _started;
	};
}

#endif /* DEBUG_H_ */
