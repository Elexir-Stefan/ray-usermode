#include <raykernel.h>
#include <exception>
#include <keyboard/keyboard.h>
#include <video/VideoStream.h>
#include <video/KernelVideo.h>

#include "Command.h"

using namespace Kernel;
using namespace std;
using namespace Keyboard;
using namespace Kernel::IPC;

const UINT32 CmdBufferSize = 32;



void InsertString(std::list<String>& list)
{
	// Only isert, when last position is not empty
	if ((list.empty()) || (strlen(list.back())) > 0)
	{
		String newString = new char[256];
		memset(newString, 0, 256);
		list.push_back(newString);
	}
}

void DisplayString(String s)
{
	KernelVideo::WriteUnformattedString("\r>                                                                              ");
	KernelVideo::WriteUnformattedString("\r>");
	KernelVideo::WriteUnformattedString(s);
}

std::list<String>::iterator DeleteUnused(std::list<String>::iterator it, std::list<String>& list)
{
	if (strlen(*it) == 0)
	{
		delete *it;
		return list.erase(it);
	} else {
		return it;
	}
}

void GetUserInput()
{
	KeyEvent keyEvent = KeyEvent();
	std::list<String> commandBuffer;

	InsertString(commandBuffer);
	std::list<String>::iterator it = commandBuffer.begin();
	UINT32 strPos = 0;
	while(true)
	{
		KeyState keyState = keyEvent.GetKey();


		if (keyState.ContainsKey)
		{
			Key key = keyState.KeyOnly;

			// Arrow keys?
			if (key.isUpArrow || key.isDownArrow)
			{
				if ((key.isUpArrow) && (*it != commandBuffer.front()))
				{
					// there is an element before this, go back one element
					//it = DeleteUnused(it, commandBuffer);
					it--;
				}

				if ((key.isDownArrow) && (*it != commandBuffer.back()))
				{
					// there is an element after this, advance one element
					//it = DeleteUnused(it, commandBuffer);
					it++;
				}
				strPos = strlen(*it);
				DisplayString(*it);
			}
			else if (key.IsReturn)
			{
				// accept string
				if (strlen(*it) > 0)
				{
					kout << VideoStream::endl;
					Command::ExecuteCommand(*it);

					InsertString(commandBuffer);
					strPos = 0;
					it = commandBuffer.end();
					it--;
				}

				kout << VideoStream::endl;
				DisplayString(*it);
			}
			else if (key.IsBackspace)
			{
				if (strPos > 0)
				{
					(*it)[--strPos] = 0;
					DisplayString(*it);
				}
			}
			else if (key.IsCharacter)
			{
				// add the character to the string
				(*it)[strPos++] = key.RawCharacter;
				DisplayString(*it);
			}
			// else do nothing ...



		}
	}
}

int UserProgramEntry(const char *arguments)
{
	// Register our connection
	Communication::Register("Console", "Basic shell application");

	kout << "NURNware Console" << VideoStream::endl;
	kout << ">_";
	GetUserInput();
	return 0;
}
