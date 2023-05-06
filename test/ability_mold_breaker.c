#include "global.h"
#include "test_battle.h"

SINGLE_BATTLE_TEST("Mold Breaker ignores various HP absorbing abilities")
{
    u32 species;
    u32 ability;
    u32 move;

    PARAMETRIZE { species = SPECIES_LANTURN;  ability = ABILITY_WATER_ABSORB; move = MOVE_WATER_GUN; }
    PARAMETRIZE { species = SPECIES_JOLTEON;  ability = ABILITY_VOLT_ABSORB;  move = MOVE_THUNDER_SHOCK; }
    PARAMETRIZE { species = SPECIES_PARASECT; ability = ABILITY_DRY_SKIN;     move = MOVE_WATER_GUN; }
    //PARAMETRIZE { species = SPECIES_ORTHWORM; ability = ABILITY_EARTH_EATER;  move = MOVE_MUD_SHOT; }

    GIVEN {
        PLAYER(SPECIES_PINSIR) { Ability(ABILITY_MOLD_BREAKER); };
        OPPONENT(species) { Ability(ability); };
    } WHEN {
        TURN { MOVE(player, move); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_MOLD_BREAKER);
        MESSAGE("Pinsir breaks the mold!");
        NOT ABILITY_POPUP(opponent, ability);
        ANIMATION(ANIM_TYPE_MOVE, move, player);
        HP_BAR(opponent);
    }
}

SINGLE_BATTLE_TEST("Mold Breaker ignores various stat boosting absorb abilities")
{
    u32 species;
    u32 ability;
    u32 move;

    PARAMETRIZE { species = SPECIES_AZUMARILL;  ability = ABILITY_SAP_SIPPER;      move = MOVE_ABSORB; }
    PARAMETRIZE { species = SPECIES_FLAREON;    ability = ABILITY_FLASH_FIRE;      move = MOVE_EMBER; }
    PARAMETRIZE { species = SPECIES_PIKACHU;    ability = ABILITY_LIGHTNING_ROD;   move = MOVE_THUNDER_SHOCK; }
    PARAMETRIZE { species = SPECIES_ELECTIVIRE; ability = ABILITY_MOTOR_DRIVE;     move = MOVE_THUNDER_SHOCK; }
    PARAMETRIZE { species = SPECIES_CRADILY;    ability = ABILITY_STORM_DRAIN;     move = MOVE_WATER_GUN; }
    //PARAMETRIZE { species = SPECIES_DACHSBUN;   ability = ABILITY_WELL_BAKED_BODY; move = MOVE_EMBER; }
    //PARAMETRIZE { species = SPECIES_BRAMBLIN;   ability = ABILITY_WIND_RIDER;      move = MOVE_FAIRY_WIND; }

    GIVEN {
        PLAYER(SPECIES_PINSIR) { Ability(ABILITY_MOLD_BREAKER); };
        OPPONENT(species) { Ability(ability); };
    } WHEN {
        TURN { MOVE(player, move); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_MOLD_BREAKER);
        MESSAGE("Pinsir breaks the mold!");
        HP_BAR(opponent);
        NOT ABILITY_POPUP(opponent, ability);
        NOT ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, opponent);
    }
}

SINGLE_BATTLE_TEST("Mold Breaker ignores various status immunity abilities, but not their curing effects")
{
    u32 species;
    u32 ability;
    u32 move;

    PARAMETRIZE { species = SPECIES_ZANGOOSE;          ability = ABILITY_IMMUNITY;     move = MOVE_TOXIC; }
    PARAMETRIZE { species = SPECIES_RAPIDASH_GALARIAN; ability = ABILITY_PASTEL_VEIL;  move = MOVE_TOXIC; }
    PARAMETRIZE { species = SPECIES_HYPNO;             ability = ABILITY_INSOMNIA;     move = MOVE_HYPNOSIS; }
    PARAMETRIZE { species = SPECIES_PRIMEAPE;          ability = ABILITY_VITAL_SPIRIT; move = MOVE_HYPNOSIS; }
    PARAMETRIZE { species = SPECIES_PERSIAN;           ability = ABILITY_LIMBER;       move = MOVE_THUNDER_WAVE; }
    PARAMETRIZE { species = SPECIES_SEAKING;           ability = ABILITY_WATER_VEIL;   move = MOVE_WILL_O_WISP; }
    PARAMETRIZE { species = SPECIES_DEWPIDER;          ability = ABILITY_WATER_BUBBLE; move = MOVE_WILL_O_WISP; }
    PARAMETRIZE { species = SPECIES_SLOWBRO;           ability = ABILITY_OBLIVIOUS;    move = MOVE_TAUNT; }
    PARAMETRIZE { species = SPECIES_LICKITUNG;         ability = ABILITY_OBLIVIOUS;    move = MOVE_ATTRACT; }
    PARAMETRIZE { species = SPECIES_MAGCARGO;          ability = ABILITY_MAGMA_ARMOR;  move = MOVE_ICE_BEAM; }
    PARAMETRIZE { species = SPECIES_SLOWKING;          ability = ABILITY_OWN_TEMPO;    move = MOVE_CONFUSE_RAY; }

    GIVEN {
        PLAYER(SPECIES_PINSIR) { Ability(ABILITY_MOLD_BREAKER); Gender(MON_MALE); };
        OPPONENT(species) { Ability(ability); Gender(MON_FEMALE); };
    } WHEN {
        TURN { MOVE(player, move); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_MOLD_BREAKER);
        MESSAGE("Pinsir breaks the mold!");

        switch (ability) {

            case ABILITY_IMMUNITY:
            case ABILITY_PASTEL_VEIL:
                STATUS_ICON(opponent, badPoison: TRUE);
                ABILITY_POPUP(opponent, ability);
                STATUS_ICON(opponent, none: TRUE);
                break;
            case ABILITY_INSOMNIA:
            case ABILITY_VITAL_SPIRIT:
                STATUS_ICON(opponent, sleep: TRUE);
                ABILITY_POPUP(opponent, ability);
                STATUS_ICON(opponent, none: TRUE);
                break;
            case ABILITY_LIMBER:
                STATUS_ICON(opponent, paralysis: TRUE);
                ABILITY_POPUP(opponent, ABILITY_LIMBER);
                STATUS_ICON(opponent, none: TRUE);
                break;
            case ABILITY_WATER_VEIL:
            case ABILITY_WATER_BUBBLE:
                STATUS_ICON(opponent, burn: TRUE);
                ABILITY_POPUP(opponent, ability);
                STATUS_ICON(opponent, none: TRUE);
                break;
            case ABILITY_OBLIVIOUS:
                if (species == SPECIES_SLOWBRO) {
                    MESSAGE("Foe Slowbro fell for the Taunt!");
                    ABILITY_POPUP(opponent, ABILITY_OBLIVIOUS);
                    MESSAGE("Foe Slowbro shook off the taunt!");
                } else {
                    MESSAGE("Foe Lickitung fell in love!");
                    ABILITY_POPUP(opponent, ABILITY_OBLIVIOUS);
                    MESSAGE("Foe Lickitung got over its infatuation!");
                }
                break;
            case ABILITY_MAGMA_ARMOR:
                STATUS_ICON(opponent, freeze: TRUE);
                // Doesn't seem to have an ability popup? Maybe it should?
                MESSAGE("Foe Magcargo was defrosted!");
                STATUS_ICON(opponent, none: TRUE);
                break;
            case ABILITY_OWN_TEMPO:
                MESSAGE("Foe Slowking became confused!");
                ABILITY_POPUP(opponent, ABILITY_OWN_TEMPO);
                MESSAGE("Foe Slowking's Own Tempo cured its confusion problem!");
                break;
        }
    }
}

SINGLE_BATTLE_TEST("Mold Breaker ignores various status immunity abilities with no curing effect")
{
    u32 species;
    u32 ability;
    u32 move;

    PARAMETRIZE { species = SPECIES_SLURPUFF;  ability = ABILITY_SWEET_VEIL;     move = MOVE_HYPNOSIS; }
    // PARAMETRIZE { species = SPECIES_GHOLDENGO; ability = ABILITY_GOOD_AS_GOLD;   move = MOVE_THUNDER_WAVE; }
    // PARAMETRIZE { species = SPECIES_GARGANACL; ability = ABILITY_PURIFYING_SALT; move = MOVE_TOXIC; }

    GIVEN {
        PLAYER(SPECIES_PINSIR) { Ability(ABILITY_MOLD_BREAKER); };
        OPPONENT(species) { Ability(ability); };
    } WHEN {
        TURN { MOVE(player, move); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_MOLD_BREAKER);
        MESSAGE("Pinsir breaks the mold!");

        switch (ability) {

            case ABILITY_SWEET_VEIL:
                MESSAGE("Pinsir used Hypnosis!");
                MESSAGE("Foe Slurpuff fell asleep!");
                STATUS_ICON(opponent, sleep: TRUE);
                break;
            // case ABILITY_GOOD_AS_GOLD:
            //     MESSAGE("Pinsir used Thunder Wave!");
            //     MESSAGE("Foe Gholdengo was paralyzed! It may be unable to move!");
            //     STATUS_ICON(opponent, paralysis: TRUE);
            //     break;
            // case ABILITY_PURIFYING_SALT:
            //     MESSAGE("Pinsir used Toxic!");
            //     MESSAGE("Foe Garganacl was badly poisoned!");
            //     STATUS_ICON(opponent, badPoison: TRUE);
            //     break;
        }
    }
}

SINGLE_BATTLE_TEST("Mold Breaker ignores various stat reducing immunity abilities")
{
    u32 species;
    u32 ability;
    u32 move;

    PARAMETRIZE { species = SPECIES_PIDGEOT;    ability = ABILITY_BIG_PECKS;    move = MOVE_LEER; }
    PARAMETRIZE { species = SPECIES_TENTACRUEL; ability = ABILITY_CLEAR_BODY;   move = MOVE_SCARY_FACE; }
    PARAMETRIZE { species = SPECIES_KINGLER;    ability = ABILITY_HYPER_CUTTER; move = MOVE_GROWL; }
    PARAMETRIZE { species = SPECIES_HITMONCHAN; ability = ABILITY_KEEN_EYE;     move = MOVE_SAND_ATTACK; }
    PARAMETRIZE { species = SPECIES_TORKOAL;    ability = ABILITY_WHITE_SMOKE;  move = MOVE_GROWL; }

    GIVEN {
        PLAYER(SPECIES_PINSIR) { Ability(ABILITY_MOLD_BREAKER); };
        OPPONENT(species) { Ability(ability); };
    } WHEN {
        TURN { MOVE(player, move); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_MOLD_BREAKER);
        MESSAGE("Pinsir breaks the mold!");

        switch (ability) {

            case ABILITY_BIG_PECKS:
                MESSAGE("Pinsir used Leer!");
                ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, opponent);
                MESSAGE("Foe Pidgeot's Defense fell!");
                break;
            case ABILITY_CLEAR_BODY:
                MESSAGE("Pinsir used Scary Face!");
                ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, opponent);
                MESSAGE("Foe Tentacruel's Speed harshly fell!");
                break;
            case ABILITY_HYPER_CUTTER:
                MESSAGE("Pinsir used Growl!");
                ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, opponent);
                MESSAGE("Foe Kingler's Attack fell!");
                break;
            case ABILITY_KEEN_EYE:
                MESSAGE("Pinsir used Sand Attack!");
                ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, opponent);
                MESSAGE("Foe Hitmonchan's accuracy fell!");
                break;
            case ABILITY_WHITE_SMOKE:
                MESSAGE("Pinsir used Growl!");
                ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, opponent);
                MESSAGE("Foe Torkoal's Attack fell!");
                break;
        }
    }
}

SINGLE_BATTLE_TEST("Mold Breaker ignores various move immunity abilities")
{
    u32 species;
    u32 ability;
    u32 move;

    PARAMETRIZE { species = SPECIES_HAUNTER;    ability = ABILITY_LEVITATE;        move = MOVE_MUD_SHOT; }
    PARAMETRIZE { species = SPECIES_SHEDINJA;   ability = ABILITY_WONDER_GUARD;    move = MOVE_MUD_SHOT; }
    PARAMETRIZE { species = SPECIES_CHESNAUGHT; ability = ABILITY_BULLETPROOF;     move = MOVE_AURA_SPHERE; }
    PARAMETRIZE { species = SPECIES_BRUXISH;    ability = ABILITY_DAZZLING;        move = MOVE_EXTREME_SPEED; }
    //PARAMETRIZE { species = SPECIES_FARIGIRAF;  ability = ABILITY_ARMOR_TAIL;      move = MOVE_EXTREME_SPEED; }
    PARAMETRIZE { species = SPECIES_TSAREENA;   ability = ABILITY_QUEENLY_MAJESTY; move = MOVE_EXTREME_SPEED; }
    PARAMETRIZE { species = SPECIES_ELECTRODE;  ability = ABILITY_SOUNDPROOF;      move = MOVE_HYPER_VOICE; }
    PARAMETRIZE { species = SPECIES_CLOYSTER;   ability = ABILITY_OVERCOAT;        move = MOVE_POISON_POWDER; }

    GIVEN {
        PLAYER(SPECIES_PINSIR) { Ability(ABILITY_MOLD_BREAKER); };
        OPPONENT(species) { Ability(ability); };
    } WHEN {
        TURN { MOVE(player, move); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_MOLD_BREAKER);
        MESSAGE("Pinsir breaks the mold!");

        switch (ability) {

            case ABILITY_LEVITATE:
            case ABILITY_WONDER_GUARD:
                ANIMATION(ANIM_TYPE_MOVE, MOVE_MUD_SHOT, player);
                break;
            case ABILITY_BULLETPROOF:
                ANIMATION(ANIM_TYPE_MOVE, MOVE_AURA_SPHERE, player);
                break;
            case ABILITY_DAZZLING:
            case ABILITY_QUEENLY_MAJESTY:
            //case ABILITY_ARMOR_TAIL:
                ANIMATION(ANIM_TYPE_MOVE, MOVE_EXTREME_SPEED, player);
                break;
            case ABILITY_SOUNDPROOF:
                ANIMATION(ANIM_TYPE_MOVE, MOVE_HYPER_VOICE, player);
                break;
            case ABILITY_OVERCOAT:
                STATUS_ICON(opponent, poison: TRUE);
                break;
        }
        HP_BAR(opponent);
    }
}

SINGLE_BATTLE_TEST("Mold Breaker ignores various secondary effect immunity abilities")
{
    u32 species;
    u32 ability;
    u32 move;

    PARAMETRIZE { species = SPECIES_GOLBAT; ability = ABILITY_INNER_FOCUS; move = MOVE_IRON_HEAD; }
    PARAMETRIZE { species = SPECIES_DUSTOX; ability = ABILITY_SHIELD_DUST; move = MOVE_THUNDER_SHOCK; }

    GIVEN {
        PLAYER(SPECIES_PINSIR) { Ability(ABILITY_MOLD_BREAKER); };
        OPPONENT(species) { Ability(ability); };
    } WHEN {
        TURN { MOVE(player, move); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_MOLD_BREAKER);
        MESSAGE("Pinsir breaks the mold!");

        switch (ability) {

            case ABILITY_INNER_FOCUS:
                MESSAGE("Pinsir used Iron Head!");
                HP_BAR(opponent);
                MESSAGE("Foe Golbat flinched!");
                break;
            case ABILITY_SHIELD_DUST:
                MESSAGE("Pinsir used ThunderShock!");
                HP_BAR(opponent);
                STATUS_ICON(opponent, paralysis: TRUE);
                break;
        }
    }
}

SINGLE_BATTLE_TEST("Mold Breaker ignores Aroma Veil")
{
    u32 move;
    PARAMETRIZE { move = MOVE_TAUNT; }
    PARAMETRIZE { move = MOVE_TORMENT; }
    PARAMETRIZE { move = MOVE_ENCORE; }
    PARAMETRIZE { move = MOVE_DISABLE; }
    PARAMETRIZE { move = MOVE_HEAL_BLOCK; }
    PARAMETRIZE { move = MOVE_ATTRACT; }

    GIVEN {
        PLAYER(SPECIES_PINSIR) { Ability(ABILITY_MOLD_BREAKER); Gender(MON_MALE); };
        OPPONENT(SPECIES_AROMATISSE) { Ability(ABILITY_AROMA_VEIL); Gender(MON_FEMALE); };
    } WHEN {
        TURN { MOVE(opponent, MOVE_CELEBRATE); MOVE(player, move); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_MOLD_BREAKER);
        MESSAGE("Pinsir breaks the mold!");

        switch (move) {

            case MOVE_TAUNT:
                MESSAGE("Pinsir used Taunt!");
                ANIMATION(ANIM_TYPE_MOVE, MOVE_TAUNT, player);
                MESSAGE("Foe Aromatisse fell for the Taunt!");
                break;
            case MOVE_TORMENT:
                MESSAGE("Pinsir used Torment!");
                ANIMATION(ANIM_TYPE_MOVE, MOVE_TORMENT, player);
                MESSAGE("Foe Aromatisse was subjected to torment!");
                break;
            case MOVE_ENCORE:
                MESSAGE("Pinsir used Encore!");
                ANIMATION(ANIM_TYPE_MOVE, MOVE_ENCORE, player);
                MESSAGE("Foe Aromatisse got an ENCORE!");
                break;
            case MOVE_DISABLE:
                MESSAGE("Pinsir used Disable!");
                ANIMATION(ANIM_TYPE_MOVE, MOVE_DISABLE, player);
                MESSAGE("Foe Aromatisse's Celebrate was disabled!");
                break;
            case MOVE_HEAL_BLOCK:
                MESSAGE("Pinsir used Heal Block!");
                ANIMATION(ANIM_TYPE_MOVE, MOVE_HEAL_BLOCK, player);
                MESSAGE("Foe Aromatisse was prevented from healing!");
                break;
            case MOVE_ATTRACT:
                MESSAGE("Pinsir used Attract!");
                ANIMATION(ANIM_TYPE_MOVE, MOVE_ATTRACT, player);
                MESSAGE("Foe Aromatisse fell in love!");
                break;
        }
    }
}

SINGLE_BATTLE_TEST("Mold Breaker ignores crit immunity abilities")
{
    u32 species;
    u32 ability;
    PARAMETRIZE { species = SPECIES_MAROWAK;  ability = ABILITY_BATTLE_ARMOR; }
    PARAMETRIZE { species = SPECIES_CLOYSTER; ability = ABILITY_SHELL_ARMOR; }

    GIVEN {
        PLAYER(SPECIES_PINSIR) { Ability(ABILITY_MOLD_BREAKER); };
        OPPONENT(species) { Ability(ability); };
    } WHEN {
        TURN { MOVE(player, MOVE_STORM_THROW); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_MOLD_BREAKER);
        MESSAGE("Pinsir breaks the mold!");
        MESSAGE("Pinsir used Storm Throw!");
        HP_BAR(opponent);
        MESSAGE("A critical hit!");
    }
}

SINGLE_BATTLE_TEST("Mold Breaker ignores evasion boosting weather abilities")
{
    u32 species;
    u32 ability;
    u32 move;

    PARAMETRIZE { species = SPECIES_CACTURNE; ability = ABILITY_SAND_VEIL;  move = MOVE_SANDSTORM; }
    PARAMETRIZE { species = SPECIES_GLACEON;  ability = ABILITY_SNOW_CLOAK; move = MOVE_HAIL; }

    PASSES_RANDOMLY(5, 5, RNG_ACCURACY);
    GIVEN {
        PLAYER(SPECIES_PINSIR) { Ability(ABILITY_MOLD_BREAKER); };
        OPPONENT(species) { Ability(ability); };
    } WHEN {
        TURN { MOVE(opponent, move); MOVE(player, MOVE_POUND); }
    } SCENE {
        MESSAGE("Pinsir used Pound!");
        HP_BAR(opponent);
    }
}

SINGLE_BATTLE_TEST("Mold Breaker ignores effect bouncing abilities")
{
    u32 species;
    u32 ability;
    u32 move;

    PARAMETRIZE { species = SPECIES_ESPEON;      ability = ABILITY_MAGIC_BOUNCE; move = MOVE_STEALTH_ROCK; }
    PARAMETRIZE { species = SPECIES_CORVIKNIGHT; ability = ABILITY_MIRROR_ARMOR; move = MOVE_GROWL; }

    GIVEN {
        PLAYER(SPECIES_PINSIR) { Ability(ABILITY_MOLD_BREAKER); };
        OPPONENT(species) { Ability(ability); };
    } WHEN {
        TURN { MOVE(player, move); }
    } SCENE {

        switch (ability) {

            case ABILITY_MAGIC_BOUNCE:
                MESSAGE("Pinsir used Stealth Rock!");
                NOT ABILITY_POPUP(opponent, ABILITY_MAGIC_BOUNCE);
                ANIMATION(ANIM_TYPE_MOVE, MOVE_STEALTH_ROCK, player);
                break;
            case ABILITY_MIRROR_ARMOR:
                MESSAGE("Pinsir used Growl!");
                NOT ABILITY_POPUP(opponent, ABILITY_MIRROR_ARMOR);
                ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, opponent);
                break;
        }
    }
}

SINGLE_BATTLE_TEST("Mold Breaker ignores Contrary")
{
    GIVEN {
        PLAYER(SPECIES_PINSIR) { Ability(ABILITY_MOLD_BREAKER); };
        OPPONENT(SPECIES_SHUCKLE) { Ability(ABILITY_CONTRARY); };
    } WHEN {
        TURN { MOVE(player, MOVE_GROWL); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_MOLD_BREAKER);
        MESSAGE("Pinsir breaks the mold!");
        MESSAGE("Pinsir used Growl!");
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, opponent);
        MESSAGE("Foe Shuckle's Attack fell!");
    }
}

SINGLE_BATTLE_TEST("Mold Breaker ignores Sturdy")
{
    u32 move;
    PARAMETRIZE { move = MOVE_EARTHQUAKE; }
    PARAMETRIZE { move = MOVE_FISSURE; }

    GIVEN {
        PLAYER(SPECIES_PINSIR) { Ability(ABILITY_MOLD_BREAKER); };
        OPPONENT(SPECIES_GOLEM) { Ability(ABILITY_STURDY); Level(1); };
    } WHEN {
        TURN { MOVE(player, move); }
    } SCENE {
        if (move == MOVE_EARTHQUAKE)
            ANIMATION(ANIM_TYPE_MOVE, MOVE_EARTHQUAKE, player);
        else
            ANIMATION(ANIM_TYPE_MOVE, MOVE_FISSURE, player);

        HP_BAR(opponent);
        MESSAGE("Foe Golem fainted!");
    }
}

SINGLE_BATTLE_TEST("Mold Breaker ignores Damp")
{
    GIVEN {
        PLAYER(SPECIES_PINSIR) { Ability(ABILITY_MOLD_BREAKER); };
        OPPONENT(SPECIES_QUAGSIRE) { Ability(ABILITY_DAMP); };
    } WHEN {
        TURN { MOVE(player, MOVE_EXPLOSION); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_MOLD_BREAKER);
        MESSAGE("Pinsir breaks the mold!");
        MESSAGE("Pinsir used Explosion!");
        HP_BAR(player, hp: 0);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_EXPLOSION, player);
        HP_BAR(opponent);
    }
}

SINGLE_BATTLE_TEST("Mold Breaker ignores Disguise and Ice Face")
{
    u32 species;
    u32 ability;

    PARAMETRIZE { species = SPECIES_MIMIKYU; ability = ABILITY_DISGUISE; }
    PARAMETRIZE { species = SPECIES_EISCUE;  ability = ABILITY_ICE_FACE; }

    GIVEN {
        PLAYER(SPECIES_PINSIR) { Ability(ABILITY_MOLD_BREAKER); };
        OPPONENT(species) { Ability(ability); };
    } WHEN {
        TURN { MOVE(player, MOVE_SHADOW_CLAW); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_MOLD_BREAKER);
        MESSAGE("Pinsir breaks the mold!");
        MESSAGE("Pinsir used Shadow Claw!");
        NOT ABILITY_POPUP(opponent, ability);
        HP_BAR(opponent);
    }
}

DOUBLE_BATTLE_TEST("Mold Breaker ignores Flower Veil")
{
    GIVEN {
        PLAYER(SPECIES_PINSIR) { Ability(ABILITY_MOLD_BREAKER); };
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_FLORGES) { Ability(ABILITY_FLOWER_VEIL); };
        OPPONENT(SPECIES_TANGELA);
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_GROWL, target: opponentRight); }
        TURN { MOVE(playerLeft, MOVE_THUNDER_WAVE, target: opponentRight); }
    } SCENE {
        ABILITY_POPUP(playerLeft, ABILITY_MOLD_BREAKER);
        MESSAGE("Pinsir breaks the mold!");

        MESSAGE("Pinsir used Growl!");
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, opponentRight);
        MESSAGE("Foe Tangela's Attack fell!");

        MESSAGE("Pinsir used Thunder Wave!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_THUNDER_WAVE, playerLeft);
        STATUS_ICON(opponentRight, paralysis: TRUE);
    }
}

SINGLE_BATTLE_TEST("Mold Breaker ignores Heatproof", s16 damage)
{
    u32 ability;
    PARAMETRIZE { ability = ABILITY_LEVITATE; }
    PARAMETRIZE { ability = ABILITY_HEATPROOF; }

    GIVEN {
        PLAYER(SPECIES_PINSIR) { Ability(ABILITY_MOLD_BREAKER); };
        OPPONENT(SPECIES_BRONZONG) { Ability(ability); };
    } WHEN {
        TURN { MOVE(player, MOVE_EMBER); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_MOLD_BREAKER);
        MESSAGE("Pinsir breaks the mold!");
        MESSAGE("Pinsir used Ember!");
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(1.0), results[1].damage);
    }
}

SINGLE_BATTLE_TEST("Mold Breaker ignores Fur Coat", s16 damage)
{
    u32 ability;
    PARAMETRIZE { ability = ABILITY_FUR_COAT; }
    PARAMETRIZE { ability = ABILITY_TECHNICIAN; }

    GIVEN {
        PLAYER(SPECIES_PINSIR) { Ability(ABILITY_MOLD_BREAKER); };
        OPPONENT(SPECIES_PERSIAN_ALOLAN) { Ability(ability); };
    } WHEN {
        TURN { MOVE(player, MOVE_TACKLE); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_MOLD_BREAKER);
        MESSAGE("Pinsir breaks the mold!");
        MESSAGE("Pinsir used Tackle!");

        if (ability == ABILITY_FUR_COAT) {
            HP_BAR(opponent, captureDamage: &results[0].damage);
        } else {
            HP_BAR(opponent, captureDamage: &results[1].damage);
        }
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(1.0), results[1].damage);
    }
}

SINGLE_BATTLE_TEST("Mold Breaker ignores Fluffy", s16 damage)
{
    u32 ability;
    PARAMETRIZE { ability = ABILITY_FLUFFY; }
    PARAMETRIZE { ability = ABILITY_KLUTZ; }

    GIVEN {
        PLAYER(SPECIES_PINSIR) { Ability(ABILITY_MOLD_BREAKER); };
        OPPONENT(SPECIES_BEWEAR) { Ability(ability); };
    } WHEN {
        TURN { MOVE(player, MOVE_TACKLE); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_MOLD_BREAKER);
        MESSAGE("Pinsir breaks the mold!");
        MESSAGE("Pinsir used Tackle!");

        if (ability == ABILITY_FLUFFY) {
            HP_BAR(opponent, captureDamage: &results[0].damage);
        } else {
            HP_BAR(opponent, captureDamage: &results[1].damage);
        }
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(1.0), results[1].damage);
    }
}

SINGLE_BATTLE_TEST("Mold Breaker ignores Ice Scales", s16 damage)
{
    u32 ability;
    PARAMETRIZE { ability = ABILITY_SHIELD_DUST; }
    PARAMETRIZE { ability = ABILITY_ICE_SCALES; }

    GIVEN {
        PLAYER(SPECIES_PINSIR) { Ability(ABILITY_MOLD_BREAKER); };
        OPPONENT(SPECIES_FROSMOTH) { Ability(ability); };
    } WHEN {
        TURN { MOVE(player, MOVE_SHADOW_BALL); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_MOLD_BREAKER);
        MESSAGE("Pinsir breaks the mold!");
        MESSAGE("Pinsir used Shadow Ball!");
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(1.0), results[1].damage);
    }
}

SINGLE_BATTLE_TEST("Mold Breaker ignores Filter", s16 damage)
{
    u32 ability;
    PARAMETRIZE { ability = ABILITY_FILTER; }
    PARAMETRIZE { ability = ABILITY_SOUNDPROOF; }

    GIVEN {
        PLAYER(SPECIES_PINSIR) { Ability(ABILITY_MOLD_BREAKER); };
        OPPONENT(SPECIES_MR_MIME) {Ability(ability); };
    } WHEN {
        TURN { MOVE(player, MOVE_PURSUIT); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_MOLD_BREAKER);
        MESSAGE("Pinsir breaks the mold!");
        MESSAGE("Pinsir used Pursuit!");
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(1.0), results[1].damage);
    }
}

SINGLE_BATTLE_TEST("Mold Breaker ignores Solid Rock", s16 damage)
{
    u32 ability;
    PARAMETRIZE { ability = ABILITY_MAGMA_ARMOR; }
    PARAMETRIZE { ability = ABILITY_SOLID_ROCK; }

    GIVEN {
        PLAYER(SPECIES_PINSIR) { Ability(ABILITY_MOLD_BREAKER); };
        OPPONENT(SPECIES_CAMERUPT) { Ability(ability); };
    } WHEN {
        TURN { MOVE(player, MOVE_WATER_GUN); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_MOLD_BREAKER);
        MESSAGE("Pinsir breaks the mold!");
        MESSAGE("Pinsir used Water Gun!");
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(1.0), results[1].damage);
    }
}

SINGLE_BATTLE_TEST("Mold Breaker ignores Leaf Guard")
{
    GIVEN {
        PLAYER(SPECIES_PINSIR) { Ability(ABILITY_MOLD_BREAKER); };
        OPPONENT(SPECIES_LEAFEON) { Ability(ABILITY_LEAF_GUARD) ; };
    } WHEN {
        TURN { MOVE(opponent, MOVE_SUNNY_DAY); MOVE(player, MOVE_HYPNOSIS); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_MOLD_BREAKER);
        MESSAGE("Pinsir breaks the mold!");
        MESSAGE("Foe Leafeon used Sunny Day!");
        MESSAGE("Pinsir used Hypnosis!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_HYPNOSIS, player);
        STATUS_ICON(opponent, sleep: TRUE);
    }
}

SINGLE_BATTLE_TEST("Mold Breaker ignores Marvel Scale", s16 damageBefore, s16 damageAfter)
{
    GIVEN {
        PLAYER(SPECIES_PINSIR) { Ability(ABILITY_MOLD_BREAKER); };
        OPPONENT(SPECIES_MILOTIC) { Ability(ABILITY_MARVEL_SCALE); };
    } WHEN {
        TURN { MOVE(player, MOVE_TACKLE); MOVE(opponent, MOVE_CELEBRATE); }
        TURN { MOVE(player, MOVE_THUNDER_WAVE); MOVE(opponent, MOVE_CELEBRATE); }
        TURN { MOVE(player, MOVE_TACKLE); MOVE(opponent, MOVE_CELEBRATE); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_MOLD_BREAKER);
        MESSAGE("Pinsir breaks the mold!");

        MESSAGE("Pinsir used Tackle!");
        HP_BAR(opponent, captureDamage: &results[i].damageBefore);

        MESSAGE("Pinsir used Thunder Wave!");
        STATUS_ICON(opponent, paralysis: TRUE);

        MESSAGE("Pinsir used Tackle!");
        HP_BAR(opponent, captureDamage: &results[i].damageAfter);
    } THEN {
        EXPECT_MUL_EQ(results[0].damageBefore, Q_4_12(1.0), results[0].damageAfter);
    }
}

SINGLE_BATTLE_TEST("Mold Breaker ignores Multiscale", s16 damage)
{
    u32 ability;
    PARAMETRIZE { ability = ABILITY_INNER_FOCUS; }
    PARAMETRIZE { ability = ABILITY_MULTISCALE; }

    GIVEN {
        PLAYER(SPECIES_PINSIR) { Ability(ABILITY_MOLD_BREAKER); };
        OPPONENT(SPECIES_DRAGONITE) { Ability(ability); };
    } WHEN {
        TURN { MOVE(player, MOVE_TACKLE); }
    } SCENE {
        MESSAGE("Pinsir used Tackle!");
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(1.0), results[1].damage);
    }
}

SINGLE_BATTLE_TEST("Mold Breaker ignores Thick Fat", s16 damage)
{
    u32 ability;
    PARAMETRIZE { ability = ABILITY_IMMUNITY; }
    PARAMETRIZE { ability = ABILITY_THICK_FAT; }

    GIVEN {
        PLAYER(SPECIES_PINSIR) { Ability(ABILITY_MOLD_BREAKER); };
        OPPONENT(SPECIES_SNORLAX) { Ability(ability); };
    } WHEN {
        TURN { MOVE(player, MOVE_ICE_BEAM); }
    } SCENE {
        MESSAGE("Pinsir used Ice Beam!");
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(1.0), results[1].damage);
    }
}

SINGLE_BATTLE_TEST("Mold Breaker ignores Grass Pelt", s16 damage)
{
    u32 ability;
    PARAMETRIZE { ability = ABILITY_SAP_SIPPER; }
    PARAMETRIZE { ability = ABILITY_GRASS_PELT; }

    GIVEN {
        PLAYER(SPECIES_PINSIR) { Ability(ABILITY_MOLD_BREAKER); };
        OPPONENT(SPECIES_GOGOAT) { Ability(ability); };
    } WHEN {
        TURN { MOVE(player, MOVE_TACKLE); MOVE(opponent, MOVE_GRASSY_TERRAIN); }
        TURN { MOVE(player, MOVE_TACKLE); }
    } SCENE {
        MESSAGE("Pinsir used Tackle!");
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(1.0), results[1].damage);
    }
}

SINGLE_BATTLE_TEST("Mold Breaker ignores Punk Rock", s16 damage)
{
    u32 ability;
    PARAMETRIZE { ability = ABILITY_MINUS; }
    PARAMETRIZE { ability = ABILITY_PUNK_ROCK; }

    GIVEN {
        PLAYER(SPECIES_PINSIR) { Ability(ABILITY_MOLD_BREAKER); };
        OPPONENT(SPECIES_TOXTRICITY_LOW_KEY) { Ability(ability); };
    } WHEN {
        TURN { MOVE(player, MOVE_HYPER_VOICE); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(1.0), results[1].damage);
    }
}

SINGLE_BATTLE_TEST("Mold Breaker ignores Unaware", s16 damage)
{
    u32 ability;
    PARAMETRIZE { ability = ABILITY_DAMP; }
    PARAMETRIZE { ability = ABILITY_UNAWARE; }

    GIVEN {
        PLAYER(SPECIES_PINSIR) { Ability(ABILITY_MOLD_BREAKER); };
        OPPONENT(SPECIES_QUAGSIRE) { Ability(ability); };
    } WHEN {
        TURN { MOVE(player, MOVE_SWORDS_DANCE); }
        TURN { MOVE(player, MOVE_TACKLE); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(1.0), results[1].damage);
    }
}

DOUBLE_BATTLE_TEST("Mold Breaker ignores Friend Guard", s16 damage)
{
    u32 ability;
    PARAMETRIZE { ability = ABILITY_CUTE_CHARM; }
    PARAMETRIZE { ability = ABILITY_FRIEND_GUARD; }

    GIVEN {
        PLAYER(SPECIES_PINSIR) { Ability(ABILITY_MOLD_BREAKER); };
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_CLEFAIRY) { Ability(ability); };
        OPPONENT(SPECIES_WYNAUT);
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_TACKLE, target: opponentRight); }
    } SCENE {
        HP_BAR(opponentRight, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(1.0), results[1].damage);
    }
}

DOUBLE_BATTLE_TEST("Mold Breaker ignores Telepathy")
{
    GIVEN {
        PLAYER(SPECIES_PINSIR) { Ability(ABILITY_MOLD_BREAKER); };
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_TELEPATHY); };
        OPPONENT(SPECIES_WYNAUT);
        OPPONENT(SPECIES_CHANSEY);
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_SURF); }
    } SCENE {
        MESSAGE("Pinsir used Surf!");
        NOT ABILITY_POPUP(playerRight, ABILITY_TELEPATHY);
        HP_BAR(playerRight);
    }
}

SINGLE_BATTLE_TEST("Mold Breaker ignores Simple")
{
    GIVEN {
        PLAYER(SPECIES_PINSIR) { Ability(ABILITY_MOLD_BREAKER); };
        OPPONENT(SPECIES_NUMEL) { Ability(ABILITY_SIMPLE); };
    } WHEN {
        TURN { MOVE(player, MOVE_GROWL); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_MOLD_BREAKER);
        MESSAGE("Pinsir breaks the mold!");
        MESSAGE("Pinsir used Growl!");
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, opponent);
        MESSAGE("Foe Numel's Attack fell!");
    }
}

SINGLE_BATTLE_TEST("Mold Breaker ignores Wonder Skin")
{
    PASSES_RANDOMLY(5, 5, RNG_ACCURACY);
    GIVEN {
        PLAYER(SPECIES_PINSIR) { Ability(ABILITY_MOLD_BREAKER); };
        OPPONENT(SPECIES_DELCATTY) { Ability(ABILITY_WONDER_SKIN); };
    } WHEN {
        TURN { MOVE(player, MOVE_GROWL); }
    } SCENE {
        MESSAGE("Pinsir used Growl!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_GROWL, player);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, opponent);
    }
}

SINGLE_BATTLE_TEST("Mold Breaker ignores Tangled Feet")
{
    PASSES_RANDOMLY(5, 5, RNG_ACCURACY);
    GIVEN {
        PLAYER(SPECIES_PINSIR) { Ability(ABILITY_MOLD_BREAKER); };
        OPPONENT(SPECIES_DODRIO) { Ability(ABILITY_TANGLED_FEET); };
    } WHEN {
        TURN { MOVE(player, MOVE_CONFUSE_RAY); MOVE(opponent, MOVE_CELEBRATE); }
        TURN { MOVE(player, MOVE_POUND); MOVE(opponent, MOVE_CELEBRATE); }
    } SCENE {
        MESSAGE("Pinsir used Pound!");
        HP_BAR(opponent);
        MESSAGE("Foe Dodrio is confused!");
    }
}

SINGLE_BATTLE_TEST("Mold Breaker ignores Suction Cups")
{
    GIVEN {
        PLAYER(SPECIES_PINSIR) { Ability(ABILITY_MOLD_BREAKER); };
        OPPONENT(SPECIES_OCTILLERY) { Ability(ABILITY_SUCTION_CUPS); };
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponent, MOVE_CELEBRATE); MOVE(player, MOVE_ROAR); }
    } SCENE {
        MESSAGE("Foe Octillery used Celebrate!");
        MESSAGE("Pinsir used Roar!");
        MESSAGE("Foe Wobbuffet was dragged out!");
    }
}

SINGLE_BATTLE_TEST("Mold Breaker ignores Sticky Hold")
{
    u32 move;
    PARAMETRIZE { move = MOVE_KNOCK_OFF; }
    PARAMETRIZE { move = MOVE_THIEF; }
    PARAMETRIZE { move = MOVE_COVET; }
    PARAMETRIZE { move = MOVE_BUG_BITE; }
    PARAMETRIZE { move = MOVE_PLUCK; }
    PARAMETRIZE { move = MOVE_INCINERATE; }

    GIVEN {
        PLAYER(SPECIES_PINSIR) { Ability(ABILITY_MOLD_BREAKER); };
        OPPONENT(SPECIES_MUK) { Ability(ABILITY_STICKY_HOLD); Item(ITEM_SITRUS_BERRY); };
    } WHEN {
        TURN { MOVE(player, move); }
    } SCENE {

        switch (move) {

            case MOVE_KNOCK_OFF:
                MESSAGE("Pinsir used Knock Off!");
                MESSAGE("Pinsir knocked off Foe Muk's Sitrus Berry!");
                break;
            case MOVE_THIEF:
            case MOVE_COVET:
                if (move == MOVE_THIEF)
                    MESSAGE("Pinsir used Thief!");
                else
                    MESSAGE("Pinsir used Covet!");
                MESSAGE("Pinsir stole Foe Muk's Sitrus Berry!");
                break;
            case MOVE_BUG_BITE:
            case MOVE_PLUCK:
                if (move == MOVE_BUG_BITE)
                    MESSAGE("Pinsir used Bug Bite!");
                else
                    MESSAGE("Pinsir used Pluck!");
                MESSAGE("Pinsir stole and ate Foe Muk's Sitrus Berry!");
                break;
            case MOVE_INCINERATE:
                MESSAGE("Pinsir used Incinerate!");
                MESSAGE("Foe Muk's Sitrus Berry was burnt up!");
                break;
        }
    }
}

SINGLE_BATTLE_TEST("Mold Breaker ignores Heavy Metal", s16 damage)
{
    u32 ability;
    PARAMETRIZE { ability = ABILITY_ROCK_HEAD; }
    PARAMETRIZE { ability = ABILITY_HEAVY_METAL; }

    GIVEN {
        PLAYER(SPECIES_PINSIR) { Ability(ABILITY_MOLD_BREAKER); };
        OPPONENT(SPECIES_AGGRON) { Ability(ability); };
    } WHEN {
        TURN { MOVE(player, MOVE_HEAVY_SLAM); }
    } SCENE {
        MESSAGE("Pinsir used Heavy Slam!");
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(1.0), results[1].damage);
    }
}

SINGLE_BATTLE_TEST("Mold Breaker ignores Light Metal", s16 damage)
{
    u32 ability;
    PARAMETRIZE { ability = ABILITY_CLEAR_BODY; }
    PARAMETRIZE { ability = ABILITY_LIGHT_METAL; }

    GIVEN {
        PLAYER(SPECIES_PINSIR) { Ability(ABILITY_MOLD_BREAKER); };
        OPPONENT(SPECIES_METAGROSS) { Ability(ability); };
    } WHEN {
        TURN { MOVE(player, MOVE_HEAVY_SLAM); }
    } SCENE {
        MESSAGE("Pinsir used Heavy Slam!");
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(1.0), results[1].damage);
    }
}

TO_DO_BATTLE_TEST("Mold Breaker ignores Flower Gift");
// Cannot reliably write a test for this until Cherrim's transformation fix is merged.
// SINGLE_BATTLE_TEST("Mold Breaker ignores Flower Gift", s16 damage)
// {
//     u32 move;
//     PARAMETRIZE { move = MOVE_CELEBRATE; }
//     PARAMETRIZE { move = MOVE_SUNNY_DAY; }
//
//     GIVEN {
//         PLAYER(SPECIES_PINSIR) { Ability(ABILITY_MOLD_BREAKER); };
//         OPPONENT(SPECIES_CHERRIM) { Ability(ABILITY_FLOWER_GIFT); };
//     } WHEN {
//         TURN { MOVE(opponent, move); MOVE(player, MOVE_SHADOW_BALL); }
//     } SCENE {
//         if (move == MOVE_CELEBRATE) {
//             MESSAGE("Foe Cherrim used Celebrate!");
//             MESSAGE("Pinsir used Shadow Ball!");
//             HP_BAR(opponent, captureDamage: &results[i].damage);
//         } else {
//             MESSAGE("Foe Cherrim used Sunny Day!");
//             MESSAGE("Pinsir used Shadow Ball!");
//             HP_BAR(opponent, captureDamage: &results[i].damage);
//         }
//     } FINALLY {
//         EXPECT_MUL_EQ(results[0].damage, Q_4_12(1.0), results[1].damage);
//     }
// }

// According to both Bulbapedia and Smogon, Mold Breaker ignores Aura Break, however the Bulbapedia page on Aura Break seems to contradict this
// despite listing Aura Break in their own list of ignorable abilities. References below.
// https://www.smogon.com/dex/sv/abilities/mold-breaker/
// https://bulbapedia.bulbagarden.net/wiki/Ignoring_Abilities#Ignorable_Abilities
// https://bulbapedia.bulbagarden.net/wiki/Aura_Break_(Ability)
// Because of this, I'm not sure what do here as I've been unable to find conclusive information and would need
// someone with access to official games and the ability to test it to provide information.
TO_DO_BATTLE_TEST("Aura Break")
