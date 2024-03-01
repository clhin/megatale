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

#Sound (Most of these are massive and need to be optimized)
XGM     ruins       "sound/ruinsSmall.vgm" -1           # Small version
WAV     levelup     "sound/levelup-16khz.wav" 5         # Small but has weird fuzz at the end
XGM     FallenDown  "sound/FallenDown.vgm"  -1          # Perfect (small and crispy)
WAV     lowFloweyLaugh "sound/lowFloweyLaugh.wav" 5     # Perfect (small and crispy)
WAV     floweyVoice  "sound/snd_floweytalk1.wav" 5       # Perfect (small and crispy)
XGM     heartacheSmall  "sound/heartacheSmall.vgm" -1   # Perfect (small and crispy)   
XGM     uwa         "sound/uwaSmall.vgm" -1             # Perfect (small and crispy)
