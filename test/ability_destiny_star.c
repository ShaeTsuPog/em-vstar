#include "global.h"
#include "test_battle.h"

ASSUMPTIONS {
    ASSUME(gBattleMoves[MOVE_TACKLE].split == SPLIT_PHYSICAL);
}

SINGLE_BATTLE_TEST("Destiny Star raises Attack when Intimidated", s16 damage)
{
    u32 ability;
    PARAMETRIZE { ability = ABILITY_DESTINY_STAR; }
    PARAMETRIZE { ability = ABILITY_VICTORY_STAR; }

    GIVEN {
        PLAYER(SPECIES_VICTINI) {Ability(ability);};
        OPPONENT(SPECIES_ARCANINE) {Ability(ABILITY_INTIMIDATE);};
    } WHEN {
        TURN {MOVE(player, MOVE_TACKLE);}
    } SCENE {
        ABILITY_POPUP(opponent, ABILITY_INTIMIDATE);
        if (ability == ABILITY_DESTINY_STAR) {
            ABILITY_POPUP(player, ABILITY_DESTINY_STAR);
            ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, player);
            MESSAGE("Victini's Attack rose!");
        }
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[1].damage, Q_4_12(2.125), results[0].damage);
    }
}

SINGLE_BATTLE_TEST("Destiny Star raises stats after using a move which would normally lower them: Overheat", s16 damageBefore, s16 damageAfter)
{
    u32 ability;
    PARAMETRIZE { ability = ABILITY_DESTINY_STAR; }
    PARAMETRIZE { ability = ABILITY_VICTORY_STAR; }

    GIVEN {
        ASSUME(gBattleMoves[MOVE_OVERHEAT].effect == EFFECT_OVERHEAT);
        ASSUME(gBattleMoves[MOVE_OVERHEAT].split == SPLIT_SPECIAL);
        PLAYER(SPECIES_VICTINI) {Ability(ability);};
        OPPONENT(SPECIES_WOBBUFFET) {HP(999);};
    } WHEN {
        TURN { MOVE(player, MOVE_OVERHEAT); }
        TURN { MOVE(player, MOVE_OVERHEAT); }
    } SCENE {
        MESSAGE("Victini used Overheat!");
        HP_BAR(opponent, captureDamage: &results[i].damageBefore);
        if (ability == ABILITY_DESTINY_STAR) {
            ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, player);
            MESSAGE("Victini's Sp. Atk sharply rose!");
        } else {
            ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, player);
            MESSAGE("Victini's Sp. Atk harshly fell!");
        }

        HP_BAR(opponent, captureDamage: &results[i].damageAfter);
        if (ability == ABILITY_DESTINY_STAR) {
            ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, player);
            MESSAGE("Victini's Sp. Atk sharply rose!");
        } else {
            ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, player);
            MESSAGE("Victini's Sp. Atk harshly fell!");
        } FINALLY {
            EXPECT_MUL_EQ(results[0].damageBefore, Q_4_12(2.0), results[0].damageAfter);
            EXPECT_MUL_EQ(results[1].damageBefore, Q_4_12(0.5), results[i].damageAfter);
        }
    }
}

SINGLE_BATTLE_TEST("Destiny Star lowers a stat after using a move which would normally raise it", s16 damageBefore, s16 damageAfter)
{
    u32 ability;
    PARAMETRIZE { ability = ABILITY_DESTINY_STAR; }
    PARAMETRIZE { ability = ABILITY_VICTORY_STAR; }

    GIVEN {
        ASSUME(gBattleMoves[MOVE_SWORDS_DANCE].effect == EFFECT_ATTACK_UP_2);
        PLAYER(SPECIES_VICTINI) {Ability(ability); Attack(100);}
        OPPONENT(SPECIES_WOBBUFFET) {Defense(102);}
    } WHEN {
        TURN {MOVE(player, MOVE_TACKLE);}
        TURN {MOVE(player, MOVE_SWORDS_DANCE);}
        TURN {MOVE(player, MOVE_TACKLE);}
    } SCENE {
        MESSAGE("Victini used Tackle!");
        HP_BAR(opponent, captureDamage: &results[i].damageBefore);

        if (ability == ABILITY_DESTINY_STAR) {
            ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, player);
            MESSAGE("Victini's Attack harshly fell!");
        } else {
            ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, player);
            MESSAGE("Victini's Attack sharply rose!");
        }

        HP_BAR(opponent, captureDamage: &results[i].damageAfter);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damageBefore, Q_4_12(0.5), results[0].damageAfter);
        EXPECT_MUL_EQ(results[1].damageBefore, Q_4_12(2.0), results[1].damageAfter);
    }
}
