/*=================================================================
	File created by Yohann NICOLAS.

	Data added to D2 base-stucture

=================================================================*/
#pragma once

#include "common.h"
namespace PlugY {
    using namespace Commons;
    extern void *unassignSkillsBtnImages;
    extern void *unassignStatsBtnImages;
    extern void *stashBtnsImages;
    extern void *newStatsInterfaceImages;
    extern void *statsBackgroundImages;
    extern void *sharedGoldBtnsImages;

// 0 - null data, used by the End (Term) fields only

// 1 - String (needs length field)
#define ADD_STRING_FIELD(O, N, L)        \
TableDesc[i].fieldName = N;                \
TableDesc[i].type = 0x01;                \
TableDesc[i].strLength = L;                \
TableDesc[i].offset = O;                \
TableDesc[i].lookup = 0x00000000; i++

// 2 - DWORD field
#define ADD_DWORD_FIELD(O, N)            \
TableDesc[i].fieldName = N;                \
TableDesc[i].type = 0x02;                \
TableDesc[i].strLength = 0x00;            \
TableDesc[i].offset = O;                \
TableDesc[i].lookup = 0x00000000; i++

// 3 - WORD field

// 4 - BYTE field
#define ADD_BYTE_FIELD(O, N)            \
TableDesc[i].fieldName = N;                \
TableDesc[i].type = 0x04;                \
TableDesc[i].strLength = 0x00;            \
TableDesc[i].offset = O;                \
TableDesc[i].lookup = 0x00000000; i++

// 6 - UBYTE field
#define ADD_UBYTE_FIELD(O, N)            \
TableDesc[i].fieldName = N;                \
TableDesc[i].type = 0x06;                \
TableDesc[i].strLength = 0x00;            \
TableDesc[i].offset = O;                \
TableDesc[i].lookup = 0x00000000; i++

// 9 - three and four letter codes
#define ADD_STRCODE_FIELD(O, N)        \
TableDesc[i].fieldName = N;                \
TableDesc[i].type = 0x09;                \
TableDesc[i].strLength = 0x00;            \
TableDesc[i].offset = O;                \
TableDesc[i].lookup = 0x00000000; i++

// A,B,D,10,11 - Lookup code
#define ADD_LOOKUP_FIELD(O, N, T, L)        \
TableDesc[i].fieldName = N;                \
TableDesc[i].type = T;                    \
TableDesc[i].strLength = 0x00;            \
TableDesc[i].offset = O;                \
TableDesc[i].lookup = L; i++
#define ADD_LOOKUP_WORD(O, N, L)        \
TableDesc[i].fieldName = N;                \
TableDesc[i].type = 0x14;                \
TableDesc[i].strLength = 0x00;            \
TableDesc[i].offset = O;                \
TableDesc[i].lookup = (void*)(L); i++


//D,F:Lookup for BYTE (F : UBYTE ?)
//17: call function
//14,16:Lookup for WORD
//11:Lookup fo DWORD
//1A: flag


//extern void* lookupItemStatCost;

    void Install_PlugYFiles();
    void Install_PlugYImagesFiles();
    void Install_PlugYTxtFiles();

}