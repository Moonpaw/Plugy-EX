#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"
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


    std::wstring* replaceColorCodes(std::wstring *str){
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
        for (auto&& [code, color]: wideColorCodes) {
            *str = std::regex_replace(*str, std::wregex(code), color);
        }
        return str;
    }

/*
6FC9275F  |. E8 ECCCFFFF    |CALL D2Game.6FC8F450                    ; \D2Game.6FC8F450
*/
    void printOutputItem(CubeOutput *output, std::wstringstream &stream, int *nbOutputs, bool InNoSocket) {
        if (output->outputType == 0)
            return;
        if (*nbOutputs > 0)
            stream << L" + ";
        *nbOutputs += 1;
        if (output->outputType == 1) {
            stream << getLocalString(STR_COW_PORTAL);
            return;
        } else if (output->outputType == 2) {
            stream << getLocalString(STR_PANDEMONIUM_PORTAL);
            return;
        } else if (output->outputType == 3) {
            stream << getLocalString(STR_PANDEMONIUM_FINAL_PORTAL);
            return;
        }
        if ((output->quantityOrNbSockets > 1) && !output->haveSockets) {
            if (output->quantityOrNbSockets == 255)
                stream << getLocalString(STR_FULL) << SPACE;
            else
                stream << output->quantityOrNbSockets << SPACE;
        }
        if (output->repair)
            stream << getLocalString(STR_REPAIR) << SPACE;
        if (output->repair && output->recharge)
            stream << getLocalString(STR_AND) << SPACE;
        if (output->recharge)
            stream << getLocalString(STR_RECHARGE) << SPACE;
        if (output->destroysFillers)
            stream << getLocalString(STR_DESTROY_FILLERS) << SPACE;
        if (output->removeFillers)
            stream << getLocalString(STR_REMOVE_FILLERS) << SPACE;
        if (output->regeneratesUnique)
            stream << getLocalString(STR_REGENERATE) << SPACE;
        if (output->upgradeToExceptional)
            stream << getLocalString(STR_UPGRADE_TO_EXCEPTIONAL) << SPACE;
        if (output->upgradeToElite)
            stream << getLocalString(STR_UPGRADE_TO_ELITE) << SPACE;
        if (output->isEthereal)
            stream << getLocalString(STR_ETHERAL) << SPACE;
        if (output->isSpecificItem) {
            if (output->quality == ITEMQUALITY_UNIQUE) {
                UniqueItemsBIN *uniqueItems = SgptDataTables->uniqueItems + output->specificID - 1;
                stream << D2GetStringFromIndex(uniqueItems->uniqueNameId);
            } else if (output->quality == ITEMQUALITY_SET) {
                SetItemsBIN *setItems = SgptDataTables->setItems + output->specificID - 1;
                stream <<  D2GetStringFromIndex(setItems->setNameId);
            } else {
                stream << STRING_ERROR;
                return;
            }
        } else {
            switch (output->quality) {
                case 1:
                    stream << getLocalString(STR_CRACKED) << SPACE;
                    break;
                case 2:
                    stream << getLocalString(STR_NORMAL) << SPACE;
                    break;
                case 3:
                    stream << getLocalString(STR_SUPERIOR) << SPACE;
                    break;
                case 4:
                    stream << getLocalString(STR_MAGIC) << SPACE;
                    break;
                case 5:
                    stream << getLocalString(STR_SET) << SPACE;
                    break;
                case 6:
                    stream << getLocalString(STR_RARE) << SPACE;
                    break;
                case 7:
                    stream << getLocalString(STR_UNIQUE) << SPACE;
                    break;
                case 8:
                    stream << getLocalString(STR_CRAFTED) << SPACE;
                    break;
                case 9:
                    stream << getLocalString(STR_TEMPERED) << SPACE;
                    break;
            }
            switch (output->outputType) {
                case 0xFC: {
                    ItemsBIN *items = D2GetItemsBIN(output->ID);
                    stream << StripGender(D2GetStringFromIndex(items->NameStr));
                    break;
                }
                case 0xFD: {
                    ItemTypesBIN *itemTypeData = D2GetItemTypesBIN(output->ID);
                    if (!itemTypeData)
                        stream << L"Unknown Item Type";
                    else
                        stream << getLocalTypeString(itemTypeData->code);
                    break;
                }
                case 0xFE:
                    stream << getLocalString(STR_ITEM);
                    break;
                case 0xFF:
                    stream << getLocalString(STR_ITEM_SAME_TYPE);
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
                stream << getLocalString(STR_WITH_SOCKETS);
        }
    }

    void printInputItem(CubeInput *input, std::wstringstream &stream, BYTE *nbInputs, bool *InNoSocket) {
        if (!input->byItemID && !input->byItemTypeID)
            return;
        if (*nbInputs)
            stream << L" + ";
        BYTE nb = input->quantity > 0 ? input->quantity : 1;
        *nbInputs += nb;
        if (nb > 1)
            stream << nb << SPACE;
        if (input->isEthereal)
            stream << getLocalString(STR_ETHERAL) << SPACE;
        if (input->isNotEthereal)
            stream << getLocalString(STR_NOT_ETHERAL) << SPACE;
        if (input->isNotRuneword)
            stream << getLocalString(STR_NOT_RUNEWORD) << SPACE;
        if (input->isBasic)
            stream << getLocalString(STR_BASIC) << SPACE;
        if (input->isExceptional)
            stream << getLocalString(STR_EXCEPTIONAL) << SPACE;
        if (input->isElite)
            stream << getLocalString(STR_ELITE) << SPACE;
        if (input->isSpecificItem) {
            if (input->quality == ITEMQUALITY_UNIQUE) {
                UniqueItemsBIN *uniqueItems = SgptDataTables->uniqueItems + input->specificID - 1;
                stream << StripGender(D2GetStringFromIndex(uniqueItems->uniqueNameId));
            } else if (input->quality == ITEMQUALITY_SET) {
                SetItemsBIN *setItems = SgptDataTables->setItems + input->specificID - 1;
                stream << StripGender(D2GetStringFromIndex(setItems->setNameId));
            } else {
                stream << STRING_ERROR << SPACE;
                return;
            }
        } else {
            switch (input->quality) {
                case 1:
                    stream << getLocalString(STR_CRACKED) << SPACE;
                    break;
                case 2:
                    stream << getLocalString(STR_NORMAL) << SPACE;
                    break;
                case 3:
                    stream << getLocalString(STR_SUPERIOR) << SPACE;
                    break;
                case 4:
                    stream << getLocalString(STR_MAGIC) << SPACE;
                    break;
                case 5:
                    stream << getLocalString(STR_SET) << SPACE;
                    break;
                case 6:
                    stream << getLocalString(STR_RARE) << SPACE;
                    break;
                case 7:
                    stream << getLocalString(STR_UNIQUE) << SPACE;
                    break;
                case 8:
                    stream << getLocalString(STR_CRAFTED) << SPACE;
                    break;
                case 9:
                    stream << getLocalString(STR_TEMPERED) << SPACE;
                    break;
            }
            if (input->byItemTypeID) {
                ItemTypesBIN *itemTypeData = D2GetItemTypesBIN(input->ID);
                if (!itemTypeData)
                    stream << L"Unknown Item Type";
                else
                    stream << getLocalTypeString(itemTypeData->code);
            } else if (input->ID == 0xFFFF) {
                stream << getLocalString(STR_ITEM);
            } else {
                ItemsBIN *items = D2GetItemsBIN(input->ID);
                stream << StripGender(D2GetStringFromIndex(items->NameStr));
            }
        }
        if (input->includeUpgradedVersions && !input->isElite)
            stream << SPACE << getLocalString(STR_INCLUDE_UPGRADED);
        if (input->haveNoSocket) {
            stream << SPACE << getLocalString(STR_WITHOUT_SOCKET);
            *InNoSocket = true;
        }
        if (input->haveSockets)
            stream << SPACE << getLocalString(STR_WITH_SOCKETS);
    }

    std::wstring printLine(CubeMainBIN *bin, int i) {
        if (!bin || !bin->enabled) return L"";
        bool InNoSocket = false;
        BYTE realNbInputs = 0;
        std::wstringstream stream;
        stream << std::setfill(L' ') << std::setw(6) << i << L": ";
        printInputItem(&bin->input1, stream, &realNbInputs, &InNoSocket);
        printInputItem(&bin->input2, stream, &realNbInputs, &InNoSocket);
        printInputItem(&bin->input3, stream, &realNbInputs, &InNoSocket);
        printInputItem(&bin->input4, stream, &realNbInputs, &InNoSocket);
        printInputItem(&bin->input5, stream, &realNbInputs, &InNoSocket);
        printInputItem(&bin->input6, stream, &realNbInputs, &InNoSocket);
        printInputItem(&bin->input7, stream, &realNbInputs, &InNoSocket);
        if (realNbInputs != bin->numinputs) {
            stream << L" *** ERROR : numInputs(" << bin->numinputs << ") != realNbInputs(" << realNbInputs << ") ***";
            return stream.str();
        }
        stream << L" => ";
        int realNbOutputs = 0;
        printOutputItem(&bin->output1, stream, &realNbOutputs, InNoSocket);
        printOutputItem(&bin->output2, stream, &realNbOutputs, InNoSocket);
        printOutputItem(&bin->output3, stream, &realNbOutputs, InNoSocket);
        if (bin->minDiff == 1)
            stream << SPACE << getLocalString(STR_ONLY_N_H);
        else if (bin->minDiff == 2)
            stream << SPACE << getLocalString(STR_ONLY_HELL);
        if (bin->playerClass != 0xFF) {
            CharStatsBIN *charStats = D2GetCharStatsBIN(bin->playerClass);
            stream << L" (";
            wchar_t buffer[200];
            swprintf_s(buffer, sizeof buffer, getLocalString(STR_ONLY_CLASS), charStats->name);
            stream << buffer;
            stream << L")";
        }
        if ((bin->op > 0) && (bin->op != 28)) {
            stream << L" [op" << bin->op << L"(" << bin->param << L"," << bin->value<< L")]";
        }
        return std::regex_replace(stream.str(), std::wregex(L"\n"), L"");
    }

    std::wstring vectorToWstring(std::vector<std::wstring> vec){
        std::wstringstream stream;
        for (std::wstring str: vec) {
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
            if(!str.empty())
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
        strcat(filename, CUBEFORMULA_FILE);
        int nbLines = D2GetNbCubeMainBIN();
        log_msg("nbLines : %d\n", nbLines);
        auto stream = printAllCubeMainBIN();
        writeStreamToFile(stream, filename);
        log_msg("\n********** Printing over **********\n\n");
    }

}
#pragma clang diagnostic pop