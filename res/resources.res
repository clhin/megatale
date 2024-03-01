#Palettes
PALETTE ruinspal	"backgrounds/start.png"

#text

#Sprites
SPRITE heart_sprite	"sprites/heart.png" 1 1 FAST NONE
SPRITE battle_select	"sprites/battle_sheet.png" 7 3 FAST NONE 
SPRITE frisk_sprite	"sprites/frisk.png" 3 4 FAST 15

#Battle Sprites 
SPRITE flowey_battle "battle/flowey.png" 6 5 FAST NONE 

#Images
IMAGE font		"fonts/8bitfonts.png" BEST NONE

#Tilesets
TILESET room_one 	"backgrounds/start.png" AUTO 1
TILESET font_sheet 	"fonts/font_sheet.png" AUTO 1

#Portraits (Tilesets)
SPRITE portrait_flowey "portrait/flowey.png" 6 5 FAST NONE

#Maps
MAP room_1 		"backgrounds/start.png" room_one -1

#Battle Dialogue 
BIN flowey_battle_dialogue "battle/flowey.bin" 1 0 