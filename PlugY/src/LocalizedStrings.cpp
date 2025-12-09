/*=================================================================
	File created by Yohann NICOLAS.

	Localized strings functions.

=================================================================*/

#include "INIfile.h"
#include "LocalizedStrings.h"
#include "common.h"
#include "error.h"
#include <stdio.h>
#include "language.h"
#include <d2constants.h>
#include <vector>
#include "D2TypeDefMacros.h"
#include <nameof.hpp>
#include <map>
//#include "D2TypeNameMacros.h"

namespace PlugY {
    using namespace Commons;

    const char *LOCALIZED_STRINGS_FILENAME = "PlugY\\LocalizedStrings.ini";

    LPCWSTR StripGender(LPCWSTR text) {
        if (text[0] == L' ')
            text++;
        if (text[0] != L'[')
            return text;
        text++;
        while (text[0] != L']' && text[0] != NULL)
            text++;
        text++;
        return text;
    }

    //LPCWSTR StripGender(LPCWSTR text) { return StripGender((LPWSTR) text); }

///////////////////////////////////////// Get Local Strings /////////////////////////////////////////

    struct LocalizedTypeString {
        DWORD code;
        LPSTR itemStr;
        LPWSTR typeLocalizedString;
    } *sLocalizedTypeStrings;

    LPWSTR sLocalizedStrings[100];

    int nbLocalizedTypeString = 0;

    LPCWSTR getLocalString(int stringId) {
        if (stringId < 0 || stringId >= 100)
            return L"";
        return sLocalizedStrings[stringId];
    }

    LPCWSTR getLocalTypeString(DWORD code) {
        for (int i = 0; i < nbLocalizedTypeString; i++) {
            if (sLocalizedTypeStrings[i].code == code) {
                log_msg("Code=%08X\n", code);
                if (sLocalizedTypeStrings[i].itemStr)
                    return StripGender(D2GetStringFromString(sLocalizedTypeStrings[i].itemStr));
                auto text = StripGender(sLocalizedTypeStrings[i].typeLocalizedString);
                if (!text || !text[0])
                    break;
                return text;
            }
        }
        char itemIdx[5];
        itemIdx[0] = (code) & 0xFF;
        itemIdx[1] = (code >> 8) & 0xFF;
        itemIdx[2] = (code >> 16) & 0xFF;
        itemIdx[3] = (code >> 24) & 0xFF;
        itemIdx[4] = 0;
        auto typeName = StripGender(D2GetStringFromString(itemIdx));
        if (wcsstr(typeName, L"-not xlated call ken") == NULL)
            return typeName;
        static WCHAR itemIdxW[5];
        itemIdxW[0] = (code) & 0xFF;
        itemIdxW[1] = (code >> 8) & 0xFF;
        itemIdxW[2] = (code >> 16) & 0xFF;
        itemIdxW[3] = (code >> 24) & 0xFF;
        itemIdxW[4] = 0;
        return itemIdxW;
    }

///////////////////////////////////////// Load Strings /////////////////////////////////////////

#define LOAD(I) loadLocalString(iniFile, I, L#I, key)
#define BUFSIZE 0x400

    void loadLocalString(INIFileW *iniFile, int id, LPCWSTR section, LPCWSTR key) {
        WCHAR buffer[BUFSIZE];
        iniFile->GetPrivateProfileString(section, key, NULL, buffer, BUFSIZE);
        int len = wcslen(buffer);
        if (len == 0)
            iniFile->GetPrivateProfileString(section, L"ENG", section, buffer, BUFSIZE);
        len = wcslen(buffer);
        if (len == 0) {
            len = wcslen(section);
            sLocalizedStrings[id] = new WCHAR[len + 1];
            wcsncpy(sLocalizedStrings[id], section, len);
            sLocalizedStrings[id][len] = NULL;
            return;
        }
        int j = 0;
        int i = 0;
        if (buffer[0] == L'"' && buffer[len - 1] == L'"') {
            buffer[len - 1] = NULL;
            i++;
            len -= 2;
        }
        sLocalizedStrings[id] = new WCHAR[len + 1];
        for (; i < len; i++) {
            if (buffer[i] == L'\\' && buffer[i + 1] == L'n') {
                sLocalizedStrings[id][j++] = L'\n';
                i++;
            } else
                sLocalizedStrings[id][j++] = buffer[i];
        }
        sLocalizedStrings[id][j] = NULL;
    }

    int GetPrivateProfileStringList(LPCWCHAR m_cache, LPCWSTR section, LPCWSTR key) {
        WCHAR sectionString[MAX_SECTIONNAME_LENGTH];
        _snwprintf(sectionString, MAX_SECTIONNAME_LENGTH, L"\n[%s", section);
        WCHAR keyString[MAX_KEYNAME_LENGTH];
        _snwprintf(keyString, MAX_KEYNAME_LENGTH, L"\n%s=", key);
        int keyLen = wcslen(keyString);
        WCHAR defKeyString[MAX_KEYNAME_LENGTH];
        _snwprintf(defKeyString, MAX_KEYNAME_LENGTH, L"\n%s=", L"ENG");
        int defKeyLen = wcslen(defKeyString);
        WCHAR itemKeyString[MAX_KEYNAME_LENGTH];
        _snwprintf(itemKeyString, MAX_KEYNAME_LENGTH, L"\n%s=", L"ITEM");
        int itemKeyLen = wcslen(itemKeyString);

        // Get nb TYPE sections.
        LPCWSTR end;
        int nb = 0;
        LPCWSTR cur = m_cache;
        while ((cur = wcsstr(cur, sectionString))) {
            cur = wcsstr(cur, L"]") + 1;
            if (cur == NULL)
                continue;
            nb++;
        }

        // Allocation
        sLocalizedTypeStrings = new LocalizedTypeString[nb];

        // Search next section.
        cur = m_cache;
        LPCWSTR nextHeader = wcsstr(cur, sectionString);

        // Treat next section
        int i = 0;
        while (nextHeader && i < nb) {
            cur = nextHeader + wcslen(sectionString);
            end = wcsstr(cur, L"]");
            if (end == NULL)
                break;
            nextHeader = wcsstr(end, sectionString);
            if (cur == end) {
                cur++;
                continue;
            }

            // Fill code
            sLocalizedTypeStrings[i].code = (*cur & 0xFF);
            cur++;
            if (cur != end) {
                sLocalizedTypeStrings[i].code |= (*cur & 0xFF) << 8;
                cur++;
            } else sLocalizedTypeStrings[i].code |= ' ' << 8;
            if (cur != end) {
                sLocalizedTypeStrings[i].code |= (*cur & 0xFF) << 16;
                cur++;
            } else sLocalizedTypeStrings[i].code |= ' ' << 16;
            if (cur != end) {
                sLocalizedTypeStrings[i].code |= (*cur & 0xFF) << 24;
                cur++;
            } else sLocalizedTypeStrings[i].code |= ' ' << 24;
            sLocalizedTypeStrings[i].itemStr = NULL;

            // Search item key
            cur = wcsstr(end + 1, itemKeyString);
            if (!(cur == NULL || (nextHeader && cur > nextHeader) || cur[itemKeyLen] == '\r' || cur[itemKeyLen] == '\n' || cur[itemKeyLen] == NULL))// Found
            {
                cur += itemKeyLen;
                end = cur;
                while (end[0] != '\r' && end[0] != '\n' && end[0] != NULL)
                    end++;
                sLocalizedTypeStrings[i].itemStr = new char[end - cur + 1];
                for (int j = 0; j < end - cur; j++)
                    sLocalizedTypeStrings[i].itemStr[j] = (char) cur[j];
                sLocalizedTypeStrings[i].itemStr[end - cur] = NULL;
                i++;
                continue;
            }

            // Search lng key
            cur = wcsstr(end + 1, keyString);
            if (cur == NULL || (nextHeader && cur > nextHeader) || cur[keyLen] == '\r' || cur[keyLen] == '\n' || cur[keyLen] == NULL)// Not found
            {
                // Search def key
                cur = wcsstr(end + 1, defKeyString);
                if (cur == NULL || (nextHeader && cur > nextHeader) || cur[defKeyLen] == '\r' || cur[defKeyLen] == '\n' || cur[defKeyLen] == NULL)// Not found
                {
                    sLocalizedTypeStrings[i].typeLocalizedString = new WCHAR[1];
                    sLocalizedTypeStrings[i].typeLocalizedString[0] = NULL;
                    i++;
                    continue;
                }
                cur += defKeyLen;
            } else
                cur += keyLen;

            // Search end value.
            end = cur;
            while (end[0] && end[0] != '\r' && end[0] != '\n')
                end++;

            // Strip ""
            if (cur[0] == '"' && (end - 1)[0] == '"') {
                cur++;
                end--;
            }

            // Strip Gender
            if (cur[0] == '[') {
                LPCWSTR tmp = cur;
                while (tmp[0] && tmp[0] != ']' && tmp[0] != '\r' && tmp[0] != '\n')
                    tmp++;
                if (tmp[0] == ']') {
                    cur = tmp + 1;
                    end = cur;
                    while (end[0] && end[0] != '[' && end[0] != '\r' && end[0] != '\n' && end[0] != '"')
                        end++;
                }
            }

            // Fill value
            sLocalizedTypeStrings[i].typeLocalizedString = new WCHAR[end - cur + 1];
            _snwprintf(sLocalizedTypeStrings[i].typeLocalizedString, end - cur, cur);
            sLocalizedTypeStrings[i].typeLocalizedString[end - cur] = NULL;
            i++;
        }
        return nb;
    }

    LPCWSTR findLanguageOrDefault(int language, std::map<int, LPCWSTR>& languages) {
        auto result = languages.find(language);
        return result != languages.end() ? result->second : L"ENG";
    }

    void loadLocalizedStrings(int language) {
        if (sLocalizedTypeStrings)
            return;
        INIFileW *iniFile = new INIFileW;
        log_msg("***** Load localized Strings *****\n");
        if (iniFile->InitReadWrite(LOCALIZED_STRINGS_FILENAME, INIFILE_MPQREAD, 0))//C:\\Jeux\\Blizzard\\D2\\-
            log_msg("File %s loaded from MPQ.\n\n", LOCALIZED_STRINGS_FILENAME);
        else if (iniFile->InitReadWrite(LOCALIZED_STRINGS_FILENAME, INIFILE_READ, 0))//C:\\Jeux\\Blizzard\\D2\\-
            log_msg("File %s loaded from PlugY folder.\n\n", LOCALIZED_STRINGS_FILENAME);
        else {
            log_msg("Failed to load %s.\n\n", LOCALIZED_STRINGS_FILENAME);
            return;
        }
        auto languages = std::map<int, LPCWSTR>{{LNG_ENG, L"ENG"},
                                                   {LNG_ESP, L"ESP"},
                                                   {LNG_DEU, L"DEU"},
                                                   {LNG_FRA, L"FRA"},
                                                   {LNG_POR, L"POR"},
                                                   {LNG_ITA, L"ITA"},
                                                   {LNG_JPN, L"JPN"},
                                                   {LNG_KOR, L"KOR"},
                                                   {LNG_SIN, L"SIN"},
                                                   {LNG_CHI, L"CHI"},
                                                   {LNG_POL, L"POL"},
                                                   {LNG_RUS, L"RUS"},
                                                   {LNG_DEF, L"ENG"},};
        auto key = findLanguageOrDefault(language, languages);
        // Load localized type string
        nbLocalizedTypeString = GetPrivateProfileStringList(iniFile->m_cache, L"TYPE_", key);
        // PlugY localized string

        auto stringNames = std::vector<eStringList>{
            STR_STATS_UNASSIGN_WITH_LIMIT,
            STR_STATS_UNASSIGN_WITHOUT_LIMIT,
            STR_STATS_BASE_MIN,
            STR_SKILLS_UNASSIGN,
            STR_STASH_PREVIOUS_PAGE,
            STR_STASH_NEXT_PAGE,
            STR_TOGGLE_TO_PERSONAL,
            STR_TOGGLE_TO_SHARED,
            STR_TOGGLE_MULTI_DISABLED,
            STR_STASH_PREVIOUS_INDEX,
            STR_STASH_NEXT_INDEX,
            STR_PUT_GOLD,
            STR_TAKE_GOLD,
            STR_PERSONAL_PAGE_NUMBER,
            STR_SHARED_PAGE_NUMBER,
            STR_NO_SELECTED_PAGE,
            STR_SHARED_GOLD_QUANTITY,
            STR_PREVIOUS_PAGE,
            STR_NEXT_PAGE,
            STR_ITEM_LEVEL,
            STR_PAGE_TYPE_CHANGE,
            STR_COW_PORTAL,
            STR_PANDEMONIUM_PORTAL,
            STR_PANDEMONIUM_FINAL_PORTAL,
            STR_FULL,
            STR_REPAIR,
            STR_AND,
            STR_RECHARGE,
            STR_DESTROY_FILLERS,
            STR_REMOVE_FILLERS,
            STR_REGENERATE,
            STR_UPGRADE_TO_EXCEPTIONAL,
            STR_UPGRADE_TO_ELITE,
            STR_ETHERAL,
            STR_NOT_ETHERAL,
            STR_NOT_RUNEWORD,
            STR_BASIC,
            STR_EXCEPTIONAL,
            STR_ELITE,
            STR_CRACKED,
            STR_NORMAL,
            STR_SUPERIOR,
            STR_MAGIC,
            STR_SET,
            STR_RARE,
            STR_UNIQUE,
            STR_CRAFTED,
            STR_TEMPERED,
            STR_ITEM,
            STR_ITEM_SAME_TYPE,
            STR_INCLUDE_UPGRADED,
            STR_WITHOUT_SOCKET,
            STR_WITH_SOCKETS,
            STR_WITH_N_SOCKETS,
            STR_ONLY_N_H,
            STR_ONLY_HELL,
            STR_ONLY_CLASS,
            STR_MERCENARIES,
            STR_MERC_ACT_1,
            STR_MERC_ACT_2,
            STR_MERC_ACT_3,
            STR_MERC_ACT_5,
            STR_BREAKPOINT,
            STR_BREAKPOINTS,
            STR_BLOCK_FRAMES,
            STR_CASTING_FRAMES,
            STR_HIT_RECOVERY_FRAMES,
            STR_1H_SWINGING_WEAPON,
            STR_OTHER_WEAPONS,
            STR_HUMAN_FORM,
            STR_BEAR_FORM,
            STR_WOLF_FORM,
            STR_VAMPIRE_FORM,
            STR_SPEARS_AND_STAVES,
            STR_LIGHTNING_CHAIN_LIGHTNING,
            STR_OTHER_SPELLS};
        for (const auto &item: stringNames) {
            auto name = to_wide(std::string(nameof::nameof_enum(item)));
            loadLocalString(iniFile, item, name.c_str(), key);
        }
        iniFile->close();
        delete iniFile;
    }

}