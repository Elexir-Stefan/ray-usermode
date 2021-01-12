#include <raykernel.h>
#include <exception>
#include <video/VideoStream.h>

using namespace Kernel;
using namespace std;

class TestException : public exception
{
	public:
		TestException(const char *message)
		{
			this->msg = message;
		}
		
		const char *GetMessage()
		{
			return this->msg;
		}
	private:
		const char *msg;
};

void DoSomething() throw(TestException)
{
	throw TestException("TestException successful");
}

int UserProgramEntry(const char *arguments)
{
	kout << "Hello, world from C++!" << VideoStream::endl;
	kout << "Supplied argument is: " << arguments << VideoStream::endl;
	
	try
	{
		DoSomething();
	}
	catch (TestException& e)
	{
		kout << "An error occured: \"" << e.GetMessage() << "\"" << VideoStream::endl;
	}
	
	return 0;
}
