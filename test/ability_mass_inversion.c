#include "global.h"
#include "test_battle.h"

SINGLE_BATTLE_TEST("Mass Inversion activates Trick Room on switch-in")
{
    KNOWN_FAILING;
    GIVEN {
        PLAYER(SPECIES_BRONZONG) {Ability(ABILITY_MASS_INVERSION); Speed(20);};
        OPPONENT(SPECIES_WOBBUFFET) {Speed(50);};
    } WHEN {
        TURN {}
    } SCENE {
        ABILITY_POPUP(player, ABILITY_MASS_INVERSION);
        MESSAGE("Bronzong twisted the dimensions!");
        MESSAGE("Bronzong used Celebrate!");
        MESSAGE("Wobbuffet used Celebrate!");
    }
}
