/*=================================================================
	File created by Yohann NICOLAS.

	New Interfaces functions

=================================================================*/
#pragma once

#include "common.h"
#include <stdio.h>
#include <string>
#include <iostream>

#define MILIEU(X,L,N) (X + ((N<L)? (L-N)/2 : 0))
#define isOnStatsPage(x,y)		((x<592) && (y<889))

extern DWORD bDontPrintBorder;
extern int extraHiddenPage;

void GoNextStatPage();
void GoPreviousStatPage();
void GoStatPage(int page);
int GetCurrentPage();

extern bool active_newInterfaces;
extern bool selectMainPageOnOpenning;
extern bool printBackgroundOnMainPage;

void Install_NewInterfaces();

/*================================= END OF FILE =================================*/