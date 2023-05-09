#include "global.h"
#include "test_battle.h"

SINGLE_BATTLE_TEST("Grapple Jaw causes biting moves to paralyze")
{
    GIVEN {
        PLAYER(SPECIES_FERALIGATR) { Item(ITEM_FERALIGATRITE); };
        OPPONENT(SPECIES_WOBBUFFET) { HP(999); Defense(999); };
    } WHEN {
        TURN { MOVE(player, MOVE_JAW_LOCK, megaEvolve: TRUE); }
    } SCENE {
        MESSAGE("Feraligatr's Feraligatrite is reacting to 1's Mega Ring!");
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_MEGA_EVOLUTION, player);
        MESSAGE("Feraligatr used Jaw Lock!");
        HP_BAR(opponent);
        STATUS_ICON(opponent, paralysis: TRUE);
    } THEN {
        EXPECT_EQ(player->species, SPECIES_FERALIGATR_MEGA);
    }
}
