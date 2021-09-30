#include "common.h"
#include "../Commons/D2TypeNameMacros.h"

s_shifting shifting;

DataTables *SgptDataTables;

#define D2S(F, I, R, N, P) typedef R (STDCALL  *T##N) P; T##N N;

typedef CharStatsBIN *(__stdcall *TD2Common10581)(DWORD charID);

TD2Common10581 D2Common10581;;//ONLY in 1.09
typedef ItemStatCostBIN *(__stdcall *TD2Common10598)(DWORD itemStatCostID);

TD2Common10598 D2Common10598;;//ONLY in 1.09
typedef ItemTypesBIN *(__stdcall *TD2Common10673)(DWORD itemTypesID);

TD2Common10673 D2Common10673;;//ONLY in 1.09
#undef D2S

TD2AddPlayerStat V2AddPlayerStat;
TD2GetPlayerStat V2GetPlayerStat;
TD2GetPlayerBaseStat V2GetPlayerBaseStat;
TD2SetSkillBaseLevel V2SetSkillBaseLevel;
TD2SetSkillBaseLevelOnClient V2SetSkillBaseLevelOnClient;
TD2PrintStat V2PrintStat;
TD2CompileCubeInput V2CompileCubeInput;
TD2BroadcastFunction V2BroadcastFunction;
TD2GetGameByClientID V2GetGameByClientID;
TD2SpawnSuperUnique V2SpawnSuperUnique;
TD2SpawnMonster V2SpawnMonster;
TD2VerifIfNotCarry1 V2VerifIfNotCarry1;
TD2GameGetObject V2GameGetObject;
TD2TestPositionInRoom V2TestPositionInRoom;
TD2GetItemTypesBIN V2GetItemTypesBIN;
TD2CompileTxtFile compileTxtFile;

WORD (*getDescStrPos)(DWORD statID);

TD2SendMsgToAll V2SendMsgToAll;
TD2SetColorPopup V2SetColorPopup;
TD2LoadImage V2LoadImage;
TD2PlaySound V2PlaySound;
TD2SendToServer V2SendToServer;
TD2GetCharStatsBIN V2GetCharStatsBIN;
TD2GetItemStatCostBIN V2GetItemStatCostBIN;
TD2SendPacket V2SendPacket;
TD2LoadInventory V2LoadInventory;
TD2SaveGame V2SaveGame;
TD2MonsterUseSkill V2MonsterUseSkill;
TD2LinkPortal V2LinkPortal;
TD2Game235C0 V2Game235C0;
TD2ReadFile V2ReadFile;

DWORD getStatDescIDFrom(DWORD statID)//FOR 1.09
{
    DWORD *desc = ptStatDescTable;
    DWORD curDesc = 0;
    while (curDesc < *ptNbStatDesc) {
        if (*desc == statID)
            return curDesc;
        desc += 4;
        curDesc++;
    }
    return curDesc;
}

__declspec(naked)void D2AddPlayerStat_9() {
    __asm{//(Unit* ptChar, DWORD statID, DWORD amount, DWORD index)
    PUSH DWORD PTR SS:[ESP+0xC]
    PUSH DWORD PTR SS:[ESP+0xC]
    PUSH DWORD PTR SS:[ESP+0xC]
    CALL V2AddPlayerStat
    RETN 0x10
    }
}

__declspec(naked)void D2GetPlayerStat_9() {
    __asm{//(Unit* ptChar, DWORD statID, DWORD index)
    PUSH DWORD PTR SS:[ESP+0x8]
    PUSH DWORD PTR SS:[ESP+0x8]
    CALL V2GetPlayerStat
    RETN 0x0C
    }
}

__declspec(naked)void D2GetPlayerBaseStat_9() {
    __asm{//(Unit* ptChar, DWORD statID, DWORD index)
    PUSH DWORD PTR SS:[ESP+0x8]
    PUSH DWORD PTR SS:[ESP+0x8]
    CALL V2GetPlayerBaseStat
    RETN 0x0C
    }
}

__declspec(naked)void D2SetSkillBaseLevel_9() {
    __asm{//(Unit* ptChar, DWORD skillID, DWORD slvl, DWORD bRemove, char*, DWORD));
    PUSH DWORD PTR SS:[ESP+0x10]
    PUSH DWORD PTR SS:[ESP+0x10]
    PUSH DWORD PTR SS:[ESP+0x10]
    PUSH DWORD PTR SS:[ESP+0x10]
    CALL V2SetSkillBaseLevel
    RETN 0x18
    }
}

__declspec(naked)void D2SetSkillBaseLevelOnClient_9() {
    __asm{//(void* ptClient, Unit* ptChar, DWORD skillID, DWORD newValue, DWORD zero)
    POP EAX
    MOV ECX, EDX
    POP EDX
    PUSH EAX
    JMP V2SetSkillBaseLevelOnClient
    }
}

__declspec(naked)void D2GetCharStatsBIN_9() {
    __asm{
    PUSH ECX
    CALL D2Common10581
    RETN
    }
}

__declspec(naked)void D2GetItemStatCostBIN_9() {
    __asm{
    PUSH ECX
    CALL D2Common10598
    RETN
    }
}

__declspec(naked)void D2GetItemTypesBIN_9() {
    __asm{
    PUSH ECX
    CALL D2Common10673
    RETN
    }
}


DWORD
FASTCALL D2PrintStat_9(Unit *ptItem, Stats *ptStats, DWORD statID, DWORD statIndex, DWORD statValue, LPWSTR lpText) {
    DWORD curDesc = getStatDescIDFrom(statID);
    if (curDesc < *ptNbStatDesc)
        return V2PrintStat(ptItem, (Stats *) curDesc, statValue, 0, 0, lpText);
    return 0;
}


void setImage(sDrawImageInfo *data, void *image) { ((void **) data)[shifting.ptImage / 4] = image; }//0x4 0x8 0x3C
void setFrame(sDrawImageInfo *data, DWORD frame) { ((DWORD *) data)[shifting.ptFrame / 4] = frame; }//0x8 0x44 0x40

WORD getDescStrPos_9(DWORD statID) {
    DWORD *desc = &ptStatDescTable[getStatDescIDFrom(statID) * 4];
    return (WORD) *(desc + 2);
}

WORD getDescStrPos_10(DWORD statID) {
    ItemStatCostBIN *itemStatCost = D2GetItemStatCostBIN(statID);
    return itemStatCost->descstrpos;
}


const char *S_compileTxtFile = "compileTxtFile";
const char *S_errorReadTxtFile = "pbData";

__declspec(naked) void *
STDCALL compileTxtFile_9(DWORD unused, const char *filename, BINField *ptFields, DWORD *ptRecordCount,
                         DWORD recordLength) {
    _asm{
            SUB ESP, 0x210
//	MOV EAX,DWORD PTR DS:[1BEA28C]
            PUSH EBX
            PUSH EBP
            PUSH ESI
            PUSH EDI
            MOV ESI, DWORD PTR SS:[ESP+0x228]
            MOV DWORD PTR SS:[ESP+0x10], 0

            MOV EDI, wsprintf
            PUSH ESI
            LEA EAX, DWORD PTR SS:[ESP+0x20]
            PUSH EAX
            CALL EDI
            ADD ESP, 8

            LEA EDX, DWORD PTR SS:[ESP+0x10]
            PUSH 0
            PUSH S_compileTxtFile
            PUSH EDX
            MOV ECX, DWORD PTR SS:[ESP+0x230]
            LEA EDX, DWORD PTR SS:[ESP+0x28]
            CALL V2ReadFile
            TEST EAX, EAX
            JNZ continue_compileTxtFile
            PUSH 0
            PUSH S_compileTxtFile
            PUSH S_errorReadTxtFile
            CALL D2FogAssertOld
            PUSH -1
            CALL exit
            continue_compileTxtFile:
            MOV ECX, D2CompileTxtFile
            ADD ECX, 0x305
            JMP ECX
    }
}

__declspec(naked) void *
STDCALL compileTxtFile_10(DWORD unused, const char *filename, BINField *ptFields, DWORD *ptRecordCount,
                          DWORD recordLength) {
    _asm{
            SUB ESP, 0x210
//	MOV EAX,DWORD PTR DS:[1BEA28C]
            PUSH EBX
            PUSH EBP
            MOV EBP, DWORD PTR SS:[ESP+0x220]
            PUSH ESI
            PUSH EDI
            MOV DWORD PTR SS:[ESP+0x10], 0

            MOV EBX, wsprintf
            PUSH EBP
            LEA EAX, DWORD PTR SS:[ESP+0x20]
            PUSH EAX
            CALL EBX
            ADD ESP, 8

            LEA EDX, DWORD PTR SS:[ESP+0x10]
            PUSH 0
            PUSH S_compileTxtFile
            PUSH EDX
            MOV ECX, DWORD PTR SS:[ESP+0x230]
            LEA EDX, DWORD PTR SS:[ESP+0x28]
            CALL V2ReadFile
            TEST EAX, EAX
            JNZ continue_compileTxtFile
            PUSH 0
            PUSH S_compileTxtFile
            PUSH S_errorReadTxtFile
            CALL D2FogAssertOld
            PUSH -1
            CALL exit
            continue_compileTxtFile:
            MOV ECX, D2CompileTxtFile
            ADD ECX, 0x2ED
            JMP ECX
    }
}


DWORD compileTxtFile114_1;
DWORD compileTxtFile114_2;
DWORD compileTxtFile114_3;
DWORD compileTxtFile114_5;
DWORD compileTxtFile114_6;
DWORD compileTxtFile114_7;

__declspec(naked) void *
STDCALL compileTxtFile_114(DWORD unused, const char *filename, BINField *ptFields, DWORD *ptRecordCount,
                           DWORD recordLength) {
    _asm{
            PUSH EBP
            MOV EBP, ESP
            SUB ESP, 0x11C
            PUSH EBX
            PUSH ESI
            PUSH EDI

            MOV EAX, DWORD PTR SS:[EBP+0x10]
            MOV ECX, DWORD PTR SS:[EBP+0x14]
            PUSH EBX
            PUSH ESI
            MOV ESI, DWORD PTR SS:[EBP+0x8]
            PUSH EDI
            MOV EDI, DWORD PTR SS:[EBP+0xC]
            MOV DWORD PTR SS:[EBP-0x11C], ESI
            MOV DWORD PTR SS:[EBP-0x10C], EDI
            MOV DWORD PTR SS:[EBP-0x110], EAX
            MOV DWORD PTR SS:[EBP-0x118], ECX
            MOV DWORD PTR SS:[EBP-0x108], 0

            PUSH __LINE__
            PUSH S_compileTxtFile
            LEA EAX, DWORD PTR SS:[EBP-0x108]
            PUSH EAX
            MOV ECX, unused
            MOV EDX, filename
            CALL V2ReadFile
            TEST EAX, EAX
            JNZ continue_compileTxtFile
            PUSH __LINE__
            CALL D2GetInstructionPointer
            PUSH EAX
            PUSH S_errorReadTxtFile
            CALL D2FogAssert
            ADD ESP, 0xC
            PUSH -1
            CALL exit
            continue_compileTxtFile:
            // EAX : file
            // ECX : -
            // EDX : -
            // EBX : -
            // MOV ESI,DWORD PTR SS:[EBP+8]
            // MOV EDI,DWORD PTR SS:[EBP+C]
            MOV ESI, DWORD PTR SS:[EBP+0xC]

            MOV ECX, DWORD PTR SS:[EBP-0x108]
            PUSH ECX; /Arg2
            PUSH EAX; |Arg1
            CALL compileTxtFile114_1; \Game.006BD640
            MOV EDI, EAX
            PUSH EDI; /Arg1
            CALL compileTxtFile114_2; \Game.006BCDE0
            MOV EBX, EAX
            MOV ESI, EBX
            IMUL ESI, DWORD PTR SS:[EBP+0x18]
            PUSH 0; /Arg3 = 00000000
            PUSH 0x904; |Arg2 = 00000904
            PUSH compileTxtFile114_3; |Arg1 = 006E6370 ASCII ".\DATATBLS\DataTbls.cpp"
            MOV EDX, ESI; |
            XOR ECX, ECX; |
            CALL D2AllocMem; \Game.0040B430
            PUSH ESI
            PUSH 0
            PUSH EAX
            MOV DWORD PTR SS:[EBP-0x10C], EAX
            CALL compileTxtFile114_5
            MOV EDX, DWORD PTR SS:[EBP+0x18]
            MOV EAX, DWORD PTR SS:[EBP-0x10C]
            MOV ECX, DWORD PTR SS:[EBP-0x110]
            ADD ESP, 0xC
            PUSH EDX
            PUSH EBX
            PUSH EAX
            PUSH ECX
            PUSH EDI
            CALL compileTxtFile114_6
            PUSH EDI; /Arg1
            CALL compileTxtFile114_7; \Game.006BCDA0

            MOV EAX, DWORD PTR SS:[EBP-0x10C]
            MOV ECX, DWORD PTR SS:[EBP-0x118]
            TEST ECX, ECX
            JE fin
            MOV DWORD PTR DS:[ECX], EBX
            fin:
            POP EDI
            POP ESI
            POP EBX
            MOV ESP, EBP
            POP EBP
            RETN 0x14
    }
}

__declspec(naked) void *
STDCALL compileTxtFile_111(DWORD unused, const char *filename, BINField *ptFields, DWORD *ptRecordCount,
                           DWORD recordLength) {
    _asm{
            SUB ESP, 0x20C
//	MOV EAX,DWORD PTR DS:[6FDF1464]
            PUSH EBX
            PUSH EBP
            PUSH ESI
            PUSH EDI
            MOV DWORD PTR SS:[ESP+0x10], 0
            MOV EBX, DWORD PTR SS:[ESP+0x224]

            PUSH EBX
            LEA EAX, DWORD PTR SS:[ESP+0x1C]
            PUSH EAX
            CALL DWORD PTR SS:[wsprintf]
            MOV EDX, DWORD PTR SS:[ESP+0x228]
            ADD ESP, 8
            LEA EDX, DWORD PTR SS:[ESP+0x10]
            PUSH EDX
            PUSH EAX
            LEA EAX, DWORD PTR SS:[ESP+0x20]
            CALL V2ReadFile
            TEST EAX, EAX
            JNZ continue_compileTxtFile
            PUSH __LINE__
            CALL D2GetInstructionPointer
            PUSH EAX
            PUSH S_errorReadTxtFile
            CALL D2FogAssert
            ADD ESP, 0xC
            PUSH -1
            CALL exit
            continue_compileTxtFile:
            MOV ECX, D2CompileTxtFile
            ADD ECX, 0x1EC
            JMP ECX
    }
}


DWORD FASTCALL    D2isLODGame_111() { return IsLodGame; }

BYTE FASTCALL    D2GetDifficultyLevel_111() { return DifficultyLevel; }

DWORD STDCALL    D2GetMouseX_111() { return MouseX; }

DWORD STDCALL    D2GetMouseY_111() { return MouseY; }

Unit *STDCALL    D2GetClientPlayer_111() { return ptClientChar; }

DWORD *StatMouse1, *StatMouse2, *StatMouse3, *StatMouse4;

void FASTCALL D2CleanStatMouseUp_111() { *StatMouse1 = *StatMouse2 = *StatMouse3 = *StatMouse4 = 0; }

Unit *STDCALL    D2GetRealItem_111(Unit *ptItem) { return ptItem; }


__declspec(naked)void D2SendMsgToAll_111() {
    __asm{
    PUSH ESI
    MOV ESI, ECX
    CALL V2SendMsgToAll
    POP ESI
    RETN
    }
}

__declspec(naked)void D2SetColorPopup_111() {
    __asm{
    PUSH EDI
    PUSH EDX
    MOV EDI, ECX
    CALL V2SetColorPopup
    POP EDI
    RETN
    }
}

__declspec(naked)void D2LoadImage_111() {
    __asm{
    PUSH EDX
    MOV EAX, ECX
    CALL V2LoadImage
    RETN
    }
}

const char *D2FreeImage_FILE = __FILE__;

__declspec(naked)void D2FreeImage_111() {
    __asm{
    PUSH ESI
    MOV ESI, ECX
    PUSH ESI
    CALL D2CMP10014
    TEST ESI, ESI
    JE END_D2Free
    PUSH 0
    PUSH __LINE__
    MOV EDX, D2FreeImage_FILE;  ASCII "C:\projects\D2\head\Diablo2\Source\D2Client\CORE\ARCHIVE.CPP"
    MOV ECX, ESI
    CALL D2FogMemDeAlloc
    END_D2Free:
    POP ESI
    RETN
    }
}


__declspec(naked)void D2PlaySound_111() {
    __asm{
    PUSH EBX
    PUSH DWORD PTR SS:[ESP+0x10]
    PUSH DWORD PTR SS:[ESP+0x10]
    PUSH DWORD PTR SS:[ESP+0x10]
    PUSH EDX
    MOV EBX, ECX
    CALL V2PlaySound
    POP EBX
    RETN 0xC
    }
}

__declspec(naked)void D2GetClient_111() {
    __asm{
    PUSH ECX
    CALL D2GetPlayerData
    MOV EAX, DWORD PTR DS:[EAX+0x9C]
    RETN 4
    }
}


__declspec(naked)void D2SetSkillBaseLevelOnClient_111() {
    __asm{
    PUSH EBX
    PUSH ESI
    PUSH DWORD PTR SS:[ESP+0x14]
    PUSH DWORD PTR SS:[ESP+0x14]
    MOV EBX, DWORD PTR SS:[ESP+0x14]
    MOV EAX, ECX
    MOV ESI, EDX
    CALL V2SetSkillBaseLevelOnClient
    POP ESI
    POP EBX
    RETN 0xC
    }
}

__declspec(naked)void D2GetCharStatsBIN_111() {
    __asm{
    MOV EAX, ECX
    JMP V2GetCharStatsBIN
    }
}

__declspec(naked)void D2GetItemStatCostBIN_111() {
    __asm{
    MOV EAX, ECX
    JMP V2GetItemStatCostBIN
    }
}

__declspec(naked)void D2SendToServer3_114() {
    __asm{
    PUSH EDI
    PUSH EBX
    PUSH ECX
    MOV BYTE PTR SS:[ESP], CL
    MOV WORD PTR SS:[ESP+1], DX
    MOV EDI, 3
    LEA EDX, DWORD PTR SS:[ESP]
    PUSH EDX
    CALL D2SendToServerXX
    POP ECX
    POP EBX
    POP EDI
    RETN
    }
}

__declspec(naked)void D2SendToServer3_111() {
    __asm{
    PUSH EBX
    PUSH ECX
    MOV BYTE PTR SS:[ESP], CL
    MOV WORD PTR SS:[ESP+1], DX
    MOV EBX, 3
    LEA EDX, DWORD PTR SS:[ESP]
    PUSH EDX
    CALL D2SendToServerXX
    POP ECX
    POP EBX
    RETN
    }
}

__declspec(naked)void D2PrintStat_114() {
    __asm{
    PUSH ESI
    MOV ESI, DWORD PTR SS:[ESP+0x14]
    PUSH DWORD PTR SS:[ESP+0x10]
    PUSH DWORD PTR SS:[ESP+0x10]
    PUSH DWORD PTR SS:[ESP+0x10]
    PUSH EDX
    PUSH ECX
    CALL V2PrintStat
    POP ESI
    RETN 0x10
    }
}

__declspec(naked)void D2PrintStat_111() {
    __asm{
    PUSH ESI
    MOV ESI, DWORD PTR SS:[ESP+0x14]
    MOV EAX, DWORD PTR SS:[ESP+0x08]
    PUSH DWORD PTR SS:[ESP+0x10]
    PUSH DWORD PTR SS:[ESP+0x10]
    PUSH EDX
    PUSH ECX
    CALL V2PrintStat
    POP ESI
    RETN 0x10
    }
}

__declspec(naked)void D2SendPacket_114() {
    __asm{
    PUSH EDI
    PUSH DWORD PTR SS:[ESP+8]
    PUSH EDX
    MOV EDI, ECX
    CALL V2SendPacket
    POP EDI
    RETN 4
    }
}

__declspec(naked)void D2SendPacket_111() {
    __asm{
    POP EAX
    PUSH EDX
    PUSH EAX
    MOV EAX, ECX
    JMP V2SendPacket
    }
}

__declspec(naked)void D2LoadInventory_111() {
    __asm{
    MOV EAX, DWORD PTR SS:[ESP+4]
    MOV DWORD PTR SS:[ESP+4], EDX
    JMP V2LoadInventory
    }
}

__declspec(naked)void D2CompileCubeInput_111() {
    __asm{
    PUSH EBX
    MOV EBX, ECX
    MOV EAX, EDX
    CALL V2CompileCubeInput
    POP EBX
    RETN 8
    }
}

__declspec(naked)void D2CompileCubeInput_114() {
    __asm{
    PUSH ECX
    MOV EAX, EDX
    CALL V2CompileCubeInput
    RETN 8
    }
}


__declspec(naked)void D2BroadcastFunction_111() {
    __asm{
    PUSH EDI
    PUSH EBX
    MOV EAX, ECX
    MOV EDI, EDX
    MOV EBX, DWORD PTR SS:[ESP+0xC]
    CALL V2BroadcastFunction
    POP EBX
    POP EDI
    RETN 4
    }
}

__declspec(naked)void D2SpawnSuperUnique_111() {
    __asm{
    PUSH DWORD PTR SS:[ESP+0x18]
    PUSH DWORD PTR SS:[ESP+0x14]
    PUSH DWORD PTR SS:[ESP+0x14]
    PUSH DWORD PTR SS:[ESP+0x14]
    PUSH ECX
    MOV ECX, DWORD PTR SS:[ESP+0x18]
    MOV EAX, DWORD PTR SS:[ESP+0x28]
    CALL V2SpawnSuperUnique
    RETN 0x18
    }
}

__declspec(naked)void D2SpawnSuperUnique_111b() {
    __asm{
    PUSH DWORD PTR SS:[ESP+0x10]
    PUSH DWORD PTR SS:[ESP+0x10]
    PUSH DWORD PTR SS:[ESP+0x10]
    PUSH EDX
    PUSH ECX
    MOV EAX, DWORD PTR SS:[ESP+0x18]
    MOV EDX, DWORD PTR SS:[ESP+0x2C]
    MOV ECX, DWORD PTR SS:[ESP+0x28]//superuniqueID
    CALL V2SpawnSuperUnique
    RETN 0x18
    }
}


__declspec(naked)void D2SpawnSuperUnique_114() {
    __asm{
    PUSH EBX
    PUSH EDI
    MOV EBX, DWORD PTR SS:[ESP+0x1C]
    MOV EDI, ECX
    PUSH DWORD PTR SS:[ESP+0x20]
    PUSH DWORD PTR SS:[ESP+0x1C]
    PUSH DWORD PTR SS:[ESP+0x1C]
    PUSH DWORD PTR SS:[ESP+0x1C]
    PUSH DWORD PTR SS:[ESP+0x1C]
    PUSH EDX
    CALL V2SpawnSuperUnique
    POP EDI
    POP EBX
    RETN 0x18
    }
}

__declspec(naked)void D2SpawnMonster_114() {
    __asm{
    PUSH DWORD PTR SS:[ESP+0x18]
    PUSH DWORD PTR SS:[ESP+0x18]
    PUSH EDX
    PUSH ECX
    PUSH DWORD PTR SS:[ESP+0x20]
    PUSH DWORD PTR SS:[ESP+0x20]
    MOV EDX, DWORD PTR SS:[ESP+0x20]
    MOV ECX, DWORD PTR SS:[ESP+0x1C]
    CALL V2SpawnMonster
    RETN 0x18
    }
}

__declspec(naked)void D2VerifIfNotCarry1_111() {
    __asm{
    PUSH EBX
    PUSH ECX
    MOV EBX, EDX
    MOV EAX, DWORD PTR SS:[ESP+0xC]
    CALL V2VerifIfNotCarry1
    POP EBX
    RETN 4
    }
}

__declspec(naked)void D2GameGetObject_111() {
    __asm{
    MOV EAX, EDX
    MOV EDX, DWORD PTR SS:[ESP+4]
    CALL V2GameGetObject
    RETN 4
    }
}


__declspec(naked)void D2TestPositionInRoom_111() {
    __asm{
    PUSH EDI
    PUSH EBX
    MOV EDI, DWORD PTR SS:[ESP+0xC]
    MOV EAX, ECX
    MOV EBX, EDX
    CALL V2TestPositionInRoom
    POP EBX
    POP EDI
    RETN 4
    }
}

__declspec(naked)void D2GetItemTypesBIN_111() {
    __asm{
    MOV EAX, ECX
    JMP V2GetItemTypesBIN
    }
}

//FCT_ASM ( D2OpenNPCMenu_111)
//	MOV ESI,ECX
//	JMP V2OpenNPCMenu
//}}
__declspec(naked)void D2SendToServer_1XX() {
    __asm{
    PUSH DWORD PTR SS:[ESP+0x4]
    PUSH DWORD PTR SS:[ESP+0x10]
    PUSH 0
    CALL V2SendToServer
    RETN 0xC
    }
}


__declspec(naked)void D2GetGameByClientID_1XX() {
    __asm{
    POP EAX
    POP ECX
    PUSH EAX
    JMP V2GetGameByClientID
    }
}

__declspec(naked)void D2SaveGame_1XX() {
    __asm{
    POP EAX
    POP ECX
    PUSH EAX
    JMP V2SaveGame
    }
}

__declspec(naked)void D2MonsterUseSkill_111() {
    __asm{
    PUSH EBX
    PUSH EDX
    MOV EBX, ECX
    MOV ECX, EDX
    MOV EAX, DWORD PTR SS:[ESP+0xC]
    PUSH DWORD PTR SS:[ESP+0x1C]
    PUSH DWORD PTR SS:[ESP+0x1C]
    PUSH DWORD PTR SS:[ESP+0x1C]
    PUSH DWORD PTR SS:[ESP+0x1C]
    CALL V2MonsterUseSkill
    // Game sets monsters AiControl args[0] to 0 after this call
    POP EDX
    MOV EDX, DWORD PTR DS:[EDX+0x14]
    MOV EDX, DWORD PTR DS:[EDX+0x28]
    MOV DWORD PTR DS:[EDX+0x14], 0
    POP EBX
    RETN 0x14
    }
}


__declspec(naked)void D2LinkPortal_114() {
    __asm{
    PUSH ECX
    MOV ECX, DWORD PTR SS:[ESP+0x8]
    PUSH DWORD PTR SS:[ESP+0x14]
    PUSH DWORD PTR SS:[ESP+0x14]
    PUSH DWORD PTR SS:[ESP+0x14]
    CALL V2LinkPortal
    POP ECX
    RETN 0x10
    }
}

__declspec(naked)void D2Game235C0_114() {
    __asm{
    POP EAX
    POP ECX
    POP EDX
    PUSH EAX
    JMP V2Game235C0
    }
}

__declspec(naked)void D2ReadFile_111() {
    __asm{
    MOV EAX, EDX
    PUSH DWORD PTR SS:[ESP+4]
    PUSH ECX
    CALL V2ReadFile
    RETN 0xC
    }
}


#define SETFCTADDR(F, I, N) setFctAddr((DWORD*)&N, (HMODULE)offset_##F, (LPCSTR)I)

void setFctAddr(DWORD *addr, HMODULE module, LPCSTR index) {
    if (index) {
        *addr = (DWORD) GetProcAddress(module, index);
        if (!*addr) {
            log_msg("Bad index fct %d for %08X\n", index, module);
        }
    } else
        *addr = NULL;
}

void misc_fct() {//////////////// MISC FCT ////////////////
    getDescStrPos = version_D2Common >= V110 ? getDescStrPos_10 : getDescStrPos_9;
    compileTxtFile114_1 = offset_D2Client + 0x002BD640;
    compileTxtFile114_2 = offset_D2Client + 0x002BCDE0;
    compileTxtFile114_3 = offset_D2Client + 0x002E6370;
    compileTxtFile114_5 = offset_D2Client + 0x00281EF0;
    compileTxtFile114_6 = offset_D2Client + 0x002BD780;
    compileTxtFile114_7 = offset_D2Client + 0x002BCDA0;
    compileTxtFile = version_D2Common >= V114a ? compileTxtFile_114 : version_D2Common >= V111 ? compileTxtFile_111 :
                                                                      version_D2Common == V110 ? compileTxtFile_10
                                                                                               : compileTxtFile_9;
    V2AddPlayerStat = D2AddPlayerStat;
    V2GetPlayerStat = D2GetPlayerStat;
    V2GetPlayerBaseStat = D2GetPlayerBaseStat;
    V2SetSkillBaseLevel = D2SetSkillBaseLevel;
    V2SetSkillBaseLevelOnClient = D2SetSkillBaseLevelOnClient;
    V2PrintStat = D2PrintStat;
    V2SendMsgToAll = D2SendMsgToAll;
    V2SetColorPopup = D2SetColorPopup;
    V2LoadImage = D2LoadImage;
    V2PlaySound = D2PlaySound;
    V2GetCharStatsBIN = D2GetCharStatsBIN;
    V2GetItemStatCostBIN = D2GetItemStatCostBIN;
    V2SendToServer = D2SendToServer;
    V2SendPacket = D2SendPacket;
    V2LoadInventory = D2LoadInventory;
    V2CompileCubeInput = D2CompileCubeInput;
    V2BroadcastFunction = D2BroadcastFunction;
    V2GetGameByClientID = D2GetGameByClientID;
    V2SpawnSuperUnique = D2SpawnSuperUnique;
    V2SpawnMonster = D2SpawnMonster;
    V2VerifIfNotCarry1 = D2VerifIfNotCarry1;
    V2GameGetObject = D2GameGetObject;
    V2TestPositionInRoom = D2TestPositionInRoom;
    V2GetItemTypesBIN = D2GetItemTypesBIN;
    V2SaveGame = D2SaveGame;
    V2MonsterUseSkill = D2MonsterUseSkill;
    V2LinkPortal = D2LinkPortal;
    V2Game235C0 = D2Game235C0;
    V2ReadFile = D2ReadFile;
}

void redirect_to_custom_functions() {
    if (version_D2Client == V114d) {
        D2SendToServer3 = (TD2SendToServer3) D2SendToServer3_114;
        D2PrintStat = (TD2PrintStat) D2PrintStat_114;
        D2SendPacket = (TD2SendPacket) D2SendPacket_114;
        D2CompileCubeInput = (TD2CompileCubeInput) D2CompileCubeInput_114;
        D2SpawnSuperUnique = (TD2SpawnSuperUnique) D2SpawnSuperUnique_114;
        D2VerifIfNotCarry1 = (TD2VerifIfNotCarry1) D2VerifIfNotCarry1_111;
        D2isLODGame = D2isLODGame_111;
        D2GetMouseX = D2GetMouseX_111;
        D2GetMouseY = D2GetMouseY_111;
        D2SpawnMonster = (TD2SpawnMonster) D2SpawnMonster_114;
        D2LinkPortal = (TD2LinkPortal) D2LinkPortal_114;
        D2Game235C0 = (TD2Game235C0) D2Game235C0_114;
        D2GetGameByClientID = (TD2GetGameByClientID) D2GetGameByClientID_1XX;
        D2SaveGame = (TD2SaveGame) D2SaveGame_1XX;
    } else if (version_D2Client >= V111) {
        D2SendMsgToAll = (TD2SendMsgToAll) D2SendMsgToAll_111;
        D2SetColorPopup = (TD2SetColorPopup) D2SetColorPopup_111;
        D2LoadImage = (TD2LoadImage) D2LoadImage_111;
        D2FreeImage = (TD2FreeImage) D2FreeImage_111;
        D2PlaySound = (TD2PlaySound) D2PlaySound_111;
        D2GetClient = (TD2GetClient) D2GetClient_111;
        D2SendToServer3 = (TD2SendToServer3) D2SendToServer3_111;
        D2SetSkillBaseLevelOnClient = (TD2SetSkillBaseLevelOnClient) D2SetSkillBaseLevelOnClient_111;
        D2GetCharStatsBIN = (TD2GetCharStatsBIN) D2GetCharStatsBIN_111;
        D2GetItemStatCostBIN = (TD2GetItemStatCostBIN) D2GetItemStatCostBIN_111;
        D2PrintStat = (TD2PrintStat) D2PrintStat_111;
        D2SendPacket = (TD2SendPacket) D2SendPacket_111;
        D2LoadInventory = (TD2LoadInventory) D2LoadInventory_111;
        D2CompileCubeInput = (TD2CompileCubeInput) D2CompileCubeInput_111;
        //D2CompileCubeOutput = (TD2CompileCubeOutput) D2CompileCubeOutput_111;
        D2BroadcastFunction = (TD2BroadcastFunction) D2BroadcastFunction_111;
        D2SpawnSuperUnique = version_D2Game >= V111b ? (TD2SpawnSuperUnique) D2SpawnSuperUnique_111b
                                                     : (TD2SpawnSuperUnique) D2SpawnSuperUnique_111;
        D2VerifIfNotCarry1 = (TD2VerifIfNotCarry1) D2VerifIfNotCarry1_111;
        D2GameGetObject = (TD2GameGetObject) D2GameGetObject_111;
        D2GetItemTypesBIN = (TD2GetItemTypesBIN) D2GetItemTypesBIN_111;
        D2TestPositionInRoom = (TD2TestPositionInRoom) D2TestPositionInRoom_111;
        //D2OpenNPCMenu = (TD2OpenNPCMenu) D2OpenNPCMenu_111;
        D2isLODGame = D2isLODGame_111;
        D2GetDifficultyLevel = D2GetDifficultyLevel_111;
        D2GetMouseX = D2GetMouseX_111;
        D2GetMouseY = D2GetMouseY_111;
        D2GetClientPlayer = D2GetClientPlayer_111;
        D2GetRealItem = D2GetRealItem_111;
        D2CleanStatMouseUp = D2CleanStatMouseUp_111;
        D2MonsterUseSkill = (TD2MonsterUseSkill) D2MonsterUseSkill_111;
        D2ReadFile = (TD2ReadFile) D2ReadFile_111;
        StatMouse1 = (DWORD *) R8(D2Client, 0000, 0000, 0000, 11C004, 11C2F4, 11C040, 11C3DC, 11D224, 3A0650);
        StatMouse2 = (DWORD *) R8(D2Client, 0000, 0000, 0000, 11C008, 11C2F8, 11C044, 11C3E0, 11D228, 3A0654);
        StatMouse3 = (DWORD *) R8(D2Client, 0000, 0000, 0000, 11C020, 11C310, 11C05C, 11C3F8, 11D240, 3A0658);
        StatMouse4 = (DWORD *) R8(D2Client, 0000, 0000, 0000, 11C024, 11C314, 11C060, 11C3FC, 11D244, 3A065C);
    } else {
        D2SendToServer = (TD2SendToServer) D2SendToServer_1XX;
        D2GetGameByClientID = (TD2GetGameByClientID) D2GetGameByClientID_1XX;
        D2SaveGame = (TD2SaveGame) D2SaveGame_1XX;
    }

    if (version_D2Common <= V109d) {
        //D2SetPlayerStat =				(TD2SetPlayerStat) D2SetPlayerStat_9;
        D2AddPlayerStat = (TD2AddPlayerStat) D2AddPlayerStat_9;
        D2GetPlayerStat = (TD2GetPlayerStat) D2GetPlayerStat_9;
        //D2GetPlayerStat20 =				(TD2GetPlayerStat20) D2GetPlayerStat20_9;
        D2GetPlayerBaseStat = (TD2GetPlayerBaseStat) D2GetPlayerBaseStat_9;
        D2SetSkillBaseLevel = (TD2SetSkillBaseLevel) D2SetSkillBaseLevel_9;
        D2GetCharStatsBIN = (TD2GetCharStatsBIN) D2GetCharStatsBIN_9;
        D2GetItemStatCostBIN = (TD2GetItemStatCostBIN) D2GetItemStatCostBIN_9;
        D2GetItemTypesBIN = (TD2GetItemTypesBIN) D2GetItemTypesBIN_9;
    }

    if (version_D2Client <= V109d)
        D2PrintStat = (TD2PrintStat) D2PrintStat_9;

    if (version_D2Game <= V109d)
        D2SetSkillBaseLevelOnClient = (TD2SetSkillBaseLevelOnClient) D2SetSkillBaseLevelOnClient_9;
}

void init_shifting() {
    const int player_data = v8(version_D2Common, 0x5D, 0x5D, 0x5D, 0x49, 0x49, 0x49, 0x49, 0x49, 0x48);
    shifting.ptPYPlayerData = *(DWORD *) ((DWORD) D2InitPlayerData + player_data);
    shifting.ptSpecificData = v8(version_D2Common, 0x70, 0x70, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14);
    shifting.ptGame = v8(version_D2Common, 0xA4, 0xA4, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80);
    shifting.ptClientGame = v8(version_D2Common, 0x170, 0x194, 0x1A8, 0x1A8, 0x1A8, 0x1A8, 0x1A8, 0x1A8, 0x1A8);
    shifting.ptInventory = v8(version_D2Common, 84, 84, 60, 60, 60, 60, 60, 60, 60);
    shifting.ptSkills = v8(version_D2Common, 0xCC, 0xCC, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8);
    shifting.ptImage = v8(version_D2Common, 0x04, 0x04, 0x04, 0x08, 0x08, 0x3C, 0x34, 0x34, 0x34);
    shifting.ptFrame = v8(version_D2Common, 0x08, 0x08, 0x08, 0x44, 0x44, 0x40, 0x00, 0x00, 0x00);
}

void initD2functions() {

#define F8Init(X, Z, A, B, C, D, E, F, G, H, I, R, N, P) \
if (version_##Z > V113d) { N = (T##N)R8(Z,A,B,C,D,E,F,G,H,I); } \
else setFctAddr((DWORD*)&N, (HMODULE)offset_##Z,     \
    (LPCSTR)(version_##Z == V113d? H :               \
    (version_##Z == V113c? G :                       \
    (version_##Z == V112? F :                        \
    (version_##Z == V111b? E :                       \
    (version_##Z == V111? D :                        \
    (version_##Z == V110? C :                        \
    (version_##Z == V109d? B :                       \
    A))))))));
#define A8Init(X, Z, A, B, C, D, E, F, G, H, I, R, N, P) N = (T##N)R8(Z,A,B,C,D,E,F,G,H,I);
#define C8Init(Z, A, B, C, D, E, F, G, H, I, T, N)       pt##N = (T*)R8(Z,A,B,C,D,E,F,G,H,I);

/*TODO:  Warning, all this code is used for macro replacement only */
#include "../Commons/D2InitMacros.h"

    SgptDataTables = *(DataTables **) R8(D2Common, 0000, 0000, 96A20, 9B74C, 9EE8C, 9B500, 99E1C, A33F0, 344304);
    if (version_D2Common < V110) {
        setFctAddr((DWORD *) &D2Common10581, (HMODULE) offset_D2Common, (LPCSTR) 10581);;//ONLY in 1.09
        setFctAddr((DWORD *) &D2Common10598, (HMODULE) offset_D2Common, (LPCSTR) 10598);;//ONLY in 1.09
        setFctAddr((DWORD *) &D2Common10673, (HMODULE) offset_D2Common, (LPCSTR) 10673);;//ONLY in 1.09
    }
#undef F8Init
#undef A8Init
#undef C8Init
#undef D2S
#undef D2F
#undef E2S
#undef E2F
#undef E2C
    misc_fct();
    redirect_to_custom_functions();
    init_shifting();
}

/*================================= END OF FILE =================================*/