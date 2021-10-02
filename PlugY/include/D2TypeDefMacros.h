#pragma once

#include <Windows.h>
#include <D2UnitStruct.h>
#include <d2Struct.h>
#include <d2Struct.h>
#include <D2UnitStruct.h>
#include <d2BinFile.h>

namespace PlugY {
    typedef DWORD(__stdcall *TD2Common11084)(Commons::Room *ptRoom, DWORD zero);

    extern TD2Common11084 D2Common11084;

    typedef DWORD(__stdcall *TD2GetLevelID)(Commons::Room *ptRoom);

    extern TD2GetLevelID D2GetLevelID;

    typedef Commons::Room *(__stdcall *TD2GetDropRoom)(Commons::Room *ptRoom, Commons::Position *, Commons::Position *, DWORD, DWORD, DWORD, DWORD);

    extern TD2GetDropRoom D2GetDropRoom;

    typedef Commons::Unit *(__stdcall *TD2Common10242)(Commons::Inventory *ptInventory, Commons::Unit *ptItem, DWORD bIsClient);

    extern TD2Common10242 D2Common10242;

    typedef Commons::Unit *(__stdcall *TD2CanPutItemInInv)(Commons::Inventory *ptInventory, Commons::Unit *ptItem, DWORD p3, DWORD zero, Commons::Unit *ptUnit, const char *file, DWORD line);

    extern TD2CanPutItemInInv D2CanPutItemInInv;

    typedef Commons::Unit *(__stdcall *TD2InvRemoveItem)(Commons::Inventory *ptInventory, Commons::Unit *ptItem);

    extern TD2InvRemoveItem D2InvRemoveItem;

    typedef DWORD(__stdcall *TD2InvAddItem)(Commons::Inventory *ptInventory, Commons::Unit *ptItem, DWORD posX, DWORD posY, DWORD vValueC, DWORD bIsClient, BYTE page);

    extern TD2InvAddItem D2InvAddItem;

    typedef DWORD(__stdcall *TD2Common10250)(const char *file, DWORD line, Commons::Inventory *ptInventory, DWORD posX, DWORD posY, DWORD vValueC, DWORD bIsClient, BYTE page);

    extern TD2Common10250 D2Common10250;

    typedef DWORD(__stdcall *TD2Common10273)(Commons::Inventory *ptInventory, void *unknown);

    extern TD2Common10273 D2Common10273;

    typedef Commons::Unit *(__stdcall *TD2InventoryGetFirstItem)(Commons::Inventory *ptInventory);

    extern TD2InventoryGetFirstItem D2InventoryGetFirstItem;

    typedef Commons::Unit *(__stdcall *TD2UnitGetNextItem)(Commons::Unit *ptItem);

    extern TD2UnitGetNextItem D2UnitGetNextItem;

    typedef Commons::Unit *(__stdcall *TD2GetRealItem)(Commons::Unit *ptUnit);

    extern TD2GetRealItem D2GetRealItem;

    typedef DWORD(__stdcall *TD2GetPosX)(Commons::Unit *ptUnit);

    extern TD2GetPosX D2GetPosX;

    typedef DWORD(__stdcall *TD2GetPosY)(Commons::Unit *ptUnit);

    extern TD2GetPosY D2GetPosY;

    typedef void(__stdcall *TD2GetPosition)(Commons::Unit *ptUnit, Commons::Position *pos);

    extern TD2GetPosition D2GetPosition;

    typedef DWORD(__stdcall *TD2GetMaxGoldBank)(Commons::Unit *ptUnit);

    extern TD2GetMaxGoldBank D2GetMaxGoldBank;

    typedef Commons::Room *(__stdcall *TD2GetRoom)(Commons::Unit *ptUnit);

    extern TD2GetRoom D2GetRoom;

    typedef Commons::PlayerData *(__stdcall *TD2InitPlayerData)(Commons::Unit *ptChar);

    extern TD2InitPlayerData D2InitPlayerData;

    typedef Commons::PlayerData *(__stdcall *TD2GetPlayerData)(Commons::Unit *ptChar);

    extern TD2GetPlayerData D2GetPlayerData;

    typedef DWORD(__stdcall *TD2GetDefence)(Commons::Unit *ptChar);

    extern TD2GetDefence D2GetDefence;

    typedef DWORD(__stdcall *TD2GetChanceToBlock)(Commons::Unit *ptChar, DWORD isLODGame);

    extern TD2GetChanceToBlock D2GetChanceToBlock;

    typedef DWORD(__stdcall *TD2GetMaxGold)(Commons::Unit *ptUnit);

    extern TD2GetMaxGold D2GetMaxGold;

    typedef DWORD(__stdcall *TD2Common10572)(Commons::Unit *ptObject, DWORD value);

    extern TD2Common10572 D2Common10572;

    typedef BYTE(__stdcall *TD2GetObjectFlags)(Commons::Unit *ptObject);

    extern TD2GetObjectFlags D2GetObjectFlags;

    typedef void(__stdcall *TD2SetObjectFlags)(Commons::Unit *ptObject, BYTE flags);

    extern TD2SetObjectFlags D2SetObjectFlags;

    typedef DWORD(__stdcall *TD2isInState)(Commons::Unit *ptChar, DWORD isLODGame);

    extern TD2isInState D2isInState;

    typedef void(__stdcall *TD2AddPlayerStat)(Commons::Unit *ptChar, DWORD statID, int amount, DWORD index);

    extern TD2AddPlayerStat D2AddPlayerStat;

    typedef int(__stdcall *TD2GetPlayerStat)(Commons::Unit *ptChar, DWORD statID, DWORD index);

    extern TD2GetPlayerStat D2GetPlayerStat;

    typedef int(__stdcall *TD2GetPlayerBaseStat)(Commons::Unit *ptChar, DWORD statID, DWORD index);

    extern TD2GetPlayerBaseStat D2GetPlayerBaseStat;

    typedef DWORD(__stdcall *TD2haveDefenceBonus)(Commons::Unit *ptChar);

    extern TD2haveDefenceBonus D2haveDefenceBonus;

    typedef DWORD(__stdcall *TD2haveFireResBonus)(Commons::Unit *ptChar);

    extern TD2haveFireResBonus D2haveFireResBonus;

    typedef DWORD(__stdcall *TD2haveColdResBonus)(Commons::Unit *ptChar);

    extern TD2haveColdResBonus D2haveColdResBonus;

    typedef DWORD(__stdcall *TD2haveLightResBonus)(Commons::Unit *ptChar);

    extern TD2haveLightResBonus D2haveLightResBonus;

    typedef DWORD(__stdcall *TD2havePoisonResBonus)(Commons::Unit *ptChar);

    extern TD2havePoisonResBonus D2havePoisonResBonus;

    typedef DWORD(__stdcall *TD2haveDefenceMalus)(Commons::Unit *ptChar);

    extern TD2haveDefenceMalus D2haveDefenceMalus;

    typedef DWORD(__stdcall *TD2haveFireResMalus)(Commons::Unit *ptChar);

    extern TD2haveFireResMalus D2haveFireResMalus;

    typedef DWORD(__stdcall *TD2haveColdResMalus)(Commons::Unit *ptChar);

    extern TD2haveColdResMalus D2haveColdResMalus;

    typedef DWORD(__stdcall *TD2haveLightResMalus)(Commons::Unit *ptChar);

    extern TD2haveLightResMalus D2haveLightResMalus;

    typedef DWORD(__stdcall *TD2havePoisonResMalus)(Commons::Unit *ptChar);

    extern TD2havePoisonResMalus D2havePoisonResMalus;

    typedef void *(__stdcall *TD2CompileTxtFile)(DWORD unused, const char *filename, Commons::BINField *ptFields, DWORD *ptRecordCount, DWORD recordLength);

    extern TD2CompileTxtFile D2CompileTxtFile;

    typedef Commons::ItemsBIN *(__stdcall *TD2GetItemsBIN)(DWORD itemID);

    extern TD2GetItemsBIN D2GetItemsBIN;

    typedef Commons::GemsBIN *(__stdcall *TD2GetGemsBIN)(DWORD gemID);

    extern TD2GetGemsBIN D2GetGemsBIN;

    typedef Commons::CubeMainBIN *(__stdcall *TD2GetCubeMainBIN)(DWORD cubemainID);

    extern TD2GetCubeMainBIN D2GetCubeMainBIN;

    typedef int(__stdcall *TD2GetNbCubeMainBIN)();

    extern TD2GetNbCubeMainBIN D2GetNbCubeMainBIN;

    typedef DWORD(__stdcall *TD2GetNextLevelXP)(DWORD classID, DWORD level);

    extern TD2GetNextLevelXP D2GetNextLevelXP;

    typedef DWORD(__stdcall *TD2GetMaxLevel)(DWORD classID);

    extern TD2GetMaxLevel D2GetMaxLevel;

    typedef Commons::DifficultyLevelsBIN *(__stdcall *TD2GetDifficultyLevelsBIN)(DWORD difficultyLevel);

    extern TD2GetDifficultyLevelsBIN D2GetDifficultyLevelsBIN;

    typedef DWORD(__stdcall *TD2GetItemQuality)(Commons::Unit *ptItem);

    extern TD2GetItemQuality D2GetItemQuality;

    typedef DWORD(__stdcall *TD2TestFlags)(Commons::Unit *ptUnit, DWORD flags, DWORD line, const char *file);

    extern TD2TestFlags D2TestFlags;

    typedef DWORD(__stdcall *TD2GetItemLevel)(Commons::Unit *ptItem);

    extern TD2GetItemLevel D2GetItemLevel;

    typedef BYTE(__stdcall *TD2ItemGetPage)(Commons::Unit *ptUnit);

    extern TD2ItemGetPage D2ItemGetPage;

    typedef void(__stdcall *TD2ItemSetPage)(Commons::Unit *ptItem, BYTE page);

    extern TD2ItemSetPage D2ItemSetPage;

    typedef DWORD(__stdcall *TD2CheckItemType)(Commons::Unit *ptItem, DWORD itype);

    extern TD2CheckItemType D2CheckItemType;

    typedef int(__stdcall *TD2GetUniqueID)(Commons::Unit *ptItem);

    extern TD2GetUniqueID D2GetUniqueID;

    typedef void(__stdcall *TD2SetAnim)(Commons::Unit *ptUnit, int anim);

    extern TD2SetAnim D2SetAnim;

    typedef int *(__stdcall *TD2GetNbRunesBIN)();

    extern TD2GetNbRunesBIN D2GetNbRunesBIN;

    typedef Commons::RunesBIN *(__stdcall *TD2GetRunesBIN)(int runesID);

    extern TD2GetRunesBIN D2GetRunesBIN;

    typedef DWORD(__stdcall *TD2SaveItem)(Commons::Unit *ptItem, Commons::saveBitField *data, DWORD startSize, DWORD p4, DWORD p5, DWORD p6);

    extern TD2SaveItem D2SaveItem;

    typedef void(__stdcall *TD2SetSkillBaseLevel)(Commons::Unit *ptChar, DWORD skillID, DWORD slvl, DWORD bRemove, char *, DWORD);

    extern TD2SetSkillBaseLevel D2SetSkillBaseLevel;

    typedef DWORD(__stdcall *TD2GetSkillLevel)(Commons::Unit *ptChar, Commons::SkillData *ptSkill, DWORD includingBonus);

    extern TD2GetSkillLevel D2GetSkillLevel;

    typedef DWORD(__stdcall *TD2GetSkillCost)(Commons::Unit *ptChar, int skpoints, DWORD skillID, DWORD curSkillLevel);

    extern TD2GetSkillCost D2GetSkillCost;

    typedef void(__fastcall *TD2SetNbPlayers)(DWORD nbPlayers);

    extern TD2SetNbPlayers D2SetNbPlayers;

    typedef DWORD(__stdcall *TD2SendToServer)(DWORD size, DWORD one, void *data);

    extern TD2SendToServer D2SendToServer;

    typedef DWORD(__stdcall *TD2SendToClient)(DWORD zero, DWORD clientID, void *data, DWORD size);

    extern TD2SendToClient D2SendToClient;

    typedef void(__stdcall *TD2FogAssertOld)(const char *ptMessage, DWORD eip, DWORD line);

    extern TD2FogAssertOld D2FogAssertOld;

    typedef void(__fastcall *TD2FogAssert)(const char *ptMessage, DWORD eip, DWORD line);

    extern TD2FogAssert D2FogAssert;

    typedef void *(__fastcall *TD2FogMemAlloc)(DWORD dwMemSize, LPCSTR lpszErrFile, DWORD ErrLine, DWORD Zero);

    extern TD2FogMemAlloc D2FogMemAlloc;

    typedef void *(__fastcall *TD2FogMemDeAlloc)(void *ptMemLoc, LPCSTR lpszErrFile, DWORD ErrLine, DWORD Zero);

    extern TD2FogMemDeAlloc D2FogMemDeAlloc;

    typedef void *(__fastcall *TD2AllocMem)(DWORD, DWORD dwMemSize, LPCSTR lpszErrFile, DWORD ErrLine, DWORD Zero);

    extern TD2AllocMem D2AllocMem;

    typedef void *(__fastcall *TD2FreeMem)(DWORD, void *ptMemLoc, LPCSTR lpszErrFile, DWORD ErrLine, DWORD Zero);

    extern TD2FreeMem D2FreeMem;

    typedef DWORD(__fastcall *TD2MPQOpenFile)(char *ptPath, void **buf);

    extern TD2MPQOpenFile D2MPQOpenFile;

    typedef DWORD(__fastcall *TD2MPQCloseFile)(void *mpqfile);

    extern TD2MPQCloseFile D2MPQCloseFile;

    typedef DWORD(__fastcall *TD2MPQReadFile)(void *mpqfile, BYTE *buffer, DWORD nbToRead, DWORD *nbRead, DWORD, DWORD, DWORD);

    extern TD2MPQReadFile D2MPQReadFile;

    typedef DWORD(__fastcall *TD2MPQGetSizeFile)(void *mpqfile, DWORD *toReset);

    extern TD2MPQGetSizeFile D2MPQGetSizeFile;

    typedef void(__fastcall *TD2FogGetSavePath)(char *ptPath, DWORD maxsize);

    extern TD2FogGetSavePath D2FogGetSavePath;

    typedef void(__fastcall *TD2FogGetInstallPath)(char *ptPath, DWORD maxsize);

    extern TD2FogGetInstallPath D2FogGetInstallPath;

    typedef void(__stdcall *TD2Fog10212)(DWORD unknow);

    extern TD2Fog10212 D2Fog10212;

    typedef int(__stdcall *TD2GetInstructionPointer)();

    extern TD2GetInstructionPointer D2GetInstructionPointer;

    typedef LPWSTR(__fastcall *TD2GetStringFromString)(const char *ptString);

    extern TD2GetStringFromString D2GetStringFromString;

    typedef LPWSTR(__fastcall *TD2GetStringFromIndex)(WORD dwIndexNum);

    extern TD2GetStringFromIndex D2GetStringFromIndex;

    typedef DWORD(__stdcall *TD2GetLang)();

    extern TD2GetLang D2GetLang;

    typedef DWORD(__stdcall *TD2PrintBigNumber)(LPWSTR ptBuf, DWORD number, DWORD size);

    extern TD2PrintBigNumber D2PrintBigNumber;

    typedef DWORD(__stdcall *TD2StormMPQOpenFile)(DWORD zero, LPCSTR fileName, DWORD dwSearchScope, void **buffer);

    extern TD2StormMPQOpenFile D2StormMPQOpenFile;

    typedef void(__stdcall *TD2Storm503)(DWORD, DWORD, DWORD);

    extern TD2Storm503 D2Storm503;

    typedef void(__stdcall *TD2FreeWinMessage)(Commons::sWinMessage *msg);

    extern TD2FreeWinMessage D2FreeWinMessage;

    typedef DWORD(__stdcall *TD2GetResolution)();

    extern TD2GetResolution D2GetResolution;

    typedef void(__stdcall *TD2FillArea)(DWORD x1, DWORD y1, DWORD x2, DWORD y2, DWORD color, DWORD transTbl);

    extern TD2FillArea D2FillArea;

    typedef void(__stdcall *TD2PrintImage)(Commons::sDrawImageInfo *data, DWORD x, DWORD y, DWORD p4, DWORD p5, DWORD p6);

    extern TD2PrintImage D2PrintImage;

    typedef void(__fastcall *TD2PrintLineOnTextBox)(void *screen, char *s, DWORD color);

    extern TD2PrintLineOnTextBox D2PrintLineOnTextBox;

    typedef void(__fastcall *TD2PrintString)(LPWSTR s, DWORD x, DWORD y, DWORD color, DWORD bfalse);

    extern TD2PrintString D2PrintString;

    typedef DWORD(__fastcall *TD2GetPixelLen)(LPWSTR s);

    extern TD2GetPixelLen D2GetPixelLen;

    typedef DWORD(__fastcall *TD2SetFont)(DWORD fontID);

    extern TD2SetFont D2SetFont;

    typedef void(__fastcall *TD2PrintPopup)(LPWSTR s, DWORD x, DWORD y, DWORD color, DWORD center);

    extern TD2PrintPopup D2PrintPopup;

    typedef void(__fastcall *TD2GetPixelRect)(LPWSTR s, DWORD *x, DWORD *y);

    extern TD2GetPixelRect D2GetPixelRect;

    typedef DWORD(__fastcall *TD2PrintTextPopup)(LPWSTR s, DWORD x, DWORD y, DWORD uk, DWORD type, DWORD color);

    extern TD2PrintTextPopup D2PrintTextPopup;

    typedef void *(__stdcall *TD2CreateTextBox)(DWORD *data);

    extern TD2CreateTextBox D2CreateTextBox;

    typedef DWORD(__stdcall *TD2CMP10014)(void *image);

    extern TD2CMP10014 D2CMP10014;

    typedef Commons::CharStatsBIN *(__fastcall *TD2GetCharStatsBIN)(DWORD charID);

    extern TD2GetCharStatsBIN D2GetCharStatsBIN;

    typedef DWORD(__fastcall *TD2CompileCubeInput)(Commons::CubeInput *cubeinput, char *s, DWORD p1, DWORD p2);

    extern TD2CompileCubeInput D2CompileCubeInput;

    typedef Commons::ItemTypesBIN *(__fastcall *TD2GetItemTypesBIN)(DWORD itemTypesId);

    extern TD2GetItemTypesBIN D2GetItemTypesBIN;

    typedef Commons::ItemStatCostBIN *(__fastcall *TD2GetItemStatCostBIN)(DWORD id);

    extern TD2GetItemStatCostBIN D2GetItemStatCostBIN;

    typedef void *(__fastcall *TD2ReadFile)(DWORD mempool, char *filename, DWORD *size, const char *, DWORD);

    extern TD2ReadFile D2ReadFile;

    typedef void(__stdcall *TD2LoadSuperuniques)(DWORD mempool);

    extern TD2LoadSuperuniques D2LoadSuperuniques;

    typedef Commons::InventoryBIN *(__stdcall *TD2GetInventoryBIN)();

    extern TD2GetInventoryBIN D2GetInventoryBIN;

    typedef void *(__fastcall *TD2LoadImage)(const char *filename, DWORD filetype);

    extern TD2LoadImage D2LoadImage;

    typedef void(__fastcall *TD2FreeImage)(void *image);

    extern TD2FreeImage D2FreeImage;

    typedef void(__fastcall *TD2SendMsgToAll)(BYTE *data);

    extern TD2SendMsgToAll D2SendMsgToAll;

    typedef DWORD(__stdcall *TD2GetLastMonsterIDFight)();

    extern TD2GetLastMonsterIDFight D2GetLastMonsterIDFight;

    typedef void(__stdcall *TD2PrintStatsPage)();

    extern TD2PrintStatsPage D2PrintStatsPage;

    typedef DWORD(__fastcall *TD2PrintStat)(Commons::Unit *ptItem, Commons::Stats *ptStats, DWORD statID, DWORD statIndex, DWORD statValue, LPWSTR lpText);

    extern TD2PrintStat D2PrintStat;

    typedef LPWSTR(__fastcall *TD2SetColorPopup)(LPWSTR popupText, DWORD color);

    extern TD2SetColorPopup D2SetColorPopup;

    typedef DWORD(__fastcall *TD2PlaySound)(DWORD id, DWORD, DWORD, DWORD, DWORD);

    extern TD2PlaySound D2PlaySound;

    typedef void(__fastcall *TD2SendToServerXX)(DWORD size, BYTE *data);

    extern TD2SendToServerXX D2SendToServerXX;

    typedef void(__fastcall *TD2TogglePage)(DWORD a, DWORD b, DWORD c);

    extern TD2TogglePage D2TogglePage;

    typedef void(__fastcall *TD2ClickOnStashButton)(DWORD x, DWORD y);

    extern TD2ClickOnStashButton D2ClickOnStashButton;

    typedef void *(__stdcall *TD2LoadBuySelBtn)();

    extern TD2LoadBuySelBtn D2LoadBuySelBtn;

    typedef void *(__fastcall *TD2LoadResImage)(const char *filename);

    extern TD2LoadResImage D2LoadResImage;

    typedef void *(__fastcall *TD2FreeResImages)();

    extern TD2FreeResImages D2FreeResImages;

    typedef void *(__fastcall *TD2ReceivePacket)(DWORD a, DWORD b);

    extern TD2ReceivePacket D2ReceivePacket;

    typedef DWORD(__stdcall *TD2PrintInterface)(void *unknown);

    extern TD2PrintInterface D2PrintInterface;

    typedef void(__fastcall *TD2AddClient)(DWORD clientID);

    extern TD2AddClient D2AddClient;

    typedef Commons::Game *(__stdcall *TD2GetGameByClientID)(DWORD clientID);

    extern TD2GetGameByClientID D2GetGameByClientID;

    typedef void(__fastcall *TD2BroadcastFunction)(Commons::Game *ptGame, void *fct, void *param);

    extern TD2BroadcastFunction D2BroadcastFunction;

    typedef DWORD(__fastcall *TD2SendPacket)(void *ptNetClient, LPVOID pData, DWORD size);

    extern TD2SendPacket D2SendPacket;

    typedef void(__fastcall *TD2SetSkillBaseLevelOnClient)(void *ptClient, Commons::Unit *ptChar, DWORD skillID, DWORD sLvl, DWORD bRemove);

    extern TD2SetSkillBaseLevelOnClient D2SetSkillBaseLevelOnClient;

    typedef DWORD(__stdcall *TD2LinkPortal)(Commons::Game *ptGame, Commons::Unit *ptObject, DWORD levelEndID, DWORD levelStartID);

    extern TD2LinkPortal D2LinkPortal;

    typedef DWORD(__fastcall *TD2VerifIfNotCarry1)(Commons::Unit *ptItem, Commons::ItemsBIN *itemsData, Commons::Unit *ptFirstItem);

    extern TD2VerifIfNotCarry1 D2VerifIfNotCarry1;

    typedef Commons::Room *(__fastcall *TD2TestPositionInRoom)(Commons::Room *ptRoom, DWORD x, DWORD y);

    extern TD2TestPositionInRoom D2TestPositionInRoom;

    typedef DWORD(__fastcall *TD2SpawnSuperUnique)(Commons::Game *ptGame, Commons::Room *ptRoom, DWORD zero1, DWORD x, DWORD y, DWORD minusOne, DWORD superuniqueID, DWORD zero2);

    extern TD2SpawnSuperUnique D2SpawnSuperUnique;

    typedef Commons::Unit *(__fastcall *TD2SpawnMonster)(DWORD id, DWORD mode, Commons::Game *ptGame, Commons::Room *ptRoom, DWORD x, DWORD y, DWORD one, DWORD zero);

    extern TD2SpawnMonster D2SpawnMonster;

    typedef void(__stdcall *TD2Game235C0)(Commons::Game *ptGame, Commons::Room *ptRoom);

    extern TD2Game235C0 D2Game235C0;

    typedef DWORD(__fastcall *TD2LoadInventory)(Commons::Game *ptGame, Commons::Unit *pChar, Commons::saveBitField *pdata, DWORD p2, DWORD maxSize, DWORD p4, DWORD *ptNbBytesRead);

    extern TD2LoadInventory D2LoadInventory;

    typedef Commons::Unit *(__fastcall *TD2GameGetObject)(Commons::Game *ptGame, DWORD type, DWORD itemNum);

    extern TD2GameGetObject D2GameGetObject;

    typedef Commons::Unit *(__fastcall *TD2CreateUnit)(DWORD type, DWORD id, DWORD x, DWORD y, Commons::Game *ptGame, Commons::Room *ptRoom, DWORD uk1, DWORD uk2, DWORD uk3);

    extern TD2CreateUnit D2CreateUnit;

    typedef void(__fastcall *TD2OpenPandPortal)(Commons::Game *ptGame, Commons::Unit *ptChar);

    extern TD2OpenPandPortal D2OpenPandPortal;

    typedef void(__fastcall *TD2OpenPandFinalPortal)(Commons::Game *ptGame, Commons::Unit *ptChar);

    extern TD2OpenPandFinalPortal D2OpenPandFinalPortal;

    typedef void(__fastcall *TD2MephAI)(Commons::Game *ptGame, Commons::Unit *ptMonster, Commons::AIParam *args);

    extern TD2MephAI D2MephAI;

    typedef void(__fastcall *TD2DiabloAI)(Commons::Game *ptGame, Commons::Unit *ptMonster, Commons::AIParam *args);

    extern TD2DiabloAI D2DiabloAI;

    typedef void(__fastcall *TD2BaalAI)(Commons::Game *ptGame, Commons::Unit *ptMonster, Commons::AIParam *args);

    extern TD2BaalAI D2BaalAI;

    typedef void(__fastcall *TD2UberBaalAI)(Commons::Game *ptGame, Commons::Unit *ptMonster, Commons::AIParam *args);

    extern TD2UberBaalAI D2UberBaalAI;

    typedef void(__fastcall *TD2UberMephAI)(Commons::Game *ptGame, Commons::Unit *ptMonster, Commons::AIParam *args);

    extern TD2UberMephAI D2UberMephAI;

    typedef void(__fastcall *TD2UberDiabloAI)(Commons::Game *ptGame, Commons::Unit *ptMonster, Commons::AIParam *args);

    extern TD2UberDiabloAI D2UberDiabloAI;

    typedef void(__stdcall *TD2SaveGame)(Commons::Game *ptGame);

    extern TD2SaveGame D2SaveGame;

    typedef void(__fastcall *TD2MonsterMove)(Commons::Game *ptGame, Commons::Unit *ptMonster, Commons::Unit *target, DWORD two, DWORD x, DWORD y, DWORD one, DWORD zero);

    extern TD2MonsterMove D2MonsterMove;

    typedef void(__fastcall *TD2MonsterUseSkill)(Commons::Game *ptGame, Commons::Unit *ptMonster, DWORD arg, DWORD skill, Commons::Unit *target, DWORD x, DWORD y);

    extern TD2MonsterUseSkill D2MonsterUseSkill;

    typedef void(__fastcall *TD2SaveSPChar)(Commons::Game *ptGame, Commons::Unit *ptChar, char *name, DWORD arg, DWORD secondPass);

    extern TD2SaveSPChar D2SaveSPChar;

//ONLY UNTIL 1.10 :
    typedef DWORD(__fastcall *TD2isLODGame)();

    extern TD2isLODGame D2isLODGame;

    typedef BYTE(__fastcall *TD2GetDifficultyLevel)();

    extern TD2GetDifficultyLevel D2GetDifficultyLevel;

    typedef DWORD(__stdcall *TD2GetMouseX)();

    extern TD2GetMouseX D2GetMouseX;

    typedef DWORD(__stdcall *TD2GetMouseY)();

    extern TD2GetMouseY D2GetMouseY;

    typedef Commons::Unit *(__stdcall *TD2GetClientPlayer)();

    extern TD2GetClientPlayer D2GetClientPlayer;

    typedef void(__fastcall *TD2CleanStatMouseUp)();

    extern TD2CleanStatMouseUp D2CleanStatMouseUp;

    typedef void(__fastcall *TD2SendToServer3)(BYTE type, WORD p);

    extern TD2SendToServer3 D2SendToServer3;

    typedef Commons::NetClient *(__fastcall *TD2GetClient)(Commons::Unit *ptUnit, char *lpszErrFile, DWORD ErrLine);

    extern TD2GetClient D2GetClient;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////// VARIABLES ////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    extern DWORD *ptResolutionY;
    extern DWORD *ptResolutionX;
    extern DWORD *ptNegWindowStartY;
    extern DWORD *ptWindowStartX;
    extern Commons::NetClient **ptClientTable;
    extern DWORD *ptIsLodGame;
    extern BYTE *ptDifficultyLevel;
    extern DWORD *ptMouseY;
    extern DWORD *ptMouseX;
    extern Commons::Unit **ptptClientChar;
    extern DWORD *ptInputCommandLen;
    extern WCHAR *ptInputCommand;
    extern DWORD *ptNbStatDesc;
    extern DWORD *ptStatDescTable;
}