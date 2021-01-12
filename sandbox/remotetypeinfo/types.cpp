#include <iostream>
#include <typeinfo>
#include <raykernel.h>
#include <ipc/ipc.h>
#include <string.h>
#include <stdarg.h>


using namespace std;

#define IPCCallback(returnType, funcPtr, arguments...) RegisterFunction(#returnType,  #arguments , (void*)&funcPtr, ((returnType (*)(arguments))&funcPtr == funcPtr))
#define IPCFunction(returnType, arguments...) RegisterFunction(#returnType,  #arguments , NULL, true)
#define MatchType(type) (strncmp(str + start, type, length) == 0)

#define OperatorImplementation(first) \
va_list arguments; \
va_start(arguments, first); \
UINT32 i; \
ARGUMENTS args; \
args.count = this->method->paramCount; \
args.values = new UINT32[args.count]; \
memcpy(args.values, &first, sizeof(UINT32)); \
for(i = 1; i < args.count; i++) \
{ \
	args.values[i] = va_arg(arguments, UINT32); \
} \
va_end(arguments); \
return (T)IPC::InvokeRemote(args, this->cable->destinationSerial, this->cable->destinationFunctionNumbers[this->functionNumber], this->blocking);

#define OperatorTypeImpl(type)\
template <class T> \
T RemoteMethod<T>::operator()(type first, ...) \
{ \
	OperatorImplementation(first); \
}


using namespace Kernel::IPC;

char TestFunction(int arg2, float arg3)
{
		cout << "This function worked properly! " << arg2 << " (" << arg3 << ")" << endl;
		
		return 1.4142;
}

BOOL GetNextType(const char* typeList, UINT32& searchStart, UINT32& typeStart, UINT32& typeLength)
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

void PrintSubString(const char* str, UINT32 start, UINT32 length)
{
	cout << "'";
	UINT32 i = start;
	while(i < start + length) {
		cout << str[i++];
	}
	cout << "'" << endl;
}

void GetType(MSG_PARAM *param, const char* str, UINT32 start, UINT32 length)
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
	else
	{
		cout << "unknown type" << endl;
		PrintSubString(str, start, length);
	}
}

MSG_CALL_USER* RegisterFunction(const char* returnType, const char* parameters, void* funcAddress, bool isTrue)
{
	UINT32 start = 0;
	UINT32 typeStart, typeLength;
	UINT32 retStart, retLength;
	
	// Create MSG_CALL_USER type
	MSG_CALL_USER* msgCall = new MSG_CALL_USER;
	
	// And save return value's type and size
	GetNextType(returnType, start, retStart, retLength);
	GetType(&msgCall->returnValue, returnType, retStart, retLength);
	
	// Initialize the rest of the structure
	msgCall->parameters = new MSG_PARAM[32];
	msgCall->paramCount = 0;
	msgCall->entryPoint = funcAddress;
	
	// And get the types of the arguments
	start = 0;
	BOOL lastType;
	do{
		lastType = GetNextType(parameters, start, typeStart, typeLength);
		GetType(msgCall->parameters + msgCall->paramCount++, parameters, typeStart, typeLength);
	} while(lastType);
	
	return msgCall;
}

void Socket::AddLocalCallback(MSG_CALL_USER* signature)
{
	this->localCallbacks->push_back(signature);
}

template <class T>
RemoteMethod<T>& Socket::AddRemoteMethod(MSG_CALL_USER* signature)
{
	RemoteMethod<T>* remote = new RemoteMethod<T>(signature, this->remoteMethodIndex++);
	this->remoteMethods->push_back(signature);
	
	return *remote;
}

void Socket::CreateFunctionList(CALLBACKS_USER* callbacks, std::list<MSG_CALL_USER*> *funcList)
{
	callbacks->numRegisteredFuncs = funcList->size();
	callbacks->functions = new MSG_CALL_USER[callbacks->numRegisteredFuncs];
	callbacks->minPriv = PRIV_PRIORITY;
	callbacks->partnership = FALSE;
	
	int i = 0;
	for(list<MSG_CALL_USER*>::const_iterator it = funcList->begin(); it != funcList->end(); ++it)
	{
		memcpy(callbacks->functions + i++, *it, sizeof(MSG_CALL_USER));
	}
	
}

IPSOCKET_USER* Socket::Create()
{
	CreateFunctionList(&this->socket.expectedRemoteFunctions, this->remoteMethods);
	CreateFunctionList(&this->socket.localCallbacks, this->localCallbacks);
	return &this->socket;
}

template <class T>
RemoteMethod<T>::RemoteMethod(MSG_CALL_USER* method, int functionNumber)
{
	this->functionNumber = functionNumber;
	this->method = method;
	this->cable = new CABLE_USER;
}

template <class T>
RemoteMethod<T>::~RemoteMethod()
{
	delete this->cable;
}

OperatorTypeImpl(unsigned int);
OperatorTypeImpl(unsigned short);
OperatorTypeImpl(unsigned char);
OperatorTypeImpl(signed int);
OperatorTypeImpl(signed short);
OperatorTypeImpl(signed char);
OperatorTypeImpl(float);
OperatorTypeImpl(char*);

UINT32 IPC::InvokeRemote(ARGUMENTS args, RMISERIAL serial, RMIFUNCTION func, BOOL blocking)
{
	// TODO: To be filled in
	cout << "Invoking remote method #" << serial << "[" << func.Value << "]" << " -- (";
	
	for(int i = 0; i < args.count; i++) {
		cout << args.values[i]  << ", ";
	}
	
	cout << ")" << endl;
	return 0;
}

template <class T>
void RemoteMethod<T>::UseBlocking(BOOL block)
{
	this->blocking = block;
}

Socket::Socket(CString socketName, PRIVLEVEL minPriv, BOOL forcePair)
: remoteMethodIndex(0)
{
	this->isRegistered = false;
	
	this->socket.socketName = socketName;
	this->socket.forcePairing = forcePair;
	this->socket.minNeeded = minPriv;
	
	this->remoteMethods = new list<MSG_CALL_USER*>();
	this->localCallbacks = new list<MSG_CALL_USER*>();
}

int main(int argc, char* argv[]) 
{

	Socket* socket = new Socket("verbindung");
	socket->AddLocalCallback(IPCCallback(char, TestFunction, int, float));
	RemoteMethod<char>& remote = socket->AddRemoteMethod<char>(IPCFunction(char, int, int));
	
	UNUSED IPSOCKET_USER* bla = socket->Create();
	
	CABLE_USER* cable = new CABLE_USER;
	
	cable->destinationSerial = 123456;
	cable->destinationFunctionNumbers = new RMIFUNCTION[5];
	cable->destinationFunctionNumbers[0].Value = 666;
	
	remote.cable = cable;
	
	char r = remote(24,555);

	return r;
}
