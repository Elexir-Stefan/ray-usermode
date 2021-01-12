#ifndef __VIDEVideoStream_H__
#define __VIDEVideoStream_H__

namespace Kernel
{

	class VideoStream
	{
		public:
			static const char digits[];
			static const char endl;
			
			VideoStream& operator << (const char *string);
			VideoStream& operator << (const char c);
			VideoStream& operator << (int i);
			VideoStream& operator << (unsigned int i);
			VideoStream& operator << (short i);
			VideoStream& operator << (unsigned short i);
			

		private:
			static UINT8 currRadix;
			
			static void WriteDecimalValue(SINT32 value);
			static void WriteDecimalUValue(UINT32 value);
			static void UIntToString(UINT32 value, char *buffer, UINT8 radix);
	};
		
	extern VideoStream kout;
}

#endif

