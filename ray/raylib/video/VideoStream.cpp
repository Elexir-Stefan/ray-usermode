#include <raykernel.h>
#include <video/VideoStream.h>
#include <video/KernelVideo.h>

namespace Kernel
{
	
	VideoStream kout;
	
	const char VideoStream::digits[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
	const char VideoStream::endl = '\n';

	VideoStream& VideoStream::operator<<(const char *string)
	{
		KernelVideo::WriteUnformattedString(string);
		return *this;
	}
	
	VideoStream& VideoStream::operator<<(const char c)
	{
		char string[2] = {c, 0};
		KernelVideo::WriteUnformattedString(string);
		return *this;
	}
	
	void VideoStream::UIntToString(UINT32 value, char *buffer, UINT8 radix) {
		int pos = 0;
		do {
			buffer[pos++] = digits[value % radix];
			value /= radix;
		} while(value);
		buffer[pos] = '\0';
		
		// reverse buffer
		char tmp;
		char *front, *end;
		front = buffer;
		end = buffer + pos - 1;
		while(front < end) {
			tmp = *front;
			*front = *end;
			*end = tmp;
			front++;
			end--;
		}
	}
	
	void VideoStream::WriteDecimalUValue(UINT32 value) {
		char buffer[11];	// maximum length (2^32) is 10 digits
		UIntToString(value, buffer, 10);
		KernelVideo::WriteUnformattedString(buffer);
	}
	
	void VideoStream::WriteDecimalValue(SINT32 value) {
		char buffer[12];	// maximum length (2^32) is 10 digits + sign symbol
		if (value >= 0) {
			// positive
			UIntToString(value, buffer, 10);
		} else {
			// negative
			UIntToString((UINT32)-value, buffer + 1, 10);
			buffer[0] = '-';
		}
		KernelVideo::WriteUnformattedString(buffer);
	}


	
	VideoStream& VideoStream::operator<<(int i)
	{
		WriteDecimalValue(i);
		return *this;
	}

	VideoStream& VideoStream::operator<<(unsigned int i)
	{
		WriteDecimalUValue(i);
		return *this;
	}
	
	VideoStream& VideoStream::operator<<(short i)
	{
		WriteDecimalValue((SINT32)i);
		return *this;
	}
	VideoStream& VideoStream::operator<<(unsigned short i)
	{
		WriteDecimalUValue((UINT32)i);
		return *this;		
	}

}

