#include "global.h"
#include "test_battle.h"

SINGLE_BATTLE_TEST("Poison Touch poisons on contact moves")
{
    GIVEN {
        PLAYER(SPECIES_MUK) { Ability(ABILITY_POISON_TOUCH); };
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_JAW_LOCK); }
    } SCENE {
        MESSAGE("Muk used Jaw Lock!");
        HP_BAR(opponent);
        STATUS_ICON(opponent, poison: TRUE);
    }
}
