CinnabarIsland_Mart_MapScripts:: @ 816EA0F
	.byte 0

CinnabarIsland_Mart_EventScript_Woman:: @ 816EA10
	msgbox CinnabarIsland_Mart_Text_DontTheyHaveXAttack, MSGBOX_NPC
	end

CinnabarIsland_Mart_EventScript_Scientist:: @ 816EA19
	msgbox CinnabarIsland_Mart_Text_ExtraItemsNeverHurt, MSGBOX_NPC
	end

CinnabarIsland_Mart_EventScript_Clerk:: @ 816EA22
	goto_if_questlog EventScript_ReleaseEnd
	lock
	faceplayer
	message Text_MayIHelpYou
	waitmessage
	pokemart CinnabarIsland_Mart_Items
	msgbox Text_PleaseComeAgain
	release
	end

	.align 2
CinnabarIsland_Mart_Items:: @ 816EA48
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_GREAT_BALL
#ifdef SCALING_POKE_BALL_MULTIPLIER
	.2byte ITEM_POKE_BALL
#endif
	.2byte ITEM_HYPER_POTION
	.2byte ITEM_REVIVE
	.2byte ITEM_FULL_HEAL
	.2byte ITEM_ESCAPE_ROPE
	.2byte ITEM_MAX_REPEL
	.2byte ITEM_NONE
	release
	end
