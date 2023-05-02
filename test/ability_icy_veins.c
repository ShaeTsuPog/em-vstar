#include "global.h"
#include "test_battle.h"

SINGLE_BATTLE_TEST("Icy Veins boosts Water type moves in hail", s16 damage)
{
    u32 ability;
    KNOWN_FAILING;
    PARAMETRIZE { ability = ABILITY_THICK_FAT; }
    PARAMETRIZE { ability = ABILITY_ICY_VEINS; }

    GIVEN {
        ASSUME(gBattleMoves[MOVE_SURF].type == TYPE_WATER);
        PLAYER(SPECIES_DEWGONG) {Ability(ability);};
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponent, MOVE_HAIL); MOVE(player, MOVE_SURF); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(1.3), results[1].damage);
    }
}

SINGLE_BATTLE_TEST("Icy Veins boosts Ice type moves in hail", s16 damage)
{
    u32 ability;
    KNOWN_FAILING;
    PARAMETRIZE { ability = ABILITY_THICK_FAT; }
    PARAMETRIZE { ability = ABILITY_ICY_VEINS; }

    GIVEN {
        ASSUME(gBattleMoves[MOVE_ICE_BEAM].type == TYPE_ICE);
        PLAYER(SPECIES_DEWGONG) {Ability(ability);};
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponent, MOVE_HAIL); MOVE(player, MOVE_ICE_BEAM); }
    } SCENE {
            HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(1.3), results[1].damage);
    }
}
