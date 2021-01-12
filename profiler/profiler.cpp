#include <raykernel.h>
#include <exception>
#include <keyboard/keyboard.h>
#include <ipc/ipc.h>
#include <debug.h>
#include <video/VideoStream.h>

using namespace Kernel;
using namespace std;
using namespace Keyboard;
using namespace Kernel::IPC;

int UserProgramEntry(const char *arguments)
{
	// Register our connection
	Communication::Register("Profiler", "Profiling user space task");

	// Initialize the kernel profiler with 100,000 data entries
	try
	{
		Profiler profiler = Profiler(100000);

		KeyEvent keyEvent = KeyEvent();
			while(true)
			{
				// capture all keys pressed
				KeyState state = keyEvent.GetKey();

				// Start profiling on Ctrl+Home
				if (state.Modifier.Ctrl && state.KeyOnly.isHome)
				{
					// start profiling
					profiler.Start();
				}

				if (state.Modifier.Ctrl && state.KeyOnly.isEnd)
				{
					// pause profiling
					profiler.Pause();
				}

				if (state.Modifier.Ctrl && state.KeyOnly.isDelete)
				{
					// flush it through kernel debug stub
					profiler.FlushKernel();
				}

			}
	}
	catch(ProfilerException &e)
	{
		kout << "Profiler coult not be started!";
		return -1;
	}


	return 0;
}
