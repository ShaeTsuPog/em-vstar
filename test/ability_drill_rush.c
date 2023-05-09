#include "global.h"
#include "test_battle.h"

SINGLE_BATTLE_TEST("Drill Rush gives priority to Drill moves")
{
    GIVEN {
        PLAYER(SPECIES_RHYPERIOR) { Item(ITEM_RHYPERIORITE); Speed(40); };
        OPPONENT(SPECIES_WOBBUFFET) { Speed(80); };
    } WHEN {
        TURN { MOVE(opponent, MOVE_CELEBRATE); MOVE(player, MOVE_DRILL_RUN, megaEvolve: TRUE); }
    } SCENE {
        MESSAGE("Rhyperior's Rhyperiorite is reacting to 1's Mega Ring!");
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_MEGA_EVOLUTION, player);
        MESSAGE("Rhyperior used Drill Run!");
        HP_BAR(opponent);
        MESSAGE("Foe Wobbuffet used Celebrate!");
    }
}