#Palettes
PALETTE ruinspal	"backgrounds/start.png"

#text

#Sprites
SPRITE heart_sprite	"sprites/heart.png" 1 1 FAST NONE
SPRITE battle_select	"sprites/battle_sheet.png" 7 3 FAST NONE 
SPRITE frisk_sprite	"sprites/frisk.png" 3 4 FAST 15

#Images
IMAGE font		"fonts/8bitfonts.png" BEST NONE

#Tilesets
TILESET room_1_tiles 	"backgrounds/start.png" AUTO 1
TILESET room_main_tiles "backgrounds/mainroom.png" AUTO 1
TILESET font_sheet 	"fonts/font_sheet.png" AUTO 1

#Portraits (Tilesets)
SPRITE portrait_flowey "portrait/flowey.png" 6 5 FAST NONE

#Maps
MAP room_1 		"backgrounds/start.png" room_1_tiles -1
MAP room_main		"backgrounds/mainroom.png" room_main_tiles -1

#Sound (Most of these are massive and need to be optimized)
XGM     ruins       "sound/ruinsSmall.vgm" -1           # Small version
WAV     levelup     "sound/levelup-16khz.wav" 5         # Small but has weird fuzz at the end
XGM     FallenDown  "sound/FallenDown.vgm"  -1          # Perfect (small and crispy)
WAV     lowFloweyLaugh "sound/lowFloweyLaugh.wav" 5     # Perfect (small and crispy)
WAV     floweyVoice  "sound/snd_floweytalk1.wav" 5       # Perfect (small and crispy)
XGM     heartacheSmall  "sound/heartacheSmall.vgm" -1   # Perfect (small and crispy)   
XGM     uwa         "sound/uwaSmall.vgm" -1             # Perfect (small and crispy)
