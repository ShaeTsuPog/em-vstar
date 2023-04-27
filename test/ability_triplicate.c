#include "global.h"
#include "test_battle.h"

SINGLE_BATTLE_TEST("Triplicate makes same type attacks hit 3 times")
{
    GIVEN {
        ASSUME(gBattleMoves[MOVE_PECK].type == TYPE_FLYING);
        PLAYER(SPECIES_DODRIO) {Ability(ABILITY_TRIPLICATE);};
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN {MOVE(player, MOVE_PECK);}
    } SCENE {
        MESSAGE("Dodrio used Peck!");
        MESSAGE("Hit 3 time(s)!");
    }
}

SINGLE_BATTLE_TEST("Triplicate only causes recoil once")
{
    GIVEN {
        ASSUME(gBattleMoves[MOVE_BRAVE_BIRD].type == TYPE_FLYING);
        PLAYER(SPECIES_DODRIO) {Ability(ABILITY_TRIPLICATE);};
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN {MOVE(player, MOVE_BRAVE_BIRD);}
    } SCENE {
        MESSAGE("Dodrio used Brave Bird!");
        MESSAGE("Hit 3 time(s)!");
        MESSAGE("Dodrio is hit with recoil!");
    }
}
