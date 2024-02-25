#pragma once
#include <raylib.h>

void spike_init(const int max_height);
void spike_next(const float new_x, int spikes_n);
void spike_reset();
bool spike_checkCollision(const float bird_y);
void spike_draw();
