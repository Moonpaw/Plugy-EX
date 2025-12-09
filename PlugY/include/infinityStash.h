/*=================================================================
	File created by Yohann NICOLAS.

	infinity Stash gestion

=================================================================*/
#pragma once

#include "common.h"
#include "playerCustomData.h"

namespace PlugY {
    extern DWORD maxSelfPages;
    extern DWORD maxSharedPages;
    extern DWORD nbPagesPerIndex;
    extern DWORD nbPagesPerIndex2;
    extern bool active_multiPageStash;
    extern int active_SharedStashInMultiPlayer;
    extern bool active_sharedStash;
    extern bool active_sharedGold;
    extern bool separateHardSoftStash;
    extern char *sharedStashFilename;
    extern bool displaySharedSetItemNameInGreen;
    extern int posXPreviousBtn;
    extern int posYPreviousBtn;
    extern int posWPreviousBtn;
    extern int posHPreviousBtn;
    extern int posXNextBtn;
    extern int posYNextBtn;
    extern int posWNextBtn;
    extern int posHNextBtn;
    extern int posXSharedBtn;
    extern int posYSharedBtn;
    extern int posWSharedBtn;
    extern int posHSharedBtn;
    extern int posXPreviousIndexBtn;
    extern int posYPreviousIndexBtn;
    extern int posWPreviousIndexBtn;
    extern int posHPreviousIndexBtn;
    extern int posXNextIndexBtn;
    extern int posYNextIndexBtn;
    extern int posWNextIndexBtn;
    extern int posHNextIndexBtn;
    extern int posXPutGoldBtn;
    extern int posYPutGoldBtn;
    extern int posWPutGoldBtn;
    extern int posHPutGoldBtn;
    extern int posXTakeGoldBtn;
    extern int posYTakeGoldBtn;
    extern int posWTakeGoldBtn;
    extern int posHTakeGoldBtn;
    extern int posXStashNameField;
    extern int posYStashNameField;
    extern int posWStashNameField;
    extern int posHStashNameField;
    extern int posXStashGoldField;
    extern int posYStashGoldField;
    extern int posWStashGoldField;
    extern int posHStashGoldField;
    extern bool autoRenameStashPage;
    extern DWORD PersonalNormalPageColor;
    extern DWORD PersonalIndexPageColor;
    extern DWORD PersonalMainIndexPageColor;
    extern DWORD SharedNormalPageColor;
    extern DWORD SharedIndexPageColor;
    extern DWORD SharedMainIndexPageColor;
    void toggleToSharedStash(Commons::Unit *ptChar);
    void toggleToSelfStash(Commons::Unit *ptChar);
    void setCurrentStashIndex(Commons::Unit *ptChar, int index);
    void selectPreviousStash(Commons::Unit *ptChar);
    void selectNextStash(Commons::Unit *ptChar);
    void selectPreviousIndexStash(Commons::Unit *ptChar);
    void selectNextIndexStash(Commons::Unit *ptChar);
    void selectPrevious2Stash(Commons::Unit *ptChar);
    void selectNext2Stash(Commons::Unit *ptChar);
    void selectPreviousIndex2Stash(Commons::Unit *ptChar);
    void selectNextIndex2Stash(Commons::Unit *ptChar);
    void swapStash(Commons::Unit *ptChar, DWORD page, bool toggle);
    void renameCurrentStash(Commons::Unit *ptChar, char *name);
    void insertStash(Commons::Unit *ptChar);
    bool deleteStash(Commons::Unit *ptChar, bool isClient);
    void updateSelectedStashClient(Commons::Unit *ptChar);
    void selectStash(Commons::Unit *ptChar, Stash *newStash, bool forceUpdate = false);
    void setSelectedStashClient(DWORD stashId, DWORD stashFlags, DWORD flags, bool bOnlyItems);
    Stash *addStash(Commons::Unit *ptChar, bool isShared, bool autoSetIndex, Stash *ptStash = NULL);
    DWORD loadStashList(Commons::Unit *ptChar, BYTE *data, DWORD maxSize, DWORD *curSize, bool isShared);
    void saveStashList(Commons::Unit *ptChar, Stash *ptStash, BYTE **data, DWORD *maxSize, DWORD *curSize);
    void getCurrentStashName(WCHAR *buffer, DWORD maxSize, Unit *ptChar);
    const WCHAR * getDefaultStashName(Commons::Unit *ptChar);
    void Install_MultiPageStash();
}
