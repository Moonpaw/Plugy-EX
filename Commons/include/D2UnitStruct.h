#pragma once

#include <Windows.h>

namespace Commons {
    struct CBPlayerData;
    struct CBItemData;
    struct Unit;
    struct SkillsBIN;
    struct SkillData;
    struct ObjectsBIN;
    struct NetClient;
    struct Game;
    struct ActMap;
    struct ActData;
    struct Level;
    struct RoomEx;
    struct Room;
    struct SkillData {                                //Offset from Code. (size = 0x3C or 0x40)
        SkillsBIN *ptSkillBin;        //+00
        SkillData *ptNextSkill;    //+04
        DWORD mode;           //+08
        DWORD uk1[3];         //+0C
        DWORD targetInfo;     //+18
        DWORD targetType;     //+1c
        DWORD targetUNID;     //+20
        DWORD uk2;            //+24
        DWORD slvl;           //+28
        DWORD slvlBonus;      //+2c
        DWORD uk3;            //+30
        int state;          //+34 (-1 if index exist)
        DWORD param1;            //+38 (nb current charge)
        DWORD param2;            //+3C
    };
    struct Skills {                                //Offset from Code.
        DWORD gameRelated;    //+00
        SkillData *ptFirstSkill;    //+04
        SkillData *ptLeftSkill;    //+08
        SkillData *ptRightSkill;    //+0c
        SkillData *ptCurrentSkill;    //+10
    };
    struct Position {
        DWORD x;
        DWORD y;
    };
    struct RoomEx //size=5C
    {
        DWORD __00[2];        //0x00
        RoomEx **roomExNear;        //0x08
        DWORD __0C[5];        //0x0C
        struct {
            INT32 roomNumber;        //0x00
            void *__04;            //0x04
            PINT32 subNumber;        //0x08
        } *pType2Info;                //0x20
        RoomEx *ptNextRoomEx;    //0x24
        UINT32 roomFlags;        //0x28
        UINT32 roomsNearCount;    //0x2C
        Room *ptRoom;            //0x30
        INT32 posX;            //0x34
        INT32 posY;            //0x38
        INT32 sizeX;            //0x3C
        INT32 sizeY;            //0x40
        DWORD __44;            //0x44
        UINT32 presetType;        //0x48
        void *ptWarpTiles;    //0x4C
        DWORD __50[2];        //0x50
        Level *ptLevel;        //0x58
    };
    struct Room //size=0x80
    {
        Room **ptNearRooms;        //0x00
        DWORD __04[3];            //0x04
        RoomEx *ptRoomEx;            //0x10
        DWORD __14[3];            //0x14
        void *coll;                //0x20
        INT32 nbNearRooms;        //0x24
        DWORD __28[9];            //0x28
        DWORD startX;                //0x4C
        DWORD startY;                //0x50
        DWORD sizeX;                //0x54
        DWORD sizeY;                //0x58
        DWORD __5C[6];            //0x5C
        Unit *ptFirstUnit;        //0x74
        DWORD __78;                //0x78
        Room *ptNextRoom;            //0x7C
    };
    struct Level //size=0x234
    {
        DWORD type;                //+000
        DWORD flags;                //+004
        DWORD __004_010[2];        //+008
        RoomEx *ptFirstRoomEx;        //+010
        DWORD __014_01C[2];        //+014
        INT32 posX;                //+01C
        INT32 posY;                //+020
        INT32 sizeX;                //+024
        INT32 sizeY;                //+028
        DWORD __0C2_1AC[96];        //+02C
        Level *ptNextLevel;        //+1AC
        DWORD __1B0;                //+1B0
        ActData *ptActData;            //+1B4
        DWORD __1B8_1C0[2];        //+1B8
        DWORD levelType;            //+1C0
        DWORD seed1;                //+1C4
        DWORD seed2;                //+1C8
        DWORD uk_1CC;                //+1CC
        UINT32 levelNo;            //+1D0
        DWORD __1D4_234[96];        //+1D4
    };
    struct ActData //size=0x488
    {
        DWORD seed1;                //+000
        DWORD seed2;                //+004
        DWORD nbRooms;            //+008
        DWORD __00C_0094[34];        //+00C
        DWORD nTalRashaTombLevel;    //094
        DWORD __098;                //+098
        Game *ptGame;                //+09C
        DWORD __0A0_450[237];        //+0A0
        BYTE difficulty;            //+450
        BYTE __451_46C[27];        //+451
        ActMap *ptActMap;            //+46C
        DWORD __470_484[5];        //+470
        DWORD nBossMummyTombLevel;//+484
    };
    struct ActMap //size=0x60
    {
        DWORD isNotManaged;        //+00
        DWORD __04;                //+04
        DWORD townLevel;            //+08
        DWORD seed;                //+0C
        Room *ptFirstRoom;        //+10
        DWORD actNumber;            //+14
        DWORD __18_48[12];        //+18
        ActData *ptActData;            //+48
        DWORD __50_5C[4];            //+4C
        void *ptMemoryPool;        //+5C
    };
//ptGame : 04E4007C
    struct Game {                                        //Offset from Code.
        BYTE uk1[0x18];                    //+00
        DWORD _ptLock;                    //+18 Unknown
        DWORD memoryPool;                    //+1C Memory Pool (??)
        BYTE uk2[0x4D];                    //+20
        BYTE difficultyLevel;            //+6D (Difficulty 0,1 or 2)
        WORD unknown1;                    //+6E Cube puts 4 here
        DWORD isLODGame;                    //+70 (D2=0 LOD =1) (DWORD ?)
        BYTE uk3[0x04];                    //+71
        WORD unknown2;                    //+78
        BYTE uk4[0x0E];                    //+7A
        NetClient *ptClient;                //+88
        BYTE __8C[0x1C];                    //+8C
        DWORD gameFrame;                    //+A8
        BYTE __AC[0x10];                    //+AC
        ActMap *mapAct[5];                    //+BC
        BYTE ukD0[0x1024];                //+D0
        DWORD *game10F4;                    //+10F4
        BYTE uk6[0x28];                    //+10F8
        Unit *units[0xA00];                //+1120
        Unit *roomtitles[0x200];            //+1B20
    };
    struct Path //(8 dword)
    {                                        //Offset from Code.		Size: 20
        WORD uk1;                        //+00
        WORD mapx;                        //+02
        WORD uk2;                        //+04
        WORD mapy;                        //+06
        DWORD uk3;                        //+08
        DWORD x;                            //+0C
        DWORD y;                            //+10
        DWORD uk6;                        //+14
        DWORD uk7;                        //+18
        Room *ptRoom;                        //+1C
    };
    struct Inventory {                                        //Offset from Code.		Size: 30 to 40
        DWORD tag;                        //+00	= 0x01020304
        BYTE uk1[0x04];                    //+04	=? 0
        Unit *ptChar;                        //+08
        Unit *ptItem;                        //+0C
        BYTE uk2[0x10];                    //+10
        Unit *inventory1;                    //+20
        BYTE uk3[0x04];                    //+24
        DWORD currentUsedSocket;            //+28 //Kingpin : a variable to know how many sockets that have added to item
        DWORD Inventory2C;                //+2C //one value
        DWORD Inventory30;                //+30
        void *ptCorpse;                    //+34
        BYTE uk5[0x04];                    //+38
        DWORD nextCorpseId;                //+3C //max = 15
        BYTE uk6[0x04];                    //+40
    };
    struct D2Stat {
        WORD index;
        WORD id;
        int value;
    };
    struct Stats                //sizeof(Stats)=0x64
    {
        DWORD nUnitId;                //+00
        Unit *ptUnit;                    //+04
        DWORD nUnitType;                //+08
        DWORD nItemNum;                //+0C
        union {
            DWORD flags;                //+10
            struct {
                DWORD fuk1: 13;            //0x00001FFF
                DWORD isDisabled: 1;        //0x00002000
                DWORD fuk2: 17;            //0x7FFFC000
                DWORD dontUseBaseValue: 1;//0x80000000
            };
        };
        DWORD id;                        //+14
        DWORD uk18;                    //+18
        BYTE uk2[0x08];                //+1C
        D2Stat *ptBaseStatsTable;        //+24
        WORD nbBaseStats;            //+28
        WORD sizeOfBaseStatsTable;    //+2A ??
        Stats *ptStats;                //+2C
        BYTE uk3[0x04];                //+30
        Stats *ptItemStats;            //+34
        BYTE uk4[0x04];                //+38
        Stats *ptAffixStats;            //+3C
        Stats *ptNextStats2;            //+40
        union {
            Unit *ptChar;                //+44
            Unit *ptItem;
        };
        D2Stat *ptStatsTable;            //+48
        WORD nbStats;                //+4C
        WORD sizeOfStatsTable;        //+4E ??
        BYTE uk5[0x8];                //+50
        BYTE *unknow0;                //+58 (sizeof(*unknow0)=0x30 (calculated)
        DWORD unknow1;                //+5C (=0)
        DWORD unknow2;                //+60 (=0)
    };
    struct AIControl {
        DWORD specialState;        // +00 SpecialState - stuff like terror, confusion goes here
        void *aiFunction;            // +04 fpAiFunction(); - the primary ai function to call (void * __fastcall)(pGame,pUnit,pAiTickArgs);
        DWORD aiFlags;            // +08 AiFlags
        DWORD ownerGUID;            // +0C OwnerGUID - the global unique identifier of the boss or minion owner
        DWORD ownerType;            // +10 eOwnerType - the unit type of the boss or minion owner
        DWORD args[3];            // +14 dwArgs[3] - three dwords holding custom data used by ai func to store counters (etc)
        void *cmdCurrent;            // +20 pCmdCurrents
        void *cmdLast;            // +24 pCmdLast
        Game *ptGame;                // +28 pGame
        DWORD ownerGUID2;            // +2C OwnerGUID - the same as +008
        DWORD ownerType2;            // +30 eOwnerType - the same as +00C
        void *minionList;            // +34 pMinionList - list of all minions, for boss units (SetBoss in MonStats, Unique, SuperUnique etc)
        DWORD trapNo;                // +3C eTrapNo - used by shadows for summoning traps (so they stick to one type usually)
    };
    struct MonStatsBIN    //size=0x1A8 (424)
    {
        BYTE uk1[0x6];        //+00
        WORD monsterNameID;    //+06
        BYTE uk2[0x168];        //+08
        WORD skill[8];        //+170
        BYTE skillArg[8];    //+180
        BYTE uk3[0x20];        //+188
    };                            //+1A8
    struct MonsterData                    // sizeof(MonsterData)=0x60
    {                                        //Offset from Code.
        MonStatsBIN *ptMonStats;            //+000 - pMonStats - record in monstats.txt
        BYTE components[0x10];    //+004 - Components[16] - bytes holding the component Ids for each component; Order: HD, TR, LG, RA, LA, RH, LH, SH, S1, S2, S3, S4, S5, S6, S7, S8
        WORD seed;                //+014 - NameSeed
        union {
            BYTE flags;                //+016 - TypeFlags
            struct {
                BYTE isOther: 1;            // MONTYPE_OTHER(set for some champs, uniques)
                BYTE isSuperUnique: 1;    // MONTYPE_SUPERUNIQUE
                BYTE isChampion: 1;        // MONTYPE_CHAMPION
                BYTE isUnique: 1;            // MONTYPE_UNIQUE
                BYTE isMinion: 1;            // MONTYPE_MINION
                BYTE isPossessed: 1;        // MONTYPE_POSSESSED
                BYTE isGhostly: 1;        // MONTYPE_GHOSTLY
                BYTE isMultishot: 1;        // MONTYPE_MULTISHOT
            };
        };
        BYTE lastMode;            //+017 - eLastMode
        DWORD duriel;                //+018 - dwDuriel - set only for duriel
        BYTE monUModList[10];    //+01C - MonUModList[9] - nine bytes holding the Ids for each MonUMod assigned to the unit
        DWORD superUniqueID;        //+026
        AIControl *ptAiGeneral;        //+02A
        BYTE uk2[0x32];            //+02E
    };
    struct ObjectData {
        ObjectsBIN *ptObjectsBIN;
        BYTE levelID;
    };
#define F2_ITEM_IS_IDENTIFIED 0x10 //or F_IS_IDENTIFIED ?
    struct ItemData//size=0x74
    {                                        //Offset from Code.
        DWORD quality;                    //+00
        DWORD seedLow;                    //+04
        DWORD seedHi;                        //+08
        DWORD playerID;                    //+0C #10734 / #10735 (getInventory(ptChar)->ptPlayer->0C)
        DWORD seedStarting;                //+10
        DWORD flags1;                        //+14
        union {
            DWORD flags2;                    //+18
            struct {
                DWORD fuk1: 1;                //0x00000001
                DWORD isIndentified: 1;    //0x00000002
                DWORD fuk2: 2;                //0x0000000C
                DWORD isUnindentified: 1;    //0x00000010
                DWORD fuk3: 3;                //0x000000E0
                DWORD isBroken: 1;            //0x00000100
                DWORD fuk4: 2;                //0x00000600
                DWORD isSocketed: 1;        //0x00000800
                DWORD fuk5: 10;            //0x003FF000
                DWORD isEtheral: 1;        //0x00400000
                DWORD fuk6: 3;                //0x03800000
                DWORD isRuneword: 1;        //0x04000000
                DWORD fuk7: 1;                //0x08000000
                DWORD isPersonalized: 1;    //0x10000000
                DWORD fuk8: 3;                //0xE0000000
            };
        };
        DWORD guid1;                        //+1C Global Unique ID 1
        DWORD guid2;                        //+20 Global Unique ID 2
        DWORD guid3;                        //+24 Global Unique ID 3
        DWORD uniqueID;                    //+28
        BYTE ilvl;                        //+2C
        BYTE uk1[0x03];                    //+2D
        WORD version;                    //+30
        WORD rarePrefix;                    //+32
        WORD rareSuffix;                    //+34
        WORD autoPref;                    //+36
        WORD prefix[3];                    //+38
        WORD suffix[3];                    //+3E
        BYTE equipLoc;                    //+44
        BYTE page;                        //+45
        BYTE uk4[0x01];                    //+46
        BYTE ItemData3;                    //+47 //D2Common10854 D2Common10853
        BYTE pEarLevel;                    //+48
        BYTE varGfx;                        //+49
        char IName[0x12];                //+4A //inscribed/ear name
        Inventory *ptInventory;            //+5C
        Unit *ptPrevItem;                    //+60
        Unit *ptNextItem;                    //+64
        BYTE uk8[0x01];                    //+68
        BYTE ItemData2;                    //+69
        BYTE uk9[0x0A];                    //+6A
    };
    struct NetClient {
        DWORD clientID;                    //+00
        BYTE uk1[0x06];                    //+04
        union {                                //+0A
            WORD flag;
            struct {
                WORD f1: 1;
                WORD f2: 1;
                WORD isHardCoreGame: 1;
            };
        };
        BYTE uk2;                        //+0C
        char name[0x10];                    //+0D
        BYTE uk3[0x15F];                    //+1D
        BYTE *savefile;                    //+17C
        DWORD finalSize;                    //+180
        DWORD counter;                    //+184
        DWORD currentSize;                //+188
        BYTE uk4[0x1C];                    //+18C
        Game *ptGame;                        //+1A8

    };
    struct PlayerData {
        char name[0x10];                //+00	Player Name
        void *ptQuest[3];                //+10	Quest Pointers for each difficulty
        BYTE uk1[0x18];                //+1C		//before : 0x14
        void *ptArenaUnit;            //+34	ptArena for the Unit
        BYTE uk2[0x4];                //+38		//before : 0x7
        WORD MPSourcePortalUniqueID;    //+3C	Source Portal Unique_ID
        BYTE uk3[0x2];                //+3E
        WORD MPDestPortalUniqueID;    //+40	Destination Portal Unique_ID
        BYTE uk4[0x06];                //+42
        BYTE ptObjectUnID;            //+48	Object UniqueID for TownPortals
        BYTE uk5[0x53];                //+49
        NetClient *ptNetClient;            //+9C	ptClient
    };
#define F1_IS_SPAWNED 0x10 //or F_IS_IDENTIFIED ?
#define F2_IS_LOD 0x2000000
    struct Unit {                                        //Offset from Code.		Size: 0xF4+4
        DWORD nUnitType;                //+00
        union {
            DWORD nPlayerClass;
            DWORD nTxtFileNo;
        };                                    //+04
        DWORD nUnitId;                //+08
        DWORD nItemNum;                //+0C
        DWORD mode;                    //+10
        union {
            MonsterData *ptMonsterData;
            ObjectData *ptObjectData;
            ItemData *ptItemData;
            PlayerData *ptPlayerData;
        };                                    //+14
        BYTE act;                    //+18
        BYTE uk12[3];                //+19
        void *ptAct;                    //+1C
        DWORD SeedLow;                //+20
        DWORD SeedHi;                    //+24
        DWORD SeedStarting;            //+28
        Path *path;                    //+2C
        BYTE uk1[0x08];                //+30
        Path *ptPos;                    //+38
        DWORD animSpeed;                //+3C
        BYTE uk2[0x04];                //+40
        DWORD curFrame;                //+44
        DWORD remainingFrame;            //+48
        WORD animSpeedW;                //+4C
        BYTE actionFlag;                //+4E
        BYTE uk3[0x1];                //+4F
        void *ptAnimData;                //+50
        BYTE uk4[0x08];                //+54
        Stats *ptStats;                //+5C
        Inventory *ptInventory;            //+60
        BYTE uk5[0x1C];                //+64
        Game *ptGame;                    //+80
        BYTE uk6[0x24];                //+84
        Skills *ptSkills;                //+A8
        void *ptCombatData;            //+AC
        BYTE uk7[0x08];                //+B0
        DWORD itemCode;                //+B8 for an item being dropped by this unit
        BYTE uk8[0x08];                //+BC
        DWORD flags1;                    //+C4
        union {
            DWORD flags2;                //+C8	//flags
            struct {
                DWORD ukf1: 25;
                DWORD isLod: 1;
            };
        };
        BYTE uk9[0x04];                //+CC
        DWORD clientId;                //+D0
        BYTE uk10[0x0C];                //+D4
        Unit *ptFirstMonster;            //+E0
        Unit *Unit1;                    //+E4
        Unit *ptNextUnitInRoom;        //+E8
        BYTE uk11[0x08];                //+EC
        union {
            CBPlayerData *ptCBPlayerData;
            CBItemData *ptCBItemData;
            void *ptCBData;
        };                                    //+F4
    };
}