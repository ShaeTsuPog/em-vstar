#include "global.h"
#include "test_battle.h"

ASSUMPTIONS
{
    ASSUME(gBattleMoves[MOVE_STONE_AXE].effect == EFFECT_HIT_SET_ENTRY_HAZARD);
    ASSUME(gBattleMoves[MOVE_CEASELESS_EDGE].effect == EFFECT_HIT_SET_ENTRY_HAZARD);
}

SINGLE_BATTLE_TEST("Stone Axe / Ceaseless Edge set up hazards after hitting the target")
{
    u16 move;
    PARAMETRIZE {move = MOVE_STONE_AXE; }
    PARAMETRIZE {move = MOVE_CEASELESS_EDGE; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, move); }
        TURN { SWITCH(opponent, 1); }
    } SCENE {
        s32 maxHP = GetMonData(&OPPONENT_PARTY[1], MON_DATA_MAX_HP);
        ANIMATION(ANIM_TYPE_MOVE, move, player);
        HP_BAR(opponent);
        if (move == MOVE_CEASELESS_EDGE) {
            MESSAGE("Spikes were scattered all around the opposing team!");
        }
        else {
            MESSAGE("Pointed stones float in the air around the opposing team!");
        }
        MESSAGE("2 sent out Wobbuffet!");
        if (move == MOVE_CEASELESS_EDGE) {
            HP_BAR(opponent, damage: maxHP / 8);
            MESSAGE("Foe Wobbuffet is hurt by spikes!");
        }
        else {
            HP_BAR(opponent, damage: maxHP / 8);
            MESSAGE("Pointed stones dug into Foe Wobbuffet!");
        }
    }
}

SINGLE_BATTLE_TEST("Ceaseless Edge can set up to 3 layers of Spikes")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WYNAUT);
    } WHEN {
        TURN { MOVE(player, MOVE_CEASELESS_EDGE); }
        TURN { MOVE(player, MOVE_CEASELESS_EDGE); }
        TURN { MOVE(player, MOVE_CEASELESS_EDGE); }
        TURN { MOVE(player, MOVE_CEASELESS_EDGE); }
        TURN { SWITCH(opponent, 1); }
    } SCENE {
        s32 maxHP = GetMonData(&OPPONENT_PARTY[1], MON_DATA_MAX_HP);

        ANIMATION(ANIM_TYPE_MOVE, MOVE_CEASELESS_EDGE, player);
        HP_BAR(opponent);
        MESSAGE("Spikes were scattered all around the opposing team!");

        ANIMATION(ANIM_TYPE_MOVE, MOVE_CEASELESS_EDGE, player);
        HP_BAR(opponent);
        MESSAGE("Spikes were scattered all around the opposing team!");

        ANIMATION(ANIM_TYPE_MOVE, MOVE_CEASELESS_EDGE, player);
        HP_BAR(opponent);
        MESSAGE("Spikes were scattered all around the opposing team!");

        ANIMATION(ANIM_TYPE_MOVE, MOVE_CEASELESS_EDGE, player);
        HP_BAR(opponent);
        NOT MESSAGE("Spikes were scattered all around the opposing team!");

        MESSAGE("2 sent out Wynaut!");
        HP_BAR(opponent, damage: maxHP / 4);
        MESSAGE("Foe Wynaut is hurt by spikes!");
    }
}

SINGLE_BATTLE_TEST("Stone Axe can set up Stealth Rock only once")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WYNAUT);
    } WHEN {
        TURN { MOVE(player, MOVE_STONE_AXE); }
        TURN { MOVE(player, MOVE_STONE_AXE); }
        TURN { MOVE(player, MOVE_STONE_AXE); }
        TURN { MOVE(player, MOVE_STONE_AXE); }
        TURN { SWITCH(opponent, 1); }
    } SCENE {
        s32 maxHP = GetMonData(&OPPONENT_PARTY[1], MON_DATA_MAX_HP);

        ANIMATION(ANIM_TYPE_MOVE, MOVE_STONE_AXE, player);
        HP_BAR(opponent);
        MESSAGE("Pointed stones float in the air around the opposing team!");

        ANIMATION(ANIM_TYPE_MOVE, MOVE_STONE_AXE, player);
        HP_BAR(opponent);
        NOT MESSAGE("Pointed stones float in the air around the opposing team!");

        ANIMATION(ANIM_TYPE_MOVE, MOVE_STONE_AXE, player);
        HP_BAR(opponent);
        NOT MESSAGE("Pointed stones float in the air around the opposing team!");

        ANIMATION(ANIM_TYPE_MOVE, MOVE_STONE_AXE, player);
        HP_BAR(opponent);
        NOT MESSAGE("Pointed stones float in the air around the opposing team!");

        MESSAGE("2 sent out Wynaut!");
        HP_BAR(opponent, damage: maxHP / 8);
        MESSAGE("Pointed stones dug into Foe Wynaut!");
    }
}

SINGLE_BATTLE_TEST("Rock Throw can set up Stealth Rock only once")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN {MOVE(player, MOVE_ROCK_THROW);}
        TURN {MOVE(player, MOVE_ROCK_THROW);}
        TURN {MOVE(player, MOVE_ROCK_THROW);}
        TURN {MOVE(player, MOVE_ROCK_THROW);}
        TURN {SWITCH(opponent, 1);}
    } SCENE {
        s32 maxHP = GetMonData(&OPPONENT_PARTY[1], MON_DATA_MAX_HP);

        ANIMATION(ANIM_TYPE_MOVE, MOVE_ROCK_THROW, player);
        HP_BAR(opponent);
        MESSAGE("Pointed stones float in the air around the opposing team!");

        ANIMATION(ANIM_TYPE_MOVE, MOVE_ROCK_THROW, player);
        HP_BAR(opponent);
        NOT MESSAGE("Pointed stones float in the air around the opposing team!");

        ANIMATION(ANIM_TYPE_MOVE, MOVE_ROCK_THROW, player);
        HP_BAR(opponent);
        NOT MESSAGE("Pointed stones float in the air around the opposing team!");

        ANIMATION(ANIM_TYPE_MOVE, MOVE_ROCK_THROW, player);
        HP_BAR(opponent);
        NOT MESSAGE("Pointed stones float in the air around the opposing team!");

        MESSAGE("2 sent out Wynaut!");
        HP_BAR(opponent, damage: maxHP / 8);
        MESSAGE("Pointed stones dug into Foe Wynaut!");
    }
}

SINGLE_BATTLE_TEST("Pinsplosion can set up to 3 layers of Spikes")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WYNAUT);
    } WHEN {
        TURN { MOVE(player, MOVE_PINSPLOSION); }
        TURN { MOVE(player, MOVE_PINSPLOSION); }
        TURN { MOVE(player, MOVE_PINSPLOSION); }
        TURN { MOVE(player, MOVE_PINSPLOSION); }
        TURN { SWITCH(opponent, 1); }
    } SCENE {
        s32 maxHP = GetMonData(&OPPONENT_PARTY[1], MON_DATA_MAX_HP);

        ANIMATION(ANIM_TYPE_MOVE, MOVE_PINSPLOSION, player);
        HP_BAR(opponent);
        MESSAGE("Spikes were scattered all around the opposing team!");

        ANIMATION(ANIM_TYPE_MOVE, MOVE_PINSPLOSION, player);
        HP_BAR(opponent);
        MESSAGE("Spikes were scattered all around the opposing team!");

        ANIMATION(ANIM_TYPE_MOVE, MOVE_PINSPLOSION, player);
        HP_BAR(opponent);
        MESSAGE("Spikes were scattered all around the opposing team!");

        ANIMATION(ANIM_TYPE_MOVE, MOVE_PINSPLOSION, player);
        HP_BAR(opponent);
        NOT MESSAGE("Spikes were scattered all around the opposing team!");

        MESSAGE("2 sent out Wynaut!");
        HP_BAR(opponent, damage: maxHP / 4);
        MESSAGE("Foe Wynaut is hurt by spikes!");
    }
}
