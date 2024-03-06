#Palettes
PALETTE intropal	"backgrounds/intro_1.png"
PALETTE ruinspal	"backgrounds/start.png"

#text

#Sprites
SPRITE heart_sprite	"sprites/heart.png" 1 1 FAST NONE
SPRITE battle_select	"sprites/battle_sheet.png" 7 3 FAST NONE 
SPRITE frisk_sprite	"sprites/frisk.png" 3 4 FAST 15

#Images
IMAGE font		"fonts/8bitfonts.png" BEST NONE

#Tilesets
TILESET title_tiles		"backgrounds/titlescreen.png" AUTO 1
TILESET intro_0_tiles		"backgrounds/intro_0.png" AUTO 1
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
TILESET font_sheet 		"fonts/font_sheet.png" AUTO 1

#Portraits (Tilesets)
SPRITE portrait_flowey "portrait/flowey.png" 6 5 FAST NONE

#Maps
MAP titlescreen		"backgrounds/titlescreen.png" title_tiles -1
MAP intro_0		"backgrounds/intro_0.png" intro_0_tiles -1
MAP intro_1		"backgrounds/intro_1.png" intro_1_tiles -1
MAP intro_2		"backgrounds/intro_2.png" intro_2_tiles -1
MAP intro_3		"backgrounds/intro_3.png" intro_3_tiles -1
MAP intro_5		"backgrounds/intro_5.png" intro_5_tiles -1
MAP intro_6		"backgrounds/intro_6.png" intro_6_tiles -1
MAP intro_7		"backgrounds/intro_7.png" intro_7_tiles -1
MAP intro_8		"backgrounds/intro_8.png" intro_8_tiles -1
MAP intro_9		"backgrounds/intro_9.png" intro_9_tiles -1
MAP intro_last		"backgrounds/intro_last.png" intro_last_tiles -1
MAP room_1 		"backgrounds/start.png" room_1_tiles -1
MAP room_main		"backgrounds/mainroom.png" room_main_tiles -1

#Sound (Most of these are massive and need to be optimized)
XGM     ruins       "sound/ruinsSmall.vgm" -1           # Small version
WAV     levelup     "sound/levelup-16khz.wav" 5         # Small but has weird fuzz at the end
XGM     FallenDown  "sound/FallenDown.vgm"  -1          # Perfect (small and crispy)
WAV     lowFloweyLaugh "sound/lowFloweyLaugh.wav" 5     # Perfect (small and crispy)
WAV     floweyVoice  "sound/snd_floweytalk1.wav" 5      # Perfect (small and crispy)
XGM     heartacheSmall  "sound/heartacheSmall.vgm" -1   # Perfect (small and crispy)   
XGM     uwa         "sound/uwaSmall.vgm" -1             # Perfect (small and crispy)
WAV     moveMenu    "sound/movemenuSmall.wav" 5         # Perfect (small and crispy)
WAV     torialTalk  "sound/txtTorialSmall.wav" 5        # Perfect (small and crispy)
WAV     select      "sound/selectSmall.wav" 5           # Perfect (small and crispy)
