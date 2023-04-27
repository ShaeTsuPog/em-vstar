#include "global.h"
#include "test_battle.h"

SINGLE_BATTLE_TEST("Hive Tactics boosts Evasion if at a type disadvantage")
{
    GIVEN {
        ASSUME(gBattleMoves[MOVE_EMBER].type == TYPE_FIRE);
        PLAYER(SPECIES_BEEDRILL) {Ability(ABILITY_HIVE_TACTICS);};
        OPPONENT(SPECIES_WOBBUFFET) {Moves(MOVE_EMBER, MOVE_CELEBRATE);};
    } WHEN {
        TURN {MOVE(opponent, MOVE_CELEBRATE); MOVE(player, MOVE_CELEBRATE);}
        TURN {MOVE(opponent, MOVE_CELEBRATE); MOVE(player, MOVE_CELEBRATE);}
    } SCENE {
        MESSAGE("Foe Wobbuffet used Celebrate!");
        MESSAGE("Beedrill used Celebrate!");
        ABILITY_POPUP(player, ABILITY_HIVE_TACTICS);
        MESSAGE("Beedrill's Hive Tactics raised its Evasion!");
    }
}

SINGLE_BATTLE_TEST("Hive Tactics does not activate if the opponenet does not have a super-effective move")
{
    GIVEN {
        ASSUME(gBattleMoves[MOVE_POUND].type == TYPE_NORMAL);
        PLAYER(SPECIES_BEEDRILL) {Ability(ABILITY_HIVE_TACTICS);};
        OPPONENT(SPECIES_WOBBUFFET) {Moves(MOVE_POUND, MOVE_CELEBRATE);};
    } WHEN {
        TURN {MOVE(opponent, MOVE_CELEBRATE); MOVE(player, MOVE_CELEBRATE);}
        TURN {MOVE(opponent, MOVE_CELEBRATE); MOVE(player, MOVE_CELEBRATE);}
    } SCENE {
        NONE_OF {ABILITY_POPUP(player, ABILITY_HIVE_TACTICS); MESSAGE("Beedrill's Hive Tactics raised its Evasion!");};
    }
}
