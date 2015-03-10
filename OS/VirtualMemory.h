/*	File:		VirtualMemory.h	Contains:	Interfaces to virtual memory functions	Copyright:	� 1992-1996 by Apple Computer, Inc., all rights reserved.	Derived from v55 internal.*/#if !defined(__VIRTUALMEMORY_H)#define __VIRTUALMEMORY_H#if !defined(__KERNELTYPES_H)#include "KernelTypes.h"#endif#if !defined(__USERTASKS_H)#include "UserTasks.h"#endif#if !defined(__COMPACTSTATE_H)#include "CompactState.h"#endif#if !defined(__SINGLEQ_H)#include "SingleQ.h"#endif#if !defined(__MEMORYLANES_H)#include "MemoryLanes.h"#endif#if !defined(__ROMEXTENSION_H)#include "ROMExtension.h"#endif#if !defined(__NEWTONGESTALT_H)#include "NewtonGestalt.h"#endifconst ULong	kKernelDomainHeapDomainNumber = 2;extern "C" NewtonErr NewHeapDomain(ULong baseMegs, ULong numMegs, ObjectId * returnDomainId);// option bits for NewHeapAreaconst ULong kNHOpts_NotCacheable			= 0x01;			// set if objects in this area should not be cacheableconst ULong	kNHOpts_ReadOnly				= 0x02;			// all heap objects will be read only (only the manager can fault them in)const ULong	kNHOpts_ExceptionOnNoMem	= 0x04;			// if we run out of memory create an exception rather than a suspendconst ULong kNHOpts_Persistent			= 0x40000000;typedef bool (*ReleaseProcPtr)(void * refcon, VAddr * start, VAddr * end, bool doRelease);extern "C" NewtonErr NewHeapArea(ObjectId domainId, VAddr requestedAddr, size_t maxSize, ULong options, VAddr * returnStart, VAddr * returnEnd);extern "C" NewtonErr NewStack(ObjectId domainId, size_t maxSize, ObjectId ownerId, VAddr * returnTopOfStack, VAddr * returnBottomOfStack);extern "C" NewtonErr FreePagedMem(VAddr addressInArea);extern "C" NewtonErr SetHeapLimits(VAddr start, VAddr end);extern "C" NewtonErr FreeHeapRange(VAddr start, VAddr end);	// never used// NOTE: The LockStack and LockHeapRange calls will lock down a virtual range// of memory to ensure that no faults can occur within the range.  This is// useful for interrupt drivers and tasks that need to do EnterAtomic which// must not fault while pending.extern "C" NewtonErr LockHeapRange(VAddr start, VAddr end, bool wire = NO);	// Lock range from start up to but not including end.  Wire will prevent v->p mappings from changing.extern "C" NewtonErr UnlockHeapRange(VAddr start, VAddr end);extern "C" NewtonErr LockStack(StackLimits * lockRef, size_t additionalSpace);	// Lock the entire stack plus additionalSpace # of bytesextern "C" NewtonErr UnlockStack(StackLimits * lockRef);extern "C" NewtonErr AddPageMappingToDomain(ObjectId domainId, VAddr address, ObjectId pageId);extern "C" NewtonErr SetRemoveRoutine(VAddr addr, ReleaseProcPtr releaseProc, void* releaseRefCon);extern "C" NewtonErr GetHeapAreaInfo(VAddr addr, VAddr * returnStart, VAddr * returnEnd);extern "C" NewtonErr GetSystemReleasable(ULong * pReleaseable, ULong* stackSpaceUsed, ULong * totalPagesUsed);const ULong kRebootMagicNumber = 'BLTG';	// Bacon, Lettuce, Tomato, and Garlic (or could be something entirely different)extern "C" VAddr GetPackageList(ULong id);extern "C" VAddr GetRExConfigEntry(ULong id, ULong tag, size_t * length);extern "C" VAddr PrimRExConfigEntry(ULong id, ULong tag, size_t * length);extern "C" VAddr PrimNextRExConfigEntry(ULong id, ULong tag, size_t * length, ArrayIndex * currentIndex);extern "C" VAddr GetLastRExConfigEntry(ULong tag, size_t * length);extern "C" VAddr PrimLastRExConfigEntry(ULong tag, size_t * length);extern "C" RExHeader* GetRExPtr(ULong id);class CPersistentRecoveryArea;struct MemObjDBIndex;#define kMaximumMemoryPartitions  10#define kMaxPatchCount             5		// this many patches at most for MP130 (base ROM + 4 ROM Extensions)#define kMaxPatchPageCount        34		// 34 allows a maximum of 136k worth of patch area#define kMaxUnsuccessfulBootCount 12struct SPatchInfo{	// Info about patch that's already installed_	ULong		fPatchCheckSum;				// Calculated checksum for installed patch	ULong		fPatchVersion;					// Current patch version	ULong		fPatchPageCount;				// # of pages in this patch	ULong		fPatchFirstPageIndex;		// Index into the patch page array													// �Track the pages for this patch.	// Info about patch that's about to be installed_	// Non-zero only when a patch has been registered but not installed yet.	VAddr		fPatchPtr;						// Ptr to the patch code	ULong		fPatchCodeSize;				// Size of the patch code in bytes	ULong		fPatchNewVersion;				// New patch version};typedef void (*PatchProcPtr)(VAddr vaddr);struct SGlobalsThatLiveAcrossReboot{	ULong			fMagicNumber;				// must be set to kRebootMagicNumber to indicate this information being valid or not	ULong			fPersistentDataInUse;	// set to kRebootMagicNumber to indicate there is persistent data SOMEWHERE or another in the system	ULong			fRebuildPageTracker;		// set to true if we need to rebuild the page tracking table	ULong			fRealTimeClockHackSavedTimeValue;		// saved value for real time clock (see interrupt.c)	ULong			fWarmBootCount;			// counts number of warm boots in a row (zero if cold boot)	NewtonErr	fRebootReason;				// why did we reboot?	MemObjDBIndex *	fMemObjDBIndexTable;	// this is the dynamic globals that live across reboot area													// NOTE: Inited by BuildMemObjDatabase	ULong			fLastNodeId;				// Last known AppleTalk node id ... init'ed to 0	// patching related stuff - still 280 bytes.	UShort		fROMBanksAreSplit;		// Begin 1278152 pmrchanged from fRestoringPatchFromBackup.													// True only if ROMBanksAreSplit(). That function (in boot.c) doesn't work after													// the MMU is turned on, so we call it early and save the value here so we know													// which rex page table to use.													// End 1278152	UShort		fTotalPatchPageCount;						// # patch pages actually installed.	SPatchInfo	fPatchArray[kMaxPatchCount];				// info for each patch	PAddr			fPatchPageArray[kMaxPatchPageCount];	// track all of the pages used for patching here...	// tablet calibration info	int			fTabletValid;			// Table data valid	int			fTabletXScale;			// Table x scale	int			fTabletXOffset;		// Table x offset	int			fTabletYScale;			// Table y scale	int			fTabletYOffset;		// Table y offset	// these are controlled by gCollectCPUStats	ULong			fTimeAtColdBoot;		// real time clock value at last cold boot	ULong			fProcessorOnTime;	ULong			fScreenOnTime;	ULong			fSerialOnTime;	ULong			fSoundOnTime;	// end of gCollectCPUStats vars	// internal store persistent state	SCompactState	fCompactState;			// +0168	block-compact state for BWS	// reboot information	ULong			fUnsuccessfulBootCount;	// +01C4 keep track of cold and warm boots in case shut down is needed	// memory configuration	ULong			fMemoryConfigured;						// set to kRebootMagicNumber after MemoryTest is finished	ULong			fMemoryConfigCksum;						// not currently supported	SFlashLaneInfo	fFlashBankInfo[kMaxMemoryLanes];	// +1D0  information about installed flash	SBankInfo	fBank[kMaximumMemoryPartitions];		// +220  information about the memory configuration	RExHeader *	fRExPtr[kMaxROMExtensions];			// +2E8  start of each ROM extension, or NULL	PAddr			fRExPTPage;									//			page for REx patchtable page table	RExHeader *	fPhysRExPtr[kMaxROMExtensions];		// +2FC  physical start of each ROM extension, or NULL	ULong			fRExSize[kMaxROMExtensions];			// +30C  size of REx, or NULL	ULong			fReserved[16];								//	+31C	some handy persistent objects for future use};extern ULong gCollectCPUStats;				// set to true if stat collection should be doneextern SGlobalsThatLiveAcrossReboot gGlobalsThatLiveAcrossReboot;extern "C" void	InitGlobalsThatLiveAcrossReboot();extern "C" PAddr	VtoP(VAddr v);#endif	/* __VIRTUALMEMORY_H */