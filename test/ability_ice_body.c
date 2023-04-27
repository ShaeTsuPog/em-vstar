#include "global.h"
#include "test_battle.h"

#define TEST_MAX_HP (100)

SINGLE_BATTLE_TEST("Ice Body heals 25% when hit by ice type moves")
{
    GIVEN {
        ASSUME(gBattleMoves[MOVE_ICE_BEAM].type == TYPE_ICE);
        PLAYER(SPECIES_GLALIE) { Ability(ABILITY_ICE_BODY); HP(1); MaxHP(TEST_MAX_HP); };
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponent, MOVE_ICE_BEAM); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_ICE_BODY);
        HP_BAR(player, hp: TEST_MAX_HP / 4 + 1);
        MESSAGE("Glalie restored HP using its Ice Body!");
    }
}

SINGLE_BATTLE_TEST("Ice Body does not activate if protected")
{
    GIVEN {
        ASSUME(gBattleMoves[MOVE_ICE_BEAM].type == TYPE_ICE);
        PLAYER(SPECIES_GLALIE) { Ability(ABILITY_ICE_BODY); HP(1); MaxHP(TEST_MAX_HP); };
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_PROTECT); MOVE(opponent, MOVE_ICE_BEAM); }
    } SCENE {
        NONE_OF { ABILITY_POPUP(player, ABILITY_ICE_BODY); HP_BAR(player); MESSAGE("Glalie restored HP using its Ice Body!"); }
    }
}

SINGLE_BATTLE_TEST("Ice Body is only trigged once on multi strike moves")
{
    GIVEN {
        ASSUME(gBattleMoves[MOVE_ICICLE_SPEAR].type == TYPE_ICE);
        ASSUME(gBattleMoves[MOVE_ICICLE_SPEAR].effect == EFFECT_MULTI_HIT);
        PLAYER(SPECIES_GLALIE) { Ability(ABILITY_ICE_BODY); HP(1); MaxHP(TEST_MAX_HP); };
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponent, MOVE_ICICLE_SPEAR); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_ICE_BODY);
        HP_BAR(player, hp: TEST_MAX_HP / 4 + 1);
        MESSAGE("Glalie restored HP using its Ice Body!");
    }
}

SINGLE_BATTLE_TEST("Ice Body prevents Items from activating")
{
    u32 item;
    PARAMETRIZE { item = ITEM_SNOWBALL; }
    GIVEN {
        ASSUME(gBattleMoves[MOVE_ICE_BEAM].type == TYPE_ICE);
        PLAYER(SPECIES_GLALIE) { Ability(ABILITY_ICE_BODY); HP(1); MaxHP(TEST_MAX_HP); Item(item); };
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponent, MOVE_ICE_BEAM); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_ICE_BODY);
        HP_BAR(player, hp: TEST_MAX_HP / 4 + 1);
        MESSAGE("Glalie restored HP using its Ice Body!");
        NONE_OF {
            ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_HELD_ITEM_EFFECT, player);
            ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, player);
        }
    }
}

SINGLE_BATTLE_TEST("Ice Body recovers 1/16th of Max HP in Hail.")
{
    GIVEN {
        PLAYER(SPECIES_GLALIE) { Ability(ABILITY_ICE_BODY); HP(1); MaxHP(TEST_MAX_HP); };
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponent, MOVE_HAIL); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_ICE_BODY);
        MESSAGE("Glalie's Ice Body healed it a little bit!");
        HP_BAR(player, hp: TEST_MAX_HP / 16 + 1);
    }
}
