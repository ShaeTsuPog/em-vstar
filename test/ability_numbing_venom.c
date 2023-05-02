#include "global.h"
#include "test_battle.h"

SINGLE_BATTLE_TEST("Numbing Venom replaces chance to poison with chance to paralyze")
{
    GIVEN {
        ASSUME(gBattleMoves[MOVE_POISON_TAIL].effect == EFFECT_POISON_HIT);
        PLAYER(SPECIES_ARBOK) {Ability(ABILITY_NUMBING_VENOM);};
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN {MOVE(player, MOVE_POISON_TAIL);}
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_POISON_TAIL);
        ANIMATION(ANIM_TYPE_STATUS, B_ANIM_STATUS_PRZ, opponent);
        MESSAGE("Foe Wobbuffet is paralyzed! It may be unable to move!");
        STATUS_ICON(opponent, paralysis: TRUE);
    }
}

SINGLE_BATTLE_TEST("Numbing Venom can paralyze Electric types")
{
    GIVEN {
        ASSUME(gBattleMoves[MOVE_POISON_TAIL].effect == EFFECT_POISON_HIT);
        PLAYER(SPECIES_ARBOK) {Ability(ABILITY_NUMBING_VENOM);};
        OPPONENT(SPECIES_JOLTEON);
    } WHEN {
        TURN {MOVE(player, MOVE_POISON_TAIL);}
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_POISON_TAIL);
        ANIMATION(ANIM_TYPE_STATUS, B_ANIM_STATUS_PRZ, opponent);
        MESSAGE("Foe Jolteon is paralyzed! It may be unable to move!");
        STATUS_ICON(opponent, paralysis: TRUE);
    }
}

SINGLE_BATTLE_TEST("Numbing Venom does not paralyze in Misty Terrain")
{
    GIVEN {
        ASSUME(gBattleMoves[MOVE_POISON_TAIL].effect == EFFECT_POISON_HIT);
        PLAYER(SPECIES_ARBOK) {Ability(ABILITY_NUMBING_VENOM);};
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN {MOVE(opponent, MOVE_MISTY_TERRAIN); MOVE(player, MOVE_POISON_TAIL);}
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_POISON_TAIL);
        NONE_OF {
            ANIMATION(ANIM_TYPE_STATUS, B_ANIM_STATUS_PRZ, opponent);
            MESSAGE("Foe Wobbuffet is paralyzed! It may be unable to move!");
            STATUS_ICON(opponent, paralysis: TRUE);
        }
    }
}

SINGLE_BATTLE_TEST("Numbing Venom does not cause Toxic to paralyze")
{
    GIVEN {
        ASSUME(gBattleMoves[MOVE_TOXIC].effect == EFFECT_TOXIC);
        PLAYER(SPECIES_ARBOK) {Ability(ABILITY_NUMBING_VENOM);};
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN {MOVE(player, MOVE_TOXIC);}
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_TOXIC);
        ANIMATION(ANIM_TYPE_STATUS, B_ANIM_STATUS_PSN, opponent);
        MESSAGE("Foe Wobbuffet is badly poisoned!");
        STATUS_ICON(opponent, badPoison: TRUE);
    }
}
