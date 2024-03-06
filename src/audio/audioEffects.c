#include <audio/audioEffects.h>
#include <resources.h>
#define LEVELUP 64
#define LOWFLOWEYLAUGH 64
#define FLOWEYVOICE 64
#define MOVEMENU 64
#define TORIALTALK 64
#define SELECTSOUND 64

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

void startUWA() {
    XGM_setLoopNumber(-1);
    XGM_startPlay(&uwa);
}

void startFloweyTalk() {
    XGM_setPCM(FLOWEYVOICE, floweyVoice, sizeof(floweyVoice));
    XGM_startPlayPCM(FLOWEYVOICE, 1, SOUND_PCM_CH2);
}

void sndmoveMenu() {
    XGM_setPCM(MOVEMENU, moveMenu, sizeof(moveMenu));
    XGM_startPlayPCM(MOVEMENU, 1, SOUND_PCM_CH2);
}

void startTorialTalk() {
    XGM_setPCM(TORIALTALK, torialTalk, sizeof(torialTalk));
    XGM_startPlayPCM(TORIALTALK, 1, SOUND_PCM_CH2);
}

void selectSound() {
    XGM_setPCM(SELECTSOUND, select, sizeof(select));
    XGM_startPlayPCM(SELECTSOUND, 1, SOUND_PCM_CH2);
}