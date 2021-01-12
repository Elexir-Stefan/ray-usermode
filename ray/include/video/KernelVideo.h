#ifndef KERNEL_VIDEO_H
#define KERNEL_VIDEO_H

#include <ray/typedefs.h>

extern "C" void KPrintfInternal(String string);

namespace Kernel {
	
	
	
	class KernelVideo
	{
		public:
			KernelVideo();
			~KernelVideo();
			static void WriteUnformattedString(const char *string);
			static void SetCharacterAttributeAt(UINT8 line, UINT8 column, UINT8 fcolour, UINT8 bcolour, char c);
	
		private:
			static void WriteAttribute(UINT32 line, UINT32 col, UINT32 attrib);
	};

}


#endif

