#include "common.h"

s_shifting shifting;

#define D2S(F, I, R, N, P)    T##N N;
#define D2F(F, I, R, N, P)    T##N N;
#define E2S(F, A, R, N, P)    T##N N;
#define E2F(F, A, R, N, P)    T##N N;
#define E2C(F, A, T, N)        T* pt##N;
#define F8(X, Z, A, B, C, D, E, F, G, H, I, R, N, P) T##N N;
#define A8(X, Z, A, B, C, D, E, F, G, H, I, R, N, P) T##N N;
#define C8(Z, A, B, C, D, E, F, G, H, I, T, N)       T* pt##N;

/* Warning, all this code is used for macro replacement only */

F8(STD, D2Common, 00000, 00000, 00000, 10188, 11084, 11109, 10346, 10907, 21AED0, DWORD, D2Common11084,
   (Room * ptRoom, DWORD zero));
F8(STD, D2Common, 10057, 10057, 10057, 10332, 11021, 10511, 10826, 10691, 21A1B0, DWORD, D2GetLevelID, (Room * ptRoom));
F8(STD, D2Common, 10138, 10138, 10138, 10623, 10491, 11043, 10654, 10716, 24E810, Room*, D2GetDropRoom,
   (Room * ptRoom, Position *, Position *, DWORD, DWORD, DWORD, DWORD));
F8(STD, D2Common, 10242, 10242, 10242, 00000, 00000, 00000, 00000, 00000, 00000, Unit*, D2Common10242,
   (Inventory * ptInventory, Unit * ptItem, DWORD bIsClient));
F8(STD, D2Common, 10246, 10246, 10246, 10855, 10813, 10289, 10133, 10402, 23B950, Unit*, D2CanPutItemInInv,
   (Inventory * ptInventory, Unit * ptItem, DWORD p3, DWORD zero, Unit * ptUnit, const char *file, DWORD line));
F8(STD, D2Common, 10243, 10243, 10243, 10461, 10827, 10936, 10646, 10490, 23AD90, Unit*, D2InvRemoveItem,
   (Inventory * ptInventory, Unit * ptItem));
F8(STD, D2Common, 10249, 10249, 10249, 10880, 11068, 10436, 11107, 10963, 23BCC0, DWORD, D2InvAddItem,
   (Inventory * ptInventory, Unit *
                             ptItem, DWORD posX, DWORD posY, DWORD vValueC, DWORD bIsClient, BYTE page));//result : boolean 0=echec  ; vValueC = 0 for Game.dll, 1 for Clientdll
F8(STD, D2Common, 10250, 10250, 10250, 00000, 00000, 00000, 00000, 00000, 00000, DWORD, D2Common10250,
   (const char* file, DWORD line, Inventory* ptInventory, DWORD posX, DWORD posY, DWORD vValueC, DWORD bIsClient, BYTE page));// result : boolean 0=echec  ; vValueC = 0 for Game.dll, 1 for Clientdll
F8(STD, D2Common, 10273, 10273, 10273, 00000, 00000, 00000, 00000, 00000, 00000, DWORD, D2Common10273,
   (Inventory * ptInventory, void * unknown));
F8(STD, D2Common, 10277, 10277, 10277, 10402, 10535, 11151, 10460, 11040, 23B2C0, Unit*, D2InventoryGetFirstItem,
   (Inventory * ptInventory));
F8(STD, D2Common, 10304, 10304, 10304, 10934, 11140, 10770, 10464, 10879, 23DFA0, Unit*, D2UnitGetNextItem,
   (Unit * ptItem));
F8(STD, D2Common, 10305, 10305, 10305, 11095, 10748, 10852, 11147, 10897, 23DFD0, Unit*, D2GetRealItem,
   (Unit * ptUnit));
F8(STD, D2Common, 10326, 10326, 00000, 00000, 00000, 00000, 00000, 00000, 00000, DWORD, D2GetPosX,
   (Unit * ptUnit));//NOT IN 1.10
F8(STD, D2Common, 10329, 10329, 00000, 00000, 00000, 00000, 00000, 00000, 00000, DWORD, D2GetPosY,
   (Unit * ptUnit));//NOT IN 1.10
F8(STD, D2Common, 10332, 10332, 10332, 11080, 10056, 10543, 10141, 11166, 220870, void, D2GetPosition,
   (Unit * ptUnit, Position * pos));
F8(STD, D2Common, 10339, 10339, 10339, 10455, 10864, 10941, 11060, 11025, 223460, DWORD, D2GetMaxGoldBank,
   (Unit * ptUnit));
F8(STD, D2Common, 10342, 10342, 10342, 10172, 10933, 10366, 10331, 10846, 220BB0, Room*, D2GetRoom, (Unit * ptUnit));
F8(STD, D2Common, 10420, 10420, 10420, 10218, 10079, 11097, 10356, 10404, 221F90, PlayerData*, D2InitPlayerData,
   (Unit * ptChar));
F8(STD, D2Common, 10424, 10424, 10424, 10562, 10800, 10860, 10920, 11103, 2221A0, PlayerData*, D2GetPlayerData,
   (Unit * ptChar));
F8(STD, D2Common, 10431, 10431, 10431, 00000, 00000, 00000, 00000, 00000, 00000, DWORD, D2GetDefence, (Unit * ptChar));
F8(STD, D2Common, 10433, 10433, 10433, 00000, 00000, 00000, 00000, 00000, 00000, DWORD, D2GetChanceToBlock,
   (Unit * ptChar, DWORD isLODGame));
F8(STD, D2Common, 10439, 10439, 10439, 10343, 11131, 10729, 10049, 11159, 222E70, DWORD, D2GetMaxGold, (Unit * ptUnit));
F8(STD, D2Common, 00000, 00000, 00000, 10440, 10572, 10481, 11090, 10193, 224690, DWORD, D2Common10572,
   (Unit * ptObject, DWORD value));
F8(STD, D2Common, 00000, 00000, 00000, 10471, 11160, 10866, 10258, 10040, 2222C0, BYTE, D2GetObjectFlags,
   (Unit * ptObject));
F8(STD, D2Common, 00000, 00000, 00000, 10572, 11048, 10150, 10111, 10033, 222300, void, D2SetObjectFlags,
   (Unit * ptObject, BYTE flags));
F8(STD, D2Common, 10487, 10487, 10487, 00000, 00000, 00000, 00000, 00000, 00000, DWORD, D2isInState,
   (Unit * ptChar, DWORD isLODGame));
F8(STD, D2Common, 10518, 10518, 10518, 10109, 10627, 10762, 10551, 10645, 2272B0, void, D2AddPlayerStat,
   (Unit * ptChar, DWORD statID, int amount, DWORD index));//ONLY 1.11b
F8(STD, D2Common, 10519, 10519, 10519, 11092, 10061, 10658, 10973, 10550, 225480, int, D2GetPlayerStat,
   (Unit * ptChar, DWORD statID, DWORD index));//ONLY 1.11b
F8(STD, D2Common, 10521, 10521, 10521, 10733, 10550, 10494, 10587, 10216, 2253B0, int, D2GetPlayerBaseStat,
   (Unit * ptChar, DWORD statID, DWORD index));//ONLY 1.11b
F8(STD, D2Common, 10539, 10539, 10539, 00000, 00000, 00000, 00000, 00000, 00000, DWORD, D2haveDefenceBonus,
   (Unit * ptChar));
F8(STD, D2Common, 10540, 10540, 10540, 00000, 00000, 00000, 00000, 00000, 00000, DWORD, D2haveFireResBonus,
   (Unit * ptChar));
F8(STD, D2Common, 10541, 10541, 10541, 00000, 00000, 00000, 00000, 00000, 00000, DWORD, D2haveColdResBonus,
   (Unit * ptChar));
F8(STD, D2Common, 10542, 10542, 10542, 00000, 00000, 00000, 00000, 00000, 00000, DWORD, D2haveLightResBonus,
   (Unit * ptChar));
F8(STD, D2Common, 10543, 10543, 10543, 00000, 00000, 00000, 00000, 00000, 00000, DWORD, D2havePoisonResBonus,
   (Unit * ptChar));
F8(STD, D2Common, 10546, 10546, 10546, 00000, 00000, 00000, 00000, 00000, 00000, DWORD, D2haveDefenceMalus,
   (Unit * ptChar));
F8(STD, D2Common, 10547, 10547, 10547, 00000, 00000, 00000, 00000, 00000, 00000, DWORD, D2haveFireResMalus,
   (Unit * ptChar));
F8(STD, D2Common, 10548, 10548, 10548, 00000, 00000, 00000, 00000, 00000, 00000, DWORD, D2haveColdResMalus,
   (Unit * ptChar));
F8(STD, D2Common, 10549, 10549, 10549, 00000, 00000, 00000, 00000, 00000, 00000, DWORD, D2haveLightResMalus,
   (Unit * ptChar));
F8(STD, D2Common, 10550, 10550, 10550, 00000, 00000, 00000, 00000, 00000, 00000, DWORD, D2havePoisonResMalus,
   (Unit * ptChar));
F8(STD, D2Common, 10578, 10578, 10578, 10653, 10496, 10244, 10849, 10037, 2122F0, void*, D2CompileTxtFile,
   (DWORD unused, const char *filename, BINField*ptFields, DWORD * ptRecordCount, DWORD recordLength));
F8(STD, D2Common, 10600, 10600, 10600, 10573, 10262, 10887, 10695, 10994, 2335F0, ItemsBIN*, D2GetItemsBIN,
   (DWORD itemID));
F8(STD, D2Common, 10616, 10616, 10616, 10500, 10523, 10774, 10806, 10619, 2372C0, GemsBIN*, D2GetGemsBIN,
   (DWORD gemID));
F8(STD, D2Common, 11232, 11232, 11232, 10746, 10258, 10913, 10783, 10393, 26A1B0, CubeMainBIN*, D2GetCubeMainBIN,
   (DWORD cubemainID));
F8(STD, D2Common, 11233, 11233, 11233, 10639, 11135, 10390, 10675, 10235, 26A200, int, D2GetNbCubeMainBIN, ());
F8(STD, D2Common, 10628, 10628, 10628, 00000, 00000, 00000, 00000, 00000, 00000, DWORD, D2GetNextLevelXP,
   (DWORD classID, DWORD level));
F8(STD, D2Common, 10629, 10629, 10629, 00000, 00000, 00000, 00000, 00000, 00000, DWORD, D2GetMaxLevel, (DWORD classID));
F8(STD, D2Common, 10655, 10655, 10655, 10655, 10309, 10297, 10218, 10694, 111D30, DifficultyLevelsBIN*,
   D2GetDifficultyLevelsBIN, (DWORD difficultyLevel));
F8(STD, D2Common, 10695, 10695, 10695, 10927, 10899, 10276, 10106, 10911, 227E70, DWORD, D2GetItemQuality,
   (Unit * ptItem));
F8(STD, D2Common, 10707, 10707, 10707, 10911, 10303, 10989, 10202, 10458, 2280A0, DWORD, D2TestFlags,
   (Unit * ptUnit, DWORD flags, DWORD line, const char *file));
F8(STD, D2Common, 10717, 10717, 10717, 10898, 10100, 10410, 10086, 10008, 2281E0, DWORD, D2GetItemLevel,
   (Unit * ptItem));
F8(STD, D2Common, 10719, 10719, 10719, 10820, 10505, 10370, 10020, 10810, 228250, BYTE, D2ItemGetPage, (Unit * ptUnit));
F8(STD, D2Common, 10720, 10720, 10720, 10485, 10608, 10223, 10012, 11026, 228280, void, D2ItemSetPage,
   (Unit * ptItem, BYTE page));
F8(STD, D2Common, 10731, 10731, 10731, 11017, 10890, 10231, 10744, 10601, 229BB0, DWORD, D2CheckItemType,
   (Unit * ptItem, DWORD itype));
F8(STD, D2Common, 10732, 10732, 10732, 10692, 10685, 10280, 10620, 10075, 229DA0, int, D2GetUniqueID, (Unit * ptItem));
F8(STD, D2Common, 10734, 10734, 10734, 00000, 00000, 00000, 00000, 00000, 00000, void, D2SetAnim,
   (Unit * ptUnit, int anim));
F8(STD, D2Common, 10619, 10619, 10619, 10687, 10877, 10321, 11032, 10981, 239CB0, int*, D2GetNbRunesBIN,
   ());//return the point on th number
F8(STD, D2Common, 10620, 10620, 10620, 10775, 10296, 10622, 10006, 10405, 239D60, RunesBIN*, D2GetRunesBIN,
   (int runesID));
F8(STD, D2Common, 10881, 10881, 10881, 10956, 11156, 10218, 10987, 10665, 2313E0, DWORD, D2SaveItem,
   (Unit * ptItem, saveBitField * data, DWORD startSize, DWORD p4, DWORD p5, DWORD p6));
F8(STD, D2Common, 10953, 10953, 10953, 10099, 10255, 10210, 10302, 10335, 247280, void, D2SetSkillBaseLevel,
   (Unit * ptChar, DWORD skillID, DWORD slvl, DWORD bRemove, char *, DWORD));
F8(STD, D2Common, 10968, 10968, 10968, 10700, 10109, 10904, 10306, 10007, 2442A0, DWORD, D2GetSkillLevel,
   (Unit * ptChar, SkillData * ptSkill, DWORD includingBonus));
F8(STD, D2Common, 11276, 11276, 11276, 10254, 10074, 10111, 10435, 11081, 246CA0, DWORD, D2GetSkillCost,
   (Unit * ptChar, int skpoints, DWORD skillID, DWORD curSkillLevel));//not 10447
A8(FAST, D2Common, 00000, 00000, 82C80, 15D0, 1800, 1220, 12D0, 17B0, 833E0, CharStatsBIN*, D2GetCharStatsBIN,
   (DWORD charID));
A8(FAST, D2Common, 00000, 00000, 12410, 5D7D0, 1A100, 116C0, 1C020, 5B0E0, 268600, DWORD, D2CompileCubeInput,
   (CubeInput * cubeinput, char * s, DWORD p1, DWORD p2));
A8(FAST, D2Common, 00000, 00000, 2B1A0, 11F0, 1380, 1140, 1300, 1160, 155C90, ItemTypesBIN*, D2GetItemTypesBIN,
   (DWORD itemTypesId));
A8(FAST, D2Common, 00000, 00000, 642B0, 13F0, 12F0, 1540, 17A0, 17E0, 5C4F0, ItemStatCostBIN*, D2GetItemStatCostBIN,
   (DWORD id));
A8(FAST, D2Common, 738A4, 739B4, 84268, 96E0, 98D0, 9900, 9900, B5E0, 117079, void*, D2ReadFile,
   (DWORD mempool, char * filename, DWORD * size, const char*, DWORD));
A8(STD, D2Common, 1F500, 1F510, 29FA0, 71EB0, 32AA0, 7D2A0, 59870, 80C40, 2552E0, void, D2LoadSuperuniques,
   (DWORD mempool));//FASCALL UNTIL 1.10
A8(STD, D2Common, 00000, 00000, 00000, 00000, 00000, 00000, 81EA0, 00000, 00000, InventoryBIN*, D2GetInventoryBIN, ());

A8(FAST, D2Client, 1000, 1000, 1000, 75D00, A9070, BEF70, 2B420, A9480, 788B0, void*, D2LoadImage,
   (const char* filename, DWORD filetype));
A8(FAST, D2Client, 1150, 1150, 1140, 00000, 00000, 00000, 00000, 00000, 78A00, void, D2FreeImage,
   (void * image));//6FAA1140
A8(FAST, D2Client, D640, D630, DB50, 73620, 5E4E0, 79670, 147A0, B6890, 787B0, void, D2SendMsgToAll,
   (BYTE * data));//1.11 and 1.11b by ESI !!
A8(STD, D2Client, 00000, 00000, 15A80, 00000, 00000, 00000, 00000, 00000, 00000, DWORD, D2GetLastMonsterIDFight,
   ());//6FAB5A80
A8(STD, D2Client, 29800, 297F0, 2FD60, 828A0, 89320, 6B280, BCEA0, BF640, A7D00, void, D2PrintStatsPage, ());
A8(FAST, D2Client, 4BB20, 4BB20, 521C0, B8CB0, 21250, 88EA0, 54E10, 2CE40, E4D80, DWORD, D2PrintStat,
   (Unit * ptItem, Stats *
                   ptStats, DWORD statID, DWORD statIndex, DWORD statValue, LPWSTR lpText));//statID=EAX, lpText=ESI 1.11b
A8(FAST, D2Client, 85A60, 84DE0, 80430, 9EEB0, 62070, 8B7A0, BF5F0, 18820, 521C0, LPWSTR, D2SetColorPopup,
   (LPWSTR popupText, DWORD color));//1.11 and 1.11b BY EDI
A8(FAST, D2Client, B4360, B36E0, B5820, 3ACC0, 54210, 31FA0, 88A70, 26270, B9A00, DWORD, D2PlaySound,
   (DWORD id, DWORD, DWORD, DWORD, DWORD));
A8(FAST, D2Client, 00000, 00000, 00000, 73260, 5DE40, 791A0, 143E0, B61F0, 78350, void, D2SendToServerXX,
   (DWORD size, BYTE * data));//by EBX
A8(FAST, D2Client, 88940, 87CC0, 83260, A1F30, 65690, 8EF00, C2790, 1C190, 55F20, void, D2TogglePage,
   (DWORD a, DWORD b, DWORD c));
A8(FAST, D2Client, 00000, 00000, 00000, A6520, 710C0, A6640, 8CD00, 90C10, 89980, void, D2ClickOnStashButton,
   (DWORD x, DWORD y));//BY x=ESI y=EDI
A8(STD, D2Client, 897B0, 88B30, 84110, 9E3B0, 621C0, 8B8F0, BEAF0, 18AA0, 54600, void*, D2LoadBuySelBtn, ());
A8(FAST, D2Client, 00000, 00000, 00000, 00000, 00000, 00000, 00000, 00000, 520C0, void*, D2LoadResImage,
   (const char* filename));
A8(FAST, D2Client, 00000, 00000, 00000, 00000, 00000, 00000, 00000, 00000, 96990, void*, D2FreeResImages, ());
A8(FAST, D2Client, 00000, 00000, 00000, 00000, 00000, 00000, 00000, 00000, 5C850, void*, D2ReceivePacket,
   (DWORD a, DWORD b));
A8(STD, D2Client, 87220, 865A0, 81B70, A35F0, 669F0, 90150, C39E0, 1D3E0, 56EE0, DWORD, D2PrintInterface,
   (void * unknown));

F8(FAST, D2Game, 10059, 10059, 10059, 10039, 10007, 10037, 10049, 10002, 135780, void, D2SetNbPlayers,
   (DWORD nbPlayers));
A8(FAST, D2Game, 00000, 00000, 6C60, E3DA0, E8210, EB060, 49930, E5070, 12C550, void, D2AddClient,
   (DWORD clientID));//BY EAX
A8(STD, D2Game, 00000, 00000, 94E0, E0520, E49A0, A6360, 2AAE0, BC700, 12E860, Game*, D2GetGameByClientID,
   (DWORD clientID));//6FC394E0
A8(FAST, D2Game, 00000, 00000, B0E0, DF250, E36D0, A5080, 29820, BB510, 12DED0, void, D2BroadcastFunction,
   (Game * ptGame, void * fct, void * param));//00DAB0E0
A8(FAST, D2Game, C380, C650, C710, 41420, A0D50, 7D220, 8A3E0, DB780, 13B280, DWORD, D2SendPacket,
   (void * ptNetClient, LPVOID pData, DWORD size));//EAX=ptNetClient [ESP]=pData
A8(FAST, D2Game, D650, D920, DB50, 44D00, A3F20, 802E0, 8D5F0, DD4F0, 13C4A0, void, D2SetSkillBaseLevelOnClient,
   (void * ptClient, Unit * ptChar, DWORD skillID, DWORD sLvl, DWORD bRemove));//by EAX,ESI,EBX
A8(STD, D2Game, 00000, 00000, 00000, 27230, 109F0, AE930, A22E0, 15F40, 16CF40, DWORD, D2LinkPortal,
   (Game * ptGame, Unit * ptObject, DWORD levelEndID, DWORD levelStartID));
A8(FAST, D2Game, 00000, 00000, 128F0, 38D90, 43E60, 11FF0, D2070, B2F70, 15CA40, DWORD, D2VerifIfNotCarry1,
   (Unit * ptItem, ItemsBIN * itemsData, Unit * ptFirstItem));// BY EBX=itemsData EAX=ptFirstItem [ESP]=ptItem
A8(FAST, D2Game, 00000, 00000, 22070, 1090, 1DF0, 11F0, 1280, 1340, 63740, Room*, D2TestPositionInRoom,
   (Room * ptRoom, DWORD x, DWORD y));
A8(FAST, D2Game, 00000, 00000, 3F220, 4ABE0, EC7E0, 40B90, 24950, CDE20, 1A09E0, DWORD, D2SpawnSuperUnique,
   (Game * ptGame, Room *
                   ptRoom, DWORD zero1, DWORD x, DWORD y, DWORD minusOne, DWORD superuniqueID, DWORD zero2));//wrong param
A8(FAST, D2Game, 00000, 00000, 00000, C80F0, EF870, EFB10, EF650, C8D70, 1B2F20, Unit*, D2SpawnMonster,
   (DWORD id, DWORD mode, Game * ptGame, Room * ptRoom, DWORD x, DWORD y, DWORD one, DWORD zero));
A8(STD, D2Game, 00000, 00000, 00000, D6D10, 235C0, D410, 200E0, 59980, 142B40, void, D2Game235C0,
   (Game * ptGame, Room * ptRoom));
A8(FAST, D2Game, 4F100, 4F500, 5B8A0, B9D70, 25D50, 44950, 54810, 3A4C0, 1335E0, DWORD, D2LoadInventory,
   (Game * ptGame, Unit * pChar, saveBitField * pdata, DWORD p2, DWORD maxSize, DWORD p4, DWORD *
                                                                                          ptNbBytesRead));//6FC8B8A0
A8(FAST, D2Game, 7BAE0, 7BFD0, 8BB00, 97620, BEF80, 93650, E03A0, 6DC40, 152F60, Unit*, D2GameGetObject,
   (Game * ptGame, DWORD type, DWORD itemNum));//6FCBBB00
A8(FAST, D2Game, 00000, 00000, 00000, 99760, C09E0, 94E70, E1D90, 6FE10, 155230, Unit*, D2CreateUnit,
   (DWORD type, DWORD id, DWORD x, DWORD y, Game * ptGame, Room * ptRoom, DWORD uk1, DWORD uk2, DWORD uk3));
A8(FAST, D2Game, 00000, 00000, 00000, 9B480, 34920, D1AA0, 70180, 941E0, 165A90, void, D2OpenPandPortal,
   (Game * ptGame, Unit * ptChar));
A8(FAST, D2Game, 00000, 00000, 00000, 9B470, 34910, D1A90, 70170, 941D0, 165AA0, void, D2OpenPandFinalPortal,
   (Game * ptGame, Unit * ptChar));
A8(FAST, D2Game, 00000, 00000, 00000, 75980, D7BD0, CD0F0, 85B60, 4EAD0, 1F78B0, void, D2MephAI,
   (Game * ptGame, Unit * ptMonster, AIParam * args));
A8(FAST, D2Game, 00000, 00000, 00000, 84730, 85AA0, DBE90, A9610, 31920, 1E9170, void, D2DiabloAI,
   (Game * ptGame, Unit * ptMonster, AIParam * args));
A8(FAST, D2Game, 00000, 00000, 00000, EAB20, 2BC80, B3B90, B8610, C8850, 1FCFE0, void, D2BaalAI,
   (Game * ptGame, Unit * ptMonster, AIParam * args));
A8(FAST, D2Game, 00000, 00000, 00000, E92B0, 2A300, B2210, B6C80, C6EC0, 1FD200, void, D2UberBaalAI,
   (Game * ptGame, Unit * ptMonster, AIParam * args));
A8(FAST, D2Game, 00000, 00000, 00000, 70320, D2D70, C2A90, 7B4E0, 49480, 1F81C0, void, D2UberMephAI,
   (Game * ptGame, Unit * ptMonster, AIParam * args));
A8(FAST, D2Game, 00000, 00000, 00000, 7F200, 7FE60, D6250, A39D0, 2C3F0, 1E9DF0, void, D2UberDiabloAI,
   (Game * ptGame, Unit * ptMonster, AIParam * args));
A8(STD, D2Game, 00000, 00000, 89C0, E2390, E66D0, A8090, 2C830, BE660, 12CA10, void, D2SaveGame, (Game * ptGame));
A8(FAST, D2Game, 00000, 00000, 00000, EF580, F0F70, F0D70, F2540, F1800, 1DEB60, void, D2MonsterMove,
   (Game * ptGame, Unit * ptMonster, Unit * target, DWORD two, DWORD x, DWORD y, DWORD one, DWORD zero));
A8(FAST, D2Game, 00000, 00000, 00000, FF1B0, F0DB0, F0BB0, F2380, F1430, 1DEAD0, void, D2MonsterUseSkill,
   (Game * ptGame, Unit * ptMonster, DWORD arg, DWORD skill, Unit * target, DWORD x, DWORD y));
A8(FAST, D2Game, 00000, 00000, 00000, B9340, 25450, 44140, 53F10, 39810, 132240, void, D2SaveSPChar,
   (Game * ptGame, Unit * ptChar, char * name, DWORD arg, DWORD secondPass));

F8(STD, D2Net, 10005, 10005, 10005, 10035, 10020, 10036, 10024, 10015, 12AE50, DWORD, D2SendToServer,
   (DWORD size, DWORD one, void * data));//(DWORD zero, void* data, DWORD size) for 1.10 and before
F8(STD, D2Net, 10006, 10006, 10006, 10018, 10018, 10015, 10002, 10012, 12B330, DWORD, D2SendToClient,
   (DWORD zero, DWORD clientID, void * data, DWORD size));

F8(STD, Fog, 10023, 10023, 10023, 00000, 00000, 00000, 00000, 00000, 00000, void, D2FogAssertOld,
   (const char* ptMessage, DWORD eip, DWORD line));//(STDCALL until 1.10)
F8(FAST, Fog, 00000, 00000, 00000, 10024, 10024, 10024, 10024, 10024, 8A60, void, D2FogAssert,
   (const char* ptMessage, DWORD eip, DWORD line));
F8(FAST, Fog, 10042, 10042, 10042, 10042, 10042, 10042, 10042, 10042, B380, void*, D2FogMemAlloc,
   (DWORD dwMemSize, LPCSTR lpszErrFile, DWORD ErrLine, DWORD Zero));
F8(FAST, Fog, 10043, 10043, 10043, 10043, 10043, 10043, 10043, 10043, B3C0, void*, D2FogMemDeAlloc,
   (void * ptMemLoc, LPCSTR lpszErrFile, DWORD ErrLine, DWORD Zero));
F8(FAST, Fog, 10045, 10045, 10045, 10045, 10045, 10045, 10045, 10045, B430, void*, D2AllocMem,
   (DWORD, DWORD dwMemSize, LPCSTR lpszErrFile, DWORD ErrLine, DWORD Zero));
F8(FAST, Fog, 10046, 10046, 10046, 10046, 10046, 10046, 10046, 10046, B480, void*, D2FreeMem,
   (DWORD, void * ptMemLoc, LPCSTR lpszErrFile, DWORD ErrLine, DWORD Zero));
F8(FAST, Fog, 10102, 10102, 10102, 10102, 10102, 10102, 10102, 10102, 68E0, DWORD, D2MPQOpenFile,
   (char * ptPath, void * *buf));
F8(FAST, Fog, 10103, 10103, 10103, 10103, 10103, 10103, 10103, 10103, 68F0, DWORD, D2MPQCloseFile, (void * mpqfile));
F8(FAST, Fog, 10104, 10104, 10104, 10104, 10104, 10104, 10104, 10104, 6900, DWORD, D2MPQReadFile,
   (void * mpqfile, BYTE * buffer, DWORD nbToRead, DWORD * nbRead, DWORD, DWORD, DWORD));
F8(FAST, Fog, 10105, 10105, 10105, 10105, 10105, 10105, 10105, 10105, 6930, DWORD, D2MPQGetSizeFile,
   (void * mpqfile, DWORD * toReset));
F8(FAST, Fog, 10115, 10115, 10115, 10115, 10115, 10115, 10115, 10115, 7050, void, D2FogGetSavePath,
   (char * ptPath, DWORD maxsize));
F8(FAST, Fog, 10116, 10116, 10116, 10116, 10116, 10116, 10116, 10116, 6BA0, void, D2FogGetInstallPath,
   (char * ptPath, DWORD maxsize));
F8(STD, Fog, 10212, 10212, 10212, 10212, 10212, 10212, 10212, 10212, 2BD0B0, void, D2Fog10212, (DWORD unknow));
F8(STD, Fog, 00000, 00000, 00000, 10265, 10265, 10265, 10265, 10265, 8090, int, D2GetInstructionPointer, ());
F8(FAST, D2Lang, 10003, 10003, 10003, 10002, 10004, 10010, 10011, 10011, 124E20, LPWSTR, D2GetStringFromString,
   (const char* ptString));//6FC13BC0 LAutour
F8(FAST, D2Lang, 10004, 10004, 10004, 10005, 10000, 10005, 10003, 10004, 124A30, LPWSTR, D2GetStringFromIndex,
   (WORD dwIndexNum));
F8(STD, D2Lang, 10007, 10007, 10007, 10009, 10013, 10002, 10009, 10001, 125150, DWORD, D2GetLang, ());//14b  00522A20
F8(STD, D2Lang, 10010, 10010, 10010, 00000, 00000, 00000, 00000, 00000, 00000, DWORD, D2PrintBigNumber,
   (LPWSTR ptBuf, DWORD number, DWORD size));//6FC14210
F8(STD, Storm, 268, 268, 268, 268, 268, 268, 268, 268, 192F0, DWORD, D2StormMPQOpenFile,
   (DWORD zero, LPCSTR fileName, DWORD dwSearchScope, void * *buffer))
F8(STD, Storm, 503, 503, 503, 503, 503, 503, 503, 503, 13750, void, D2Storm503, (DWORD, DWORD, DWORD));
F8(STD, Storm, 511, 511, 511, 511, 511, 511, 511, 511, 20290, void, D2FreeWinMessage, (sWinMessage * msg));


F8(STD, D2gfx, 10005, 10005, 10005, 10000, 10063, 10043, 10031, 10012, F5160, DWORD, D2GetResolution, ());
F8(STD, D2gfx, 10055, 10055, 10055, 10028, 10000, 10062, 10014, 10028, F6300, void, D2FillArea,
   (DWORD x1, DWORD y1, DWORD x2, DWORD y2, DWORD color, DWORD transTbl));
F8(STD, D2gfx, 10072, 10072, 10072, 10047, 10044, 10024, 10041, 10042, F6480, void, D2PrintImage,
   (sDrawImageInfo * data, DWORD x, DWORD y, DWORD p4, DWORD p5, DWORD p6));


F8(FAST, D2Win, 10046, 10046, 10046, 10061, 10075, 10015, 10022, 10051, FCFF0, void, D2PrintLineOnTextBox,
   (void * screen, char * s, DWORD color));
F8(FAST, D2Win, 10117, 10117, 10117, 10020, 10064, 10001, 10150, 10076, 102320, void, D2PrintString,
   (LPWSTR s, DWORD x, DWORD y, DWORD color, DWORD bfalse));
F8(FAST, D2Win, 10121, 10121, 10121, 10034, 10128, 10132, 10028, 10150, 101820, DWORD, D2GetPixelLen, (LPWSTR s));
F8(FAST, D2Win, 10127, 10127, 10127, 10141, 10170, 10010, 10184, 10047, 102EF0, DWORD, D2SetFont, (DWORD fontID));
F8(FAST, D2Win, 10129, 10129, 10129, 10118, 10039, 10031, 10085, 10137, 102280, void, D2PrintPopup,
   (LPWSTR s, DWORD x, DWORD y, DWORD color, DWORD center));
F8(FAST, D2Win, 10131, 10131, 10131, 00000, 00000, 00000, 00000, 00000, 00000, void, D2GetPixelRect,
   (LPWSTR s, DWORD * x, DWORD * y));//6F8AB260
F8(FAST, D2Win, 10132, 10132, 10132, 00000, 00000, 00000, 00000, 00000, 00000, DWORD, D2PrintTextPopup,
   (LPWSTR s, DWORD x, DWORD y, DWORD uk, DWORD type, DWORD color));//6F8AB080
F8(STD, D2Win, 10017, 10017, 10017, 10147, 10113, 10098, 10098, 10164, F93C0, void*, D2CreateTextBox, (DWORD * data));

F8(STD, D2CMP, 10032, 10032, 10032, 10021, 10014, 10106, 10065, 10020, 201A50, DWORD, D2CMP10014, (void * image));


//ONLY UNTIL 1.10 :
A8(FAST, D2Client, BA00, B9F0, C080, 00000, 00000, 00000, 00000, 00000, 00000, DWORD, D2isLODGame, ());//6FAAC080
A8(FAST, D2Client, 00000, 00000, C090, 00000, 00000, 00000, 00000, 00000, 00000, BYTE, D2GetDifficultyLevel,
   ());//6FAAC090  1.09 should be BA10 (b) BA00 (d)
A8(STD, D2Client, B6670, B59F0, B7BC0, 00000, 00000, 00000, 00000, 00000, 00000, DWORD, D2GetMouseX, ());//6FB57BC0
A8(STD, D2Client, B6680, B5A00, B7BD0, 00000, 00000, 00000, 00000, 00000, 00000, DWORD, D2GetMouseY, ());//6FB57BD0
A8(STD, D2Client, 8DC40, 8CFC0, 883D0, 00000, 00000, 00000, 00000, 00000, 63DD0, Unit*, D2GetClientPlayer,
   ());//6FB283D0
A8(FAST, D2Client, B920, B910, BF60, 00000, 00000, 00000, 00000, 00000, 4DA70, void, D2CleanStatMouseUp, ());//6FAABF60
A8(FAST, D2Client, D210, D200, D990, 00000, 00000, 00000, 00000, 00000, 00000, void, D2SendToServer3,
   (BYTE type, WORD p));//6FAAD990
A8(FAST, D2Game, 7C2C0, 7C7B0, 8C2E0, 00000, 00000, 00000, 00000, 00000, 1531C0, NetClient*, D2GetClient,
   (Unit * ptUnit, char * lpszErrFile, DWORD ErrLine));//6FCBC2E0


C8(D2Client, D50E8, D40E0, D40F0, F5C60, F4FC8, DC6E4, DBC4C, F7038, 311470, DWORD, ResolutionY);//0x258 = 600
C8(D2Client, D50EC, D40E4, D40F4, F5C5C, F4FC4, DC6E0, DBC48, F7034, 31146C, DWORD, ResolutionX);//0x320 = 800
C8(D2Client, 125AD8, 124958, 11A74C, 11BD28, 11BEFC, 11BD2C, 11B9A4, 11D358, 3A285C, DWORD,
   NegWindowStartY);//0xFFFFFFC4 = -60
C8(D2Client, 125AD4, 124954, 11A748, 11BD24, 11BEF8, 11BD28, 11B9A0, 11D354, 3A2858, DWORD, WindowStartX);//0x50 = 80
C8(D2Game, F2A80, F2918, 113FB8, 111718, 1115E0, 1105E0, 1107B8, 1105E0, 4842A8, NetClient*, ClientTable);
C8(D2Client, 000000, 000000, 000000, FB3F4, 11A2F4, 10330C, 119854, 1087B4, 3A04F4, DWORD, IsLodGame);
C8(D2Client, 000000, 000000, 10795C, 11BFB8, 11C2A8, 11BFF4, 000000, 000000, 000000, BYTE, DifficultyLevel);
C8(D2Client, 000000, 000000, 000000, 10A40C, 11B414, 101634, 11B824, 11C94C, 3A6AAC, DWORD, MouseY);//0x258 = 600
C8(D2Client, 000000, 000000, 000000, 10A410, 11B418, 101638, 11B828, 11C950, 3A6AB0, DWORD, MouseX);//0x320 = 800
C8(D2Client, 000000, 000000, 000000, 11C4F0, 11C1E0, 11C3D0, 11BBFC, 11D050, 3A6A70, Unit*, ptClientChar);
C8(D2Client, 11E0F4, 11CF54, 112D04, 11B9A8, 11BB30, 11BF48, 11C028, 11CAA4, 3BB5E8, DWORD, InputCommandLen);
C8(D2Client, 11CE50, 11BCB0, 111A58, 11C590, 11D590, 11FC40, 11EC80, 11D650, 3BB638, WCHAR, InputCommand);

C8(D2Client, DB918, DA828, 000000, 000000, 000000, 000000, 000000, 000000, 000000, DWORD, NbStatDesc);
C8(D2Client, DAF98, D9EA8, 000000, 000000, 000000, 000000, 000000, 000000, 000000, DWORD, StatDescTable);
DataTables *SgptDataTables;

#undef F8
#undef A8
#undef C8
#undef D2S
#undef D2F
#undef E2S
#undef E2F
#undef E2C

#define D2S(F, I, R, N, P)    typedef R (STDCALL  *T##N) P; T##N N;

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
    int playerData = V8_(version_D2Common, 0x5D, 0x5D, 0x5D, 0x49, 0x49, 0x49, 0x49, 0x49, 0x48);
    shifting.ptPYPlayerData = *(DWORD *) ((DWORD) D2InitPlayerData + playerData);
    shifting.ptSpecificData =
            V8_(version_D2Common, 0x70, 0x70, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14);
    shifting.ptGame = get_offset_or_default(
            version_D2Common, 0xA4, 0xA4, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80);
    shifting.ptClientGame = V8(D2Common, 170, 194, 1A8, 1A8, 1A8, 1A8, 1A8, 1A8, 1A8);
    shifting.ptInventory = V8(D2Common, 84, 84, 60, 60, 60, 60, 60, 60, 60);
    shifting.ptSkills = V8(D2Common, CC, CC, A8, A8, A8, A8, A8, A8, A8);
    shifting.ptImage = V8(D2Common, 04, 04, 04, 08, 08, 3C, 34, 34, 34);
    shifting.ptFrame = V8(D2Common, 08, 08, 08, 44, 44, 40, 00, 00, 00);
}

void initD2functions() {

#define F8(X, Z, A, B, C, D, E, F, G, H, I, R, N, P) if (version_##Z > V113d) { N = (T##N)R8(Z,A,B,C,D,E,F,G,H,I); } else setFctAddr((DWORD*)&N, (HMODULE)offset_##Z, (LPCSTR)(version_##Z == V113d? H : (version_##Z == V113c? G : (version_##Z == V112? F : (version_##Z == V111b? E : (version_##Z == V111? D : (version_##Z == V110? C : (version_##Z == V109d? B : A))))))));
#define A8(X, Z, A, B, C, D, E, F, G, H, I, R, N, P) N = (T##N)R8(Z,A,B,C,D,E,F,G,H,I);
#define C8(Z, A, B, C, D, E, F, G, H, I, T, N)       pt##N = (T*)R8(Z,A,B,C,D,E,F,G,H,I);

    /* Warning, all this code is used for macro replacement only */

    F8(STD, D2Common, 00000, 00000, 00000, 10188, 11084, 11109, 10346, 10907, 21AED0, DWORD, D2Common11084,
       (Room * ptRoom, DWORD zero));
    F8(STD, D2Common, 10057, 10057, 10057, 10332, 11021, 10511, 10826, 10691, 21A1B0, DWORD, D2GetLevelID,
       (Room * ptRoom));
    F8(STD, D2Common, 10138, 10138, 10138, 10623, 10491, 11043, 10654, 10716, 24E810, Room*, D2GetDropRoom,
       (Room * ptRoom, Position *, Position *, DWORD, DWORD, DWORD, DWORD));
    F8(STD, D2Common, 10242, 10242, 10242, 00000, 00000, 00000, 00000, 00000, 00000, Unit*, D2Common10242,
       (Inventory * ptInventory, Unit * ptItem, DWORD bIsClient));
    F8(STD, D2Common, 10246, 10246, 10246, 10855, 10813, 10289, 10133, 10402, 23B950, Unit*, D2CanPutItemInInv,
       (Inventory * ptInventory, Unit * ptItem, DWORD p3, DWORD zero, Unit * ptUnit, const char *file, DWORD line));
    F8(STD, D2Common, 10243, 10243, 10243, 10461, 10827, 10936, 10646, 10490, 23AD90, Unit*, D2InvRemoveItem,
       (Inventory * ptInventory, Unit * ptItem));
    F8(STD, D2Common, 10249, 10249, 10249, 10880, 11068, 10436, 11107, 10963, 23BCC0, DWORD, D2InvAddItem,
       (Inventory * ptInventory, Unit *
                                 ptItem, DWORD posX, DWORD posY, DWORD vValueC, DWORD bIsClient, BYTE page));//result : boolean 0=echec  ; vValueC = 0 for Game.dll, 1 for Clientdll
    F8(STD, D2Common, 10250, 10250, 10250, 00000, 00000, 00000, 00000, 00000, 00000, DWORD, D2Common10250,
       (const char* file, DWORD line, Inventory* ptInventory, DWORD posX, DWORD posY, DWORD vValueC, DWORD bIsClient, BYTE page));// result : boolean 0=echec  ; vValueC = 0 for Game.dll, 1 for Clientdll
    F8(STD, D2Common, 10273, 10273, 10273, 00000, 00000, 00000, 00000, 00000, 00000, DWORD, D2Common10273,
       (Inventory * ptInventory, void * unknown));
    F8(STD, D2Common, 10277, 10277, 10277, 10402, 10535, 11151, 10460, 11040, 23B2C0, Unit*, D2InventoryGetFirstItem,
       (Inventory * ptInventory));
    F8(STD, D2Common, 10304, 10304, 10304, 10934, 11140, 10770, 10464, 10879, 23DFA0, Unit*, D2UnitGetNextItem,
       (Unit * ptItem));
    F8(STD, D2Common, 10305, 10305, 10305, 11095, 10748, 10852, 11147, 10897, 23DFD0, Unit*, D2GetRealItem,
       (Unit * ptUnit));
    F8(STD, D2Common, 10326, 10326, 00000, 00000, 00000, 00000, 00000, 00000, 00000, DWORD, D2GetPosX,
       (Unit * ptUnit));//NOT IN 1.10
    F8(STD, D2Common, 10329, 10329, 00000, 00000, 00000, 00000, 00000, 00000, 00000, DWORD, D2GetPosY,
       (Unit * ptUnit));//NOT IN 1.10
    F8(STD, D2Common, 10332, 10332, 10332, 11080, 10056, 10543, 10141, 11166, 220870, void, D2GetPosition,
       (Unit * ptUnit, Position * pos));
    F8(STD, D2Common, 10339, 10339, 10339, 10455, 10864, 10941, 11060, 11025, 223460, DWORD, D2GetMaxGoldBank,
       (Unit * ptUnit));
    F8(STD, D2Common, 10342, 10342, 10342, 10172, 10933, 10366, 10331, 10846, 220BB0, Room*, D2GetRoom,
       (Unit * ptUnit));
    F8(STD, D2Common, 10420, 10420, 10420, 10218, 10079, 11097, 10356, 10404, 221F90, PlayerData*, D2InitPlayerData,
       (Unit * ptChar));
    F8(STD, D2Common, 10424, 10424, 10424, 10562, 10800, 10860, 10920, 11103, 2221A0, PlayerData*, D2GetPlayerData,
       (Unit * ptChar));
    F8(STD, D2Common, 10431, 10431, 10431, 00000, 00000, 00000, 00000, 00000, 00000, DWORD, D2GetDefence,
       (Unit * ptChar));
    F8(STD, D2Common, 10433, 10433, 10433, 00000, 00000, 00000, 00000, 00000, 00000, DWORD, D2GetChanceToBlock,
       (Unit * ptChar, DWORD isLODGame));
    F8(STD, D2Common, 10439, 10439, 10439, 10343, 11131, 10729, 10049, 11159, 222E70, DWORD, D2GetMaxGold,
       (Unit * ptUnit));
    F8(STD, D2Common, 00000, 00000, 00000, 10440, 10572, 10481, 11090, 10193, 224690, DWORD, D2Common10572,
       (Unit * ptObject, DWORD value));
    F8(STD, D2Common, 00000, 00000, 00000, 10471, 11160, 10866, 10258, 10040, 2222C0, BYTE, D2GetObjectFlags,
       (Unit * ptObject));
    F8(STD, D2Common, 00000, 00000, 00000, 10572, 11048, 10150, 10111, 10033, 222300, void, D2SetObjectFlags,
       (Unit * ptObject, BYTE flags));
    F8(STD, D2Common, 10487, 10487, 10487, 00000, 00000, 00000, 00000, 00000, 00000, DWORD, D2isInState,
       (Unit * ptChar, DWORD isLODGame));
    F8(STD, D2Common, 10518, 10518, 10518, 10109, 10627, 10762, 10551, 10645, 2272B0, void, D2AddPlayerStat,
       (Unit * ptChar, DWORD statID, int amount, DWORD index));//ONLY 1.11b
    F8(STD, D2Common, 10519, 10519, 10519, 11092, 10061, 10658, 10973, 10550, 225480, int, D2GetPlayerStat,
       (Unit * ptChar, DWORD statID, DWORD index));//ONLY 1.11b
    F8(STD, D2Common, 10521, 10521, 10521, 10733, 10550, 10494, 10587, 10216, 2253B0, int, D2GetPlayerBaseStat,
       (Unit * ptChar, DWORD statID, DWORD index));//ONLY 1.11b
    F8(STD, D2Common, 10539, 10539, 10539, 00000, 00000, 00000, 00000, 00000, 00000, DWORD, D2haveDefenceBonus,
       (Unit * ptChar));
    F8(STD, D2Common, 10540, 10540, 10540, 00000, 00000, 00000, 00000, 00000, 00000, DWORD, D2haveFireResBonus,
       (Unit * ptChar));
    F8(STD, D2Common, 10541, 10541, 10541, 00000, 00000, 00000, 00000, 00000, 00000, DWORD, D2haveColdResBonus,
       (Unit * ptChar));
    F8(STD, D2Common, 10542, 10542, 10542, 00000, 00000, 00000, 00000, 00000, 00000, DWORD, D2haveLightResBonus,
       (Unit * ptChar));
    F8(STD, D2Common, 10543, 10543, 10543, 00000, 00000, 00000, 00000, 00000, 00000, DWORD, D2havePoisonResBonus,
       (Unit * ptChar));
    F8(STD, D2Common, 10546, 10546, 10546, 00000, 00000, 00000, 00000, 00000, 00000, DWORD, D2haveDefenceMalus,
       (Unit * ptChar));
    F8(STD, D2Common, 10547, 10547, 10547, 00000, 00000, 00000, 00000, 00000, 00000, DWORD, D2haveFireResMalus,
       (Unit * ptChar));
    F8(STD, D2Common, 10548, 10548, 10548, 00000, 00000, 00000, 00000, 00000, 00000, DWORD, D2haveColdResMalus,
       (Unit * ptChar));
    F8(STD, D2Common, 10549, 10549, 10549, 00000, 00000, 00000, 00000, 00000, 00000, DWORD, D2haveLightResMalus,
       (Unit * ptChar));
    F8(STD, D2Common, 10550, 10550, 10550, 00000, 00000, 00000, 00000, 00000, 00000, DWORD, D2havePoisonResMalus,
       (Unit * ptChar));
    F8(STD, D2Common, 10578, 10578, 10578, 10653, 10496, 10244, 10849, 10037, 2122F0, void*, D2CompileTxtFile,
       (DWORD unused, const char *filename, BINField*ptFields, DWORD * ptRecordCount, DWORD recordLength));
    F8(STD, D2Common, 10600, 10600, 10600, 10573, 10262, 10887, 10695, 10994, 2335F0, ItemsBIN*, D2GetItemsBIN,
       (DWORD itemID));
    F8(STD, D2Common, 10616, 10616, 10616, 10500, 10523, 10774, 10806, 10619, 2372C0, GemsBIN*, D2GetGemsBIN,
       (DWORD gemID));
    F8(STD, D2Common, 11232, 11232, 11232, 10746, 10258, 10913, 10783, 10393, 26A1B0, CubeMainBIN*, D2GetCubeMainBIN,
       (DWORD cubemainID));
    F8(STD, D2Common, 11233, 11233, 11233, 10639, 11135, 10390, 10675, 10235, 26A200, int, D2GetNbCubeMainBIN, ());
    F8(STD, D2Common, 10628, 10628, 10628, 00000, 00000, 00000, 00000, 00000, 00000, DWORD, D2GetNextLevelXP,
       (DWORD classID, DWORD level));
    F8(STD, D2Common, 10629, 10629, 10629, 00000, 00000, 00000, 00000, 00000, 00000, DWORD, D2GetMaxLevel,
       (DWORD classID));
    F8(STD, D2Common, 10655, 10655, 10655, 10655, 10309, 10297, 10218, 10694, 111D30, DifficultyLevelsBIN*,
       D2GetDifficultyLevelsBIN, (DWORD difficultyLevel));
    F8(STD, D2Common, 10695, 10695, 10695, 10927, 10899, 10276, 10106, 10911, 227E70, DWORD, D2GetItemQuality,
       (Unit * ptItem));
    F8(STD, D2Common, 10707, 10707, 10707, 10911, 10303, 10989, 10202, 10458, 2280A0, DWORD, D2TestFlags,
       (Unit * ptUnit, DWORD flags, DWORD line, const char *file));
    F8(STD, D2Common, 10717, 10717, 10717, 10898, 10100, 10410, 10086, 10008, 2281E0, DWORD, D2GetItemLevel,
       (Unit * ptItem));
    F8(STD, D2Common, 10719, 10719, 10719, 10820, 10505, 10370, 10020, 10810, 228250, BYTE, D2ItemGetPage,
       (Unit * ptUnit));
    F8(STD, D2Common, 10720, 10720, 10720, 10485, 10608, 10223, 10012, 11026, 228280, void, D2ItemSetPage,
       (Unit * ptItem, BYTE page));
    F8(STD, D2Common, 10731, 10731, 10731, 11017, 10890, 10231, 10744, 10601, 229BB0, DWORD, D2CheckItemType,
       (Unit * ptItem, DWORD itype));
    F8(STD, D2Common, 10732, 10732, 10732, 10692, 10685, 10280, 10620, 10075, 229DA0, int, D2GetUniqueID,
       (Unit * ptItem));
    F8(STD, D2Common, 10734, 10734, 10734, 00000, 00000, 00000, 00000, 00000, 00000, void, D2SetAnim,
       (Unit * ptUnit, int anim));
    F8(STD, D2Common, 10619, 10619, 10619, 10687, 10877, 10321, 11032, 10981, 239CB0, int*, D2GetNbRunesBIN,
       ());//return the point on th number
    F8(STD, D2Common, 10620, 10620, 10620, 10775, 10296, 10622, 10006, 10405, 239D60, RunesBIN*, D2GetRunesBIN,
       (int runesID));
    F8(STD, D2Common, 10881, 10881, 10881, 10956, 11156, 10218, 10987, 10665, 2313E0, DWORD, D2SaveItem,
       (Unit * ptItem, saveBitField * data, DWORD startSize, DWORD p4, DWORD p5, DWORD p6));
    F8(STD, D2Common, 10953, 10953, 10953, 10099, 10255, 10210, 10302, 10335, 247280, void, D2SetSkillBaseLevel,
       (Unit * ptChar, DWORD skillID, DWORD slvl, DWORD bRemove, char *, DWORD));
    F8(STD, D2Common, 10968, 10968, 10968, 10700, 10109, 10904, 10306, 10007, 2442A0, DWORD, D2GetSkillLevel,
       (Unit * ptChar, SkillData * ptSkill, DWORD includingBonus));
    F8(STD, D2Common, 11276, 11276, 11276, 10254, 10074, 10111, 10435, 11081, 246CA0, DWORD, D2GetSkillCost,
       (Unit * ptChar, int skpoints, DWORD skillID, DWORD curSkillLevel));//not 10447
    A8(FAST, D2Common, 00000, 00000, 82C80, 15D0, 1800, 1220, 12D0, 17B0, 833E0, CharStatsBIN*, D2GetCharStatsBIN,
       (DWORD charID));
    A8(FAST, D2Common, 00000, 00000, 12410, 5D7D0, 1A100, 116C0, 1C020, 5B0E0, 268600, DWORD, D2CompileCubeInput,
       (CubeInput * cubeinput, char * s, DWORD p1, DWORD p2));
    A8(FAST, D2Common, 00000, 00000, 2B1A0, 11F0, 1380, 1140, 1300, 1160, 155C90, ItemTypesBIN*, D2GetItemTypesBIN,
       (DWORD itemTypesId));
    A8(FAST, D2Common, 00000, 00000, 642B0, 13F0, 12F0, 1540, 17A0, 17E0, 5C4F0, ItemStatCostBIN*, D2GetItemStatCostBIN,
       (DWORD id));
    A8(FAST, D2Common, 738A4, 739B4, 84268, 96E0, 98D0, 9900, 9900, B5E0, 117079, void*, D2ReadFile,
       (DWORD mempool, char * filename, DWORD * size, const char*, DWORD));
    A8(STD, D2Common, 1F500, 1F510, 29FA0, 71EB0, 32AA0, 7D2A0, 59870, 80C40, 2552E0, void, D2LoadSuperuniques,
       (DWORD mempool));//FASCALL UNTIL 1.10
    A8(STD, D2Common, 00000, 00000, 00000, 00000, 00000, 00000, 81EA0, 00000, 00000, InventoryBIN*, D2GetInventoryBIN,
       ());

    A8(FAST, D2Client, 1000, 1000, 1000, 75D00, A9070, BEF70, 2B420, A9480, 788B0, void*, D2LoadImage,
       (const char* filename, DWORD filetype));
    A8(FAST, D2Client, 1150, 1150, 1140, 00000, 00000, 00000, 00000, 00000, 78A00, void, D2FreeImage,
       (void * image));//6FAA1140
    A8(FAST, D2Client, D640, D630, DB50, 73620, 5E4E0, 79670, 147A0, B6890, 787B0, void, D2SendMsgToAll,
       (BYTE * data));//1.11 and 1.11b by ESI !!
    A8(STD, D2Client, 00000, 00000, 15A80, 00000, 00000, 00000, 00000, 00000, 00000, DWORD, D2GetLastMonsterIDFight,
       ());//6FAB5A80
    A8(STD, D2Client, 29800, 297F0, 2FD60, 828A0, 89320, 6B280, BCEA0, BF640, A7D00, void, D2PrintStatsPage, ());
    A8(FAST, D2Client, 4BB20, 4BB20, 521C0, B8CB0, 21250, 88EA0, 54E10, 2CE40, E4D80, DWORD, D2PrintStat,
       (Unit * ptItem, Stats *
                       ptStats, DWORD statID, DWORD statIndex, DWORD statValue, LPWSTR lpText));//statID=EAX, lpText=ESI 1.11b
    A8(FAST, D2Client, 85A60, 84DE0, 80430, 9EEB0, 62070, 8B7A0, BF5F0, 18820, 521C0, LPWSTR, D2SetColorPopup,
       (LPWSTR popupText, DWORD color));//1.11 and 1.11b BY EDI
    A8(FAST, D2Client, B4360, B36E0, B5820, 3ACC0, 54210, 31FA0, 88A70, 26270, B9A00, DWORD, D2PlaySound,
       (DWORD id, DWORD, DWORD, DWORD, DWORD));
    A8(FAST, D2Client, 00000, 00000, 00000, 73260, 5DE40, 791A0, 143E0, B61F0, 78350, void, D2SendToServerXX,
       (DWORD size, BYTE * data));//by EBX
    A8(FAST, D2Client, 88940, 87CC0, 83260, A1F30, 65690, 8EF00, C2790, 1C190, 55F20, void, D2TogglePage,
       (DWORD a, DWORD b, DWORD c));
    A8(FAST, D2Client, 00000, 00000, 00000, A6520, 710C0, A6640, 8CD00, 90C10, 89980, void, D2ClickOnStashButton,
       (DWORD x, DWORD y));//BY x=ESI y=EDI
    A8(STD, D2Client, 897B0, 88B30, 84110, 9E3B0, 621C0, 8B8F0, BEAF0, 18AA0, 54600, void*, D2LoadBuySelBtn, ());
    A8(FAST, D2Client, 00000, 00000, 00000, 00000, 00000, 00000, 00000, 00000, 520C0, void*, D2LoadResImage,
       (const char* filename));
    A8(FAST, D2Client, 00000, 00000, 00000, 00000, 00000, 00000, 00000, 00000, 96990, void*, D2FreeResImages, ());
    A8(FAST, D2Client, 00000, 00000, 00000, 00000, 00000, 00000, 00000, 00000, 5C850, void*, D2ReceivePacket,
       (DWORD a, DWORD b));
    A8(STD, D2Client, 87220, 865A0, 81B70, A35F0, 669F0, 90150, C39E0, 1D3E0, 56EE0, DWORD, D2PrintInterface,
       (void * unknown));

    F8(FAST, D2Game, 10059, 10059, 10059, 10039, 10007, 10037, 10049, 10002, 135780, void, D2SetNbPlayers,
       (DWORD nbPlayers));
    A8(FAST, D2Game, 00000, 00000, 6C60, E3DA0, E8210, EB060, 49930, E5070, 12C550, void, D2AddClient,
       (DWORD clientID));//BY EAX
    A8(STD, D2Game, 00000, 00000, 94E0, E0520, E49A0, A6360, 2AAE0, BC700, 12E860, Game*, D2GetGameByClientID,
       (DWORD clientID));//6FC394E0
    A8(FAST, D2Game, 00000, 00000, B0E0, DF250, E36D0, A5080, 29820, BB510, 12DED0, void, D2BroadcastFunction,
       (Game * ptGame, void * fct, void * param));//00DAB0E0
    A8(FAST, D2Game, C380, C650, C710, 41420, A0D50, 7D220, 8A3E0, DB780, 13B280, DWORD, D2SendPacket,
       (void * ptNetClient, LPVOID pData, DWORD size));//EAX=ptNetClient [ESP]=pData
    A8(FAST, D2Game, D650, D920, DB50, 44D00, A3F20, 802E0, 8D5F0, DD4F0, 13C4A0, void, D2SetSkillBaseLevelOnClient,
       (void * ptClient, Unit * ptChar, DWORD skillID, DWORD sLvl, DWORD bRemove));//by EAX,ESI,EBX
    A8(STD, D2Game, 00000, 00000, 00000, 27230, 109F0, AE930, A22E0, 15F40, 16CF40, DWORD, D2LinkPortal,
       (Game * ptGame, Unit * ptObject, DWORD levelEndID, DWORD levelStartID));
    A8(FAST, D2Game, 00000, 00000, 128F0, 38D90, 43E60, 11FF0, D2070, B2F70, 15CA40, DWORD, D2VerifIfNotCarry1,
       (Unit * ptItem, ItemsBIN * itemsData, Unit * ptFirstItem));// BY EBX=itemsData EAX=ptFirstItem [ESP]=ptItem
    A8(FAST, D2Game, 00000, 00000, 22070, 1090, 1DF0, 11F0, 1280, 1340, 63740, Room*, D2TestPositionInRoom,
       (Room * ptRoom, DWORD x, DWORD y));
    A8(FAST, D2Game, 00000, 00000, 3F220, 4ABE0, EC7E0, 40B90, 24950, CDE20, 1A09E0, DWORD, D2SpawnSuperUnique,
       (Game * ptGame, Room *
                       ptRoom, DWORD zero1, DWORD x, DWORD y, DWORD minusOne, DWORD superuniqueID, DWORD zero2));//wrong param
    A8(FAST, D2Game, 00000, 00000, 00000, C80F0, EF870, EFB10, EF650, C8D70, 1B2F20, Unit*, D2SpawnMonster,
       (DWORD id, DWORD mode, Game * ptGame, Room * ptRoom, DWORD x, DWORD y, DWORD one, DWORD zero));
    A8(STD, D2Game, 00000, 00000, 00000, D6D10, 235C0, D410, 200E0, 59980, 142B40, void, D2Game235C0,
       (Game * ptGame, Room * ptRoom));
    A8(FAST, D2Game, 4F100, 4F500, 5B8A0, B9D70, 25D50, 44950, 54810, 3A4C0, 1335E0, DWORD, D2LoadInventory,
       (Game * ptGame, Unit * pChar, saveBitField * pdata, DWORD p2, DWORD maxSize, DWORD p4, DWORD *
                                                                                              ptNbBytesRead));//6FC8B8A0
    A8(FAST, D2Game, 7BAE0, 7BFD0, 8BB00, 97620, BEF80, 93650, E03A0, 6DC40, 152F60, Unit*, D2GameGetObject,
       (Game * ptGame, DWORD type, DWORD itemNum));//6FCBBB00
    A8(FAST, D2Game, 00000, 00000, 00000, 99760, C09E0, 94E70, E1D90, 6FE10, 155230, Unit*, D2CreateUnit,
       (DWORD type, DWORD id, DWORD x, DWORD y, Game * ptGame, Room * ptRoom, DWORD uk1, DWORD uk2, DWORD uk3));
    A8(FAST, D2Game, 00000, 00000, 00000, 9B480, 34920, D1AA0, 70180, 941E0, 165A90, void, D2OpenPandPortal,
       (Game * ptGame, Unit * ptChar));
    A8(FAST, D2Game, 00000, 00000, 00000, 9B470, 34910, D1A90, 70170, 941D0, 165AA0, void, D2OpenPandFinalPortal,
       (Game * ptGame, Unit * ptChar));
    A8(FAST, D2Game, 00000, 00000, 00000, 75980, D7BD0, CD0F0, 85B60, 4EAD0, 1F78B0, void, D2MephAI,
       (Game * ptGame, Unit * ptMonster, AIParam * args));
    A8(FAST, D2Game, 00000, 00000, 00000, 84730, 85AA0, DBE90, A9610, 31920, 1E9170, void, D2DiabloAI,
       (Game * ptGame, Unit * ptMonster, AIParam * args));
    A8(FAST, D2Game, 00000, 00000, 00000, EAB20, 2BC80, B3B90, B8610, C8850, 1FCFE0, void, D2BaalAI,
       (Game * ptGame, Unit * ptMonster, AIParam * args));
    A8(FAST, D2Game, 00000, 00000, 00000, E92B0, 2A300, B2210, B6C80, C6EC0, 1FD200, void, D2UberBaalAI,
       (Game * ptGame, Unit * ptMonster, AIParam * args));
    A8(FAST, D2Game, 00000, 00000, 00000, 70320, D2D70, C2A90, 7B4E0, 49480, 1F81C0, void, D2UberMephAI,
       (Game * ptGame, Unit * ptMonster, AIParam * args));
    A8(FAST, D2Game, 00000, 00000, 00000, 7F200, 7FE60, D6250, A39D0, 2C3F0, 1E9DF0, void, D2UberDiabloAI,
       (Game * ptGame, Unit * ptMonster, AIParam * args));
    A8(STD, D2Game, 00000, 00000, 89C0, E2390, E66D0, A8090, 2C830, BE660, 12CA10, void, D2SaveGame, (Game * ptGame));
    A8(FAST, D2Game, 00000, 00000, 00000, EF580, F0F70, F0D70, F2540, F1800, 1DEB60, void, D2MonsterMove,
       (Game * ptGame, Unit * ptMonster, Unit * target, DWORD two, DWORD x, DWORD y, DWORD one, DWORD zero));
    A8(FAST, D2Game, 00000, 00000, 00000, FF1B0, F0DB0, F0BB0, F2380, F1430, 1DEAD0, void, D2MonsterUseSkill,
       (Game * ptGame, Unit * ptMonster, DWORD arg, DWORD skill, Unit * target, DWORD x, DWORD y));
    A8(FAST, D2Game, 00000, 00000, 00000, B9340, 25450, 44140, 53F10, 39810, 132240, void, D2SaveSPChar,
       (Game * ptGame, Unit * ptChar, char * name, DWORD arg, DWORD secondPass));

    F8(STD, D2Net, 10005, 10005, 10005, 10035, 10020, 10036, 10024, 10015, 12AE50, DWORD, D2SendToServer,
       (DWORD size, DWORD one, void * data));//(DWORD zero, void* data, DWORD size) for 1.10 and before
    F8(STD, D2Net, 10006, 10006, 10006, 10018, 10018, 10015, 10002, 10012, 12B330, DWORD, D2SendToClient,
       (DWORD zero, DWORD clientID, void * data, DWORD size));

    F8(STD, Fog, 10023, 10023, 10023, 00000, 00000, 00000, 00000, 00000, 00000, void, D2FogAssertOld,
       (const char* ptMessage, DWORD eip, DWORD line));//(STDCALL until 1.10)
    F8(FAST, Fog, 00000, 00000, 00000, 10024, 10024, 10024, 10024, 10024, 8A60, void, D2FogAssert,
       (const char* ptMessage, DWORD eip, DWORD line));
    F8(FAST, Fog, 10042, 10042, 10042, 10042, 10042, 10042, 10042, 10042, B380, void*, D2FogMemAlloc,
       (DWORD dwMemSize, LPCSTR lpszErrFile, DWORD ErrLine, DWORD Zero));
    F8(FAST, Fog, 10043, 10043, 10043, 10043, 10043, 10043, 10043, 10043, B3C0, void*, D2FogMemDeAlloc,
       (void * ptMemLoc, LPCSTR lpszErrFile, DWORD ErrLine, DWORD Zero));
    F8(FAST, Fog, 10045, 10045, 10045, 10045, 10045, 10045, 10045, 10045, B430, void*, D2AllocMem,
       (DWORD, DWORD dwMemSize, LPCSTR lpszErrFile, DWORD ErrLine, DWORD Zero));
    F8(FAST, Fog, 10046, 10046, 10046, 10046, 10046, 10046, 10046, 10046, B480, void*, D2FreeMem,
       (DWORD, void * ptMemLoc, LPCSTR lpszErrFile, DWORD ErrLine, DWORD Zero));
    F8(FAST, Fog, 10102, 10102, 10102, 10102, 10102, 10102, 10102, 10102, 68E0, DWORD, D2MPQOpenFile,
       (char * ptPath, void * *buf));
    F8(FAST, Fog, 10103, 10103, 10103, 10103, 10103, 10103, 10103, 10103, 68F0, DWORD, D2MPQCloseFile,
       (void * mpqfile));
    F8(FAST, Fog, 10104, 10104, 10104, 10104, 10104, 10104, 10104, 10104, 6900, DWORD, D2MPQReadFile,
       (void * mpqfile, BYTE * buffer, DWORD nbToRead, DWORD * nbRead, DWORD, DWORD, DWORD));
    F8(FAST, Fog, 10105, 10105, 10105, 10105, 10105, 10105, 10105, 10105, 6930, DWORD, D2MPQGetSizeFile,
       (void * mpqfile, DWORD * toReset));
    F8(FAST, Fog, 10115, 10115, 10115, 10115, 10115, 10115, 10115, 10115, 7050, void, D2FogGetSavePath,
       (char * ptPath, DWORD maxsize));
    F8(FAST, Fog, 10116, 10116, 10116, 10116, 10116, 10116, 10116, 10116, 6BA0, void, D2FogGetInstallPath,
       (char * ptPath, DWORD maxsize));
    F8(STD, Fog, 10212, 10212, 10212, 10212, 10212, 10212, 10212, 10212, 2BD0B0, void, D2Fog10212, (DWORD unknow));
    F8(STD, Fog, 00000, 00000, 00000, 10265, 10265, 10265, 10265, 10265, 8090, int, D2GetInstructionPointer, ());
    F8(FAST, D2Lang, 10003, 10003, 10003, 10002, 10004, 10010, 10011, 10011, 124E20, LPWSTR, D2GetStringFromString,
       (const char* ptString));//6FC13BC0 LAutour
    F8(FAST, D2Lang, 10004, 10004, 10004, 10005, 10000, 10005, 10003, 10004, 124A30, LPWSTR, D2GetStringFromIndex,
       (WORD dwIndexNum));
    F8(STD, D2Lang, 10007, 10007, 10007, 10009, 10013, 10002, 10009, 10001, 125150, DWORD, D2GetLang,
       ());//14b  00522A20
    F8(STD, D2Lang, 10010, 10010, 10010, 00000, 00000, 00000, 00000, 00000, 00000, DWORD, D2PrintBigNumber,
       (LPWSTR ptBuf, DWORD number, DWORD size));//6FC14210
    F8(STD, Storm, 268, 268, 268, 268, 268, 268, 268, 268, 192F0, DWORD, D2StormMPQOpenFile,
       (DWORD zero, LPCSTR fileName, DWORD dwSearchScope, void * *buffer))
    F8(STD, Storm, 503, 503, 503, 503, 503, 503, 503, 503, 13750, void, D2Storm503, (DWORD, DWORD, DWORD));
    F8(STD, Storm, 511, 511, 511, 511, 511, 511, 511, 511, 20290, void, D2FreeWinMessage, (sWinMessage * msg));


    F8(STD, D2gfx, 10005, 10005, 10005, 10000, 10063, 10043, 10031, 10012, F5160, DWORD, D2GetResolution, ());
    F8(STD, D2gfx, 10055, 10055, 10055, 10028, 10000, 10062, 10014, 10028, F6300, void, D2FillArea,
       (DWORD x1, DWORD y1, DWORD x2, DWORD y2, DWORD color, DWORD transTbl));
    F8(STD, D2gfx, 10072, 10072, 10072, 10047, 10044, 10024, 10041, 10042, F6480, void, D2PrintImage,
       (sDrawImageInfo * data, DWORD x, DWORD y, DWORD p4, DWORD p5, DWORD p6));


    F8(FAST, D2Win, 10046, 10046, 10046, 10061, 10075, 10015, 10022, 10051, FCFF0, void, D2PrintLineOnTextBox,
       (void * screen, char * s, DWORD color));
    F8(FAST, D2Win, 10117, 10117, 10117, 10020, 10064, 10001, 10150, 10076, 102320, void, D2PrintString,
       (LPWSTR s, DWORD x, DWORD y, DWORD color, DWORD bfalse));
    F8(FAST, D2Win, 10121, 10121, 10121, 10034, 10128, 10132, 10028, 10150, 101820, DWORD, D2GetPixelLen, (LPWSTR s));
    F8(FAST, D2Win, 10127, 10127, 10127, 10141, 10170, 10010, 10184, 10047, 102EF0, DWORD, D2SetFont, (DWORD fontID));
    F8(FAST, D2Win, 10129, 10129, 10129, 10118, 10039, 10031, 10085, 10137, 102280, void, D2PrintPopup,
       (LPWSTR s, DWORD x, DWORD y, DWORD color, DWORD center));
    F8(FAST, D2Win, 10131, 10131, 10131, 00000, 00000, 00000, 00000, 00000, 00000, void, D2GetPixelRect,
       (LPWSTR s, DWORD * x, DWORD * y));//6F8AB260
    F8(FAST, D2Win, 10132, 10132, 10132, 00000, 00000, 00000, 00000, 00000, 00000, DWORD, D2PrintTextPopup,
       (LPWSTR s, DWORD x, DWORD y, DWORD uk, DWORD type, DWORD color));//6F8AB080
    F8(STD, D2Win, 10017, 10017, 10017, 10147, 10113, 10098, 10098, 10164, F93C0, void*, D2CreateTextBox,
       (DWORD * data));

    F8(STD, D2CMP, 10032, 10032, 10032, 10021, 10014, 10106, 10065, 10020, 201A50, DWORD, D2CMP10014, (void * image));


//ONLY UNTIL 1.10 :
    A8(FAST, D2Client, BA00, B9F0, C080, 00000, 00000, 00000, 00000, 00000, 00000, DWORD, D2isLODGame, ());//6FAAC080
    A8(FAST, D2Client, 00000, 00000, C090, 00000, 00000, 00000, 00000, 00000, 00000, BYTE, D2GetDifficultyLevel,
       ());//6FAAC090  1.09 should be BA10 (b) BA00 (d)
    A8(STD, D2Client, B6670, B59F0, B7BC0, 00000, 00000, 00000, 00000, 00000, 00000, DWORD, D2GetMouseX, ());//6FB57BC0
    A8(STD, D2Client, B6680, B5A00, B7BD0, 00000, 00000, 00000, 00000, 00000, 00000, DWORD, D2GetMouseY, ());//6FB57BD0
    A8(STD, D2Client, 8DC40, 8CFC0, 883D0, 00000, 00000, 00000, 00000, 00000, 63DD0, Unit*, D2GetClientPlayer,
       ());//6FB283D0
    A8(FAST, D2Client, B920, B910, BF60, 00000, 00000, 00000, 00000, 00000, 4DA70, void, D2CleanStatMouseUp,
       ());//6FAABF60
    A8(FAST, D2Client, D210, D200, D990, 00000, 00000, 00000, 00000, 00000, 00000, void, D2SendToServer3,
       (BYTE type, WORD p));//6FAAD990
    A8(FAST, D2Game, 7C2C0, 7C7B0, 8C2E0, 00000, 00000, 00000, 00000, 00000, 1531C0, NetClient*, D2GetClient,
       (Unit * ptUnit, char * lpszErrFile, DWORD ErrLine));//6FCBC2E0


    C8(D2Client, D50E8, D40E0, D40F0, F5C60, F4FC8, DC6E4, DBC4C, F7038, 311470, DWORD, ResolutionY);//0x258 = 600
    C8(D2Client, D50EC, D40E4, D40F4, F5C5C, F4FC4, DC6E0, DBC48, F7034, 31146C, DWORD, ResolutionX);//0x320 = 800
    C8(D2Client, 125AD8, 124958, 11A74C, 11BD28, 11BEFC, 11BD2C, 11B9A4, 11D358, 3A285C, DWORD,
       NegWindowStartY);//0xFFFFFFC4 = -60
    C8(D2Client, 125AD4, 124954, 11A748, 11BD24, 11BEF8, 11BD28, 11B9A0, 11D354, 3A2858, DWORD,
       WindowStartX);//0x50 = 80
    C8(D2Game, F2A80, F2918, 113FB8, 111718, 1115E0, 1105E0, 1107B8, 1105E0, 4842A8, NetClient*, ClientTable);
    C8(D2Client, 000000, 000000, 000000, FB3F4, 11A2F4, 10330C, 119854, 1087B4, 3A04F4, DWORD, IsLodGame);
    C8(D2Client, 000000, 000000, 10795C, 11BFB8, 11C2A8, 11BFF4, 000000, 000000, 000000, BYTE, DifficultyLevel);
    C8(D2Client, 000000, 000000, 000000, 10A40C, 11B414, 101634, 11B824, 11C94C, 3A6AAC, DWORD, MouseY);//0x258 = 600
    C8(D2Client, 000000, 000000, 000000, 10A410, 11B418, 101638, 11B828, 11C950, 3A6AB0, DWORD, MouseX);//0x320 = 800
    C8(D2Client, 000000, 000000, 000000, 11C4F0, 11C1E0, 11C3D0, 11BBFC, 11D050, 3A6A70, Unit*, ptClientChar);
    C8(D2Client, 11E0F4, 11CF54, 112D04, 11B9A8, 11BB30, 11BF48, 11C028, 11CAA4, 3BB5E8, DWORD, InputCommandLen);
    C8(D2Client, 11CE50, 11BCB0, 111A58, 11C590, 11D590, 11FC40, 11EC80, 11D650, 3BB638, WCHAR, InputCommand);

    C8(D2Client, DB918, DA828, 000000, 000000, 000000, 000000, 000000, 000000, 000000, DWORD, NbStatDesc);
    C8(D2Client, DAF98, D9EA8, 000000, 000000, 000000, 000000, 000000, 000000, 000000, DWORD, StatDescTable);

    SgptDataTables = *(DataTables **) R8(D2Common, 0000, 0000, 96A20, 9B74C, 9EE8C, 9B500, 99E1C, A33F0, 344304);
    if (version_D2Common < V110) {
        setFctAddr((DWORD *) &D2Common10581, (HMODULE) offset_D2Common, (LPCSTR) 10581);;//ONLY in 1.09
        setFctAddr((DWORD *) &D2Common10598, (HMODULE) offset_D2Common, (LPCSTR) 10598);;//ONLY in 1.09
        setFctAddr((DWORD *) &D2Common10673, (HMODULE) offset_D2Common, (LPCSTR) 10673);;//ONLY in 1.09
    }
#undef F8
#undef A8
#undef C8
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