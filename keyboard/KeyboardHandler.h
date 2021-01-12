/*
 * KeyboardHandler.h
 *
 *  Created on: May 9, 2010
 *      Author: stefan
 */

#ifndef KEYBOARDHANDLER_H_
#define KEYBOARDHANDLER_H_

#include <rdm/rdm.h>
#include <ipc/ipc.h>
#include <processes/processes.h>

class KeyboardHandler: public Kernel::RDM::IRQHandler {
public:
	KeyboardHandler(Kernel::IPC::Socket& socket, Kernel::Processes::Sync& barrier);
	void InitDriver();
	void HandleIRQ();

	void CaughtException(Kernel::Exception& ex);
	virtual ~KeyboardHandler();

private:
	void NotifyObservers(UINT32 keyCode);

	Kernel::IPC::Socket& socket;
	Kernel::Processes::Sync& barrier;
	Kernel::IPC::CABLE_USER* cableList[128];


};

#endif /* KEYBOARDHANDLER_H_ */
