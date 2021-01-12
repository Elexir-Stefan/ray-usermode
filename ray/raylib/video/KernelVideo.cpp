#include <raykernel.h>
#include <video/KernelVideo.h>

#include <syscall.h>
#include <ray/sct.h>

void KPrintfInternal(String string)
{
	SysCallN(Kernel::SCT::Video::Print, &string);
}

namespace Kernel {
	KernelVideo::KernelVideo()
	{
	}
	
	KernelVideo::~KernelVideo()
	{
	}
	
	void KernelVideo::WriteUnformattedString(const char *string)
	{
		SysCallN(SCT::Video::Print, &string);
	}
	
	void KernelVideo::WriteAttribute(UINT32 line, UINT32 col, UINT32 attrib) {
		SysCallN(SCT::Video::WriteAttrib, &line);
	}
	
	void KernelVideo::SetCharacterAttributeAt(UINT8 line, UINT8 column, UINT8 fcolour, UINT8 bcolour, char c)
	{
		WriteAttribute(line, column, (fcolour & 0x0F) << 12 | (bcolour & 0x0F) << 8 | c);
	}

}
