TestArea_MapScripts::
    .byte 0

TestArea_EventScript_Boris::
    trainerbattle_single TRAINER_BORIS_1, TestArea_Text_BorisIntro, TestArea_Text_BorisDefeat, TestArea_EventScript_BorisDefeated, NO_MUSIC
    specialvar VAR_RESULT, ShouldTryRematchBattle
    goto_if_unset FLAG_RECEIVED_TM51, TestArea_EventScript_GiveBugBite
    msgbox TestArea_Text_BorisPostBattle, MSGBOX_DEFAULT
    release
    end

TestArea_EventScript_BorisDefeated::
    message TestArea_Text_RecievedHiveBadge
    waitmessage
    call Common_EventScript_PlayGymBadgeFanfare
    msgbox TestArea_Text_HiveBadgeInfoTakeThis, MSGBOX_DEFAULT
    setflag FLAG_BADGE01_GET
    call Common_EventScript_SetGymTrainers
    goto TestArea_EventScript_GiveBugBite
    end

TestArea_EventScript_GiveBugBite::
    giveitem ITEM_TM51
    goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
    setflag FLAG_RECEIVED_TM51
    msgbox TestArea_Text_ExplainBugBute, MSGBOX_DEFAULT
    release
    end

TestArea_Text_BorisIntro:
    .string "HELLO??? DOES THIS TEXT WORK?\p"
    .string "ahem, well hopefully...\p"
    .string "Anyways, let's see what\n"
    .string "you've got.$"

TestArea_Text_BorisDefeat:
    .string "Ha, so you've got what\n"
    .string "it takes?\p"
    .string "Believe it or not, most\n"
    .string "trainers journeys end here!$"

TestArea_Text_RecievedHiveBadge:
    .string "{PLAYER} received the Hive Badge\n"
    .string "from Boris.$"

TestArea_Text_HiveBadgeInfoTakeThis:
    .string "With your first badge, your level\n"
    .string "cap has been raised to 24.\p"
    .string "You'll also be able to use Rock Smash\n"
    .string "out of battle, even if none of your\p"
    .string "'mons knows it.\p"
    .string "BUT you should take a look at it,\n"
    .string "'cause it's a pretty decent move\p"
    .string "nowadays.\p"
    .string "Here, have this too.$"

TestArea_Text_ExplainBugBute:
    .string "That's TM51, Bug Bite.\n"
    .string "If your opponent relies on berries\p"
    .string "a lot, that can really throw a wrench\n"
    .string "in their plans.\p"
    .string "Of course, a TM can be used infinitely,\n"
    .string "so don't feel like you gotta save it.$"

TestArea_Text_BorisPostBattle:
    .string "I wasn't kidding earlier. Most trainers\n"
    .string "don't make it past their first gym.\p"
    .string "I'll be watching you, maybe later we can\n"
    .string "have a rematch with me at full power!$"
