#include <raykernel.h>
#include <debug.h>
#include <exception>
#include <rdm/rdm.h>
#include <processes/processes.h>
#include <video/VideoStream.h>
#include "KeyboardHandler.h"

#include "../commondrivers/keyboard/barrier.h"

using namespace Kernel;
using namespace Kernel::Processes;
using namespace Kernel::IPC;
using namespace std;



int UserProgramEntry(const char *arguments)
{
	Sync barrier = Sync(KEYBOARD_BARRIER, FALSE);

	// Set up the IPC communication plugs
	// Register our connection
	Communication::Register("keyboard", "The Keyboard driver and server");
	Socket& commSocket = Communication::CreateSocket("KeyEvents");

	commSocket.AddRemoteMethod(void, unsigned int);
	try
	{
		UNUSED Plug* plug = new Plug(commSocket);
		
	}
	catch(IPCSetupException &e)
	{
		Debug::WriteDebugMsg("An error occurred while registering the socket!");
		return -1;
	}

	KeyboardHandler* kbh = new KeyboardHandler(commSocket, barrier);
	kbh->InitDriver();

	while(true)
	{
		Thread::Sleep();
	}

	return 0;
}
