#include "global.h"
#include "test_battle.h"

SINGLE_BATTLE_TEST("Esper gives priority to Psychic type moves")
{
    GIVEN {
        PLAYER(SPECIES_ELGYEM) { Ability(ABILITY_ESPER); Speed(100); };
        OPPONENT(SPECIES_WOBBUFFET) { Speed(105); };
    } WHEN {
        TURN { MOVE(opponent, MOVE_CELEBRATE); MOVE(player, MOVE_PSYCHIC); }
    } SCENE {
        MESSAGE("Elgyem used Psychic!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_PSYCHIC, player);
        HP_BAR(opponent);
        MESSAGE("Foe Wobbuffet used Celebrate!");
    }
}