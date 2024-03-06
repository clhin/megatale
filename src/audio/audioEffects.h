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

#endif