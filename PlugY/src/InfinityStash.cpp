/*=================================================================
	File created by Yohann NICOLAS.
	Add support 1.13d by L'Autour.
	Add support 1.14d by haxifix.

	Gestion of the infinity and shared Stash.

=================================================================*/

#include "infinityStash.h"
#include "updateClient.h"
#include "interface_Stash.h"
#include "common.h"
#include "d2functions.h"
#include "error.h"
#include "LocalizedStrings.h"
#include <updatingConst.h>
#include <d2constants.h>
#include "modifMemory.h"

namespace PlugY {
    using namespace Commons;
#define STASH_TAG 0x5453            //"ST"
#define JM_TAG 0x4D4A                //"JM"

    DWORD maxSelfPages = -1;

    DWORD maxSharedPages = -1;

    DWORD nbPagesPerIndex = 10;

    DWORD nbPagesPerIndex2 = 100;

    bool active_multiPageStash = false;

    bool autoRenameStashPage = false;

    int active_SharedStashInMultiPlayer = 0;//0: disabled, 1:shared in SP, 2: shared in SP & TCP/IP
    bool active_sharedStash = false;

    bool separateHardSoftStash = false;

    bool active_sharedGold = false;

    char *sharedStashFilename = NULL;

    typedef int (*TchangeToSelectedStash)(Commons::Unit *ptChar, Stash *newStash, DWORD bOnlyItems, DWORD bIsClient);

    Commons::Unit *firstClassicStashItem(Commons::Unit *ptChar) {
        Commons::Unit *ptItem = D2InventoryGetFirstItem(getInventory(ptChar));
        while (ptItem) {
            if (D2ItemGetPage(D2GetRealItem(ptItem)) == 4)
                return ptItem;
            ptItem = D2UnitGetNextItem(ptItem);
        }
        return NULL;
    }

    DWORD endStashList(Commons::Unit *ptChar, Stash *ptStash) {
        Stash *stash = ptStash;
        while (stash) {
            if (stash->ptListItem || ((stash == getPYPlayerData(ptChar)->currentStash) && firstClassicStashItem(ptChar))) return 0;
            if (stash->name != NULL && stash->name[0]) return 0;
            stash = stash->nextStash;
        }
        return 1;
    }

//bool isInList(Stash* list, Stash* pStash)
//{
//	Stash* ptStash = list;
//	while(ptStash)
//	{
//		if (ptStash->id == pStash->id) return true;
//		ptStash = ptStash->nextStash;
//	}
//	return false;
//}


    Stash *getLastStash(Stash *ptStash) {
        if (!ptStash)
            return NULL;
        while (ptStash->nextStash)
            ptStash = ptStash->nextStash;
        return ptStash;
    }

    Stash *newStash(DWORD id) {
        d2_assert(id == 0xFFFFFFFF, "Too much stash", __FILE__, __LINE__);
        Stash *stash = (Stash *) malloc(sizeof(Stash));//D2AllocMem(memPool, sizeof(Stash),__FILE__,__LINE__,0);
        d2_assert(!stash, "Error on stash allocation.", __FILE__, __LINE__);
        ZeroMemory(stash, sizeof(Stash));
        stash->id = id;
        return stash;
    }

    Stash *addStash(Commons::Unit *ptChar, bool isShared, bool autoSetIndex, Stash *previous) {
        previous = getLastStash(previous ? previous : isShared ? getPYPlayerData(ptChar)->sharedStash : getPYPlayerData(ptChar)->selfStash);
        if (previous)
            isShared = previous->isShared;
        Stash *stash = newStash(isShared ? getPYPlayerData(ptChar)->nbSharedPages++ : getPYPlayerData(ptChar)->nbSelfPages++);
        stash->isShared = isShared;
        stash->previousStash = previous;
        if (previous) {
            previous->nextStash = stash;
            if (autoSetIndex) {
                stash->isIndex = ((stash->id + 1) % nbPagesPerIndex) == 0;
                stash->isMainIndex = ((stash->id + 1) % nbPagesPerIndex2) == 0;
            }
        } else if (isShared) {
            getPYPlayerData(ptChar)->sharedStash = stash;
            stash->isIndex = 1;
            stash->isMainIndex = 1;
        } else {
            getPYPlayerData(ptChar)->selfStash = stash;
            stash->isIndex = 1;
            stash->isMainIndex = 1;
        }
        log_msg("AddStash: stash->id=%d\tstash->isShared=%d\tnbSelf=%d\tnbShared=%d\n", stash->id, stash->isShared, getPYPlayerData(ptChar)->nbSelfPages, getPYPlayerData(ptChar)->nbSharedPages);
        return stash;
    }

    Stash *getStash(Commons::Unit *ptChar, DWORD isShared, DWORD id) {
        Stash *ptStash = isShared ? getPYPlayerData(ptChar)->sharedStash : getPYPlayerData(ptChar)->selfStash;
        while (ptStash) {
            if (ptStash->id == id) return ptStash;
            ptStash = ptStash->nextStash;
        }
        return NULL;
    }

    int changeToSelectedStash_9(Commons::Unit *ptChar, Stash *newStash, DWORD bOnlyItems, DWORD bIsClient) {
        if (!newStash) return 0;
        Stash *currentStash = getPYPlayerData(ptChar)->currentStash;
        if (currentStash == newStash) return 0;
        log_msg("changeToSelectedStash ID:%d\tshared:%d\tonlyItems:%d\tclient:%d\n", newStash->id, newStash->isShared, bOnlyItems, bIsClient);
        d2_assert(currentStash && currentStash->ptListItem, "ERROR : currentStash isn't empty (ptListItem != NULL)", __FILE__, __LINE__);

        // collect items to remove
        Inventory *ptInventory = getInventory(ptChar);
        Commons::Unit *ptNextItem;
        Commons::Unit *ptPrevItem = NULL;
        auto ptItem = D2InventoryGetFirstItem(ptInventory);
        while (ptItem) {
            ptNextItem = D2UnitGetNextItem(ptItem);
            if (D2ItemGetPage(D2GetRealItem(ptItem)) == 4) {
                D2SetAnim(D2GetRealItem(ptItem), -1);
                if (ptPrevItem) {
                    ptPrevItem->mode = (DWORD) ptNextItem;//is ptPrevItem->nextNode = ptNextItem;
                } else {
                    ptInventory->currentUsedSocket = (DWORD) ptNextItem;//is ptInventory->ptListItem = ptNextItem;
                }
                if (!ptNextItem)
                    ptInventory->Inventory2C = (DWORD) ptPrevItem;
                ptInventory->Inventory30 = ptInventory->Inventory30 - 1;
                D2Common10250(__FILE__, __LINE__, ptInventory, D2GetPosX(D2GetRealItem(ptItem)), D2GetPosY(D2GetRealItem(ptItem)), 0xC, bIsClient, 4);
//			ptItem = D2InvRemoveItem(getInventory(ptChar), D2GetRealItem(ptItem));
//			D2Common10250(__FILE__,__LINE__,getInventory(ptChar), D2GetPosX(ptItem), D2GetPosY(ptItem), 0xC, bIsClient, 4);
                if (currentStash) {
//				ptItem = setNextItem(ptItem, getPYPlayerData(ptChar)->currentStash->ptListItem);
                    ptItem->mode = (DWORD) currentStash->ptListItem;//is ptItem->nextNode = ptListItem
                    currentStash->ptListItem = ptItem;
                };
            } else ptPrevItem = ptItem;
            ptItem = ptNextItem;
        }

        // add items of new stash
        ptItem = newStash->ptListItem;
        while (ptItem) {
            D2InvAddItem(getInventory(ptChar), D2GetRealItem(ptItem), D2GetPosX(D2GetRealItem(ptItem)), D2GetPosY(D2GetRealItem(ptItem)), 0xC, bIsClient, 4);
            D2Common10242(getInventory(ptChar), D2GetRealItem(ptItem), 1);
            ptItem = D2UnitGetNextItem(ptItem);
        }
        if (bOnlyItems)
            newStash->ptListItem = getPYPlayerData(ptChar)->currentStash->ptListItem;
        else
            getPYPlayerData(ptChar)->currentStash = newStash;
        getPYPlayerData(ptChar)->currentStash->ptListItem = NULL;
        return 1;
    }

    int changeToSelectedStash_10(Commons::Unit *ptChar, Stash *newStash, DWORD bOnlyItems, DWORD bIsClient) {
        if (!newStash) return 0;
        Stash *currentStash = getPYPlayerData(ptChar)->currentStash;
        if (currentStash == newStash) return 0;
        log_msg("changeToSelectedStash ID:%d\tshared:%d\tonlyItems:%d\tclient:%d\n", newStash->id, newStash->isShared, bOnlyItems, bIsClient);
        d2_assert(currentStash && currentStash->ptListItem, "ERROR : currentStash isn't empty (ptListItem != NULL)", __FILE__, __LINE__);

        // Remove items from current page
        Unit *ptNextItem;
        Unit *ptItem = D2InventoryGetFirstItem(getInventory(ptChar));
        while (ptItem) {
            ptNextItem = D2UnitGetNextItem(ptItem);
            if (D2ItemGetPage(ptItem) == 4) {
                BYTE tmp = ptItem->ptItemData->ItemData2;
                ptItem = D2InvRemoveItem(getInventory(ptChar), ptItem);
                ptItem->ptItemData->ItemData2 = tmp;
                if (currentStash) {
                    ptItem->ptItemData->ptNextItem = currentStash->ptListItem;
                    currentStash->ptListItem = ptItem;
                }
            }
            ptItem = ptNextItem;
        }

        // add items of new stash
        ptItem = newStash->ptListItem;
        while (ptItem) {
            D2InvAddItem(getInventory(ptChar), ptItem, ptItem->path->x, ptItem->path->y, 0xC, bIsClient, 4);
            ptItem = D2UnitGetNextItem(ptItem);
        }
        if (bOnlyItems)
            newStash->ptListItem = getPYPlayerData(ptChar)->currentStash->ptListItem;
        else
            getPYPlayerData(ptChar)->currentStash = newStash;
        getPYPlayerData(ptChar)->currentStash->ptListItem = NULL;
        return 1;
    }

    TchangeToSelectedStash changeToSelectedStash;

    DWORD loadStash(Commons::Unit *ptChar, Stash *ptStash, BYTE data[], DWORD startSize, DWORD maxSize, DWORD *retSize) {
        DWORD curSize = startSize;
        DWORD nbBytesRead;
        log_msg("loadStash\n");
        *retSize = curSize;
        if (*(WORD *) &data[curSize] != STASH_TAG)//"ST"
        {
            log_msg("loadStash -> Bad tag of stash of character %s : %04X\n", getPlayerData(ptChar)->name, *(WORD *) &data[curSize]);
            return 0x7;//Unable to enter game. Bad inventory data
        }
        curSize += 2;

        // Read flags.
        int len = strlen((char *) &data[curSize]);
        if (*(WORD *) &data[curSize + len + 1] != JM_TAG) {
            ptStash->flags = *(DWORD *) &data[curSize];
            curSize += 4;
        }

        // Read Name
//	if (strlen((char *)&data[curSize]) > 0xF)
//		*(char *)&data[curSize+0xF] = NULL;
        if (strlen((char *) &data[curSize]))
            ptStash->name = (char *) malloc(strlen((char *) &data[curSize]) + 1);//D2AllocMem(getGame(ptChar)->memoryPool, strlen((char *)&data[curSize]),__FILE__,__LINE__,0);
        if (ptStash->name)
            strcpy(ptStash->name, (char *) &data[curSize]);
        curSize += strlen((char *) &data[curSize]) + 1;

        // Read inventory.
        DWORD ret = D2LoadInventory(getGame(ptChar), ptChar, (saveBitField *) &data[curSize], 0x60, maxSize - curSize, 0, &nbBytesRead);
        if (ret) log_msg("loadStash -> D2LoadInventory failed\n");
        log_msg("Stash loaded (%d : %s)\n", ptStash->id, ptStash->name);
        *retSize = curSize + nbBytesRead;
        return ret;
    }

    void autoSetIndex(Stash *firstStash) {
        if (!firstStash)
            return;
        log_msg("autoSetIndex\n");
        Stash *stash = firstStash;
        while (stash) {
            if (stash->isIndex || stash->isMainIndex)
                return;
            stash = stash->nextStash;
        }
        stash = firstStash;
        stash->isIndex = 1;
        stash->isMainIndex = 1;
        stash = stash->nextStash;
        while (stash) {
            stash->isIndex = ((stash->id + 1) % nbPagesPerIndex) == 0;
            stash->isMainIndex = ((stash->id + 1) % nbPagesPerIndex2) == 0;
            stash = stash->nextStash;
        }
    }

    DWORD loadStashList(Commons::Unit *ptChar, BYTE *data, DWORD maxSize, DWORD *curSize, bool isShared) {
        DWORD curStash = 0;
        Stash *newStash = NULL;
        DWORD nbStash = *(DWORD *) &data[*curSize];
        *curSize += 4;
        log_msg("loadStashList nbStash=%d\n", nbStash);
        while (curStash < nbStash) {
            newStash = addStash(ptChar, isShared, false, newStash);
            changeToSelectedStash(ptChar, newStash, 0, false);
            DWORD ret = loadStash(ptChar, newStash, data, *curSize, 10000000, curSize);
            if (ret) return ret;
            curStash++;
        }
        if (!isShared) {
            if (getPYPlayerData(ptChar)->selfStash)
                autoSetIndex(getPYPlayerData(ptChar)->selfStash);
            else {
                newStash = addStash(ptChar, isShared, true, newStash);
                getPYPlayerData(ptChar)->currentStash = newStash;
            }
        }
        if (isShared) {
            if (getPYPlayerData(ptChar)->sharedStash)
                autoSetIndex(getPYPlayerData(ptChar)->sharedStash);
            else {
                newStash = addStash(ptChar, isShared, true, newStash);
                if (!getPYPlayerData(ptChar)->currentStash)
                    getPYPlayerData(ptChar)->currentStash = newStash;
            }
        }
        changeToSelectedStash(ptChar, isShared ? getPYPlayerData(ptChar)->sharedStash : getPYPlayerData(ptChar)->selfStash, 0, false);
        return 0;
    }

//ADDDATA(DWORD, curSize, 0);

#define DATA (*data + *curSize)
#define ADDDATA(T)        (T*)DATA;        *curSize += sizeof(T)
#define SETDATA(T, V)    *(T*)DATA = V;    *curSize += sizeof(T)

    void saveStash(Commons::Unit *ptChar, Stash *ptStash, BYTE **data, DWORD *maxSize, DWORD *curSize) {
        //write "ST"
        SETDATA(WORD, STASH_TAG);

        //Write flags.
        SETDATA(DWORD, ptStash->flags);

        //save name
        if (ptStash->name) {
            int size = strlen(ptStash->name);
            if (size > 20) size = 20;
            strncpy((char *) DATA, ptStash->name, size);
            *curSize += size;
        }
        SETDATA(char, NULL);

        //Write "JM" of inventory
        SETDATA(WORD, JM_TAG);

        //Get position of counter of items in inventory
        WORD *ptNBItem = ADDDATA(WORD);
        *ptNBItem = 0;

        //Get first item
        Unit *ptItem;
        if ((ptStash->id == getPYPlayerData(ptChar)->currentStash->id) && (ptStash->isShared == getPYPlayerData(ptChar)->currentStash->isShared))
            ptItem = D2InventoryGetFirstItem(getInventory(ptChar));
        else
            ptItem = ptStash->ptListItem;

        //Write all items
        while (ptItem) {
            if (D2ItemGetPage(D2GetRealItem(ptItem)) == 4) {
                int nbBytes = D2SaveItem(D2GetRealItem(ptItem), (saveBitField *) DATA, *maxSize - *curSize, 1, 1, 0);
                d2_assert(!nbBytes, "!\"Character has too many items\"", __FILE__, __LINE__);
                *curSize += nbBytes;
                (*ptNBItem)++;
            }
            ptItem = D2UnitGetNextItem(ptItem);
        }
    }

    void saveStashList(Commons::Unit *ptChar, Stash *ptStash, BYTE **data, DWORD *maxSize, DWORD *curSize) {
        DWORD curSizeNbStash = *curSize;
        *curSize += sizeof(DWORD);
        DWORD nbStash = 0;
        while (ptStash) {
            if (*curSize + 0x2000 > *maxSize) {
                BYTE *oldData = *data;
                *maxSize *= 2;
                *data = (BYTE *) D2AllocMem(getGame(ptChar)->memoryPool, *maxSize, __FILE__, __LINE__, 0);
                d2_assert(!*data, "Error : Memory allocation", __FILE__, __LINE__);
                CopyMemory(*data, oldData, *curSize);
                D2FreeMem(getGame(ptChar)->memoryPool, oldData, __FILE__, __LINE__, 0);
            }
            saveStash(ptChar, ptStash, data, maxSize, curSize);
            nbStash++;
            ptStash = endStashList(ptChar, ptStash->nextStash) ? NULL : ptStash->nextStash;
        }
        *(DWORD *) (*data + curSizeNbStash) = nbStash;
    }

/////// client
    void updateSelectedStashClient(Commons::Unit *ptChar) {
        Stash *newStash = getPYPlayerData(ptChar)->currentStash;
        if (!newStash)
            return;
        updateClient(ptChar, UC_SELECT_STASH, newStash->id, newStash->flags, getPYPlayerData(ptChar)->flags);
        updateClient(ptChar, UC_PAGE_NAME, newStash->name);
    }

    void setSelectedStashClient(DWORD stashId, DWORD stashFlags, DWORD flags, bool bOnlyItems) {
        log_msg("setSelectedStashClient ID:%d, stashFlags:%d, flags:%08X\n", stashId, stashFlags, flags);
        Unit *ptChar = D2GetClientPlayer();
        Stash *newStash = getStash(ptChar, (stashFlags & 1) == 1, stashId);
        if (!newStash)
            do
                newStash = addStash(ptChar, (stashFlags & 1) == 1, false, newStash);
            while (newStash->id < stashId);
        newStash->flags = stashFlags;
        changeToSelectedStash(ptChar, newStash, bOnlyItems, 1);
        getPYPlayerData(ptChar)->flags = flags;
    }

    void selectStash(Commons::Unit *ptChar, Stash *newStash, bool forceUpdate) {
        if (!newStash)
            return;
        if (!forceUpdate && newStash == getPYPlayerData(ptChar)->currentStash)
            return;
        log_msg("selectStash ID:%d\tshared:%d\tforceUpdate:%d\n", newStash->id, newStash->isShared, forceUpdate);
        changeToSelectedStash(ptChar, newStash, 0, 0);
        updateSelectedStashClient(ptChar);
    }

///// public functions
    void toggleToSelfStash(Commons::Unit *ptChar) {
        Stash *selStash = getPYPlayerData(ptChar)->selfStash;
        if (selStash && (selStash != getPYPlayerData(ptChar)->currentStash)) {
            getPYPlayerData(ptChar)->showSharedStash = false;
            selectStash(ptChar, selStash);
        }
    }

    void toggleToSharedStash(Commons::Unit *ptChar) {
        Stash *selStash = getPYPlayerData(ptChar)->sharedStash;
        if (selStash && (selStash != getPYPlayerData(ptChar)->currentStash)) {
            getPYPlayerData(ptChar)->showSharedStash = true;
            selectStash(ptChar, selStash);
        }
    }

    void swapStash(Commons::Unit *ptChar, Stash *curStash, Stash *swpStash) {
        log_msg("swapStash ID:%d\tshared:%d\tonlyItems:%d\tclient:%d\n", swpStash->id, swpStash->isShared, 1, 0);
        if (!ptChar || !curStash || !swpStash || curStash == swpStash)
            return;
        changeToSelectedStash(ptChar, swpStash, 1, 0);
        updateClient(ptChar, UC_SELECT_STASH, swpStash->id, swpStash->flags | 8, getPYPlayerData(ptChar)->flags);
    }

    void toggleStash(Commons::Unit *ptChar, DWORD page) {
        log_msg("toggle stash page = %u\n", page);
        Stash *curStash = getPYPlayerData(ptChar)->currentStash;
        Stash *swpStash = curStash->isShared ? getPYPlayerData(ptChar)->selfStash : getPYPlayerData(ptChar)->sharedStash;
        swapStash(ptChar, curStash, swpStash);
    }

    void swapStash(Commons::Unit *ptChar, DWORD page, bool toggle) {
        log_msg("swap stash page = %u, toggle=%u\n", page, toggle);
        Stash *curStash = getPYPlayerData(ptChar)->currentStash;
        Stash *swpStash = curStash->isShared == toggle ? getPYPlayerData(ptChar)->selfStash : getPYPlayerData(ptChar)->sharedStash;
        if (!swpStash)
            swpStash = addStash(ptChar, !curStash->isShared, true, swpStash);
        for (DWORD i = 0; i < page; i++) {
            log_msg("swap stash : %i\n", i);
            if (swpStash->nextStash == NULL)
                addStash(ptChar, swpStash->isShared, false, swpStash);
            swpStash = swpStash->nextStash;
        }
        swapStash(ptChar, curStash, swpStash);
    }

    void insertStash(Commons::Unit *ptChar) {
        Stash *curStash = getPYPlayerData(ptChar)->currentStash;
        Stash *stash = addStash(ptChar, curStash->isShared, false, curStash);
        while (stash->previousStash != curStash) {
            stash->flags = stash->previousStash->flags;
            stash->name = stash->previousStash->name;
            stash->ptListItem = stash->previousStash->ptListItem;
            stash = stash->previousStash;
        }
        stash->isIndex = 0;
        stash->isMainIndex = 0;
        stash->name = NULL;
        stash->ptListItem = NULL;
    }

    bool deleteStash(Commons::Unit *ptChar, bool isClient) {
        if (firstClassicStashItem(ptChar) != NULL)
            return false;
        //if (D2InventoryGetFirstItem())
        Stash *stash = getPYPlayerData(ptChar)->currentStash;
        if (stash->nextStash == NULL) {
            stash->isIndex = 0;
            stash->isMainIndex = 0;
            stash->name = NULL;
            return true;
        }
        stash->flags = stash->nextStash->flags;
        stash->name = stash->nextStash->name;
        if (stash->nextStash->ptListItem != NULL) {
            log_msg("deleteStash ID:%d\tshared:%d\tonlyItems:%d\tclient:%d\n", stash->id, stash->isShared, 1, isClient);
            changeToSelectedStash(ptChar, stash->nextStash, 1, isClient);
        }
        stash = stash->nextStash;
        while (stash->nextStash) {
            stash->flags = stash->nextStash->flags;
            stash->name = stash->nextStash->name;
            stash->ptListItem = stash->nextStash->ptListItem;
            stash = stash->nextStash;
        }
        stash->isIndex = 0;
        stash->isMainIndex = 0;
        stash->name = NULL;
        stash->ptListItem = NULL;
        return true;
    }

    void renameCurrentStash(Commons::Unit *ptChar, char *name) {
        log_msg("renameCurrentStash : '%s'\n", name);
        Stash *stash = getPYPlayerData(ptChar)->currentStash;
        int len = 0;
        if (name != NULL)
            len = strlen(name);
        if (stash->name)
            D2FogMemDeAlloc(stash->name, __FILE__, __LINE__, 0);
        if (len > 0) {
            stash->name = (char *) malloc(len + 1);//D2FogMemAlloc(len,__FILE__,__LINE__,0);
            strcpy(stash->name, name);
        } else
            stash->name = NULL;
    }

    void setCurrentStashIndex(Commons::Unit *ptChar, int index) {
        if (!getPYPlayerData(ptChar)->currentStash)
            return;
        getPYPlayerData(ptChar)->currentStash->isIndex = index >= 1;
        getPYPlayerData(ptChar)->currentStash->isMainIndex = index == 2;
        updateSelectedStashClient(ptChar);
    }

    void selectPreviousStash(Commons::Unit *ptChar) {
        Stash *selStash = getPYPlayerData(ptChar)->currentStash->previousStash;
        if (selStash && (selStash != getPYPlayerData(ptChar)->currentStash))
            selectStash(ptChar, selStash);
    }

    void selectPrevious2Stash(Commons::Unit *ptChar)// Select first stash
    {
        Stash *selStash = getPYPlayerData(ptChar)->showSharedStash ? getPYPlayerData(ptChar)->sharedStash : getPYPlayerData(ptChar)->selfStash;
        if (selStash && (selStash != getPYPlayerData(ptChar)->currentStash))
            selectStash(ptChar, selStash);
    }

    void selectNextStash(Commons::Unit *ptChar) {
        Stash *selStash = getPYPlayerData(ptChar)->currentStash;
        if (!selStash->isShared && (selStash->id >= maxSelfPages)) return;
        if (selStash->isShared && (selStash->id >= maxSharedPages)) return;
        selStash = selStash->nextStash ? selStash->nextStash : addStash(ptChar, getPYPlayerData(ptChar)->showSharedStash, true, selStash);
        if (selStash && (selStash != getPYPlayerData(ptChar)->currentStash))
            selectStash(ptChar, selStash);
    }

    void selectNext2Stash(Commons::Unit *ptChar)//select last stash
    {
        Stash *selStash = getPYPlayerData(ptChar)->showSharedStash ? getPYPlayerData(ptChar)->sharedStash : getPYPlayerData(ptChar)->selfStash;//getPYPlayerData(ptChar)->currentStash;
        Stash *lastStash = NULL;
        Unit *currentStashItem = firstClassicStashItem(ptChar);
        while (selStash) {
            if (selStash->ptListItem || (selStash == getPYPlayerData(ptChar)->currentStash) && currentStashItem) lastStash = selStash;
            selStash = selStash->nextStash;
        }
        if (!lastStash)
            lastStash = getPYPlayerData(ptChar)->showSharedStash ? getPYPlayerData(ptChar)->sharedStash : getPYPlayerData(ptChar)->selfStash;
        if (lastStash != getPYPlayerData(ptChar)->currentStash)
            selectStash(ptChar, lastStash);
    }

    void selectPreviousIndexStash(Commons::Unit *ptChar) {
        selectPreviousStash(ptChar);
        Stash *selStash = getPYPlayerData(ptChar)->currentStash;
        while (selStash && !selStash->isIndex)
            selStash = selStash->previousStash;
        if (selStash == NULL) {
            selStash = getPYPlayerData(ptChar)->currentStash;
            while (selStash->previousStash && ((selStash->id + 1) % nbPagesPerIndex != 0))
                selStash = selStash->previousStash;
        }
        if (selStash && (selStash != getPYPlayerData(ptChar)->currentStash))
            selectStash(ptChar, selStash);
    }

    void selectPreviousIndex2Stash(Commons::Unit *ptChar) {
        selectPreviousStash(ptChar);
        Stash *selStash = getPYPlayerData(ptChar)->currentStash;
        while (selStash && !selStash->isMainIndex)
            selStash = selStash->previousStash;
        if (selStash == NULL) {
            selStash = getPYPlayerData(ptChar)->currentStash;
            while (selStash->previousStash && ((selStash->id + 1) % nbPagesPerIndex2 != 0))
                selStash = selStash->previousStash;
        }
        if (selStash && (selStash != getPYPlayerData(ptChar)->currentStash))
            selectStash(ptChar, selStash);
    }

    void selectNextIndexStash(Commons::Unit *ptChar) {
        selectNextStash(ptChar);
        Stash *selStash = getPYPlayerData(ptChar)->currentStash;
        while (selStash && !selStash->isIndex)
            selStash = selStash->nextStash;
        if (selStash == NULL) {
            selStash = getPYPlayerData(ptChar)->currentStash;
            while ((selStash->id + 1) % nbPagesPerIndex != 0) {
                if (!selStash->isShared && (selStash->id >= maxSelfPages)) break;
                if (selStash->isShared && (selStash->id >= maxSharedPages)) break;
                selStash = selStash->nextStash ? selStash->nextStash : addStash(ptChar, getPYPlayerData(ptChar)->showSharedStash, true, selStash);
            }
        }
        if (selStash && (selStash != getPYPlayerData(ptChar)->currentStash))
            selectStash(ptChar, selStash);
    }

    void selectNextIndex2Stash(Commons::Unit *ptChar) {
        selectNextStash(ptChar);
        Stash *selStash = getPYPlayerData(ptChar)->currentStash;
        while (selStash && !selStash->isMainIndex)
            selStash = selStash->nextStash;
        if (selStash == NULL) {
            selStash = getPYPlayerData(ptChar)->currentStash;
            while ((selStash->id + 1) % nbPagesPerIndex2 != 0) {
                if (!selStash->isShared && (selStash->id >= maxSelfPages)) break;
                if (selStash->isShared && (selStash->id >= maxSharedPages)) break;
                selStash = selStash->nextStash ? selStash->nextStash : addStash(ptChar, getPYPlayerData(ptChar)->showSharedStash, true, selStash);
            }
        }
        if (selStash && (selStash != getPYPlayerData(ptChar)->currentStash))
            selectStash(ptChar, selStash);
    }

    const WCHAR * getDefaultStashName(Commons::Unit *ptChar) {
        if (!autoRenameStashPage)
            return getLocalString(getPYPlayerData(ptChar)->currentStash->isShared ? STR_SHARED_PAGE_NUMBER : STR_PERSONAL_PAGE_NUMBER);
        int onlyOneUnique = -1;
        int uniqueNameIndex = -1;
        int onlyOneSet = -1;
        int setNameIndex = -1;
        int onlyOneMisc = -1;
        int miscNameIndex = -1;
        Unit *ptItem = D2InventoryGetFirstItem(getInventory(ptChar));
        int nb = 0;
        while (ptItem) {
            if (D2ItemGetPage(ptItem) == 4) {
                if (onlyOneUnique != 0) {
                    if (ptItem->ptItemData->quality != ITEMQUALITY_UNIQUE) {
                        onlyOneUnique = 0;
                        uniqueNameIndex = -1;
                    } else {
                        int uniqueId = D2GetUniqueID(ptItem);
                        UniqueItemsBIN *uniqueBIN = SgptDataTables->uniqueItems + uniqueId;
                        if (onlyOneUnique < 0) {
                            onlyOneUnique = 1;
                            uniqueNameIndex = uniqueBIN->uniqueNameId;
                        } else if (setNameIndex != uniqueBIN->uniqueNameId) {
                            onlyOneUnique = 0;
                            uniqueNameIndex = -1;
                        }
                    }
                }
                if (onlyOneSet != 0) {
                    if (ptItem->ptItemData->quality != ITEMQUALITY_SET) {
                        onlyOneSet = 0;
                        setNameIndex = -1;
                    } else {
                        int uniqueID = ptItem->ptItemData->uniqueID;
                        SetItemsBIN *itemBIN = &SgptDataTables->setItems[uniqueID];
                        SetsBIN *setBIN = &SgptDataTables->sets[itemBIN->setId];
                        if (onlyOneSet < 0) {
                            onlyOneSet = 1;
                            setNameIndex = setBIN->setNameIndex;
                        } else if (setNameIndex != setBIN->setNameIndex) {
                            onlyOneSet = 0;
                            setNameIndex = -1;
                        }
                    }
                }
                if (onlyOneMisc != 0) {
                    if (ptItem->ptItemData->quality != ITEMQUALITY_NORMAL) {
                        onlyOneMisc = 0;
                        miscNameIndex = -1;
                    } else {
                        ItemsBIN *ptItemsBin = D2GetItemsBIN(ptItem->nTxtFileNo);
                        if (onlyOneMisc < 0) {
                            onlyOneMisc = 1;
                            miscNameIndex = ptItemsBin->NameStr;
                        } else if (miscNameIndex != ptItemsBin->NameStr) {
                            onlyOneMisc = 0;
                            miscNameIndex = -1;
                        }
                    }
                }
            }
            ptItem = D2UnitGetNextItem(ptItem);
        }
        if (onlyOneUnique == 1 && uniqueNameIndex >= 0)
            return StripGender(D2GetStringFromIndex(uniqueNameIndex));
        if (onlyOneSet == 1 && setNameIndex >= 0)
            return StripGender(D2GetStringFromIndex(setNameIndex));
        if (onlyOneMisc == 1 && miscNameIndex >= 0)
            return StripGender(D2GetStringFromIndex(miscNameIndex));
        return getLocalString(getPYPlayerData(ptChar)->currentStash->isShared ? STR_SHARED_PAGE_NUMBER : STR_PERSONAL_PAGE_NUMBER);
    }

    void getCurrentStashName(WCHAR *buffer, DWORD maxSize, Unit *ptChar) {
        if (getPYPlayerData(ptChar)->currentStash->name && getPYPlayerData(ptChar)->currentStash->name[0]) {
            mbstowcs(buffer, getPYPlayerData(ptChar)->currentStash->name, maxSize - 1);
        } else {
            wcsncpy(buffer, getDefaultStashName(ptChar), maxSize - 1);;
        }
        buffer[20] = NULL;
    }

//////////////////////////////////////////////////////////////////////
    Stash *curStash2;

    DWORD currentSawStash2;

    Commons::Unit *__stdcall getNextItem(Commons::Unit *ptChar, Unit *ptItem) {
        Commons::Unit *item = D2UnitGetNextItem(ptItem);
        if (item) return item;
        if (!curStash2) {
            switch (currentSawStash2) {
                case 0:
                    curStash2 = getPYPlayerData(ptChar)->selfStash;
                    currentSawStash2 = 1;
                    break;
                case 1:
                    curStash2 = getPYPlayerData(ptChar)->sharedStash;
                    currentSawStash2 = 2;
                    break;
                default:
                    return NULL;//case 2:
            }
        } else {
            curStash2 = curStash2->nextStash;
        }
        if (curStash2) {
            item = curStash2->ptListItem;
            if (item) return item;
        }
        return getNextItem(ptChar, item);
    }

    Unit *__stdcall initGetNextItem(Commons::Unit *ptChar, Unit *ptItem) {
        if (ptChar->nUnitType != UNIT_PLAYER) return NULL;
        if (!getPYPlayerData(ptChar)) return NULL;
        curStash2 = NULL;
        currentSawStash2 = 0;
        if (ptItem) return ptItem;
        return getNextItem(ptChar, ptItem);
    }

    __declspec(naked)void caller_initGetNextItem() {
        __asm{
        PUSH DWORD PTR SS:[ESP+0x20]
        PUSH DWORD PTR SS:[ESP+0xC]
        CALL initGetNextItem
        MOV EDI, EAX
        TEST EDI, EDI
        RETN
        }
    }

    __declspec(naked)void caller_getNextItem() {
        __asm{
        PUSH DWORD PTR SS:[ESP+4]
        PUSH DWORD PTR SS:[ESP+0x10]
        CALL getNextItem
        RETN 4
        }
    }


    DWORD __stdcall carry1Limit(Commons::Unit *ptChar, Unit *ptItemParam, DWORD itemNum, BYTE page) {
        if (!ptChar) return 0;
        Unit *ptItem = ptItemParam ? ptItemParam : D2GameGetObject(getGame(ptChar), UNIT_ITEM, itemNum);
        if ((page != 4) && (D2GetItemQuality(ptItem) == ITEMQUALITY_UNIQUE) && ptChar) {
            int uniqueID = D2GetUniqueID(ptItem);
            if ((uniqueID >= 0) && (uniqueID < (int) SgptDataTables->nbUniqueItems)) {
                UniqueItemsBIN *uniqueItems = SgptDataTables->uniqueItems + uniqueID;
                if (uniqueItems && (uniqueItems->carry1 == 1)) {
                    ItemsBIN *ptItemsBin = D2GetItemsBIN(ptItem->nTxtFileNo);
                    Unit *ptFirstItem = D2InventoryGetFirstItem(getInventory(ptChar));
                    if (ptItemsBin && ptFirstItem)
                        return D2VerifIfNotCarry1(ptItem, ptItemsBin, ptFirstItem);
                }
            }
        }
        return 0;
    }

    __declspec(naked)void caller_carry1Limit_114() {
        __asm{
        PUSH DWORD PTR SS:[ESP+0x08]//page
        PUSH 0//EDI
        PUSH DWORD PTR SS:[ESP+0x0C]
        PUSH ESI//ptChar
        CALL carry1Limit
        TEST EAX, EAX
        JNZ    end_carry1Limit
        JMP D2ItemSetPage
        end_carry1Limit:
        ADD ESP, 0xC
        XOR EAX, EAX
        POP EDI
        POP EBX
        POP ESI
        MOV ESP, EBP
        POP EBP
        RETN 8
        }
    }

    __declspec(naked)void caller_carry1Limit_111() {
        __asm{
        PUSH DWORD PTR SS:[ESP+0x08]//page
        PUSH 0//EDI
        PUSH DWORD PTR SS:[ESP+0x0C]
        PUSH ESI//ptChar
        CALL carry1Limit
        TEST EAX, EAX
        JNZ    end_carry1Limit
        JMP D2ItemSetPage
        end_carry1Limit:
        ADD ESP, 0xC
        XOR EAX, EAX
        POP EDI
        POP EBX
        POP ESI
        POP EBP
        RETN 8
        }
    }

    __declspec(naked)void caller_carry1Limit() {
        __asm{
        PUSH DWORD PTR SS:[ESP+0x08]//page
        PUSH 0//EBP
        PUSH DWORD PTR SS:[ESP+0x0C]
        PUSH DWORD PTR SS:[ESP+0x28]//ptChar
        CALL carry1Limit
        TEST EAX, EAX
        JNZ    end_carry1Limit
        JMP D2ItemSetPage
        end_carry1Limit:
        ADD ESP, 0xC
        POP EDI
        POP ESI
        POP EBP
        XOR EAX, EAX
        POP EBX
        ADD ESP, 0x24
        RETN 8
        }
    }

    __declspec(naked)void caller_carry1LimitSwap_114() {
        __asm{
        PUSH EAX
        PUSH DWORD PTR SS:[ESP+0x20]
        PUSH 0
        PUSH EDI//ptChar
        CALL carry1Limit
        TEST EAX, EAX
        JNZ    end_carry1Limit
        JMP D2ItemGetPage
        end_carry1Limit:
        ADD ESP, 8
        XOR EAX, EAX
        POP EBX
        POP EDI
        POP ESI
        MOV ESP, EBP
        POP EBP
        RETN 8
        }
    }

    __declspec(naked)void caller_carry1LimitSwap_112() {
        __asm{
        PUSH EAX
        PUSH DWORD PTR SS:[ESP+0x1C]
        PUSH 0
        PUSH ESI//ptChar
        CALL carry1Limit
        TEST EAX, EAX
        JNZ    end_carry1Limit
        JMP D2ItemGetPage
        end_carry1Limit:
        ADD ESP, 8
        XOR EAX, EAX
        POP EDI
        POP EBP
        POP ESI
        POP EBX
        POP ECX
        RETN 8
        }
    }

    __declspec(naked)void caller_carry1LimitSwap_111() {
        __asm{
        PUSH EAX
        PUSH EBP
        PUSH 0
        PUSH DWORD PTR SS:[ESP+0x24]//ptChar
        CALL carry1Limit
        TEST EAX, EAX
        JNZ    end_carry1Limit
        JMP D2ItemGetPage
        end_carry1Limit:
        ADD ESP, 8
        XOR EAX, EAX
        POP EDI
        POP EBP
        POP ESI
        POP EBX
        POP ECX
        RETN 8
        }
    }

    __declspec(naked)void caller_carry1LimitSwap() {
        __asm{
        PUSH EAX
        PUSH DWORD PTR SS:[ESP+0x20]
        PUSH 0
        PUSH EBP//ptChar
        CALL carry1Limit
        TEST EAX, EAX
        JNZ    end_carry1Limit
        JMP D2ItemGetPage
        end_carry1Limit:
        ADD ESP, 8
        POP EDI
        POP ESI
        POP EBP
        XOR EAX, EAX
        POP EBX
        ADD ESP, 0x4C
        RETN 8
        }
    }

/*
FCT_ASM ( caller_carry1LimitWhenDrop )
	PUSH EAX
	PUSH 0
	PUSH ESI//ptItem
	PUSH EDI//ptChar
	CALL carry1Limit
	TEST EAX,EAX
	POP EAX
	JE END_carry1LimitWhenDrop
	MOV EDX,0x806
	RETN
END_carry1LimitWhenDrop:
	ADD DWORD PTR SS:[ESP],0x1F
	RETN
}}*/

    __declspec(naked)void caller_carry1LimitWhenDrop_114() {
        __asm{
        PUSH 0
        PUSH 0
        PUSH DWORD PTR SS:[ESP+0x10] //ptItem
        PUSH EBX //ptChar
        CALL carry1Limit
        TEST EAX, EAX
        JNZ    end_carry1Limit
        JMP D2CanPutItemInInv
        end_carry1Limit:
        XOR EAX, EAX
        RETN 0x1C
        }
    }

    __declspec(naked)void caller_carry1LimitWhenDrop_111() {
        __asm{
        PUSH 0
        PUSH 0
        PUSH DWORD PTR SS:[ESP+0x10] //ptItem
        PUSH ESI //ptChar
        CALL carry1Limit
        TEST EAX, EAX
        JNZ    end_carry1Limit
        JMP D2CanPutItemInInv
        end_carry1Limit:
        XOR EAX, EAX
        RETN 0x1C
        }
    }

/*
FCT_ASM ( caller_carry1LimitWhenDrop )
	PUSH 0
	PUSH 0
	PUSH DWORD PTR SS:[ESP+0x10] //ptItem
	PUSH EDI //ptChar
	CALL carry1Limit
	JNZ	end_carry1Limit
	JMP D2CanPutItemInInv
end_carry1Limit:
	XOR EAX,EAX
	RETN 0x1C
}}*/


    __declspec(naked)void caller_carry1LimitWhenDrop() {
        __asm{
        PUSH EAX
        PUSH 0
        PUSH 0
        PUSH ESI//ptItem
        PUSH EDI//ptChar
        CALL carry1Limit
        TEST EAX, EAX
        POP EAX
        JNZ END_carry1LimitWhenDrop
        MOV EDX, 0x806
        RETN
        END_carry1LimitWhenDrop:
        ADD DWORD PTR SS:[ESP], 0x1F
        RETN
        }
    }

    __declspec(naked)void caller_carry1OutOfStash_114() {
        __asm{
        PUSH ESI
        CALL D2ItemGetPage
        CMP AL, 4
        JNZ continue_carry1OutOfStash
        //SUB DWORD PTR SS:[ESP],0xC
        ADD DWORD PTR SS:[ESP], 0x17D
        RETN
        continue_carry1OutOfStash:
        MOV EDI, DWORD PTR SS:[EBP-4]
        TEST EDI, EDI
        RETN
        }
    }

    __declspec(naked)void caller_carry1OutOfStash_111() {
        __asm{
        PUSH EDI
        CALL D2ItemGetPage
        CMP AL, 4
        JNZ continue_carry1OutOfStash
        ADD DWORD PTR SS:[ESP], 0x17C
        RETN
        continue_carry1OutOfStash:
        MOV ESI, DWORD PTR SS:[ESP+0x10]
        TEST ESI, ESI
        RETN
        }
    }

    __declspec(naked)void caller_carry1OutOfStash() {
        __asm{
        PUSH ESI
        CALL D2ItemGetPage
        CMP AL, 4
        JNZ continue_carry1OutOfStash
        ADD DWORD PTR SS:[ESP], 0x1AF
        RETN
        continue_carry1OutOfStash:
        MOV EAX, DWORD PTR SS:[ESP+0x14]
        TEST EAX, EAX
        RETN
        }
    }

    void Install_MultiPageStash() {
        static int isInstalled = false;
        if (isInstalled) return;
        Install_PlayerCustomData();
        Install_InterfaceStash();
        changeToSelectedStash = version_D2Common >= V110 ? changeToSelectedStash_10 : changeToSelectedStash_9;
        if (version_D2Game >= V110) {
            log_msg("Patch D2Game for carry1 unique item. (MultiPageStash)\n");

            // Cannot put 2 items carry1 in inventory
            mem_seek(
                offset_D2Game + (
                    version_D2Game == V114d ? 0x14AC7F : (
                        version_D2Game == V113d ? 0x6B013 : (
                            version_D2Game == V113c ? 0xCF1E3 : (
                                version_D2Game == V112 ? 0x99B03 : (
                                    version_D2Game == V111b ? 0x2FE63 : (
                                        version_D2Game == V111 ? 0x57CA3 : (version_D2Game == V110 ? 0x55050 : (version_D2Game == V109d ? 0x0000 : 0x0000)))))))));
            MEMJ_REF4(D2ItemSetPage, version_D2Game >= V114d ? caller_carry1Limit_114 : version_D2Game >= V111 ? caller_carry1Limit_111 : caller_carry1Limit);
            //6FC8504F   . E8 94670900    CALL <JMP.&D2Common.#10720>
            //01FD7CA2   . E8 6329FBFF    CALL <JMP.&D2Common.#10485>
            //01F9FE62   . E8 47A8FDFF    CALL <JMP.&D2Common.#10608>
            //6FCB9B02   . E8 9709F7FF    CALL <JMP.&D2Common.#10223>
            //6FCEF1E2   . E8 47B7F3FF    CALL <JMP.&D2Common.#10012>
            //6FC8B012   . E8 13F7F9FF    CALL <JMP.&D2Common.#11026>
            //0054AC7E  |. E8 FDD50D00    CALL Game.00628280                       ; \Game.00628280

            // Cannot put 2 items carry1 in inventory by swapping
            mem_seek(
                offset_D2Game + (
                    version_D2Game == V114d ? 0x14B179 : (
                        version_D2Game == V113d ? 0x6BC78 : (
                            version_D2Game == V113c ? 0xD10C8 : (
                                version_D2Game == V112 ? 0x9B6E8 : (
                                    version_D2Game == V111b ? 0x310E8 : (
                                        version_D2Game == V111 ? 0x58968 : (version_D2Game == V110 ? 0x558D9 : (version_D2Game == V109d ? 0x0000 : 0x0000)))))))));
            MEMJ_REF4(D2ItemGetPage, version_D2Game >= V114d ? caller_carry1LimitSwap_114 : version_D2Game >= V112 ? caller_carry1LimitSwap_112 : version_D2Game >= V111 ? caller_carry1LimitSwap_111 : caller_carry1LimitSwap);
            //6FC858D8   . E8 175F0900    CALL <JMP.&D2Common.#10719>
            //01FD8967   . E8 8E1DFBFF    CALL <JMP.&D2Common.#10820>
            //01FA10E7   . E8 9A96FDFF    CALL <JMP.&D2Common.#10505>
            //6FCBB6E7   . E8 CAEDF6FF    CALL <JMP.&D2Common.#10370>
            //6FCF10C7   . E8 F895F3FF    CALL <JMP.&D2Common.#10020>
            //6FC8BC77   . E8 22E9F9FF    CALL <JMP.&D2Common.#10810>
            //0054B178  |. E8 D3D00D00    CALL Game.00628250                       ; \Game.00628250

            if (version_D2Game >= V111) {
                // Cannot put 2 items carry1 in inventory when drop cube
                mem_seek(
                    offset_D2Game + (
                        version_D2Game == V114d ? 0x163A89 : (
                            version_D2Game == V113d ? 0xB7B15 : (
                                version_D2Game == V113c ? 0xD7B75 : (
                                    version_D2Game == V112 ? 0x17AD5 : (
                                        version_D2Game == V111b ? 0x49FD5 : (
                                            version_D2Game == V111 ? 0x3D935 : (version_D2Game == V110 ? 0x0000 : (version_D2Game == V109d ? 0x0000 : 0x0000)))))))));
                MEMJ_REF4(D2CanPutItemInInv, version_D2Game >= V114d ? caller_carry1LimitWhenDrop_114 : caller_carry1LimitWhenDrop_111);
                //01FBD934  |. E8 5BD3FCFF    |CALL <JMP.&D2Common.#10855>
                //01FB9FD4  |. E8 3912FCFF    |CALL <JMP.&D2Common.#10813>
                //6FC37AD4  |. E8 0535FFFF    |CALL <JMP.&D2Common.#10289>
                //6FCF7B74  |. E8 232FF3FF    |CALL <JMP.&D2Common.#10133>
                //6FCD7B14  |. E8 7D32F5FF    |CALL <JMP.&D2Common.#10402>
                //00563A88   . E8 C37E0D00    CALL Game.0063B950                       ; \Game.0063B950
            } else {
                // Cannot put 2 items carry1 in inventory when drop cube
                mem_seek(
                    offset_D2Game + (
                        version_D2Game == V114d ? 0x0000 : (
                            version_D2Game == V113d ? 0x0000 : (
                                version_D2Game == V113c ? 0x0000 : (
                                    version_D2Game == V112 ? 0x0000 : (
                                        version_D2Game == V111b ? 0x0000 : (
                                            version_D2Game == V111 ? 0x0000 : (version_D2Game == V110 ? 0x14341 : (version_D2Game == V109d ? 0x0000 : 0x0000)))))))));
                memt_byte(0xBA, 0xE8);
                MEMT_REF4(0x00000806, caller_carry1LimitWhenDrop);
                //6FC44341  |. BA 06080000    |MOV EDX,806
            }

            // Verif only carry1 out of stash page when pick up an item
            mem_seek(
                offset_D2Game + (
                    version_D2Game == V114d ? 0x15CADD : (
                        version_D2Game == V113d ? 0xB301B : (
                            version_D2Game == V113c ? 0xD211B : (
                                version_D2Game == V112 ? 0x1209B : (
                                    version_D2Game == V111b ? 0x43F0B : (
                                        version_D2Game == V111 ? 0x38E3B : (version_D2Game == V110 ? 0x1299E : (version_D2Game == V109d ? 0x0000 : 0x0000)))))))));
            memt_byte(0x8B, 0xE8);
            MEMT_REF4(version_D2Game >= V114d ? 0xFF85FC7D : version_D2Game >= V111 ? 0x850C2474 : 0x85102444,
                version_D2Game >= V114d ? caller_carry1OutOfStash_114 : version_D2Game >= V111 ? caller_carry1OutOfStash_111 : caller_carry1OutOfStash);
            if (version_D2Game < V114d) memt_byte(version_D2Game >= V111 ? 0xF6 : 0xC0, 0x90);
            //6FC4299E  |. 8B4424 10      |MOV EAX,DWORD PTR SS:[ESP+10]
            //6FC429A2  |. 85C0           |TEST EAX,EAX
            //01FB8E3B  |. 8B7424 0C      |MOV ESI,DWORD PTR SS:[ESP+C]
            //01FB8E3F  |. 85F6           |TEST ESI,ESI
            //01FB3F0B  |. 8B7424 0C      |MOV ESI,DWORD PTR SS:[ESP+C]
            //01FB3F0F  |. 85F6           |TEST ESI,ESI
            //6FC3209B  |. 8B7424 0C      |MOV ESI,DWORD PTR SS:[ESP+C]
            //6FC3209F  |. 85F6           |TEST ESI,ESI
            //6FCF211B  |. 8B7424 0C      |MOV ESI,DWORD PTR SS:[ESP+C]
            //6FCF211F  |. 85F6           |TEST ESI,ESI
            //6FCD301B  |. 8B7424 0C      |MOV ESI,DWORD PTR SS:[ESP+C]
            //6FCD301F  |. 85F6           |TEST ESI,ESI
            //0055CADD  |> 8B7D FC        |MOV EDI,DWORD PTR SS:[EBP-4]
            //0055CAE0  |. 85FF           |TEST EDI,EDI

            log_msg("\n");
        }
        isInstalled = true;
    }
}