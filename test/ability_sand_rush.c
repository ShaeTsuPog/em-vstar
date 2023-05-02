#include "global.h"
#include "test_battle.h"

SINGLE_BATTLE_TEST("Sand Rush doubles speed in hail")
{
    GIVEN {
        PLAYER(SPECIES_SANDSLASH) {Ability(ABILITY_SAND_RUSH); Speed(80);};
        OPPONENT(SPECIES_WOBBUFFET) {Speed(100);};
    } WHEN {
        TURN {MOVE(opponent, MOVE_SANDSTORM); MOVE(player, MOVE_CELEBRATE);}
        TURN {}
    } SCENE {
        MESSAGE("Foe Wobbuffet used Sandstorm!");
        MESSAGE("Sandslash used Celebrate!");
        MESSAGE("Sandslash used Celebrate!");
        MESSAGE("Foe Wobbuffet used Celebrate!");
    }
}
