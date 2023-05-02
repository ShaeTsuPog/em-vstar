#include "global.h"
#include "test_battle.h"

SINGLE_BATTLE_TEST("Whiteout increases Attack and Special Attack by 50% in hail", s16 damage)
{
    u32 ability;
    KNOWN_FAILING;
    PARAMETRIZE { ability = ABILITY_WHITEOUT; }
    PARAMETRIZE { ability = ABILITY_SOUNDPROOF; }

    GIVEN {
        ASSUME(gBattleMoves[MOVE_WOOD_HAMMER].split == SPLIT_PHYSICAL);
        PLAYER(SPECIES_ABOMASNOW) {Ability(ability);};
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponent, MOVE_HAIL); MOVE(player, MOVE_WOOD_HAMMER);}
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(1.5), results[1].damage);
    }
}
