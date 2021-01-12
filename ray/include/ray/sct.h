#ifndef SCT_H
#define SCT_H

namespace Kernel {
	class SCT {
		public:
			static const UINT32 Exit = 119;
			static const UINT32 HardSystemReset = 400;

			class Debug {
			public:
				static const UINT32 DebugMsg = 503;
				static const UINT32 Break = 511;
				static const UINT32 Profile_GetBuffer = 502;
				static const UINT32 Profile_Flush = 504;
				static const UINT32 Profile_Setup = 505;
				static const UINT32 Profile_Start = 506;
				static const UINT32 Profile_Stop = 507;
				static const UINT32 Profile_Reset = 508;
				static const UINT32 Profile_Size = 509;
				static const UINT32 Profile_RCount = 510;
			};

			class RDM {
			public:
				static const UINT32 RegisterIRQ = 106;
				static const UINT32 RequestIO = 103;
				static const UINT32 IRQWait = 108;
			};

			class Memory {
				public:
				static const UINT32 MAlloc = 100;
				static const UINT32 Free = 101;
				static const UINT32 MemSize = 104;
			};

			class Video {
			public:
				static const UINT32 Print = 99;
				static const UINT32 WriteAttrib = 98;
			};

			class Sync {
			public:
				static const UINT32 BarrierArrive = 140;
				static const UINT32 BarrierGo = 141;
				static const UINT32 BarrierClose = 142;
				static const UINT32 BarrierCreate = 143;
				static const UINT32 IP_LOCK_CREATE = 122;
				static const UINT32 IP_LOCK_GET	 = 123;
				static const UINT32 IP_LOCK_ENTER = 124;
				static const UINT32 IP_LOCK_LEAVE = 125;
				static const UINT32 IP_LOCK_STATUS = 126;
				static const UINT32 IP_LOCK_DESTROY = 127;
			};

			class Process {
			public:
				static const UINT32 Sleep = 107;
				static const UINT32 GetPID = 130;
				static const UINT32 Pause = 128;
				static const UINT32 THREAD_CREATE = 116;
				static const UINT32 THREAD_EXIT	 = 117;
				static const UINT32 THREAD_INFO	 = 118;
				static const UINT32 StandardReturn = 120;
				static const UINT32 THREAD_GET	 = 132;
				static const UINT32 THREAD_ABORT = 133;
				static const UINT32 THREAD_NOTIFY = 134;
				static const UINT32 THREAD_ALIVE = 135;
				static const UINT32 THREAD_JOIN	 = 136;
			};

			class IPC {
				public:
					static const UINT32 CreateWall = 150;
					static const UINT32 CreateSocket = 151;
					static const UINT32 RemoveSocket = 152;
					static const UINT32 PlugByName = 153;
					static const UINT32 PlugByPID = 154;
					static const UINT32 AllocateMB = 155;
					static const UINT32 FreeMB = 156;
					static const UINT32 CallMethod = 157;
					static const UINT32 GetRMICable = 158;
					static const UINT32 GetAllCables = 159;
			};

	};
}


#endif

