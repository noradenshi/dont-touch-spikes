#include "spike.h"
#include <raylib.h>
#include <stdlib.h>

const Vector2 spikeOrigin = {0, 0};
const float spikeSize = 40.f;
const int maxSpikes = 10;
Rectangle *spikeRecs;
int maxHeight;
int activeSpikes = 0;

void spike_init(const int max_height) {
    spikeRecs = malloc(sizeof(Rectangle) * maxSpikes);
    for (int i = 0; i < maxSpikes; i++) {
        spikeRecs[i].width = spikeSize;
        spikeRecs[i].height = spikeSize;
    }
    maxHeight = max_height;
}

void spike_next(const float x, const int n) {
    activeSpikes = (n > maxSpikes) ? maxSpikes : n;

    for (int i = 0; i < activeSpikes; i++) {
        spikeRecs[i].x = x;
        spikeRecs[i].y = rand() % maxHeight;
    }
}

void spike_reset() {
    activeSpikes = 0;
}

bool spike_checkCollision(const float birdHeight) {
    for (int i = 0; i < activeSpikes; i++) {
        if (birdHeight > spikeRecs[i].y &&
            birdHeight < spikeRecs[i].y + spikeRecs[i].height)
            return true;
    }
    return false;
}

void spike_draw() {
    for (int i = 0; i < activeSpikes; i++) {
        DrawRectanglePro(spikeRecs[i], spikeOrigin, 45.f, BLACK);
    }
}
