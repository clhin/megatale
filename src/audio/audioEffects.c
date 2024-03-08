#include <audio/audioEffects.h>
#include <resources.h>
#define LEVELUP 64
#define LOWFLOWEYLAUGH 64
#define FLOWEYVOICE 64
#define MOVEMENU 64
#define TORIALTALK 64
#define SELECTSOUND 64
#define HEARTSHOTSOUND 64
#define BATTLEFALLSOUND 64
#define BELLSOUND 64
#define BOMBSOUND 64
#define DAMAGESOUND 64
#define FALLSOUND 64
#define SWITCHESSOUND 64
#define LIGHTSWITCHSOUND 64
#define PHONESOUND 64
#define SAVESOUND 64
#define SCREENSHAKESOUND 64
#define SPARKLESOUND 64
#define SWITCHPULLSOUND 64
#define TEXTNOISESOUND 64

void startHeartache() {
    // Start heartache in the background
    XGM_setLoopNumber(-1);
    XGM_startPlay(heartacheSmall);
}

void startRuins() {
    // Start ruins music
    XGM_setLoopNumber(-1);
    XGM_startPlay(ruins);
}



void levelUpSound() {
    XGM_setPCM(LEVELUP, levelup, sizeof(levelup));
    XGM_startPlayPCM(LEVELUP,1,SOUND_PCM_CH2);
}

void startFallenDown() {
    XGM_setLoopNumber(-1);
    XGM_startPlay(FallenDown);
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
    XGM_startPlay(uwa);
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
    XGM_setPCM(SELECTSOUND, sndselect, sizeof(sndselect));
    XGM_startPlayPCM(SELECTSOUND, 1, SOUND_PCM_CH2);
}

void heartshotSound() {
    XGM_setPCM(HEARTSHOTSOUND, heartshot, sizeof(heartshot));
    XGM_startPlayPCM(HEARTSHOTSOUND, 1, SOUND_PCM_CH2);
}

void battlefallSound() {
    XGM_setPCM(BATTLEFALLSOUND, battlefall, sizeof(battlefall));
    XGM_startPlayPCM(BATTLEFALLSOUND, 1, SOUND_PCM_CH2);
}


void bellSound() {
    XGM_setPCM(BELLSOUND, bell, sizeof(bell));
    XGM_startPlayPCM(BELLSOUND, 1, SOUND_PCM_CH2);
}

void bombSound() {
    XGM_setPCM(BOMBSOUND, bomb, sizeof(bomb));
    XGM_startPlayPCM(BOMBSOUND, 1, SOUND_PCM_CH2);
}

void damageSound() {
    XGM_setPCM(DAMAGESOUND, damage, sizeof(damage));
    XGM_startPlayPCM(DAMAGESOUND, 1, SOUND_PCM_CH2);
}

void fallSound() {
    XGM_setPCM(FALLSOUND, fall, sizeof(fall));
    XGM_startPlayPCM(FALLSOUND, 1, SOUND_PCM_CH2);
}

void switchSound() {
    XGM_setPCM(SWITCHESSOUND, switches, sizeof(switches));
    XGM_startPlayPCM(SWITCHESSOUND, 1, SOUND_PCM_CH2);
}

void lightSwitchSound() {
    XGM_setPCM(LIGHTSWITCHSOUND, lightSwitch, sizeof(lightSwitch));
    XGM_startPlayPCM(LIGHTSWITCHSOUND, 1, SOUND_PCM_CH2);
}

void phoneSound() {
    XGM_setPCM(PHONESOUND, phone, sizeof(phone));
    XGM_startPlayPCM(PHONESOUND, 1, SOUND_PCM_CH2);
}

void saveSound() {
    XGM_setPCM(SAVESOUND, sndsave, sizeof(sndsave));
    XGM_startPlayPCM(SAVESOUND, 1, SOUND_PCM_CH2);
}

void screenShakeSound() {
    XGM_setPCM(SCREENSHAKESOUND, screenShake, sizeof(screenShake));
    XGM_startPlayPCM(SCREENSHAKESOUND, 1, SOUND_PCM_CH2);
}

void sparkleSound() {
    XGM_setPCM(SPARKLESOUND, sparkle, sizeof(sparkle));
    XGM_startPlayPCM(SPARKLESOUND, 1, SOUND_PCM_CH2);
}

void switchPullSound() {
    XGM_setPCM(SWITCHPULLSOUND, switchPull, sizeof(switchPull));
    XGM_startPlayPCM(SWITCHPULLSOUND, 1, SOUND_PCM_CH2);
}

void textNoiseSound() {
    XGM_setPCM(TEXTNOISESOUND, textNoise, sizeof(textNoise));
    XGM_startPlayPCM(TEXTNOISESOUND, 1, SOUND_PCM_CH2);
}