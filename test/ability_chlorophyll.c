#include "global.h"
#include "test_battle.h"

SINGLE_BATTLE_TEST("Chlorophyll doubles speed in sun")
{
    GIVEN {
        PLAYER(SPECIES_VENUSAUR) {Ability(ABILITY_CHLOROPHYLL); Speed(80);};
        OPPONENT(SPECIES_WOBBUFFET) {Speed(100);};
    } WHEN {
        TURN {MOVE(opponent, MOVE_SUNNY_DAY); MOVE(player, MOVE_CELEBRATE);}
        TURN {}
    } SCENE {
        MESSAGE("Foe Wobbuffet used Sunny Day!");
        MESSAGE("Venusaur used Celebrate!");
        MESSAGE("Venusaur used Celebrate!");
        MESSAGE("Foe Wobbuffet used Celebrate!");
    }
}
