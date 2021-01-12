#ifndef IPC_METHOD_TEMPLATE_H
#define IPC_METHOD_TEMPLATE_H


#define OperatorImplementation(first) \
	va_list arguments; \
	va_start(arguments, first); \
	UINT32 i; \
	ARGUMENTS args; \
	args.count = this->method->paramCount; \
	UINT32 array[args.count]; \
	args.values = array; \
	memcpy(args.values, &first, sizeof(UINT32)); \
	for(i = 1; i < args.count; i++) \
	{ \
	args.values[i] = va_arg(arguments, UINT32); \
	} \
	va_end(arguments); \
	return (T)Communication::InvokeRemote(args, this->cable->destinationSerial, this->cable->destinationFunctionNumbers[this->functionNumber], this->blocking);

#define OperatorTypeImpl(type)\
	template <class T> \
	T RemoteMethod<T>::operator()(type first, ...) \
	{ \
	OperatorImplementation(first); \
	}
	
	
	template <class T>
	RemoteMethod<T>& Plug::GetRemoteMethod(UINT32 index)
	{
		if (index < this->NumRemoteMethods)
		{
			RemoteMethod<T>* remote = new RemoteMethod<T>(this->socket.remoteMethods[index]->internalSignature, index, this->cable);
			return *remote;
		}
		else
		{
			throw IPCSetupException(OutOfRange);
		}
		
	}
	
	
	template <class T>
	RemoteMethod<T>::RemoteMethod(MSG_CALL_USER* method, int functionNumber, CABLE_USER* cable)
	{
		this->functionNumber = functionNumber;
		this->method = method;
		this->cable = cable;
		this->blocking = TRUE;
	}
	
	template <class T>
	RemoteMethod<T>::~RemoteMethod()
	{
		// Do not delete the cable - kernel still uses it!
		// delete this->cable;
	}	
	
	template <class T>
	void RemoteMethod<T>::UseBlocking(BOOL block)
	{
		this->blocking = block;
	}

		OperatorTypeImpl(unsigned int);
		OperatorTypeImpl(unsigned short);
		OperatorTypeImpl(unsigned char);
		OperatorTypeImpl(signed int);
		OperatorTypeImpl(signed short);
		OperatorTypeImpl(signed char);
		OperatorTypeImpl(float);
		OperatorTypeImpl(char*);
		
		
		
		
		/*
		template <class T>
		T RemoteMethod<T>::operator()(signed int first, ...) 
		{
			va_list arguments;
			va_start(arguments, first);
			UINT32 i;
			ARGUMENTS args;
			args.count = this->method->paramCount;
			args.values = new UINT32[args.count];
			memcpy(args.values, &first, sizeof(UINT32));
			for(i = 1; i < args.count; i++)
			{
				args.values[i] = va_arg(arguments, UINT32);
			}
			va_end(arguments);
			return (T)Communication::InvokeRemote(args, this->cable->destinationSerial, this->cable->destinationFunctionNumbers[this->functionNumber], this->blocking);
		}
		*/

#endif
