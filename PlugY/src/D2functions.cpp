#include "common.h"
#include "D2TypeNameMacros.h"
#include "d2functions.h"
#include "error.h"

namespace PlugY {
    using namespace PlugY;
    s_shifting shifting;
    DataTables *SgptDataTables;

    typedef CharStatsBIN *(__stdcall *TD2Common10581)(DWORD charID);

    TD2Common10581 D2Common10581;//ONLY in 1.09
    typedef ItemStatCostBIN *(__stdcall *TD2Common10598)(DWORD itemStatCostID);

    TD2Common10598 D2Common10598;//ONLY in 1.09
    typedef ItemTypesBIN *(__stdcall *TD2Common10673)(DWORD itemTypesID);

    TD2Common10673 D2Common10673;//ONLY in 1.09

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
        __asm{//(Commons::Unit* ptChar, DWORD statID, DWORD amount, DWORD index)
        PUSH DWORD PTR SS:[ESP+0xC]
        PUSH DWORD PTR SS:[ESP+0xC]
        PUSH DWORD PTR SS:[ESP+0xC]
        CALL V2AddPlayerStat
        RETN 0x10
        }
    }

    __declspec(naked)void D2GetPlayerStat_9() {
        __asm{//(Commons::Unit* ptChar, DWORD statID, DWORD index)
        PUSH DWORD PTR SS:[ESP+0x8]
        PUSH DWORD PTR SS:[ESP+0x8]
        CALL V2GetPlayerStat
        RETN 0x0C
        }
    }

    __declspec(naked)void D2GetPlayerBaseStat_9() {
        __asm{//(Commons::Unit* ptChar, DWORD statID, DWORD index)
        PUSH DWORD PTR SS:[ESP+0x8]
        PUSH DWORD PTR SS:[ESP+0x8]
        CALL V2GetPlayerBaseStat
        RETN 0x0C
        }
    }

    __declspec(naked)void D2SetSkillBaseLevel_9() {
        __asm{//(Commons::Unit* ptChar, DWORD skillID, DWORD slvl, DWORD bRemove, char*, DWORD));
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
    FASTCALL D2PrintStat_9(Commons::Unit *ptItem, Stats *ptStats, DWORD statID, DWORD statIndex, DWORD statValue, LPWSTR lpText) {
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

    DWORD FASTCALL    D2isLODGame_111() { return (*ptIsLodGame); }

    BYTE FASTCALL    D2GetDifficultyLevel_111() { return (*ptDifficultyLevel); }

    DWORD STDCALL    D2GetMouseX_111() { return (*ptMouseX); }

    DWORD STDCALL    D2GetMouseY_111() { return (*ptMouseY); }

    Unit *STDCALL    D2GetClientPlayer_111() { return (*ptptClientChar); }

    DWORD *StatMouse1, *StatMouse2, *StatMouse3, *StatMouse4;

    void FASTCALL D2CleanStatMouseUp_111() { *StatMouse1 = *StatMouse2 = *StatMouse3 = *StatMouse4 = 0; }

    Unit *STDCALL    D2GetRealItem_111(Commons::Unit *ptItem) { return ptItem; }

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
            StatMouse1 = (DWORD *) (offset_D2Client + (version_D2Client == V114d ? 0x3A0650 : (version_D2Client == V113d ? 0x11D224 : (version_D2Client == V113c ? 0x11C3DC : (version_D2Client == V112 ? 0x11C040 : (version_D2Client == V111b ? 0x11C2F4 : (version_D2Client == V111 ? 0x11C004 : (version_D2Client == V110 ? 0x0000 : (version_D2Client == V109d ? 0x0000 : 0x0000)))))))));
            StatMouse2 = (DWORD *) (offset_D2Client + (version_D2Client == V114d ? 0x3A0654 : (version_D2Client == V113d ? 0x11D228 : (version_D2Client == V113c ? 0x11C3E0 : (version_D2Client == V112 ? 0x11C044 : (version_D2Client == V111b ? 0x11C2F8 : (version_D2Client == V111 ? 0x11C008 : (version_D2Client == V110 ? 0x0000 : (version_D2Client == V109d ? 0x0000 : 0x0000)))))))));
            StatMouse3 = (DWORD *) (offset_D2Client + (version_D2Client == V114d ? 0x3A0658 : (version_D2Client == V113d ? 0x11D240 : (version_D2Client == V113c ? 0x11C3F8 : (version_D2Client == V112 ? 0x11C05C : (version_D2Client == V111b ? 0x11C310 : (version_D2Client == V111 ? 0x11C020 : (version_D2Client == V110 ? 0x0000 : (version_D2Client == V109d ? 0x0000 : 0x0000)))))))));
            StatMouse4 = (DWORD *) (offset_D2Client + (version_D2Client == V114d ? 0x3A065C : (version_D2Client == V113d ? 0x11D244 : (version_D2Client == V113c ? 0x11C3FC : (version_D2Client == V112 ? 0x11C060 : (version_D2Client == V111b ? 0x11C314 : (version_D2Client == V111 ? 0x11C024 : (version_D2Client == V110 ? 0x0000 : (version_D2Client == V109d ? 0x0000 : 0x0000)))))))));
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
    DWORD getAddressOfVersion(eGameVersion version, DWORD defaultValue, DWORD v109d, DWORD v110, DWORD v111, DWORD v111b, DWORD v112, DWORD v113c, DWORD v113d, DWORD v114d) {
        using namespace Commons;
        std::map<eGameVersion, DWORD> versions = {
                {V114d, v114d},
                {V113d, v113d},
                {V113c, v113c},
                {V112,  v112},
                {V111b, v111b},
                {V111,  v111},
                {V110,  v110},
                {V109d, v109d},
        };
        auto result = versions.find(version);
        return result != versions.end() ? result->second : defaultValue;
    }

    void init_shifting() {
        const DWORD player_data = getAddressOfVersion(version_D2Common, 0x5D, 0x5D, 0x5D, 0x49, 0x49, 0x49, 0x49, 0x49, 0x48);
        shifting.ptPYPlayerData = *(DWORD *) ((DWORD) D2InitPlayerData + player_data);
        shifting.ptSpecificData = getAddressOfVersion(version_D2Common, 0x70, 0x70, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14);
        shifting.ptGame = getAddressOfVersion(version_D2Common, 0xA4, 0xA4, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80);
        shifting.ptClientGame = getAddressOfVersion(version_D2Common, 0x170, 0x194, 0x1A8, 0x1A8, 0x1A8, 0x1A8, 0x1A8, 0x1A8, 0x1A8);
        shifting.ptInventory = getAddressOfVersion(version_D2Common, 84, 84, 60, 60, 60, 60, 60, 60, 60);
        shifting.ptSkills = getAddressOfVersion(version_D2Common, 0xCC, 0xCC, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8);
        shifting.ptImage = getAddressOfVersion(version_D2Common, 0x04, 0x04, 0x04, 0x08, 0x08, 0x3C, 0x34, 0x34, 0x34);
        shifting.ptFrame = getAddressOfVersion(version_D2Common, 0x08, 0x08, 0x08, 0x44, 0x44, 0x40, 0x00, 0x00, 0x00);
    }

    DWORD RX(DWORD v) {
        return (*ptWindowStartX) + v;
    }

    DWORD RY(DWORD y) {
        return (*ptResolutionY) + (*ptNegWindowStartY) - (y);
    }

    std::map<D2DllName, eGameVersion> init_dll_versions() {
        return {
                {game,     version_Game},
                {D2Client, version_D2Client},
                {D2Common, version_D2Common},
                {D2Game,   version_D2Game},
                {D2gfx,    version_D2gfx},
                {D2Lang,   version_D2Lang},
                {D2Launch, version_D2Launch},
                {D2Net,    version_D2Net},
                {D2Win,    version_D2Win},
                {Fog,      version_Fog},
                {Storm,    version_Storm}
        };
    }

    std::map<D2DllName, DWORD> init_dll_offsets() {
        return {
                {game,     offset_Game},
                {D2Client, offset_D2Client},
                {D2Common, offset_D2Common},
                {D2Game,   offset_D2Game},
                {D2gfx,    offset_D2gfx},
                {D2Lang,   offset_D2Lang},
                {D2Launch, offset_D2Launch},
                {D2Net,    offset_D2Net},
                {D2Win,    offset_D2Win},
                {Fog,      offset_Fog},
                {Storm,    offset_Storm}
        };
    }

    void init_dll_maps() {
        dllVersions = init_dll_versions();
        dllOffsets = init_dll_offsets();
    }

    std::map<D2DllName, eGameVersion> dllVersions;
    std::map<D2DllName, DWORD> dllOffsets;


    void initD2functions() {



        if (version_D2Common > V113d) { D2Common11084 = (TD2Common11084) (offset_D2Common + (version_D2Common == V114d ? 0x21AED0 : (version_D2Common == V113d ? 0x10907 : (version_D2Common == V113c ? 0x10346 : (version_D2Common == V112 ? 0x11109 : (version_D2Common == V111b ? 0x11084 : (version_D2Common == V111 ? 0x10188 : (version_D2Common == V110 ? 0x00000 : (version_D2Common == V109d ? 0x00000 : 0x00000))))))))); } else setFctAddr((DWORD *) &D2Common11084, (HMODULE) offset_D2Common, (LPCSTR) (version_D2Common == V113d ? 10907 : (version_D2Common == V113c ? 10346 : (version_D2Common == V112 ? 11109 : (version_D2Common == V111b ? 11084 : (version_D2Common == V111 ? 10188 : (version_D2Common == V110 ? 00000 : (version_D2Common == V109d ? 00000 : 00000))))))));
        if (version_D2Common > V113d) { D2GetLevelID = (TD2GetLevelID) (offset_D2Common + (version_D2Common == V114d ? 0x21A1B0 : (version_D2Common == V113d ? 0x10691 : (version_D2Common == V113c ? 0x10826 : (version_D2Common == V112 ? 0x10511 : (version_D2Common == V111b ? 0x11021 : (version_D2Common == V111 ? 0x10332 : (version_D2Common == V110 ? 0x10057 : (version_D2Common == V109d ? 0x10057 : 0x10057))))))))); } else setFctAddr((DWORD *) &D2GetLevelID, (HMODULE) offset_D2Common, (LPCSTR) (version_D2Common == V113d ? 10691 : (version_D2Common == V113c ? 10826 : (version_D2Common == V112 ? 10511 : (version_D2Common == V111b ? 11021 : (version_D2Common == V111 ? 10332 : (version_D2Common == V110 ? 10057 : (version_D2Common == V109d ? 10057 : 10057))))))));
        if (version_D2Common > V113d) { D2GetDropRoom = (TD2GetDropRoom) (offset_D2Common + (version_D2Common == V114d ? 0x24E810 : (version_D2Common == V113d ? 0x10716 : (version_D2Common == V113c ? 0x10654 : (version_D2Common == V112 ? 0x11043 : (version_D2Common == V111b ? 0x10491 : (version_D2Common == V111 ? 0x10623 : (version_D2Common == V110 ? 0x10138 : (version_D2Common == V109d ? 0x10138 : 0x10138))))))))); } else setFctAddr((DWORD *) &D2GetDropRoom, (HMODULE) offset_D2Common, (LPCSTR) (version_D2Common == V113d ? 10716 : (version_D2Common == V113c ? 10654 : (version_D2Common == V112 ? 11043 : (version_D2Common == V111b ? 10491 : (version_D2Common == V111 ? 10623 : (version_D2Common == V110 ? 10138 : (version_D2Common == V109d ? 10138 : 10138))))))));
        if (version_D2Common > V113d) { D2Common10242 = (TD2Common10242) (offset_D2Common + (version_D2Common == V114d ? 0x00000 : (version_D2Common == V113d ? 0x00000 : (version_D2Common == V113c ? 0x00000 : (version_D2Common == V112 ? 0x00000 : (version_D2Common == V111b ? 0x00000 : (version_D2Common == V111 ? 0x00000 : (version_D2Common == V110 ? 0x10242 : (version_D2Common == V109d ? 0x10242 : 0x10242))))))))); } else setFctAddr((DWORD *) &D2Common10242, (HMODULE) offset_D2Common, (LPCSTR) (version_D2Common == V113d ? 00000 : (version_D2Common == V113c ? 00000 : (version_D2Common == V112 ? 00000 : (version_D2Common == V111b ? 00000 : (version_D2Common == V111 ? 00000 : (version_D2Common == V110 ? 10242 : (version_D2Common == V109d ? 10242 : 10242))))))));
        if (version_D2Common > V113d) { D2CanPutItemInInv = (TD2CanPutItemInInv) (offset_D2Common + (version_D2Common == V114d ? 0x23B950 : (version_D2Common == V113d ? 0x10402 : (version_D2Common == V113c ? 0x10133 : (version_D2Common == V112 ? 0x10289 : (version_D2Common == V111b ? 0x10813 : (version_D2Common == V111 ? 0x10855 : (version_D2Common == V110 ? 0x10246 : (version_D2Common == V109d ? 0x10246 : 0x10246))))))))); } else setFctAddr((DWORD *) &D2CanPutItemInInv, (HMODULE) offset_D2Common, (LPCSTR) (version_D2Common == V113d ? 10402 : (version_D2Common == V113c ? 10133 : (version_D2Common == V112 ? 10289 : (version_D2Common == V111b ? 10813 : (version_D2Common == V111 ? 10855 : (version_D2Common == V110 ? 10246 : (version_D2Common == V109d ? 10246 : 10246))))))));
        if (version_D2Common > V113d) { D2InvRemoveItem = (TD2InvRemoveItem) (offset_D2Common + (version_D2Common == V114d ? 0x23AD90 : (version_D2Common == V113d ? 0x10490 : (version_D2Common == V113c ? 0x10646 : (version_D2Common == V112 ? 0x10936 : (version_D2Common == V111b ? 0x10827 : (version_D2Common == V111 ? 0x10461 : (version_D2Common == V110 ? 0x10243 : (version_D2Common == V109d ? 0x10243 : 0x10243))))))))); } else setFctAddr((DWORD *) &D2InvRemoveItem, (HMODULE) offset_D2Common, (LPCSTR) (version_D2Common == V113d ? 10490 : (version_D2Common == V113c ? 10646 : (version_D2Common == V112 ? 10936 : (version_D2Common == V111b ? 10827 : (version_D2Common == V111 ? 10461 : (version_D2Common == V110 ? 10243 : (version_D2Common == V109d ? 10243 : 10243))))))));
        if (version_D2Common > V113d) { D2InvAddItem = (TD2InvAddItem) (offset_D2Common + (version_D2Common == V114d ? 0x23BCC0 : (version_D2Common == V113d ? 0x10963 : (version_D2Common == V113c ? 0x11107 : (version_D2Common == V112 ? 0x10436 : (version_D2Common == V111b ? 0x11068 : (version_D2Common == V111 ? 0x10880 : (version_D2Common == V110 ? 0x10249 : (version_D2Common == V109d ? 0x10249 : 0x10249))))))))); } else setFctAddr((DWORD *) &D2InvAddItem, (HMODULE) offset_D2Common, (LPCSTR) (version_D2Common == V113d ? 10963 : (version_D2Common == V113c ? 11107 : (version_D2Common == V112 ? 10436 : (version_D2Common == V111b ? 11068 : (version_D2Common == V111 ? 10880 : (version_D2Common == V110 ? 10249 : (version_D2Common == V109d ? 10249 : 10249))))))));
        if (version_D2Common > V113d) { D2Common10250 = (TD2Common10250) (offset_D2Common + (version_D2Common == V114d ? 0x00000 : (version_D2Common == V113d ? 0x00000 : (version_D2Common == V113c ? 0x00000 : (version_D2Common == V112 ? 0x00000 : (version_D2Common == V111b ? 0x00000 : (version_D2Common == V111 ? 0x00000 : (version_D2Common == V110 ? 0x10250 : (version_D2Common == V109d ? 0x10250 : 0x10250))))))))); } else setFctAddr((DWORD *) &D2Common10250, (HMODULE) offset_D2Common, (LPCSTR) (version_D2Common == V113d ? 00000 : (version_D2Common == V113c ? 00000 : (version_D2Common == V112 ? 00000 : (version_D2Common == V111b ? 00000 : (version_D2Common == V111 ? 00000 : (version_D2Common == V110 ? 10250 : (version_D2Common == V109d ? 10250 : 10250))))))));
        if (version_D2Common > V113d) { D2Common10273 = (TD2Common10273) (offset_D2Common + (version_D2Common == V114d ? 0x00000 : (version_D2Common == V113d ? 0x00000 : (version_D2Common == V113c ? 0x00000 : (version_D2Common == V112 ? 0x00000 : (version_D2Common == V111b ? 0x00000 : (version_D2Common == V111 ? 0x00000 : (version_D2Common == V110 ? 0x10273 : (version_D2Common == V109d ? 0x10273 : 0x10273))))))))); } else setFctAddr((DWORD *) &D2Common10273, (HMODULE) offset_D2Common, (LPCSTR) (version_D2Common == V113d ? 00000 : (version_D2Common == V113c ? 00000 : (version_D2Common == V112 ? 00000 : (version_D2Common == V111b ? 00000 : (version_D2Common == V111 ? 00000 : (version_D2Common == V110 ? 10273 : (version_D2Common == V109d ? 10273 : 10273))))))));
        if (version_D2Common > V113d) { D2InventoryGetFirstItem = (TD2InventoryGetFirstItem) (offset_D2Common + (version_D2Common == V114d ? 0x23B2C0 : (version_D2Common == V113d ? 0x11040 : (version_D2Common == V113c ? 0x10460 : (version_D2Common == V112 ? 0x11151 : (version_D2Common == V111b ? 0x10535 : (version_D2Common == V111 ? 0x10402 : (version_D2Common == V110 ? 0x10277 : (version_D2Common == V109d ? 0x10277 : 0x10277))))))))); } else setFctAddr((DWORD *) &D2InventoryGetFirstItem, (HMODULE) offset_D2Common, (LPCSTR) (version_D2Common == V113d ? 11040 : (version_D2Common == V113c ? 10460 : (version_D2Common == V112 ? 11151 : (version_D2Common == V111b ? 10535 : (version_D2Common == V111 ? 10402 : (version_D2Common == V110 ? 10277 : (version_D2Common == V109d ? 10277 : 10277))))))));
        if (version_D2Common > V113d) { D2UnitGetNextItem = (TD2UnitGetNextItem) (offset_D2Common + (version_D2Common == V114d ? 0x23DFA0 : (version_D2Common == V113d ? 0x10879 : (version_D2Common == V113c ? 0x10464 : (version_D2Common == V112 ? 0x10770 : (version_D2Common == V111b ? 0x11140 : (version_D2Common == V111 ? 0x10934 : (version_D2Common == V110 ? 0x10304 : (version_D2Common == V109d ? 0x10304 : 0x10304))))))))); } else setFctAddr((DWORD *) &D2UnitGetNextItem, (HMODULE) offset_D2Common, (LPCSTR) (version_D2Common == V113d ? 10879 : (version_D2Common == V113c ? 10464 : (version_D2Common == V112 ? 10770 : (version_D2Common == V111b ? 11140 : (version_D2Common == V111 ? 10934 : (version_D2Common == V110 ? 10304 : (version_D2Common == V109d ? 10304 : 10304))))))));
        if (version_D2Common > V113d) { D2GetRealItem = (TD2GetRealItem) (offset_D2Common + (version_D2Common == V114d ? 0x23DFD0 : (version_D2Common == V113d ? 0x10897 : (version_D2Common == V113c ? 0x11147 : (version_D2Common == V112 ? 0x10852 : (version_D2Common == V111b ? 0x10748 : (version_D2Common == V111 ? 0x11095 : (version_D2Common == V110 ? 0x10305 : (version_D2Common == V109d ? 0x10305 : 0x10305))))))))); } else setFctAddr((DWORD *) &D2GetRealItem, (HMODULE) offset_D2Common, (LPCSTR) (version_D2Common == V113d ? 10897 : (version_D2Common == V113c ? 11147 : (version_D2Common == V112 ? 10852 : (version_D2Common == V111b ? 10748 : (version_D2Common == V111 ? 11095 : (version_D2Common == V110 ? 10305 : (version_D2Common == V109d ? 10305 : 10305))))))));
        if (version_D2Common > V113d) { D2GetPosX = (TD2GetPosX) (offset_D2Common + (version_D2Common == V114d ? 0x00000 : (version_D2Common == V113d ? 0x00000 : (version_D2Common == V113c ? 0x00000 : (version_D2Common == V112 ? 0x00000 : (version_D2Common == V111b ? 0x00000 : (version_D2Common == V111 ? 0x00000 : (version_D2Common == V110 ? 0x00000 : (version_D2Common == V109d ? 0x10326 : 0x10326))))))))); } else setFctAddr((DWORD *) &D2GetPosX, (HMODULE) offset_D2Common, (LPCSTR) (version_D2Common == V113d ? 00000 : (version_D2Common == V113c ? 00000 : (version_D2Common == V112 ? 00000 : (version_D2Common == V111b ? 00000 : (version_D2Common == V111 ? 00000 : (version_D2Common == V110 ? 00000 : (version_D2Common == V109d ? 10326 : 10326))))))));
        if (version_D2Common > V113d) { D2GetPosY = (TD2GetPosY) (offset_D2Common + (version_D2Common == V114d ? 0x00000 : (version_D2Common == V113d ? 0x00000 : (version_D2Common == V113c ? 0x00000 : (version_D2Common == V112 ? 0x00000 : (version_D2Common == V111b ? 0x00000 : (version_D2Common == V111 ? 0x00000 : (version_D2Common == V110 ? 0x00000 : (version_D2Common == V109d ? 0x10329 : 0x10329))))))))); } else setFctAddr((DWORD *) &D2GetPosY, (HMODULE) offset_D2Common, (LPCSTR) (version_D2Common == V113d ? 00000 : (version_D2Common == V113c ? 00000 : (version_D2Common == V112 ? 00000 : (version_D2Common == V111b ? 00000 : (version_D2Common == V111 ? 00000 : (version_D2Common == V110 ? 00000 : (version_D2Common == V109d ? 10329 : 10329))))))));
        if (version_D2Common > V113d) { D2GetPosition = (TD2GetPosition) (offset_D2Common + (version_D2Common == V114d ? 0x220870 : (version_D2Common == V113d ? 0x11166 : (version_D2Common == V113c ? 0x10141 : (version_D2Common == V112 ? 0x10543 : (version_D2Common == V111b ? 0x10056 : (version_D2Common == V111 ? 0x11080 : (version_D2Common == V110 ? 0x10332 : (version_D2Common == V109d ? 0x10332 : 0x10332))))))))); } else setFctAddr((DWORD *) &D2GetPosition, (HMODULE) offset_D2Common, (LPCSTR) (version_D2Common == V113d ? 11166 : (version_D2Common == V113c ? 10141 : (version_D2Common == V112 ? 10543 : (version_D2Common == V111b ? 10056 : (version_D2Common == V111 ? 11080 : (version_D2Common == V110 ? 10332 : (version_D2Common == V109d ? 10332 : 10332))))))));
        if (version_D2Common > V113d) { D2GetMaxGoldBank = (TD2GetMaxGoldBank) (offset_D2Common + (version_D2Common == V114d ? 0x223460 : (version_D2Common == V113d ? 0x11025 : (version_D2Common == V113c ? 0x11060 : (version_D2Common == V112 ? 0x10941 : (version_D2Common == V111b ? 0x10864 : (version_D2Common == V111 ? 0x10455 : (version_D2Common == V110 ? 0x10339 : (version_D2Common == V109d ? 0x10339 : 0x10339))))))))); } else setFctAddr((DWORD *) &D2GetMaxGoldBank, (HMODULE) offset_D2Common, (LPCSTR) (version_D2Common == V113d ? 11025 : (version_D2Common == V113c ? 11060 : (version_D2Common == V112 ? 10941 : (version_D2Common == V111b ? 10864 : (version_D2Common == V111 ? 10455 : (version_D2Common == V110 ? 10339 : (version_D2Common == V109d ? 10339 : 10339))))))));
        if (version_D2Common > V113d) { D2GetRoom = (TD2GetRoom) (offset_D2Common + (version_D2Common == V114d ? 0x220BB0 : (version_D2Common == V113d ? 0x10846 : (version_D2Common == V113c ? 0x10331 : (version_D2Common == V112 ? 0x10366 : (version_D2Common == V111b ? 0x10933 : (version_D2Common == V111 ? 0x10172 : (version_D2Common == V110 ? 0x10342 : (version_D2Common == V109d ? 0x10342 : 0x10342))))))))); } else setFctAddr((DWORD *) &D2GetRoom, (HMODULE) offset_D2Common, (LPCSTR) (version_D2Common == V113d ? 10846 : (version_D2Common == V113c ? 10331 : (version_D2Common == V112 ? 10366 : (version_D2Common == V111b ? 10933 : (version_D2Common == V111 ? 10172 : (version_D2Common == V110 ? 10342 : (version_D2Common == V109d ? 10342 : 10342))))))));
        if (version_D2Common > V113d) { D2InitPlayerData = (TD2InitPlayerData) (offset_D2Common + (version_D2Common == V114d ? 0x221F90 : (version_D2Common == V113d ? 0x10404 : (version_D2Common == V113c ? 0x10356 : (version_D2Common == V112 ? 0x11097 : (version_D2Common == V111b ? 0x10079 : (version_D2Common == V111 ? 0x10218 : (version_D2Common == V110 ? 0x10420 : (version_D2Common == V109d ? 0x10420 : 0x10420))))))))); } else setFctAddr((DWORD *) &D2InitPlayerData, (HMODULE) offset_D2Common, (LPCSTR) (version_D2Common == V113d ? 10404 : (version_D2Common == V113c ? 10356 : (version_D2Common == V112 ? 11097 : (version_D2Common == V111b ? 10079 : (version_D2Common == V111 ? 10218 : (version_D2Common == V110 ? 10420 : (version_D2Common == V109d ? 10420 : 10420))))))));
        if (version_D2Common > V113d) { D2GetPlayerData = (TD2GetPlayerData) (offset_D2Common + (version_D2Common == V114d ? 0x2221A0 : (version_D2Common == V113d ? 0x11103 : (version_D2Common == V113c ? 0x10920 : (version_D2Common == V112 ? 0x10860 : (version_D2Common == V111b ? 0x10800 : (version_D2Common == V111 ? 0x10562 : (version_D2Common == V110 ? 0x10424 : (version_D2Common == V109d ? 0x10424 : 0x10424))))))))); } else setFctAddr((DWORD *) &D2GetPlayerData, (HMODULE) offset_D2Common, (LPCSTR) (version_D2Common == V113d ? 11103 : (version_D2Common == V113c ? 10920 : (version_D2Common == V112 ? 10860 : (version_D2Common == V111b ? 10800 : (version_D2Common == V111 ? 10562 : (version_D2Common == V110 ? 10424 : (version_D2Common == V109d ? 10424 : 10424))))))));
        if (version_D2Common > V113d) { D2GetDefence = (TD2GetDefence) (offset_D2Common + (version_D2Common == V114d ? 0x00000 : (version_D2Common == V113d ? 0x00000 : (version_D2Common == V113c ? 0x00000 : (version_D2Common == V112 ? 0x00000 : (version_D2Common == V111b ? 0x00000 : (version_D2Common == V111 ? 0x00000 : (version_D2Common == V110 ? 0x10431 : (version_D2Common == V109d ? 0x10431 : 0x10431))))))))); } else setFctAddr((DWORD *) &D2GetDefence, (HMODULE) offset_D2Common, (LPCSTR) (version_D2Common == V113d ? 00000 : (version_D2Common == V113c ? 00000 : (version_D2Common == V112 ? 00000 : (version_D2Common == V111b ? 00000 : (version_D2Common == V111 ? 00000 : (version_D2Common == V110 ? 10431 : (version_D2Common == V109d ? 10431 : 10431))))))));
        if (version_D2Common > V113d) { D2GetChanceToBlock = (TD2GetChanceToBlock) (offset_D2Common + (version_D2Common == V114d ? 0x00000 : (version_D2Common == V113d ? 0x00000 : (version_D2Common == V113c ? 0x00000 : (version_D2Common == V112 ? 0x00000 : (version_D2Common == V111b ? 0x00000 : (version_D2Common == V111 ? 0x00000 : (version_D2Common == V110 ? 0x10433 : (version_D2Common == V109d ? 0x10433 : 0x10433))))))))); } else setFctAddr((DWORD *) &D2GetChanceToBlock, (HMODULE) offset_D2Common, (LPCSTR) (version_D2Common == V113d ? 00000 : (version_D2Common == V113c ? 00000 : (version_D2Common == V112 ? 00000 : (version_D2Common == V111b ? 00000 : (version_D2Common == V111 ? 00000 : (version_D2Common == V110 ? 10433 : (version_D2Common == V109d ? 10433 : 10433))))))));
        if (version_D2Common > V113d) { D2GetMaxGold = (TD2GetMaxGold) (offset_D2Common + (version_D2Common == V114d ? 0x222E70 : (version_D2Common == V113d ? 0x11159 : (version_D2Common == V113c ? 0x10049 : (version_D2Common == V112 ? 0x10729 : (version_D2Common == V111b ? 0x11131 : (version_D2Common == V111 ? 0x10343 : (version_D2Common == V110 ? 0x10439 : (version_D2Common == V109d ? 0x10439 : 0x10439))))))))); } else setFctAddr((DWORD *) &D2GetMaxGold, (HMODULE) offset_D2Common, (LPCSTR) (version_D2Common == V113d ? 11159 : (version_D2Common == V113c ? 10049 : (version_D2Common == V112 ? 10729 : (version_D2Common == V111b ? 11131 : (version_D2Common == V111 ? 10343 : (version_D2Common == V110 ? 10439 : (version_D2Common == V109d ? 10439 : 10439))))))));
        if (version_D2Common > V113d) { D2Common10572 = (TD2Common10572) (offset_D2Common + (version_D2Common == V114d ? 0x224690 : (version_D2Common == V113d ? 0x10193 : (version_D2Common == V113c ? 0x11090 : (version_D2Common == V112 ? 0x10481 : (version_D2Common == V111b ? 0x10572 : (version_D2Common == V111 ? 0x10440 : (version_D2Common == V110 ? 0x00000 : (version_D2Common == V109d ? 0x00000 : 0x00000))))))))); } else setFctAddr((DWORD *) &D2Common10572, (HMODULE) offset_D2Common, (LPCSTR) (version_D2Common == V113d ? 10193 : (version_D2Common == V113c ? 11090 : (version_D2Common == V112 ? 10481 : (version_D2Common == V111b ? 10572 : (version_D2Common == V111 ? 10440 : (version_D2Common == V110 ? 00000 : (version_D2Common == V109d ? 00000 : 00000))))))));
        if (version_D2Common > V113d) { D2GetObjectFlags = (TD2GetObjectFlags) (offset_D2Common + (version_D2Common == V114d ? 0x2222C0 : (version_D2Common == V113d ? 0x10040 : (version_D2Common == V113c ? 0x10258 : (version_D2Common == V112 ? 0x10866 : (version_D2Common == V111b ? 0x11160 : (version_D2Common == V111 ? 0x10471 : (version_D2Common == V110 ? 0x00000 : (version_D2Common == V109d ? 0x00000 : 0x00000))))))))); } else setFctAddr((DWORD *) &D2GetObjectFlags, (HMODULE) offset_D2Common, (LPCSTR) (version_D2Common == V113d ? 10040 : (version_D2Common == V113c ? 10258 : (version_D2Common == V112 ? 10866 : (version_D2Common == V111b ? 11160 : (version_D2Common == V111 ? 10471 : (version_D2Common == V110 ? 00000 : (version_D2Common == V109d ? 00000 : 00000))))))));
        if (version_D2Common > V113d) { D2SetObjectFlags = (TD2SetObjectFlags) (offset_D2Common + (version_D2Common == V114d ? 0x222300 : (version_D2Common == V113d ? 0x10033 : (version_D2Common == V113c ? 0x10111 : (version_D2Common == V112 ? 0x10150 : (version_D2Common == V111b ? 0x11048 : (version_D2Common == V111 ? 0x10572 : (version_D2Common == V110 ? 0x00000 : (version_D2Common == V109d ? 0x00000 : 0x00000))))))))); } else setFctAddr((DWORD *) &D2SetObjectFlags, (HMODULE) offset_D2Common, (LPCSTR) (version_D2Common == V113d ? 10033 : (version_D2Common == V113c ? 10111 : (version_D2Common == V112 ? 10150 : (version_D2Common == V111b ? 11048 : (version_D2Common == V111 ? 10572 : (version_D2Common == V110 ? 00000 : (version_D2Common == V109d ? 00000 : 00000))))))));
        if (version_D2Common > V113d) { D2isInState = (TD2isInState) (offset_D2Common + (version_D2Common == V114d ? 0x00000 : (version_D2Common == V113d ? 0x00000 : (version_D2Common == V113c ? 0x00000 : (version_D2Common == V112 ? 0x00000 : (version_D2Common == V111b ? 0x00000 : (version_D2Common == V111 ? 0x00000 : (version_D2Common == V110 ? 0x10487 : (version_D2Common == V109d ? 0x10487 : 0x10487))))))))); } else setFctAddr((DWORD *) &D2isInState, (HMODULE) offset_D2Common, (LPCSTR) (version_D2Common == V113d ? 00000 : (version_D2Common == V113c ? 00000 : (version_D2Common == V112 ? 00000 : (version_D2Common == V111b ? 00000 : (version_D2Common == V111 ? 00000 : (version_D2Common == V110 ? 10487 : (version_D2Common == V109d ? 10487 : 10487))))))));
        if (version_D2Common > V113d) { D2AddPlayerStat = (TD2AddPlayerStat) (offset_D2Common + (version_D2Common == V114d ? 0x2272B0 : (version_D2Common == V113d ? 0x10645 : (version_D2Common == V113c ? 0x10551 : (version_D2Common == V112 ? 0x10762 : (version_D2Common == V111b ? 0x10627 : (version_D2Common == V111 ? 0x10109 : (version_D2Common == V110 ? 0x10518 : (version_D2Common == V109d ? 0x10518 : 0x10518))))))))); } else setFctAddr((DWORD *) &D2AddPlayerStat, (HMODULE) offset_D2Common, (LPCSTR) (version_D2Common == V113d ? 10645 : (version_D2Common == V113c ? 10551 : (version_D2Common == V112 ? 10762 : (version_D2Common == V111b ? 10627 : (version_D2Common == V111 ? 10109 : (version_D2Common == V110 ? 10518 : (version_D2Common == V109d ? 10518 : 10518))))))));
        if (version_D2Common > V113d) { D2GetPlayerStat = (TD2GetPlayerStat) (offset_D2Common + (version_D2Common == V114d ? 0x225480 : (version_D2Common == V113d ? 0x10550 : (version_D2Common == V113c ? 0x10973 : (version_D2Common == V112 ? 0x10658 : (version_D2Common == V111b ? 0x10061 : (version_D2Common == V111 ? 0x11092 : (version_D2Common == V110 ? 0x10519 : (version_D2Common == V109d ? 0x10519 : 0x10519))))))))); } else setFctAddr((DWORD *) &D2GetPlayerStat, (HMODULE) offset_D2Common, (LPCSTR) (version_D2Common == V113d ? 10550 : (version_D2Common == V113c ? 10973 : (version_D2Common == V112 ? 10658 : (version_D2Common == V111b ? 10061 : (version_D2Common == V111 ? 11092 : (version_D2Common == V110 ? 10519 : (version_D2Common == V109d ? 10519 : 10519))))))));
        if (version_D2Common > V113d) { D2GetPlayerBaseStat = (TD2GetPlayerBaseStat) (offset_D2Common + (version_D2Common == V114d ? 0x2253B0 : (version_D2Common == V113d ? 0x10216 : (version_D2Common == V113c ? 0x10587 : (version_D2Common == V112 ? 0x10494 : (version_D2Common == V111b ? 0x10550 : (version_D2Common == V111 ? 0x10733 : (version_D2Common == V110 ? 0x10521 : (version_D2Common == V109d ? 0x10521 : 0x10521))))))))); } else setFctAddr((DWORD *) &D2GetPlayerBaseStat, (HMODULE) offset_D2Common, (LPCSTR) (version_D2Common == V113d ? 10216 : (version_D2Common == V113c ? 10587 : (version_D2Common == V112 ? 10494 : (version_D2Common == V111b ? 10550 : (version_D2Common == V111 ? 10733 : (version_D2Common == V110 ? 10521 : (version_D2Common == V109d ? 10521 : 10521))))))));
        if (version_D2Common > V113d) { D2haveDefenceBonus = (TD2haveDefenceBonus) (offset_D2Common + (version_D2Common == V114d ? 0x00000 : (version_D2Common == V113d ? 0x00000 : (version_D2Common == V113c ? 0x00000 : (version_D2Common == V112 ? 0x00000 : (version_D2Common == V111b ? 0x00000 : (version_D2Common == V111 ? 0x00000 : (version_D2Common == V110 ? 0x10539 : (version_D2Common == V109d ? 0x10539 : 0x10539))))))))); } else setFctAddr((DWORD *) &D2haveDefenceBonus, (HMODULE) offset_D2Common, (LPCSTR) (version_D2Common == V113d ? 00000 : (version_D2Common == V113c ? 00000 : (version_D2Common == V112 ? 00000 : (version_D2Common == V111b ? 00000 : (version_D2Common == V111 ? 00000 : (version_D2Common == V110 ? 10539 : (version_D2Common == V109d ? 10539 : 10539))))))));
        if (version_D2Common > V113d) { D2haveFireResBonus = (TD2haveFireResBonus) (offset_D2Common + (version_D2Common == V114d ? 0x00000 : (version_D2Common == V113d ? 0x00000 : (version_D2Common == V113c ? 0x00000 : (version_D2Common == V112 ? 0x00000 : (version_D2Common == V111b ? 0x00000 : (version_D2Common == V111 ? 0x00000 : (version_D2Common == V110 ? 0x10540 : (version_D2Common == V109d ? 0x10540 : 0x10540))))))))); } else setFctAddr((DWORD *) &D2haveFireResBonus, (HMODULE) offset_D2Common, (LPCSTR) (version_D2Common == V113d ? 00000 : (version_D2Common == V113c ? 00000 : (version_D2Common == V112 ? 00000 : (version_D2Common == V111b ? 00000 : (version_D2Common == V111 ? 00000 : (version_D2Common == V110 ? 10540 : (version_D2Common == V109d ? 10540 : 10540))))))));
        if (version_D2Common > V113d) { D2haveColdResBonus = (TD2haveColdResBonus) (offset_D2Common + (version_D2Common == V114d ? 0x00000 : (version_D2Common == V113d ? 0x00000 : (version_D2Common == V113c ? 0x00000 : (version_D2Common == V112 ? 0x00000 : (version_D2Common == V111b ? 0x00000 : (version_D2Common == V111 ? 0x00000 : (version_D2Common == V110 ? 0x10541 : (version_D2Common == V109d ? 0x10541 : 0x10541))))))))); } else setFctAddr((DWORD *) &D2haveColdResBonus, (HMODULE) offset_D2Common, (LPCSTR) (version_D2Common == V113d ? 00000 : (version_D2Common == V113c ? 00000 : (version_D2Common == V112 ? 00000 : (version_D2Common == V111b ? 00000 : (version_D2Common == V111 ? 00000 : (version_D2Common == V110 ? 10541 : (version_D2Common == V109d ? 10541 : 10541))))))));
        if (version_D2Common > V113d) { D2haveLightResBonus = (TD2haveLightResBonus) (offset_D2Common + (version_D2Common == V114d ? 0x00000 : (version_D2Common == V113d ? 0x00000 : (version_D2Common == V113c ? 0x00000 : (version_D2Common == V112 ? 0x00000 : (version_D2Common == V111b ? 0x00000 : (version_D2Common == V111 ? 0x00000 : (version_D2Common == V110 ? 0x10542 : (version_D2Common == V109d ? 0x10542 : 0x10542))))))))); } else setFctAddr((DWORD *) &D2haveLightResBonus, (HMODULE) offset_D2Common, (LPCSTR) (version_D2Common == V113d ? 00000 : (version_D2Common == V113c ? 00000 : (version_D2Common == V112 ? 00000 : (version_D2Common == V111b ? 00000 : (version_D2Common == V111 ? 00000 : (version_D2Common == V110 ? 10542 : (version_D2Common == V109d ? 10542 : 10542))))))));
        if (version_D2Common > V113d) { D2havePoisonResBonus = (TD2havePoisonResBonus) (offset_D2Common + (version_D2Common == V114d ? 0x00000 : (version_D2Common == V113d ? 0x00000 : (version_D2Common == V113c ? 0x00000 : (version_D2Common == V112 ? 0x00000 : (version_D2Common == V111b ? 0x00000 : (version_D2Common == V111 ? 0x00000 : (version_D2Common == V110 ? 0x10543 : (version_D2Common == V109d ? 0x10543 : 0x10543))))))))); } else setFctAddr((DWORD *) &D2havePoisonResBonus, (HMODULE) offset_D2Common, (LPCSTR) (version_D2Common == V113d ? 00000 : (version_D2Common == V113c ? 00000 : (version_D2Common == V112 ? 00000 : (version_D2Common == V111b ? 00000 : (version_D2Common == V111 ? 00000 : (version_D2Common == V110 ? 10543 : (version_D2Common == V109d ? 10543 : 10543))))))));
        if (version_D2Common > V113d) { D2haveDefenceMalus = (TD2haveDefenceMalus) (offset_D2Common + (version_D2Common == V114d ? 0x00000 : (version_D2Common == V113d ? 0x00000 : (version_D2Common == V113c ? 0x00000 : (version_D2Common == V112 ? 0x00000 : (version_D2Common == V111b ? 0x00000 : (version_D2Common == V111 ? 0x00000 : (version_D2Common == V110 ? 0x10546 : (version_D2Common == V109d ? 0x10546 : 0x10546))))))))); } else setFctAddr((DWORD *) &D2haveDefenceMalus, (HMODULE) offset_D2Common, (LPCSTR) (version_D2Common == V113d ? 00000 : (version_D2Common == V113c ? 00000 : (version_D2Common == V112 ? 00000 : (version_D2Common == V111b ? 00000 : (version_D2Common == V111 ? 00000 : (version_D2Common == V110 ? 10546 : (version_D2Common == V109d ? 10546 : 10546))))))));
        if (version_D2Common > V113d) { D2haveFireResMalus = (TD2haveFireResMalus) (offset_D2Common + (version_D2Common == V114d ? 0x00000 : (version_D2Common == V113d ? 0x00000 : (version_D2Common == V113c ? 0x00000 : (version_D2Common == V112 ? 0x00000 : (version_D2Common == V111b ? 0x00000 : (version_D2Common == V111 ? 0x00000 : (version_D2Common == V110 ? 0x10547 : (version_D2Common == V109d ? 0x10547 : 0x10547))))))))); } else setFctAddr((DWORD *) &D2haveFireResMalus, (HMODULE) offset_D2Common, (LPCSTR) (version_D2Common == V113d ? 00000 : (version_D2Common == V113c ? 00000 : (version_D2Common == V112 ? 00000 : (version_D2Common == V111b ? 00000 : (version_D2Common == V111 ? 00000 : (version_D2Common == V110 ? 10547 : (version_D2Common == V109d ? 10547 : 10547))))))));
        if (version_D2Common > V113d) { D2haveColdResMalus = (TD2haveColdResMalus) (offset_D2Common + (version_D2Common == V114d ? 0x00000 : (version_D2Common == V113d ? 0x00000 : (version_D2Common == V113c ? 0x00000 : (version_D2Common == V112 ? 0x00000 : (version_D2Common == V111b ? 0x00000 : (version_D2Common == V111 ? 0x00000 : (version_D2Common == V110 ? 0x10548 : (version_D2Common == V109d ? 0x10548 : 0x10548))))))))); } else setFctAddr((DWORD *) &D2haveColdResMalus, (HMODULE) offset_D2Common, (LPCSTR) (version_D2Common == V113d ? 00000 : (version_D2Common == V113c ? 00000 : (version_D2Common == V112 ? 00000 : (version_D2Common == V111b ? 00000 : (version_D2Common == V111 ? 00000 : (version_D2Common == V110 ? 10548 : (version_D2Common == V109d ? 10548 : 10548))))))));
        if (version_D2Common > V113d) { D2haveLightResMalus = (TD2haveLightResMalus) (offset_D2Common + (version_D2Common == V114d ? 0x00000 : (version_D2Common == V113d ? 0x00000 : (version_D2Common == V113c ? 0x00000 : (version_D2Common == V112 ? 0x00000 : (version_D2Common == V111b ? 0x00000 : (version_D2Common == V111 ? 0x00000 : (version_D2Common == V110 ? 0x10549 : (version_D2Common == V109d ? 0x10549 : 0x10549))))))))); } else setFctAddr((DWORD *) &D2haveLightResMalus, (HMODULE) offset_D2Common, (LPCSTR) (version_D2Common == V113d ? 00000 : (version_D2Common == V113c ? 00000 : (version_D2Common == V112 ? 00000 : (version_D2Common == V111b ? 00000 : (version_D2Common == V111 ? 00000 : (version_D2Common == V110 ? 10549 : (version_D2Common == V109d ? 10549 : 10549))))))));
        if (version_D2Common > V113d) { D2havePoisonResMalus = (TD2havePoisonResMalus) (offset_D2Common + (version_D2Common == V114d ? 0x00000 : (version_D2Common == V113d ? 0x00000 : (version_D2Common == V113c ? 0x00000 : (version_D2Common == V112 ? 0x00000 : (version_D2Common == V111b ? 0x00000 : (version_D2Common == V111 ? 0x00000 : (version_D2Common == V110 ? 0x10550 : (version_D2Common == V109d ? 0x10550 : 0x10550))))))))); } else setFctAddr((DWORD *) &D2havePoisonResMalus, (HMODULE) offset_D2Common, (LPCSTR) (version_D2Common == V113d ? 00000 : (version_D2Common == V113c ? 00000 : (version_D2Common == V112 ? 00000 : (version_D2Common == V111b ? 00000 : (version_D2Common == V111 ? 00000 : (version_D2Common == V110 ? 10550 : (version_D2Common == V109d ? 10550 : 10550))))))));
        if (version_D2Common > V113d) { D2CompileTxtFile = (TD2CompileTxtFile) (offset_D2Common + (version_D2Common == V114d ? 0x2122F0 : (version_D2Common == V113d ? 0x10037 : (version_D2Common == V113c ? 0x10849 : (version_D2Common == V112 ? 0x10244 : (version_D2Common == V111b ? 0x10496 : (version_D2Common == V111 ? 0x10653 : (version_D2Common == V110 ? 0x10578 : (version_D2Common == V109d ? 0x10578 : 0x10578))))))))); } else setFctAddr((DWORD *) &D2CompileTxtFile, (HMODULE) offset_D2Common, (LPCSTR) (version_D2Common == V113d ? 10037 : (version_D2Common == V113c ? 10849 : (version_D2Common == V112 ? 10244 : (version_D2Common == V111b ? 10496 : (version_D2Common == V111 ? 10653 : (version_D2Common == V110 ? 10578 : (version_D2Common == V109d ? 10578 : 10578))))))));
        if (version_D2Common > V113d) { D2GetItemsBIN = (TD2GetItemsBIN) (offset_D2Common + (version_D2Common == V114d ? 0x2335F0 : (version_D2Common == V113d ? 0x10994 : (version_D2Common == V113c ? 0x10695 : (version_D2Common == V112 ? 0x10887 : (version_D2Common == V111b ? 0x10262 : (version_D2Common == V111 ? 0x10573 : (version_D2Common == V110 ? 0x10600 : (version_D2Common == V109d ? 0x10600 : 0x10600))))))))); } else setFctAddr((DWORD *) &D2GetItemsBIN, (HMODULE) offset_D2Common, (LPCSTR) (version_D2Common == V113d ? 10994 : (version_D2Common == V113c ? 10695 : (version_D2Common == V112 ? 10887 : (version_D2Common == V111b ? 10262 : (version_D2Common == V111 ? 10573 : (version_D2Common == V110 ? 10600 : (version_D2Common == V109d ? 10600 : 10600))))))));
        if (version_D2Common > V113d) { D2GetGemsBIN = (TD2GetGemsBIN) (offset_D2Common + (version_D2Common == V114d ? 0x2372C0 : (version_D2Common == V113d ? 0x10619 : (version_D2Common == V113c ? 0x10806 : (version_D2Common == V112 ? 0x10774 : (version_D2Common == V111b ? 0x10523 : (version_D2Common == V111 ? 0x10500 : (version_D2Common == V110 ? 0x10616 : (version_D2Common == V109d ? 0x10616 : 0x10616))))))))); } else setFctAddr((DWORD *) &D2GetGemsBIN, (HMODULE) offset_D2Common, (LPCSTR) (version_D2Common == V113d ? 10619 : (version_D2Common == V113c ? 10806 : (version_D2Common == V112 ? 10774 : (version_D2Common == V111b ? 10523 : (version_D2Common == V111 ? 10500 : (version_D2Common == V110 ? 10616 : (version_D2Common == V109d ? 10616 : 10616))))))));
        if (version_D2Common > V113d) { D2GetCubeMainBIN = (TD2GetCubeMainBIN) (offset_D2Common + (version_D2Common == V114d ? 0x26A1B0 : (version_D2Common == V113d ? 0x10393 : (version_D2Common == V113c ? 0x10783 : (version_D2Common == V112 ? 0x10913 : (version_D2Common == V111b ? 0x10258 : (version_D2Common == V111 ? 0x10746 : (version_D2Common == V110 ? 0x11232 : (version_D2Common == V109d ? 0x11232 : 0x11232))))))))); } else setFctAddr((DWORD *) &D2GetCubeMainBIN, (HMODULE) offset_D2Common, (LPCSTR) (version_D2Common == V113d ? 10393 : (version_D2Common == V113c ? 10783 : (version_D2Common == V112 ? 10913 : (version_D2Common == V111b ? 10258 : (version_D2Common == V111 ? 10746 : (version_D2Common == V110 ? 11232 : (version_D2Common == V109d ? 11232 : 11232))))))));
        if (version_D2Common > V113d) { D2GetNbCubeMainBIN = (TD2GetNbCubeMainBIN) (offset_D2Common + (version_D2Common == V114d ? 0x26A200 : (version_D2Common == V113d ? 0x10235 : (version_D2Common == V113c ? 0x10675 : (version_D2Common == V112 ? 0x10390 : (version_D2Common == V111b ? 0x11135 : (version_D2Common == V111 ? 0x10639 : (version_D2Common == V110 ? 0x11233 : (version_D2Common == V109d ? 0x11233 : 0x11233))))))))); } else setFctAddr((DWORD *) &D2GetNbCubeMainBIN, (HMODULE) offset_D2Common, (LPCSTR) (version_D2Common == V113d ? 10235 : (version_D2Common == V113c ? 10675 : (version_D2Common == V112 ? 10390 : (version_D2Common == V111b ? 11135 : (version_D2Common == V111 ? 10639 : (version_D2Common == V110 ? 11233 : (version_D2Common == V109d ? 11233 : 11233))))))));
        if (version_D2Common > V113d) { D2GetNextLevelXP = (TD2GetNextLevelXP) (offset_D2Common + (version_D2Common == V114d ? 0x00000 : (version_D2Common == V113d ? 0x00000 : (version_D2Common == V113c ? 0x00000 : (version_D2Common == V112 ? 0x00000 : (version_D2Common == V111b ? 0x00000 : (version_D2Common == V111 ? 0x00000 : (version_D2Common == V110 ? 0x10628 : (version_D2Common == V109d ? 0x10628 : 0x10628))))))))); } else setFctAddr((DWORD *) &D2GetNextLevelXP, (HMODULE) offset_D2Common, (LPCSTR) (version_D2Common == V113d ? 00000 : (version_D2Common == V113c ? 00000 : (version_D2Common == V112 ? 00000 : (version_D2Common == V111b ? 00000 : (version_D2Common == V111 ? 00000 : (version_D2Common == V110 ? 10628 : (version_D2Common == V109d ? 10628 : 10628))))))));
        if (version_D2Common > V113d) { D2GetMaxLevel = (TD2GetMaxLevel) (offset_D2Common + (version_D2Common == V114d ? 0x00000 : (version_D2Common == V113d ? 0x00000 : (version_D2Common == V113c ? 0x00000 : (version_D2Common == V112 ? 0x00000 : (version_D2Common == V111b ? 0x00000 : (version_D2Common == V111 ? 0x00000 : (version_D2Common == V110 ? 0x10629 : (version_D2Common == V109d ? 0x10629 : 0x10629))))))))); } else setFctAddr((DWORD *) &D2GetMaxLevel, (HMODULE) offset_D2Common, (LPCSTR) (version_D2Common == V113d ? 00000 : (version_D2Common == V113c ? 00000 : (version_D2Common == V112 ? 00000 : (version_D2Common == V111b ? 00000 : (version_D2Common == V111 ? 00000 : (version_D2Common == V110 ? 10629 : (version_D2Common == V109d ? 10629 : 10629))))))));
        if (version_D2Common > V113d) { D2GetDifficultyLevelsBIN = (TD2GetDifficultyLevelsBIN) (offset_D2Common + (version_D2Common == V114d ? 0x111D30 : (version_D2Common == V113d ? 0x10694 : (version_D2Common == V113c ? 0x10218 : (version_D2Common == V112 ? 0x10297 : (version_D2Common == V111b ? 0x10309 : (version_D2Common == V111 ? 0x10655 : (version_D2Common == V110 ? 0x10655 : (version_D2Common == V109d ? 0x10655 : 0x10655))))))))); } else setFctAddr((DWORD *) &D2GetDifficultyLevelsBIN, (HMODULE) offset_D2Common, (LPCSTR) (version_D2Common == V113d ? 10694 : (version_D2Common == V113c ? 10218 : (version_D2Common == V112 ? 10297 : (version_D2Common == V111b ? 10309 : (version_D2Common == V111 ? 10655 : (version_D2Common == V110 ? 10655 : (version_D2Common == V109d ? 10655 : 10655))))))));
        if (version_D2Common > V113d) { D2GetItemQuality = (TD2GetItemQuality) (offset_D2Common + (version_D2Common == V114d ? 0x227E70 : (version_D2Common == V113d ? 0x10911 : (version_D2Common == V113c ? 0x10106 : (version_D2Common == V112 ? 0x10276 : (version_D2Common == V111b ? 0x10899 : (version_D2Common == V111 ? 0x10927 : (version_D2Common == V110 ? 0x10695 : (version_D2Common == V109d ? 0x10695 : 0x10695))))))))); } else setFctAddr((DWORD *) &D2GetItemQuality, (HMODULE) offset_D2Common, (LPCSTR) (version_D2Common == V113d ? 10911 : (version_D2Common == V113c ? 10106 : (version_D2Common == V112 ? 10276 : (version_D2Common == V111b ? 10899 : (version_D2Common == V111 ? 10927 : (version_D2Common == V110 ? 10695 : (version_D2Common == V109d ? 10695 : 10695))))))));
        if (version_D2Common > V113d) { D2TestFlags = (TD2TestFlags) (offset_D2Common + (version_D2Common == V114d ? 0x2280A0 : (version_D2Common == V113d ? 0x10458 : (version_D2Common == V113c ? 0x10202 : (version_D2Common == V112 ? 0x10989 : (version_D2Common == V111b ? 0x10303 : (version_D2Common == V111 ? 0x10911 : (version_D2Common == V110 ? 0x10707 : (version_D2Common == V109d ? 0x10707 : 0x10707))))))))); } else setFctAddr((DWORD *) &D2TestFlags, (HMODULE) offset_D2Common, (LPCSTR) (version_D2Common == V113d ? 10458 : (version_D2Common == V113c ? 10202 : (version_D2Common == V112 ? 10989 : (version_D2Common == V111b ? 10303 : (version_D2Common == V111 ? 10911 : (version_D2Common == V110 ? 10707 : (version_D2Common == V109d ? 10707 : 10707))))))));
        if (version_D2Common > V113d) { D2GetItemLevel = (TD2GetItemLevel) (offset_D2Common + (version_D2Common == V114d ? 0x2281E0 : (version_D2Common == V113d ? 0x10008 : (version_D2Common == V113c ? 0x10086 : (version_D2Common == V112 ? 0x10410 : (version_D2Common == V111b ? 0x10100 : (version_D2Common == V111 ? 0x10898 : (version_D2Common == V110 ? 0x10717 : (version_D2Common == V109d ? 0x10717 : 0x10717))))))))); } else setFctAddr((DWORD *) &D2GetItemLevel, (HMODULE) offset_D2Common, (LPCSTR) (version_D2Common == V113d ? 10008 : (version_D2Common == V113c ? 10086 : (version_D2Common == V112 ? 10410 : (version_D2Common == V111b ? 10100 : (version_D2Common == V111 ? 10898 : (version_D2Common == V110 ? 10717 : (version_D2Common == V109d ? 10717 : 10717))))))));
        if (version_D2Common > V113d) { D2ItemGetPage = (TD2ItemGetPage) (offset_D2Common + (version_D2Common == V114d ? 0x228250 : (version_D2Common == V113d ? 0x10810 : (version_D2Common == V113c ? 0x10020 : (version_D2Common == V112 ? 0x10370 : (version_D2Common == V111b ? 0x10505 : (version_D2Common == V111 ? 0x10820 : (version_D2Common == V110 ? 0x10719 : (version_D2Common == V109d ? 0x10719 : 0x10719))))))))); } else setFctAddr((DWORD *) &D2ItemGetPage, (HMODULE) offset_D2Common, (LPCSTR) (version_D2Common == V113d ? 10810 : (version_D2Common == V113c ? 10020 : (version_D2Common == V112 ? 10370 : (version_D2Common == V111b ? 10505 : (version_D2Common == V111 ? 10820 : (version_D2Common == V110 ? 10719 : (version_D2Common == V109d ? 10719 : 10719))))))));
        if (version_D2Common > V113d) { D2ItemSetPage = (TD2ItemSetPage) (offset_D2Common + (version_D2Common == V114d ? 0x228280 : (version_D2Common == V113d ? 0x11026 : (version_D2Common == V113c ? 0x10012 : (version_D2Common == V112 ? 0x10223 : (version_D2Common == V111b ? 0x10608 : (version_D2Common == V111 ? 0x10485 : (version_D2Common == V110 ? 0x10720 : (version_D2Common == V109d ? 0x10720 : 0x10720))))))))); } else setFctAddr((DWORD *) &D2ItemSetPage, (HMODULE) offset_D2Common, (LPCSTR) (version_D2Common == V113d ? 11026 : (version_D2Common == V113c ? 10012 : (version_D2Common == V112 ? 10223 : (version_D2Common == V111b ? 10608 : (version_D2Common == V111 ? 10485 : (version_D2Common == V110 ? 10720 : (version_D2Common == V109d ? 10720 : 10720))))))));
        if (version_D2Common > V113d) { D2CheckItemType = (TD2CheckItemType) (offset_D2Common + (version_D2Common == V114d ? 0x229BB0 : (version_D2Common == V113d ? 0x10601 : (version_D2Common == V113c ? 0x10744 : (version_D2Common == V112 ? 0x10231 : (version_D2Common == V111b ? 0x10890 : (version_D2Common == V111 ? 0x11017 : (version_D2Common == V110 ? 0x10731 : (version_D2Common == V109d ? 0x10731 : 0x10731))))))))); } else setFctAddr((DWORD *) &D2CheckItemType, (HMODULE) offset_D2Common, (LPCSTR) (version_D2Common == V113d ? 10601 : (version_D2Common == V113c ? 10744 : (version_D2Common == V112 ? 10231 : (version_D2Common == V111b ? 10890 : (version_D2Common == V111 ? 11017 : (version_D2Common == V110 ? 10731 : (version_D2Common == V109d ? 10731 : 10731))))))));
        if (version_D2Common > V113d) { D2GetUniqueID = (TD2GetUniqueID) (offset_D2Common + (version_D2Common == V114d ? 0x229DA0 : (version_D2Common == V113d ? 0x10075 : (version_D2Common == V113c ? 0x10620 : (version_D2Common == V112 ? 0x10280 : (version_D2Common == V111b ? 0x10685 : (version_D2Common == V111 ? 0x10692 : (version_D2Common == V110 ? 0x10732 : (version_D2Common == V109d ? 0x10732 : 0x10732))))))))); } else setFctAddr((DWORD *) &D2GetUniqueID, (HMODULE) offset_D2Common, (LPCSTR) (version_D2Common == V113d ? 10075 : (version_D2Common == V113c ? 10620 : (version_D2Common == V112 ? 10280 : (version_D2Common == V111b ? 10685 : (version_D2Common == V111 ? 10692 : (version_D2Common == V110 ? 10732 : (version_D2Common == V109d ? 10732 : 10732))))))));
        if (version_D2Common > V113d) { D2SetAnim = (TD2SetAnim) (offset_D2Common + (version_D2Common == V114d ? 0x00000 : (version_D2Common == V113d ? 0x00000 : (version_D2Common == V113c ? 0x00000 : (version_D2Common == V112 ? 0x00000 : (version_D2Common == V111b ? 0x00000 : (version_D2Common == V111 ? 0x00000 : (version_D2Common == V110 ? 0x10734 : (version_D2Common == V109d ? 0x10734 : 0x10734))))))))); } else setFctAddr((DWORD *) &D2SetAnim, (HMODULE) offset_D2Common, (LPCSTR) (version_D2Common == V113d ? 00000 : (version_D2Common == V113c ? 00000 : (version_D2Common == V112 ? 00000 : (version_D2Common == V111b ? 00000 : (version_D2Common == V111 ? 00000 : (version_D2Common == V110 ? 10734 : (version_D2Common == V109d ? 10734 : 10734))))))));
        if (version_D2Common > V113d) { D2GetNbRunesBIN = (TD2GetNbRunesBIN) (offset_D2Common + (version_D2Common == V114d ? 0x239CB0 : (version_D2Common == V113d ? 0x10981 : (version_D2Common == V113c ? 0x11032 : (version_D2Common == V112 ? 0x10321 : (version_D2Common == V111b ? 0x10877 : (version_D2Common == V111 ? 0x10687 : (version_D2Common == V110 ? 0x10619 : (version_D2Common == V109d ? 0x10619 : 0x10619))))))))); } else setFctAddr((DWORD *) &D2GetNbRunesBIN, (HMODULE) offset_D2Common, (LPCSTR) (version_D2Common == V113d ? 10981 : (version_D2Common == V113c ? 11032 : (version_D2Common == V112 ? 10321 : (version_D2Common == V111b ? 10877 : (version_D2Common == V111 ? 10687 : (version_D2Common == V110 ? 10619 : (version_D2Common == V109d ? 10619 : 10619))))))));
        if (version_D2Common > V113d) { D2GetRunesBIN = (TD2GetRunesBIN) (offset_D2Common + (version_D2Common == V114d ? 0x239D60 : (version_D2Common == V113d ? 0x10405 : (version_D2Common == V113c ? 0x10006 : (version_D2Common == V112 ? 0x10622 : (version_D2Common == V111b ? 0x10296 : (version_D2Common == V111 ? 0x10775 : (version_D2Common == V110 ? 0x10620 : (version_D2Common == V109d ? 0x10620 : 0x10620))))))))); } else setFctAddr((DWORD *) &D2GetRunesBIN, (HMODULE) offset_D2Common, (LPCSTR) (version_D2Common == V113d ? 10405 : (version_D2Common == V113c ? 10006 : (version_D2Common == V112 ? 10622 : (version_D2Common == V111b ? 10296 : (version_D2Common == V111 ? 10775 : (version_D2Common == V110 ? 10620 : (version_D2Common == V109d ? 10620 : 10620))))))));
        if (version_D2Common > V113d) { D2SaveItem = (TD2SaveItem) (offset_D2Common + (version_D2Common == V114d ? 0x2313E0 : (version_D2Common == V113d ? 0x10665 : (version_D2Common == V113c ? 0x10987 : (version_D2Common == V112 ? 0x10218 : (version_D2Common == V111b ? 0x11156 : (version_D2Common == V111 ? 0x10956 : (version_D2Common == V110 ? 0x10881 : (version_D2Common == V109d ? 0x10881 : 0x10881))))))))); } else setFctAddr((DWORD *) &D2SaveItem, (HMODULE) offset_D2Common, (LPCSTR) (version_D2Common == V113d ? 10665 : (version_D2Common == V113c ? 10987 : (version_D2Common == V112 ? 10218 : (version_D2Common == V111b ? 11156 : (version_D2Common == V111 ? 10956 : (version_D2Common == V110 ? 10881 : (version_D2Common == V109d ? 10881 : 10881))))))));
        if (version_D2Common > V113d) { D2SetSkillBaseLevel = (TD2SetSkillBaseLevel) (offset_D2Common + (version_D2Common == V114d ? 0x247280 : (version_D2Common == V113d ? 0x10335 : (version_D2Common == V113c ? 0x10302 : (version_D2Common == V112 ? 0x10210 : (version_D2Common == V111b ? 0x10255 : (version_D2Common == V111 ? 0x10099 : (version_D2Common == V110 ? 0x10953 : (version_D2Common == V109d ? 0x10953 : 0x10953))))))))); } else setFctAddr((DWORD *) &D2SetSkillBaseLevel, (HMODULE) offset_D2Common, (LPCSTR) (version_D2Common == V113d ? 10335 : (version_D2Common == V113c ? 10302 : (version_D2Common == V112 ? 10210 : (version_D2Common == V111b ? 10255 : (version_D2Common == V111 ? 10099 : (version_D2Common == V110 ? 10953 : (version_D2Common == V109d ? 10953 : 10953))))))));
        if (version_D2Common > V113d) { D2GetSkillLevel = (TD2GetSkillLevel) (offset_D2Common + (version_D2Common == V114d ? 0x2442A0 : (version_D2Common == V113d ? 0x10007 : (version_D2Common == V113c ? 0x10306 : (version_D2Common == V112 ? 0x10904 : (version_D2Common == V111b ? 0x10109 : (version_D2Common == V111 ? 0x10700 : (version_D2Common == V110 ? 0x10968 : (version_D2Common == V109d ? 0x10968 : 0x10968))))))))); } else setFctAddr((DWORD *) &D2GetSkillLevel, (HMODULE) offset_D2Common, (LPCSTR) (version_D2Common == V113d ? 10007 : (version_D2Common == V113c ? 10306 : (version_D2Common == V112 ? 10904 : (version_D2Common == V111b ? 10109 : (version_D2Common == V111 ? 10700 : (version_D2Common == V110 ? 10968 : (version_D2Common == V109d ? 10968 : 10968))))))));
        if (version_D2Common > V113d) { D2GetSkillCost = (TD2GetSkillCost) (offset_D2Common + (version_D2Common == V114d ? 0x246CA0 : (version_D2Common == V113d ? 0x11081 : (version_D2Common == V113c ? 0x10435 : (version_D2Common == V112 ? 0x10111 : (version_D2Common == V111b ? 0x10074 : (version_D2Common == V111 ? 0x10254 : (version_D2Common == V110 ? 0x11276 : (version_D2Common == V109d ? 0x11276 : 0x11276))))))))); } else setFctAddr((DWORD *) &D2GetSkillCost, (HMODULE) offset_D2Common, (LPCSTR) (version_D2Common == V113d ? 11081 : (version_D2Common == V113c ? 10435 : (version_D2Common == V112 ? 10111 : (version_D2Common == V111b ? 10074 : (version_D2Common == V111 ? 10254 : (version_D2Common == V110 ? 11276 : (version_D2Common == V109d ? 11276 : 11276))))))));
        if (version_D2Game > V113d) { D2SetNbPlayers = (TD2SetNbPlayers) (offset_D2Game + (version_D2Game == V114d ? 0x135780 : (version_D2Game == V113d ? 0x10002 : (version_D2Game == V113c ? 0x10049 : (version_D2Game == V112 ? 0x10037 : (version_D2Game == V111b ? 0x10007 : (version_D2Game == V111 ? 0x10039 : (version_D2Game == V110 ? 0x10059 : (version_D2Game == V109d ? 0x10059 : 0x10059))))))))); } else setFctAddr((DWORD *) &D2SetNbPlayers, (HMODULE) offset_D2Game, (LPCSTR) (version_D2Game == V113d ? 10002 : (version_D2Game == V113c ? 10049 : (version_D2Game == V112 ? 10037 : (version_D2Game == V111b ? 10007 : (version_D2Game == V111 ? 10039 : (version_D2Game == V110 ? 10059 : (version_D2Game == V109d ? 10059 : 10059))))))));
        if (version_D2Net > V113d) { D2SendToServer = (TD2SendToServer) (offset_D2Net + (version_D2Net == V114d ? 0x12AE50 : (version_D2Net == V113d ? 0x10015 : (version_D2Net == V113c ? 0x10024 : (version_D2Net == V112 ? 0x10036 : (version_D2Net == V111b ? 0x10020 : (version_D2Net == V111 ? 0x10035 : (version_D2Net == V110 ? 0x10005 : (version_D2Net == V109d ? 0x10005 : 0x10005))))))))); } else setFctAddr((DWORD *) &D2SendToServer, (HMODULE) offset_D2Net, (LPCSTR) (version_D2Net == V113d ? 10015 : (version_D2Net == V113c ? 10024 : (version_D2Net == V112 ? 10036 : (version_D2Net == V111b ? 10020 : (version_D2Net == V111 ? 10035 : (version_D2Net == V110 ? 10005 : (version_D2Net == V109d ? 10005 : 10005))))))));
        if (version_D2Net > V113d) { D2SendToClient = (TD2SendToClient) (offset_D2Net + (version_D2Net == V114d ? 0x12B330 : (version_D2Net == V113d ? 0x10012 : (version_D2Net == V113c ? 0x10002 : (version_D2Net == V112 ? 0x10015 : (version_D2Net == V111b ? 0x10018 : (version_D2Net == V111 ? 0x10018 : (version_D2Net == V110 ? 0x10006 : (version_D2Net == V109d ? 0x10006 : 0x10006))))))))); } else setFctAddr((DWORD *) &D2SendToClient, (HMODULE) offset_D2Net, (LPCSTR) (version_D2Net == V113d ? 10012 : (version_D2Net == V113c ? 10002 : (version_D2Net == V112 ? 10015 : (version_D2Net == V111b ? 10018 : (version_D2Net == V111 ? 10018 : (version_D2Net == V110 ? 10006 : (version_D2Net == V109d ? 10006 : 10006))))))));
        if (version_Fog > V113d) { D2FogAssertOld = (TD2FogAssertOld) (offset_Fog + (version_Fog == V114d ? 0x00000 : (version_Fog == V113d ? 0x00000 : (version_Fog == V113c ? 0x00000 : (version_Fog == V112 ? 0x00000 : (version_Fog == V111b ? 0x00000 : (version_Fog == V111 ? 0x00000 : (version_Fog == V110 ? 0x10023 : (version_Fog == V109d ? 0x10023 : 0x10023))))))))); } else setFctAddr((DWORD *) &D2FogAssertOld, (HMODULE) offset_Fog, (LPCSTR) (version_Fog == V113d ? 00000 : (version_Fog == V113c ? 00000 : (version_Fog == V112 ? 00000 : (version_Fog == V111b ? 00000 : (version_Fog == V111 ? 00000 : (version_Fog == V110 ? 10023 : (version_Fog == V109d ? 10023 : 10023))))))));
        if (version_Fog > V113d) { D2FogAssert = (TD2FogAssert) (offset_Fog + (version_Fog == V114d ? 0x8A60 : (version_Fog == V113d ? 0x10024 : (version_Fog == V113c ? 0x10024 : (version_Fog == V112 ? 0x10024 : (version_Fog == V111b ? 0x10024 : (version_Fog == V111 ? 0x10024 : (version_Fog == V110 ? 0x00000 : (version_Fog == V109d ? 0x00000 : 0x00000))))))))); } else setFctAddr((DWORD *) &D2FogAssert, (HMODULE) offset_Fog, (LPCSTR) (version_Fog == V113d ? 10024 : (version_Fog == V113c ? 10024 : (version_Fog == V112 ? 10024 : (version_Fog == V111b ? 10024 : (version_Fog == V111 ? 10024 : (version_Fog == V110 ? 00000 : (version_Fog == V109d ? 00000 : 00000))))))));
        if (version_Fog > V113d) { D2FogMemAlloc = (TD2FogMemAlloc) (offset_Fog + (version_Fog == V114d ? 0xB380 : (version_Fog == V113d ? 0x10042 : (version_Fog == V113c ? 0x10042 : (version_Fog == V112 ? 0x10042 : (version_Fog == V111b ? 0x10042 : (version_Fog == V111 ? 0x10042 : (version_Fog == V110 ? 0x10042 : (version_Fog == V109d ? 0x10042 : 0x10042))))))))); } else setFctAddr((DWORD *) &D2FogMemAlloc, (HMODULE) offset_Fog, (LPCSTR) (version_Fog == V113d ? 10042 : (version_Fog == V113c ? 10042 : (version_Fog == V112 ? 10042 : (version_Fog == V111b ? 10042 : (version_Fog == V111 ? 10042 : (version_Fog == V110 ? 10042 : (version_Fog == V109d ? 10042 : 10042))))))));
        if (version_Fog > V113d) { D2FogMemDeAlloc = (TD2FogMemDeAlloc) (offset_Fog + (version_Fog == V114d ? 0xB3C0 : (version_Fog == V113d ? 0x10043 : (version_Fog == V113c ? 0x10043 : (version_Fog == V112 ? 0x10043 : (version_Fog == V111b ? 0x10043 : (version_Fog == V111 ? 0x10043 : (version_Fog == V110 ? 0x10043 : (version_Fog == V109d ? 0x10043 : 0x10043))))))))); } else setFctAddr((DWORD *) &D2FogMemDeAlloc, (HMODULE) offset_Fog, (LPCSTR) (version_Fog == V113d ? 10043 : (version_Fog == V113c ? 10043 : (version_Fog == V112 ? 10043 : (version_Fog == V111b ? 10043 : (version_Fog == V111 ? 10043 : (version_Fog == V110 ? 10043 : (version_Fog == V109d ? 10043 : 10043))))))));
        if (version_Fog > V113d) { D2AllocMem = (TD2AllocMem) (offset_Fog + (version_Fog == V114d ? 0xB430 : (version_Fog == V113d ? 0x10045 : (version_Fog == V113c ? 0x10045 : (version_Fog == V112 ? 0x10045 : (version_Fog == V111b ? 0x10045 : (version_Fog == V111 ? 0x10045 : (version_Fog == V110 ? 0x10045 : (version_Fog == V109d ? 0x10045 : 0x10045))))))))); } else setFctAddr((DWORD *) &D2AllocMem, (HMODULE) offset_Fog, (LPCSTR) (version_Fog == V113d ? 10045 : (version_Fog == V113c ? 10045 : (version_Fog == V112 ? 10045 : (version_Fog == V111b ? 10045 : (version_Fog == V111 ? 10045 : (version_Fog == V110 ? 10045 : (version_Fog == V109d ? 10045 : 10045))))))));
        if (version_Fog > V113d) { D2FreeMem = (TD2FreeMem) (offset_Fog + (version_Fog == V114d ? 0xB480 : (version_Fog == V113d ? 0x10046 : (version_Fog == V113c ? 0x10046 : (version_Fog == V112 ? 0x10046 : (version_Fog == V111b ? 0x10046 : (version_Fog == V111 ? 0x10046 : (version_Fog == V110 ? 0x10046 : (version_Fog == V109d ? 0x10046 : 0x10046))))))))); } else setFctAddr((DWORD *) &D2FreeMem, (HMODULE) offset_Fog, (LPCSTR) (version_Fog == V113d ? 10046 : (version_Fog == V113c ? 10046 : (version_Fog == V112 ? 10046 : (version_Fog == V111b ? 10046 : (version_Fog == V111 ? 10046 : (version_Fog == V110 ? 10046 : (version_Fog == V109d ? 10046 : 10046))))))));
        if (version_Fog > V113d) { D2MPQOpenFile = (TD2MPQOpenFile) (offset_Fog + (version_Fog == V114d ? 0x68E0 : (version_Fog == V113d ? 0x10102 : (version_Fog == V113c ? 0x10102 : (version_Fog == V112 ? 0x10102 : (version_Fog == V111b ? 0x10102 : (version_Fog == V111 ? 0x10102 : (version_Fog == V110 ? 0x10102 : (version_Fog == V109d ? 0x10102 : 0x10102))))))))); } else setFctAddr((DWORD *) &D2MPQOpenFile, (HMODULE) offset_Fog, (LPCSTR) (version_Fog == V113d ? 10102 : (version_Fog == V113c ? 10102 : (version_Fog == V112 ? 10102 : (version_Fog == V111b ? 10102 : (version_Fog == V111 ? 10102 : (version_Fog == V110 ? 10102 : (version_Fog == V109d ? 10102 : 10102))))))));
        if (version_Fog > V113d) { D2MPQCloseFile = (TD2MPQCloseFile) (offset_Fog + (version_Fog == V114d ? 0x68F0 : (version_Fog == V113d ? 0x10103 : (version_Fog == V113c ? 0x10103 : (version_Fog == V112 ? 0x10103 : (version_Fog == V111b ? 0x10103 : (version_Fog == V111 ? 0x10103 : (version_Fog == V110 ? 0x10103 : (version_Fog == V109d ? 0x10103 : 0x10103))))))))); } else setFctAddr((DWORD *) &D2MPQCloseFile, (HMODULE) offset_Fog, (LPCSTR) (version_Fog == V113d ? 10103 : (version_Fog == V113c ? 10103 : (version_Fog == V112 ? 10103 : (version_Fog == V111b ? 10103 : (version_Fog == V111 ? 10103 : (version_Fog == V110 ? 10103 : (version_Fog == V109d ? 10103 : 10103))))))));
        if (version_Fog > V113d) { D2MPQReadFile = (TD2MPQReadFile) (offset_Fog + (version_Fog == V114d ? 0x6900 : (version_Fog == V113d ? 0x10104 : (version_Fog == V113c ? 0x10104 : (version_Fog == V112 ? 0x10104 : (version_Fog == V111b ? 0x10104 : (version_Fog == V111 ? 0x10104 : (version_Fog == V110 ? 0x10104 : (version_Fog == V109d ? 0x10104 : 0x10104))))))))); } else setFctAddr((DWORD *) &D2MPQReadFile, (HMODULE) offset_Fog, (LPCSTR) (version_Fog == V113d ? 10104 : (version_Fog == V113c ? 10104 : (version_Fog == V112 ? 10104 : (version_Fog == V111b ? 10104 : (version_Fog == V111 ? 10104 : (version_Fog == V110 ? 10104 : (version_Fog == V109d ? 10104 : 10104))))))));
        if (version_Fog > V113d) { D2MPQGetSizeFile = (TD2MPQGetSizeFile) (offset_Fog + (version_Fog == V114d ? 0x6930 : (version_Fog == V113d ? 0x10105 : (version_Fog == V113c ? 0x10105 : (version_Fog == V112 ? 0x10105 : (version_Fog == V111b ? 0x10105 : (version_Fog == V111 ? 0x10105 : (version_Fog == V110 ? 0x10105 : (version_Fog == V109d ? 0x10105 : 0x10105))))))))); } else setFctAddr((DWORD *) &D2MPQGetSizeFile, (HMODULE) offset_Fog, (LPCSTR) (version_Fog == V113d ? 10105 : (version_Fog == V113c ? 10105 : (version_Fog == V112 ? 10105 : (version_Fog == V111b ? 10105 : (version_Fog == V111 ? 10105 : (version_Fog == V110 ? 10105 : (version_Fog == V109d ? 10105 : 10105))))))));
        if (version_Fog > V113d) { D2FogGetSavePath = (TD2FogGetSavePath) (offset_Fog + (version_Fog == V114d ? 0x7050 : (version_Fog == V113d ? 0x10115 : (version_Fog == V113c ? 0x10115 : (version_Fog == V112 ? 0x10115 : (version_Fog == V111b ? 0x10115 : (version_Fog == V111 ? 0x10115 : (version_Fog == V110 ? 0x10115 : (version_Fog == V109d ? 0x10115 : 0x10115))))))))); } else setFctAddr((DWORD *) &D2FogGetSavePath, (HMODULE) offset_Fog, (LPCSTR) (version_Fog == V113d ? 10115 : (version_Fog == V113c ? 10115 : (version_Fog == V112 ? 10115 : (version_Fog == V111b ? 10115 : (version_Fog == V111 ? 10115 : (version_Fog == V110 ? 10115 : (version_Fog == V109d ? 10115 : 10115))))))));
        if (version_Fog > V113d) { D2FogGetInstallPath = (TD2FogGetInstallPath) (offset_Fog + (version_Fog == V114d ? 0x6BA0 : (version_Fog == V113d ? 0x10116 : (version_Fog == V113c ? 0x10116 : (version_Fog == V112 ? 0x10116 : (version_Fog == V111b ? 0x10116 : (version_Fog == V111 ? 0x10116 : (version_Fog == V110 ? 0x10116 : (version_Fog == V109d ? 0x10116 : 0x10116))))))))); } else setFctAddr((DWORD *) &D2FogGetInstallPath, (HMODULE) offset_Fog, (LPCSTR) (version_Fog == V113d ? 10116 : (version_Fog == V113c ? 10116 : (version_Fog == V112 ? 10116 : (version_Fog == V111b ? 10116 : (version_Fog == V111 ? 10116 : (version_Fog == V110 ? 10116 : (version_Fog == V109d ? 10116 : 10116))))))));
        if (version_Fog > V113d) { D2Fog10212 = (TD2Fog10212) (offset_Fog + (version_Fog == V114d ? 0x2BD0B0 : (version_Fog == V113d ? 0x10212 : (version_Fog == V113c ? 0x10212 : (version_Fog == V112 ? 0x10212 : (version_Fog == V111b ? 0x10212 : (version_Fog == V111 ? 0x10212 : (version_Fog == V110 ? 0x10212 : (version_Fog == V109d ? 0x10212 : 0x10212))))))))); } else setFctAddr((DWORD *) &D2Fog10212, (HMODULE) offset_Fog, (LPCSTR) (version_Fog == V113d ? 10212 : (version_Fog == V113c ? 10212 : (version_Fog == V112 ? 10212 : (version_Fog == V111b ? 10212 : (version_Fog == V111 ? 10212 : (version_Fog == V110 ? 10212 : (version_Fog == V109d ? 10212 : 10212))))))));
        if (version_Fog > V113d) { D2GetInstructionPointer = (TD2GetInstructionPointer) (offset_Fog + (version_Fog == V114d ? 0x8090 : (version_Fog == V113d ? 0x10265 : (version_Fog == V113c ? 0x10265 : (version_Fog == V112 ? 0x10265 : (version_Fog == V111b ? 0x10265 : (version_Fog == V111 ? 0x10265 : (version_Fog == V110 ? 0x00000 : (version_Fog == V109d ? 0x00000 : 0x00000))))))))); } else setFctAddr((DWORD *) &D2GetInstructionPointer, (HMODULE) offset_Fog, (LPCSTR) (version_Fog == V113d ? 10265 : (version_Fog == V113c ? 10265 : (version_Fog == V112 ? 10265 : (version_Fog == V111b ? 10265 : (version_Fog == V111 ? 10265 : (version_Fog == V110 ? 00000 : (version_Fog == V109d ? 00000 : 00000))))))));
        if (version_D2Lang > V113d) { D2GetStringFromString = (TD2GetStringFromString) (offset_D2Lang + (version_D2Lang == V114d ? 0x124E20 : (version_D2Lang == V113d ? 0x10011 : (version_D2Lang == V113c ? 0x10011 : (version_D2Lang == V112 ? 0x10010 : (version_D2Lang == V111b ? 0x10004 : (version_D2Lang == V111 ? 0x10002 : (version_D2Lang == V110 ? 0x10003 : (version_D2Lang == V109d ? 0x10003 : 0x10003))))))))); } else setFctAddr((DWORD *) &D2GetStringFromString, (HMODULE) offset_D2Lang, (LPCSTR) (version_D2Lang == V113d ? 10011 : (version_D2Lang == V113c ? 10011 : (version_D2Lang == V112 ? 10010 : (version_D2Lang == V111b ? 10004 : (version_D2Lang == V111 ? 10002 : (version_D2Lang == V110 ? 10003 : (version_D2Lang == V109d ? 10003 : 10003))))))));
        if (version_D2Lang > V113d) { D2GetStringFromIndex = (TD2GetStringFromIndex) (offset_D2Lang + (version_D2Lang == V114d ? 0x124A30 : (version_D2Lang == V113d ? 0x10004 : (version_D2Lang == V113c ? 0x10003 : (version_D2Lang == V112 ? 0x10005 : (version_D2Lang == V111b ? 0x10000 : (version_D2Lang == V111 ? 0x10005 : (version_D2Lang == V110 ? 0x10004 : (version_D2Lang == V109d ? 0x10004 : 0x10004))))))))); } else setFctAddr((DWORD *) &D2GetStringFromIndex, (HMODULE) offset_D2Lang, (LPCSTR) (version_D2Lang == V113d ? 10004 : (version_D2Lang == V113c ? 10003 : (version_D2Lang == V112 ? 10005 : (version_D2Lang == V111b ? 10000 : (version_D2Lang == V111 ? 10005 : (version_D2Lang == V110 ? 10004 : (version_D2Lang == V109d ? 10004 : 10004))))))));
        if (version_D2Lang > V113d) { D2GetLang = (TD2GetLang) (offset_D2Lang + (version_D2Lang == V114d ? 0x125150 : (version_D2Lang == V113d ? 0x10001 : (version_D2Lang == V113c ? 0x10009 : (version_D2Lang == V112 ? 0x10002 : (version_D2Lang == V111b ? 0x10013 : (version_D2Lang == V111 ? 0x10009 : (version_D2Lang == V110 ? 0x10007 : (version_D2Lang == V109d ? 0x10007 : 0x10007))))))))); } else setFctAddr((DWORD *) &D2GetLang, (HMODULE) offset_D2Lang, (LPCSTR) (version_D2Lang == V113d ? 10001 : (version_D2Lang == V113c ? 10009 : (version_D2Lang == V112 ? 10002 : (version_D2Lang == V111b ? 10013 : (version_D2Lang == V111 ? 10009 : (version_D2Lang == V110 ? 10007 : (version_D2Lang == V109d ? 10007 : 10007))))))));
        if (version_D2Lang > V113d) { D2PrintBigNumber = (TD2PrintBigNumber) (offset_D2Lang + (version_D2Lang == V114d ? 0x00000 : (version_D2Lang == V113d ? 0x00000 : (version_D2Lang == V113c ? 0x00000 : (version_D2Lang == V112 ? 0x00000 : (version_D2Lang == V111b ? 0x00000 : (version_D2Lang == V111 ? 0x00000 : (version_D2Lang == V110 ? 0x10010 : (version_D2Lang == V109d ? 0x10010 : 0x10010))))))))); } else setFctAddr((DWORD *) &D2PrintBigNumber, (HMODULE) offset_D2Lang, (LPCSTR) (version_D2Lang == V113d ? 00000 : (version_D2Lang == V113c ? 00000 : (version_D2Lang == V112 ? 00000 : (version_D2Lang == V111b ? 00000 : (version_D2Lang == V111 ? 00000 : (version_D2Lang == V110 ? 10010 : (version_D2Lang == V109d ? 10010 : 10010))))))));
        if (version_Storm > V113d) { D2StormMPQOpenFile = (TD2StormMPQOpenFile) (offset_Storm + (version_Storm == V114d ? 0x192F0 : (version_Storm == V113d ? 0x268 : (version_Storm == V113c ? 0x268 : (version_Storm == V112 ? 0x268 : (version_Storm == V111b ? 0x268 : (version_Storm == V111 ? 0x268 : (version_Storm == V110 ? 0x268 : (version_Storm == V109d ? 0x268 : 0x268))))))))); } else setFctAddr((DWORD *) &D2StormMPQOpenFile, (HMODULE) offset_Storm, (LPCSTR) (version_Storm == V113d ? 268 : (version_Storm == V113c ? 268 : (version_Storm == V112 ? 268 : (version_Storm == V111b ? 268 : (version_Storm == V111 ? 268 : (version_Storm == V110 ? 268 : (version_Storm == V109d ? 268 : 268))))))));
        if (version_Storm > V113d) { D2Storm503 = (TD2Storm503) (offset_Storm + (version_Storm == V114d ? 0x13750 : (version_Storm == V113d ? 0x503 : (version_Storm == V113c ? 0x503 : (version_Storm == V112 ? 0x503 : (version_Storm == V111b ? 0x503 : (version_Storm == V111 ? 0x503 : (version_Storm == V110 ? 0x503 : (version_Storm == V109d ? 0x503 : 0x503))))))))); } else setFctAddr((DWORD *) &D2Storm503, (HMODULE) offset_Storm, (LPCSTR) (version_Storm == V113d ? 503 : (version_Storm == V113c ? 503 : (version_Storm == V112 ? 503 : (version_Storm == V111b ? 503 : (version_Storm == V111 ? 503 : (version_Storm == V110 ? 503 : (version_Storm == V109d ? 503 : 503))))))));
        if (version_Storm > V113d) { D2FreeWinMessage = (TD2FreeWinMessage) (offset_Storm + (version_Storm == V114d ? 0x20290 : (version_Storm == V113d ? 0x511 : (version_Storm == V113c ? 0x511 : (version_Storm == V112 ? 0x511 : (version_Storm == V111b ? 0x511 : (version_Storm == V111 ? 0x511 : (version_Storm == V110 ? 0x511 : (version_Storm == V109d ? 0x511 : 0x511))))))))); } else setFctAddr((DWORD *) &D2FreeWinMessage, (HMODULE) offset_Storm, (LPCSTR) (version_Storm == V113d ? 511 : (version_Storm == V113c ? 511 : (version_Storm == V112 ? 511 : (version_Storm == V111b ? 511 : (version_Storm == V111 ? 511 : (version_Storm == V110 ? 511 : (version_Storm == V109d ? 511 : 511))))))));
        if (version_D2gfx > V113d) { D2GetResolution = (TD2GetResolution) (offset_D2gfx + (version_D2gfx == V114d ? 0xF5160 : (version_D2gfx == V113d ? 0x10012 : (version_D2gfx == V113c ? 0x10031 : (version_D2gfx == V112 ? 0x10043 : (version_D2gfx == V111b ? 0x10063 : (version_D2gfx == V111 ? 0x10000 : (version_D2gfx == V110 ? 0x10005 : (version_D2gfx == V109d ? 0x10005 : 0x10005))))))))); } else setFctAddr((DWORD *) &D2GetResolution, (HMODULE) offset_D2gfx, (LPCSTR) (version_D2gfx == V113d ? 10012 : (version_D2gfx == V113c ? 10031 : (version_D2gfx == V112 ? 10043 : (version_D2gfx == V111b ? 10063 : (version_D2gfx == V111 ? 10000 : (version_D2gfx == V110 ? 10005 : (version_D2gfx == V109d ? 10005 : 10005))))))));
        if (version_D2gfx > V113d) { D2FillArea = (TD2FillArea) (offset_D2gfx + (version_D2gfx == V114d ? 0xF6300 : (version_D2gfx == V113d ? 0x10028 : (version_D2gfx == V113c ? 0x10014 : (version_D2gfx == V112 ? 0x10062 : (version_D2gfx == V111b ? 0x10000 : (version_D2gfx == V111 ? 0x10028 : (version_D2gfx == V110 ? 0x10055 : (version_D2gfx == V109d ? 0x10055 : 0x10055))))))))); } else setFctAddr((DWORD *) &D2FillArea, (HMODULE) offset_D2gfx, (LPCSTR) (version_D2gfx == V113d ? 10028 : (version_D2gfx == V113c ? 10014 : (version_D2gfx == V112 ? 10062 : (version_D2gfx == V111b ? 10000 : (version_D2gfx == V111 ? 10028 : (version_D2gfx == V110 ? 10055 : (version_D2gfx == V109d ? 10055 : 10055))))))));
        if (version_D2gfx > V113d) { D2PrintImage = (TD2PrintImage) (offset_D2gfx + (version_D2gfx == V114d ? 0xF6480 : (version_D2gfx == V113d ? 0x10042 : (version_D2gfx == V113c ? 0x10041 : (version_D2gfx == V112 ? 0x10024 : (version_D2gfx == V111b ? 0x10044 : (version_D2gfx == V111 ? 0x10047 : (version_D2gfx == V110 ? 0x10072 : (version_D2gfx == V109d ? 0x10072 : 0x10072))))))))); } else setFctAddr((DWORD *) &D2PrintImage, (HMODULE) offset_D2gfx, (LPCSTR) (version_D2gfx == V113d ? 10042 : (version_D2gfx == V113c ? 10041 : (version_D2gfx == V112 ? 10024 : (version_D2gfx == V111b ? 10044 : (version_D2gfx == V111 ? 10047 : (version_D2gfx == V110 ? 10072 : (version_D2gfx == V109d ? 10072 : 10072))))))));
        if (version_D2Win > V113d) { D2PrintLineOnTextBox = (TD2PrintLineOnTextBox) (offset_D2Win + (version_D2Win == V114d ? 0xFCFF0 : (version_D2Win == V113d ? 0x10051 : (version_D2Win == V113c ? 0x10022 : (version_D2Win == V112 ? 0x10015 : (version_D2Win == V111b ? 0x10075 : (version_D2Win == V111 ? 0x10061 : (version_D2Win == V110 ? 0x10046 : (version_D2Win == V109d ? 0x10046 : 0x10046))))))))); } else setFctAddr((DWORD *) &D2PrintLineOnTextBox, (HMODULE) offset_D2Win, (LPCSTR) (version_D2Win == V113d ? 10051 : (version_D2Win == V113c ? 10022 : (version_D2Win == V112 ? 10015 : (version_D2Win == V111b ? 10075 : (version_D2Win == V111 ? 10061 : (version_D2Win == V110 ? 10046 : (version_D2Win == V109d ? 10046 : 10046))))))));
        if (version_D2Win > V113d) { D2PrintString = (TD2PrintString) (offset_D2Win + (version_D2Win == V114d ? 0x102320 : (version_D2Win == V113d ? 0x10076 : (version_D2Win == V113c ? 0x10150 : (version_D2Win == V112 ? 0x10001 : (version_D2Win == V111b ? 0x10064 : (version_D2Win == V111 ? 0x10020 : (version_D2Win == V110 ? 0x10117 : (version_D2Win == V109d ? 0x10117 : 0x10117))))))))); } else setFctAddr((DWORD *) &D2PrintString, (HMODULE) offset_D2Win, (LPCSTR) (version_D2Win == V113d ? 10076 : (version_D2Win == V113c ? 10150 : (version_D2Win == V112 ? 10001 : (version_D2Win == V111b ? 10064 : (version_D2Win == V111 ? 10020 : (version_D2Win == V110 ? 10117 : (version_D2Win == V109d ? 10117 : 10117))))))));
        if (version_D2Win > V113d) { D2GetPixelLen = (TD2GetPixelLen) (offset_D2Win + (version_D2Win == V114d ? 0x101820 : (version_D2Win == V113d ? 0x10150 : (version_D2Win == V113c ? 0x10028 : (version_D2Win == V112 ? 0x10132 : (version_D2Win == V111b ? 0x10128 : (version_D2Win == V111 ? 0x10034 : (version_D2Win == V110 ? 0x10121 : (version_D2Win == V109d ? 0x10121 : 0x10121))))))))); } else setFctAddr((DWORD *) &D2GetPixelLen, (HMODULE) offset_D2Win, (LPCSTR) (version_D2Win == V113d ? 10150 : (version_D2Win == V113c ? 10028 : (version_D2Win == V112 ? 10132 : (version_D2Win == V111b ? 10128 : (version_D2Win == V111 ? 10034 : (version_D2Win == V110 ? 10121 : (version_D2Win == V109d ? 10121 : 10121))))))));
        if (version_D2Win > V113d) { D2SetFont = (TD2SetFont) (offset_D2Win + (version_D2Win == V114d ? 0x102EF0 : (version_D2Win == V113d ? 0x10047 : (version_D2Win == V113c ? 0x10184 : (version_D2Win == V112 ? 0x10010 : (version_D2Win == V111b ? 0x10170 : (version_D2Win == V111 ? 0x10141 : (version_D2Win == V110 ? 0x10127 : (version_D2Win == V109d ? 0x10127 : 0x10127))))))))); } else setFctAddr((DWORD *) &D2SetFont, (HMODULE) offset_D2Win, (LPCSTR) (version_D2Win == V113d ? 10047 : (version_D2Win == V113c ? 10184 : (version_D2Win == V112 ? 10010 : (version_D2Win == V111b ? 10170 : (version_D2Win == V111 ? 10141 : (version_D2Win == V110 ? 10127 : (version_D2Win == V109d ? 10127 : 10127))))))));
        if (version_D2Win > V113d) { D2PrintPopup = (TD2PrintPopup) (offset_D2Win + (version_D2Win == V114d ? 0x102280 : (version_D2Win == V113d ? 0x10137 : (version_D2Win == V113c ? 0x10085 : (version_D2Win == V112 ? 0x10031 : (version_D2Win == V111b ? 0x10039 : (version_D2Win == V111 ? 0x10118 : (version_D2Win == V110 ? 0x10129 : (version_D2Win == V109d ? 0x10129 : 0x10129))))))))); } else setFctAddr((DWORD *) &D2PrintPopup, (HMODULE) offset_D2Win, (LPCSTR) (version_D2Win == V113d ? 10137 : (version_D2Win == V113c ? 10085 : (version_D2Win == V112 ? 10031 : (version_D2Win == V111b ? 10039 : (version_D2Win == V111 ? 10118 : (version_D2Win == V110 ? 10129 : (version_D2Win == V109d ? 10129 : 10129))))))));
        if (version_D2Win > V113d) { D2GetPixelRect = (TD2GetPixelRect) (offset_D2Win + (version_D2Win == V114d ? 0x00000 : (version_D2Win == V113d ? 0x00000 : (version_D2Win == V113c ? 0x00000 : (version_D2Win == V112 ? 0x00000 : (version_D2Win == V111b ? 0x00000 : (version_D2Win == V111 ? 0x00000 : (version_D2Win == V110 ? 0x10131 : (version_D2Win == V109d ? 0x10131 : 0x10131))))))))); } else setFctAddr((DWORD *) &D2GetPixelRect, (HMODULE) offset_D2Win, (LPCSTR) (version_D2Win == V113d ? 00000 : (version_D2Win == V113c ? 00000 : (version_D2Win == V112 ? 00000 : (version_D2Win == V111b ? 00000 : (version_D2Win == V111 ? 00000 : (version_D2Win == V110 ? 10131 : (version_D2Win == V109d ? 10131 : 10131))))))));
        if (version_D2Win > V113d) { D2PrintTextPopup = (TD2PrintTextPopup) (offset_D2Win + (version_D2Win == V114d ? 0x00000 : (version_D2Win == V113d ? 0x00000 : (version_D2Win == V113c ? 0x00000 : (version_D2Win == V112 ? 0x00000 : (version_D2Win == V111b ? 0x00000 : (version_D2Win == V111 ? 0x00000 : (version_D2Win == V110 ? 0x10132 : (version_D2Win == V109d ? 0x10132 : 0x10132))))))))); } else setFctAddr((DWORD *) &D2PrintTextPopup, (HMODULE) offset_D2Win, (LPCSTR) (version_D2Win == V113d ? 00000 : (version_D2Win == V113c ? 00000 : (version_D2Win == V112 ? 00000 : (version_D2Win == V111b ? 00000 : (version_D2Win == V111 ? 00000 : (version_D2Win == V110 ? 10132 : (version_D2Win == V109d ? 10132 : 10132))))))));
        if (version_D2Win > V113d) { D2CreateTextBox = (TD2CreateTextBox) (offset_D2Win + (version_D2Win == V114d ? 0xF93C0 : (version_D2Win == V113d ? 0x10164 : (version_D2Win == V113c ? 0x10098 : (version_D2Win == V112 ? 0x10098 : (version_D2Win == V111b ? 0x10113 : (version_D2Win == V111 ? 0x10147 : (version_D2Win == V110 ? 0x10017 : (version_D2Win == V109d ? 0x10017 : 0x10017))))))))); } else setFctAddr((DWORD *) &D2CreateTextBox, (HMODULE) offset_D2Win, (LPCSTR) (version_D2Win == V113d ? 10164 : (version_D2Win == V113c ? 10098 : (version_D2Win == V112 ? 10098 : (version_D2Win == V111b ? 10113 : (version_D2Win == V111 ? 10147 : (version_D2Win == V110 ? 10017 : (version_D2Win == V109d ? 10017 : 10017))))))));
        if (version_D2CMP > V113d) { D2CMP10014 = (TD2CMP10014) (offset_D2CMP + (version_D2CMP == V114d ? 0x201A50 : (version_D2CMP == V113d ? 0x10020 : (version_D2CMP == V113c ? 0x10065 : (version_D2CMP == V112 ? 0x10106 : (version_D2CMP == V111b ? 0x10014 : (version_D2CMP == V111 ? 0x10021 : (version_D2CMP == V110 ? 0x10032 : (version_D2CMP == V109d ? 0x10032 : 0x10032))))))))); } else setFctAddr((DWORD *) &D2CMP10014, (HMODULE) offset_D2CMP, (LPCSTR) (version_D2CMP == V113d ? 10020 : (version_D2CMP == V113c ? 10065 : (version_D2CMP == V112 ? 10106 : (version_D2CMP == V111b ? 10014 : (version_D2CMP == V111 ? 10021 : (version_D2CMP == V110 ? 10032 : (version_D2CMP == V109d ? 10032 : 10032))))))));
///A8 section
        D2GetCharStatsBIN = (TD2GetCharStatsBIN) (offset_D2Common + (version_D2Common == V114d ? 0x833E0 : (version_D2Common == V113d ? 0x17B0 : (version_D2Common == V113c ? 0x12D0 : (version_D2Common == V112 ? 0x1220 : (version_D2Common == V111b ? 0x1800 : (version_D2Common == V111 ? 0x15D0 : (version_D2Common == V110 ? 0x82C80 : (version_D2Common == V109d ? 0x00000 : 0x00000)))))))));
        D2CompileCubeInput = (TD2CompileCubeInput) (offset_D2Common + (version_D2Common == V114d ? 0x268600 : (version_D2Common == V113d ? 0x5B0E0 : (version_D2Common == V113c ? 0x1C020 : (version_D2Common == V112 ? 0x116C0 : (version_D2Common == V111b ? 0x1A100 : (version_D2Common == V111 ? 0x5D7D0 : (version_D2Common == V110 ? 0x12410 : (version_D2Common == V109d ? 0x00000 : 0x00000)))))))));
        D2GetItemTypesBIN = (TD2GetItemTypesBIN) (offset_D2Common + (version_D2Common == V114d ? 0x155C90 : (version_D2Common == V113d ? 0x1160 : (version_D2Common == V113c ? 0x1300 : (version_D2Common == V112 ? 0x1140 : (version_D2Common == V111b ? 0x1380 : (version_D2Common == V111 ? 0x11F0 : (version_D2Common == V110 ? 0x2B1A0 : (version_D2Common == V109d ? 0x00000 : 0x00000)))))))));
        D2GetItemStatCostBIN = (TD2GetItemStatCostBIN) (offset_D2Common + (version_D2Common == V114d ? 0x5C4F0 : (version_D2Common == V113d ? 0x17E0 : (version_D2Common == V113c ? 0x17A0 : (version_D2Common == V112 ? 0x1540 : (version_D2Common == V111b ? 0x12F0 : (version_D2Common == V111 ? 0x13F0 : (version_D2Common == V110 ? 0x642B0 : (version_D2Common == V109d ? 0x00000 : 0x00000)))))))));
        D2ReadFile = (TD2ReadFile) (offset_D2Common + (version_D2Common == V114d ? 0x117079 : (version_D2Common == V113d ? 0xB5E0 : (version_D2Common == V113c ? 0x9900 : (version_D2Common == V112 ? 0x9900 : (version_D2Common == V111b ? 0x98D0 : (version_D2Common == V111 ? 0x96E0 : (version_D2Common == V110 ? 0x84268 : (version_D2Common == V109d ? 0x739B4 : 0x738A4)))))))));
        D2LoadSuperuniques = (TD2LoadSuperuniques) (offset_D2Common + (version_D2Common == V114d ? 0x2552E0 : (version_D2Common == V113d ? 0x80C40 : (version_D2Common == V113c ? 0x59870 : (version_D2Common == V112 ? 0x7D2A0 : (version_D2Common == V111b ? 0x32AA0 : (version_D2Common == V111 ? 0x71EB0 : (version_D2Common == V110 ? 0x29FA0 : (version_D2Common == V109d ? 0x1F510 : 0x1F500)))))))));
        D2GetInventoryBIN = (TD2GetInventoryBIN) (offset_D2Common + (version_D2Common == V114d ? 0x00000 : (version_D2Common == V113d ? 0x00000 : (version_D2Common == V113c ? 0x81EA0 : (version_D2Common == V112 ? 0x00000 : (version_D2Common == V111b ? 0x00000 : (version_D2Common == V111 ? 0x00000 : (version_D2Common == V110 ? 0x00000 : (version_D2Common == V109d ? 0x00000 : 0x00000)))))))));
        D2LoadImage = (TD2LoadImage) (offset_D2Client + (version_D2Client == V114d ? 0x788B0 : (version_D2Client == V113d ? 0xA9480 : (version_D2Client == V113c ? 0x2B420 : (version_D2Client == V112 ? 0xBEF70 : (version_D2Client == V111b ? 0xA9070 : (version_D2Client == V111 ? 0x75D00 : (version_D2Client == V110 ? 0x1000 : (version_D2Client == V109d ? 0x1000 : 0x1000)))))))));
        D2FreeImage = (TD2FreeImage) (offset_D2Client + (version_D2Client == V114d ? 0x78A00 : (version_D2Client == V113d ? 0x00000 : (version_D2Client == V113c ? 0x00000 : (version_D2Client == V112 ? 0x00000 : (version_D2Client == V111b ? 0x00000 : (version_D2Client == V111 ? 0x00000 : (version_D2Client == V110 ? 0x1140 : (version_D2Client == V109d ? 0x1150 : 0x1150)))))))));
        D2SendMsgToAll = (TD2SendMsgToAll) (offset_D2Client + (version_D2Client == V114d ? 0x787B0 : (version_D2Client == V113d ? 0xB6890 : (version_D2Client == V113c ? 0x147A0 : (version_D2Client == V112 ? 0x79670 : (version_D2Client == V111b ? 0x5E4E0 : (version_D2Client == V111 ? 0x73620 : (version_D2Client == V110 ? 0xDB50 : (version_D2Client == V109d ? 0xD630 : 0xD640)))))))));
        D2GetLastMonsterIDFight = (TD2GetLastMonsterIDFight) (offset_D2Client + (version_D2Client == V114d ? 0x00000 : (version_D2Client == V113d ? 0x00000 : (version_D2Client == V113c ? 0x00000 : (version_D2Client == V112 ? 0x00000 : (version_D2Client == V111b ? 0x00000 : (version_D2Client == V111 ? 0x00000 : (version_D2Client == V110 ? 0x15A80 : (version_D2Client == V109d ? 0x00000 : 0x00000)))))))));
        D2PrintStatsPage = (TD2PrintStatsPage) (offset_D2Client + (version_D2Client == V114d ? 0xA7D00 : (version_D2Client == V113d ? 0xBF640 : (version_D2Client == V113c ? 0xBCEA0 : (version_D2Client == V112 ? 0x6B280 : (version_D2Client == V111b ? 0x89320 : (version_D2Client == V111 ? 0x828A0 : (version_D2Client == V110 ? 0x2FD60 : (version_D2Client == V109d ? 0x297F0 : 0x29800)))))))));
        D2PrintStat = (TD2PrintStat) (offset_D2Client + (version_D2Client == V114d ? 0xE4D80 : (version_D2Client == V113d ? 0x2CE40 : (version_D2Client == V113c ? 0x54E10 : (version_D2Client == V112 ? 0x88EA0 : (version_D2Client == V111b ? 0x21250 : (version_D2Client == V111 ? 0xB8CB0 : (version_D2Client == V110 ? 0x521C0 : (version_D2Client == V109d ? 0x4BB20 : 0x4BB20)))))))));
        D2SetColorPopup = (TD2SetColorPopup) (offset_D2Client + (version_D2Client == V114d ? 0x521C0 : (version_D2Client == V113d ? 0x18820 : (version_D2Client == V113c ? 0xBF5F0 : (version_D2Client == V112 ? 0x8B7A0 : (version_D2Client == V111b ? 0x62070 : (version_D2Client == V111 ? 0x9EEB0 : (version_D2Client == V110 ? 0x80430 : (version_D2Client == V109d ? 0x84DE0 : 0x85A60)))))))));
        D2PlaySound = (TD2PlaySound) (offset_D2Client + (version_D2Client == V114d ? 0xB9A00 : (version_D2Client == V113d ? 0x26270 : (version_D2Client == V113c ? 0x88A70 : (version_D2Client == V112 ? 0x31FA0 : (version_D2Client == V111b ? 0x54210 : (version_D2Client == V111 ? 0x3ACC0 : (version_D2Client == V110 ? 0xB5820 : (version_D2Client == V109d ? 0xB36E0 : 0xB4360)))))))));
        D2SendToServerXX = (TD2SendToServerXX) (offset_D2Client + (version_D2Client == V114d ? 0x78350 : (version_D2Client == V113d ? 0xB61F0 : (version_D2Client == V113c ? 0x143E0 : (version_D2Client == V112 ? 0x791A0 : (version_D2Client == V111b ? 0x5DE40 : (version_D2Client == V111 ? 0x73260 : (version_D2Client == V110 ? 0x00000 : (version_D2Client == V109d ? 0x00000 : 0x00000)))))))));
        D2TogglePage = (TD2TogglePage) (offset_D2Client + (version_D2Client == V114d ? 0x55F20 : (version_D2Client == V113d ? 0x1C190 : (version_D2Client == V113c ? 0xC2790 : (version_D2Client == V112 ? 0x8EF00 : (version_D2Client == V111b ? 0x65690 : (version_D2Client == V111 ? 0xA1F30 : (version_D2Client == V110 ? 0x83260 : (version_D2Client == V109d ? 0x87CC0 : 0x88940)))))))));
        D2ClickOnStashButton = (TD2ClickOnStashButton) (offset_D2Client + (version_D2Client == V114d ? 0x89980 : (version_D2Client == V113d ? 0x90C10 : (version_D2Client == V113c ? 0x8CD00 : (version_D2Client == V112 ? 0xA6640 : (version_D2Client == V111b ? 0x710C0 : (version_D2Client == V111 ? 0xA6520 : (version_D2Client == V110 ? 0x00000 : (version_D2Client == V109d ? 0x00000 : 0x00000)))))))));
        D2LoadBuySelBtn = (TD2LoadBuySelBtn) (offset_D2Client + (version_D2Client == V114d ? 0x54600 : (version_D2Client == V113d ? 0x18AA0 : (version_D2Client == V113c ? 0xBEAF0 : (version_D2Client == V112 ? 0x8B8F0 : (version_D2Client == V111b ? 0x621C0 : (version_D2Client == V111 ? 0x9E3B0 : (version_D2Client == V110 ? 0x84110 : (version_D2Client == V109d ? 0x88B30 : 0x897B0)))))))));
        D2LoadResImage = (TD2LoadResImage) (offset_D2Client + (version_D2Client == V114d ? 0x520C0 : (version_D2Client == V113d ? 0x00000 : (version_D2Client == V113c ? 0x00000 : (version_D2Client == V112 ? 0x00000 : (version_D2Client == V111b ? 0x00000 : (version_D2Client == V111 ? 0x00000 : (version_D2Client == V110 ? 0x00000 : (version_D2Client == V109d ? 0x00000 : 0x00000)))))))));
        D2FreeResImages = (TD2FreeResImages) (offset_D2Client + (version_D2Client == V114d ? 0x96990 : (version_D2Client == V113d ? 0x00000 : (version_D2Client == V113c ? 0x00000 : (version_D2Client == V112 ? 0x00000 : (version_D2Client == V111b ? 0x00000 : (version_D2Client == V111 ? 0x00000 : (version_D2Client == V110 ? 0x00000 : (version_D2Client == V109d ? 0x00000 : 0x00000)))))))));
        D2ReceivePacket = (TD2ReceivePacket) (offset_D2Client + (version_D2Client == V114d ? 0x5C850 : (version_D2Client == V113d ? 0x00000 : (version_D2Client == V113c ? 0x00000 : (version_D2Client == V112 ? 0x00000 : (version_D2Client == V111b ? 0x00000 : (version_D2Client == V111 ? 0x00000 : (version_D2Client == V110 ? 0x00000 : (version_D2Client == V109d ? 0x00000 : 0x00000)))))))));
        D2PrintInterface = (TD2PrintInterface) (offset_D2Client + (version_D2Client == V114d ? 0x56EE0 : (version_D2Client == V113d ? 0x1D3E0 : (version_D2Client == V113c ? 0xC39E0 : (version_D2Client == V112 ? 0x90150 : (version_D2Client == V111b ? 0x669F0 : (version_D2Client == V111 ? 0xA35F0 : (version_D2Client == V110 ? 0x81B70 : (version_D2Client == V109d ? 0x865A0 : 0x87220)))))))));
        D2AddClient = (TD2AddClient) (offset_D2Game + (version_D2Game == V114d ? 0x12C550 : (version_D2Game == V113d ? 0xE5070 : (version_D2Game == V113c ? 0x49930 : (version_D2Game == V112 ? 0xEB060 : (version_D2Game == V111b ? 0xE8210 : (version_D2Game == V111 ? 0xE3DA0 : (version_D2Game == V110 ? 0x6C60 : (version_D2Game == V109d ? 0x00000 : 0x00000)))))))));
        D2GetGameByClientID = (TD2GetGameByClientID) (offset_D2Game + (version_D2Game == V114d ? 0x12E860 : (version_D2Game == V113d ? 0xBC700 : (version_D2Game == V113c ? 0x2AAE0 : (version_D2Game == V112 ? 0xA6360 : (version_D2Game == V111b ? 0xE49A0 : (version_D2Game == V111 ? 0xE0520 : (version_D2Game == V110 ? 0x94E0 : (version_D2Game == V109d ? 0x00000 : 0x00000)))))))));
        D2BroadcastFunction = (TD2BroadcastFunction) (offset_D2Game + (version_D2Game == V114d ? 0x12DED0 : (version_D2Game == V113d ? 0xBB510 : (version_D2Game == V113c ? 0x29820 : (version_D2Game == V112 ? 0xA5080 : (version_D2Game == V111b ? 0xE36D0 : (version_D2Game == V111 ? 0xDF250 : (version_D2Game == V110 ? 0xB0E0 : (version_D2Game == V109d ? 0x00000 : 0x00000)))))))));
        D2SendPacket = (TD2SendPacket) (offset_D2Game + (version_D2Game == V114d ? 0x13B280 : (version_D2Game == V113d ? 0xDB780 : (version_D2Game == V113c ? 0x8A3E0 : (version_D2Game == V112 ? 0x7D220 : (version_D2Game == V111b ? 0xA0D50 : (version_D2Game == V111 ? 0x41420 : (version_D2Game == V110 ? 0xC710 : (version_D2Game == V109d ? 0xC650 : 0xC380)))))))));
        D2SetSkillBaseLevelOnClient = (TD2SetSkillBaseLevelOnClient) (offset_D2Game + (version_D2Game == V114d ? 0x13C4A0 : (version_D2Game == V113d ? 0xDD4F0 : (version_D2Game == V113c ? 0x8D5F0 : (version_D2Game == V112 ? 0x802E0 : (version_D2Game == V111b ? 0xA3F20 : (version_D2Game == V111 ? 0x44D00 : (version_D2Game == V110 ? 0xDB50 : (version_D2Game == V109d ? 0xD920 : 0xD650)))))))));
        D2LinkPortal = (TD2LinkPortal) (offset_D2Game + (version_D2Game == V114d ? 0x16CF40 : (version_D2Game == V113d ? 0x15F40 : (version_D2Game == V113c ? 0xA22E0 : (version_D2Game == V112 ? 0xAE930 : (version_D2Game == V111b ? 0x109F0 : (version_D2Game == V111 ? 0x27230 : (version_D2Game == V110 ? 0x00000 : (version_D2Game == V109d ? 0x00000 : 0x00000)))))))));
        D2VerifIfNotCarry1 = (TD2VerifIfNotCarry1) (offset_D2Game + (version_D2Game == V114d ? 0x15CA40 : (version_D2Game == V113d ? 0xB2F70 : (version_D2Game == V113c ? 0xD2070 : (version_D2Game == V112 ? 0x11FF0 : (version_D2Game == V111b ? 0x43E60 : (version_D2Game == V111 ? 0x38D90 : (version_D2Game == V110 ? 0x128F0 : (version_D2Game == V109d ? 0x00000 : 0x00000)))))))));
        D2TestPositionInRoom = (TD2TestPositionInRoom) (offset_D2Game + (version_D2Game == V114d ? 0x63740 : (version_D2Game == V113d ? 0x1340 : (version_D2Game == V113c ? 0x1280 : (version_D2Game == V112 ? 0x11F0 : (version_D2Game == V111b ? 0x1DF0 : (version_D2Game == V111 ? 0x1090 : (version_D2Game == V110 ? 0x22070 : (version_D2Game == V109d ? 0x00000 : 0x00000)))))))));
        D2SpawnSuperUnique = (TD2SpawnSuperUnique) (offset_D2Game + (version_D2Game == V114d ? 0x1A09E0 : (version_D2Game == V113d ? 0xCDE20 : (version_D2Game == V113c ? 0x24950 : (version_D2Game == V112 ? 0x40B90 : (version_D2Game == V111b ? 0xEC7E0 : (version_D2Game == V111 ? 0x4ABE0 : (version_D2Game == V110 ? 0x3F220 : (version_D2Game == V109d ? 0x00000 : 0x00000)))))))));
        D2SpawnMonster = (TD2SpawnMonster) (offset_D2Game + (version_D2Game == V114d ? 0x1B2F20 : (version_D2Game == V113d ? 0xC8D70 : (version_D2Game == V113c ? 0xEF650 : (version_D2Game == V112 ? 0xEFB10 : (version_D2Game == V111b ? 0xEF870 : (version_D2Game == V111 ? 0xC80F0 : (version_D2Game == V110 ? 0x00000 : (version_D2Game == V109d ? 0x00000 : 0x00000)))))))));
        D2Game235C0 = (TD2Game235C0) (offset_D2Game + (version_D2Game == V114d ? 0x142B40 : (version_D2Game == V113d ? 0x59980 : (version_D2Game == V113c ? 0x200E0 : (version_D2Game == V112 ? 0xD410 : (version_D2Game == V111b ? 0x235C0 : (version_D2Game == V111 ? 0xD6D10 : (version_D2Game == V110 ? 0x00000 : (version_D2Game == V109d ? 0x00000 : 0x00000)))))))));
        D2LoadInventory = (TD2LoadInventory) (offset_D2Game + (version_D2Game == V114d ? 0x1335E0 : (version_D2Game == V113d ? 0x3A4C0 : (version_D2Game == V113c ? 0x54810 : (version_D2Game == V112 ? 0x44950 : (version_D2Game == V111b ? 0x25D50 : (version_D2Game == V111 ? 0xB9D70 : (version_D2Game == V110 ? 0x5B8A0 : (version_D2Game == V109d ? 0x4F500 : 0x4F100)))))))));
        D2GameGetObject = (TD2GameGetObject) (offset_D2Game + (version_D2Game == V114d ? 0x152F60 : (version_D2Game == V113d ? 0x6DC40 : (version_D2Game == V113c ? 0xE03A0 : (version_D2Game == V112 ? 0x93650 : (version_D2Game == V111b ? 0xBEF80 : (version_D2Game == V111 ? 0x97620 : (version_D2Game == V110 ? 0x8BB00 : (version_D2Game == V109d ? 0x7BFD0 : 0x7BAE0)))))))));
        D2CreateUnit = (TD2CreateUnit) (offset_D2Game + (version_D2Game == V114d ? 0x155230 : (version_D2Game == V113d ? 0x6FE10 : (version_D2Game == V113c ? 0xE1D90 : (version_D2Game == V112 ? 0x94E70 : (version_D2Game == V111b ? 0xC09E0 : (version_D2Game == V111 ? 0x99760 : (version_D2Game == V110 ? 0x00000 : (version_D2Game == V109d ? 0x00000 : 0x00000)))))))));
        D2OpenPandPortal = (TD2OpenPandPortal) (offset_D2Game + (version_D2Game == V114d ? 0x165A90 : (version_D2Game == V113d ? 0x941E0 : (version_D2Game == V113c ? 0x70180 : (version_D2Game == V112 ? 0xD1AA0 : (version_D2Game == V111b ? 0x34920 : (version_D2Game == V111 ? 0x9B480 : (version_D2Game == V110 ? 0x00000 : (version_D2Game == V109d ? 0x00000 : 0x00000)))))))));
        D2OpenPandFinalPortal = (TD2OpenPandFinalPortal) (offset_D2Game + (version_D2Game == V114d ? 0x165AA0 : (version_D2Game == V113d ? 0x941D0 : (version_D2Game == V113c ? 0x70170 : (version_D2Game == V112 ? 0xD1A90 : (version_D2Game == V111b ? 0x34910 : (version_D2Game == V111 ? 0x9B470 : (version_D2Game == V110 ? 0x00000 : (version_D2Game == V109d ? 0x00000 : 0x00000)))))))));
        D2MephAI = (TD2MephAI) (offset_D2Game + (version_D2Game == V114d ? 0x1F78B0 : (version_D2Game == V113d ? 0x4EAD0 : (version_D2Game == V113c ? 0x85B60 : (version_D2Game == V112 ? 0xCD0F0 : (version_D2Game == V111b ? 0xD7BD0 : (version_D2Game == V111 ? 0x75980 : (version_D2Game == V110 ? 0x00000 : (version_D2Game == V109d ? 0x00000 : 0x00000)))))))));
        D2DiabloAI = (TD2DiabloAI) (offset_D2Game + (version_D2Game == V114d ? 0x1E9170 : (version_D2Game == V113d ? 0x31920 : (version_D2Game == V113c ? 0xA9610 : (version_D2Game == V112 ? 0xDBE90 : (version_D2Game == V111b ? 0x85AA0 : (version_D2Game == V111 ? 0x84730 : (version_D2Game == V110 ? 0x00000 : (version_D2Game == V109d ? 0x00000 : 0x00000)))))))));
        D2BaalAI = (TD2BaalAI) (offset_D2Game + (version_D2Game == V114d ? 0x1FCFE0 : (version_D2Game == V113d ? 0xC8850 : (version_D2Game == V113c ? 0xB8610 : (version_D2Game == V112 ? 0xB3B90 : (version_D2Game == V111b ? 0x2BC80 : (version_D2Game == V111 ? 0xEAB20 : (version_D2Game == V110 ? 0x00000 : (version_D2Game == V109d ? 0x00000 : 0x00000)))))))));
        D2UberBaalAI = (TD2UberBaalAI) (offset_D2Game + (version_D2Game == V114d ? 0x1FD200 : (version_D2Game == V113d ? 0xC6EC0 : (version_D2Game == V113c ? 0xB6C80 : (version_D2Game == V112 ? 0xB2210 : (version_D2Game == V111b ? 0x2A300 : (version_D2Game == V111 ? 0xE92B0 : (version_D2Game == V110 ? 0x00000 : (version_D2Game == V109d ? 0x00000 : 0x00000)))))))));
        D2UberMephAI = (TD2UberMephAI) (offset_D2Game + (version_D2Game == V114d ? 0x1F81C0 : (version_D2Game == V113d ? 0x49480 : (version_D2Game == V113c ? 0x7B4E0 : (version_D2Game == V112 ? 0xC2A90 : (version_D2Game == V111b ? 0xD2D70 : (version_D2Game == V111 ? 0x70320 : (version_D2Game == V110 ? 0x00000 : (version_D2Game == V109d ? 0x00000 : 0x00000)))))))));
        D2UberDiabloAI = (TD2UberDiabloAI) (offset_D2Game + (version_D2Game == V114d ? 0x1E9DF0 : (version_D2Game == V113d ? 0x2C3F0 : (version_D2Game == V113c ? 0xA39D0 : (version_D2Game == V112 ? 0xD6250 : (version_D2Game == V111b ? 0x7FE60 : (version_D2Game == V111 ? 0x7F200 : (version_D2Game == V110 ? 0x00000 : (version_D2Game == V109d ? 0x00000 : 0x00000)))))))));
        D2SaveGame = (TD2SaveGame) (offset_D2Game + (version_D2Game == V114d ? 0x12CA10 : (version_D2Game == V113d ? 0xBE660 : (version_D2Game == V113c ? 0x2C830 : (version_D2Game == V112 ? 0xA8090 : (version_D2Game == V111b ? 0xE66D0 : (version_D2Game == V111 ? 0xE2390 : (version_D2Game == V110 ? 0x89C0 : (version_D2Game == V109d ? 0x00000 : 0x00000)))))))));
        D2MonsterMove = (TD2MonsterMove) (offset_D2Game + (version_D2Game == V114d ? 0x1DEB60 : (version_D2Game == V113d ? 0xF1800 : (version_D2Game == V113c ? 0xF2540 : (version_D2Game == V112 ? 0xF0D70 : (version_D2Game == V111b ? 0xF0F70 : (version_D2Game == V111 ? 0xEF580 : (version_D2Game == V110 ? 0x00000 : (version_D2Game == V109d ? 0x00000 : 0x00000)))))))));
        D2MonsterUseSkill = (TD2MonsterUseSkill) (offset_D2Game + (version_D2Game == V114d ? 0x1DEAD0 : (version_D2Game == V113d ? 0xF1430 : (version_D2Game == V113c ? 0xF2380 : (version_D2Game == V112 ? 0xF0BB0 : (version_D2Game == V111b ? 0xF0DB0 : (version_D2Game == V111 ? 0xFF1B0 : (version_D2Game == V110 ? 0x00000 : (version_D2Game == V109d ? 0x00000 : 0x00000)))))))));
        D2SaveSPChar = (TD2SaveSPChar) (offset_D2Game + (version_D2Game == V114d ? 0x132240 : (version_D2Game == V113d ? 0x39810 : (version_D2Game == V113c ? 0x53F10 : (version_D2Game == V112 ? 0x44140 : (version_D2Game == V111b ? 0x25450 : (version_D2Game == V111 ? 0xB9340 : (version_D2Game == V110 ? 0x00000 : (version_D2Game == V109d ? 0x00000 : 0x00000)))))))));
//ONLY UNTIL 1.10 :
        D2isLODGame = (TD2isLODGame) (offset_D2Client + (version_D2Client == V114d ? 0x00000 : (version_D2Client == V113d ? 0x00000 : (version_D2Client == V113c ? 0x00000 : (version_D2Client == V112 ? 0x00000 : (version_D2Client == V111b ? 0x00000 : (version_D2Client == V111 ? 0x00000 : (version_D2Client == V110 ? 0xC080 : (version_D2Client == V109d ? 0xB9F0 : 0xBA00)))))))));
        D2GetDifficultyLevel = (TD2GetDifficultyLevel) (offset_D2Client + (version_D2Client == V114d ? 0x00000 : (version_D2Client == V113d ? 0x00000 : (version_D2Client == V113c ? 0x00000 : (version_D2Client == V112 ? 0x00000 : (version_D2Client == V111b ? 0x00000 : (version_D2Client == V111 ? 0x00000 : (version_D2Client == V110 ? 0xC090 : (version_D2Client == V109d ? 0x00000 : 0x00000)))))))));
        D2GetMouseX = (TD2GetMouseX) (offset_D2Client + (version_D2Client == V114d ? 0x00000 : (version_D2Client == V113d ? 0x00000 : (version_D2Client == V113c ? 0x00000 : (version_D2Client == V112 ? 0x00000 : (version_D2Client == V111b ? 0x00000 : (version_D2Client == V111 ? 0x00000 : (version_D2Client == V110 ? 0xB7BC0 : (version_D2Client == V109d ? 0xB59F0 : 0xB6670)))))))));
        D2GetMouseY = (TD2GetMouseY) (offset_D2Client + (version_D2Client == V114d ? 0x00000 : (version_D2Client == V113d ? 0x00000 : (version_D2Client == V113c ? 0x00000 : (version_D2Client == V112 ? 0x00000 : (version_D2Client == V111b ? 0x00000 : (version_D2Client == V111 ? 0x00000 : (version_D2Client == V110 ? 0xB7BD0 : (version_D2Client == V109d ? 0xB5A00 : 0xB6680)))))))));
        D2GetClientPlayer = (TD2GetClientPlayer) (offset_D2Client + (version_D2Client == V114d ? 0x63DD0 : (version_D2Client == V113d ? 0x00000 : (version_D2Client == V113c ? 0x00000 : (version_D2Client == V112 ? 0x00000 : (version_D2Client == V111b ? 0x00000 : (version_D2Client == V111 ? 0x00000 : (version_D2Client == V110 ? 0x883D0 : (version_D2Client == V109d ? 0x8CFC0 : 0x8DC40)))))))));
        D2CleanStatMouseUp = (TD2CleanStatMouseUp) (offset_D2Client + (version_D2Client == V114d ? 0x4DA70 : (version_D2Client == V113d ? 0x00000 : (version_D2Client == V113c ? 0x00000 : (version_D2Client == V112 ? 0x00000 : (version_D2Client == V111b ? 0x00000 : (version_D2Client == V111 ? 0x00000 : (version_D2Client == V110 ? 0xBF60 : (version_D2Client == V109d ? 0xB910 : 0xB920)))))))));
        D2SendToServer3 = (TD2SendToServer3) (offset_D2Client + (version_D2Client == V114d ? 0x00000 : (version_D2Client == V113d ? 0x00000 : (version_D2Client == V113c ? 0x00000 : (version_D2Client == V112 ? 0x00000 : (version_D2Client == V111b ? 0x00000 : (version_D2Client == V111 ? 0x00000 : (version_D2Client == V110 ? 0xD990 : (version_D2Client == V109d ? 0xD200 : 0xD210)))))))));
        D2GetClient = (TD2GetClient) (offset_D2Game + (version_D2Game == V114d ? 0x1531C0 : (version_D2Game == V113d ? 0x00000 : (version_D2Game == V113c ? 0x00000 : (version_D2Game == V112 ? 0x00000 : (version_D2Game == V111b ? 0x00000 : (version_D2Game == V111 ? 0x00000 : (version_D2Game == V110 ? 0x8C2E0 : (version_D2Game == V109d ? 0x7C7B0 : 0x7C2C0)))))))));

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////// VARIABLES ////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ptClientTable = (NetClient **) (offset_D2Game + (version_D2Game == V114d ? 0x4842A8 : (version_D2Game == V113d ? 0x1105E0 : (version_D2Game == V113c ? 0x1107B8 : (version_D2Game == V112 ? 0x1105E0 : (version_D2Game == V111b ? 0x1115E0 : (version_D2Game == V111 ? 0x111718 : (version_D2Game == V110 ? 0x113FB8 : (version_D2Game == V109d ? 0xF2918 : 0xF2A80)))))))));
        ptResolutionY = (DWORD *) (offset_D2Client + (version_D2Client == V114d ? 0x311470 : (version_D2Client == V113d ? 0xF7038 : (version_D2Client == V113c ? 0xDBC4C : (version_D2Client == V112 ? 0xDC6E4 : (version_D2Client == V111b ? 0xF4FC8 : (version_D2Client == V111 ? 0xF5C60 : (version_D2Client == V110 ? 0xD40F0 : (version_D2Client == V109d ? 0xD40E0 : 0xD50E8)))))))));
        ptResolutionX = (DWORD *) (offset_D2Client + (version_D2Client == V114d ? 0x31146C : (version_D2Client == V113d ? 0xF7034 : (version_D2Client == V113c ? 0xDBC48 : (version_D2Client == V112 ? 0xDC6E0 : (version_D2Client == V111b ? 0xF4FC4 : (version_D2Client == V111 ? 0xF5C5C : (version_D2Client == V110 ? 0xD40F4 : (version_D2Client == V109d ? 0xD40E4 : 0xD50EC)))))))));
        ptNegWindowStartY = (DWORD *) (offset_D2Client + (version_D2Client == V114d ? 0x3A285C : (version_D2Client == V113d ? 0x11D358 : (version_D2Client == V113c ? 0x11B9A4 : (version_D2Client == V112 ? 0x11BD2C : (version_D2Client == V111b ? 0x11BEFC : (version_D2Client == V111 ? 0x11BD28 : (version_D2Client == V110 ? 0x11A74C : (version_D2Client == V109d ? 0x124958 : 0x125AD8)))))))));
        ptWindowStartX = (DWORD *) (offset_D2Client + (version_D2Client == V114d ? 0x3A2858 : (version_D2Client == V113d ? 0x11D354 : (version_D2Client == V113c ? 0x11B9A0 : (version_D2Client == V112 ? 0x11BD28 : (version_D2Client == V111b ? 0x11BEF8 : (version_D2Client == V111 ? 0x11BD24 : (version_D2Client == V110 ? 0x11A748 : (version_D2Client == V109d ? 0x124954 : 0x125AD4)))))))));
        ptIsLodGame = (DWORD *) (offset_D2Client + (version_D2Client == V114d ? 0x3A04F4 : (version_D2Client == V113d ? 0x1087B4 : (version_D2Client == V113c ? 0x119854 : (version_D2Client == V112 ? 0x10330C : (version_D2Client == V111b ? 0x11A2F4 : (version_D2Client == V111 ? 0xFB3F4 : (version_D2Client == V110 ? 0x000000 : (version_D2Client == V109d ? 0x000000 : 0x000000)))))))));
        ptDifficultyLevel = (BYTE *) (offset_D2Client + (version_D2Client == V114d ? 0x000000 : (version_D2Client == V113d ? 0x000000 : (version_D2Client == V113c ? 0x000000 : (version_D2Client == V112 ? 0x11BFF4 : (version_D2Client == V111b ? 0x11C2A8 : (version_D2Client == V111 ? 0x11BFB8 : (version_D2Client == V110 ? 0x10795C : (version_D2Client == V109d ? 0x000000 : 0x000000)))))))));
        ptMouseY = (DWORD *) (offset_D2Client + (version_D2Client == V114d ? 0x3A6AAC : (version_D2Client == V113d ? 0x11C94C : (version_D2Client == V113c ? 0x11B824 : (version_D2Client == V112 ? 0x101634 : (version_D2Client == V111b ? 0x11B414 : (version_D2Client == V111 ? 0x10A40C : (version_D2Client == V110 ? 0x000000 : (version_D2Client == V109d ? 0x000000 : 0x000000)))))))));
        ptMouseX = (DWORD *) (offset_D2Client + (version_D2Client == V114d ? 0x3A6AB0 : (version_D2Client == V113d ? 0x11C950 : (version_D2Client == V113c ? 0x11B828 : (version_D2Client == V112 ? 0x101638 : (version_D2Client == V111b ? 0x11B418 : (version_D2Client == V111 ? 0x10A410 : (version_D2Client == V110 ? 0x000000 : (version_D2Client == V109d ? 0x000000 : 0x000000)))))))));
        ptptClientChar = (Unit **) (offset_D2Client + (version_D2Client == V114d ? 0x3A6A70 : (version_D2Client == V113d ? 0x11D050 : (version_D2Client == V113c ? 0x11BBFC : (version_D2Client == V112 ? 0x11C3D0 : (version_D2Client == V111b ? 0x11C1E0 : (version_D2Client == V111 ? 0x11C4F0 : (version_D2Client == V110 ? 0x000000 : (version_D2Client == V109d ? 0x000000 : 0x000000)))))))));
        ptInputCommandLen = (DWORD *) (offset_D2Client + (version_D2Client == V114d ? 0x3BB5E8 : (version_D2Client == V113d ? 0x11CAA4 : (version_D2Client == V113c ? 0x11C028 : (version_D2Client == V112 ? 0x11BF48 : (version_D2Client == V111b ? 0x11BB30 : (version_D2Client == V111 ? 0x11B9A8 : (version_D2Client == V110 ? 0x112D04 : (version_D2Client == V109d ? 0x11CF54 : 0x11E0F4)))))))));
        ptInputCommand = (WCHAR *) (offset_D2Client + (version_D2Client == V114d ? 0x3BB638 : (version_D2Client == V113d ? 0x11D650 : (version_D2Client == V113c ? 0x11EC80 : (version_D2Client == V112 ? 0x11FC40 : (version_D2Client == V111b ? 0x11D590 : (version_D2Client == V111 ? 0x11C590 : (version_D2Client == V110 ? 0x111A58 : (version_D2Client == V109d ? 0x11BCB0 : 0x11CE50)))))))));
        ptNbStatDesc = (DWORD *) (offset_D2Client + (version_D2Client == V114d ? 0x000000 : (version_D2Client == V113d ? 0x000000 : (version_D2Client == V113c ? 0x000000 : (version_D2Client == V112 ? 0x000000 : (version_D2Client == V111b ? 0x000000 : (version_D2Client == V111 ? 0x000000 : (version_D2Client == V110 ? 0x000000 : (version_D2Client == V109d ? 0xDA828 : 0xDB918)))))))));
        ptStatDescTable = (DWORD *) (offset_D2Client + (version_D2Client == V114d ? 0x000000 : (version_D2Client == V113d ? 0x000000 : (version_D2Client == V113c ? 0x000000 : (version_D2Client == V112 ? 0x000000 : (version_D2Client == V111b ? 0x000000 : (version_D2Client == V111 ? 0x000000 : (version_D2Client == V110 ? 0x000000 : (version_D2Client == V109d ? 0xD9EA8 : 0xDAF98)))))))));
        SgptDataTables = *(DataTables **) (offset_D2Common + (version_D2Common == V114d ? 0x344304 : (version_D2Common == V113d ? 0xA33F0 : (version_D2Common == V113c ? 0x99E1C : (version_D2Common == V112 ? 0x9B500 : (version_D2Common == V111b ? 0x9EE8C : (version_D2Common == V111 ? 0x9B74C : (version_D2Common == V110 ? 0x96A20 : (version_D2Common == V109d ? 0x0000 : 0x0000)))))))));
        if (version_D2Common < V110) {
            setFctAddr((DWORD *) &D2Common10581, (HMODULE) offset_D2Common, (LPCSTR) 10581);//ONLY in 1.09
            setFctAddr((DWORD *) &D2Common10598, (HMODULE) offset_D2Common, (LPCSTR) 10598);//ONLY in 1.09
            setFctAddr((DWORD *) &D2Common10673, (HMODULE) offset_D2Common, (LPCSTR) 10673);//ONLY in 1.09
        }
        misc_fct();
        redirect_to_custom_functions();
        init_shifting();
        init_dll_maps();
    }
}
