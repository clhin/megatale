#ifndef AUDIO_EFFECTS_H_
#define AUDIO_EFFECTS_H_
#include <genesis.h>
#include <resources.h>

// Pause any music playing
void pause();

// Resume any music that had been previously playing
void resume();

// Heartache soundtrack
void startHeartache();

// Ruins soundtrack
void startRuins();

// Level up sound effect
void levelUpSound();

// FallenDown soundtrack
void startFallenDown();

// Flowey Laugh (Big)
void startFloweyLaugh();

// UWA
void startUWA();

// Flowey Talk beep noise
void startFloweyTalk();

// Move menu sound
void sndmoveMenu();

// Torial talking sound
void startTorialTalk();

// Select sound (for selecting options in menu)
void selectSound();

// Heartshot sound effect
void heartshotSound();

// Battle Start Falling Sound
void battlefallSound();

// Bell sound
void bellSound();

// Bomb sound
void bombSound();

// Damage sound
void damageSound();

// Fall sound
void fallSound();

// Switch sound
void switchSound();

// Light switch sound
void lightSwitchSound();

// Phone call sound
void phoneSound();

// Save game sound
void saveSound();

// Screen shaking sound
void screenShakeSound();

// Sound of the sparkel things
void sparkleSound();

// Sound of the pull switches (may or may not be useful here)
void switchPullSound();

// Sound of text (not sure when we'd use this, maybe someone who knows the game more knows)
void textNoiseSound();

#endif