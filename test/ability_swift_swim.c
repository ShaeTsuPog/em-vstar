#include "global.h"
#include "test_battle.h"

SINGLE_BATTLE_TEST("Swift Swim doubles speed in rain")
{
    GIVEN {
        PLAYER(SPECIES_OMASTAR) {Ability(ABILITY_SWIFT_SWIM); Speed(80);};
        OPPONENT(SPECIES_WOBBUFFET) {Speed(100);};
    } WHEN {
        TURN {MOVE(opponent, MOVE_RAIN_DANCE); MOVE(player, MOVE_CELEBRATE);}
        TURN {}
    } SCENE {
        MESSAGE("Foe Wobbuffet used Rain Dance!");
        MESSAGE("Omastar used Celebrate!");
        MESSAGE("Omastar used Celebrate!");
        MESSAGE("Foe Wobbuffet used Celebrate!");
    }
}
