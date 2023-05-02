#include "global.h"
#include "test_battle.h"

#define TEST_MAX_HP (200)

SINGLE_BATTLE_TEST("Solar Power increases special attack by 50% in sun", s16 damage)
{
    u32 ability;
    PARAMETRIZE { ability = ABILITY_BLAZE; }
    PARAMETRIZE { ability = ABILITY_SOLAR_POWER; }
    GIVEN {
        ASSUME(gBattleMoves[MOVE_DRAGON_BREATH].split == SPLIT_SPECIAL);
        PLAYER(SPECIES_CHARIZARD) { Ability(ability); HP(100); MaxHP(TEST_MAX_HP); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponent, MOVE_SUNNY_DAY); MOVE(player, MOVE_DRAGON_BREATH); }
    } SCENE {
        if (ability == ABILITY_BLAZE)
            HP_BAR(opponent, captureDamage: &results[0].damage);
        else if (ability == ABILITY_SOLAR_POWER)
        {
            HP_BAR(opponent, captureDamage: &results[1].damage);
            MESSAGE("The sunlight is strong.");
            ABILITY_POPUP(player, ABILITY_SOLAR_POWER);
            HP_BAR(player, damage: (TEST_MAX_HP / 8));
            MESSAGE("The Charizard's Solar Power takes its toll!");
        }
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(1.5), results[1].damage);
    }
}
