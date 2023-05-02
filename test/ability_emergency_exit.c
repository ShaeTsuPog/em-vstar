#include "global.h"
#include "test_battle.h"

#define TEST_MAX_HP (200)

SINGLE_BATTLE_TEST("Emergency Exit creates substitute and baton passes")
{
    GIVEN {
        PLAYER(SPECIES_GOLISOPOD) {Ability(ABILITY_EMERGENCY_EXIT); HP(110); MaxHP(TEST_MAX_HP);};
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN {MOVE(opponent, MOVE_SHADOW_BALL);}
    } SCENE {
        ABILITY_POPUP(player, ABILITY_EMERGENCY_EXIT);
        SWITCH(player, 2);
        MESSAGE("");
    }
}
