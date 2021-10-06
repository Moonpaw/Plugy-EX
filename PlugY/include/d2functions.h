#pragma once

#include <map>
#include "D2TypeDefMacros.h"
#include "d2wrapper.h"
#include <VersionInfo.h>
#include <D2UnitStruct.h>

namespace PlugY {
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

    extern inline int RANDOM(int V) {
        return int(rand() / (RAND_MAX + 1.0) * (V));
    }

    extern inline double RANDOMF() {
        return (double) rand() / (double) RAND_MAX;
    }

    extern inline Commons::PlayerData *getPlayerData(const Commons::Unit *ptChar) {
        return (*(Commons::PlayerData **) ((DWORD) (ptChar) + shifting.ptSpecificData));
    }

    extern inline Commons::Game *getGame(const Commons::Unit *ptChar) {
        return (*(Commons::Game **) ((DWORD) (ptChar) + shifting.ptGame));
    }

    extern inline Commons::Game *getClientGame(const Commons::NetClient *ptClient) {
        return (*(Commons::Game**)((DWORD)(ptClient)+shifting.ptClientGame));
    }

#define PCInventory (*(Inventory**)((DWORD)(ptChar)+shifting.ptInventory)) //->ptInventory
#define PCPY ((PYPlayerData*)((DWORD)getPlayerData(ptChar)+shifting.ptPYPlayerData)) //->ptPYPlayerData

//#define PCSkills (*(Skills**)((DWORD)(ptChar)+shifting.ptSkills)) //->ptSkills
    extern inline Commons::Skills *PCSkills(Commons::Unit *ptChar) { return (*(Commons::Skills **) ((DWORD) (ptChar) + shifting.ptSkills)); }

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
    extern std::map<D2DllName, Commons::eGameVersion> dllVersions;
    extern std::map<D2DllName, DWORD> dllOffsets;

    extern inline Commons::eGameVersion findVersionOrDefault(D2DllName d2DllName) {
        auto result = dllVersions.find(d2DllName);
        return result != dllVersions.end() ? result->second : Commons::UNKNOWN;
    }

    extern inline DWORD findOffsetOrDefault(D2DllName d2DllName, DWORD defaultValue) {
        auto result = dllOffsets.find(d2DllName);
        return result != dllOffsets.end() ? result->second : defaultValue;
    }

//    extern DWORD r8(D2DllName d2DllName, DWORD defaultValue, DWORD v109d, DWORD v110, DWORD v111, DWORD v111b, DWORD v112, DWORD v113c, DWORD v113d, DWORD v114d);

    extern DWORD getAddressOfVersion(Commons::eGameVersion version, DWORD defaultValue, DWORD v109d, DWORD v110, DWORD v111, DWORD v111b, DWORD v112, DWORD v113c, DWORD v113d, DWORD v114d = 0);

    extern DWORD RX(DWORD v);
    extern DWORD RY(DWORD y);
    extern Commons::DataTables *SgptDataTables;
    extern TD2AddPlayerStat V2AddPlayerStat;
    extern TD2GetGameByClientID V2GetGameByClientID;
    extern TD2SpawnSuperUnique V2SpawnSuperUnique;
    extern TD2SpawnMonster V2SpawnMonster;
    extern TD2Game235C0 V2Game235C0;
    extern TD2ReadFile V2ReadFile;

    extern WORD (*getDescStrPos)(DWORD statID);

    extern void *(__stdcall *compileTxtFile)(DWORD unused, const char *filename, Commons::BINField *ptFields, DWORD *ptRecordCount, DWORD recordLength);

    void setImage(Commons::sDrawImageInfo *data, void *image);

    void setFrame(Commons::sDrawImageInfo *data, DWORD frame);

    void __inline fillRect(DWORD x, DWORD y, DWORD Width, DWORD Height, DWORD color, DWORD transTbl) {
        D2FillArea(x, y, x + Width, y + Height, color, transTbl);
    }

//#define GameTypeMode (*ptGameTypeMode)
    void init_dll_maps();
    void initD2functions();
}