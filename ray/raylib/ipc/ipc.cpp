#include <raykernel.h>
#include <ipc/ipc_int.h>
#include <syscall.h>
#include <ray/sct.h>
#include <cstring>
#include <list>
#include <string.h>

#define MatchType(type) (strncmp(str + start, type, length) == 0)


using namespace Kernel::IPC;

	/* ******************* IPCSetupException *********************** */

	IPCSetupException::IPCSetupException(SetupFailureReason reason)
	{
		this->reason = reason;
	}
	
	SetupFailureReason IPCSetupException::GetReason()
	{
		return this->reason;
	}

	/* ******************* IPCCommException *********************** */

	IPCCommException::IPCCommException(CommFailureReason reason)
	{
		this->reason = reason;
	}

	CommFailureReason IPCCommException::GetReason()
	{
		return this->reason;
	}

	/* ******************* Communication *********************** */
	
	/**
	* Static variables
	*/
	CString Communication::_wallName = NULL;
	bool Communication::isRegistered = false;
	std::list<Socket*> Communication::registeredSockets;
	
	/**
	* Static registration function for IPC. Only one IPC per process
	* is allowed.
	* @param wallName Name of the "wall" were the sockets
	* will be plugged into.
	*/
	void SYSTEM Communication::Register(CString wallName, CString description) throw(IPCSetupException)
	{
		RAY_RMI result;
		SysCall(SCT::IPC::CreateWall, &wallName, result);
		
		switch(result)
		{
			case RMI_SUCCESS:
				// Copy the name to a local variable
				_wallName = wallName;
				isRegistered = true;
				return;
			case RMI_OCCUPIED:
				throw IPCSetupException(Occupied);
			case RMI_WRONG_SETUP:
				throw IPCSetupException(AlreadyInUse);
			default:
				throw IPCSetupException(UnknownSetupFailure);
		}
	}
	
	UINT32 Communication::InvokeRemote(ARGUMENTS args, RMISERIAL serial, RMIFUNCTION func, BOOL blocking) throw(IPCCommException)
	{
		UINT32 resultValue = 0;
		UINT32 parameters[] = {(UINT32)serial, (UINT32)func.Value, args.count, (UINT32)args.values, (UINT32)blocking, (UINT32)&resultValue};
		
		RAY_RMI result;
		SysCall(SCT::IPC::CallMethod, parameters, result);
		switch(result)
		{
			case RMI_SUCCESS:
				return resultValue;
			case RMI_ARGUMENT_COUNT_MISMATCH:
				throw IPCCommException(ArgumentCountMismatch);
			case RMI_INSUFF_RIGHTS:
				throw IPCCommException(InsufficientRights);
			case RMI_EXPORT_NOT_FOUND:
				throw IPCCommException(ExportNotFound);
			case RMI_NOT_SUPPORTED:
				throw IPCCommException(NotSupported);
			case RMI_NO_SERIAL:
				throw IPCCommException(UnknownRemoteProcess);
			default:
				throw IPCCommException(UnknownCommFailure);
				
		}
	}
	
	bool Communication::SocketRegistered(Socket& socket)
	{
		for(std::list<Socket*>::iterator it = registeredSockets.begin(); it != registeredSockets.end(); it++)
		{
			if (*it == &socket)
			{
				return true;
			}
		}
		
		return false;
	}
	
	void Communication::RegisterSocket(Socket& socket) throw (IPCSetupException)
	{
		if (!SocketRegistered(socket))
		{
			IPSOCKET_USER* userSocket = &socket.socket;
			
			RAY_RMI result;
			SysCall(SCT::IPC::CreateSocket, &userSocket, result);
			switch(result)
			{
				case RMI_SUCCESS:
					registeredSockets.push_back(&socket);
					return;
				case RMI_OUT_OF_MEMORY:
					throw IPCSetupException(OutOfMemory);
				case RMI_OCCUPIED:
					throw IPCSetupException(AlreadyInUse);
				default:
					throw IPCSetupException(UnknownSetupFailure);
			}
			
			
		}
	}
	
	void Communication::PlugInto(Socket& socket, CString remoteWall, CString remoteSocket, CABLE_USER** cable)
	{
		UINT32 arguments[] = {(UINT32)socket.socket.socketName, (UINT32)remoteSocket, (UINT32)remoteWall, (UINT32)cable};
		RAY_RMI result;
		
		SysCall(SCT::IPC::PlugByName, arguments, result);
		switch(result)
		{
			case RMI_SUCCESS:
				return;
			case RMI_INCOMPATIBLE:
				throw IPCSetupException(Incompatible);
			case RMI_EXPORT_NOT_FOUND:
				throw IPCSetupException(NoSuchSocket);
			case RMI_WRONG_SETUP:
				throw IPCSetupException(WrongSetup);
			case RMI_INVALID_PROCESS:
				throw IPCSetupException(ProcessDoesNotExist);
			default:
				throw IPCSetupException(UnknownSetupFailure);
		}
	}
	
	/* ******************* Socket *********************** */
	
	
	
	Socket::Socket(CString socketName, PRIVLEVEL minPriv, BOOL forcePair)
	: remoteMethodIndex(0)
	{
		this->isRegistered = false;
		this->created = false;
		
		this->socket.socketName = socketName;
		this->socket.forcePairing = forcePair;
		this->socket.minNeeded = minPriv;
		
	}
	
	Socket& Communication::CreateSocket(CString socketName, PRIVLEVEL minPriv, BOOL forcePair)
	{
		if (!isRegistered)
		{
			throw IPCSetupException(NotRegistered);
		}
		
		Socket* socket = new Socket(socketName, minPriv, forcePair);
		
		return *socket;
	}
	
	BOOL Socket::GetNextType(const char* typeList, UINT32& searchStart, UINT32& typeStart, UINT32& typeLength)
	{
		char currChar;
		BOOL beginFound = FALSE;
		typeStart = searchStart;
		typeLength = 0;
		while((currChar = typeList[searchStart++]))
		{
			if (currChar == ' ')
			{
				// Space is either at front or end
				if (!beginFound)
				{
					// Space is at front
					typeStart++;
				}
			}
			else if (currChar == ',')
			{
				return TRUE;
			}
			else
			{
				beginFound = TRUE;
				typeLength++;
			}
		}
		// reached end of string
		return FALSE;
	}
	
	void Socket::GetType(MSG_PARAM *param, const char* str, UINT32 start, UINT32 length) throw(IPCSetupException)
	{
		if (MatchType("int"))
		{
			param->type = RTYPE_SINT32;
			param->maxSize = 4;
		}
		else if (MatchType("unsigned int"))
		{
			param->type = RTYPE_UINT32;
			param->maxSize = 4;
		}
		else if (MatchType("short"))
		{
			param->type = RTYPE_SINT16;
			param->maxSize = 2;
		}
		else if (MatchType("unsigned short"))
		{
			param->type = RTYPE_UINT16;
			param->maxSize = 2;
		}
		else if (MatchType("unsigned char"))
		{
			param->type = RTYPE_UINT8;
			param->maxSize = 1;
		}
		else if (MatchType("float"))
		{
			param->type = RTYPE_FLOAT;
			param->maxSize = 4;
		}
		else if (MatchType("char"))
		{
			param->type = RTYPE_CHAR;
			param->maxSize = 1;
		}
		else if (MatchType("char *"))
		{
			param->type = RTYPE_STRING;
			param->maxSize = 99999999;
		}
	        else if (MatchType("void"))
		{
			param->type = RTYPE_VOID;
			param->maxSize = 0;
		}
		else
		{
			param->type = RTYPE_MEM;
			param->maxSize = 9999999;
		}
	}
	
	MSG_CALL_USER* Socket::RegisterFunction(const char* returnType, const char* parameters, void* funcPtr, bool isTrue)
	{
		UINT32 start = 0;
		UINT32 typeStart, typeLength;
		UINT32 retStart, retLength;
		
		if (!isTrue)
		{
			throw IPCSetupException(Incompatible);
		}
		
		// Create MSG_CALL_USER type
		MSG_CALL_USER* msgCall = new MSG_CALL_USER;
		
		// And save return value's type and size
		GetNextType(returnType, start, retStart, retLength);
		GetType(&msgCall->returnValue, returnType, retStart, retLength);
		
		// Initialize the rest of the structure
		msgCall->parameters = new MSG_PARAM[32];
		msgCall->paramCount = 0;
		msgCall->entryPoint = funcPtr;
		
		// And get the types of the arguments
		start = 0;
		BOOL lastType;
		do{
			lastType = GetNextType(parameters, start, typeStart, typeLength);
			GetType(msgCall->parameters + msgCall->paramCount++, parameters, typeStart, typeLength);
		} while(lastType);
		
		return msgCall;
	}
	
	void Socket::_AddLocalCallback(MSG_CALL_USER* signature, const std::type_info* cppSignature)
	{
		FunctionSignature* sig = new FunctionSignature();
		sig->internalSignature = signature;
		sig->cppSignature = cppSignature;
		
		this->localCallbacks.push_back(sig);
	}
	
	void Socket::_AddRemoteMethod(MSG_CALL_USER* signature, const std::type_info* cppSignature)
	{
		FunctionSignature* sig = new FunctionSignature();
		sig->internalSignature = signature;
		sig->cppSignature = cppSignature;
		
		this->remoteMethods.push_back(sig);
	}
	
	void Socket::CreateFunctionList(CALLBACKS_USER* callbacks, std::vector<FunctionSignature*> *funcList)
	{
		callbacks->numRegisteredFuncs = funcList->size();
		callbacks->functions = new MSG_CALL_USER[callbacks->numRegisteredFuncs];
		callbacks->minPriv = PRIV_PRIORITY;
		callbacks->partnership = FALSE;
		
		int i = 0;
		for(std::vector<FunctionSignature*>::const_iterator it = funcList->begin(); it != funcList->end(); ++it)
		{
			memcpy(callbacks->functions + i++, (*it)->internalSignature, sizeof(MSG_CALL_USER));
		}
		
	}
	
	void Socket::Create()
	{
		if (!this->created)
		{
			CreateFunctionList(&this->socket.expectedRemoteFunctions, &this->remoteMethods);
			CreateFunctionList(&this->socket.localCallbacks, &this->localCallbacks);
			this->created = true;
		}
	}
	
	CABLE_USER* Socket::GetCurrentCable() throw (IPCCommException)
	{
		UINT32 result;
		SysCall(SCT::IPC::GetRMICable, 0, result);

		if (result == 0)
		{
			throw IPCCommException(NotInIPCTask);
		}

		return (CABLE_USER*)result;
	}

	UINT32 Socket::GetAllCables(CString cableName, CABLE_USER** cableList)
	{
		UINT32 result;
		UINT32 parameters[] = {(UINT32)cableName, (UINT32)cableList};
		SysCall(SCT::IPC::GetAllCables, &parameters, result);

		return result;
	}

	UINT32 Socket::GetAllCablesRaw(CABLE_USER** cableList)
	{
		return Socket::GetAllCables(this->socket.socketName, cableList);
	}

	std::list<CABLE_USER*>& Socket::GetAllCables()
	{
		UINT32 count = Socket::GetAllCables(this->socket.socketName, this->userCables);
		std::list<CABLE_USER*>* list = new std::list<CABLE_USER*>(count);

		for(UINT32 i = 0; i < count; i++)
		{
			list->push_back(this->userCables[i]);
		}

		return *list;
	}

	/* ****************************** Plug ****************************/
	
	/**
	 * Creates a plug (connection) from a socket (protocol) and registers
	 * the socket at the kernel. This constructor does not connect
	 * the plug to a remote socket.
	 * @param socket
	 */
	Plug::Plug(Socket& socket)
	: socket(socket)
	{
		socket.Create();
		Communication::RegisterSocket(socket);
	}
	
	/**
	 * Standard constructor that connects a socket to a remote one
	 * by name.
	 */
	Plug::Plug(Socket& socket, CString remoteWall, CString remoteSocket)
	: socket(socket)
	{
		socket.Create();
		
		this->NumLocalCallbacks = socket.socket.localCallbacks.numRegisteredFuncs;
		this->NumRemoteMethods = socket.socket.expectedRemoteFunctions.numRegisteredFuncs;
		
		Communication::RegisterSocket(socket);
		Communication::PlugInto(socket, remoteWall, remoteSocket, &this->cable);
	}
	
	/**
	 * Private constructor that is used to create a usable plug (which can return remote
	 * methods) by providing a cable.
	 * @param socket Socket to use for this plug
	 * @param cable Cable to use for this plug
	 */
	Plug::Plug(Socket& socket, CABLE_USER* cable)
	: socket(socket)
	{
		socket.Create();
		this->NumLocalCallbacks = socket.socket.localCallbacks.numRegisteredFuncs;
		this->NumRemoteMethods = socket.socket.expectedRemoteFunctions.numRegisteredFuncs;

		this->cable = cable;
	}

	Plug& Plug::GetCurrentPlug(Socket& socket)
	{
		Plug* plug = new Plug(socket, Socket::GetCurrentCable());
		return *plug;
	}


	Plug::~Plug()
	{
		
	}
	
	
	const std::type_info& Plug::GetLocalType(UINT32 index)
	{
		if (index < this->NumLocalCallbacks)
		{
			return *this->socket.localCallbacks[index]->cppSignature;
		}
		else
		{
			throw IPCSetupException(OutOfRange);
		}
	}

	/* ************************* Memory ****************************/
	
	Memory::Memory()
	{
		
	}
	
	// Constant, static object
	_IPCMessage IPCMessage;
	
	void* Memory::AllocateMessageBuffer(UINT32 size, MSG_TYPE type)
	{
		UINT32 result;
		SysCall(Kernel::SCT::IPC::AllocateMB, &size, result);
		
		return (void*)result;
	}
	
	BOOL Memory::FreeMessageBuffer(void* pointer)
	{
		UINT32 result;
		SysCall(Kernel::SCT::IPC::FreeMB, &pointer, result);
		
		return (BOOL)result;
	}
	
	
	void* operator new(long unsigned int sizeInBytes, const _IPCMessage& mem)
	{
		return Kernel::IPC::Memory::AllocateMessageBuffer(sizeInBytes, RTYPE_MEM);
	}
	
	void* operator new[](long unsigned int sizeInBytes, const _IPCMessage& mem)
	{
		return Kernel::IPC::Memory::AllocateMessageBuffer(sizeInBytes, RTYPE_MEM);
	}
	
	void operator delete(void* address, const _IPCMessage& mem)
	{
		Kernel::IPC::Memory::FreeMessageBuffer(address);
	}
	
	void operator delete[](void* address, const _IPCMessage& mem)
	{
		Kernel::IPC::Memory::FreeMessageBuffer(address);
	}
	
