#include "updateServer.h"
#include "plugYFiles.h"
#include "statsPoints.h"
#include "newInterfaces.h"
#include "common.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include "newInterface_Runewords.h"

using std::vector;
using std::find;

constexpr auto RunesPerPage = 25;
constexpr auto ButtonHeight = 32;
constexpr auto ButtonLength = 32;

constexpr auto getXCloseBtn() { return 360; }
constexpr auto getYCloseBtn() { return RY(0x50); }

auto isOnCloseBtn(DWORD x, DWORD y) { return isOnRect(x, y, getXCloseBtn(), getYCloseBtn(), ButtonLength, ButtonHeight); }

constexpr auto getXNextPageBtn() { return RX(0xBA); }
constexpr auto getYNextPageBtn() { return RY(0x50); }

auto isOnNextPageBtn(DWORD x, DWORD y) { return isOnRect(x, y, getXNextPageBtn(), getYNextPageBtn(), ButtonLength, ButtonHeight); }

constexpr auto getXPrevRunesBtn() { return RX(0xF9); }
constexpr auto getYPrevRunesBtn() { return RY(0x50); }

auto isOnPrevRunesBtn(DWORD x, DWORD y) { return isOnRect(x, y, getXPrevRunesBtn(), getYPrevRunesBtn(), ButtonLength, ButtonHeight); }

constexpr auto getXNextRunesBtn() { return RX(0x123); }
constexpr auto getYNextRunesBtn() { return RY(0x50); }

auto isOnNextRunesBtn(DWORD x, DWORD y) { return isOnRect(x, y, getXNextRunesBtn(), getYNextRunesBtn(), ButtonLength, ButtonHeight); }

constexpr auto getXTwoRunesBtn() { return RX(0x6B); }
constexpr auto getYTwoRunesBtn() { return RY(0x7A); }

auto isOnTwoRunesBtn(DWORD x, DWORD y) { return isOnRect(x, y, getXTwoRunesBtn(), getYTwoRunesBtn(), ButtonLength, ButtonHeight); }

constexpr auto getXThreeRunesBtn() { return RX(0x95); }
constexpr auto getYThreeRunesBtn() { return RY(0x7A); }

auto isOnThreeRunesBtn(DWORD x, DWORD y) { return isOnRect(x, y, getXThreeRunesBtn(), getYThreeRunesBtn(), ButtonLength, ButtonHeight); }

constexpr auto getXFourRunesBtn() { return RX(0xBF); }
constexpr auto getYFourRunesBtn() { return RY(0x7A); }

auto isOnFourRunesBtn(DWORD x, DWORD y) { return isOnRect(x, y, getXFourRunesBtn(), getYFourRunesBtn(), ButtonLength, ButtonHeight); }

constexpr auto getXFiveRunesBtn() { return RX(0xE9); }
constexpr auto getYFiveRunesBtn() { return RY(0x7A); }

auto isOnFiveRunesBtn(DWORD x, DWORD y) { return isOnRect(x, y, getXFiveRunesBtn(), getYFiveRunesBtn(), ButtonLength, ButtonHeight); }

constexpr auto getXSixRunesBtn() { return RX(0x113); }
constexpr auto getYSixRunesBtn() { return RY(0x7A); }

auto isOnSixRunesBtn(DWORD x, DWORD y) { return isOnRect(x, y, getXSixRunesBtn(), getYSixRunesBtn(), ButtonLength, ButtonHeight); }


//Itemtype filtering
constexpr auto getXShowWepBtn() { return RX(0x13D); }
constexpr auto getYShowWepBtn() { return RY(0x7A); }

auto isOnShowWepBtn(DWORD x, DWORD y) { return isOnRect(x, y, getXShowWepBtn(), getYShowWepBtn(), ButtonLength, ButtonHeight); }

constexpr auto getXShowArmorBtn() { return RX(0x167); }
constexpr auto getYShowArmorBtn() { return RY(0x7A); }

auto isOnShowArmorBtn(DWORD x, DWORD y) { return isOnRect(x, y, getXShowArmorBtn(), getYShowArmorBtn(), ButtonLength, ButtonHeight); }

constexpr auto getXShowCharmsBtn() { return RX(0x191); }
constexpr auto getYShowCharmsBtn() { return RY(0x7A); }

auto isOnShowCharmsBtn(DWORD x, DWORD y) { return isOnRect(x, y, getXShowCharmsBtn(), getYShowCharmsBtn(), ButtonLength, ButtonHeight); }

vector<int> weps = { 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 42, 43, 44, 45, 46, 47, 48, 49, 55, 56, 57, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 85, 86, 87, 88, 112, 123, 124, 125 };
vector<int> arms = { 2, 3, 15, 16, 19, 37, 50, 51, 70, 71, 72, 73, 75 };
vector<int> charms = { 13, 83, 84, 106, 107, 108, 119, 120, 121, 138 };
vector<vector<int>> allowedTypes = { weps, arms, charms };

const bool IsInVector(int element, vector<int> v) {
	return find(v.begin(), v.end(), element) != v.end();
}

const bool ITypeIsAllowed(const int iType, const vector<vector<int>> v) {
	for (auto& ig : v) {
		if (IsInVector(iType, ig))
			return true;
	}

	return false;
}

int curRunesPage = 0;
int MaxRunesPage = 0xFFFF;
int CompleteRunewords = 0;
bool twoRunes = true;
bool threeRunes = true;
bool fourRunes = true;
bool fiveRunes = true;
bool sixRunes = true;
bool showarmors = true;
bool showweapons = true;
bool showcharms = true;
bool runewordRects[RunesPerPage];
RunesBIN* runesOnPage[RunesPerPage];

static struct
{
	union {
		DWORD all;
		struct {
			DWORD close : 1;
			DWORD nextPage : 1;
			DWORD prevRunes : 1;
			DWORD nextRunes : 1;
			DWORD twoRunes : 1;
			DWORD threeRunes : 1;
			DWORD fourRunes : 1;
			DWORD fiveRunes : 1;
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
	DWORD x = 250;
	LPWSTR lpText = D2GetStringFromIndex(runesData->RuneNameID);
	D2SetFont(6);
	DWORD nbPixel = D2GetPixelLen(lpText);
	DWORD x1 = (nbPixel >= x) ? 0 : x - nbPixel;
	D2PrintString(lpText, x1, 100 + pos * 20, GOLD, 0);//MILIEU(0x00,0x70,nbPixel)

	typesList[0] = L'\0';
	DWORD numItype = 0;
	while (numItype < 6)
	{
		WORD type = runesData->Itypes[numItype];
		if (!type) break;
		ItemTypesBIN* itemTypeData = D2GetItemTypesBIN(type);
		LPCWSTR typeName = getLocalTypeString(itemTypeData->code);
		if (numItype) wcscat(typesList, L"/");
		wcscat(typesList, typeName);
		numItype++;
	}
	nbPixel = D2GetPixelLen(typesList);
	x1 = (nbPixel >= x) ? 0 : x - nbPixel;
	D2PrintString(typesList, x1, 110 + pos * 20, WHITE, 0);//MILIEU(0x70,0xA0,nbPixel)

	runesList[0] = L'\0';
	DWORD numRune = 0;
	int curRuneID = runesData->Runes[0];
	while ((curRuneID > 0) && (numRune < 6))
	{
		ItemsBIN* itemsData = D2GetItemsBIN(curRuneID);
		d2_assert(!itemsData, "itemsData", __FILE__, __LINE__);
		GemsBIN* gemData = D2GetGemsBIN(itemsData->GemOffset);
		if (gemData) {
			d2_assert(!gemData, "gemData", __FILE__, __LINE__);
			mbstowcs(temp, gemData->letter, 50);
			if (numRune) wcscat(runesList, L" ");
			//		else wcscat(runesList,L"");
			wcscat(runesList, temp);
		}
		numRune++;
		curRuneID = runesData->Runes[numRune];
	}
	//	wcscat(runesList,L"");
	D2SetFont(1);
	DWORD y1;
	nbPixel = D2GetPixelLen(runesList);
	if (nbPixel > x)
	{
		D2SetFont(6);
		nbPixel = D2GetPixelLen(runesList);
		y1 = 106;
		x1 = nbPixel > x ? x + 200 - nbPixel : x + 9;
	}
	else {
		x1 = x + 10;
		y1 = 108;
	}

	//	x1 = (nbPixel < 145) ? 155 : 300-nbPixel;
	D2PrintString(runesList, x1, y1 + pos * 20, WHITE, 0);//MILIEU(0xD0,0xA0,nbPixel)
}

static RunesBIN* CachedGlobalRunesBin = nullptr;
static int RuneWordsCount = 0;

void LogItypes(RunesBIN* runeword)
{
	log_msg("\t itypes");
	for (int i = 0; i < 6; i++)
	{
		if (runeword->Itypes[i] > 0)
			log_msg(" %d", runeword->Itypes[i]);
	}
	log_msg("\n");
}

void LogRunewords()
{
	int runewordsCount = *D2GetNbRunesBIN();
	log_msg("CachedRunes stored (%d) runes \n", runewordsCount);
	for (RunesBIN* runeword = CachedGlobalRunesBin; runeword < CachedGlobalRunesBin + runewordsCount; runeword++) {
		if (!runeword->Complete || runeword->Server) continue;
		log_msg("%s - %s\n", runeword->Name, runeword->RuneName);
		LogItypes(runeword);
	}
}

void InitMaxRunesPage()
{
	int runewordsCount = *D2GetNbRunesBIN();
	int runesCompleted = 0;
	for (RunesBIN* runeword = CachedGlobalRunesBin; runeword < CachedGlobalRunesBin + runewordsCount; runeword++) {
		if (!runeword->Complete || runeword->Server) continue;
		++runesCompleted;
	}
	CompleteRunewords = runesCompleted;
	MaxRunesPage = runesCompleted ? (runesCompleted - 1) / RunesPerPage : 0;
}

void EnsureGlobalRunesAreCached()
{
	if (!CachedGlobalRunesBin)
	{
		CachedGlobalRunesBin = D2GetRunesBIN(1);
		RuneWordsCount = *D2GetNbRunesBIN();
		LogRunewords();
		InitMaxRunesPage();
	}
}

sDrawImageInfo CreateDrawImageInfo() {
	//Init data for print image
	sDrawImageInfo data;
	ZeroMemory(&data, sizeof(data));
	return data;
}

int GetRuneCount(RunesBIN* runeword) {
	int runecount = 0;
	for (int i = 0; i < 6; i++)
	{
		if (runeword->Runes[i] > -1)
		{
			runecount++;
		}
	}
	return runecount;
}

const bool ContainsAllowedType(RunesBIN* runeword) {
	for (int i = 0; i < 6; i++) {

		if (ITypeIsAllowed(runeword->Itypes[i], allowedTypes)) {
			return true;
		}
	}
	return false;
}

constexpr auto BUFSIZE = 0x80;

void STDCALL printRunewordsPage()
{
	EnsureGlobalRunesAreCached();

	if (IsUnexpectedGameType()) return D2PrintStatsPage();

	LPWSTR lpText;
	bDontPrintBorder = true;

	sDrawImageInfo data = CreateDrawImageInfo();

	PrintBackground(data);
	PrintCloseButton(data);
	PrintNextPageButton(data);
	PrintPreviousRunesButton(data);
	PrintNextRunesButton(data);
	PrintRuneFilterButtons(data);

	D2SetFont(6);

	//int nbRunesCompleted = 0;
	int runewordsOnPage = 0;
	int matchingRunewords = 0;
	ResetRunes();
	if (allowedTypes.empty()) return;
	
	DWORD curNbRunes = 0;
	for (RunesBIN* runesData = CachedGlobalRunesBin; runesData < CachedGlobalRunesBin + RuneWordsCount; runesData++)
	{
		if (!runesData->Complete || runesData->Server) continue;
		const int runecount = GetRuneCount(runesData);

		if (runewordsOnPage < RunesPerPage
			&& RuneCountMatchesLengthFilter(runecount)
			&& ContainsAllowedType(runesData))
		{
			matchingRunewords++;
			if (matchingRunewords > curRunesPage * RunesPerPage
				&& matchingRunewords <= (curRunesPage + 1) * RunesPerPage)
			{
				runesOnPage[runewordsOnPage] = runesData;
				runewordRects[runewordsOnPage] = true;
				printRuneword(runesData, curNbRunes++);
				runewordsOnPage++;
			}
		}
		else if (curRunesPage * RunesPerPage > CompleteRunewords)
		{
			for (int j = runewordsOnPage; j < RunesPerPage; j++)
				runewordRects[j] = false;
		}
	}
	PrintPopupRunewords(lpText);
}

void ResetRunes()
{
	for (int j = 0; j < RunesPerPage; j++)
	{
		runewordRects[j] = false;
		runesOnPage[j] = nullptr;
	}
}

bool RuneCountMatchesLengthFilter(int runecount)
{
	return (runecount == 2 && twoRunes)
		|| (runecount == 3 && threeRunes)
		|| (runecount == 4 && fourRunes)
		|| (runecount == 5 && fiveRunes)
		|| (runecount == 6 && sixRunes);
}

bool IsUnexpectedGameType()
{
	return !D2isLODGame() || !D2GetResolution();
}

void PrintRuneFilterButtons(sDrawImageInfo& data)
{
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

	setFrame(&data, 22 + showweapons);
	D2PrintImage(&data, getXShowWepBtn(), getYShowWepBtn(), -1, 5, 0);

	setFrame(&data, 24 + showarmors);
	D2PrintImage(&data, getXShowArmorBtn(), getYShowArmorBtn(), -1, 5, 0);

	setFrame(&data, 26 + showcharms);
	D2PrintImage(&data, getXShowCharmsBtn(), getYShowCharmsBtn(), -1, 5, 0);
}

void PrintNextRunesButton(sDrawImageInfo& data)
{
	setFrame(&data, 2 + isDownBtn.nextRunes);
	D2PrintImage(&data, getXNextRunesBtn(), getYNextRunesBtn(), -1, 5, 0);
}

void PrintPreviousRunesButton(sDrawImageInfo& data)
{
	setImage(&data, stashBtnsImages);
	setFrame(&data, isDownBtn.prevRunes);
	D2PrintImage(&data, getXPrevRunesBtn(), getYPrevRunesBtn(), -1, 5, 0);
}

void PrintNextPageButton(sDrawImageInfo& data)
{
	setImage(&data, stashBtnsImages);
	setFrame(&data, 2 + isDownBtn.nextPage);
	D2PrintImage(&data, getXNextPageBtn(), getYNextPageBtn(), -1, 5, 0);
}

void PrintCloseButton(sDrawImageInfo& data)
{
	setImage(&data, D2LoadBuySelBtn());
	setFrame(&data, 10 + isDownBtn.close);
	D2PrintImage(&data, getXCloseBtn(), getYCloseBtn(), -1, 5, 0);
}

void PrintBackground(sDrawImageInfo& data)
{
	fillRect(RX(0), RY(816), 512, 768, 0, 5);
	setImage(&data, newStatsInterfaceImages);
	setFrame(&data, 0);
	D2PrintImage(&data, RX(0), RY(512), -1, 5, 0);
	setFrame(&data, 1);
	D2PrintImage(&data, RX(256), RY(512), -1, 5, 0);
	setFrame(&data, 2);
	D2PrintImage(&data, RX(0), RY(256), -1, 5, 0);
	setFrame(&data, 3);
	D2PrintImage(&data, RX(256), RY(256), -1, 5, 0);
	setFrame(&data, 4);
	D2PrintImage(&data, RX(0), RY(0), -1, 5, 0);
	setFrame(&data, 5);
	D2PrintImage(&data, RX(256), RY(0), -1, 5, 0);
}

void PrintPopupRunewords(LPWSTR& lpText)
{
	DWORD x = D2GetMouseX();
	DWORD y = D2GetMouseY();

	if (isOnCloseBtn(x, y))			// print popup "close"
	{
		D2PrintPopup(D2GetStringFromIndex(0x1030), getXCloseBtn() + ButtonLength / 2, getYCloseBtn() - ButtonHeight, WHITE, 1);
	}
	else if (isOnNextPageBtn(x, y))	// print popup "next page"
	{
		lpText = getLocalString(STR_NEXT_PAGE);
		D2PrintPopup(lpText, getXNextPageBtn() + ButtonLength / 2, getYNextPageBtn() - ButtonHeight, WHITE, 1);
	}
	//Show runeword properties as floating text
	//if (x >= 125 && x <= 250)
	//{
	//	//mouse isnt in spalte für runewort namen?
	//	int yRunewordRect = (y - 90) / 20;
	//	if (yRunewordRect < RunesPerPage && runewordRects[yRunewordRect])
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

DWORD STDCALL mouseRunewordsPageLeftDown(sWinMessage* msg)
{
	if (IsUnexpectedGameType()) return -1;

	if (!isOnStatsPage(msg->x, msg->y)) return 1;

	if (isOnCloseBtn(msg->x, msg->y))
	{
		isDownBtn.close = 1;
		D2PlaySound(4, 0, 0, 0, 0);
	}
	else if (isOnNextPageBtn(msg->x, msg->y))
	{
		isDownBtn.nextPage = 1;
		D2PlaySound(4, 0, 0, 0, 0);
	}
	else if (isOnPrevRunesBtn(msg->x, msg->y))
	{
		isDownBtn.prevRunes = 1;
		D2PlaySound(4, 0, 0, 0, 0);
	}
	else if (isOnNextRunesBtn(msg->x, msg->y))
	{
		isDownBtn.nextRunes = 1;
		D2PlaySound(4, 0, 0, 0, 0);
	}
	else if (isOnTwoRunesBtn(msg->x, msg->y))
	{
		isDownBtn.twoRunes = 1;
		D2PlaySound(4, 0, 0, 0, 0);
	}
	else if (isOnThreeRunesBtn(msg->x, msg->y))
	{
		isDownBtn.threeRunes = 1;
		D2PlaySound(4, 0, 0, 0, 0);
	}
	else if (isOnFourRunesBtn(msg->x, msg->y))
	{
		isDownBtn.fourRunes = 1;
		D2PlaySound(4, 0, 0, 0, 0);
	}
	else if (isOnFiveRunesBtn(msg->x, msg->y))
	{
		isDownBtn.fiveRunes = 1;
		D2PlaySound(4, 0, 0, 0, 0);
	}
	else if (isOnSixRunesBtn(msg->x, msg->y))
	{
		isDownBtn.sixRunes = 1;
		D2PlaySound(4, 0, 0, 0, 0);
	}
	//Itemtype filtering
	else if (isOnShowWepBtn(msg->x, msg->y))
	{
		isDownBtn.weapons = 1;
		D2PlaySound(4, 0, 0, 0, 0);
	}
	else if (isOnShowArmorBtn(msg->x, msg->y))
	{
		isDownBtn.armors = 1;
		D2PlaySound(4, 0, 0, 0, 0);
	}
	else if (isOnShowCharmsBtn(msg->x, msg->y))
	{
		isDownBtn.charms = 1;
		D2PlaySound(4, 0, 0, 0, 0);
	}

	freeMessage(msg);
	return 0;
}

void ToggleButton(bool& btn)
{
	btn = !btn;
	D2PlaySound(4, 0, 0, 0, 0);
}

void UpdateAllowedTypes()
{
	allowedTypes.clear();
	if (showweapons)
	{
		allowedTypes.push_back(weps);
	}
	if (showarmors)
	{
		allowedTypes.push_back(arms);
	}
	if (showcharms)
	{
		allowedTypes.push_back(charms);
	}
}

DWORD STDCALL mouseRunewordsPageLeftUp(sWinMessage* msg)
{
	if (IsUnexpectedGameType()) return -1;

	if (!isOnStatsPage(msg->x, msg->y)) return 1;

	if (isOnCloseBtn(msg->x, msg->y))
	{
		D2TogglePage(2, 1, 0);
	}
	else if (isOnNextPageBtn(msg->x, msg->y))
	{
		GoStatPage(GetCurrentPage() + 1);
	}
	else if (isOnPrevRunesBtn(msg->x, msg->y))
	{
		if (curRunesPage)
			curRunesPage--;
		D2PlaySound(4, 0, 0, 0, 0);
	}
	else if (isOnNextRunesBtn(msg->x, msg->y))
	{
		if (curRunesPage < MaxRunesPage)
			curRunesPage++;
		D2PlaySound(4, 0, 0, 0, 0);
	}
	else if (isOnTwoRunesBtn(msg->x, msg->y))
	{
		ToggleButton(twoRunes);
	}

	else if (isOnThreeRunesBtn(msg->x, msg->y))
	{
		ToggleButton(threeRunes);
	}

	else if (isOnFourRunesBtn(msg->x, msg->y))
	{
		ToggleButton(fourRunes);
	}

	else if (isOnFiveRunesBtn(msg->x, msg->y))
	{
		ToggleButton(fiveRunes);
	}

	else if (isOnSixRunesBtn(msg->x, msg->y))
	{
		ToggleButton(sixRunes);
	}
	//Itemtype filtering
	else if (isOnShowWepBtn(msg->x, msg->y))
	{
		ToggleButton(showweapons);
		UpdateAllowedTypes();
	}
	else if (isOnShowArmorBtn(msg->x, msg->y))
	{
		ToggleButton(showarmors);
		UpdateAllowedTypes();
	}
	else if (isOnShowCharmsBtn(msg->x, msg->y))
	{
		ToggleButton(showcharms);
		UpdateAllowedTypes();
	}

	D2CleanStatMouseUp();
	freeMessage(msg);
	isDownBtn.all = 0;
	return 0;
}
