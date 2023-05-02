#include "global.h"
#include "test_battle.h"

SINGLE_BATTLE_TEST("Slush Rush doubles speed in hail")
{
    GIVEN {
        PLAYER(SPECIES_SANDSLASH_ALOLAN) {Ability(ABILITY_SLUSH_RUSH); Speed(80);};
        OPPONENT(SPECIES_WOBBUFFET) {Speed(100);};
    } WHEN {
        TURN {MOVE(opponent, MOVE_HAIL); MOVE(player, MOVE_CELEBRATE);}
        TURN {}
    } SCENE {
        MESSAGE("Foe Wobbuffet used Hail!");
        MESSAGE("Sandslash used Celebrate!");
        MESSAGE("Sandslash used Celebrate!");
        MESSAGE("Foe Wobbuffet used Celebrate!");
    }
}
