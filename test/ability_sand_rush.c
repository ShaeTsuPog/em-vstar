#include "global.h"
#include "test_battle.h"

SINGLE_BATTLE_TEST("Sand Rush prevents damage from sandstorm")
{
    GIVEN {
        PLAYER(SPECIES_HERDIER) {Ability(ABILITY_SAND_RUSH);};
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN {MOVE(opponent, MOVE_SANDSTORM);}
    } SCENE {
        NONE_OF {HP_BAR(player);}
    }
}

SINGLE_BATTLE_TEST("Sand Rush doubles speed in sandstorm")
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
