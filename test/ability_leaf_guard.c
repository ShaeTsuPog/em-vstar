#include "global.h"
#include "test_battle.h"

SINGLE_BATTLE_TEST("Leaf Guard prevents non-volatile status conditions in sun")
{
    GIVEN {
        ASSUME(gBattleMoves[MOVE_WILL_O_WISP].effect == EFFECT_WILL_O_WISP);
        PLAYER(SPECIES_LEAFEON) { Ability(ABILITY_LEAF_GUARD); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_SUNNY_DAY); MOVE(opponent, MOVE_WILL_O_WISP); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_LEAF_GUARD);
        NOT ANIMATION(ANIM_TYPE_MOVE, MOVE_WILL_O_WISP, opponent);
        MESSAGE("It doesn't affect Leafeon…");
        NOT STATUS_ICON(player, burn: TRUE);
    }
}

SINGLE_BATTLE_TEST("Leaf Guard prevents non-volatile status conditions from items")
{
    GIVEN {
        ASSUME(gItems[ITEM_FLAME_ORB].holdEffect == HOLD_EFFECT_FLAME_ORB);
        PLAYER(SPECIES_LEAFEON) {Ability(ABILITY_LEAF_GUARD); Item(ITEM_FLAME_ORB); };
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_SUNNY_DAY); }
    } SCENE {
        NOT MESSAGE("Leafeon was burned!");
        NOT STATUS_ICON(player, burn: TRUE);
    }
}

SINGLE_BATTLE_TEST("Leaf Guard prevents Rest during sun")
{
    GIVEN {
        ASSUME(gBattleMoves[MOVE_REST].effect == EFFECT_REST);
        PLAYER(SPECIES_LEAFEON) { Ability(ABILITY_LEAF_GUARD); HP(100); MaxHP(200); };
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponent, MOVE_SUNNY_DAY); MOVE(player, MOVE_REST); }
    } SCENE {
        NOT MESSAGE("Leafeon went to sleep!");
        NOT STATUS_ICON(player, sleep: TRUE);
        NOT MESSAGE("Leafeon regained health!");
        NONE_OF {HP_BAR(player);}
    }
}
