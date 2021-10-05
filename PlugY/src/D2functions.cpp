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
            StatMouse1 = (DWORD *) (offset_D2Client + getAddressOfVersion(version_D2Client, 0x0000, 0x0000, 0x0000, 0x11C004, 0x11C2F4, 0x11C040, 0x11C3DC, 0x11D224, 0x3A0650));
            StatMouse2 = (DWORD *) (offset_D2Client + getAddressOfVersion(version_D2Client, 0x0000, 0x0000, 0x0000, 0x11C008, 0x11C2F8, 0x11C044, 0x11C3E0, 0x11D228, 0x3A0654));
            StatMouse3 = (DWORD *) (offset_D2Client + getAddressOfVersion(version_D2Client, 0x0000, 0x0000, 0x0000, 0x11C020, 0x11C310, 0x11C05C, 0x11C3F8, 0x11D240, 0x3A0658));
            StatMouse4 = (DWORD *) (offset_D2Client + getAddressOfVersion(version_D2Client, 0x0000, 0x0000, 0x0000, 0x11C024, 0x11C314, 0x11C060, 0x11C3FC, 0x11D244, 0x3A065C));
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



        if (version_D2Common > V113d) { D2Common11084 = (TD2Common11084) (offset_D2Common + getAddressOfVersion(version_D2Common, 0x00000, 0x00000, 0x00000, 0x10188, 0x11084, 0x11109, 0x10346, 0x10907, 0x21AED0)); } else setFctAddr((DWORD *) &D2Common11084, (HMODULE) offset_D2Common, (LPCSTR) getAddressOfVersion(version_D2Common, 00000, 00000, 00000, 10188, 11084, 11109, 10346, 10907));
        if (version_D2Common > V113d) { D2GetLevelID = (TD2GetLevelID) (offset_D2Common + getAddressOfVersion(version_D2Common, 0x10057, 0x10057, 0x10057, 0x10332, 0x11021, 0x10511, 0x10826, 0x10691, 0x21A1B0)); } else setFctAddr((DWORD *) &D2GetLevelID, (HMODULE) offset_D2Common, (LPCSTR) getAddressOfVersion(version_D2Common, 10057, 10057, 10057, 10332, 11021, 10511, 10826, 10691));
        if (version_D2Common > V113d) { D2GetDropRoom = (TD2GetDropRoom) (offset_D2Common + getAddressOfVersion(version_D2Common, 0x10138, 0x10138, 0x10138, 0x10623, 0x10491, 0x11043, 0x10654, 0x10716, 0x24E810)); } else setFctAddr((DWORD *) &D2GetDropRoom, (HMODULE) offset_D2Common, (LPCSTR) getAddressOfVersion(version_D2Common, 10138, 10138, 10138, 10623, 10491, 11043, 10654, 10716));
        if (version_D2Common > V113d) { D2Common10242 = (TD2Common10242) (offset_D2Common + getAddressOfVersion(version_D2Common, 0x10242, 0x10242, 0x10242, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000)); } else setFctAddr((DWORD *) &D2Common10242, (HMODULE) offset_D2Common, (LPCSTR) getAddressOfVersion(version_D2Common, 10242, 10242, 10242, 00000, 00000, 00000, 00000, 00000));
        if (version_D2Common > V113d) { D2CanPutItemInInv = (TD2CanPutItemInInv) (offset_D2Common + getAddressOfVersion(version_D2Common, 0x10246, 0x10246, 0x10246, 0x10855, 0x10813, 0x10289, 0x10133, 0x10402, 0x23B950)); } else setFctAddr((DWORD *) &D2CanPutItemInInv, (HMODULE) offset_D2Common, (LPCSTR) getAddressOfVersion(version_D2Common, 10246, 10246, 10246, 10855, 10813, 10289, 10133, 10402));
        if (version_D2Common > V113d) { D2InvRemoveItem = (TD2InvRemoveItem) (offset_D2Common + getAddressOfVersion(version_D2Common, 0x10243, 0x10243, 0x10243, 0x10461, 0x10827, 0x10936, 0x10646, 0x10490, 0x23AD90)); } else setFctAddr((DWORD *) &D2InvRemoveItem, (HMODULE) offset_D2Common, (LPCSTR) getAddressOfVersion(version_D2Common, 10243, 10243, 10243, 10461, 10827, 10936, 10646, 10490));
        if (version_D2Common > V113d) { D2InvAddItem = (TD2InvAddItem) (offset_D2Common + getAddressOfVersion(version_D2Common, 0x10249, 0x10249, 0x10249, 0x10880, 0x11068, 0x10436, 0x11107, 0x10963, 0x23BCC0)); } else setFctAddr((DWORD *) &D2InvAddItem, (HMODULE) offset_D2Common, (LPCSTR) getAddressOfVersion(version_D2Common, 10249, 10249, 10249, 10880, 11068, 10436, 11107, 10963));
        if (version_D2Common > V113d) { D2Common10250 = (TD2Common10250) (offset_D2Common + getAddressOfVersion(version_D2Common, 0x10250, 0x10250, 0x10250, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000)); } else setFctAddr((DWORD *) &D2Common10250, (HMODULE) offset_D2Common, (LPCSTR) getAddressOfVersion(version_D2Common, 10250, 10250, 10250, 00000, 00000, 00000, 00000, 00000));
        if (version_D2Common > V113d) { D2Common10273 = (TD2Common10273) (offset_D2Common + getAddressOfVersion(version_D2Common, 0x10273, 0x10273, 0x10273, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000)); } else setFctAddr((DWORD *) &D2Common10273, (HMODULE) offset_D2Common, (LPCSTR) getAddressOfVersion(version_D2Common, 10273, 10273, 10273, 00000, 00000, 00000, 00000, 00000));
        if (version_D2Common > V113d) { D2InventoryGetFirstItem = (TD2InventoryGetFirstItem) (offset_D2Common + getAddressOfVersion(version_D2Common, 0x10277, 0x10277, 0x10277, 0x10402, 0x10535, 0x11151, 0x10460, 0x11040, 0x23B2C0)); } else setFctAddr((DWORD *) &D2InventoryGetFirstItem, (HMODULE) offset_D2Common, (LPCSTR) getAddressOfVersion(version_D2Common, 10277, 10277, 10277, 10402, 10535, 11151, 10460, 11040));
        if (version_D2Common > V113d) { D2UnitGetNextItem = (TD2UnitGetNextItem) (offset_D2Common + getAddressOfVersion(version_D2Common, 0x10304, 0x10304, 0x10304, 0x10934, 0x11140, 0x10770, 0x10464, 0x10879, 0x23DFA0)); } else setFctAddr((DWORD *) &D2UnitGetNextItem, (HMODULE) offset_D2Common, (LPCSTR) getAddressOfVersion(version_D2Common, 10304, 10304, 10304, 10934, 11140, 10770, 10464, 10879));
        if (version_D2Common > V113d) { D2GetRealItem = (TD2GetRealItem) (offset_D2Common + getAddressOfVersion(version_D2Common, 0x10305, 0x10305, 0x10305, 0x11095, 0x10748, 0x10852, 0x11147, 0x10897, 0x23DFD0)); } else setFctAddr((DWORD *) &D2GetRealItem, (HMODULE) offset_D2Common, (LPCSTR) getAddressOfVersion(version_D2Common, 10305, 10305, 10305, 11095, 10748, 10852, 11147, 10897));
        if (version_D2Common > V113d) { D2GetPosX = (TD2GetPosX) (offset_D2Common + getAddressOfVersion(version_D2Common, 0x10326, 0x10326, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000)); } else setFctAddr((DWORD *) &D2GetPosX, (HMODULE) offset_D2Common, (LPCSTR) getAddressOfVersion(version_D2Common, 10326, 10326, 00000, 00000, 00000, 00000, 00000, 00000));
        if (version_D2Common > V113d) { D2GetPosY = (TD2GetPosY) (offset_D2Common + getAddressOfVersion(version_D2Common, 0x10329, 0x10329, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000)); } else setFctAddr((DWORD *) &D2GetPosY, (HMODULE) offset_D2Common, (LPCSTR) getAddressOfVersion(version_D2Common, 10329, 10329, 00000, 00000, 00000, 00000, 00000, 00000));
        if (version_D2Common > V113d) { D2GetPosition = (TD2GetPosition) (offset_D2Common + getAddressOfVersion(version_D2Common, 0x10332, 0x10332, 0x10332, 0x11080, 0x10056, 0x10543, 0x10141, 0x11166, 0x220870)); } else setFctAddr((DWORD *) &D2GetPosition, (HMODULE) offset_D2Common, (LPCSTR) getAddressOfVersion(version_D2Common, 10332, 10332, 10332, 11080, 10056, 10543, 10141, 11166));
        if (version_D2Common > V113d) { D2GetMaxGoldBank = (TD2GetMaxGoldBank) (offset_D2Common + getAddressOfVersion(version_D2Common, 0x10339, 0x10339, 0x10339, 0x10455, 0x10864, 0x10941, 0x11060, 0x11025, 0x223460)); } else setFctAddr((DWORD *) &D2GetMaxGoldBank, (HMODULE) offset_D2Common, (LPCSTR) getAddressOfVersion(version_D2Common, 10339, 10339, 10339, 10455, 10864, 10941, 11060, 11025));
        if (version_D2Common > V113d) { D2GetRoom = (TD2GetRoom) (offset_D2Common + getAddressOfVersion(version_D2Common, 0x10342, 0x10342, 0x10342, 0x10172, 0x10933, 0x10366, 0x10331, 0x10846, 0x220BB0)); } else setFctAddr((DWORD *) &D2GetRoom, (HMODULE) offset_D2Common, (LPCSTR) getAddressOfVersion(version_D2Common, 10342, 10342, 10342, 10172, 10933, 10366, 10331, 10846));
        if (version_D2Common > V113d) { D2InitPlayerData = (TD2InitPlayerData) (offset_D2Common + getAddressOfVersion(version_D2Common, 0x10420, 0x10420, 0x10420, 0x10218, 0x10079, 0x11097, 0x10356, 0x10404, 0x221F90)); } else setFctAddr((DWORD *) &D2InitPlayerData, (HMODULE) offset_D2Common, (LPCSTR) getAddressOfVersion(version_D2Common, 10420, 10420, 10420, 10218, 10079, 11097, 10356, 10404));
        if (version_D2Common > V113d) { D2GetPlayerData = (TD2GetPlayerData) (offset_D2Common + getAddressOfVersion(version_D2Common, 0x10424, 0x10424, 0x10424, 0x10562, 0x10800, 0x10860, 0x10920, 0x11103, 0x2221A0)); } else setFctAddr((DWORD *) &D2GetPlayerData, (HMODULE) offset_D2Common, (LPCSTR) getAddressOfVersion(version_D2Common, 10424, 10424, 10424, 10562, 10800, 10860, 10920, 11103));
        if (version_D2Common > V113d) { D2GetDefence = (TD2GetDefence) (offset_D2Common + getAddressOfVersion(version_D2Common, 0x10431, 0x10431, 0x10431, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000)); } else setFctAddr((DWORD *) &D2GetDefence, (HMODULE) offset_D2Common, (LPCSTR) getAddressOfVersion(version_D2Common, 10431, 10431, 10431, 00000, 00000, 00000, 00000, 00000));
        if (version_D2Common > V113d) { D2GetChanceToBlock = (TD2GetChanceToBlock) (offset_D2Common + getAddressOfVersion(version_D2Common, 0x10433, 0x10433, 0x10433, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000)); } else setFctAddr((DWORD *) &D2GetChanceToBlock, (HMODULE) offset_D2Common, (LPCSTR) getAddressOfVersion(version_D2Common, 10433, 10433, 10433, 00000, 00000, 00000, 00000, 00000));
        if (version_D2Common > V113d) { D2GetMaxGold = (TD2GetMaxGold) (offset_D2Common + getAddressOfVersion(version_D2Common, 0x10439, 0x10439, 0x10439, 0x10343, 0x11131, 0x10729, 0x10049, 0x11159, 0x222E70)); } else setFctAddr((DWORD *) &D2GetMaxGold, (HMODULE) offset_D2Common, (LPCSTR) getAddressOfVersion(version_D2Common, 10439, 10439, 10439, 10343, 11131, 10729, 10049, 11159));
        if (version_D2Common > V113d) { D2Common10572 = (TD2Common10572) (offset_D2Common + getAddressOfVersion(version_D2Common, 0x00000, 0x00000, 0x00000, 0x10440, 0x10572, 0x10481, 0x11090, 0x10193, 0x224690)); } else setFctAddr((DWORD *) &D2Common10572, (HMODULE) offset_D2Common, (LPCSTR) getAddressOfVersion(version_D2Common, 00000, 00000, 00000, 10440, 10572, 10481, 11090, 10193));
        if (version_D2Common > V113d) { D2GetObjectFlags = (TD2GetObjectFlags) (offset_D2Common + getAddressOfVersion(version_D2Common, 0x00000, 0x00000, 0x00000, 0x10471, 0x11160, 0x10866, 0x10258, 0x10040, 0x2222C0)); } else setFctAddr((DWORD *) &D2GetObjectFlags, (HMODULE) offset_D2Common, (LPCSTR) getAddressOfVersion(version_D2Common, 00000, 00000, 00000, 10471, 11160, 10866, 10258, 10040));
        if (version_D2Common > V113d) { D2SetObjectFlags = (TD2SetObjectFlags) (offset_D2Common + getAddressOfVersion(version_D2Common, 0x00000, 0x00000, 0x00000, 0x10572, 0x11048, 0x10150, 0x10111, 0x10033, 0x222300)); } else setFctAddr((DWORD *) &D2SetObjectFlags, (HMODULE) offset_D2Common, (LPCSTR) getAddressOfVersion(version_D2Common, 00000, 00000, 00000, 10572, 11048, 10150, 10111, 10033));
        if (version_D2Common > V113d) { D2isInState = (TD2isInState) (offset_D2Common + getAddressOfVersion(version_D2Common, 0x10487, 0x10487, 0x10487, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000)); } else setFctAddr((DWORD *) &D2isInState, (HMODULE) offset_D2Common, (LPCSTR) getAddressOfVersion(version_D2Common, 10487, 10487, 10487, 00000, 00000, 00000, 00000, 00000));
        if (version_D2Common > V113d) { D2AddPlayerStat = (TD2AddPlayerStat) (offset_D2Common + getAddressOfVersion(version_D2Common, 0x10518, 0x10518, 0x10518, 0x10109, 0x10627, 0x10762, 0x10551, 0x10645, 0x2272B0)); } else setFctAddr((DWORD *) &D2AddPlayerStat, (HMODULE) offset_D2Common, (LPCSTR) getAddressOfVersion(version_D2Common, 10518, 10518, 10518, 10109, 10627, 10762, 10551, 10645));
        if (version_D2Common > V113d) { D2GetPlayerStat = (TD2GetPlayerStat) (offset_D2Common + getAddressOfVersion(version_D2Common, 0x10519, 0x10519, 0x10519, 0x11092, 0x10061, 0x10658, 0x10973, 0x10550, 0x225480)); } else setFctAddr((DWORD *) &D2GetPlayerStat, (HMODULE) offset_D2Common, (LPCSTR) getAddressOfVersion(version_D2Common, 10519, 10519, 10519, 11092, 10061, 10658, 10973, 10550));
        if (version_D2Common > V113d) { D2GetPlayerBaseStat = (TD2GetPlayerBaseStat) (offset_D2Common + getAddressOfVersion(version_D2Common, 0x10521, 0x10521, 0x10521, 0x10733, 0x10550, 0x10494, 0x10587, 0x10216, 0x2253B0)); } else setFctAddr((DWORD *) &D2GetPlayerBaseStat, (HMODULE) offset_D2Common, (LPCSTR) getAddressOfVersion(version_D2Common, 10521, 10521, 10521, 10733, 10550, 10494, 10587, 10216));
        if (version_D2Common > V113d) { D2haveDefenceBonus = (TD2haveDefenceBonus) (offset_D2Common + getAddressOfVersion(version_D2Common, 0x10539, 0x10539, 0x10539, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000)); } else setFctAddr((DWORD *) &D2haveDefenceBonus, (HMODULE) offset_D2Common, (LPCSTR) getAddressOfVersion(version_D2Common, 10539, 10539, 10539, 00000, 00000, 00000, 00000, 00000));
        if (version_D2Common > V113d) { D2haveFireResBonus = (TD2haveFireResBonus) (offset_D2Common + getAddressOfVersion(version_D2Common, 0x10540, 0x10540, 0x10540, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000)); } else setFctAddr((DWORD *) &D2haveFireResBonus, (HMODULE) offset_D2Common, (LPCSTR) getAddressOfVersion(version_D2Common, 10540, 10540, 10540, 00000, 00000, 00000, 00000, 00000));
        if (version_D2Common > V113d) { D2haveColdResBonus = (TD2haveColdResBonus) (offset_D2Common + getAddressOfVersion(version_D2Common, 0x10541, 0x10541, 0x10541, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000)); } else setFctAddr((DWORD *) &D2haveColdResBonus, (HMODULE) offset_D2Common, (LPCSTR) getAddressOfVersion(version_D2Common, 10541, 10541, 10541, 00000, 00000, 00000, 00000, 00000));
        if (version_D2Common > V113d) { D2haveLightResBonus = (TD2haveLightResBonus) (offset_D2Common + getAddressOfVersion(version_D2Common, 0x10542, 0x10542, 0x10542, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000)); } else setFctAddr((DWORD *) &D2haveLightResBonus, (HMODULE) offset_D2Common, (LPCSTR) getAddressOfVersion(version_D2Common, 10542, 10542, 10542, 00000, 00000, 00000, 00000, 00000));
        if (version_D2Common > V113d) { D2havePoisonResBonus = (TD2havePoisonResBonus) (offset_D2Common + getAddressOfVersion(version_D2Common, 0x10543, 0x10543, 0x10543, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000)); } else setFctAddr((DWORD *) &D2havePoisonResBonus, (HMODULE) offset_D2Common, (LPCSTR) getAddressOfVersion(version_D2Common, 10543, 10543, 10543, 00000, 00000, 00000, 00000, 00000));
        if (version_D2Common > V113d) { D2haveDefenceMalus = (TD2haveDefenceMalus) (offset_D2Common + getAddressOfVersion(version_D2Common, 0x10546, 0x10546, 0x10546, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000)); } else setFctAddr((DWORD *) &D2haveDefenceMalus, (HMODULE) offset_D2Common, (LPCSTR) getAddressOfVersion(version_D2Common, 10546, 10546, 10546, 00000, 00000, 00000, 00000, 00000));
        if (version_D2Common > V113d) { D2haveFireResMalus = (TD2haveFireResMalus) (offset_D2Common + getAddressOfVersion(version_D2Common, 0x10547, 0x10547, 0x10547, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000)); } else setFctAddr((DWORD *) &D2haveFireResMalus, (HMODULE) offset_D2Common, (LPCSTR) getAddressOfVersion(version_D2Common, 10547, 10547, 10547, 00000, 00000, 00000, 00000, 00000));
        if (version_D2Common > V113d) { D2haveColdResMalus = (TD2haveColdResMalus) (offset_D2Common + getAddressOfVersion(version_D2Common, 0x10548, 0x10548, 0x10548, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000)); } else setFctAddr((DWORD *) &D2haveColdResMalus, (HMODULE) offset_D2Common, (LPCSTR) getAddressOfVersion(version_D2Common, 10548, 10548, 10548, 00000, 00000, 00000, 00000, 00000));
        if (version_D2Common > V113d) { D2haveLightResMalus = (TD2haveLightResMalus) (offset_D2Common + getAddressOfVersion(version_D2Common, 0x10549, 0x10549, 0x10549, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000)); } else setFctAddr((DWORD *) &D2haveLightResMalus, (HMODULE) offset_D2Common, (LPCSTR) getAddressOfVersion(version_D2Common, 10549, 10549, 10549, 00000, 00000, 00000, 00000, 00000));
        if (version_D2Common > V113d) { D2havePoisonResMalus = (TD2havePoisonResMalus) (offset_D2Common + getAddressOfVersion(version_D2Common, 0x10550, 0x10550, 0x10550, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000)); } else setFctAddr((DWORD *) &D2havePoisonResMalus, (HMODULE) offset_D2Common, (LPCSTR) getAddressOfVersion(version_D2Common, 10550, 10550, 10550, 00000, 00000, 00000, 00000, 00000));
        if (version_D2Common > V113d) { D2CompileTxtFile = (TD2CompileTxtFile) (offset_D2Common + getAddressOfVersion(version_D2Common, 0x10578, 0x10578, 0x10578, 0x10653, 0x10496, 0x10244, 0x10849, 0x10037, 0x2122F0)); } else setFctAddr((DWORD *) &D2CompileTxtFile, (HMODULE) offset_D2Common, (LPCSTR) getAddressOfVersion(version_D2Common, 10578, 10578, 10578, 10653, 10496, 10244, 10849, 10037));
        if (version_D2Common > V113d) { D2GetItemsBIN = (TD2GetItemsBIN) (offset_D2Common + getAddressOfVersion(version_D2Common, 0x10600, 0x10600, 0x10600, 0x10573, 0x10262, 0x10887, 0x10695, 0x10994, 0x2335F0)); } else setFctAddr((DWORD *) &D2GetItemsBIN, (HMODULE) offset_D2Common, (LPCSTR) getAddressOfVersion(version_D2Common, 10600, 10600, 10600, 10573, 10262, 10887, 10695, 10994));
        if (version_D2Common > V113d) { D2GetGemsBIN = (TD2GetGemsBIN) (offset_D2Common + getAddressOfVersion(version_D2Common, 0x10616, 0x10616, 0x10616, 0x10500, 0x10523, 0x10774, 0x10806, 0x10619, 0x2372C0)); } else setFctAddr((DWORD *) &D2GetGemsBIN, (HMODULE) offset_D2Common, (LPCSTR) getAddressOfVersion(version_D2Common, 10616, 10616, 10616, 10500, 10523, 10774, 10806, 10619));
        if (version_D2Common > V113d) { D2GetCubeMainBIN = (TD2GetCubeMainBIN) (offset_D2Common + getAddressOfVersion(version_D2Common, 0x11232, 0x11232, 0x11232, 0x10746, 0x10258, 0x10913, 0x10783, 0x10393, 0x26A1B0)); } else setFctAddr((DWORD *) &D2GetCubeMainBIN, (HMODULE) offset_D2Common, (LPCSTR) getAddressOfVersion(version_D2Common, 11232, 11232, 11232, 10746, 10258, 10913, 10783, 10393));
        if (version_D2Common > V113d) { D2GetNbCubeMainBIN = (TD2GetNbCubeMainBIN) (offset_D2Common + getAddressOfVersion(version_D2Common, 0x11233, 0x11233, 0x11233, 0x10639, 0x11135, 0x10390, 0x10675, 0x10235, 0x26A200)); } else setFctAddr((DWORD *) &D2GetNbCubeMainBIN, (HMODULE) offset_D2Common, (LPCSTR) getAddressOfVersion(version_D2Common, 11233, 11233, 11233, 10639, 11135, 10390, 10675, 10235));
        if (version_D2Common > V113d) { D2GetNextLevelXP = (TD2GetNextLevelXP) (offset_D2Common + getAddressOfVersion(version_D2Common, 0x10628, 0x10628, 0x10628, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000)); } else setFctAddr((DWORD *) &D2GetNextLevelXP, (HMODULE) offset_D2Common, (LPCSTR) getAddressOfVersion(version_D2Common, 10628, 10628, 10628, 00000, 00000, 00000, 00000, 00000));
        if (version_D2Common > V113d) { D2GetMaxLevel = (TD2GetMaxLevel) (offset_D2Common + getAddressOfVersion(version_D2Common, 0x10629, 0x10629, 0x10629, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000)); } else setFctAddr((DWORD *) &D2GetMaxLevel, (HMODULE) offset_D2Common, (LPCSTR) getAddressOfVersion(version_D2Common, 10629, 10629, 10629, 00000, 00000, 00000, 00000, 00000));
        if (version_D2Common > V113d) { D2GetDifficultyLevelsBIN = (TD2GetDifficultyLevelsBIN) (offset_D2Common + getAddressOfVersion(version_D2Common, 0x10655, 0x10655, 0x10655, 0x10655, 0x10309, 0x10297, 0x10218, 0x10694, 0x111D30)); } else setFctAddr((DWORD *) &D2GetDifficultyLevelsBIN, (HMODULE) offset_D2Common, (LPCSTR) getAddressOfVersion(version_D2Common, 10655, 10655, 10655, 10655, 10309, 10297, 10218, 10694));
        if (version_D2Common > V113d) { D2GetItemQuality = (TD2GetItemQuality) (offset_D2Common + getAddressOfVersion(version_D2Common, 0x10695, 0x10695, 0x10695, 0x10927, 0x10899, 0x10276, 0x10106, 0x10911, 0x227E70)); } else setFctAddr((DWORD *) &D2GetItemQuality, (HMODULE) offset_D2Common, (LPCSTR) getAddressOfVersion(version_D2Common, 10695, 10695, 10695, 10927, 10899, 10276, 10106, 10911));
        if (version_D2Common > V113d) { D2TestFlags = (TD2TestFlags) (offset_D2Common + getAddressOfVersion(version_D2Common, 0x10707, 0x10707, 0x10707, 0x10911, 0x10303, 0x10989, 0x10202, 0x10458, 0x2280A0)); } else setFctAddr((DWORD *) &D2TestFlags, (HMODULE) offset_D2Common, (LPCSTR) getAddressOfVersion(version_D2Common, 10707, 10707, 10707, 10911, 10303, 10989, 10202, 10458));
        if (version_D2Common > V113d) { D2GetItemLevel = (TD2GetItemLevel) (offset_D2Common + getAddressOfVersion(version_D2Common, 0x10717, 0x10717, 0x10717, 0x10898, 0x10100, 0x10410, 0x10086, 0x10008, 0x2281E0)); } else setFctAddr((DWORD *) &D2GetItemLevel, (HMODULE) offset_D2Common, (LPCSTR) getAddressOfVersion(version_D2Common, 10717, 10717, 10717, 10898, 10100, 10410, 10086, 10008));
        if (version_D2Common > V113d) { D2ItemGetPage = (TD2ItemGetPage) (offset_D2Common + getAddressOfVersion(version_D2Common, 0x10719, 0x10719, 0x10719, 0x10820, 0x10505, 0x10370, 0x10020, 0x10810, 0x228250)); } else setFctAddr((DWORD *) &D2ItemGetPage, (HMODULE) offset_D2Common, (LPCSTR) getAddressOfVersion(version_D2Common, 10719, 10719, 10719, 10820, 10505, 10370, 10020, 10810));
        if (version_D2Common > V113d) { D2ItemSetPage = (TD2ItemSetPage) (offset_D2Common + getAddressOfVersion(version_D2Common, 0x10720, 0x10720, 0x10720, 0x10485, 0x10608, 0x10223, 0x10012, 0x11026, 0x228280)); } else setFctAddr((DWORD *) &D2ItemSetPage, (HMODULE) offset_D2Common, (LPCSTR) getAddressOfVersion(version_D2Common, 10720, 10720, 10720, 10485, 10608, 10223, 10012, 11026));
        if (version_D2Common > V113d) { D2CheckItemType = (TD2CheckItemType) (offset_D2Common + getAddressOfVersion(version_D2Common, 0x10731, 0x10731, 0x10731, 0x11017, 0x10890, 0x10231, 0x10744, 0x10601, 0x229BB0)); } else setFctAddr((DWORD *) &D2CheckItemType, (HMODULE) offset_D2Common, (LPCSTR) getAddressOfVersion(version_D2Common, 10731, 10731, 10731, 11017, 10890, 10231, 10744, 10601));
        if (version_D2Common > V113d) { D2GetUniqueID = (TD2GetUniqueID) (offset_D2Common + getAddressOfVersion(version_D2Common, 0x10732, 0x10732, 0x10732, 0x10692, 0x10685, 0x10280, 0x10620, 0x10075, 0x229DA0)); } else setFctAddr((DWORD *) &D2GetUniqueID, (HMODULE) offset_D2Common, (LPCSTR) getAddressOfVersion(version_D2Common, 10732, 10732, 10732, 10692, 10685, 10280, 10620, 10075));
        if (version_D2Common > V113d) { D2SetAnim = (TD2SetAnim) (offset_D2Common + getAddressOfVersion(version_D2Common, 0x10734, 0x10734, 0x10734, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000)); } else setFctAddr((DWORD *) &D2SetAnim, (HMODULE) offset_D2Common, (LPCSTR) getAddressOfVersion(version_D2Common, 10734, 10734, 10734, 00000, 00000, 00000, 00000, 00000));
        if (version_D2Common > V113d) { D2GetNbRunesBIN = (TD2GetNbRunesBIN) (offset_D2Common + getAddressOfVersion(version_D2Common, 0x10619, 0x10619, 0x10619, 0x10687, 0x10877, 0x10321, 0x11032, 0x10981, 0x239CB0)); } else setFctAddr((DWORD *) &D2GetNbRunesBIN, (HMODULE) offset_D2Common, (LPCSTR) getAddressOfVersion(version_D2Common, 10619, 10619, 10619, 10687, 10877, 10321, 11032, 10981));
        if (version_D2Common > V113d) { D2GetRunesBIN = (TD2GetRunesBIN) (offset_D2Common + getAddressOfVersion(version_D2Common, 0x10620, 0x10620, 0x10620, 0x10775, 0x10296, 0x10622, 0x10006, 0x10405, 0x239D60)); } else setFctAddr((DWORD *) &D2GetRunesBIN, (HMODULE) offset_D2Common, (LPCSTR) getAddressOfVersion(version_D2Common, 10620, 10620, 10620, 10775, 10296, 10622, 10006, 10405));
        if (version_D2Common > V113d) { D2SaveItem = (TD2SaveItem) (offset_D2Common + getAddressOfVersion(version_D2Common, 0x10881, 0x10881, 0x10881, 0x10956, 0x11156, 0x10218, 0x10987, 0x10665, 0x2313E0)); } else setFctAddr((DWORD *) &D2SaveItem, (HMODULE) offset_D2Common, (LPCSTR) getAddressOfVersion(version_D2Common, 10881, 10881, 10881, 10956, 11156, 10218, 10987, 10665));
        if (version_D2Common > V113d) { D2SetSkillBaseLevel = (TD2SetSkillBaseLevel) (offset_D2Common + getAddressOfVersion(version_D2Common, 0x10953, 0x10953, 0x10953, 0x10099, 0x10255, 0x10210, 0x10302, 0x10335, 0x247280)); } else setFctAddr((DWORD *) &D2SetSkillBaseLevel, (HMODULE) offset_D2Common, (LPCSTR) getAddressOfVersion(version_D2Common, 10953, 10953, 10953, 10099, 10255, 10210, 10302, 10335));
        if (version_D2Common > V113d) { D2GetSkillLevel = (TD2GetSkillLevel) (offset_D2Common + getAddressOfVersion(version_D2Common, 0x10968, 0x10968, 0x10968, 0x10700, 0x10109, 0x10904, 0x10306, 0x10007, 0x2442A0)); } else setFctAddr((DWORD *) &D2GetSkillLevel, (HMODULE) offset_D2Common, (LPCSTR) getAddressOfVersion(version_D2Common, 10968, 10968, 10968, 10700, 10109, 10904, 10306, 10007));
        if (version_D2Common > V113d) { D2GetSkillCost = (TD2GetSkillCost) (offset_D2Common + getAddressOfVersion(version_D2Common, 0x11276, 0x11276, 0x11276, 0x10254, 0x10074, 0x10111, 0x10435, 0x11081, 0x246CA0)); } else setFctAddr((DWORD *) &D2GetSkillCost, (HMODULE) offset_D2Common, (LPCSTR) getAddressOfVersion(version_D2Common, 11276, 11276, 11276, 10254, 10074, 10111, 10435, 11081));
        if (version_D2Game > V113d) { D2SetNbPlayers = (TD2SetNbPlayers) (offset_D2Game + getAddressOfVersion(version_D2Game, 0x10059, 0x10059, 0x10059, 0x10039, 0x10007, 0x10037, 0x10049, 0x10002, 0x135780)); } else setFctAddr((DWORD *) &D2SetNbPlayers, (HMODULE) offset_D2Game, (LPCSTR) getAddressOfVersion(version_D2Game, 10059, 10059, 10059, 10039, 10007, 10037, 10049, 10002));
        if (version_D2Net > V113d) { D2SendToServer = (TD2SendToServer) (offset_D2Net + getAddressOfVersion(version_D2Net, 0x10005, 0x10005, 0x10005, 0x10035, 0x10020, 0x10036, 0x10024, 0x10015, 0x12AE50)); } else setFctAddr((DWORD *) &D2SendToServer, (HMODULE) offset_D2Net, (LPCSTR) getAddressOfVersion(version_D2Net, 10005, 10005, 10005, 10035, 10020, 10036, 10024, 10015));
        if (version_D2Net > V113d) { D2SendToClient = (TD2SendToClient) (offset_D2Net + getAddressOfVersion(version_D2Net, 0x10006, 0x10006, 0x10006, 0x10018, 0x10018, 0x10015, 0x10002, 0x10012, 0x12B330)); } else setFctAddr((DWORD *) &D2SendToClient, (HMODULE) offset_D2Net, (LPCSTR) getAddressOfVersion(version_D2Net, 10006, 10006, 10006, 10018, 10018, 10015, 10002, 10012));
        if (version_Fog > V113d) { D2FogAssertOld = (TD2FogAssertOld) (offset_Fog + getAddressOfVersion(version_Fog, 0x10023, 0x10023, 0x10023, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000)); } else setFctAddr((DWORD *) &D2FogAssertOld, (HMODULE) offset_Fog, (LPCSTR) getAddressOfVersion(version_Fog, 10023, 10023, 10023, 00000, 00000, 00000, 00000, 00000));
        if (version_Fog > V113d) { D2FogAssert = (TD2FogAssert) (offset_Fog + getAddressOfVersion(version_Fog, 0x00000, 0x00000, 0x00000, 0x10024, 0x10024, 0x10024, 0x10024, 0x10024, 0x8A60)); } else setFctAddr((DWORD *) &D2FogAssert, (HMODULE) offset_Fog, (LPCSTR) getAddressOfVersion(version_Fog, 00000, 00000, 00000, 10024, 10024, 10024, 10024, 10024));
        if (version_Fog > V113d) { D2FogMemAlloc = (TD2FogMemAlloc) (offset_Fog + getAddressOfVersion(version_Fog, 0x10042, 0x10042, 0x10042, 0x10042, 0x10042, 0x10042, 0x10042, 0x10042, 0xB380)); } else setFctAddr((DWORD *) &D2FogMemAlloc, (HMODULE) offset_Fog, (LPCSTR) getAddressOfVersion(version_Fog, 10042, 10042, 10042, 10042, 10042, 10042, 10042, 10042));
        if (version_Fog > V113d) { D2FogMemDeAlloc = (TD2FogMemDeAlloc) (offset_Fog + getAddressOfVersion(version_Fog, 0x10043, 0x10043, 0x10043, 0x10043, 0x10043, 0x10043, 0x10043, 0x10043, 0xB3C0)); } else setFctAddr((DWORD *) &D2FogMemDeAlloc, (HMODULE) offset_Fog, (LPCSTR) getAddressOfVersion(version_Fog, 10043, 10043, 10043, 10043, 10043, 10043, 10043, 10043));
        if (version_Fog > V113d) { D2AllocMem = (TD2AllocMem) (offset_Fog + getAddressOfVersion(version_Fog, 0x10045, 0x10045, 0x10045, 0x10045, 0x10045, 0x10045, 0x10045, 0x10045, 0xB430)); } else setFctAddr((DWORD *) &D2AllocMem, (HMODULE) offset_Fog, (LPCSTR) getAddressOfVersion(version_Fog, 10045, 10045, 10045, 10045, 10045, 10045, 10045, 10045));
        if (version_Fog > V113d) { D2FreeMem = (TD2FreeMem) (offset_Fog + getAddressOfVersion(version_Fog, 0x10046, 0x10046, 0x10046, 0x10046, 0x10046, 0x10046, 0x10046, 0x10046, 0xB480)); } else setFctAddr((DWORD *) &D2FreeMem, (HMODULE) offset_Fog, (LPCSTR) getAddressOfVersion(version_Fog, 10046, 10046, 10046, 10046, 10046, 10046, 10046, 10046));
        if (version_Fog > V113d) { D2MPQOpenFile = (TD2MPQOpenFile) (offset_Fog + getAddressOfVersion(version_Fog, 0x10102, 0x10102, 0x10102, 0x10102, 0x10102, 0x10102, 0x10102, 0x10102, 0x68E0)); } else setFctAddr((DWORD *) &D2MPQOpenFile, (HMODULE) offset_Fog, (LPCSTR) getAddressOfVersion(version_Fog, 10102, 10102, 10102, 10102, 10102, 10102, 10102, 10102));
        if (version_Fog > V113d) { D2MPQCloseFile = (TD2MPQCloseFile) (offset_Fog + getAddressOfVersion(version_Fog, 0x10103, 0x10103, 0x10103, 0x10103, 0x10103, 0x10103, 0x10103, 0x10103, 0x68F0)); } else setFctAddr((DWORD *) &D2MPQCloseFile, (HMODULE) offset_Fog, (LPCSTR) getAddressOfVersion(version_Fog, 10103, 10103, 10103, 10103, 10103, 10103, 10103, 10103));
        if (version_Fog > V113d) { D2MPQReadFile = (TD2MPQReadFile) (offset_Fog + getAddressOfVersion(version_Fog, 0x10104, 0x10104, 0x10104, 0x10104, 0x10104, 0x10104, 0x10104, 0x10104, 0x6900)); } else setFctAddr((DWORD *) &D2MPQReadFile, (HMODULE) offset_Fog, (LPCSTR) getAddressOfVersion(version_Fog, 10104, 10104, 10104, 10104, 10104, 10104, 10104, 10104));
        if (version_Fog > V113d) { D2MPQGetSizeFile = (TD2MPQGetSizeFile) (offset_Fog + getAddressOfVersion(version_Fog, 0x10105, 0x10105, 0x10105, 0x10105, 0x10105, 0x10105, 0x10105, 0x10105, 0x6930)); } else setFctAddr((DWORD *) &D2MPQGetSizeFile, (HMODULE) offset_Fog, (LPCSTR) getAddressOfVersion(version_Fog, 10105, 10105, 10105, 10105, 10105, 10105, 10105, 10105));
        if (version_Fog > V113d) { D2FogGetSavePath = (TD2FogGetSavePath) (offset_Fog + getAddressOfVersion(version_Fog, 0x10115, 0x10115, 0x10115, 0x10115, 0x10115, 0x10115, 0x10115, 0x10115, 0x7050)); } else setFctAddr((DWORD *) &D2FogGetSavePath, (HMODULE) offset_Fog, (LPCSTR) getAddressOfVersion(version_Fog, 10115, 10115, 10115, 10115, 10115, 10115, 10115, 10115));
        if (version_Fog > V113d) { D2FogGetInstallPath = (TD2FogGetInstallPath) (offset_Fog + getAddressOfVersion(version_Fog, 0x10116, 0x10116, 0x10116, 0x10116, 0x10116, 0x10116, 0x10116, 0x10116, 0x6BA0)); } else setFctAddr((DWORD *) &D2FogGetInstallPath, (HMODULE) offset_Fog, (LPCSTR) getAddressOfVersion(version_Fog, 10116, 10116, 10116, 10116, 10116, 10116, 10116, 10116));
        if (version_Fog > V113d) { D2Fog10212 = (TD2Fog10212) (offset_Fog + getAddressOfVersion(version_Fog, 0x10212, 0x10212, 0x10212, 0x10212, 0x10212, 0x10212, 0x10212, 0x10212, 0x2BD0B0)); } else setFctAddr((DWORD *) &D2Fog10212, (HMODULE) offset_Fog, (LPCSTR) getAddressOfVersion(version_Fog, 10212, 10212, 10212, 10212, 10212, 10212, 10212, 10212));
        if (version_Fog > V113d) { D2GetInstructionPointer = (TD2GetInstructionPointer) (offset_Fog + getAddressOfVersion(version_Fog, 0x00000, 0x00000, 0x00000, 0x10265, 0x10265, 0x10265, 0x10265, 0x10265, 0x8090)); } else setFctAddr((DWORD *) &D2GetInstructionPointer, (HMODULE) offset_Fog, (LPCSTR) getAddressOfVersion(version_Fog, 00000, 00000, 00000, 10265, 10265, 10265, 10265, 10265));
        if (version_D2Lang > V113d) { D2GetStringFromString = (TD2GetStringFromString) (offset_D2Lang + getAddressOfVersion(version_D2Lang, 0x10003, 0x10003, 0x10003, 0x10002, 0x10004, 0x10010, 0x10011, 0x10011, 0x124E20)); } else setFctAddr((DWORD *) &D2GetStringFromString, (HMODULE) offset_D2Lang, (LPCSTR) getAddressOfVersion(version_D2Lang, 10003, 10003, 10003, 10002, 10004, 10010, 10011, 10011));
        if (version_D2Lang > V113d) { D2GetStringFromIndex = (TD2GetStringFromIndex) (offset_D2Lang + getAddressOfVersion(version_D2Lang, 0x10004, 0x10004, 0x10004, 0x10005, 0x10000, 0x10005, 0x10003, 0x10004, 0x124A30)); } else setFctAddr((DWORD *) &D2GetStringFromIndex, (HMODULE) offset_D2Lang, (LPCSTR) getAddressOfVersion(version_D2Lang, 10004, 10004, 10004, 10005, 10000, 10005, 10003, 10004));
        if (version_D2Lang > V113d) { D2GetLang = (TD2GetLang) (offset_D2Lang + getAddressOfVersion(version_D2Lang, 0x10007, 0x10007, 0x10007, 0x10009, 0x10013, 0x10002, 0x10009, 0x10001, 0x125150)); } else setFctAddr((DWORD *) &D2GetLang, (HMODULE) offset_D2Lang, (LPCSTR) getAddressOfVersion(version_D2Lang, 10007, 10007, 10007, 10009, 10013, 10002, 10009, 10001));
        if (version_D2Lang > V113d) { D2PrintBigNumber = (TD2PrintBigNumber) (offset_D2Lang + getAddressOfVersion(version_D2Lang, 0x10010, 0x10010, 0x10010, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000)); } else setFctAddr((DWORD *) &D2PrintBigNumber, (HMODULE) offset_D2Lang, (LPCSTR) getAddressOfVersion(version_D2Lang, 10010, 10010, 10010, 00000, 00000, 00000, 00000, 00000));
        if (version_Storm > V113d) { D2StormMPQOpenFile = (TD2StormMPQOpenFile) (offset_Storm + getAddressOfVersion(version_Storm, 0x268, 0x268, 0x268, 0x268, 0x268, 0x268, 0x268, 0x268, 0x192F0)); } else setFctAddr((DWORD *) &D2StormMPQOpenFile, (HMODULE) offset_Storm, (LPCSTR) getAddressOfVersion(version_Storm, 268, 268, 268, 268, 268, 268, 268, 268));
        if (version_Storm > V113d) { D2Storm503 = (TD2Storm503) (offset_Storm + getAddressOfVersion(version_Storm, 0x503, 0x503, 0x503, 0x503, 0x503, 0x503, 0x503, 0x503, 0x13750)); } else setFctAddr((DWORD *) &D2Storm503, (HMODULE) offset_Storm, (LPCSTR) getAddressOfVersion(version_Storm, 503, 503, 503, 503, 503, 503, 503, 503));
        if (version_Storm > V113d) { D2FreeWinMessage = (TD2FreeWinMessage) (offset_Storm + getAddressOfVersion(version_Storm, 0x511, 0x511, 0x511, 0x511, 0x511, 0x511, 0x511, 0x511, 0x20290)); } else setFctAddr((DWORD *) &D2FreeWinMessage, (HMODULE) offset_Storm, (LPCSTR) getAddressOfVersion(version_Storm, 511, 511, 511, 511, 511, 511, 511, 511));
        if (version_D2gfx > V113d) { D2GetResolution = (TD2GetResolution) (offset_D2gfx + getAddressOfVersion(version_D2gfx, 0x10005, 0x10005, 0x10005, 0x10000, 0x10063, 0x10043, 0x10031, 0x10012, 0xF5160)); } else setFctAddr((DWORD *) &D2GetResolution, (HMODULE) offset_D2gfx, (LPCSTR) getAddressOfVersion(version_D2gfx, 10005, 10005, 10005, 10000, 10063, 10043, 10031, 10012));
        if (version_D2gfx > V113d) { D2FillArea = (TD2FillArea) (offset_D2gfx + getAddressOfVersion(version_D2gfx, 0x10055, 0x10055, 0x10055, 0x10028, 0x10000, 0x10062, 0x10014, 0x10028, 0xF6300)); } else setFctAddr((DWORD *) &D2FillArea, (HMODULE) offset_D2gfx, (LPCSTR) getAddressOfVersion(version_D2gfx, 10055, 10055, 10055, 10028, 10000, 10062, 10014, 10028));
        if (version_D2gfx > V113d) { D2PrintImage = (TD2PrintImage) (offset_D2gfx + getAddressOfVersion(version_D2gfx, 0x10072, 0x10072, 0x10072, 0x10047, 0x10044, 0x10024, 0x10041, 0x10042, 0xF6480)); } else setFctAddr((DWORD *) &D2PrintImage, (HMODULE) offset_D2gfx, (LPCSTR) getAddressOfVersion(version_D2gfx, 10072, 10072, 10072, 10047, 10044, 10024, 10041, 10042));
        if (version_D2Win > V113d) { D2PrintLineOnTextBox = (TD2PrintLineOnTextBox) (offset_D2Win + getAddressOfVersion(version_D2Win, 0x10046, 0x10046, 0x10046, 0x10061, 0x10075, 0x10015, 0x10022, 0x10051, 0xFCFF0)); } else setFctAddr((DWORD *) &D2PrintLineOnTextBox, (HMODULE) offset_D2Win, (LPCSTR) getAddressOfVersion(version_D2Win, 10046, 10046, 10046, 10061, 10075, 10015, 10022, 10051));
        if (version_D2Win > V113d) { D2PrintString = (TD2PrintString) (offset_D2Win + getAddressOfVersion(version_D2Win, 0x10117, 0x10117, 0x10117, 0x10020, 0x10064, 0x10001, 0x10150, 0x10076, 0x102320)); } else setFctAddr((DWORD *) &D2PrintString, (HMODULE) offset_D2Win, (LPCSTR) getAddressOfVersion(version_D2Win, 10117, 10117, 10117, 10020, 10064, 10001, 10150, 10076));
        if (version_D2Win > V113d) { D2GetPixelLen = (TD2GetPixelLen) (offset_D2Win + getAddressOfVersion(version_D2Win, 0x10121, 0x10121, 0x10121, 0x10034, 0x10128, 0x10132, 0x10028, 0x10150, 0x101820)); } else setFctAddr((DWORD *) &D2GetPixelLen, (HMODULE) offset_D2Win, (LPCSTR) getAddressOfVersion(version_D2Win, 10121, 10121, 10121, 10034, 10128, 10132, 10028, 10150));
        if (version_D2Win > V113d) { D2SetFont = (TD2SetFont) (offset_D2Win + getAddressOfVersion(version_D2Win, 0x10127, 0x10127, 0x10127, 0x10141, 0x10170, 0x10010, 0x10184, 0x10047, 0x102EF0)); } else setFctAddr((DWORD *) &D2SetFont, (HMODULE) offset_D2Win, (LPCSTR) getAddressOfVersion(version_D2Win, 10127, 10127, 10127, 10141, 10170, 10010, 10184, 10047));
        if (version_D2Win > V113d) { D2PrintPopup = (TD2PrintPopup) (offset_D2Win + getAddressOfVersion(version_D2Win, 0x10129, 0x10129, 0x10129, 0x10118, 0x10039, 0x10031, 0x10085, 0x10137, 0x102280)); } else setFctAddr((DWORD *) &D2PrintPopup, (HMODULE) offset_D2Win, (LPCSTR) getAddressOfVersion(version_D2Win, 10129, 10129, 10129, 10118, 10039, 10031, 10085, 10137));
        if (version_D2Win > V113d) { D2GetPixelRect = (TD2GetPixelRect) (offset_D2Win + getAddressOfVersion(version_D2Win, 0x10131, 0x10131, 0x10131, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000)); } else setFctAddr((DWORD *) &D2GetPixelRect, (HMODULE) offset_D2Win, (LPCSTR) getAddressOfVersion(version_D2Win, 10131, 10131, 10131, 00000, 00000, 00000, 00000, 00000));
        if (version_D2Win > V113d) { D2PrintTextPopup = (TD2PrintTextPopup) (offset_D2Win + getAddressOfVersion(version_D2Win, 0x10132, 0x10132, 0x10132, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000)); } else setFctAddr((DWORD *) &D2PrintTextPopup, (HMODULE) offset_D2Win, (LPCSTR) getAddressOfVersion(version_D2Win, 10132, 10132, 10132, 00000, 00000, 00000, 00000, 00000));
        if (version_D2Win > V113d) { D2CreateTextBox = (TD2CreateTextBox) (offset_D2Win + getAddressOfVersion(version_D2Win, 0x10017, 0x10017, 0x10017, 0x10147, 0x10113, 0x10098, 0x10098, 0x10164, 0xF93C0)); } else setFctAddr((DWORD *) &D2CreateTextBox, (HMODULE) offset_D2Win, (LPCSTR) getAddressOfVersion(version_D2Win, 10017, 10017, 10017, 10147, 10113, 10098, 10098, 10164));
        if (version_D2CMP > V113d) { D2CMP10014 = (TD2CMP10014) (offset_D2CMP + getAddressOfVersion(version_D2CMP, 0x10032, 0x10032, 0x10032, 0x10021, 0x10014, 0x10106, 0x10065, 0x10020, 0x201A50)); } else setFctAddr((DWORD *) &D2CMP10014, (HMODULE) offset_D2CMP, (LPCSTR) getAddressOfVersion(version_D2CMP, 10032, 10032, 10032, 10021, 10014, 10106, 10065, 10020));
///A8 section
        D2GetCharStatsBIN = (TD2GetCharStatsBIN) (offset_D2Common + getAddressOfVersion(version_D2Common, 0x00000, 0x00000, 0x82C80, 0x15D0, 0x1800, 0x1220, 0x12D0, 0x17B0, 0x833E0));
        D2CompileCubeInput = (TD2CompileCubeInput) (offset_D2Common + getAddressOfVersion(version_D2Common, 0x00000, 0x00000, 0x12410, 0x5D7D0, 0x1A100, 0x116C0, 0x1C020, 0x5B0E0, 0x268600));
        D2GetItemTypesBIN = (TD2GetItemTypesBIN) (offset_D2Common + getAddressOfVersion(version_D2Common, 0x00000, 0x00000, 0x2B1A0, 0x11F0, 0x1380, 0x1140, 0x1300, 0x1160, 0x155C90));
        D2GetItemStatCostBIN = (TD2GetItemStatCostBIN) (offset_D2Common + getAddressOfVersion(version_D2Common, 0x00000, 0x00000, 0x642B0, 0x13F0, 0x12F0, 0x1540, 0x17A0, 0x17E0, 0x5C4F0));
        D2ReadFile = (TD2ReadFile) (offset_D2Common + getAddressOfVersion(version_D2Common, 0x738A4, 0x739B4, 0x84268, 0x96E0, 0x98D0, 0x9900, 0x9900, 0xB5E0, 0x117079));
        D2LoadSuperuniques = (TD2LoadSuperuniques) (offset_D2Common + getAddressOfVersion(version_D2Common, 0x1F500, 0x1F510, 0x29FA0, 0x71EB0, 0x32AA0, 0x7D2A0, 0x59870, 0x80C40, 0x2552E0));
        D2GetInventoryBIN = (TD2GetInventoryBIN) (offset_D2Common + getAddressOfVersion(version_D2Common, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000, 0x81EA0, 0x00000, 0x00000));
        D2LoadImage = (TD2LoadImage) (offset_D2Client + getAddressOfVersion(version_D2Client, 0x1000, 0x1000, 0x1000, 0x75D00, 0xA9070, 0xBEF70, 0x2B420, 0xA9480, 0x788B0));
        D2FreeImage = (TD2FreeImage) (offset_D2Client + getAddressOfVersion(version_D2Client, 0x1150, 0x1150, 0x1140, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000, 0x78A00));
        D2SendMsgToAll = (TD2SendMsgToAll) (offset_D2Client + getAddressOfVersion(version_D2Client, 0xD640, 0xD630, 0xDB50, 0x73620, 0x5E4E0, 0x79670, 0x147A0, 0xB6890, 0x787B0));
        D2GetLastMonsterIDFight = (TD2GetLastMonsterIDFight) (offset_D2Client + getAddressOfVersion(version_D2Client, 0x00000, 0x00000, 0x15A80, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000));
        D2PrintStatsPage = (TD2PrintStatsPage) (offset_D2Client + getAddressOfVersion(version_D2Client, 0x29800, 0x297F0, 0x2FD60, 0x828A0, 0x89320, 0x6B280, 0xBCEA0, 0xBF640, 0xA7D00));
        D2PrintStat = (TD2PrintStat) (offset_D2Client + getAddressOfVersion(version_D2Client, 0x4BB20, 0x4BB20, 0x521C0, 0xB8CB0, 0x21250, 0x88EA0, 0x54E10, 0x2CE40, 0xE4D80));
        D2SetColorPopup = (TD2SetColorPopup) (offset_D2Client + getAddressOfVersion(version_D2Client, 0x85A60, 0x84DE0, 0x80430, 0x9EEB0, 0x62070, 0x8B7A0, 0xBF5F0, 0x18820, 0x521C0));
        D2PlaySound = (TD2PlaySound) (offset_D2Client + getAddressOfVersion(version_D2Client, 0xB4360, 0xB36E0, 0xB5820, 0x3ACC0, 0x54210, 0x31FA0, 0x88A70, 0x26270, 0xB9A00));
        D2SendToServerXX = (TD2SendToServerXX) (offset_D2Client + getAddressOfVersion(version_D2Client, 0x00000, 0x00000, 0x00000, 0x73260, 0x5DE40, 0x791A0, 0x143E0, 0xB61F0, 0x78350));
        D2TogglePage = (TD2TogglePage) (offset_D2Client + getAddressOfVersion(version_D2Client, 0x88940, 0x87CC0, 0x83260, 0xA1F30, 0x65690, 0x8EF00, 0xC2790, 0x1C190, 0x55F20));
        D2ClickOnStashButton = (TD2ClickOnStashButton) (offset_D2Client + getAddressOfVersion(version_D2Client, 0x00000, 0x00000, 0x00000, 0xA6520, 0x710C0, 0xA6640, 0x8CD00, 0x90C10, 0x89980));
        D2LoadBuySelBtn = (TD2LoadBuySelBtn) (offset_D2Client + getAddressOfVersion(version_D2Client, 0x897B0, 0x88B30, 0x84110, 0x9E3B0, 0x621C0, 0x8B8F0, 0xBEAF0, 0x18AA0, 0x54600));
        D2LoadResImage = (TD2LoadResImage) (offset_D2Client + getAddressOfVersion(version_D2Client, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000, 0x520C0));
        D2FreeResImages = (TD2FreeResImages) (offset_D2Client + getAddressOfVersion(version_D2Client, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000, 0x96990));
        D2ReceivePacket = (TD2ReceivePacket) (offset_D2Client + getAddressOfVersion(version_D2Client, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000, 0x5C850));
        D2PrintInterface = (TD2PrintInterface) (offset_D2Client + getAddressOfVersion(version_D2Client, 0x87220, 0x865A0, 0x81B70, 0xA35F0, 0x669F0, 0x90150, 0xC39E0, 0x1D3E0, 0x56EE0));
        D2AddClient = (TD2AddClient) (offset_D2Game + getAddressOfVersion(version_D2Game, 0x00000, 0x00000, 0x6C60, 0xE3DA0, 0xE8210, 0xEB060, 0x49930, 0xE5070, 0x12C550));
        D2GetGameByClientID = (TD2GetGameByClientID) (offset_D2Game + getAddressOfVersion(version_D2Game, 0x00000, 0x00000, 0x94E0, 0xE0520, 0xE49A0, 0xA6360, 0x2AAE0, 0xBC700, 0x12E860));
        D2BroadcastFunction = (TD2BroadcastFunction) (offset_D2Game + getAddressOfVersion(version_D2Game, 0x00000, 0x00000, 0xB0E0, 0xDF250, 0xE36D0, 0xA5080, 0x29820, 0xBB510, 0x12DED0));
        D2SendPacket = (TD2SendPacket) (offset_D2Game + getAddressOfVersion(version_D2Game, 0xC380, 0xC650, 0xC710, 0x41420, 0xA0D50, 0x7D220, 0x8A3E0, 0xDB780, 0x13B280));
        D2SetSkillBaseLevelOnClient = (TD2SetSkillBaseLevelOnClient) (offset_D2Game + getAddressOfVersion(version_D2Game, 0xD650, 0xD920, 0xDB50, 0x44D00, 0xA3F20, 0x802E0, 0x8D5F0, 0xDD4F0, 0x13C4A0));
        D2LinkPortal = (TD2LinkPortal) (offset_D2Game + getAddressOfVersion(version_D2Game, 0x00000, 0x00000, 0x00000, 0x27230, 0x109F0, 0xAE930, 0xA22E0, 0x15F40, 0x16CF40));
        D2VerifIfNotCarry1 = (TD2VerifIfNotCarry1) (offset_D2Game + getAddressOfVersion(version_D2Game, 0x00000, 0x00000, 0x128F0, 0x38D90, 0x43E60, 0x11FF0, 0xD2070, 0xB2F70, 0x15CA40));
        D2TestPositionInRoom = (TD2TestPositionInRoom) (offset_D2Game + getAddressOfVersion(version_D2Game, 0x00000, 0x00000, 0x22070, 0x1090, 0x1DF0, 0x11F0, 0x1280, 0x1340, 0x63740));
        D2SpawnSuperUnique = (TD2SpawnSuperUnique) (offset_D2Game + getAddressOfVersion(version_D2Game, 0x00000, 0x00000, 0x3F220, 0x4ABE0, 0xEC7E0, 0x40B90, 0x24950, 0xCDE20, 0x1A09E0));
        D2SpawnMonster = (TD2SpawnMonster) (offset_D2Game + getAddressOfVersion(version_D2Game, 0x00000, 0x00000, 0x00000, 0xC80F0, 0xEF870, 0xEFB10, 0xEF650, 0xC8D70, 0x1B2F20));
        D2Game235C0 = (TD2Game235C0) (offset_D2Game + getAddressOfVersion(version_D2Game, 0x00000, 0x00000, 0x00000, 0xD6D10, 0x235C0, 0xD410, 0x200E0, 0x59980, 0x142B40));
        D2LoadInventory = (TD2LoadInventory) (offset_D2Game + getAddressOfVersion(version_D2Game, 0x4F100, 0x4F500, 0x5B8A0, 0xB9D70, 0x25D50, 0x44950, 0x54810, 0x3A4C0, 0x1335E0));
        D2GameGetObject = (TD2GameGetObject) (offset_D2Game + getAddressOfVersion(version_D2Game, 0x7BAE0, 0x7BFD0, 0x8BB00, 0x97620, 0xBEF80, 0x93650, 0xE03A0, 0x6DC40, 0x152F60));
        D2CreateUnit = (TD2CreateUnit) (offset_D2Game + getAddressOfVersion(version_D2Game, 0x00000, 0x00000, 0x00000, 0x99760, 0xC09E0, 0x94E70, 0xE1D90, 0x6FE10, 0x155230));
        D2OpenPandPortal = (TD2OpenPandPortal) (offset_D2Game + getAddressOfVersion(version_D2Game, 0x00000, 0x00000, 0x00000, 0x9B480, 0x34920, 0xD1AA0, 0x70180, 0x941E0, 0x165A90));
        D2OpenPandFinalPortal = (TD2OpenPandFinalPortal) (offset_D2Game + getAddressOfVersion(version_D2Game, 0x00000, 0x00000, 0x00000, 0x9B470, 0x34910, 0xD1A90, 0x70170, 0x941D0, 0x165AA0));
        D2MephAI = (TD2MephAI) (offset_D2Game + getAddressOfVersion(version_D2Game, 0x00000, 0x00000, 0x00000, 0x75980, 0xD7BD0, 0xCD0F0, 0x85B60, 0x4EAD0, 0x1F78B0));
        D2DiabloAI = (TD2DiabloAI) (offset_D2Game + getAddressOfVersion(version_D2Game, 0x00000, 0x00000, 0x00000, 0x84730, 0x85AA0, 0xDBE90, 0xA9610, 0x31920, 0x1E9170));
        D2BaalAI = (TD2BaalAI) (offset_D2Game + getAddressOfVersion(version_D2Game, 0x00000, 0x00000, 0x00000, 0xEAB20, 0x2BC80, 0xB3B90, 0xB8610, 0xC8850, 0x1FCFE0));
        D2UberBaalAI = (TD2UberBaalAI) (offset_D2Game + getAddressOfVersion(version_D2Game, 0x00000, 0x00000, 0x00000, 0xE92B0, 0x2A300, 0xB2210, 0xB6C80, 0xC6EC0, 0x1FD200));
        D2UberMephAI = (TD2UberMephAI) (offset_D2Game + getAddressOfVersion(version_D2Game, 0x00000, 0x00000, 0x00000, 0x70320, 0xD2D70, 0xC2A90, 0x7B4E0, 0x49480, 0x1F81C0));
        D2UberDiabloAI = (TD2UberDiabloAI) (offset_D2Game + getAddressOfVersion(version_D2Game, 0x00000, 0x00000, 0x00000, 0x7F200, 0x7FE60, 0xD6250, 0xA39D0, 0x2C3F0, 0x1E9DF0));
        D2SaveGame = (TD2SaveGame) (offset_D2Game + getAddressOfVersion(version_D2Game, 0x00000, 0x00000, 0x89C0, 0xE2390, 0xE66D0, 0xA8090, 0x2C830, 0xBE660, 0x12CA10));
        D2MonsterMove = (TD2MonsterMove) (offset_D2Game + getAddressOfVersion(version_D2Game, 0x00000, 0x00000, 0x00000, 0xEF580, 0xF0F70, 0xF0D70, 0xF2540, 0xF1800, 0x1DEB60));
        D2MonsterUseSkill = (TD2MonsterUseSkill) (offset_D2Game + getAddressOfVersion(version_D2Game, 0x00000, 0x00000, 0x00000, 0xFF1B0, 0xF0DB0, 0xF0BB0, 0xF2380, 0xF1430, 0x1DEAD0));
        D2SaveSPChar = (TD2SaveSPChar) (offset_D2Game + getAddressOfVersion(version_D2Game, 0x00000, 0x00000, 0x00000, 0xB9340, 0x25450, 0x44140, 0x53F10, 0x39810, 0x132240));
//ONLY UNTIL 1.10 :
        D2isLODGame = (TD2isLODGame) (offset_D2Client + getAddressOfVersion(version_D2Client, 0xBA00, 0xB9F0, 0xC080, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000));
        D2GetDifficultyLevel = (TD2GetDifficultyLevel) (offset_D2Client + getAddressOfVersion(version_D2Client, 0x00000, 0x00000, 0xC090, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000));
        D2GetMouseX = (TD2GetMouseX) (offset_D2Client + getAddressOfVersion(version_D2Client, 0xB6670, 0xB59F0, 0xB7BC0, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000));
        D2GetMouseY = (TD2GetMouseY) (offset_D2Client + getAddressOfVersion(version_D2Client, 0xB6680, 0xB5A00, 0xB7BD0, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000));
        D2GetClientPlayer = (TD2GetClientPlayer) (offset_D2Client + getAddressOfVersion(version_D2Client, 0x8DC40, 0x8CFC0, 0x883D0, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000, 0x63DD0));
        D2CleanStatMouseUp = (TD2CleanStatMouseUp) (offset_D2Client + getAddressOfVersion(version_D2Client, 0xB920, 0xB910, 0xBF60, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000, 0x4DA70));
        D2SendToServer3 = (TD2SendToServer3) (offset_D2Client + getAddressOfVersion(version_D2Client, 0xD210, 0xD200, 0xD990, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000));
        D2GetClient = (TD2GetClient) (offset_D2Game + getAddressOfVersion(version_D2Game, 0x7C2C0, 0x7C7B0, 0x8C2E0, 0x00000, 0x00000, 0x00000, 0x00000, 0x00000, 0x1531C0));

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////// VARIABLES ////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ptClientTable = (NetClient **) (offset_D2Game + getAddressOfVersion(version_D2Game, 0xF2A80, 0xF2918, 0x113FB8, 0x111718, 0x1115E0, 0x1105E0, 0x1107B8, 0x1105E0, 0x4842A8));
        ptResolutionY = (DWORD *) (offset_D2Client + getAddressOfVersion(version_D2Client, 0xD50E8, 0xD40E0, 0xD40F0, 0xF5C60, 0xF4FC8, 0xDC6E4, 0xDBC4C, 0xF7038, 0x311470));
        ptResolutionX = (DWORD *) (offset_D2Client + getAddressOfVersion(version_D2Client, 0xD50EC, 0xD40E4, 0xD40F4, 0xF5C5C, 0xF4FC4, 0xDC6E0, 0xDBC48, 0xF7034, 0x31146C));
        ptNegWindowStartY = (DWORD *) (offset_D2Client + getAddressOfVersion(version_D2Client, 0x125AD8, 0x124958, 0x11A74C, 0x11BD28, 0x11BEFC, 0x11BD2C, 0x11B9A4, 0x11D358, 0x3A285C));
        ptWindowStartX = (DWORD *) (offset_D2Client + getAddressOfVersion(version_D2Client, 0x125AD4, 0x124954, 0x11A748, 0x11BD24, 0x11BEF8, 0x11BD28, 0x11B9A0, 0x11D354, 0x3A2858));
        ptIsLodGame = (DWORD *) (offset_D2Client + getAddressOfVersion(version_D2Client, 0x000000, 0x000000, 0x000000, 0xFB3F4, 0x11A2F4, 0x10330C, 0x119854, 0x1087B4, 0x3A04F4));
        ptDifficultyLevel = (BYTE *) (offset_D2Client + getAddressOfVersion(version_D2Client, 0x000000, 0x000000, 0x10795C, 0x11BFB8, 0x11C2A8, 0x11BFF4, 0x000000, 0x000000, 0x000000));
        ptMouseY = (DWORD *) (offset_D2Client + getAddressOfVersion(version_D2Client, 0x000000, 0x000000, 0x000000, 0x10A40C, 0x11B414, 0x101634, 0x11B824, 0x11C94C, 0x3A6AAC));
        ptMouseX = (DWORD *) (offset_D2Client + getAddressOfVersion(version_D2Client, 0x000000, 0x000000, 0x000000, 0x10A410, 0x11B418, 0x101638, 0x11B828, 0x11C950, 0x3A6AB0));
        ptptClientChar = (Unit **) (offset_D2Client + getAddressOfVersion(version_D2Client, 0x000000, 0x000000, 0x000000, 0x11C4F0, 0x11C1E0, 0x11C3D0, 0x11BBFC, 0x11D050, 0x3A6A70));
        ptInputCommandLen = (DWORD *) (offset_D2Client + getAddressOfVersion(version_D2Client, 0x11E0F4, 0x11CF54, 0x112D04, 0x11B9A8, 0x11BB30, 0x11BF48, 0x11C028, 0x11CAA4, 0x3BB5E8));
        ptInputCommand = (WCHAR *) (offset_D2Client + getAddressOfVersion(version_D2Client, 0x11CE50, 0x11BCB0, 0x111A58, 0x11C590, 0x11D590, 0x11FC40, 0x11EC80, 0x11D650, 0x3BB638));
        ptNbStatDesc = (DWORD *) (offset_D2Client + getAddressOfVersion(version_D2Client, 0xDB918, 0xDA828, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000));
        ptStatDescTable = (DWORD *) (offset_D2Client + getAddressOfVersion(version_D2Client, 0xDAF98, 0xD9EA8, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000));
        SgptDataTables = *(DataTables **) (offset_D2Common + getAddressOfVersion(version_D2Common, 0x0000, 0x0000, 0x96A20, 0x9B74C, 0x9EE8C, 0x9B500, 0x99E1C, 0xA33F0, 0x344304));
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
