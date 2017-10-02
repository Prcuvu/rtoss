/*
	CPUID.C - V0.2 - Jim Howes <jimhowes@ (exactly the same again).net>

	This code comes with NO WARRANTY.
	If it breaks you get to keep all of the pieces.

	This code may look like it was knocked up in ten minutes by
	a crazed psychopathic C coder
	This is because that is precisely how it was created.

	The _asm syntax is suitable for MSVC 6.0

	In a SMP system, there is no way (in this code) to tell which CPU
	you are physically running on.  In an Intel SMP system this probably
	does not matter, as all CPUs should be the same model and stepping.

	Running this code on anything prior to (whatever first responded
	to 0x80000003 in EAX on CPUID) will probably do wierd things.
*/
#include <stdio.h>
#include <string.h>
#include <windows.h>

#pragma comment(lib, "User32.lib")

typedef struct CPUID_01_ValuesInEAX
{
	unsigned int	iSteppingID : 4;
	unsigned int	iModelID : 4;
	unsigned int	iFamilyID : 4;
	unsigned int	iProcessorType : 2;
	unsigned int	Reserved_14 : 2;
	unsigned int	iExtendedModelID : 4;
	unsigned int	iExtendedFamilyID : 8;
	unsigned int	Reserved_28 : 3;
	unsigned int	iProcessorBrandString : 1;
} CPUID_01_EAX_t;

typedef struct CPUID_01_ValuesInECX
{
	unsigned int	iSSE3 : 1;
	unsigned int	iReserved_1 : 2;
	unsigned int	iMWAIT : 1;
	unsigned int	iQDS : 1;
	unsigned int	iVMX : 1;
	unsigned int	iSMX : 1;
	unsigned int	iEST : 1;
	unsigned int	iTM2 : 1;
	unsigned int	iSSSE3 : 1;
	unsigned int	iCID : 1;
	unsigned int	Reserved_11 : 1;
	unsigned int	i256FMA : 1;
	unsigned int	iCHG16B : 1;
	unsigned int	ixTPRUpd : 1;
	unsigned int	iPDMSR : 1;
	unsigned int	Reserved_16 : 2;
	unsigned int	iDCA : 1;
	unsigned int	iSSE41 : 1;
	unsigned int	iSSE42 : 1;
	unsigned int	ix2APIC : 1;
	unsigned int	iMOVBE : 1;
	unsigned int	iPOPCNT : 1;
	unsigned int	Reserved_23 : 1;
	unsigned int	iAES : 1;
	unsigned int	iXSAVE : 1;
	unsigned int	iOSXSAVE : 1;
	unsigned int	iIAV256 : 1;
	unsigned int	Reserved_28 : 3;
} CPUID_01_ECX_t;

typedef struct CPUID_01_ValuesInEDX
{
	unsigned int	iFPU : 1;
	unsigned int	iVME : 1;
	unsigned int	iDE  : 1;
	unsigned int	iPSE : 1;
	unsigned int	iTSC : 1;
	unsigned int	iMSR : 1;
	unsigned int	iPAE : 1;
	unsigned int	iMCE : 1;
	unsigned int	iCX8 : 1;
	unsigned int	iAPIC: 1;
	unsigned int	Reserved_10 : 1;
	unsigned int	iSEP : 1;
	unsigned int	iMTRR: 1;
	unsigned int	iPGE : 1;
	unsigned int	iMCA : 1;
	unsigned int	iCMOV: 1;
	unsigned int	iPAT : 1;
	unsigned int	iPSE36:1;
	unsigned int	iPSN : 1;
	unsigned int	iCFLSH:1;
	unsigned int	Reserved_20 : 1;
	unsigned int	iDS  : 1;
	unsigned int	iACPI: 1;
	unsigned int	iMMX : 1;
	unsigned int	iFXSR: 1;
	unsigned int	iSSE : 1;
	unsigned int	iSSE2: 1;
	unsigned int	iSS  : 1;
	unsigned int	iHTT : 1;
	unsigned int	iTM  : 1;
	unsigned int	Reserved_30 : 1;
	unsigned int	iPBE : 1;
} CPUID_01_EDX_t;

typedef struct CPUID_80000001_ValuesInECX
{
	unsigned int	iLAHF : 1;
	unsigned int	iCmpLegacy : 1;
	unsigned int	iSVM  : 1;
	unsigned int	iExtApicSpace : 1;
	unsigned int	iAMCr8 : 1;
	unsigned int	iLZCNT : 1;
	unsigned int	iSSE4A : 1;
	unsigned int	imSSE : 1;
	unsigned int	iPREFETCH : 1;
	unsigned int	iOSVW : 1;
	unsigned int	iIBS : 1;
	unsigned int	iSSE5 : 1;
	unsigned int	iSKINIT : 1;
	unsigned int	iWDT : 1;
	unsigned int	Reserved_14 : 18;
} CPUID_80000001_ECX_t;

typedef struct CPUID_80000001_ValuesInEDX
{
	unsigned int	iFPU : 1;
	unsigned int	iVME : 1;
	unsigned int	iDE  : 1;
	unsigned int	iPSE : 1;
	unsigned int	iTSC : 1;
	unsigned int	iMSR : 1;
	unsigned int	iPAE : 1;
	unsigned int	iMCE : 1;
	unsigned int	iCX8 : 1;
	unsigned int	iAPIC: 1;
	unsigned int	Reserved_10 : 1;
	unsigned int	iSYSCALL : 1;
	unsigned int	iMTRR: 1;
	unsigned int	iPGE : 1;
	unsigned int	iMCA : 1;
	unsigned int	iCMOV: 1;
	unsigned int	iPAT : 1;
	unsigned int	iPSE36:1;
	unsigned int	Reserved_18 : 1;
	unsigned int	Reserved_19 : 1;
	unsigned int	iNX : 1;
	unsigned int	Reserved_21 : 1;
	unsigned int	iMMXEx: 1;
	unsigned int	iMMX : 1;
	unsigned int	iFXSR: 1;
	unsigned int	iFFXSR : 1;
	unsigned int	Reserved_26: 1;
	unsigned int	iRDTSCP  : 1;
	unsigned int	Reserved_28 : 1;
	unsigned int	iLM  : 1;
	unsigned int	i3DNEx : 1;
	unsigned int	i3DN : 1;
} CPUID_80000001_EDX_t;

typedef struct CPUID_80000005_ValuesInECX
{
	unsigned int	Reserved_0 : 24;
	unsigned int	iL1ICSize : 8;
} CPUID_80000005_ECX_t;

typedef struct CPUID_80000005_ValuesInEDX
{
	unsigned int	Reserved_0 : 24;
	unsigned int	iL1DCSize : 8;
} CPUID_80000005_EDX_t;

typedef struct CPUID_80000006_ValuesInECX
{
	unsigned int	Reserved_0 : 16;
	unsigned int	iL2Size : 16;
} CPUID_80000006_ECX_t;

typedef struct CPUID_80000006_ValuesInEDX
{
	unsigned int	Reserved_0 : 18;
	unsigned int	iL3Size : 14;
} CPUID_80000006_EDX_t;

static	int		iCPUFlagsLoaded = 0;
static	CPUID_01_EAX_t	uBasicFlags;
static	CPUID_01_ECX_t	uExtFlags;
static	CPUID_01_EDX_t	uExt2Flags;
static	CPUID_80000001_ECX_t	u8ExtFlags;
static	CPUID_80000001_EDX_t	u8Ext2Flags;
static	CPUID_80000005_ECX_t	uL1ICSize;
static	CPUID_80000005_EDX_t	uL1DCSize;
static	CPUID_80000006_ECX_t	uL2Size;
static	CPUID_80000006_EDX_t	uL3Size;
static	char		sCPUBranding[65];
static	char		sCPUVendor[16];
static	unsigned long uHighestCPUID;
static	unsigned long uHighestCPUID0;


int identifyCPU(void)
{
	iCPUFlagsLoaded = 1;
	memset(sCPUBranding,0,65);
	memset(sCPUVendor,0,16);
	_asm {
		mov	  eax, 0
		cpuid
		mov	 DWORD PTR [sCPUVendor+0],ebx  // Stash the manufacturer string for later
		mov	 DWORD PTR [sCPUVendor+4],edx
		mov	 DWORD PTR [sCPUVendor+8],ecx
		mov	 uHighestCPUID0,eax			 // Store highest extended CPUID number
		mov	  eax, 80000000h
		cpuid
		mov	 uHighestCPUID,eax			 // Store highest extended CPUID number
	}
	_asm {
		mov	eax, 01h
		cpuid
		mov	uBasicFlags,eax
		mov	uExtFlags,ecx
		mov	uExt2Flags,edx
	}

	if(uHighestCPUID >= 0x80000001) {
		_asm {
			mov	eax, 80000001h
			cpuid
			mov	u8ExtFlags,ecx
			mov	u8Ext2Flags,edx
		}
	}
	
	if(uHighestCPUID >= 0x80000004) {
		_asm {
			mov eax, 80000002h
			cpuid
			mov DWORD PTR [sCPUBranding+ 0],eax
			mov DWORD PTR [sCPUBranding+ 4],ebx
			mov DWORD PTR [sCPUBranding+ 8],ecx
			mov DWORD PTR [sCPUBranding+12],edx
			mov eax, 80000003h
			cpuid
			mov DWORD PTR [sCPUBranding+16],eax
			mov DWORD PTR [sCPUBranding+20],ebx
			mov DWORD PTR [sCPUBranding+24],ecx
			mov DWORD PTR [sCPUBranding+28],edx
			mov eax, 80000004h
			cpuid
			mov DWORD PTR [sCPUBranding+32],eax
			mov DWORD PTR [sCPUBranding+36],ebx
			mov DWORD PTR [sCPUBranding+40],ecx
			mov DWORD PTR [sCPUBranding+44],edx
		}
	}
	else {
		if(*sCPUVendor) {
			if (!strncmp("AuthenticAMD", sCPUVendor, 12)) {
				switch (uBasicFlags.iFamilyID) { // extract family code
					case 4: // Am486/AM5x86
						strcpy (sCPUBranding, "AMD Am486");
						break;

					case 5: // K6
						switch (uBasicFlags.iModelID) { // extract model code
							case 0:
							case 1:
							case 2:
							case 3:
								strcpy (sCPUBranding, "AMD K5");
								break;
							case 6:
							case 7:
								strcpy (sCPUBranding, "AMD K6");
								break;
							case 8:
								strcpy (sCPUBranding, "AMD K6-2");
								break;
							case 9:
							case 10:
							case 11:
							case 12:
							case 13:
							case 14:
							case 15:
								strcpy (sCPUBranding, "AMD K6-3");
								break;
						}
						break;

					case 6: // Athlon
						// No model numbers are currently defined
						strcpy (sCPUBranding, "AMD Athlon");
						break;
				}
			}
			else if (!strncmp("GenuineIntel", sCPUVendor, 12)) {
				switch (uBasicFlags.iFamilyID) { // extract family code
					case 4:
						switch (uBasicFlags.iModelID) { // extract model code
							case 0:
							case 1:
								strcpy (sCPUBranding, "INTEL 486DX");
								break;
							case 2:
								strcpy (sCPUBranding, "INTEL 486SX");
								break;
							case 3:
								strcpy (sCPUBranding, "INTEL 486DX2");
								break;
							case 4:
								strcpy (sCPUBranding, "INTEL 486SL");
								break;
							case 5:
								strcpy (sCPUBranding, "INTEL 486SX2");
								break;
							case 7:
								strcpy (sCPUBranding, "INTEL 486DX2E");
								break;
							case 8:
								strcpy (sCPUBranding, "INTEL 486DX4");
								break;
						}
						break;

					case 5:
						switch (uBasicFlags.iModelID) { // extract model code
							case 1:
							case 2:
							case 3:
								strcpy (sCPUBranding, "INTEL Pentium");
								break;
							case 4:
								strcpy (sCPUBranding, "INTEL Pentium-MMX");
								break;
						}
						break;

					case 6:
						switch (uBasicFlags.iModelID) { // extract model code
							case 1:
								strcpy (sCPUBranding, "INTEL Pentium-Pro");
								break;
							case 3:
							case 5:
								strcpy (sCPUBranding, "INTEL Pentium-II");
								break;  // actual differentiation depends on cache settings
							case 6:
								strcpy (sCPUBranding, "INTEL Celeron");
								break;
							case 7:
							case 8:
							case 10:
								strcpy (sCPUBranding, "INTEL Pentium-III");
								break;  // actual differentiation depends on cache settings
						}
						break;

					case 15: // family 15, extended family 0x00
						if(uBasicFlags.iExtendedFamilyID<<4 == 0) {
							switch (uBasicFlags.iModelID) {
								case 0:
									strcpy (sCPUBranding, "INTEL Pentium-4");
									break;
							}
						}
						break;
				}
			}
		}
	}

	if(uHighestCPUID >= 0x80000005) {
		_asm {
			mov	eax, 80000005h
			cpuid
			mov	uL1ICSize,ecx
			mov	uL1DCSize,edx
		}
	}

	if(uHighestCPUID >= 0x80000006) {
		_asm {
			mov	eax, 80000006h
			cpuid
			mov	uL2Size,ecx
			mov	uL3Size,edx
		}
	}

	return(0);
}


int main(int argc, char *argv[])

{
	char	sMsg[2048];
	char	cache[100];

	identifyCPU();

	sprintf(sMsg,"%s %s\n\nProcessor ID Family %d Model %d Stepping %d\nFlags: ",(*sCPUVendor)?sCPUVendor:"<unknown>",(*sCPUBranding)?sCPUBranding:"<No Name>",uBasicFlags.iExtendedFamilyID<<4 | uBasicFlags.iFamilyID,
								 uBasicFlags.iExtendedModelID<<4  | uBasicFlags.iModelID,
								 uBasicFlags.iSteppingID);

	if( uExt2Flags.iFPU  ) strcat(sMsg, "FPU ");	// Integrated FPU
	if( uExt2Flags.iVME  ) strcat(sMsg, "VME ");	// Virtual Memory Extensions
	if( uExt2Flags.iDE   ) strcat(sMsg, "DE ");	// Debugging extensions
	if( uExt2Flags.iPSE  ) strcat(sMsg, "PSE ");	// Page Size Extensions
	if( uExt2Flags.iTSC  ) strcat(sMsg, "TSC ");	// Time Stamp COunter
	if( uExt2Flags.iMSR  ) strcat(sMsg, "MSR ");	// Model specific registers, RDMSR/WRMSR instructions
	if( uExt2Flags.iPAE  ) strcat(sMsg, "PAE ");	// Physical Address Extension
	if( uExt2Flags.iMCE  ) strcat(sMsg, "MCE ");	// Machine Check Exception
	if( uExt2Flags.iCX8  ) strcat(sMsg, "CX8 ");	// CMPXCHG8B instruction
	if( uExt2Flags.iAPIC ) strcat(sMsg, "APIC ");	// On-chip APIC
	if( uExt2Flags.iSEP  ) strcat(sMsg, "SEP ");	// SYSENTER and SYSEXIT instructions and MSRs
	if( uExt2Flags.iMTRR ) strcat(sMsg, "MTRR ");	// Memory Type Range Registers
	if( uExt2Flags.iPGE  ) strcat(sMsg, "PGE ");	// PTE Global Bit
	if( uExt2Flags.iMCA  ) strcat(sMsg, "MCA ");	// Machine Check Architecture
	if( uExt2Flags.iCMOV ) strcat(sMsg, "CMOV ");	// Conditional MOV instruction
	if( uExt2Flags.iPAT  ) strcat(sMsg, "PAT ");	// Page Attribute Table
	if( uExt2Flags.iPSE36) strcat(sMsg, "PSE36 ");	// 36-bit page size extension
	if( uExt2Flags.iPSN  ) strcat(sMsg, "PSN ");	// Processor serial number
	if( uExt2Flags.iCFLSH) strcat(sMsg, "CFLSH ");	// CLFLUSH instruction
	if( uExt2Flags.iDS   ) strcat(sMsg, "DS ");	// Debug Store
	if( uExt2Flags.iACPI ) strcat(sMsg, "ACPI ");	// Thermal monitor and software-controlled-clock functions
	if( uExt2Flags.iMMX  ) strcat(sMsg, "MMX ");	// MMX present
	if( uExt2Flags.iFXSR ) strcat(sMsg, "FXSR ");	// FXSAVE and FXRESTORE instructions
	if( uExt2Flags.iSSE  ) strcat(sMsg, "SSE ");	// Streaming SIMD Extensions
	if( uExt2Flags.iSSE2 ) strcat(sMsg, "SSE2 ");	// Streaming SIMD Extensions 2 present
	if( uExtFlags.iSSE3  ) strcat(sMsg, "SSE3 ");	// Streaming SIMD Extensions 3 present
	if( uExtFlags.iSSSE3  ) strcat(sMsg, "SSSE3 ");	// Supplemental Streaming SIMD Extensions 3 present
	if( uExtFlags.iSSE41  ) strcat(sMsg, "SSE4.1 ");	// Streaming SIMD Extensions 4.1 present
	if( uExtFlags.iSSE42  ) strcat(sMsg, "SSE4.2 ");	// Streaming SIMD Extensions 4.2 present
	if( u8ExtFlags.iSSE4A ) strcat(sMsg, "SSE4A ");	// Streaming SIMD Extensions 4A present
	if( u8ExtFlags.imSSE ) strcat(sMsg, "maSSE ");	// Misaligned SSE
	if( u8Ext2Flags.i3DN ) strcat(sMsg, "3DNow! ");	// 3DNow!
	if( u8Ext2Flags.i3DNEx ) strcat(sMsg, "3DNow!+ ");	// 3DNow!+
	if( u8Ext2Flags.iMMXEx ) strcat(sMsg, "MMX+ ");	// MMX+
	if( uExt2Flags.iSS   ) strcat(sMsg, "SS ");	// Self Snoop
	if( uExt2Flags.iHTT  ) strcat(sMsg, "HTT ");	// Hyperthreading
	if( uExt2Flags.iTM   ) strcat(sMsg, "TM ");	// Thermal Monitoring
	if( uExtFlags.iTM2 ) strcat(sMsg, "TM2 ");	// Thermal Monitoring 2
	if( uExt2Flags.iPBE  ) strcat(sMsg, "PBE ");	// Pending Break Enable (FERR#/PBE# pins)
	if( uExtFlags.iMWAIT ) strcat(sMsg, "MWAIT ");	// MONITOR/MWAIT instructions
	if( uExtFlags.iQDS ) strcat(sMsg, "QDS ");	// CPL Qualified Debug Store present
	if( uExtFlags.iEST ) strcat(sMsg, "EST ");	// Enhanced SpeedStep
	if( uExtFlags.iCID ) strcat(sMsg, "CID ");	// Context-ID
	if( uExtFlags.iVMX ) strcat(sMsg, "VMX ");	// Virtual Machine Extensions
	if( u8ExtFlags.iSVM ) strcat(sMsg, "SVM ");	// LAHF
	if( u8Ext2Flags.iLM ) strcat(sMsg, "x86-64 ");	// 64-bit technology
	if( u8Ext2Flags.iNX ) strcat(sMsg, "NX ");	// No Execute
	if( u8ExtFlags.iLAHF ) strcat(sMsg, "LAHF ");	// LAHF

	sprintf(cache,"\nL1 I-Cache: %d KB, L1 D-Cache: %d KB",uL1ICSize.iL1ICSize,uL1DCSize.iL1DCSize);
	strcat(sMsg, cache);

	sprintf(cache,"\nL2 Cache: %d KB, L3 Cache: %d KB",uL2Size.iL2Size,uL3Size.iL3Size);
	strcat(sMsg, cache);

	sprintf(cache,"\nHighest CPUID = %08X",uHighestCPUID0);
	strcat(sMsg, cache);
	sprintf(cache,"\nHighest CPUIDEx = %08X",uHighestCPUID);
	strcat(sMsg, cache);

#ifndef CPUID_CONSOLE
	MessageBox(NULL,sMsg,"CPU Identification", MB_OK);
#else
	puts(sMsg);
#endif
	return(0);
}