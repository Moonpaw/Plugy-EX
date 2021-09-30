#pragma once

#include <map>

// Convertion to 1.09
struct s_shifting {
    DWORD ptInventory;
    DWORD ptSpecificData;
    DWORD ptPYPlayerData;
    DWORD ptGame;
    DWORD ptClientGame;
    DWORD ptSkills;
    DWORD ptImage;
    DWORD ptFrame;
};
extern s_shifting shifting;

#define FASTCALL __fastcall
#define STDCALL        __stdcall

inline int RANDOM(int V) {
    return int(rand()/(RAND_MAX+1.0)*(V));
}

inline double RANDOMF() {
    return (double)rand() / (double)RAND_MAX;
}

#define PCPlayerData (*(PlayerData**)((DWORD)(ptChar)+shifting.ptSpecificData)) //->ptPlayerData
#define PCGame (*(Game**)((DWORD)(ptChar)+shifting.ptGame)) //->ptGame
#define PClientGame (*(Game**)((DWORD)(ptClient)+shifting.ptClientGame)) //ptClient->ptGame
#define PCInventory (*(Inventory**)((DWORD)(ptChar)+shifting.ptInventory)) //->ptInventory
#define PCPY ((PYPlayerData*)((DWORD)PCPlayerData+shifting.ptPYPlayerData)) //->ptPYPlayerData
//#define PCSkills (*(Skills**)((DWORD)(ptChar)+shifting.ptSkills)) //->ptSkills
inline Skills *PCSkills(Unit *ptChar) { return (*(Skills **) ((DWORD) (ptChar) + shifting.ptSkills)); }

#define R8(Z, A, B, C, D, E, F, G, H, I) \
(offset_##Z +                            \
(version_##Z == V114d? 0x##I :           \
(version_##Z == V113d? 0x##H :           \
(version_##Z == V113c? 0x##G :           \
(version_##Z == V112? 0x##F :            \
(version_##Z == V111b? 0x##E :           \
(version_##Z == V111? 0x##D :            \
(version_##Z == V110? 0x##C :            \
(version_##Z == V109d? 0x##B : 0x##A)))))))))

enum D2DllName {
    game,
    binkw32,
    Bnclient,
    D2Client,
    D2Common,
    D2DDraw,
    D2Direct3D,
    D2Game,
    D2Gdi,
    D2gfx,
    D2Glide,
    D2Lang,
    D2Launch,
    D2MCPClient,
    D2Multi,
    D2Net,
    D2sound,
    D2Win,
    Fog,
    ijl11,
    SmackW32,
    Storm
};

inline std::map<int, int> dllVersions = {
        {game, version_Game},
        {D2Client, version_D2Client},
        {D2Common, version_D2Common},
        {D2Game, version_D2Game},
        {D2gfx, version_D2gfx},
        {D2Lang, version_D2Lang},
        {D2Launch, version_D2Launch},
        {D2Net, version_D2Net},
        {D2Win, version_D2Win},
        {Fog, version_Fog},
        {Storm, version_Storm}
};

inline std::map<int, int> dllOffsets = {
        {game, offset_Game},
        {D2Client, offset_D2Client},
        {D2Common, offset_D2Common},
        {D2Game, offset_D2Game},
        {D2gfx, offset_D2gfx},
        {D2Lang, offset_D2Lang},
        {D2Launch, offset_D2Launch},
        {D2Net, offset_D2Net},
        {D2Win, offset_D2Win},
        {Fog, offset_Fog},
        {Storm, offset_Storm}
};

inline int r8(int offset, int version, int defaultValue, int B, int C, int D, int E, int F, int G, int H, int I) {
    std::map<int, int> versions = {
            {V114d, I},
            {V113d, H},
            {V113c, G},
            {V112,  F},
            {V111b, E},
            {V111,  D},
            {V110,  C},
            {V109d, B},
    };
    auto result = versions.find(version);
    return result != versions.end() ? offset + result->second : offset + defaultValue;
}

inline int v8(int version, int defaultValue, int B, int C, int D, int E, int F, int G, int H, int I) {
    std::map<int, int> versions = {
            {V114d, I},
            {V113d, H},
            {V113c, G},
            {V112,  F},
            {V111b, E},
            {V111,  D},
            {V110,  C},
            {V109d, B},
    };
    auto result = versions.find(version);
    return result != versions.end() ? result->second : defaultValue;
}

#define RX(v) (WindowStartX+(v))
#define RY(v) (ResolutionY+NegWindowStartY-(v))


#define D2S(F, I, R, N, P)    typedef R (STDCALL  *T##N) P; extern T##N N;//static D N = (D)(A);
#define D2F(F, I, R, N, P)    typedef R (FASTCALL *T##N) P; extern T##N N;//static D N = (D)(A);
#define E2S(F, A, R, N, P)    typedef R (STDCALL  *T##N) P; extern T##N N;
#define E2F(F, A, R, N, P)    typedef R (FASTCALL *T##N) P; extern T##N N;
#define E2C(F, A, T, N)        extern T* pt##N;
#define F8(X, Z, A, B, C, D, E, F, G, H, I, R, N, P) typedef R (X##CALL  *T##N) P; extern T##N N;
#define A8(X, Z, A, B, C, D, E, F, G, H, I, R, N, P) typedef R (X##CALL  *T##N) P; extern T##N N;
#define C8(Z, A, B, C, D, E, F, G, H, I, T, N)       extern T* pt##N;

/* Warning, all this code is used for macro replacement only */

F8(STD, D2Common, 00000, 00000, 00000, 10188, 11084, 11109, 10346, 10907, 21AED0, DWORD, D2Common11084,
   (Room * ptRoom, DWORD zero))

F8(STD, D2Common, 10057, 10057, 10057, 10332, 11021, 10511, 10826, 10691, 21A1B0, DWORD, D2GetLevelID, (Room * ptRoom))

F8(STD, D2Common, 10138, 10138, 10138, 10623, 10491, 11043, 10654, 10716, 24E810, Room*, D2GetDropRoom,
   (Room * ptRoom, Position *, Position *, DWORD, DWORD, DWORD, DWORD))

F8(STD, D2Common, 10242, 10242, 10242, 00000, 00000, 00000, 00000, 00000, 00000, Unit*, D2Common10242,
   (Inventory * ptInventory, Unit * ptItem, DWORD bIsClient))

F8(STD, D2Common, 10246, 10246, 10246, 10855, 10813, 10289, 10133, 10402, 23B950, Unit*, D2CanPutItemInInv,
   (Inventory * ptInventory, Unit * ptItem, DWORD p3, DWORD zero, Unit * ptUnit, const char *file, DWORD line))

F8(STD, D2Common, 10243, 10243, 10243, 10461, 10827, 10936, 10646, 10490, 23AD90, Unit*, D2InvRemoveItem,
   (Inventory * ptInventory, Unit * ptItem))

F8(STD, D2Common, 10249, 10249, 10249, 10880, 11068, 10436, 11107, 10963, 23BCC0, DWORD, D2InvAddItem,
   (Inventory * ptInventory, Unit * ptItem, DWORD posX, DWORD posY, DWORD vValueC, DWORD bIsClient, BYTE page))

F8(STD, D2Common, 10250, 10250, 10250, 00000, 00000, 00000, 00000, 00000, 00000, DWORD, D2Common10250,
   (const char* file, DWORD line, Inventory* ptInventory, DWORD posX, DWORD posY, DWORD vValueC, DWORD bIsClient, BYTE page))

F8(STD, D2Common, 10273, 10273, 10273, 00000, 00000, 00000, 00000, 00000, 00000, DWORD, D2Common10273,
   (Inventory * ptInventory, void * unknown))

F8(STD, D2Common, 10277, 10277, 10277, 10402, 10535, 11151, 10460, 11040, 23B2C0, Unit*, D2InventoryGetFirstItem,
   (Inventory * ptInventory))

F8(STD, D2Common, 10304, 10304, 10304, 10934, 11140, 10770, 10464, 10879, 23DFA0, Unit*, D2UnitGetNextItem,
   (Unit * ptItem))

F8(STD, D2Common, 10305, 10305, 10305, 11095, 10748, 10852, 11147, 10897, 23DFD0, Unit*, D2GetRealItem, (Unit * ptUnit))

F8(STD, D2Common, 10326, 10326, 00000, 00000, 00000, 00000, 00000, 00000, 00000, DWORD, D2GetPosX, (Unit * ptUnit))

F8(STD, D2Common, 10329, 10329, 00000, 00000, 00000, 00000, 00000, 00000, 00000, DWORD, D2GetPosY, (Unit * ptUnit))

F8(STD, D2Common, 10332, 10332, 10332, 11080, 10056, 10543, 10141, 11166, 220870, void, D2GetPosition,
   (Unit * ptUnit, Position * pos))

F8(STD, D2Common, 10339, 10339, 10339, 10455, 10864, 10941, 11060, 11025, 223460, DWORD, D2GetMaxGoldBank,
   (Unit * ptUnit))

F8(STD, D2Common, 10342, 10342, 10342, 10172, 10933, 10366, 10331, 10846, 220BB0, Room*, D2GetRoom, (Unit * ptUnit))

F8(STD, D2Common, 10420, 10420, 10420, 10218, 10079, 11097, 10356, 10404, 221F90, PlayerData*, D2InitPlayerData,
   (Unit * ptChar))

F8(STD, D2Common, 10424, 10424, 10424, 10562, 10800, 10860, 10920, 11103, 2221A0, PlayerData*, D2GetPlayerData,
   (Unit * ptChar))

F8(STD, D2Common, 10431, 10431, 10431, 00000, 00000, 00000, 00000, 00000, 00000, DWORD, D2GetDefence, (Unit * ptChar))

F8(STD, D2Common, 10433, 10433, 10433, 00000, 00000, 00000, 00000, 00000, 00000, DWORD, D2GetChanceToBlock,
   (Unit * ptChar, DWORD isLODGame))

F8(STD, D2Common, 10439, 10439, 10439, 10343, 11131, 10729, 10049, 11159, 222E70, DWORD, D2GetMaxGold, (Unit * ptUnit))

F8(STD, D2Common, 00000, 00000, 00000, 10440, 10572, 10481, 11090, 10193, 224690, DWORD, D2Common10572,
   (Unit * ptObject, DWORD value))

F8(STD, D2Common, 00000, 00000, 00000, 10471, 11160, 10866, 10258, 10040, 2222C0, BYTE, D2GetObjectFlags,
   (Unit * ptObject))

F8(STD, D2Common, 00000, 00000, 00000, 10572, 11048, 10150, 10111, 10033, 222300, void, D2SetObjectFlags,
   (Unit * ptObject, BYTE flags))

F8(STD, D2Common, 10487, 10487, 10487, 00000, 00000, 00000, 00000, 00000, 00000, DWORD, D2isInState,
   (Unit * ptChar, DWORD isLODGame))

F8(STD, D2Common, 10518, 10518, 10518, 10109, 10627, 10762, 10551, 10645, 2272B0, void, D2AddPlayerStat,
   (Unit * ptChar, DWORD statID, int amount, DWORD index))

F8(STD, D2Common, 10519, 10519, 10519, 11092, 10061, 10658, 10973, 10550, 225480, int, D2GetPlayerStat,
   (Unit * ptChar, DWORD statID, DWORD index))

F8(STD, D2Common, 10521, 10521, 10521, 10733, 10550, 10494, 10587, 10216, 2253B0, int, D2GetPlayerBaseStat,
   (Unit * ptChar, DWORD statID, DWORD index))

F8(STD, D2Common, 10539, 10539, 10539, 00000, 00000, 00000, 00000, 00000, 00000, DWORD, D2haveDefenceBonus,
   (Unit * ptChar))

F8(STD, D2Common, 10540, 10540, 10540, 00000, 00000, 00000, 00000, 00000, 00000, DWORD, D2haveFireResBonus,
   (Unit * ptChar))

F8(STD, D2Common, 10541, 10541, 10541, 00000, 00000, 00000, 00000, 00000, 00000, DWORD, D2haveColdResBonus,
   (Unit * ptChar))

F8(STD, D2Common, 10542, 10542, 10542, 00000, 00000, 00000, 00000, 00000, 00000, DWORD, D2haveLightResBonus,
   (Unit * ptChar))

F8(STD, D2Common, 10543, 10543, 10543, 00000, 00000, 00000, 00000, 00000, 00000, DWORD, D2havePoisonResBonus,
   (Unit * ptChar))

F8(STD, D2Common, 10546, 10546, 10546, 00000, 00000, 00000, 00000, 00000, 00000, DWORD, D2haveDefenceMalus,
   (Unit * ptChar))

F8(STD, D2Common, 10547, 10547, 10547, 00000, 00000, 00000, 00000, 00000, 00000, DWORD, D2haveFireResMalus,
   (Unit * ptChar))

F8(STD, D2Common, 10548, 10548, 10548, 00000, 00000, 00000, 00000, 00000, 00000, DWORD, D2haveColdResMalus,
   (Unit * ptChar))

F8(STD, D2Common, 10549, 10549, 10549, 00000, 00000, 00000, 00000, 00000, 00000, DWORD, D2haveLightResMalus,
   (Unit * ptChar))

F8(STD, D2Common, 10550, 10550, 10550, 00000, 00000, 00000, 00000, 00000, 00000, DWORD, D2havePoisonResMalus,
   (Unit * ptChar))

F8(STD, D2Common, 10578, 10578, 10578, 10653, 10496, 10244, 10849, 10037, 2122F0, void*, D2CompileTxtFile,
   (DWORD unused, const char *filename, BINField*ptFields, DWORD * ptRecordCount, DWORD recordLength))

F8(STD, D2Common, 10600, 10600, 10600, 10573, 10262, 10887, 10695, 10994, 2335F0, ItemsBIN*, D2GetItemsBIN,
   (DWORD itemID))

F8(STD, D2Common, 10616, 10616, 10616, 10500, 10523, 10774, 10806, 10619, 2372C0, GemsBIN*, D2GetGemsBIN, (DWORD gemID))

F8(STD, D2Common, 11232, 11232, 11232, 10746, 10258, 10913, 10783, 10393, 26A1B0, CubeMainBIN*, D2GetCubeMainBIN,
   (DWORD cubemainID))

F8(STD, D2Common, 11233, 11233, 11233, 10639, 11135, 10390, 10675, 10235, 26A200, int, D2GetNbCubeMainBIN, ())

F8(STD, D2Common, 10628, 10628, 10628, 00000, 00000, 00000, 00000, 00000, 00000, DWORD, D2GetNextLevelXP,
   (DWORD classID, DWORD level))

F8(STD, D2Common, 10629, 10629, 10629, 00000, 00000, 00000, 00000, 00000, 00000, DWORD, D2GetMaxLevel, (DWORD classID))

F8(STD, D2Common, 10655, 10655, 10655, 10655, 10309, 10297, 10218, 10694, 111D30, DifficultyLevelsBIN*,
   D2GetDifficultyLevelsBIN, (DWORD difficultyLevel))

F8(STD, D2Common, 10695, 10695, 10695, 10927, 10899, 10276, 10106, 10911, 227E70, DWORD, D2GetItemQuality,
   (Unit * ptItem))

F8(STD, D2Common, 10707, 10707, 10707, 10911, 10303, 10989, 10202, 10458, 2280A0, DWORD, D2TestFlags,
   (Unit * ptUnit, DWORD flags, DWORD line, const char *file))

F8(STD, D2Common, 10717, 10717, 10717, 10898, 10100, 10410, 10086, 10008, 2281E0, DWORD, D2GetItemLevel,
   (Unit * ptItem))

F8(STD, D2Common, 10719, 10719, 10719, 10820, 10505, 10370, 10020, 10810, 228250, BYTE, D2ItemGetPage, (Unit * ptUnit))

F8(STD, D2Common, 10720, 10720, 10720, 10485, 10608, 10223, 10012, 11026, 228280, void, D2ItemSetPage,
   (Unit * ptItem, BYTE page))

F8(STD, D2Common, 10731, 10731, 10731, 11017, 10890, 10231, 10744, 10601, 229BB0, DWORD, D2CheckItemType,
   (Unit * ptItem, DWORD itype))

F8(STD, D2Common, 10732, 10732, 10732, 10692, 10685, 10280, 10620, 10075, 229DA0, int, D2GetUniqueID, (Unit * ptItem))

F8(STD, D2Common, 10734, 10734, 10734, 00000, 00000, 00000, 00000, 00000, 00000, void, D2SetAnim,
   (Unit * ptUnit, int anim))

F8(STD, D2Common, 10619, 10619, 10619, 10687, 10877, 10321, 11032, 10981, 239CB0, int*, D2GetNbRunesBIN, ())

F8(STD, D2Common, 10620, 10620, 10620, 10775, 10296, 10622, 10006, 10405, 239D60, RunesBIN*, D2GetRunesBIN,
   (int runesID))

F8(STD, D2Common, 10881, 10881, 10881, 10956, 11156, 10218, 10987, 10665, 2313E0, DWORD, D2SaveItem,
   (Unit * ptItem, saveBitField * data, DWORD startSize, DWORD p4, DWORD p5, DWORD p6))

F8(STD, D2Common, 10953, 10953, 10953, 10099, 10255, 10210, 10302, 10335, 247280, void, D2SetSkillBaseLevel,
   (Unit * ptChar, DWORD skillID, DWORD slvl, DWORD bRemove, char *, DWORD))

F8(STD, D2Common, 10968, 10968, 10968, 10700, 10109, 10904, 10306, 10007, 2442A0, DWORD, D2GetSkillLevel,
   (Unit * ptChar, SkillData * ptSkill, DWORD includingBonus))

F8(STD, D2Common, 11276, 11276, 11276, 10254, 10074, 10111, 10435, 11081, 246CA0, DWORD, D2GetSkillCost,
   (Unit * ptChar, int skpoints, DWORD skillID, DWORD curSkillLevel))

A8(FAST, D2Common, 00000, 00000, 82C80, 15D0, 1800, 1220, 12D0, 17B0, 833E0, CharStatsBIN*, D2GetCharStatsBIN,
   (DWORD charID))

A8(FAST, D2Common, 00000, 00000, 12410, 5D7D0, 1A100, 116C0, 1C020, 5B0E0, 268600, DWORD, D2CompileCubeInput,
   (CubeInput * cubeinput, char * s, DWORD p1, DWORD p2))

A8(FAST, D2Common, 00000, 00000, 2B1A0, 11F0, 1380, 1140, 1300, 1160, 155C90, ItemTypesBIN*, D2GetItemTypesBIN,
   (DWORD itemTypesId))

A8(FAST, D2Common, 00000, 00000, 642B0, 13F0, 12F0, 1540, 17A0, 17E0, 5C4F0, ItemStatCostBIN*, D2GetItemStatCostBIN,
   (DWORD id))

A8(FAST, D2Common, 738A4, 739B4, 84268, 96E0, 98D0, 9900, 9900, B5E0, 117079, void*, D2ReadFile,
   (DWORD mempool, char * filename, DWORD * size, const char*, DWORD))

A8(STD, D2Common, 1F500, 1F510, 29FA0, 71EB0, 32AA0, 7D2A0, 59870, 80C40, 2552E0, void, D2LoadSuperuniques,
   (DWORD mempool))

A8(STD, D2Common, 00000, 00000, 00000, 00000, 00000, 00000, 81EA0, 00000, 00000, InventoryBIN*, D2GetInventoryBIN, ())

A8(FAST, D2Client, 1000, 1000, 1000, 75D00, A9070, BEF70, 2B420, A9480, 788B0, void*, D2LoadImage,
   (const char* filename, DWORD filetype))

A8(FAST, D2Client, 1150, 1150, 1140, 00000, 00000, 00000, 00000, 00000, 78A00, void, D2FreeImage, (void * image))

A8(FAST, D2Client, D640, D630, DB50, 73620, 5E4E0, 79670, 147A0, B6890, 787B0, void, D2SendMsgToAll, (BYTE * data))

A8(STD, D2Client, 00000, 00000, 15A80, 00000, 00000, 00000, 00000, 00000, 00000, DWORD, D2GetLastMonsterIDFight, ())

A8(STD, D2Client, 29800, 297F0, 2FD60, 828A0, 89320, 6B280, BCEA0, BF640, A7D00, void, D2PrintStatsPage, ())

A8(FAST, D2Client, 4BB20, 4BB20, 521C0, B8CB0, 21250, 88EA0, 54E10, 2CE40, E4D80, DWORD, D2PrintStat,
   (Unit * ptItem, Stats * ptStats, DWORD statID, DWORD statIndex, DWORD statValue, LPWSTR lpText))

A8(FAST, D2Client, 85A60, 84DE0, 80430, 9EEB0, 62070, 8B7A0, BF5F0, 18820, 521C0, LPWSTR, D2SetColorPopup,
   (LPWSTR popupText, DWORD color))

A8(FAST, D2Client, B4360, B36E0, B5820, 3ACC0, 54210, 31FA0, 88A70, 26270, B9A00, DWORD, D2PlaySound,
   (DWORD id, DWORD, DWORD, DWORD, DWORD))

A8(FAST, D2Client, 00000, 00000, 00000, 73260, 5DE40, 791A0, 143E0, B61F0, 78350, void, D2SendToServerXX,
   (DWORD size, BYTE * data))

A8(FAST, D2Client, 88940, 87CC0, 83260, A1F30, 65690, 8EF00, C2790, 1C190, 55F20, void, D2TogglePage,
   (DWORD a, DWORD b, DWORD c))

A8(FAST, D2Client, 00000, 00000, 00000, A6520, 710C0, A6640, 8CD00, 90C10, 89980, void, D2ClickOnStashButton,
   (DWORD x, DWORD y))

A8(STD, D2Client, 897B0, 88B30, 84110, 9E3B0, 621C0, 8B8F0, BEAF0, 18AA0, 54600, void*, D2LoadBuySelBtn, ())

A8(FAST, D2Client, 00000, 00000, 00000, 00000, 00000, 00000, 00000, 00000, 520C0, void*, D2LoadResImage,
   (const char* filename))

A8(FAST, D2Client, 00000, 00000, 00000, 00000, 00000, 00000, 00000, 00000, 96990, void*, D2FreeResImages, ())

A8(FAST, D2Client, 00000, 00000, 00000, 00000, 00000, 00000, 00000, 00000, 5C850, void*, D2ReceivePacket,
   (DWORD a, DWORD b))

A8(STD, D2Client, 87220, 865A0, 81B70, A35F0, 669F0, 90150, C39E0, 1D3E0, 56EE0, DWORD, D2PrintInterface,
   (void * unknown))

F8(FAST, D2Game, 10059, 10059, 10059, 10039, 10007, 10037, 10049, 10002, 135780, void, D2SetNbPlayers,
   (DWORD nbPlayers))

A8(FAST, D2Game, 00000, 00000, 6C60, E3DA0, E8210, EB060, 49930, E5070, 12C550, void, D2AddClient, (DWORD clientID))

A8(STD, D2Game, 00000, 00000, 94E0, E0520, E49A0, A6360, 2AAE0, BC700, 12E860, Game*, D2GetGameByClientID,
   (DWORD clientID))

A8(FAST, D2Game, 00000, 00000, B0E0, DF250, E36D0, A5080, 29820, BB510, 12DED0, void, D2BroadcastFunction,
   (Game * ptGame, void * fct, void * param))

A8(FAST, D2Game, C380, C650, C710, 41420, A0D50, 7D220, 8A3E0, DB780, 13B280, DWORD, D2SendPacket,
   (void * ptNetClient, LPVOID pData, DWORD size))

A8(FAST, D2Game, D650, D920, DB50, 44D00, A3F20, 802E0, 8D5F0, DD4F0, 13C4A0, void, D2SetSkillBaseLevelOnClient,
   (void * ptClient, Unit * ptChar, DWORD skillID, DWORD sLvl, DWORD bRemove))

A8(STD, D2Game, 00000, 00000, 00000, 27230, 109F0, AE930, A22E0, 15F40, 16CF40, DWORD, D2LinkPortal,
   (Game * ptGame, Unit * ptObject, DWORD levelEndID, DWORD levelStartID))

A8(FAST, D2Game, 00000, 00000, 128F0, 38D90, 43E60, 11FF0, D2070, B2F70, 15CA40, DWORD, D2VerifIfNotCarry1,
   (Unit * ptItem, ItemsBIN * itemsData, Unit * ptFirstItem))

A8(FAST, D2Game, 00000, 00000, 22070, 1090, 1DF0, 11F0, 1280, 1340, 63740, Room*, D2TestPositionInRoom,
   (Room * ptRoom, DWORD x, DWORD y))

A8(FAST, D2Game, 00000, 00000, 3F220, 4ABE0, EC7E0, 40B90, 24950, CDE20, 1A09E0, DWORD, D2SpawnSuperUnique,
   (Game * ptGame, Room * ptRoom, DWORD zero1, DWORD x, DWORD y, DWORD minusOne, DWORD superuniqueID, DWORD zero2))

A8(FAST, D2Game, 00000, 00000, 00000, C80F0, EF870, EFB10, EF650, C8D70, 1B2F20, Unit*, D2SpawnMonster,
   (DWORD id, DWORD mode, Game * ptGame, Room * ptRoom, DWORD x, DWORD y, DWORD one, DWORD zero))

A8(STD, D2Game, 00000, 00000, 00000, D6D10, 235C0, D410, 200E0, 59980, 142B40, void, D2Game235C0,
   (Game * ptGame, Room * ptRoom))

A8(FAST, D2Game, 4F100, 4F500, 5B8A0, B9D70, 25D50, 44950, 54810, 3A4C0, 1335E0, DWORD, D2LoadInventory,
   (Game * ptGame, Unit * pChar, saveBitField * pdata, DWORD p2, DWORD maxSize, DWORD p4, DWORD * ptNbBytesRead))

A8(FAST, D2Game, 7BAE0, 7BFD0, 8BB00, 97620, BEF80, 93650, E03A0, 6DC40, 152F60, Unit*, D2GameGetObject,
   (Game * ptGame, DWORD type, DWORD itemNum))

A8(FAST, D2Game, 00000, 00000, 00000, 99760, C09E0, 94E70, E1D90, 6FE10, 155230, Unit*, D2CreateUnit,
   (DWORD type, DWORD id, DWORD x, DWORD y, Game * ptGame, Room * ptRoom, DWORD uk1, DWORD uk2, DWORD uk3))

A8(FAST, D2Game, 00000, 00000, 00000, 9B480, 34920, D1AA0, 70180, 941E0, 165A90, void, D2OpenPandPortal,
   (Game * ptGame, Unit * ptChar))

A8(FAST, D2Game, 00000, 00000, 00000, 9B470, 34910, D1A90, 70170, 941D0, 165AA0, void, D2OpenPandFinalPortal,
   (Game * ptGame, Unit * ptChar))

A8(FAST, D2Game, 00000, 00000, 00000, 75980, D7BD0, CD0F0, 85B60, 4EAD0, 1F78B0, void, D2MephAI,
   (Game * ptGame, Unit * ptMonster, AIParam * args))

A8(FAST, D2Game, 00000, 00000, 00000, 84730, 85AA0, DBE90, A9610, 31920, 1E9170, void, D2DiabloAI,
   (Game * ptGame, Unit * ptMonster, AIParam * args))

A8(FAST, D2Game, 00000, 00000, 00000, EAB20, 2BC80, B3B90, B8610, C8850, 1FCFE0, void, D2BaalAI,
   (Game * ptGame, Unit * ptMonster, AIParam * args))

A8(FAST, D2Game, 00000, 00000, 00000, E92B0, 2A300, B2210, B6C80, C6EC0, 1FD200, void, D2UberBaalAI,
   (Game * ptGame, Unit * ptMonster, AIParam * args))

A8(FAST, D2Game, 00000, 00000, 00000, 70320, D2D70, C2A90, 7B4E0, 49480, 1F81C0, void, D2UberMephAI,
   (Game * ptGame, Unit * ptMonster, AIParam * args))

A8(FAST, D2Game, 00000, 00000, 00000, 7F200, 7FE60, D6250, A39D0, 2C3F0, 1E9DF0, void, D2UberDiabloAI,
   (Game * ptGame, Unit * ptMonster, AIParam * args))

A8(STD, D2Game, 00000, 00000, 89C0, E2390, E66D0, A8090, 2C830, BE660, 12CA10, void, D2SaveGame, (Game * ptGame))

A8(FAST, D2Game, 00000, 00000, 00000, EF580, F0F70, F0D70, F2540, F1800, 1DEB60, void, D2MonsterMove,
   (Game * ptGame, Unit * ptMonster, Unit * target, DWORD two, DWORD x, DWORD y, DWORD one, DWORD zero))

A8(FAST, D2Game, 00000, 00000, 00000, FF1B0, F0DB0, F0BB0, F2380, F1430, 1DEAD0, void, D2MonsterUseSkill,
   (Game * ptGame, Unit * ptMonster, DWORD arg, DWORD skill, Unit * target, DWORD x, DWORD y))

A8(FAST, D2Game, 00000, 00000, 00000, B9340, 25450, 44140, 53F10, 39810, 132240, void, D2SaveSPChar,
   (Game * ptGame, Unit * ptChar, char * name, DWORD arg, DWORD secondPass))

F8(STD, D2Net, 10005, 10005, 10005, 10035, 10020, 10036, 10024, 10015, 12AE50, DWORD, D2SendToServer,
   (DWORD size, DWORD one, void * data))

F8(STD, D2Net, 10006, 10006, 10006, 10018, 10018, 10015, 10002, 10012, 12B330, DWORD, D2SendToClient,
   (DWORD zero, DWORD clientID, void * data, DWORD size))

F8(STD, Fog, 10023, 10023, 10023, 00000, 00000, 00000, 00000, 00000, 00000, void, D2FogAssertOld,
   (const char* ptMessage, DWORD eip, DWORD line))

F8(FAST, Fog, 00000, 00000, 00000, 10024, 10024, 10024, 10024, 10024, 8A60, void, D2FogAssert,
   (const char* ptMessage, DWORD eip, DWORD line))

F8(FAST, Fog, 10042, 10042, 10042, 10042, 10042, 10042, 10042, 10042, B380, void*, D2FogMemAlloc,
   (DWORD dwMemSize, LPCSTR lpszErrFile, DWORD ErrLine, DWORD Zero))

F8(FAST, Fog, 10043, 10043, 10043, 10043, 10043, 10043, 10043, 10043, B3C0, void*, D2FogMemDeAlloc,
   (void * ptMemLoc, LPCSTR lpszErrFile, DWORD ErrLine, DWORD Zero))

F8(FAST, Fog, 10045, 10045, 10045, 10045, 10045, 10045, 10045, 10045, B430, void*, D2AllocMem,
   (DWORD, DWORD dwMemSize, LPCSTR lpszErrFile, DWORD ErrLine, DWORD Zero))

F8(FAST, Fog, 10046, 10046, 10046, 10046, 10046, 10046, 10046, 10046, B480, void*, D2FreeMem,
   (DWORD, void * ptMemLoc, LPCSTR lpszErrFile, DWORD ErrLine, DWORD Zero))

F8(FAST, Fog, 10102, 10102, 10102, 10102, 10102, 10102, 10102, 10102, 68E0, DWORD, D2MPQOpenFile,
   (char * ptPath, void * *buf))

F8(FAST, Fog, 10103, 10103, 10103, 10103, 10103, 10103, 10103, 10103, 68F0, DWORD, D2MPQCloseFile, (void * mpqfile))

F8(FAST, Fog, 10104, 10104, 10104, 10104, 10104, 10104, 10104, 10104, 6900, DWORD, D2MPQReadFile,
   (void * mpqfile, BYTE * buffer, DWORD nbToRead, DWORD * nbRead, DWORD, DWORD, DWORD))

F8(FAST, Fog, 10105, 10105, 10105, 10105, 10105, 10105, 10105, 10105, 6930, DWORD, D2MPQGetSizeFile,
   (void * mpqfile, DWORD * toReset))

F8(FAST, Fog, 10115, 10115, 10115, 10115, 10115, 10115, 10115, 10115, 7050, void, D2FogGetSavePath,
   (char * ptPath, DWORD maxsize))

F8(FAST, Fog, 10116, 10116, 10116, 10116, 10116, 10116, 10116, 10116, 6BA0, void, D2FogGetInstallPath,
   (char * ptPath, DWORD maxsize))

F8(STD, Fog, 10212, 10212, 10212, 10212, 10212, 10212, 10212, 10212, 2BD0B0, void, D2Fog10212, (DWORD unknow))

F8(STD, Fog, 00000, 00000, 00000, 10265, 10265, 10265, 10265, 10265, 8090, int, D2GetInstructionPointer, ())

F8(FAST, D2Lang, 10003, 10003, 10003, 10002, 10004, 10010, 10011, 10011, 124E20, LPWSTR, D2GetStringFromString,
   (const char* ptString))

F8(FAST, D2Lang, 10004, 10004, 10004, 10005, 10000, 10005, 10003, 10004, 124A30, LPWSTR, D2GetStringFromIndex,
   (WORD dwIndexNum))

F8(STD, D2Lang, 10007, 10007, 10007, 10009, 10013, 10002, 10009, 10001, 125150, DWORD, D2GetLang, ())

F8(STD, D2Lang, 10010, 10010, 10010, 00000, 00000, 00000, 00000, 00000, 00000, DWORD, D2PrintBigNumber,
   (LPWSTR ptBuf, DWORD number, DWORD size))

F8(STD, Storm, 268, 268, 268, 268, 268, 268, 268, 268, 192F0, DWORD, D2StormMPQOpenFile,
   (DWORD zero, LPCSTR fileName, DWORD dwSearchScope, void * *buffer))

F8(STD, Storm, 503, 503, 503, 503, 503, 503, 503, 503, 13750, void, D2Storm503, (DWORD, DWORD, DWORD))

F8(STD, Storm, 511, 511, 511, 511, 511, 511, 511, 511, 20290, void, D2FreeWinMessage, (sWinMessage * msg))


F8(STD, D2gfx, 10005, 10005, 10005, 10000, 10063, 10043, 10031, 10012, F5160, DWORD, D2GetResolution, ())

F8(STD, D2gfx, 10055, 10055, 10055, 10028, 10000, 10062, 10014, 10028, F6300, void, D2FillArea,
   (DWORD x1, DWORD y1, DWORD x2, DWORD y2, DWORD color, DWORD transTbl))

F8(STD, D2gfx, 10072, 10072, 10072, 10047, 10044, 10024, 10041, 10042, F6480, void, D2PrintImage,
   (sDrawImageInfo * data, DWORD x, DWORD y, DWORD p4, DWORD p5, DWORD p6))

F8(FAST, D2Win, 10046, 10046, 10046, 10061, 10075, 10015, 10022, 10051, FCFF0, void, D2PrintLineOnTextBox,
   (void * screen, char * s, DWORD color))

F8(FAST, D2Win, 10117, 10117, 10117, 10020, 10064, 10001, 10150, 10076, 102320, void, D2PrintString,
   (LPWSTR s, DWORD x, DWORD y, DWORD color, DWORD bfalse))

F8(FAST, D2Win, 10121, 10121, 10121, 10034, 10128, 10132, 10028, 10150, 101820, DWORD, D2GetPixelLen, (LPWSTR s))

F8(FAST, D2Win, 10127, 10127, 10127, 10141, 10170, 10010, 10184, 10047, 102EF0, DWORD, D2SetFont, (DWORD fontID))

F8(FAST, D2Win, 10129, 10129, 10129, 10118, 10039, 10031, 10085, 10137, 102280, void, D2PrintPopup,
   (LPWSTR s, DWORD x, DWORD y, DWORD color, DWORD center))

F8(FAST, D2Win, 10131, 10131, 10131, 00000, 00000, 00000, 00000, 00000, 00000, void, D2GetPixelRect,
   (LPWSTR s, DWORD * x, DWORD * y))

F8(FAST, D2Win, 10132, 10132, 10132, 00000, 00000, 00000, 00000, 00000, 00000, DWORD, D2PrintTextPopup,
   (LPWSTR s, DWORD x, DWORD y, DWORD uk, DWORD type, DWORD color))

F8(STD, D2Win, 10017, 10017, 10017, 10147, 10113, 10098, 10098, 10164, F93C0, void*, D2CreateTextBox, (DWORD * data))

F8(STD, D2CMP, 10032, 10032, 10032, 10021, 10014, 10106, 10065, 10020, 201A50, DWORD, D2CMP10014, (void * image))


//ONLY UNTIL 1.10 :
A8(FAST, D2Client, BA00, B9F0, C080, 00000, 00000, 00000, 00000, 00000, 00000, DWORD, D2isLODGame, ())

A8(FAST, D2Client, 00000, 00000, C090, 00000, 00000, 00000, 00000, 00000, 00000, BYTE, D2GetDifficultyLevel, ())

A8(STD, D2Client, B6670, B59F0, B7BC0, 00000, 00000, 00000, 00000, 00000, 00000, DWORD, D2GetMouseX, ())

A8(STD, D2Client, B6680, B5A00, B7BD0, 00000, 00000, 00000, 00000, 00000, 00000, DWORD, D2GetMouseY, ())

A8(STD, D2Client, 8DC40, 8CFC0, 883D0, 00000, 00000, 00000, 00000, 00000, 63DD0, Unit*, D2GetClientPlayer, ())

A8(FAST, D2Client, B920, B910, BF60, 00000, 00000, 00000, 00000, 00000, 4DA70, void, D2CleanStatMouseUp, ())

A8(FAST, D2Client, D210, D200, D990, 00000, 00000, 00000, 00000, 00000, 00000, void, D2SendToServer3,
   (BYTE type, WORD p))

A8(FAST, D2Game, 7C2C0, 7C7B0, 8C2E0, 00000, 00000, 00000, 00000, 00000, 1531C0, NetClient*, D2GetClient,
   (Unit * ptUnit, char * lpszErrFile, DWORD ErrLine))


C8(D2Client, D50E8, D40E0, D40F0, F5C60, F4FC8, DC6E4, DBC4C, F7038, 311470, DWORD, ResolutionY)
C8(D2Client, D50EC, D40E4, D40F4, F5C5C, F4FC4, DC6E0, DBC48, F7034, 31146C, DWORD, ResolutionX)
C8(D2Client, 125AD8, 124958, 11A74C, 11BD28, 11BEFC, 11BD2C, 11B9A4, 11D358, 3A285C, DWORD, NegWindowStartY)
C8(D2Client, 125AD4, 124954, 11A748, 11BD24, 11BEF8, 11BD28, 11B9A0, 11D354, 3A2858, DWORD, WindowStartX)
C8(D2Game, F2A80, F2918, 113FB8, 111718, 1115E0, 1105E0, 1107B8, 1105E0, 4842A8, NetClient*, ClientTable)
C8(D2Client, 000000, 000000, 000000, FB3F4, 11A2F4, 10330C, 119854, 1087B4, 3A04F4, DWORD, IsLodGame)
C8(D2Client, 000000, 000000, 10795C, 11BFB8, 11C2A8, 11BFF4, 000000, 000000, 000000, BYTE, DifficultyLevel)
C8(D2Client, 000000, 000000, 000000, 10A40C, 11B414, 101634, 11B824, 11C94C, 3A6AAC, DWORD, MouseY)
C8(D2Client, 000000, 000000, 000000, 10A410, 11B418, 101638, 11B828, 11C950, 3A6AB0, DWORD, MouseX)
C8(D2Client, 000000, 000000, 000000, 11C4F0, 11C1E0, 11C3D0, 11BBFC, 11D050, 3A6A70, Unit*, ptClientChar)
C8(D2Client, 11E0F4, 11CF54, 112D04, 11B9A8, 11BB30, 11BF48, 11C028, 11CAA4, 3BB5E8, DWORD, InputCommandLen)
C8(D2Client, 11CE50, 11BCB0, 111A58, 11C590, 11D590, 11FC40, 11EC80, 11D650, 3BB638, WCHAR, InputCommand)

C8(D2Client, DB918, DA828, 000000, 000000, 000000, 000000, 000000, 000000, 000000, DWORD, NbStatDesc)
C8(D2Client, DAF98, D9EA8, 000000, 000000, 000000, 000000, 000000, 000000, 000000, DWORD, StatDescTable)
extern DataTables *SgptDataTables;

#undef F8
#undef A8
#undef C8
#undef D2S
#undef D2F
#undef E2S
#undef E2F
#undef E2C

extern TD2AddPlayerStat V2AddPlayerStat;
extern TD2GetGameByClientID V2GetGameByClientID;
extern TD2SpawnSuperUnique V2SpawnSuperUnique;
extern TD2SpawnMonster V2SpawnMonster;
extern TD2Game235C0 V2Game235C0;
extern TD2ReadFile V2ReadFile;

extern WORD (*getDescStrPos)(DWORD statID);

extern void *(STDCALL *compileTxtFile)(DWORD unused, const char *filename, BINField *ptFields, DWORD *ptRecordCount,
                                       DWORD recordLength);

void setImage(sDrawImageInfo *data, void *image);

void setFrame(sDrawImageInfo *data, DWORD frame);

void __inline fillRect(DWORD x, DWORD y, DWORD Width, DWORD Height, DWORD color, DWORD transTbl) {
    D2FillArea(x, y, x + Width, y + Height, color, transTbl);
}

#define ResolutionY (*ptResolutionY)
#define ResolutionX (*ptResolutionX)
#define NegWindowStartY (*ptNegWindowStartY)
#define WindowStartX (*ptWindowStartX)
#define GameTypeMode (*ptGameTypeMode)
#define ClientTable (*ptClientTable)
#define IsLodGame (*ptIsLodGame)
#define DifficultyLevel (*ptDifficultyLevel)
#define MouseY (*ptMouseY)
#define MouseX (*ptMouseX)
#define ptClientChar (*ptptClientChar)
#define InputCommandLen (*ptInputCommandLen)
#define InputCommand (*ptInputCommand)

void initD2functions();
