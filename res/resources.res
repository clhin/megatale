#Palettes
PALETTE intropal	    "backgrounds/intro_1.png"
PALETTE ruinspal	    "backgrounds/start.png"
PALETTE textpal	"fonts/font_sheet.png"
#PALETTE ruinsmodified	"palettes/ruinsmodified.png"

#text
BIN introtext "dialog/introtext.txt" 2 2 0 APLIB FALSE
BIN flowey_battle_dialogue "dialog/floweyintro.txt" 2 2 0 APLIB FALSE

#Sprites
SPRITE heart_sprite	    "sprites/heart.png" 1 1 FAST NONE
SPRITE battle_select	"sprites/battle_sheet.png" 7 3 FAST NONE 
SPRITE frisk_sprite	    "sprites/frisk.png" 3 4 FAST 10

#Battle Sprites 
SPRITE health_sprite "battle/health.png" 1 1 FAST NONE 

SPRITE flowey_battle "battle/flowey.png" 6 5 FAST NONE 
SPRITE flowey_bullet "battle/flowey_bullet.png" 1 1 FAST 5
SPRITE flowey_toriel "battle/flowey_toriel.png" 9 13 FAST NONE  
SPRITE toriel_fireball "battle/toriel_fireball.png" 4 4 FAST 5 

#Tilesets
TILESET font			"fonts/8bitfonts.png" AUTO 0
TILESET dialogfont		"fonts/dialogfont.png" AUTO 0
TILESET title_tiles		"backgrounds/titlescreen.png" AUTO 1
TILESET intro_0_tiles		"backgrounds/intro_0.png" AUTO 1
TILESET intro_0_alt_tiles	"backgrounds/intro_0_alt.png" AUTO 1
TILESET intro_1_tiles		"backgrounds/intro_1.png" AUTO 1
TILESET intro_2_tiles		"backgrounds/intro_2.png" AUTO 1
TILESET intro_3_tiles		"backgrounds/intro_3.png" AUTO 1
TILESET intro_5_tiles		"backgrounds/intro_5.png" AUTO 1
TILESET intro_6_tiles		"backgrounds/intro_6.png" AUTO 1
TILESET intro_7_tiles		"backgrounds/intro_7.png" AUTO 1
TILESET intro_8_tiles		"backgrounds/intro_8.png" AUTO 1
TILESET intro_9_tiles		"backgrounds/intro_9.png" AUTO 1
TILESET intro_last_tiles 	"backgrounds/intro_last.png" AUTO 1
TILESET room_1_tiles 		"backgrounds/start.png" AUTO 1
TILESET room_main_tiles 	"backgrounds/mainroom.png" AUTO 1
TILESET room_ruins1_tiles	"backgrounds/room_ruins1.png" AUTO 1
TILESET room_ruins2_tiles	"backgrounds/room_ruins2.png" AUTO 1
TILESET font_sheet 		    "fonts/font_sheet.png" AUTO 1
TILESET start_menu_tiles    "backgrounds/mainroom.png" BEST ALL

#Portraits (Tilesets)
SPRITE portrait_flowey  "portrait/flowey.png" 6 5 FAST NONE

#Maps
MAP titlescreen		    "backgrounds/titlescreen.png" title_tiles -1
MAP intro_0_alt			"backgrounds/intro_0_alt.png" intro_0_alt_tiles -1
MAP intro_0		        "backgrounds/intro_0.png" intro_0_tiles -1
MAP intro_1		        "backgrounds/intro_1.png" intro_1_tiles -1
MAP intro_2		        "backgrounds/intro_2.png" intro_2_tiles -1
MAP intro_3		        "backgrounds/intro_3.png" intro_3_tiles -1
MAP intro_5		        "backgrounds/intro_5.png" intro_5_tiles -1
MAP intro_6		        "backgrounds/intro_6.png" intro_6_tiles -1
MAP intro_7		        "backgrounds/intro_7.png" intro_7_tiles -1
MAP intro_8		        "backgrounds/intro_8.png" intro_8_tiles -1
MAP intro_9		        "backgrounds/intro_9.png" intro_9_tiles -1
MAP intro_last		    "backgrounds/intro_last.png" intro_last_tiles -1
MAP room_1 		        "backgrounds/start.png" room_1_tiles -1
MAP room_main		    "backgrounds/mainroom.png" room_main_tiles -1
MAP room_ruins1		    "backgrounds/room_ruins1.png" room_ruins1_tiles -1
MAP room_ruins2		    "backgrounds/room_ruins2.png" room_ruins2_tiles -1
MAP start_menu          "backgrounds/mainroom.png" start_menu_tiles BEST 0

#Sounds (background music and sound effects)
XGM2    FallenDown      "sound/fallendown.vgm"
XGM2	startmenu	"sound/startmenu.vgm"
XGM2	yourbestfriend	"sound/yourbestfriend.vgm"
XGM2	anticipation	"sound/anticipation.vgm"
XGM2	determination	"sound/determination.vgm"
XGM2	unnecessarytension	"sound/unnecessary_tension.vgm"
XGM2	heartache	"sound/heartache.vgm"
XGM2	ruins		"sound/ruins.vgm"
XGM2    onceuponatime   "sound/onceuponatime.vgm"
XGM2	shop		"sound/shop.vgm"
XGM2	thundersnail	"sound/thundersnail.vgm"
XGM2	megalovania	"sound/megalovania.vgm"
XGM2	anothermedium	"sound/another_medium.vgm"
XGM2	showtime	"sound/itsshowtime.vgm"
XGM2	deathbyglamour	"sound/deathbyglamour.vgm"
XGM2	sans		"sound/sans.vgm"
