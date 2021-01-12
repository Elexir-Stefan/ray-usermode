#include <raykernel.h>
#include <exception>
#include <video/VideoStream.h>
#include <processes/processes.h>
#include <ipc/ipc.h>

using namespace Kernel;
using namespace Kernel::IPC;
using namespace Kernel::Processes;

/**
* TestFunction used as callback
*/
char TestFunction(int arg2, float arg3)
{
	kout << "This is IPC1's function " << arg2 << VideoStream::endl;
	
	return 'g';
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
		// Register our connection
		Communication::Register("Verbindung", "Eine Testverbindung");
		
		Socket& socket = Communication::CreateSocket("testsocket");
		socket.AddLocalCallback(char, TestFunction, int, float);
		socket.AddLocalCallback(float, AnotherTestFunction, char, int, int);
		socket.AddRemoteMethod(int, int, float);
		socket.AddRemoteMethod(char*, int, char*);
		
		// Wait before plugging in
		Sync waitForOther = Sync("dingsbums");
		waitForOther.Arrive();
		Plug* plug = new Plug(socket, "andererProzess", "dessenSocket");
		
		RemoteMethod<int>& remote = plug->GetRemoteMethod<int>(0);
		RemoteMethod<char*>& toString = plug->GetRemoteMethod<char*>(1);
		
		int result = remote(42, 3.1415926f);
		
		kout << "Other thread returned " << result << " as a result." << VideoStream::endl;
		
		char* buffer = ipcnew char[24];
		strcpy(buffer, "String value = ");
		char* string = toString(result, buffer);
		
		kout << "The string constant is: '" << string << "'." << VideoStream::endl;
		
		ipcdelete (string);
		
		return 0;
	}
	catch (IPCSetupException &e)
	{
		kout << "An error occured while setting up the communication wall." << VideoStream::endl;
		
		return -1;
	}
}
