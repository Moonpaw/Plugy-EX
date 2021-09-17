/*=================================================================
	File created by Yohann NICOLAS.

	New runeword Interface

=================================================================*/
#pragma once

#include "common.h"

void STDCALL printRunewordsPage();
void ResetRunes();
void EnsureGlobalRunesAreCached();
void LogRunewords();
void LogItypes(RunesBIN* runeword);
bool RuneCountMatchesLengthFilter(int runecount);
bool IsUnexpectedGameType();
void PrintRuneFilterButtons(sDrawImageInfo& data);
void PrintNextRunesButton(sDrawImageInfo& data);
void PrintPreviousRunesButton(sDrawImageInfo& data);
void PrintNextPageButton(sDrawImageInfo& data);
void PrintCloseButton(sDrawImageInfo& data);
void PrintBackground(sDrawImageInfo& data);
void PrintPopupRunewords(LPWSTR& lpText);
DWORD STDCALL mouseRunewordsPageLeftDown(sWinMessage* msg);
DWORD STDCALL mouseRunewordsPageLeftUp(sWinMessage* msg);

void ToggleButton();

void UpdateAllowedTypes();

/*================================= END OF FILE =================================*/
