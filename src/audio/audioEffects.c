#include <audio/audioEffects.h>
#include <resources.h>
#define LEVELUP 64
#define LOWFLOWEYLAUGH 64

void startHeartache() {
    // Start heartache in the background
    XGM_setLoopNumber(-1);
    XGM_startPlay(&heartacheSmall);
}

void startRuins() {
    // Start ruins music
    XGM_setLoopNumber(-1);
    XGM_startPlay(&ruins);
}



void levelUpSound() {
    XGM_setPCM(LEVELUP, levelup, sizeof(levelup));
    XGM_startPlayPCM(LEVELUP,1,SOUND_PCM_CH2);
}

void startFallenDown() {
    XGM_setLoopNumber(-1);
    XGM_startPlay(&FallenDown);
}

void pause() {
    XGM_pausePlay();
}

void resume() {
    XGM_resumePlay();
}

void startFloweyLaugh() {
    XGM_setPCM(LOWFLOWEYLAUGH, lowFloweyLaugh, sizeof(lowFloweyLaugh));
    XGM_startPlayPCM(LOWFLOWEYLAUGH,1,SOUND_PCM_CH2);
}


void startMegalovania() {
    XGM_setLoopNumber(-1);
    XGM_startPlay(&megalovania);
}