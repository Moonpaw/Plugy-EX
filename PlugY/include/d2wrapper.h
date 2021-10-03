/******************************************************************************
	File created by Yohann NICOLAS.

	Main Diablo II extra DLL handler.

******************************************************************************/
#pragma once
#include <Windows.h>
#include <VersionInfo.h>

namespace PlugY {
    extern Commons::eGameVersion version_Game;
    extern Commons::eGameVersion version_D2Client;
    extern Commons::eGameVersion version_D2CMP;
    extern Commons::eGameVersion version_D2Common;
    extern Commons::eGameVersion version_D2Game;
    extern Commons::eGameVersion version_D2gfx;
    extern Commons::eGameVersion version_D2Lang;
    extern Commons::eGameVersion version_D2Launch;
    extern Commons::eGameVersion version_D2Net;
    extern Commons::eGameVersion version_D2Win;
    extern Commons::eGameVersion version_Fog;
    extern Commons::eGameVersion version_Storm;
    extern DWORD offset_Game;
    extern DWORD offset_D2Client;
    extern DWORD offset_D2CMP;
    extern DWORD offset_D2Common;
    extern DWORD offset_D2Game;
    extern DWORD offset_D2gfx;
    extern DWORD offset_D2Lang;
    extern DWORD offset_D2Launch;
    extern DWORD offset_D2Net;
    extern DWORD offset_D2Win;
    extern DWORD offset_Fog;
    extern DWORD offset_Storm;
}