#include "global.h"
#include "test_battle.h"

SINGLE_BATTLE_TEST("Sand Force prevents damage from sandstorm")
{
    GIVEN {
        PLAYER(SPECIES_SHELLOS) {Ability(ABILITY_SAND_FORCE);};
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN {MOVE(opponent, MOVE_SANDSTORM); }
    } SCENE {
        NONE_OF {HP_BAR(player);}
    }
}

SINGLE_BATTLE_TEST("Sand Force boosts boost Rock, Ground, and Steel type moves by 30% in sandstorm", s16 damage)
{
    u32 ability;
    PARAMETRIZE { ability = ABILITY_ARENA_TRAP; }
    PARAMETRIZE { ability = ABILITY_SAND_FORCE; }

    GIVEN {
        ASSUME(gBattleMoves[MOVE_ROCK_SLIDE].type == TYPE_ROCK);
        PLAYER(SPECIES_DUGTRIO) { Ability(ability); };
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponent, MOVE_SANDSTORM); MOVE(player, MOVE_ROCK_SLIDE); }
        TURN { MOVE(player, MOVE_EARTHQUAKE); }
        TURN { MOVE(player, MOVE_IRON_HEAD); }
    } SCENE {
        if (ability == ABILITY_ARENA_TRAP)
            HP_BAR(opponent, captureDamage: &results[1].damage);
        else if (ability == ABILITY_SAND_FORCE)
            HP_BAR(opponent, captureDamage: &results[2].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[1].damage, Q_4_12(1.3), results[2].damage);
    }
}
