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

inline int findVersionOrDefault(int dll, int defaultValue) {
    auto result = dllVersions.find(dll);
    return result != dllVersions.end() ? result->second : defaultValue;
}

inline int findOffsetOrDefault(int dll, int defaultValue) {
    auto result = dllOffsets.find(dll);
    return result != dllOffsets.end() ? result->second : defaultValue;
}

inline int r8(int d2DllName, int defaultValue, int B, int C, int D, int E, int F, int G, int H, int I) {
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
    auto ver = findVersionOrDefault(d2DllName, defaultValue);
    auto offset = findOffsetOrDefault(d2DllName, defaultValue);
    return offset + ver;
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

/* Warning, never include code like this.. */
#include "../Commons/D2Macros.h"

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
