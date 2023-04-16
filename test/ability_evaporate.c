#include "global.h"
#include "test_battle.h"

SINGLE_BATTLE_TEST("Evaporate nullifies water type moves")
{
    u32 ability;
    PARAMETRIZE { ability = ABILITY_EVAPORATE; }
    GIVEN {
        PLAYER(SPECIES_MAGCARGO) { Ability(ability); };
        OPPONENT(SPECIES_SWAMPERT);
    } WHEN {
        TURN { MOVE(opponent, MOVE_SURF); }
    } SCENE {
        /*if (ability == ABILITY_EVAPORATE)
        {
            ABILITY_POPUP(player, ABILITY_EVAPORATE);
        }*/
        ABILITY_POPUP(player, ABILITY_EVAPORATE);
        NONE_OF { HP_BAR(player); }
    }
}