/**
 * @file keyboard.h
 *
 * @date May 29, 2010
 * @author stefan
 * @brief Keyboard handling - Events and string representation.
 */

#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include <raykernel.h>
#include <ipc/ipc_int.h>
#include <processes/processes.h>
#include <list>


namespace Keyboard
{

	static const UINT32 AddKeysCTRL	= 0x10000;
	static const UINT32 AddKeysALT = 0x20000;
	static const UINT32 AddKeysSHIFT = 0x40000;

// Special keys, no characters
// Ctrl, Alt, Shift, but no other keys pressed
	static const UINT32 SP_KEY_NONE = 0;
	static const UINT32 SP_KEY_TAB = 9;
	static const UINT32 SP_KEY_BACKSPACE = 10;
	static const UINT32 SP_KEY_RETURN = 13;
	static const UINT32 SP_KEY_RETURN2 = 269;
	static const UINT32 SP_KEY_ARR_UP = 328;
	static const UINT32 SP_KEY_ARR_DN = 336;
	static const UINT32 SP_KEY_ARR_LT = 331;
	static const UINT32 SP_KEY_ARR_RT = 333;
	static const UINT32 SP_KEY_INS = 270;
	static const UINT32 SP_KEY_DEL = 271;
	static const UINT32 SP_KEY_HOME = 0x110;
	static const UINT32 SP_KEY_END = 0x111;
	static const UINT32 SP_KEY_PGUP= 0x112;
	static const UINT32 SP_KEY_PGDN= 0x113;

	class KeyEvent;

	class KeyboardException : public Kernel::Exception
	{

	};

	class KeyModifier
	{
	public:
		KeyModifier(UINT32 keyCode);
		bool Shift;
		bool Alt;
		bool Ctrl;
	};

	class Key
	{
	public:
		Key(UINT32 keyCode);
		char RawCharacter;
		UINT16 RawKey;

		bool IsCharacter;

		bool IsReturn;
		bool IsBackspace;
		bool isUpArrow;
		bool isDownArrow;
		bool isLeftArrow;
		bool isRightArrow;
		bool isHome;
		bool isEnd;
		bool isPgUp;
		bool isPgDn;
		bool isInsert;
		bool isDelete;

	};

	class KeyState
	{
	public:
		KeyState(UINT32 keyCode);

		bool ContainsKey;
		Key KeyOnly;
		KeyModifier Modifier;
	};

	class KeyEvent
	{
	public:
		KeyEvent();

		UINT32 GetRawInputKey();
		KeyState GetKey();
	private:
		static void KeyEventCallback(UINT32 keyCode);

		static Kernel::IPC::Socket* keyboardSocket;
		static bool globalListenerLock;
		static Kernel::Processes::Sync* sync;
		static UINT32 savedValue;
	};

}

#endif /* KEYBOARD_H_ */
