#include "updateServer.h"
#include "plugYFiles.h"
#include "newInterfaces.h"
#include <utility>
#include <array>
#include <vector>
#include <algorithm>
#include "newInterface_Runewords.h"
#include "d2functions.h"
#include "error.h"
#include "LocalizedStrings.h"
#include <updatingConst.h>
#include <d2constants.h>
#include "modifMemory.h"

namespace PlugY {
    using std::vector;
    using std::find;
    constexpr auto RunesPerPage = 25;
    constexpr auto ButtonHeight = 32;
    constexpr auto ButtonLength = 32;

    auto getXCloseBtn() { return 360; }

    auto getYCloseBtn() { return RY(0x50); }

    auto isOnCloseBtn(DWORD x, DWORD y) {
        return isOnRect(x, y, getXCloseBtn(), getYCloseBtn(), ButtonLength, ButtonHeight);
    }

    auto getXNextPageBtn() { return RX(0xBA); }

    auto getYNextPageBtn() { return RY(0x50); }

    auto isOnNextPageBtn(DWORD x, DWORD y) {
        return isOnRect(x, y, getXNextPageBtn(), getYNextPageBtn(), ButtonLength, ButtonHeight);
    }

    auto getXPrevRunesBtn() { return RX(0xF9); }

    auto getYPrevRunesBtn() { return RY(0x50); }

    auto isOnPrevRunesBtn(DWORD x, DWORD y) {
        return isOnRect(x, y, getXPrevRunesBtn(), getYPrevRunesBtn(), ButtonLength, ButtonHeight);
    }

    auto getXNextRunesBtn() { return RX(0x123); }

    auto getYNextRunesBtn() { return RY(0x50); }

    auto isOnNextRunesBtn(DWORD x, DWORD y) {
        return isOnRect(x, y, getXNextRunesBtn(), getYNextRunesBtn(), ButtonLength, ButtonHeight);
    }

    auto getXTwoRunesBtn() { return RX(0x6B); }

    auto getYTwoRunesBtn() { return RY(0x7A); }

    auto isOnTwoRunesBtn(DWORD x, DWORD y) {
        return isOnRect(x, y, getXTwoRunesBtn(), getYTwoRunesBtn(), ButtonLength, ButtonHeight);
    }

    auto getXThreeRunesBtn() { return RX(0x95); }

    auto getYThreeRunesBtn() { return RY(0x7A); }

    auto isOnThreeRunesBtn(DWORD x, DWORD y) {
        return isOnRect(x, y, getXThreeRunesBtn(), getYThreeRunesBtn(), ButtonLength, ButtonHeight);
    }

    auto getXFourRunesBtn() { return RX(0xBF); }

    auto getYFourRunesBtn() { return RY(0x7A); }

    auto isOnFourRunesBtn(DWORD x, DWORD y) {
        return isOnRect(x, y, getXFourRunesBtn(), getYFourRunesBtn(), ButtonLength, ButtonHeight);
    }

    auto getXFiveRunesBtn() { return RX(0xE9); }

    auto getYFiveRunesBtn() { return RY(0x7A); }

    auto isOnFiveRunesBtn(DWORD x, DWORD y) {
        return isOnRect(x, y, getXFiveRunesBtn(), getYFiveRunesBtn(), ButtonLength, ButtonHeight);
    }

    auto getXSixRunesBtn() { return RX(0x113); }

    auto getYSixRunesBtn() { return RY(0x7A); }

    auto isOnSixRunesBtn(DWORD x, DWORD y) {
        return isOnRect(x, y, getXSixRunesBtn(), getYSixRunesBtn(), ButtonLength, ButtonHeight);
    }

//ItemType filtering
    auto getXShowWepBtn() { return RX(0x13D); }

    auto getYShowWepBtn() { return RY(0x7A); }

    auto isOnShowWepBtn(DWORD x, DWORD y) {
        return isOnRect(x, y, getXShowWepBtn(), getYShowWepBtn(), ButtonLength, ButtonHeight);
    }

    auto getXShowArmorBtn() { return RX(0x167); }

    auto getYShowArmorBtn() { return RY(0x7A); }

    auto isOnShowArmorBtn(DWORD x, DWORD y) {
        return isOnRect(x, y, getXShowArmorBtn(), getYShowArmorBtn(), ButtonLength, ButtonHeight);
    }

    auto getXShowCharmsBtn() { return RX(0x191); }

    auto getYShowCharmsBtn() { return RY(0x7A); }

    auto isOnShowCharmsBtn(DWORD x, DWORD y) {
        return isOnRect(x, y, getXShowCharmsBtn(), getYShowCharmsBtn(), ButtonLength, ButtonHeight);
    }

    vector<int> weapons;
    vector<int> arms;
    vector<int> charms;
    vector<vector<int>> allowedTypes;

    bool IsInVector(int element, vector<int> v) {
        return find(v.begin(), v.end(), element) != v.end();
    }

    bool ITypeIsAllowed(int iType, vector<vector<int>> v) {
        return std::any_of(v.begin(), v.end(), [iType](auto vec) { return IsInVector(iType, vec); });
    }

    int curRunesPage = 0;
    int MaxRunesPage = 0xFFFF;
//int CompleteRuneWords = 0;
    bool twoRunes = true;
    bool threeRunes = true;
    bool fourRunes = true;
    bool fiveRunes = true;
    bool sixRunes = true;
    bool showArmors = true;
    bool showWeapons = true;
    bool showCharms = true;
    static struct {
        union {
            DWORD all;
            struct {
                DWORD close: 1;
                DWORD nextPage: 1;
                DWORD prevRunes: 1;
                DWORD nextRunes: 1;
                DWORD twoRunes: 1;
                DWORD threeRunes: 1;
                DWORD fourRunes: 1;
                DWORD fiveRunes: 1;
                DWORD sixRunes: 1;
                DWORD armors: 1;
                DWORD weapons: 1;
                DWORD charms: 1;
            };
        };
    } isDownBtn;

    void printRuneWord(RunesBIN *runesData, DWORD pos) {
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
        DWORD numItemType = 0;
        while (numItemType < 6) {
            WORD type = runesData->Itypes[numItemType];
            if (!type) break;
            ItemTypesBIN *itemTypeData = D2GetItemTypesBIN(type);
            LPCWSTR typeName = getLocalTypeString(itemTypeData->code);
            if (numItemType) wcscat_s(typesList, L"/");
            wcscat_s(typesList, typeName);
            numItemType++;
        }
        nbPixel = D2GetPixelLen(typesList);
        x1 = (nbPixel >= x) ? 0 : x - nbPixel;
        D2PrintString(typesList, x1, 110 + pos * 20, WHITE, 0);//MILIEU(0x70,0xA0,nbPixel)

        runesList[0] = L'\0';
        DWORD numRune = 0;
        int curRuneID = runesData->Runes[0];
        while ((curRuneID > 0) && (numRune < 6)) {
            ItemsBIN *itemsData = D2GetItemsBIN(curRuneID);
            d2_assert(!itemsData, "itemsData", __FILE__, __LINE__);
            GemsBIN *gemData = D2GetGemsBIN(itemsData->GemOffset);
            if (gemData) {
                d2_assert(!gemData, "gemData", __FILE__, __LINE__);
                size_t *charsConverted = nullptr;
                mbstowcs_s(charsConverted, temp, gemData->letter, 50);
                if (numRune) wcscat_s(runesList, L" ");
                wcscat_s(runesList, temp);
            }
            numRune++;
            curRuneID = runesData->Runes[numRune];
        }
        D2SetFont(1);
        DWORD y1;
        nbPixel = D2GetPixelLen(runesList);
        if (nbPixel > x) {
            D2SetFont(6);
            nbPixel = D2GetPixelLen(runesList);
            y1 = 106;
            x1 = nbPixel > x ? x + 200 - nbPixel : x + 9;
        } else {
            x1 = x + 10;
            y1 = 108;
        }

        //	x1 = (nbPixel < 145) ? 155 : 300-nbPixel;
        D2PrintString(runesList, x1, y1 + pos * 20, WHITE, 0);//MILIEU(0xD0,0xA0,nbPixel)
    }

    static RunesBIN *CachedGlobalRunesBin = nullptr;
    static int RuneWordsCount = 0;

    void LogItemTypes(RunesBIN *runeWord) {
        log_msg("\t item types");
        for (unsigned short iType: runeWord->Itypes) {
            if (iType > 0)
                log_msg(" %d", iType);
        }
        log_msg("\n");
    }

    void LogRuneWords() {
        int runeWordsCount = *D2GetNbRunesBIN();
        log_msg("CachedRunes stored (%d) runes \n", runeWordsCount);
        for (RunesBIN *runeWord = CachedGlobalRunesBin; runeWord < CachedGlobalRunesBin + runeWordsCount; runeWord++) {
            if (!runeWord->Complete || runeWord->Server) continue;
            log_msg("%s - %s\n", runeWord->Name, runeWord->RuneName);
            LogItemTypes(runeWord);
        }
    }

    void InitMaxRunesPage() {
        int runeWordsCount = *D2GetNbRunesBIN();
        int runesCompleted = 0;
        for (RunesBIN *runeWord = CachedGlobalRunesBin; runeWord < CachedGlobalRunesBin + runeWordsCount; runeWord++) {
            if (!runeWord->Complete || runeWord->Server) continue;
            ++runesCompleted;
        }
//    CompleteRuneWords = runesCompleted;
        MaxRunesPage = runesCompleted ? (runesCompleted - 1) / RunesPerPage : 0;
    }

    void InitItemTypeVectors() {
        weapons = {24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 42, 43, 44, 45, 46, 47, 48, 49, 55, 56, 57, 59, 60,
                   61, 62, 63, 64, 65, 66, 67, 68, 69, 85, 86, 87, 88, 112, 123, 124, 125};
        arms = {2, 3, 15, 16, 19, 37, 50, 51, 70, 71, 72, 73, 75};
        charms = {13, 83, 84, 106, 107, 108, 119, 120, 121, 138};
        allowedTypes = {weapons, arms, charms};
    }

    void EnsureGlobalRunesAreCached() {
        if (!CachedGlobalRunesBin) {
            CachedGlobalRunesBin = D2GetRunesBIN(1);
            RuneWordsCount = *D2GetNbRunesBIN();
            LogRuneWords();
            InitItemTypeVectors();
            InitMaxRunesPage();
        }
    }

    int GetRuneCount(RunesBIN *runeWord) {
        int runeCount = 0;
        for (int Rune: runeWord->Runes)
            if (Rune > -1)
                runeCount++;
        return runeCount;
    }

    bool ContainsAllowedType(RunesBIN *runeWord) {
        std::array<WORD, 6> itemTypes{};
        std::copy(std::begin(runeWord->Itypes), std::end(runeWord->Itypes), itemTypes.begin());
        return std::any_of(itemTypes.begin(), itemTypes.end(),
                           [](unsigned short I) { return ITypeIsAllowed(I, allowedTypes); });
    }

    bool RuneCountMatchesLengthFilter(int runeCount) {
        return (runeCount == 2 && twoRunes)
               || (runeCount == 3 && threeRunes)
               || (runeCount == 4 && fourRunes)
               || (runeCount == 5 && fiveRunes)
               || (runeCount == 6 && sixRunes);
    }

    void PrintRuneWords() {
        int runeWordsOnPage = 0;
        int matchingRuneWords = 0;
        DWORD curNbRunes = 0;
        for (RunesBIN *runesData = CachedGlobalRunesBin; runesData < CachedGlobalRunesBin + RuneWordsCount; runesData++) {
            if (!runesData->Complete || runesData->Server) continue;
            const int runeCount = GetRuneCount(runesData);
            if (runeWordsOnPage < RunesPerPage
                && RuneCountMatchesLengthFilter(runeCount)
                && ContainsAllowedType(runesData)) {
                matchingRuneWords++;
                if (matchingRuneWords > curRunesPage * RunesPerPage
                    && matchingRuneWords <= (curRunesPage + 1) * RunesPerPage) {
                    printRuneWord(runesData, curNbRunes++);
                    runeWordsOnPage++;
                }
            }
        }
    }

    bool IsUnexpectedGameType() {
        return !D2isLODGame() || !D2GetResolution();
    }

    void PrintRuneFilterButtons(sDrawImageInfo &data) {
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
        setFrame(&data, 22 + showWeapons);
        D2PrintImage(&data, getXShowWepBtn(), getYShowWepBtn(), -1, 5, 0);
        setFrame(&data, 24 + showArmors);
        D2PrintImage(&data, getXShowArmorBtn(), getYShowArmorBtn(), -1, 5, 0);
        setFrame(&data, 26 + showCharms);
        D2PrintImage(&data, getXShowCharmsBtn(), getYShowCharmsBtn(), -1, 5, 0);
    }

    void PrintNextRunesButton(sDrawImageInfo &data) {
        setFrame(&data, (DWORD) 2 + isDownBtn.nextRunes);
        D2PrintImage(&data, getXNextRunesBtn(), getYNextRunesBtn(), -1, 5, 0);
    }

    void PrintPreviousRunesButton(sDrawImageInfo &data) {
        setImage(&data, stashBtnsImages);
        setFrame(&data, isDownBtn.prevRunes);
        D2PrintImage(&data, getXPrevRunesBtn(), getYPrevRunesBtn(), -1, 5, 0);
    }

    void PrintNextPageButton(sDrawImageInfo &data) {
        setImage(&data, stashBtnsImages);
        setFrame(&data, 2ul + isDownBtn.nextPage);
        D2PrintImage(&data, getXNextPageBtn(), getYNextPageBtn(), -1, 5, 0);
    }

    void PrintCloseButton(sDrawImageInfo &data) {
        setImage(&data, D2LoadBuySelBtn());
        setFrame(&data, 10ul + isDownBtn.close);
        D2PrintImage(&data, getXCloseBtn(), getYCloseBtn(), -1, 5, 0);
    }

    void PrintBackground(sDrawImageInfo &data) {
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

    void PrintPopupRuneWords() {
        DWORD x = D2GetMouseX();
        DWORD y = D2GetMouseY();
        if (isOnCloseBtn(x, y))            // print popup "close"
        {
            D2PrintPopup(D2GetStringFromIndex(0x1030),
                         getXCloseBtn() + ButtonLength / 2,
                         getYCloseBtn() - ButtonHeight,
                         WHITE, 1);
        } else if (isOnNextPageBtn(x, y))    // print popup "next page"
        {
            auto text = const_cast<LPWSTR>(getLocalString(STR_NEXT_PAGE));
            D2PrintPopup(text, getXNextPageBtn() + ButtonLength / 2, getYNextPageBtn() - ButtonHeight, WHITE, 1);
        }
    }

    void __stdcall printRuneWordsPage() {
        EnsureGlobalRunesAreCached();
        if (IsUnexpectedGameType()) return D2PrintStatsPage();
        bDontPrintBorder = true;
        sDrawImageInfo data = {};
        PrintBackground(data);
        PrintCloseButton(data);
        PrintNextPageButton(data);
        PrintPreviousRunesButton(data);
        PrintNextRunesButton(data);
        PrintRuneFilterButtons(data);
        D2SetFont(6);
        if (allowedTypes.empty()) return;
        PrintRuneWords();
        PrintPopupRuneWords();
    }

    DWORD __stdcall mouseRuneWordsPageLeftDown(sWinMessage *msg) {
        if (IsUnexpectedGameType()) return -1;
        if (!isOnStatsPage(msg->x, msg->y)) return 1;
        if (isOnCloseBtn(msg->x, msg->y)) {
            isDownBtn.close = 1;
            D2PlaySound(4, 0, 0, 0, 0);
        } else if (isOnNextPageBtn(msg->x, msg->y)) {
            isDownBtn.nextPage = 1;
            D2PlaySound(4, 0, 0, 0, 0);
        } else if (isOnPrevRunesBtn(msg->x, msg->y)) {
            isDownBtn.prevRunes = 1;
            D2PlaySound(4, 0, 0, 0, 0);
        } else if (isOnNextRunesBtn(msg->x, msg->y)) {
            isDownBtn.nextRunes = 1;
            D2PlaySound(4, 0, 0, 0, 0);
        } else if (isOnTwoRunesBtn(msg->x, msg->y)) {
            isDownBtn.twoRunes = 1;
            D2PlaySound(4, 0, 0, 0, 0);
        } else if (isOnThreeRunesBtn(msg->x, msg->y)) {
            isDownBtn.threeRunes = 1;
            D2PlaySound(4, 0, 0, 0, 0);
        } else if (isOnFourRunesBtn(msg->x, msg->y)) {
            isDownBtn.fourRunes = 1;
            D2PlaySound(4, 0, 0, 0, 0);
        } else if (isOnFiveRunesBtn(msg->x, msg->y)) {
            isDownBtn.fiveRunes = 1;
            D2PlaySound(4, 0, 0, 0, 0);
        } else if (isOnSixRunesBtn(msg->x, msg->y)) {
            isDownBtn.sixRunes = 1;
            D2PlaySound(4, 0, 0, 0, 0);
        }
            //ItemType filtering
        else if (isOnShowWepBtn(msg->x, msg->y)) {
            isDownBtn.weapons = 1;
            D2PlaySound(4, 0, 0, 0, 0);
        } else if (isOnShowArmorBtn(msg->x, msg->y)) {
            isDownBtn.armors = 1;
            D2PlaySound(4, 0, 0, 0, 0);
        } else if (isOnShowCharmsBtn(msg->x, msg->y)) {
            isDownBtn.charms = 1;
            D2PlaySound(4, 0, 0, 0, 0);
        }
        freeMessage(msg);
        return 0;
    }

    void ToggleButton(bool &btn) {
        btn = !btn;
        D2PlaySound(4, 0, 0, 0, 0);
    }

    void UpdateAllowedTypes() {
        allowedTypes.clear();
        if (showWeapons) {
            allowedTypes.push_back(weapons);
        }
        if (showArmors) {
            allowedTypes.push_back(arms);
        }
        if (showCharms) {
            allowedTypes.push_back(charms);
        }
    }

    DWORD __stdcall mouseRuneWordsPageLeftUp(sWinMessage *msg) {
        if (IsUnexpectedGameType()) return -1;
        if (!isOnStatsPage(msg->x, msg->y)) return 1;
        if (isOnCloseBtn(msg->x, msg->y)) {
            D2TogglePage(2, 1, 0);
        } else if (isOnNextPageBtn(msg->x, msg->y)) {
            GoStatPage(GetCurrentPage() + 1);
        } else if (isOnPrevRunesBtn(msg->x, msg->y)) {
            if (curRunesPage)
                curRunesPage--;
            D2PlaySound(4, 0, 0, 0, 0);
        } else if (isOnNextRunesBtn(msg->x, msg->y)) {
            if (curRunesPage < MaxRunesPage)
                curRunesPage++;
            D2PlaySound(4, 0, 0, 0, 0);
        } else if (isOnTwoRunesBtn(msg->x, msg->y)) {
            ToggleButton(twoRunes);
        } else if (isOnThreeRunesBtn(msg->x, msg->y)) {
            ToggleButton(threeRunes);
        } else if (isOnFourRunesBtn(msg->x, msg->y)) {
            ToggleButton(fourRunes);
        } else if (isOnFiveRunesBtn(msg->x, msg->y)) {
            ToggleButton(fiveRunes);
        } else if (isOnSixRunesBtn(msg->x, msg->y)) {
            ToggleButton(sixRunes);
        }
            //ItemType filtering
        else if (isOnShowWepBtn(msg->x, msg->y)) {
            ToggleButton(showWeapons);
            UpdateAllowedTypes();
        } else if (isOnShowArmorBtn(msg->x, msg->y)) {
            ToggleButton(showArmors);
            UpdateAllowedTypes();
        } else if (isOnShowCharmsBtn(msg->x, msg->y)) {
            ToggleButton(showCharms);
            UpdateAllowedTypes();
        }
        D2CleanStatMouseUp();
        freeMessage(msg);
        isDownBtn.all = 0;
        return 0;
    }
}