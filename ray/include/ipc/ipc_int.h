#ifndef IPC_INT_H
#define IPC_INT_H

#include <ray/typedefs.h>
#include <processes/privileges.h>
#include <processes/arguments.h>
#include <rayexception.h>
#include <list>
#include <vector>
#include <typeinfo>

#include <stdarg.h>
#include <string.h>

#define NewType(baseType, newType) typedef union {baseType Value; UINT32 CastIntValue; UINT8 GetByte[4];} newType;
#define ConvertToMSGCALL(returnType, funcPtr, arguments...) Kernel::IPC::Socket::RegisterFunction(#returnType,  #arguments , (void*)&funcPtr, ((returnType (*)(arguments))&funcPtr == funcPtr))
#define ConvertToRemoteMSGCALL(returnType, arguments...) Kernel::IPC::Socket::RegisterFunction(#returnType,  #arguments , NULL, true)
#define AddLocalCallback(returnType, funcPtr, arguments...) _AddLocalCallback(ConvertToMSGCALL(returnType, funcPtr, arguments), &typeid(returnType(*)(arguments)))
#define AddRemoteMethod(returnType, arguments...) _AddRemoteMethod(ConvertToRemoteMSGCALL(returnType, arguments), &typeid(returnType(*)(arguments)))

typedef struct {
	
} _IPCMessage;


namespace Kernel {
namespace IPC {
	
	typedef UINT32 RMISERIAL;
	NewType(UINT32, RMIFUNCTION);

	typedef enum {
		RTYPE_UINT8 = 1,
		RTYPE_SINT8 = 2,
		RTYPE_UINT16 = 3,
		RTYPE_SINT16 = 4,
		RTYPE_UINT32 = 5,
		RTYPE_SINT32 = 6,
		RTYPE_FLOAT = 7,
		RTYPE_CHAR = 8,
		RTYPE_STRING = 9,
		RTYPE_VOID = 10,
		RTYPE_MEM = 11,
	} PACKED MSG_TYPE;

	typedef struct {
		MSG_TYPE type;
		UINT32 maxSize;
	} PACKED MSG_PARAM;
	
	typedef struct {
		RMISERIAL destinationSerial;
		RMIFUNCTION* destinationFunctionNumbers;
	} CABLE_USER;

	typedef struct {
		void *entryPoint;
		MSG_PARAM* parameters;
		UINT32 paramCount;
		MSG_PARAM returnValue;
	} PACKED MSG_CALL_USER;

	typedef struct {
		UINT32 numRegisteredFuncs;
		MSG_CALL_USER* functions;
		PRIVLEVEL minPriv;
		BOOL partnership;
	} PACKED CALLBACKS_USER;

	typedef struct _IPSOCKET_USER{
		CString socketName;					/// Public name of the socket (must only be unique within the application)
		CALLBACKS_USER expectedRemoteFunctions;	/// List of functions the socket expects the other process to offer
		CALLBACKS_USER localCallbacks;			/// List of functions (and their parameters and return types) the socket offers
		PRIVLEVEL minNeeded;				/// The minimum privilege level the other process must have
		BOOL forcePairing;					/// Disable use of this socket for unauthenticated processes
	} PACKED IPSOCKET_USER;

	/**
	* Possible return values for Remote Method Invokation
	*/
	typedef enum {
		RMI_SUCCESS = 0,			/**< everything is OK */
		RMI_EXPORT_NOT_FOUND = 1,	/**< There is no function with that number registered at the receiver's thread */
		RMI_TRANSMIT_ERROR = 2,		/**< General error concerning method invocation */
		RMI_GEN_ERROR = 3,			/**< An unknown error occurred */
		RMI_WRONG_SETUP = 4,		/**< Too many functions exported for current RMISetup */
		RMI_NO_SETUP = 5,			/**< Must be initialized with RMISetup first! */
		RMI_NO_SERIAL = 6,			/**< Sender has not set up RMI! */
		RMI_INSUFF_RIGHTS = 7,		/**< Insufficient rights to send a message to that thread */
		RMI_NOT_SUPPORTED = 8,		/**< Remote thread has not set up RMI */
		RMI_OCCUPIED = 9,			/**< Exported function number already in use */
		RMI_OVERLOAD = 10,			/**< Calling remote thread would cause stack problems at remote thread */
		RMI_OUT_OF_MEMORY = 11,		/**< Out of memory */
		RMI_ARGUMENT_COUNT_MISMATCH = 12,
		RMI_ARGUMENT_TYPE_MISMATCH = 13,
		RMI_ARGUMENT_SIZE_MISMATCH = 14,
		RMI_INCOMPATIBLE = 15,
		RMI_ARGUMENT_NO_GIFT = 16,
		RMI_INVALID_PROCESS = 17,
		RMI_DOUBLE_CABLE = 18,
		RMSG_INVALID_BUFFER = 20,
		RMSG_INVALID_HANDLE = 21,
		RMSG_OWNERSHIP_ERROR = 22,
		RMSG_SAME_TYPE_NEEDS_MEM = 23

	} RAY_RMI;
	
	enum CommFailureReason {
		ArgumentCountMismatch,
		InsufficientRights,
		ExportNotFound,
		NotSupported,
		UnknownRemoteProcess,
		NotInIPCTask,
		UnknownCommFailure
	};
	
	enum SetupFailureReason {
		Occupied,
		AlreadyInUse,
		UnknownType,
		NotRegistered,
		AlreadRegistered,
		OutOfMemory,
		OutOfRange,
		ProcessDoesNotExist,
		Incompatible,
		WrongSetup,
		NoSuchSocket,
		UnknownSetupFailure
	};
	
	class IPCCommException : public Exception
	{
		public:
			IPCCommException(CommFailureReason reason);
			CommFailureReason GetReason();
		private:
			CommFailureReason reason;
	};
	
	class IPCSetupException : public Exception
	{
		public:
			IPCSetupException(SetupFailureReason reason);
			SetupFailureReason GetReason();
		private:
			SetupFailureReason reason;
	};
	
	
	template<class T>
	class RemoteMethod
	{
		
		public:
			RemoteMethod(MSG_CALL_USER* method, int functionNumber, CABLE_USER* cable);
			~RemoteMethod();
			
			T operator()(unsigned int first, ...);
			T operator()(unsigned short first, ...);
			T operator()(unsigned char first, ...);
			T operator()(signed int first, ...);
			T operator()(signed short first, ...);
			T operator()(signed char first, ...);
			T operator()(float first, ...);
			T operator()(char* first, ...);
			
			void UseBlocking(BOOL block);
			friend class Plug;
		private:
			MSG_CALL_USER* method;
			BOOL blocking;
			int functionNumber;
			
			CABLE_USER* cable;
	};
	
	class Socket
	{
		protected:
			Socket(CString socketName, PRIVLEVEL minPriv = PRIV_PRIORITY, BOOL forcePair = FALSE);
			
			void Create();
			
		public:	
			~Socket();
			
			static MSG_CALL_USER* RegisterFunction(const char* returnType, const char* parameters, void* funcPtr, bool isTrue);
			std::list<CABLE_USER*>& GetAllCables();
			UINT32 GetAllCablesRaw(CABLE_USER** cableList);
			void _AddLocalCallback(MSG_CALL_USER* signature, const std::type_info* cppSignature);
			void _AddRemoteMethod(MSG_CALL_USER* signature, const std::type_info* cppSignature);
			
			friend class Communication;
			friend class Plug;
		private:
			typedef struct {
				MSG_CALL_USER* internalSignature;
				const std::type_info* cppSignature;
			} FunctionSignature;
			
			static UINT32 GetAllCables(CString cableName, CABLE_USER** cableList);
			static CABLE_USER* GetCurrentCable() throw (IPCCommException);
			static void CreateFunctionList(CALLBACKS_USER* callbacks, std::vector<FunctionSignature*> *funcList);
			static BOOL GetNextType(const char* typeList, UINT32& searchStart, UINT32& typeStart, UINT32& typeLength);
			static void GetType(MSG_PARAM *param, const char* str, UINT32 start, UINT32 length) throw(IPCSetupException);
			
			bool isRegistered;
			int remoteMethodIndex;
			std::vector<FunctionSignature*> localCallbacks;
			std::vector<FunctionSignature*> remoteMethods;
			IPSOCKET_USER socket;
			
			CABLE_USER* userCables[128];

			bool created;
	};
	
	/**
	 * Represents a connected socket to a remote socket (in another thread)
	 */
	class Plug
	{
		public:
			Plug(Socket& socket);
			Plug(Socket& socket, CABLE_USER* cable);
			Plug(Socket& socket, CString remoteWall, CString remoteSocket);

			static Plug& GetCurrentPlug(Socket& socket);
			~Plug();
			
			UINT32 NumLocalCallbacks;
			UINT32 NumRemoteMethods;
			
			const std::type_info& GetLocalType(UINT32 index);
			
			template<class T>
			RemoteMethod<T>& GetRemoteMethod(UINT32 index);
			
		private:
			Socket& socket;
			CABLE_USER* cable;
	};
	
	class Communication
	{
		public:
			static void Register(CString wallName, CString description) throw(IPCSetupException);
			static UINT32 InvokeRemote(ARGUMENTS args, RMISERIAL serial, RMIFUNCTION func, BOOL blocking) throw(IPCCommException);
			static Socket& CreateSocket(CString socketName, PRIVLEVEL minPriv = PRIV_PRIORITY, BOOL forcePair = FALSE);
			static void PlugInto(Socket& socket, CString remoteWall, CString remoteSocket, CABLE_USER** cable);
			
			friend class Plug;
		private:
			static void RegisterSocket(Socket& socket) throw (IPCSetupException);
			static bool SocketRegistered(Socket& socket);
			static CString _wallName ;
			static bool isRegistered;
			
			static std::list<Socket*> registeredSockets;
			
			
	};
	
	class Memory
	{
		public:
			Memory();
			
			static void* AllocateMessageBuffer(UINT32 size, MSG_TYPE type);
			static BOOL FreeMessageBuffer(void* size);
	};

	#include "methodtemplate.h"
}
}



#endif
