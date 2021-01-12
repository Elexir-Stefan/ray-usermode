#include <raykernel.h>
#include <exception>
#include <video/VideoStream.h>
#include <processes/processes.h>
#include <ipc/ipc.h>
#include <sstream>


using namespace Kernel;
using namespace Kernel::IPC;
using namespace Kernel::Processes;

/**
* TestFunction used as callback
*/
int TestFunction(int arg2, float arg3)
{
	kout << "This function worked properly! " << arg2 << VideoStream::endl;
	
	return 666;
}

char* ToString(int number, char* result)
{
	
	
	char* nPtr = result + strlen(result);
	
	std::ostringstream sin;
	sin << number;
	strcpy(nPtr, sin.str().c_str());
	
	
	
	return result;
}

float AnotherTestFunction(char arg1, int arg2, int arg3)
{
	kout << "This is another test function -- " << arg2 << " (" << arg3 << ")" << VideoStream::endl;
	
	return 1.4142f;
}

int UserProgramEntry(const char *arguments)
{
	try
	{
		Sync waitForOther = Sync("dingsbums", TRUE);
		
		
		// Register our connection
		Communication::Register("andererProzess", "Wartet auf eine Verbindung");
		
		Socket& socket = Communication::CreateSocket("dessenSocket");
		socket.AddLocalCallback(int, TestFunction, int, float);
		socket.AddLocalCallback(char*, ToString, int, char*);
		
		socket.AddRemoteMethod(char, int, float);
		socket.AddRemoteMethod(float, char, int, int);

		try
		{
			UNUSED Plug* plug = new Plug(socket);
			waitForOther.Go(TRUE);
		}
		catch(IPCSetupException &e)
		{
			kout << "An error occured while registering the socket!" << VideoStream::endl;
		}
		
		
		Thread::Sleep();
		
		// never reaches this point...
		return 0;
	}
	catch (IPCSetupException &e)
	{
		kout << "An error occured while setting up the communication wall." << VideoStream::endl;
		
		return -1;
	}
}
