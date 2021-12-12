#include "newInterface_CubeListing.h"
#include "updateClient.h"
#include "common.h"
#include "LocalizedStrings.h"
#include "d2functions.h"
#include "error.h"
#include <direct.h>
#include <d2constants.h>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <map>
#include <regex>

namespace PlugY {
    static const char *CUBEFORMULA_FILE = "cube.txt";
    static const LPCWSTR STRING_ERROR = L"***Error***";
    static const wchar_t *const SPACE = L" ";


    std::wstring *replaceColorCodes(std::wstring *str) {
        std::map<std::wstring, std::wstring> wideColorCodes = {
                {L"\\xFFc1", L"[Red]"},
                {L"\\xFFc2", L"[Green]"},
                {L"\\xFFc3", L"[Blue]"},
                {L"\\xFFc4", L"[Gold]"},
                {L"\\xFFc8", L"[Orange]"},
                {L"\\xFFc:", L"[Dark Green]"},
                {L"\\xFFc0", L"[white]"},
                {L"\\xFFc5", L"[grey]"},
                {L"\\xFFc6", L"[black]"},
                {L"\\xFFc7", L"[gold]"},
                {L"\\xFFc9", L"[Yellow]"},
                {L"\\xFFc;", L"[Purple]"}
        };
        for (auto&&[code, color]: wideColorCodes) {
            *str = std::regex_replace(*str, std::wregex(code), color);
        }
        return str;
    }

/*
6FC9275F  |. E8 ECCCFFFF    |CALL D2Game.6FC8F450                    ; \D2Game.6FC8F450
*/
    void printOutputItem(CubeOutput *output, std::wstringstream &stream, int *nbOutputs, bool InNoSocket) {
        auto streamLocal = [&str = stream](auto id) -> std::wstringstream & {
            str << getLocalString(id);
            return str;
        };
        auto streamLocalSpace = [streamLocal](auto id) {
            streamLocal(id) << SPACE;
        };
        auto streamD2StringRaw = [&str = stream](auto index) {
            str << D2GetStringFromIndex(index);
        };
        auto streamD2String = [&str = stream](auto index) {
            str << StripGender(D2GetStringFromIndex(index));
        };
        if (output->outputType == 0)
            return;
        if (*nbOutputs > 0)
            stream << L" + ";
        *nbOutputs += 1;
        if (output->outputType == 1) {

            streamLocal(STR_COW_PORTAL);
            return;
        } else if (output->outputType == 2) {
            streamLocal(STR_PANDEMONIUM_PORTAL);
            return;
        } else if (output->outputType == 3) {
            streamLocal(STR_PANDEMONIUM_FINAL_PORTAL);
            return;
        }
        if ((output->quantityOrNbSockets > 1) && !output->haveSockets) {
            if (output->quantityOrNbSockets == 255)
                streamLocalSpace(STR_FULL);
            else
                stream << output->quantityOrNbSockets << SPACE;
        }
        if (output->repair)
            streamLocalSpace(STR_REPAIR);
        if (output->repair && output->recharge)
            streamLocalSpace(STR_AND);
        if (output->recharge)
            streamLocalSpace(STR_RECHARGE);
        if (output->destroysFillers)
            streamLocalSpace(STR_DESTROY_FILLERS);
        if (output->removeFillers)
            streamLocalSpace(STR_REMOVE_FILLERS);
        if (output->regeneratesUnique)
            streamLocalSpace(STR_REGENERATE);
        if (output->upgradeToExceptional)
            streamLocalSpace(STR_UPGRADE_TO_EXCEPTIONAL);
        if (output->upgradeToElite)
            streamLocalSpace(STR_UPGRADE_TO_ELITE);
        if (output->isEthereal)
            streamLocalSpace(STR_ETHERAL);
        if (output->isSpecificItem) {
            if (output->quality == ITEMQUALITY_UNIQUE) {
                UniqueItemsBIN *uniqueItems = SgptDataTables->uniqueItems + output->specificID - 1;
                streamD2StringRaw(uniqueItems->uniqueNameId);
            } else if (output->quality == ITEMQUALITY_SET) {
                SetItemsBIN *setItems = SgptDataTables->setItems + output->specificID - 1;
                streamD2StringRaw(setItems->setNameId);
            } else {
                stream << STRING_ERROR;
                return;
            }
        } else {
            switch (output->quality) {
                case 1:
                    streamLocalSpace(STR_CRACKED);
                    break;
                case 2:
                    streamLocalSpace(STR_NORMAL);
                    break;
                case 3:
                    streamLocalSpace(STR_SUPERIOR);
                    break;
                case 4:
                    streamLocalSpace(STR_MAGIC);
                    break;
                case 5:
                    streamLocalSpace(STR_SET);
                    break;
                case 6:
                    streamLocalSpace(STR_RARE);
                    break;
                case 7:
                    streamLocalSpace(STR_UNIQUE);
                    break;
                case 8:
                    streamLocalSpace(STR_CRAFTED);
                    break;
                case 9:
                    streamLocalSpace(STR_TEMPERED);
                    break;
            }
            switch (output->outputType) {
                case 0xFC: {
                    ItemsBIN *items = D2GetItemsBIN(output->ID);
                    streamD2String(items->NameStr);
                    break;
                }
                case 0xFD: {
                    ItemTypesBIN *itemTypeData = D2GetItemTypesBIN(output->ID);
                    if (!itemTypeData)
                        stream << L"Unknown Item Type";
                    else
                        streamLocal(itemTypeData->code);
                    break;
                }
                case 0xFE:
                    streamLocal(STR_ITEM);
                    break;
                case 0xFF:
                    streamLocal(STR_ITEM_SAME_TYPE);
                    break;
                default:
                    stream << STRING_ERROR << SPACE;
                    return;
            }
        }
        if (output->haveSockets == 1 || InNoSocket) {
            stream << SPACE;
            if (output->quantityOrNbSockets >= 1) {
                wchar_t buffer[200];
                swprintf_s(buffer, sizeof buffer, getLocalString(STR_WITH_N_SOCKETS), output->quantityOrNbSockets);
                stream << buffer;
            } else
                streamLocal(STR_WITH_SOCKETS);
        }
    }

    void printInputItem(CubeInput *input, std::wstringstream &stream, BYTE *nbInputs, bool *InNoSocket) {
        auto streamLocal = [&str = stream](auto id) -> std::wstringstream & {
            str << getLocalString(id);
            return str;
        };
        auto streamLocalSpace = [streamLocal](auto id) {
            streamLocal(id) << SPACE;
        };
        auto streamSpaceLocal = [&str = stream](auto id) {
            str << SPACE << getLocalString(id);
        };
        auto streamD2String = [&str = stream](auto index) {
            str << StripGender(D2GetStringFromIndex(index));
        };
        if (!input->byItemID && !input->byItemTypeID)
            return;
        if (*nbInputs)
            stream << L" + ";
        BYTE nb = input->quantity > 0 ? input->quantity : 1;
        *nbInputs += nb;
        if (nb > 1)
            stream << nb << SPACE;
        if (input->isEthereal)
            streamLocalSpace(STR_ETHERAL);
        if (input->isNotEthereal)
            streamLocalSpace(STR_NOT_ETHERAL);
        if (input->isNotRuneword)
            streamLocalSpace(STR_NOT_RUNEWORD);
        if (input->isBasic)
            streamLocalSpace(STR_BASIC);
        if (input->isExceptional)
            streamLocalSpace(STR_EXCEPTIONAL);
        if (input->isElite)
            streamLocalSpace(STR_ELITE);
        if (input->isSpecificItem) {
            if (input->quality == ITEMQUALITY_UNIQUE) {
                UniqueItemsBIN *uniqueItems = SgptDataTables->uniqueItems + input->specificID - 1;
                streamD2String(uniqueItems->uniqueNameId);
            } else if (input->quality == ITEMQUALITY_SET) {
                SetItemsBIN *setItems = SgptDataTables->setItems + input->specificID - 1;
                streamD2String(setItems->setNameId);
            } else {
                stream << STRING_ERROR << SPACE;
                return;
            }
        } else {
            switch (input->quality) {
                case 1:
                    streamLocalSpace(STR_CRACKED);
                    break;
                case 2:
                    streamLocalSpace(STR_NORMAL);
                    break;
                case 3:
                    streamLocalSpace(STR_SUPERIOR);
                    break;
                case 4:
                    streamLocalSpace(STR_MAGIC);
                    break;
                case 5:
                    streamLocalSpace(STR_SET);
                    break;
                case 6:
                    streamLocalSpace(STR_RARE);
                    break;
                case 7:
                    streamLocalSpace(STR_UNIQUE);
                    break;
                case 8:
                    streamLocalSpace(STR_CRAFTED);
                    break;
                case 9:
                    streamLocalSpace(STR_TEMPERED);
                    break;
            }
            if (input->byItemTypeID) {
                ItemTypesBIN *itemTypeData = D2GetItemTypesBIN(input->ID);
                if (!itemTypeData)
                    stream << L"Unknown Item Type";
                else
                    streamLocal(itemTypeData->code);
            } else if (input->ID == 0xFFFF) {
                streamLocal(STR_ITEM);
            } else {
                ItemsBIN *items = D2GetItemsBIN(input->ID);
                streamD2String(items->NameStr);
            }
        }
        if (input->includeUpgradedVersions && !input->isElite)
            streamSpaceLocal(STR_INCLUDE_UPGRADED);
        if (input->haveNoSocket) {
            streamSpaceLocal(STR_WITHOUT_SOCKET);
            *InNoSocket = true;
        }
        if (input->haveSockets)
            streamSpaceLocal(STR_WITH_SOCKETS);
    }

    std::wstring printLine(CubeMainBIN *bin, int i) {
        if (!bin || !bin->enabled) return L"";
        bool InNoSocket = false;
        BYTE realNbInputs = 0;
        std::wstringstream stream;
        stream << std::setfill(L' ') << std::setw(6) << i << L": ";
        auto streamInput = [&stream , &realNbInputs, &InNoSocket](auto input) {
            printInputItem(input, stream, &realNbInputs, &InNoSocket);
        };
        streamInput(&bin->input1);
        streamInput(&bin->input2);
        streamInput(&bin->input3);
        streamInput(&bin->input4);
        streamInput(&bin->input5);
        streamInput(&bin->input6);
        streamInput(&bin->input7);
        if (realNbInputs != bin->numinputs) {
            stream << L" *** ERROR : numInputs(" << bin->numinputs << ") != realNbInputs(" << realNbInputs << ") ***";
            return stream.str();
        }
        stream << L" => ";
        int realNbOutputs = 0;
        auto streamOutput = [&stream , &realNbOutputs, &InNoSocket](auto output) {
            printOutputItem(output, stream, &realNbOutputs, InNoSocket);
        };
        streamOutput(&bin->output1);
        streamOutput(&bin->output2);
        streamOutput(&bin->output3);
        auto streamSpaceLocal = [&str = stream](auto id) {
            str << SPACE << getLocalString(id);
        };

        if (bin->minDiff == 1)
            streamSpaceLocal(STR_ONLY_N_H);
        else if (bin->minDiff == 2)
            streamSpaceLocal(STR_ONLY_HELL);
        if (bin->playerClass != 0xFF) {
            CharStatsBIN *charStats = D2GetCharStatsBIN(bin->playerClass);
            stream << L" (";
            wchar_t buffer[200];
            swprintf_s(buffer, sizeof buffer, getLocalString(STR_ONLY_CLASS), charStats->name);
            stream << buffer;
            stream << L")";
        }
        if ((bin->op > 0) && (bin->op != 28)) {
            stream << L" [op" << bin->op << L"(" << bin->param << L"," << bin->value << L")]";
        }
        return std::regex_replace(stream.str(), std::wregex(L"\n"), L"");
    }

    std::wstring vectorToWstring(const std::vector<std::wstring>& vec) {
        std::wstringstream stream;
        for (const std::wstring& str: vec) {
            stream << str << std::endl;
        }
        return stream.str();
    }

    std::wstring printAllCubeMainBIN() {
        std::vector<std::wstring> recipes = std::vector<std::wstring>();
        recipes.reserve(12000);
        int lines = D2GetNbCubeMainBIN();
        for (int i = 0; i < lines; i++) {
            auto str = printLine(D2GetCubeMainBIN(i), i);
            if (!str.empty())
                recipes.push_back(str);
        }
        recipes.shrink_to_fit();
        auto str = vectorToWstring(recipes);
        auto fixedStr = replaceColorCodes(&str);
        return *fixedStr;
    }

    void writeStreamToFile(std::wstring &string, const std::string &filename) {
        std::wofstream outFile(filename);
        outFile << string;
        outFile.close();
    }

    void listAllCubeFormula() {
        log_msg("\n\n********** Print all cube formula **********\n");
        char filename[MAX_PATH];
        D2FogGetSavePath(filename, MAX_PATH);
        strcat_s(filename, CUBEFORMULA_FILE);
        int nbLines = D2GetNbCubeMainBIN();
        log_msg("nbLines : %d\n", nbLines);
        auto stream = printAllCubeMainBIN();
        writeStreamToFile(stream, filename);
        log_msg("\n********** Printing over **********\n\n");
    }

}
