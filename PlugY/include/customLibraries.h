/*=================================================================
	File created by Yohann NICOLAS.

	Language management.

=================================================================*/
#pragma once

#include "common.h"

#include "d2functions.h"

namespace PlugY {
    typedef int (__stdcall *TsaveSaveFile)(Commons::Unit *ptChar, BYTE **data, DWORD *maxSize, DWORD *curSize);

    typedef int (__stdcall *TloadSaveFile)(Commons::Unit *ptChar, BYTE *data, DWORD maxSize, DWORD *curSize);

    typedef int (__stdcall *TinitSaveFile)(BYTE **data, DWORD *maxSize, DWORD *curSize
    );

    class TCustomDll {
    public:
        union {
            HMODULE module;
            DWORD offset;
        };
        TCustomDll *nextDll;

        void initialize(DWORD offsetDll);

        void init();

        void release();

        void saveExtendedSaveFile(Commons::Unit *ptChar, BYTE **data, DWORD *maxSize, DWORD *curSize);

        int loadExtendedSaveFile(Commons::Unit *ptChar, BYTE *data, DWORD maxSize, DWORD *curSize);

        int initExtendedSaveFile(BYTE **data, DWORD *maxSize, DWORD *curSize);

        void saveSharedSaveFile(Commons::Unit *ptChar, BYTE **data, DWORD *maxSize, DWORD *curSize);

        int loadSharedSaveFile(Commons::Unit *ptChar, BYTE *data, DWORD maxSize, DWORD *curSize);

        int initSharedSaveFile(BYTE **data, DWORD *maxSize, DWORD *curSize);
//	__inline TCustomDll() {ZeroMemory(this,sizeof(this));}
    private:
        FARPROC initFct;
        FARPROC releaseFct;
        TsaveSaveFile saveExtendedSaveFileFct;
        TloadSaveFile loadExtendedSaveFileFct;
        TinitSaveFile initExtendedSaveFileFct;
        TsaveSaveFile saveSharedSaveFileFct;
        TloadSaveFile loadSharedSaveFileFct;
        TinitSaveFile initSharedSaveFileFct;
    };

    extern TCustomDll *customDlls;

}