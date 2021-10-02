#pragma once

#include <map>
#include "D2TypeDefMacros.h"
#include "d2wrapper.h"
#include <VersionInfo.h>

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
#define FASTCALL __fastcall
#define STDCALL        __stdcall

    extern inline int RANDOM(int V) {
        return int(rand() / (RAND_MAX + 1.0) * (V));
    }

    extern inline double RANDOMF() {
        return (double) rand() / (double) RAND_MAX;
    }

#define PCPlayerData (*(PlayerData**)((DWORD)(ptChar)+shifting.ptSpecificData)) //->ptPlayerData
#define PCGame (*(Game**)((DWORD)(ptChar)+shifting.ptGame)) //->ptGame
#define PClientGame (*(Game**)((DWORD)(ptClient)+shifting.ptClientGame)) //ptClient->ptGame
#define PCInventory (*(Inventory**)((DWORD)(ptChar)+shifting.ptInventory)) //->ptInventory
#define PCPY ((PYPlayerData*)((DWORD)PCPlayerData+shifting.ptPYPlayerData)) //->ptPYPlayerData

//#define PCSkills (*(Skills**)((DWORD)(ptChar)+shifting.ptSkills)) //->ptSkills
    extern inline Commons::Skills *PCSkills(Commons::Unit *ptChar) { return (*(Commons::Skills **) ((DWORD) (ptChar) + shifting.ptSkills)); }

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
    extern std::map<int, int> dllVersions;
    extern std::map<int, int> dllOffsets;

    extern inline int findVersionOrDefault(int d2DllName, int defaultValue) {
        auto result = dllVersions.find(d2DllName);
        return result != dllVersions.end() ? result->second : defaultValue;
    }

    extern inline int findOffsetOrDefault(int d2DllName, int defaultValue) {
        auto result = dllOffsets.find(d2DllName);
        return result != dllOffsets.end() ? result->second : defaultValue;
    }

    extern int r8(DWORD d2DllName, DWORD defaultValue, int B, int C, int D, int E, int F, int G, int H, int I);

    extern int v8(int version, int defaultValue, int B, int C, int D, int E, int F, int G, int H, int I);

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

    extern void *(STDCALL *compileTxtFile)(DWORD unused, const char *filename, Commons::BINField *ptFields, DWORD *ptRecordCount, DWORD recordLength);

    void setImage(Commons::sDrawImageInfo *data, void *image);

    void setFrame(Commons::sDrawImageInfo *data, DWORD frame);

    void __inline fillRect(DWORD x, DWORD y, DWORD Width, DWORD Height, DWORD color, DWORD transTbl) {
        D2FillArea(x, y, x + Width, y + Height, color, transTbl);
    }

//#define GameTypeMode (*ptGameTypeMode)

    void initD2functions();
}