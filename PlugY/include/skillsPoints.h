/*=================================================================
	File created by Yohann NICOLAS.

	Unassign Skill Point for futher re-assignment.

=================================================================*/
#pragma once

#include "common.h"

namespace PlugY {
    extern bool active_SkillsPoints;
    extern bool unassignSkillsPointsOneForOne;
    extern int posXUnassignSkillBtn, posYUnassignSkillBtn;

    void UnassignAllSkillsPoints(Commons::Unit *ptChar);

    void client_UnassignAllSkillsPoints();

    void Install_SkillsPoints();

}