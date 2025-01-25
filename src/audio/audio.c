#include "audio.h"

void playmusic(const u8 * music, s8 loop) {
	XGM2_load(music);
        XGM2_setLoopNumber(loop);
        XGM2_play(music);
}
