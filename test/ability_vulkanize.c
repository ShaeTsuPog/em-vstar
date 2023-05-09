#include "global.h"
#include "test_battle.h"

#define TEST_MAX_HP (500)

SINGLE_BATTLE_TEST("Vulkanize causes Fire type attacks to heal the user")
{
    s16 damage;
    s16 healed;

    GIVEN {
        PLAYER(SPECIES_TYPHLOSION) { Item(ITEM_TYPHLOSIONITE); HP(1); MaxHP(TEST_MAX_HP); };
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_EARTH_POWER, megaEvolve: TRUE); }
    } SCENE {
        MESSAGE("Typhlosion's Typhlosionite is reacting to 1's Mega Ring!");
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_MEGA_EVOLUTION, player);
        MESSAGE("Typhlosion used Earth Power!");
        HP_BAR(opponent, captureDamage: &damage);
        HP_BAR(player, captureDamage: &healed);
    } THEN {
        EXPECT_MUL_EQ(damage, Q_4_12(-0.5), healed);
    }
}

SINGLE_BATTLE_TEST("Vulkanize makes all attacks Fire type")
{
    GIVEN {
        PLAYER(SPECIES_TYPHLOSION) { Item(ITEM_TYPHLOSIONITE); };
        OPPONENT(SPECIES_QUAGSIRE);
    } WHEN {
        TURN { MOVE(player, MOVE_EARTH_POWER, megaEvolve: TRUE); }
    } SCENE {
        MESSAGE("Typhlosion's Typhlosionite is reacting to 1's Mega Ring!");
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_MEGA_EVOLUTION, player);
        MESSAGE("Typhlosion used Earth Power!");
        HP_BAR(opponent);
        MESSAGE("It's not very effective…");
    } THEN {
        EXPECT_EQ(player->species, SPECIES_TYPHLOSION_MEGA);
    }
}
