#include "global.h"
#include "test_battle.h"

SINGLE_BATTLE_TEST("Mold Breaker ignores Levitate")
{
    GIVEN {
        ASSUME(gBattleMoves[MOVE_EARTHQUAKE].type == TYPE_GROUND);
        PLAYER(SPECIES_PINSIR) {Ability(ABILITY_MOLD_BREAKER); };
        OPPONENT(SPECIES_FLYGON) {Ability(ABILITY_LEVITATE); };
    } WHEN {
        TURN { MOVE(player, MOVE_EARTHQUAKE); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_MOLD_BREAKER);
        MESSAGE("Pinsir breaks the mold!");
        MESSAGE("Pinsir used Earthquake!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_EARTHQUAKE, player);
        HP_BAR(opponent);
    }
}

SINGLE_BATTLE_TEST("Mold Breaker ignores Water Absorb, Dry Skin, and Storm Drain")
{
    GIVEN {
        ASSUME(gBattleMoves[MOVE_BUBBLE].type == TYPE_WATER);
        PLAYER(SPECIES_PINSIR) {Ability(ABILITY_MOLD_BREAKER);};
        OPPONENT(SPECIES_POLIWHIRL) {Ability(ABILITY_WATER_ABSORB);};
    } WHEN {
        TURN { MOVE(player, MOVE_BUBBLE); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_MOLD_BREAKER);
        HP_BAR(opponent);
        NONE_OF {
            ABILITY_POPUP(opponent);
            MESSAGE("Poliwhirl restored HP using its Water Absorb!");
        }
    }
}
