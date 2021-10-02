/*=================================================================
	File created by Yohann NICOLAS.

	Unassign Stats Point for futher re-assignment.

=================================================================*/
#pragma once

#include "common.h"

namespace PlugY {
    extern bool active_StatsPoints;
    extern DWORD keyUsedForUnassignStatPoint;
    extern bool active_StatsShiftClickLimit;
    extern DWORD limitValueToShiftClick;

    void UnassignStrPoint(Commons::Unit *ptChar);

    void UnassignStrPoints(Commons::Unit *ptChar);

    void UnassignDexPoint(Commons::Unit *ptChar);

    void UnassignDexPoints(Commons::Unit *ptChar);

    void UnassignVitPoint(Commons::Unit *ptChar);

    void UnassignVitPoints(Commons::Unit *ptChar);

    void UnassignEnePoint(Commons::Unit *ptChar);

    void UnassignEnePoints(Commons::Unit *ptChar);

    void Install_StatsLimitShiftClick();

    void Install_StatsPoints();

}