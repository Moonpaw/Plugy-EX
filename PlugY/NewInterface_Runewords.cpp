/*=================================================================
	File created by Yohann NICOLAS.

	Interface functions

=================================================================*/

#include "updateServer.h"	// Install_UpdateServer()
#include "plugYFiles.h"		// Install_PlugYImagesFiles()
#include "statsPoints.h"
#include "newInterfaces.h"
#include "common.h"
#include <stdio.h>
#include <string>
#include <iostream>

#define NB_RUNES_PER_PAGE 25

#define	getXCloseBtn()			360
#define	getLCloseBtn()			32
#define	getYCloseBtn()			RY(0x50)//40//(ResolutionY - 60)
#define	getHCloseBtn()			32
#define isOnCloseBtn(x,y) isOnRect(x, y, getXCloseBtn(), getYCloseBtn(), getLCloseBtn(), getHCloseBtn())

#define	getXNextPageBtn()		RX(D2GetResolution()?0xBA:0xBA)//0x43:0x8A
#define	getLNextPageBtn()		32
#define	getYNextPageBtn()		RY(D2GetResolution()?0x50:0x50)//40:0x70
#define	getHNextPageBtn()		32
#define isOnNextPageBtn(x,y)	isOnRect(x, y, getXNextPageBtn(), getYNextPageBtn(), getLNextPageBtn(), getHNextPageBtn())

#define	getXPrevRunesBtn()		107
#define	getLPrevRunesBtn()		32
#define	getYPrevRunesBtn()		RY(D2GetResolution()?0x50:0x50)//40:0x70
#define	getHPrevRunesBtn()		32
#define isOnPrevRunesBtn(x,y)	isOnRect(x, y, getXPrevRunesBtn(), getYPrevRunesBtn(), getLPrevRunesBtn(), getHPrevRunesBtn())

#define	getXNextRunesBtn()		RX(0x95)//0x70 //19
#define	getLNextRunesBtn()		32
#define	getYNextRunesBtn()		RY(D2GetResolution()?0x50:0x50)//40:0x70
#define	getHNextRunesBtn()		32
#define isOnNextRunesBtn(x,y)	isOnRect(x, y, getXNextRunesBtn(), getYNextRunesBtn(), getLNextRunesBtn(), getHNextRunesBtn())

#define	getXTwoRunesBtn()		RX(0x6B)//0x70 //19
#define	getLTwoRunesBtn()		32
#define	getYTwoRunesBtn()		RY(D2GetResolution()?0x7A:0x7A)//40:0x70
#define	getHTwoRunesBtn()		32
#define isOnTwoRunesBtn(x,y)	isOnRect(x, y, getXTwoRunesBtn(), getYTwoRunesBtn(), getLTwoRunesBtn(), getHTwoRunesBtn())

#define	getXThreeRunesBtn()		RX(0x95)//0x70 //19
#define	getLThreeRunesBtn()		32
#define	getYThreeRunesBtn()		RY(D2GetResolution()?0x7A:0x7A)//40:0x70
#define	getHThreeRunesBtn()		32
#define isOnThreeRunesBtn(x,y)	isOnRect(x, y, getXThreeRunesBtn(), getYThreeRunesBtn(), getLThreeRunesBtn(), getHThreeRunesBtn())

#define	getXFourRunesBtn()		RX(0xBF)//0x70 //19
#define	getLFourRunesBtn()		32
#define	getYFourRunesBtn()		RY(D2GetResolution()?0x7A:0x7A)//40:0x70
#define	getHFourRunesBtn()		32
#define isOnFourRunesBtn(x,y)	isOnRect(x, y, getXFourRunesBtn(), getYFourRunesBtn(), getLFourRunesBtn(), getHFourRunesBtn())

#define	getXFiveRunesBtn()		RX(0xE9)//0x70 //19
#define	getLFiveRunesBtn()		32
#define	getYFiveRunesBtn()		RY(D2GetResolution()?0x7A:0x7A)//40:0x70
#define	getHFiveRunesBtn()		32
#define isOnFiveRunesBtn(x,y)	isOnRect(x, y, getXFiveRunesBtn(), getYFiveRunesBtn(), getLFiveRunesBtn(), getHFiveRunesBtn())

#define	getXSixRunesBtn()		RX(0x113)//0x70 //19
#define	getLSixRunesBtn()		32
#define	getYSixRunesBtn()		RY(D2GetResolution()?0x7A:0x7A)//40:0x70
#define	getHSixRunesBtn()		32
#define isOnSixRunesBtn(x,y)	isOnRect(x, y, getXSixRunesBtn(), getYSixRunesBtn(), getLSixRunesBtn(), getHSixRunesBtn())


//Itemtype filtering
//#define	getXShowWepBtn()		RX(0x13D)//0x70 //19
//#define	getLShowWepBtn()		32
//#define	getYShowWepBtn()		RY(D2GetResolution()?0x7A:0x7A)//40:0x70
//#define	getHShowWepBtn()		32
//#define isOnShowWepBtn(x,y)	isOnRect(x, y, getXShowWepBtn(), getYShowWepBtn(), getLShowWepBtn(), getHShowWepBtn())
//
//#define	getXShowArmorBtn()		RX(0x167)//0x70 //19
//#define	getLShowArmorBtn()		32
//#define	getYShowArmorBtn()		RY(D2GetResolution()?0x7A:0x7A)//40:0x70
//#define	getHShowArmorBtn()		32
//#define isOnShowArmorBtn(x,y)	isOnRect(x, y, getXShowArmorBtn(), getYShowArmorBtn(), getLShowArmorBtn(), getHShowArmorBtn())
//
//#define	getXShowCharmsBtn()		RX(0x191)//0x70 //19
//#define	getLShowCharmsBtn()		32
//#define	getYShowCharmsBtn()		RY(D2GetResolution()?0x7A:0x7A)//40:0x70
//#define	getHShowCharmsBtn()		32
//#define isOnShowCharmsBtn(x,y)	isOnRect(x, y, getXShowCharmsBtn(), getYShowCharmsBtn(), getLShowCharmsBtn(), getHShowCharmsBtn())
//std::string weps = " 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 42, 43, 44, 45, 46, 47, 48, 49, 55, 56, 57, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 85, 86, 87, 88, 112, 123, 124, 125,";
//std::string arms = " 2, 3, 15, 16, 19, 37, 50, 51, 70, 71, 72, 73, 75,";
//std::string charms = " 13, 83, 84, 106, 107, 108, 119, 120, 121, 138,";
//std::string allowedTypes = weps + arms + charms;


int curRunesPage=0;
int maxRunesPage=0xFFFF;
bool twoRunes = true;
bool threeRunes = true;
bool fourRunes = true;
bool fiveRunes = true;
bool sixRunes = true;
bool showarmors = true;
bool showweapons = true;
bool showcharms = true;
bool runewordRects[25];
RunesBIN* runesOnPage[25];

static struct
{
	union{
		DWORD all;
		struct{
			DWORD close:1;
			DWORD nextPage:1;
			DWORD prevRunes:1;
			DWORD nextRunes:1;
			DWORD twoRunes:1;
			DWORD threeRunes:1;
			DWORD fourRunes:1;
			DWORD fiveRunes:1;
			DWORD sixRunes : 1;
			DWORD armors : 1;
			DWORD weapons : 1;
			DWORD charms : 1;
		};
	};
} isDownBtn;


void printRuneword(RunesBIN* runesData, DWORD pos)
{
	WCHAR temp[50];
	WCHAR runesList[50];
	WCHAR typesList[50];
	int x = 250;
	LPWSTR lpText = D2GetStringFromIndex(runesData->RuneNameID);
	D2SetFont(6);
	DWORD nbPixel = D2GetPixelLen(lpText);
	DWORD x1 = (nbPixel >= x) ? 0 : x-nbPixel;
	D2PrintString(lpText, x1, 100 + pos*20, GOLD, 0);//MILIEU(0x00,0x70,nbPixel)

	typesList[0]=L'\0';
	DWORD numItype=0;
	while (numItype<6)
	{
		WORD type = runesData->Itypes[numItype];
		if (!type) break;
		ItemTypesBIN* itemTypeData = D2GetItemTypesBIN(type);
		LPCWSTR typeName = getLocalTypeString(itemTypeData->code);
		if (numItype) wcscat(typesList,L"/");
		wcscat(typesList, typeName);
		numItype++;
	}
	nbPixel = D2GetPixelLen(typesList);
	x1 = (nbPixel >= x) ? 0 : x-nbPixel;
	D2PrintString(typesList, x1, 110 + pos*20, WHITE, 0);//MILIEU(0x70,0xA0,nbPixel)

	runesList[0]=L'\0';
	DWORD numRune=0;
	int curRuneID = runesData->Runes[0];
	while ((curRuneID>0) && (numRune<6))
	{
		ItemsBIN* itemsData = D2GetItemsBIN(curRuneID);
		d2_assert( !itemsData , "itemsData", __FILE__, __LINE__);
		GemsBIN* gemData = D2GetGemsBIN(itemsData->GemOffset);
		if (gemData) {
		d2_assert( !gemData , "gemData", __FILE__, __LINE__);
		mbstowcs(temp, gemData->letter, 50);
		if (numRune) wcscat(runesList,L" ");
//		else wcscat(runesList,L"");
		wcscat(runesList,temp);}
		numRune++;
		curRuneID = runesData->Runes[numRune];
	}
//	wcscat(runesList,L"");
	D2SetFont(1);
	DWORD y1;
	nbPixel = D2GetPixelLen(runesList);
	if (nbPixel>x)
	{
		D2SetFont(6);
		nbPixel = D2GetPixelLen(runesList);
		y1=106;
		x1 = nbPixel>x ? x+200-nbPixel : x+9;
	} else {
		x1=x+10;
		y1=108;
	}

//	x1 = (nbPixel < 145) ? 155 : 300-nbPixel;
	D2PrintString(runesList, x1, y1 + pos*20, WHITE, 0);//MILIEU(0xD0,0xA0,nbPixel)
}

//static RunesBIN* CachedGlobalRunesBin = nullptr;


#define BUFSIZE 0x80
//6FB21FAA
void STDCALL printRunewordsPage()
{
	//if (!CachedGlobalRunesBin)
	//{
	//	CachedGlobalRunesBin = D2GetRunesBIN(1);
	//}

	


	if (!D2isLODGame() || !D2GetResolution()) return D2PrintStatsPage();
	
	LPWSTR lpText;
	bDontPrintBorder = true;

	//Init data for print image
	sDrawImageInfo data;
	ZeroMemory(&data,sizeof(data));

	//print background
	fillRect(RX(0), RY(816), 512, 768, 0, 5);//552
	setImage(&data, newStatsInterfaceImages);
	setFrame(&data, 0);
	D2PrintImage(&data, RX(0), RY(512), -1, 5, 0);
	setFrame(&data, 1);
	D2PrintImage(&data, RX(256), RY(512), -1, 5, 0);//256
	setFrame(&data, 2);
	D2PrintImage(&data, RX(0), RY(256), -1, 5, 0);//432
	setFrame(&data, 3);
	D2PrintImage(&data, RX(256), RY(256), -1, 5, 0);
	setFrame(&data, 4);
	D2PrintImage(&data, RX(0), RY(0), -1, 5, 0);
	setFrame(&data, 5);
	D2PrintImage(&data, RX(256), RY(0), -1, 5, 0);

	//print button close
	setImage(&data, D2LoadBuySelBtn());
	setFrame(&data, 10 + isDownBtn.close);
	D2PrintImage(&data, getXCloseBtn(), getYCloseBtn(), -1, 5, 0);
	
	//print next page button
	setImage(&data, stashBtnsImages);
	setFrame(&data, 2 + isDownBtn.nextPage);
	D2PrintImage(&data, getXNextPageBtn(), getYNextPageBtn(), -1, 5, 0);

	//print previous runes button
	setImage(&data, stashBtnsImages);
	setFrame(&data, isDownBtn.prevRunes);
	D2PrintImage(&data, getXPrevRunesBtn(), getYPrevRunesBtn(), -1, 5, 0);

	//print previous runes button
	setFrame(&data, 2 + isDownBtn.nextRunes);
	D2PrintImage(&data, getXNextRunesBtn(), getYNextRunesBtn(), -1, 5, 0);
	
	//print two runes button
	setFrame(&data, 12 + twoRunes);
	D2PrintImage(&data, getXTwoRunesBtn(), getYTwoRunesBtn(), -1, 5, 0);

	setFrame(&data, 14 + threeRunes);
	D2PrintImage(&data, getXThreeRunesBtn(), getYThreeRunesBtn(), -1, 5, 0);

	setFrame(&data, 16 + fourRunes);
	D2PrintImage(&data, getXFourRunesBtn(), getYFourRunesBtn(), -1, 5, 0);

	setFrame(&data, 18 + fiveRunes);
	D2PrintImage(&data, getXFiveRunesBtn(), getYFiveRunesBtn(), -1, 5, 0);

	setFrame(&data, 20 + sixRunes);
	D2PrintImage(&data, getXSixRunesBtn(), getYSixRunesBtn(), -1, 5, 0);
	
	//Itemtype filtering
	/*setFrame(&data, 22 + showweapons);
	D2PrintImage(&data, getXShowWepBtn(), getYShowWepBtn(), -1, 5, 0);
	
	setFrame(&data, 24 + showarmors);
	D2PrintImage(&data, getXShowArmorBtn(), getYShowArmorBtn(), -1, 5, 0);
	
	setFrame(&data, 26 + showcharms);
	D2PrintImage(&data, getXShowCharmsBtn(), getYShowCharmsBtn(), -1, 5, 0);*/

	D2SetFont(6);

	//146;//B400
	int nbRunes = *D2GetNbRunesBIN();
	RunesBIN* runesFirst = nbRunes>1 ? D2GetRunesBIN(1) - 1 : NULL;
	RunesBIN* runesLast = runesFirst ? runesFirst + nbRunes : NULL;
//	log_msg("nbRunes(%d,%d) runesFirst(%08X, %08X) runesLast(%08X, %08X)",nbRunes,SgptDataTables->nbRunes,runesFirst, SgptDataTables->runes,runesLast,SgptDataTables->runes + SgptDataTables->nbRunes);
 
	int nbRunesCompleted=0;
	int runewordsOnPage = 0;
	int matchingRunewords=0;
	for (int j = 0; j < 25; j++)
	{
		runewordRects[j] = false;
		runesOnPage[j] = nullptr;
	}
	
	if (showarmors || showcharms || showweapons)
	{
		DWORD curNbRunes = 0;
		for (RunesBIN* runesData = runesFirst; runesData < runesLast; runesData++)
		{
			if (!runesData->Complete || runesData->Server) continue;
			nbRunesCompleted++;
			int runecount = 0;
			//Itemtype filtering
			//bool containsAllowedType = false;
			for (int i = 0; i < 6; i++)
			{
				if (runesData->Runes[i] > -1)
				{
					runecount++;
				}
				//Itemtype filtering
			/*	if (runewordsOnPage < NB_RUNES_PER_PAGE)
				{
					if (!containsAllowedType && runesData->Itypes[i] > 0 && allowedTypes.find(" " + std::to_string(runesData->Itypes[i]) + ",") != std::string::npos)
					{
						containsAllowedType = true;
					}
				}*/
			}
			//if ((curRunesPage * NB_RUNES_PER_PAGE < nbRunesCompleted) &&
			//	(nbRunesCompleted <= (curRunesPage + 1) * NB_RUNES_PER_PAGE)
			//if (containsAllowedType && runewordsOnPage < NB_RUNES_PER_PAGE
			if (runewordsOnPage < NB_RUNES_PER_PAGE
				&& ((runecount == 2 && twoRunes)
					|| (runecount == 3 && threeRunes)
					|| (runecount == 4 && fourRunes)
					|| (runecount == 5 && fiveRunes)
					|| (runecount == 6 && sixRunes)))
			{
				matchingRunewords++;
				if (matchingRunewords > curRunesPage * NB_RUNES_PER_PAGE
					&& matchingRunewords <= (curRunesPage + 1) * NB_RUNES_PER_PAGE)
				{
					runesOnPage[runewordsOnPage] = runesData;
					runewordRects[runewordsOnPage] = true;
					printRuneword(runesData, curNbRunes++);
					runewordsOnPage++;
				}
			}
			else if ((curRunesPage * NB_RUNES_PER_PAGE > nbRunesCompleted))
			{

				for (int j = runewordsOnPage; j < 25; j++)
				{
					runewordRects[j] = false;
				}
			}
		}
	}
	maxRunesPage = nbRunesCompleted ?  (nbRunesCompleted-1) / NB_RUNES_PER_PAGE : 0;


//////////////////// POPUP PRINTING ////////////////////
	//set MouseX & MouseY
	DWORD x = D2GetMouseX();
	DWORD y = D2GetMouseY();

	if (isOnCloseBtn(x,y))			// print popup "close"
	{
		D2PrintPopup(D2GetStringFromIndex(0x1030), getXCloseBtn()+getLCloseBtn()/2, getYCloseBtn()-getHCloseBtn(), WHITE, 1);
	}
	else if (isOnNextPageBtn(x,y))	// print popup "next page"
	{
		lpText = getLocalString(STR_NEXT_PAGE);
		D2PrintPopup(lpText, getXNextPageBtn()+getLNextPageBtn()/2, getYNextPageBtn()-getHNextPageBtn(), WHITE, 1);
	}
	
	//Show runeword properties as floating text
	//if (x >= 125 && x <= 250)
	//{
	//	//mouse isnt in spalte für runewort namen?
	//	int yRunewordRect = (y - 90) / 20;
	//	if (yRunewordRect < 25 && runewordRects[yRunewordRect])
	//	{
	//		RunesBIN* runesData = runesOnPage[yRunewordRect];
	//		LPWSTR lpText = D2GetStringFromIndex(runesData->t1code1);
	//		/*std::string text = "Runeword";
	//		wchar_t wtext[255];
	//		mbstowcs(wtext, text.c_str(), text.length());
	//		LPWSTR ptr = wtext;*/
	//		D2PrintPopup(lpText, 175, 90 + (yRunewordRect*20), WHITE, 1);
	//	}
	//}
	//runeword bonus display
	//Unit* ptChar = D2GetClientPlayer();
}

//////////////////////////////////////////////////////////////////////////////////////////////

DWORD STDCALL mouseRunewordsPageLeftDown(sWinMessage* msg)
{
	if (!D2isLODGame() || !D2GetResolution()) return -1;

	if (!isOnStatsPage(msg->x,msg->y)) return 1;

	if (isOnCloseBtn(msg->x,msg->y))
	{
		log_msg("push down left button close\n");
		isDownBtn.close = 1;
		D2PlaySound(4,0,0,0,0);
	}
	else if (isOnNextPageBtn(msg->x,msg->y))
	{
		log_msg("push down left button next page\n");
		isDownBtn.nextPage = 1;
		D2PlaySound(4,0,0,0,0);
	}
	else if (isOnPrevRunesBtn(msg->x,msg->y))
	{
		log_msg("push down left button prev page\n");
		isDownBtn.prevRunes = 1;
		D2PlaySound(4,0,0,0,0);
	}
	else if (isOnNextRunesBtn(msg->x, msg->y))
	{
		log_msg("push down left button next runes\n");
		isDownBtn.nextRunes = 1;
		D2PlaySound(4, 0, 0, 0, 0);
	}
	else if (isOnTwoRunesBtn(msg->x, msg->y))
	{
		log_msg("push down left button two runes\n");
		isDownBtn.twoRunes = 1;
		D2PlaySound(4, 0, 0, 0, 0);
	}
	else if (isOnThreeRunesBtn(msg->x, msg->y))
	{
		log_msg("push down left button 3 runes\n");
		isDownBtn.threeRunes = 1;
		D2PlaySound(4, 0, 0, 0, 0);
	}
	else if (isOnFourRunesBtn(msg->x, msg->y))
	{
		log_msg("push down left button 4 runes\n");
		isDownBtn.fourRunes = 1;
		D2PlaySound(4, 0, 0, 0, 0);
	}
	else if (isOnFiveRunesBtn(msg->x, msg->y))
	{
		log_msg("push down left button 5 runes\n");
		isDownBtn.fiveRunes = 1;
		D2PlaySound(4, 0, 0, 0, 0);
	}
	else if (isOnSixRunesBtn(msg->x, msg->y))
	{
		log_msg("push down left button 6 runes\n");
		isDownBtn.sixRunes = 1;
		D2PlaySound(4, 0, 0, 0, 0);
	}
	//Itemtype filtering
	/*else if (isOnShowWepBtn(msg->x, msg->y))
	{
		log_msg("push down left button show weapons\n");
		isDownBtn.weapons = 1;
		D2PlaySound(4, 0, 0, 0, 0);
	}
	else if (isOnShowArmorBtn(msg->x, msg->y))
	{
		log_msg("push down left button show armor\n");
		isDownBtn.armors = 1;
		D2PlaySound(4, 0, 0, 0, 0);
	}
	else if (isOnShowCharmsBtn(msg->x, msg->y))
	{
		log_msg("push down left button show charms\n");
		isDownBtn.charms = 1;
		D2PlaySound(4, 0, 0, 0, 0);
	}*/


	freeMessage(msg);
	return 0;
}


DWORD STDCALL mouseRunewordsPageLeftUp(sWinMessage* msg)
{
	if (!D2isLODGame() || !D2GetResolution()) return -1;

	if (!isOnStatsPage(msg->x,msg->y)) return 1;

	if (isOnCloseBtn(msg->x,msg->y))
	{
		log_msg("push up left button close\n");
		//if (isDownBtn.close)
			D2TogglePage(2,1,0);
	}
	else if (isOnNextPageBtn(msg->x,msg->y))
	{
		log_msg("push up left button next page\n");
		/*if (isDownBtn.nextPage)
		{*/
			GoStatPage(GetCurrentPage()+1);
			log_msg("next page press\n");
		//}
	}
	else if (isOnPrevRunesBtn(msg->x,msg->y))
	{
		log_msg("push up left button prev runes\n");
		/*if (isDownBtn.prevRunes)
		{*/
			if (curRunesPage) 
				curRunesPage--;
		//}
	}
	else if (isOnNextRunesBtn(msg->x, msg->y))
	{
		log_msg("push up left button next runes\n");
		/*if (isDownBtn.nextRunes)
		{*/
		if (curRunesPage < maxRunesPage)
			curRunesPage++;
		/*}*/
	}
	else if (isOnTwoRunesBtn(msg->x, msg->y))
	{
		log_msg("push up left button two runes filter\n");
		twoRunes = !twoRunes;
	}

	else if (isOnThreeRunesBtn(msg->x, msg->y))
	{
		log_msg("push up left button two runes filter\n");
		threeRunes = !threeRunes;
	}

	else if (isOnFourRunesBtn(msg->x, msg->y))
	{
		log_msg("push up left button two runes filter\n");
		fourRunes = !fourRunes;
	}

	else if (isOnFiveRunesBtn(msg->x, msg->y))
	{
		log_msg("push up left button two runes filter\n");
		fiveRunes = !fiveRunes;
	}

	else if (isOnSixRunesBtn(msg->x, msg->y))
	{
		log_msg("push up left button two runes filter\n");
		sixRunes = !sixRunes;
	}
	//Itemtype filtering
	/*else if (isOnShowWepBtn(msg->x, msg->y))
	{
		log_msg("push up left button showweapons filter\n");
		showweapons = !showweapons;
		allowedTypes = "";
		if (showweapons)
		{
			allowedTypes += weps;
		}
		if (showarmors)
		{
			allowedTypes += arms;
		}
		if (showcharms)
		{
			allowedTypes += charms;
		}
	}
	else if (isOnShowArmorBtn(msg->x, msg->y))
	{
		log_msg("push up left button showarmors filter\n");
		showarmors = !showarmors;
		allowedTypes = "";
		if (showweapons)
		{
			allowedTypes += weps;
		}
		if (showarmors)
		{
			allowedTypes += arms;
		}
		if (showcharms)
		{
			allowedTypes += charms;
		}
	}
	else if (isOnShowCharmsBtn(msg->x, msg->y))
	{
		log_msg("push up left button showcharms filter\n");
		showcharms = !showcharms;
		allowedTypes = "";
		if (showweapons)
		{
			allowedTypes += weps;
		}
		if (showarmors)
		{
			allowedTypes += arms;
		}
		if (showcharms)
		{
			allowedTypes += charms;
		}
	}*/

	D2CleanStatMouseUp();
	freeMessage(msg);
	isDownBtn.all=0;
	return 0;
}





/*================================= END OF FILE =================================*/