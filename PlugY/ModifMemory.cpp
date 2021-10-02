/*=================================================================
	File created by Yohann NICOLAS.

	Modification of code in memory functions.

=================================================================*/

#include "error.h"
#include "parameters.h"
#include "modifMemory.h"

namespace PlugY {
    const char *MSG_ERROR_READ_MEMORY = "Error : Read access missing to patch memory at %08X.\n\nAn option in PlugY.ini is incompatible with another mod.";
    const char *MSG_CRITICAL_WRITE_MEMORY = "Error.\nWrite access missing to patch memory at %08X.\n\nAn option in PlugY.ini is incompatible with another mod.";
    const char *ERROR_TESTING1 = "Error : BYTE %02X wanted but %02X found to change memory at %08X.\n\nAn option in PlugY.ini is incompatible with another mod.";
    const char *ERROR_TESTING4 = "Error : DWORD %08X wanted but %08X found to change memory at %08X.\n\nAn option in PlugY.ini is incompatible with another mod.";


    void *currentMemoryPos = 0;

    DWORD mem_seek(DWORD newPos) {
        currentMemoryPos = (void *) newPos;
        return (DWORD) currentMemoryPos;
    }

    void patchMemory1(BYTE value) {
        if (IsBadWritePtr(currentMemoryPos, 1)) {
            log_box(MSG_CRITICAL_WRITE_MEMORY, currentMemoryPos);
            exit(1);
        }
        *(BYTE *) currentMemoryPos = value;
        currentMemoryPos = (LPVOID) ((DWORD) currentMemoryPos + 1);
    }

    void patchMemory4(DWORD value) {
        if (IsBadWritePtr(currentMemoryPos, 4)) {
            log_box(MSG_CRITICAL_WRITE_MEMORY, currentMemoryPos);
            exit(1);
        }
        *(DWORD *) currentMemoryPos = value;
        currentMemoryPos = (LPVOID) ((DWORD) currentMemoryPos + 4);
    }

    BYTE getMemory1(LPVOID mempos) {
        if (IsBadReadPtr(mempos, 1)) {
            log_box(MSG_ERROR_READ_MEMORY, currentMemoryPos);
            exit(1);
        }
        return *(BYTE *) mempos;
    }

    DWORD getMemory4(LPVOID mempos) {
        if (IsBadReadPtr(mempos, 4)) {
            log_box(MSG_ERROR_READ_MEMORY, currentMemoryPos);
            exit(1);
        }
        return *(DWORD *) mempos;
    }


    void memt_byte(BYTE old, BYTE val) {
        BYTE current = getMemory1(currentMemoryPos);
        if (current == val) {
            log_msg("Warning : BYTE %02X is already set at memory %08X\n", val, currentMemoryPos);
            currentMemoryPos = (LPVOID) ((DWORD) currentMemoryPos + 1);
            return;
        }
        if (old != current) {
            if (active_CheckMemory) {
                log_box(ERROR_TESTING1, old, current, currentMemoryPos);
                exit(1);
            } else log_msg(ERROR_TESTING1, old, current, currentMemoryPos);
        }
        log_msg("BYTE\t%08X : %02X->%02X\n", currentMemoryPos, old, val);
        patchMemory1(val);
    }

    bool testIfAlreadySet(DWORD current, DWORD wanted) {
        if (current == wanted) {
            log_msg("Warning : DWORD %08X is already set at memory %08X\n", wanted, currentMemoryPos);
            currentMemoryPos = (LPVOID) ((DWORD) currentMemoryPos + 4);
            return true;
        }
        return false;
    }

    void testMemory4(DWORD old, DWORD found) {
        if (old != found) {
            if (active_CheckMemory) {
                log_box(ERROR_TESTING4, old, found, currentMemoryPos);
                exit(1);
            } else log_msg(ERROR_TESTING4, old, found, currentMemoryPos);
        }
    }

    void memt_dword(DWORD old, DWORD val) {
        DWORD current = getMemory4(currentMemoryPos);
        DWORD wanted = val;
        if (testIfAlreadySet(current, wanted)) return;
        testMemory4(old, current);
        log_msg("DWORD\t%08X : %08X->%08X\n", currentMemoryPos, old, wanted);
        patchMemory4(wanted);
    }


    void memt_ref4(DWORD old, DWORD ref) {
        DWORD current = getMemory4(currentMemoryPos);
        DWORD wanted = ref - (DWORD) currentMemoryPos - 4;
        if (testIfAlreadySet(current, wanted)) return;
        testMemory4(old, current);
        log_msg("DWORD\t%08X : %08X->%08X\n", currentMemoryPos, old, wanted);
        patchMemory4(wanted);
    }

    void memc_ref4(DWORD old, DWORD ref) {
        DWORD current = getMemory4(currentMemoryPos);
        DWORD wanted = ref - (DWORD) currentMemoryPos - 4;
        if (testIfAlreadySet(current, wanted)) return;
        testMemory4(old, current + (DWORD) currentMemoryPos + 4);
        log_msg("DWORD\t%08X : %08X->%08X\n", currentMemoryPos, old, wanted);
        patchMemory4(wanted);
    }

    void memj_ref4(DWORD old, DWORD ref) {
        DWORD current = getMemory4(currentMemoryPos);
        DWORD wanted = ref - (DWORD) currentMemoryPos - 4;
        if (testIfAlreadySet(current, wanted)) return;
        testMemory4(old, getMemory4((LPVOID) getMemory4((LPVOID) (current + (DWORD) currentMemoryPos + 6))));
        log_msg("DWORD\t%08X : %08X->%08X\n", currentMemoryPos, old, wanted);
        patchMemory4(wanted);
    }


    void memd_ref4(DWORD old, DWORD ref) {
        DWORD current = getMemory4(currentMemoryPos);
        DWORD wanted = ref - (DWORD) currentMemoryPos - 4;
        if (testIfAlreadySet(current, wanted)) return;
        testMemory4(old, getMemory4((LPVOID) current));
        log_msg("DWORD\t%08X : %08X->%08X\n", currentMemoryPos, old, wanted);
        patchMemory4(wanted);
    }


}