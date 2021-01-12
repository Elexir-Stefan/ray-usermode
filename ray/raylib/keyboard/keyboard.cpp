/**
 * @file keyboard.cpp
 *
 * @date Jun 5, 2010
 * @author stefan
 * @brief (summary)
 */

#include <raykernel.h>
#include <keyboard/keyboard.h>
#include <processes/processes.h>

#include "../../commondrivers/keyboard/barrier.h"

using namespace Keyboard;
using namespace Kernel::IPC;
using namespace Kernel::Processes;


bool KeyEvent::globalListenerLock = false;
Kernel::IPC::Socket* KeyEvent::keyboardSocket;
Kernel::Processes::Sync* KeyEvent::sync;
UINT32 KeyEvent::savedValue = 0;

void KeyEvent::KeyEventCallback(UINT32 keyCode)
{
	KeyEvent::savedValue = keyCode;

	KeyEvent::sync->Go(FALSE);
	KeyEvent::sync->Close();
}

/**
 * Constructor of KeyEvent
 * Registers itself as listener
 * @return
 */
KeyEvent::KeyEvent()
{
	// Class cannot be instantiated twice per process
	if (KeyEvent::globalListenerLock) {
		throw KeyboardException();
	}

	KeyEvent::globalListenerLock = true;

	keyboardSocket = &Communication::CreateSocket("keyboardCallback");
	keyboardSocket->AddLocalCallback(void, KeyEvent::KeyEventCallback, unsigned int);

	// Wait before plugging in
	Sync waitForKeyboardHandler = Sync(KEYBOARD_BARRIER);
	waitForKeyboardHandler.Arrive();

	// Plug it in!
	UNUSED Plug* plug = new Plug(*keyboardSocket, "keyboard", "KeyEvents");

	// And create a barrier to notify key events
	KeyEvent::sync = new Sync("KeyEventSync", FALSE);
}

UINT32 KeyEvent::GetRawInputKey()
{
	UINT32 value;
	// Wait, before we continue
	KeyEvent::sync->Arrive();
	value = KeyEvent::savedValue;

	return value;
}

KeyState KeyEvent::GetKey()
{
	return KeyState(GetRawInputKey());
}

KeyState::KeyState(UINT32 keyCode)
:ContainsKey((keyCode & 0xFFFF) != 0),
 KeyOnly(Key(keyCode)),
 Modifier(KeyModifier(keyCode))
{

}

KeyModifier::KeyModifier(UINT32 keyCode)
:Shift(keyCode & AddKeysSHIFT),
 Alt(keyCode & AddKeysALT),
 Ctrl(keyCode & AddKeysCTRL)
{

}

Key::Key(UINT32 keyCode)
: RawCharacter(keyCode & 0xFF),
  RawKey(keyCode & 0xFFFF),
  IsCharacter(
		  ((RawKey >= 'a') && (RawKey <= 'z')) ||
		  ((RawKey >= 'A') && (RawKey <= 'Z')) ||
		  ((RawKey >= '0') && (RawKey <= '9')) ||
		  (RawKey == ' ') ||
		  (RawKey == '.') ||
		  (RawKey == ';') ||
		  (RawKey == '-') ||
		  (RawKey == '_') ||
		  (RawKey == '!') ||
		  (RawKey == '"') ||
		  (RawKey == '$') ||
		  (RawKey == '%') ||
		  (RawKey == '*') ||
		  (RawKey == '+') ||
		  (RawKey == '\'') ||
		  (RawKey == '#') ||
		  (RawKey == '=') ||
		  (RawKey == '~') ||
		  (RawKey == '&')
		  ),
  IsReturn((RawKey == SP_KEY_RETURN) || (RawKey == SP_KEY_RETURN2)),
  IsBackspace(RawKey == SP_KEY_BACKSPACE),
  isUpArrow(RawKey == SP_KEY_ARR_UP),
  isDownArrow(RawKey == SP_KEY_ARR_DN),
  isLeftArrow(RawKey == SP_KEY_ARR_LT),
  isRightArrow(RawKey == SP_KEY_ARR_RT),
  isHome(RawKey == SP_KEY_HOME),
  isEnd(RawKey == SP_KEY_END),
  isPgUp(RawKey == SP_KEY_PGUP),
  isPgDn(RawKey == SP_KEY_PGDN),
  isInsert(RawKey == SP_KEY_INS),
  isDelete(RawKey == SP_KEY_DEL)
{

}

