#pragma once

#include <Windows.h>
#include "d2BinFile.h"

namespace Commons {
    struct Unit;
    struct Game;
    struct Room;
#pragma pack(1)
    struct sWinMessage {
        DWORD msg;
        DWORD type;
        DWORD key;
        WORD x;
        WORD y;
        DWORD uk3;
        DWORD uk4;
        DWORD managed;
        DWORD unmanaged;
    };
#pragma pack()
    struct sDrawImageInfo//size = 0x48
    {
        DWORD uk1;
        DWORD uk2;
        void *image;
        DWORD uk3;
        DWORD uk4;
        void *reserved;
        DWORD uk5[0xB];
        DWORD frame;
    };
    struct saveBitField {
        BYTE *data;
        DWORD maxBits;
        DWORD currentByte;
        DWORD currentBit;
        DWORD overflaw;
    };
    struct BINField {
        char *fieldName;
        int type;
        DWORD strLength;
        DWORD offset;
        void *lookup;
    };
    struct ItemGenerationData //size=0x84
    {
        Unit *ptMonster;        //+00
        BYTE uk1[0x04];        //+04
        Game *ptGame;            //+08
        DWORD ilvl;            //+0C
        BYTE uk2[0x04];        //+10
        DWORD nTxtFileNo;        //+14
        DWORD unknow1;        //+18
        DWORD x;                //+1C
        DWORD y;                //+20
        Room *ptRoom;            //+24
        WORD unknow2;        //+28
        WORD gameUnknown2;    //+2A
        BYTE uk3[0x04];        //+2C
        DWORD quality;        //+30
        BYTE uk4[0x34];        //+34
        int prefixID[3];    //+68 (-1: no prefix; 0:random prefix)
        int suffixID[3];    //+74 (-1: no suffix; 0:random suffix)
        union {                    //+80
            DWORD flags;
            struct {
                DWORD fuk1: 5;        //0x0000001F
                DWORD unknow3: 1;    //0x00000020
            };
        };
    };
    struct AIParam {
        void *control;            //+0x00
        void *u_0x04;             //+0x04
        Unit *target;                //+0x08
        void *u_0x0C;             //+0x0C
        void *u_0x10;             //+0x10
        DWORD distanceToTarget;   //+0x14
        BOOL engagedInCombat;    //+0x18
        MonStatsBIN *ptMonStatsBIN;        //+0x1C
        void *ptMonStats2BIN;        //+0x20
    };

/*=================================================================*/
/*   Data Structure to Update Client                               */
/*=================================================================*/
    struct DataPacket {
        BYTE mType;            // +00 Packet Type
        BYTE mFunc;            // +02 Function to Call
        BYTE mSize;            // +04 Size of the Packet
        DWORD mReserved;    // +06 Used with items
        BYTE mUnitType;        // +0A Always '0'
        DWORD mPlayerID;    // +0C The Player ID (ptUnit + 08h)
        DWORD mItemID;        // +10 The Item ID
        DWORD mMod1_ID;        // +14 The Stat/Mod ID
        DWORD mParam1;        // +18 3 Paramters
        DWORD mParam2;        // +1C
        DWORD mParam3;        // +20
    };
}